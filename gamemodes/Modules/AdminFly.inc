static
	Float:FlyX[MAX_PLAYERS],
	Float:FlyY[MAX_PLAYERS],
	Float:FlyZ[MAX_PLAYERS],
	Float:FlyA[MAX_PLAYERS],

	FlyWorld[MAX_PLAYERS],
	FlyInt[MAX_PLAYERS],

	bool:FlySpawn[MAX_PLAYERS],
	FlyState[MAX_PLAYERS],
	FlyObject[MAX_PLAYERS],

	FlyLastMove[MAX_PLAYERS],
	FlyMode[MAX_PLAYERS],
	FlyLastUD[MAX_PLAYERS],
	FlyLastLR[MAX_PLAYERS],
	Float:FlyAccelmul[MAX_PLAYERS];

enum
{
	CAMERA_MODE_NONE	= 0,
	CAMERA_MODE_FLY		= 1,
	CAMERA_MODE_REVERSE	= 2
};
enum
{
	MOVE_FORWARD = 1,
	MOVE_BACK,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_FORWARD_LEFT,
	MOVE_FORWARD_RIGHT,
	MOVE_BACK_LEFT,
	MOVE_BACK_RIGHT
};

const
	Float:MOVE_SPEED = 175.0,
	Float:ACCEL_RATE = 0.06;


public: fly_OnPlayerConnect(playerid)
{
	FlyX[playerid] = 0.0;
	FlyY[playerid] = 0.0;
	FlyZ[playerid] = 0.0;
	FlyA[playerid] = 0.0;

	FlyWorld[playerid] = 0;
	FlyInt[playerid] = 0;

	FlyState[playerid] = CAMERA_MODE_NONE;

	FlyObject[playerid] = -1,

	bool:FlySpawn[playerid] = false;

	FlyLastMove[playerid] = 0;
	FlyMode[playerid] = 0;
	FlyLastUD[playerid] = 0;
	FlyLastLR[playerid] = 0;
	FlyAccelmul[playerid] = 0.0;
}

stock SetPlayerFlyStatus(playerid, status = 2)
{
	if(status == CAMERA_MODE_FLY && FlyState[playerid] == CAMERA_MODE_FLY)
		return SCM(playerid, COLOR_LIGHTGREY, !"Вы уже находитесь в режиме полета");

	else if(status == CAMERA_MODE_NONE && FlyState[playerid] == CAMERA_MODE_NONE)
		return SCM(playerid, COLOR_LIGHTGREY, !"Вы не находитесь в режиме полета");

	switch(status)
	{
		case CAMERA_MODE_NONE:
		{
			CancelEdit(playerid);
			GetPlayerCameraPos(playerid, FlyX[playerid], FlyY[playerid], FlyZ[playerid]);
			TogglePlayerSpectating(playerid, false);

			FlyState[playerid] = CAMERA_MODE_NONE;
			FlySpawn[playerid] = true;

			SCM(playerid, COLOR_LIGHTGREY, !"Вы вышли из режима полета");			
		}
		case CAMERA_MODE_FLY:
		{
			GetPlayerPos(playerid, FlyX[playerid], FlyY[playerid], FlyZ[playerid]);
			FlyWorld[playerid] = GetPlayerVirtualWorld(playerid);
			FlyInt[playerid] = GetPlayerInterior(playerid);
			GetPlayerFacingAngle(playerid, FlyA[playerid]);

			FlyObject[playerid] = CreatePlayerObject(playerid, 19300, FlyX[playerid], FlyY[playerid], FlyZ[playerid], 0.0, 0.0, 0.0);
			TogglePlayerSpectating(playerid, true);

			AttachCameraToPlayerObject(playerid, FlyObject[playerid]);

			FlyState[playerid] = CAMERA_MODE_FLY;

			SCM(playerid, COLOR_LIGHTGREY, !"Вы вошли в первый режим полета");		
		}
		case CAMERA_MODE_REVERSE:
		{
			if(FlyState[playerid] == CAMERA_MODE_NONE)
				return SetPlayerFlyStatus(playerid, CAMERA_MODE_FLY);
			else
				return SetPlayerFlyStatus(playerid, CAMERA_MODE_NONE);
		}
		default:
			return SCM(playerid, COLOR_LIGHTGREY, !"Вы ввели неверный режим полета") & 0;
	}
	return 1;
}

stock IsPlayerFlying(playerid)
	return FlyState[playerid];
	
public: fly_OnPlayerDeath(playerid, killerid, reason)
{
	if(IsPlayerFlying(playerid))
		SetPlayerFlyStatus(playerid, false);
}

public: fly_OnPlayerSpawn(playerid)
{
	if(FlySpawn[playerid] == true)
		SetTimerEx("@OnPlayerSpawnEx", 100, false, "i", playerid);

    return true;
}

@OnPlayerSpawnEx(playerid);
@OnPlayerSpawnEx(playerid)
{
	SetPlayerPos(playerid, FlyX[playerid], FlyY[playerid], FlyZ[playerid]);
	SetPlayerFacingAngle(playerid, FlyA[playerid]);
	SetPlayerVirtualWorld(playerid, FlyWorld[playerid]);
	SetPlayerInterior(playerid, FlyInt[playerid]);

	FlySpawn[playerid] = false;
	return 1;
}

public: fly_OnPlayerUpdate(playerid)
{
	if(FlyState[playerid] == CAMERA_MODE_FLY)
	{
		new keys, ud, lr;
		GetPlayerKeys(playerid, keys, ud, lr);
		
		if(FlyMode[playerid] && (GetTickCount() - FlyLastMove[playerid] > 100))
			MoveCamera(playerid);

		if(FlyLastUD[playerid] != ud || FlyLastLR[playerid] != lr)
		{
			if((FlyLastUD[playerid] != 0 || FlyLastLR[playerid] != 0) && ud == 0 && lr == 0)
			{
				StopPlayerObject(playerid, FlyObject[playerid]);
				FlyMode[playerid] = 0;
				FlyAccelmul[playerid] = 0.0;
			}
			else
			{

				FlyMode[playerid] = GetMoveDirectionFromKeys(ud, lr);
				MoveCamera(playerid);
			}
		}
		FlyLastUD[playerid] = ud;
		FlyLastLR[playerid] = lr;
		return 0;

	}
    return true;
}

stock MoveCamera(playerid)
{
	new
		Float:CameraPosX, Float:CameraPosY, Float:CameraPosZ,
		Float:CameraFrontX, Float:CameraFrontY, Float:CameraFrontZ;
		
	GetPlayerCameraPos(playerid, CameraPosX, CameraPosY, CameraPosZ);
	GetPlayerCameraFrontVector(playerid, CameraFrontX, CameraFrontY, CameraFrontZ);

	if(FlyAccelmul[playerid] <= 1)
		FlyAccelmul[playerid] += ACCEL_RATE;

	new
		Float:speed = MOVE_SPEED * FlyAccelmul[playerid],
		Float:x, Float:y, Float:z;
		
	GetNextCameraPosition(FlyMode[playerid], CameraPosX, CameraPosY, CameraPosZ, CameraFrontX, CameraFrontY, CameraFrontZ, x, y, z);
	MovePlayerObject(playerid, FlyObject[playerid], x, y, z, speed);

	FlyLastMove[playerid] = GetTickCount();
	return 1;
}

stock GetNextCameraPosition
	(
		move_mode,
		Float:CameraPosX, Float:CameraPosY, Float:CameraPosZ,
		Float:CameraFrontX, Float:CameraFrontY, Float:CameraFrontZ,
		&Float:x, &Float:y, &Float:z
	)
{
	new const
		Float:change = 6000.0,
		Float:PosX = CameraFrontX * change,
		Float:PosY = CameraFrontY * change,
		Float:PosZ = CameraFrontZ * change;

	switch(move_mode)
	{
		case MOVE_FORWARD:
		{
			x = CameraPosX + PosX;
			y = CameraPosY + PosY;
			z = CameraPosZ + PosZ;
		}
		case MOVE_BACK:
		{
			x = CameraPosX - PosX;
			y = CameraPosY - PosY;
			z = CameraPosZ - PosZ;
		}
		case MOVE_LEFT:
		{
			x = CameraPosX - PosY;
			y = CameraPosY + PosX;
			z = CameraPosZ;
		}
		case MOVE_RIGHT:
		{
			x = CameraPosX + PosY;
			y = CameraPosY - PosX;
			z = CameraPosZ;
		}
		case MOVE_BACK_LEFT:
		{
			x = CameraPosX + (-PosX - PosY);
 			y = CameraPosY + (-PosY + PosX);
		 	z = CameraPosZ - PosZ;
		}
		case MOVE_BACK_RIGHT:
		{
			x = CameraPosX + (-PosX + PosY);
 			y = CameraPosY + (-PosY - PosX);
		 	z = CameraPosZ - PosZ;
		}
		case MOVE_FORWARD_LEFT:
		{
			x = CameraPosX + (PosX  - PosY);
			y = CameraPosY + (PosY  + PosX);
			z = CameraPosZ + PosZ;
		}
		case MOVE_FORWARD_RIGHT:
		{
			x = CameraPosX + (PosX  + PosY);
			y = CameraPosY + (PosY  - PosX);
			z = CameraPosZ + PosZ;
		}
	}
}
stock GetMoveDirectionFromKeys(ud, lr)
{
	new
		direction = 0;

	if(lr < 0)
	{
		if(ud < 0)
			direction = MOVE_FORWARD_LEFT;
		else if(ud > 0)
			direction = MOVE_BACK_LEFT;
		else
			direction = MOVE_LEFT;
	}
	else if(lr > 0)
	{
		if(ud < 0)
			direction = MOVE_FORWARD_RIGHT;
		else if(ud > 0)
			direction = MOVE_BACK_RIGHT;
		else
			direction = MOVE_RIGHT;
	}
	else if(ud < 0)
		direction = MOVE_FORWARD;
	else if(ud > 0)
		direction = MOVE_BACK;

	return direction;
}

cmd:fly(playerid, params[])
{
    if(!CheckAccess(playerid, 2, 2))
		return 0;

    if(isnull(params)) 
        return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /fly [мод (0-2)]");

    new mode;

    if(sscanf(params, "d", mode)) 
        return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /fly [мод (0-2)]") & 0;
    
    if(!(mode >= 0 && mode <= 2))
        return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /fly [мод (0-2)]") & 0;

    return SetPlayerFlyStatus(playerid, mode);
}
/*cmd:checkfly(playerid, params[])
{
    static const MSG_USE_CMD[] = !"» Usage the command: /checkfly [playerid]";
    
    if(isnull(params)) {
        return SCM(playerid, -1, MSG_USE_CMD) & 0;
    }

    new id;
    if(sscanf(params, "u", id)) {
        return SCM(playerid, -1, MSG_USE_CMD) & 0;
    }

    if(id == INVALID_PLAYER_ID) {
        return SCM(playerid, -1, !"The player is not connected") & 0;
    }

    static const status_fly[][] =
    {
        !"The player is not flying",
        !"The player is flying"
    };
    
    SCM(playerid, -1, status_fly[IsPlayerFlying(id)]);
    return 1;
}*/