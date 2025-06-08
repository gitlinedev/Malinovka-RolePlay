@include_a_samp_();
@include_a_samp_()
{
    #emit    stack    0x7FFFFFFF
    #emit    inc.s    cellmax
    static const ___[][] = {"protected from", "deamx"};
    #emit    retn
    #emit    load.s.pri    ___
    #emit    proc
    #emit    proc
    #emit    fill    cellmax
    #emit    proc
    #emit    stack    1
    #emit    stor.alt    ___
    #emit    strb.i    2
    #emit    switch    4
    #emit    retn
L1:
	#emit    jump    L1
	#emit    zero    cellmin
}
new 
	global_str[4097],
	mysql_string[800],
	SQL_STRING[4097],
	SQL_GET_ROW_STR[20][128],
	Global_Time,
	day_of_week;

#include <a_samp>

#undef MAX_PLAYERS
#define MAX_PLAYERS 100
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#include streamer
#include Pawn.CMD
#include a_mysql
#include sscanf2
#include foreach
#include sampvoice
#include md5
#include cef
#include fmt
#include mapandreas

new mysql, logs_skill_high;
//======================================[ macro ]================================================//

#define public:%0(%1) forward%0(%1); public%0(%1)
#define or ||
#define f format
#define SCM	SendClientMessage
#define SCMALL	SendClientMessageToAll
#define SCMF SendClientMessagef
#define PN(%0) PlayerName[%0]

#define SPD ShowPlayerDialog
#define SPDF ShowPlayerDialogf

#define str_f(%0,%1) format(SQL_STRING, sizeof SQL_STRING, %0, %1), SQL_STRING
#define CallTimeOutFunction SetTimerEx

stock sql_get_row(id_0, _:id_1[], array_size = sizeof(id_1)) 
{
	for new i; i < array_size; i++ do
		cache_get_row(id_0, id_1[i], SQL_GET_ROW_STR[i], mysql);
}

//======================================[ modules ]================================================//

#include modules/remove_build.pwn // удаление зданий
#include modules/data.pwn // массивы и цвета
#include modules/player_actions.pwn // массивы и цвета

//=====================================[ global server settings ]==================================//

#define Mode_Names 					   "Malinovka"
#define Mode_Text                      "Malinovka | Игра про Россию"

#define Mode_Site 		               "server-site.com"
#define Mode_Forum 					   "forum.server-site.com"

// MySQL
#define DB_HOST						   "localhost"
#define DB_USER						   "gs99002"
#define DB_TABLE					   "gs99002"
#define DB_PASSWORD					   "983Orange1MySQL152SQls399PHP"
#define DB_PORT						   3306

main()
{
	print("\n----------------------------------");
	print(" Lethality Productions 2025");
	print("----------------------------------\n");
}

public OnGameModeInit()
{
	Global_Time = gettime();
	MapAndreas_Init(MAP_ANDREAS_MODE_MINIMAL);
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	mysql = mysql_connect(DB_HOST, DB_USER, DB_TABLE, DB_PASSWORD, DB_PORT);

	if !mysql_errno(mysql) *then
		print("  [Data Base]: Ошибок не выявлено, загрузка продолжается!");
	else
		printf("  [Data Base]: Найденна ошибка '%d', повторяем подключение.", mysql_errno(mysql));

	mysql_log(LOG_ERROR | LOG_WARNING);
	mysql_set_charset("cp1251", mysql);
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	format(global_str, 256, "hostname %s",  Mode_Text);
    SendRconCommand(global_str);

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    ManualVehicleEngineAndLights();
   	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
	LimitPlayerMarkerRadius(70.0);
	SetNameTagDrawDistance(25.0);
   	ShowPlayerMarkers(2);
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	SetGameModeText(Mode_Text);

	new hour;
	
	Global_Time = gettime(hour);
	SetWorldTime(hour);
	
	day_of_week = getDayEx();
	
    SetTimer("ServerTimer", 1000, true);
    SetTimer("UpdatePlayer", 250, true);

	printf("main.amx was database connect_id [%d] (day %d)", logs_skill_high = CallRemoteFunction("@CONNECTION_LOG_BASE", "d", Global_Time, day_of_week));

	print("  [Game Mode]: Инициализация успешно завершена!");
	return 1;
}

public: UpdatePlayer()
{
	return 1;
}

public: ServerTimer()
{
	//new debug = GetTickCount();
	new year,month,day,minuite,second,hour;
   	getdate(year,month,day);
   	Global_Time = gettime(hour,minuite,second);


	if second == 0 *then
	{
		MinuteTimer();
	}
	//printf("ServerTimer: %d MS;", GetTickCount() - debug);
}
stock MinuteTimer()
{
	return 1;
}

public OnGameModeExit()
{
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraPos(playerid, 1958.3783, 1343.1572, 15.3746);
	SetPlayerCameraLookAt(playerid, 1958.3783, 1343.1572, 15.3746);
	return 1;
}

stock getDayEx()
{
    new hour, minuite, second, year, month, day, w = Global_Time, saturday = 1310155200, day_week;
    gettime(hour, minuite, second);
	getdate(year, month, day);
	while(w - saturday > 60 * 60 * 24)
    {
        w -= 60 * 60 * 24;
        day_week ++;
    }
    while(day_week >= 7) day_week -= 7;
	return day_week;
}
stock IsValidNickName(const player[MAX_PLAYER_NAME])
{
	for(new n = 0; n < strlen(player); n++)
	{
		if (player[n] == '_') return 1;
		if (player[n] == ']' || player[n] == '[') return 0;
	}
    return 0;
} 
public OnPlayerConnect(playerid)
{
	ClearPlayerData(playerid);
	GetPlayerName(playerid, PlayerName[playerid], MAX_PLAYER_NAME);

	if !IsValidNickName(PlayerName[playerid]) *then
		return Kick(playerid);

	GetPlayerIp(playerid, PlayerIp[playerid], 16);
	SetPlayerVirtualWorld(playerid, 1228);
	SetPlayerWeather(playerid, WeatherServer);
	ClearChatForPlayer(playerid);

	f(global_str, 150, "SELECT `ID`, `Mail` FROM accounts WHERE NickName = '%s' LIMIT 1;", PlayerName[playerid]);
    mysql_tquery(mysql, global_str, "GetPlayerDataMysql", "d", playerid);

	RemoveBuildings(playerid);

	return 1;
}

stock ClearChatForPlayer(playerid)
{
	for(new i; i < 20; i ++) SCM(playerid, -1, !" ");
	return 1;
}
public: SetRandomWeather() 
{
	new rand = random(sizeof Weather);
	SendClientMessageToAllf(COLOR_GREEN, "[Прогноз погоды] в области ожидается %s (+%d °С)", Weather[rand][WeatherName], Weather[rand][WeatherDegrees]);
    WeatherServer = Weather[rand][WeatherId];
	return SetWeather(WeatherServer);
}
public OnPlayerDisconnect(playerid, reason)
{
	PlayerName[playerid][0] = EOS;
	return 1;
}

public OnPlayerSpawn(playerid)
{
	new hour, minute, second;
	gettime(hour, minute, second);
	SetPlayerTime(playerid, hour, minute);
	SetPlayerWeather(playerid, WeatherServer);
	StopAudioStreamForPlayer(playerid);

	SettingSpawn(playerid);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

public OnPlayerText(playerid, text[])
{
	if !IsPlayerLogged{playerid} *then return false;

 	if(GetString(text, "xD"))
	{
		f(global_str, 18 + MAX_PLAYER_NAME, "%s валяется от смеха", PN(playerid));
		ProxDetector(25, playerid, global_str, COLOR_ME);
		return 0;
	}
	if(GetString(text, "("))
	{
		f(global_str, 36, "%s грустит", PN(playerid));
		ProxDetector(25, playerid, global_str, COLOR_ME);
		return 0;
	}
	if(GetString(text, "(("))
	{
		f(global_str, 50, "%s сильно расстроился", PN(playerid));
		ProxDetector(25, playerid, global_str, COLOR_ME);
		return 0;
	}
	if(GetString(text, "чВ"))
	{
		f(global_str, 48, "%s валяется от смеха", PN(playerid));
		ProxDetector(25, playerid, global_str, COLOR_ME);
		return 0;
	}
	if(GetString(text, ")"))
	{
		f(global_str, 39, "%s улыбается", PN(playerid));
		ProxDetector(25, playerid, global_str, COLOR_ME);
		return 0;
	}
	if(GetString(text, "))"))
	{
		f(global_str, 39, "%s смеётся", PN(playerid));
		ProxDetector(25, playerid, global_str, COLOR_ME);
		return 0;
	}

	f(global_str, 300, "- %s {FF0000}(%s)[%d]", text, PN(playerid), playerid);
	ProxDetector(30.0, playerid, global_str, -1);

	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		ApplyAnimation(playerid, !"PED", !"IDLE_CHAT", 4.1, 0, 1, 1, 1, 1, 1);
		CallTimeOutFunction("ClearAnim", 100 * strlen(text), false, "d", playerid);
	}
	SetPlayerChatBubble(playerid, text, COLOR_WHITE, 20.0, 10000);
	return 1;
}

public: ClearAnim(playerid) return ApplyAnimation(playerid, !"CARRY", !"crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);

stock ProxDetector(Float:radi, playerid, string[], color)
{
	if(IsPlayerConnected(playerid))
	{
		new Float:X, Float:Y, Float:Z;
		GetPlayerPos(playerid, X, Y, Z);
		
		foreach(new i: Player)
		{
			if (IsPlayerInRangeOfPoint(i,radi,X,Y,Z) && GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid)) SCM(i, color, string);
		}
	}
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	static inputtextsave[256];
	inputtextsave[0] = EOS; global_str = "";

	mysql_escape_string(inputtext, inputtextsave);
	
	for new i; i < strlen(inputtextsave); i ++ do
	{
		if inputtextsave[i] == '%' *then inputtextsave[i] = '#';
		else if inputtextsave[i] == '{' && inputtextsave[i+7] == '}' *then strdel(inputtextsave, i, i+8);
	}

	switch dialogid do
	{
		case 1:
	    {
			if(response)
			{
			    switch RegisterState[playerid] do
			    {
				    case 1:
				    {
						if(strlen(inputtextsave) < 6) return ShowRegisterDialog(playerid,RegisterState[playerid]);
						else if(!CheckPassword(inputtextsave)) return ShowRegisterDialog(playerid,RegisterState[playerid]);
						RegisterState[playerid] = 2;
						mysql_real_escape_string(inputtextsave, RegPass[playerid]);
						ShowRegisterDialog(playerid, RegisterState[playerid]);
					}
				    case 3:
				    {
						SetString(RegReferal[playerid],"No Referal");
						mysql_tquery(mysql, (str_f("SELECT `ID` FROM accounts WHERE NickName = BINARY('%s') LIMIT 1;", PlayerName[playerid])), "OnPlayerRegister", "ds", playerid, RegPass[playerid]);

				        //mysql_format(mysql, global_str, 256, "SELECT `ID` FROM `accounts` WHERE `NickName` = '%s' LIMIT 1", inputtextsave);
				        //mysql_tquery(mysql, global_str, "MysqlCheckNickReferal", "ds", playerid, inputtextsave);
				    }
				    default: return 0;
				}
			}
			else
			{
		        if(RegisterState[playerid] > 1)
		        {
		       	 	RegisterState[playerid] --;
					ShowRegisterDialog(playerid,RegisterState[playerid]);
				}
				else SPD(playerid, 2, DIALOG_STYLE_MSGBOX, !"{EE3366}Регистрация", !"{FFFFFF}Вы действительно желайте прервать регистрацию?", !"Да", !"Нет");

			}
			return 1;
		}
		case 2:
		{
			if !response *then return Kick(playerid);
			else if !strlen(inputtext) *then  return ShowLoginDialog(playerid);
			
			f(global_str, 150, "SELECT `Password` FROM `accounts` WHERE `NickName` = '%s' LIMIT 1", PN(playerid));
			mysql_tquery(mysql, global_str, "LoginDialogMysql", "ds", playerid, inputtext);
			return true;
		}
		case 3: 
		{
			if(response) RegSex[playerid] = 1;
			else if(!response) RegSex[playerid] = 2;
			RegisterState[playerid] = 3;
			ShowRegisterDialog(playerid, RegisterState[playerid]);
		}
	}
	return 1;
}

stock SetString(param_1[], param_2[], size = 300)
{
	return strmid(param_1, param_2, 0, strlen(param_2), size);
}

stock GetString(param1[],param2[])
{
	return !strcmp(param1, param2, false);
}

stock PlayerIP(playerid)
{
	return PlayerIp[playerid];
}


public: PlayerSpawn(playerid)
{
	if IsPlayerNPC(playerid) *then return 1;
    if IsPlayerInAnyVehicle(playerid) *then
	{
	    new Float:X, Float:Y, Float:Z;
	    GetPlayerPos(playerid, X, Y, Z);
		SetPlayerPos(playerid, X ,Y, Z);
	}
 	SettingSpawn(playerid);
	if pTemp[playerid][SpectPlayer] == true *then SpecPl(playerid, false);
	else SpawnPlayer(playerid);
	return 1;
}
stock SpecPl(playerid, bool:spec)
{
	pTemp[playerid][SpectPlayer] = spec;
	TogglePlayerSpectating(playerid, spec);
}
stock SettingSpawn(playerid)
{
	if IsPlayerNPC(playerid) *then return 1;
	new skin = 24; // 24 - skin id for player

	SetSpawnInfoEx(playerid, skin, 1802.0438, 2505.7705, 15.8725, 304.8401);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);

	return true;
}

stock SetSpawnInfoEx(playerid, skin, Float:x, Float:y, Float:z, Float:a)
{
    return SetSpawnInfo(playerid, 255, skin, x, y, z-0.4, a, 0, 0, 0, 0, 0, 0);
}

stock UpdatePlayerHealth(playerid, Float:hp)
{
	return SetPlayerHealth(playerid, PI[playerid][pHealth] = hp);
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}

CMD:test(playerid) return SetPlayerSkin(playerid, 35);

stock PreloadAllAnimLibs(playerid)
{
    PreloadAnimLib(playerid,"AIRPORT");     
    PreloadAnimLib(playerid,"Attractors");  
    PreloadAnimLib(playerid,"BAR"); 
    PreloadAnimLib(playerid,"BASEBALL");    
    PreloadAnimLib(playerid,"BD_FIRE");     
    PreloadAnimLib(playerid,"BEACH");       
    PreloadAnimLib(playerid,"benchpress");  
    PreloadAnimLib(playerid,"BF_injection");
    PreloadAnimLib(playerid,"BIKED");       
    PreloadAnimLib(playerid,"BIKEH"); 
    PreloadAnimLib(playerid,"BIKELEAP");      
    PreloadAnimLib(playerid,"BIKES"); 
    PreloadAnimLib(playerid,"BIKEV"); 
    PreloadAnimLib(playerid,"BIKE_DBZ");      
    PreloadAnimLib(playerid,"BLOWJOBZ");      
    PreloadAnimLib(playerid,"BMX");   
    PreloadAnimLib(playerid,"BOMBER");
    PreloadAnimLib(playerid,"BOX");   
    PreloadAnimLib(playerid,"BSKTBALL");      
    PreloadAnimLib(playerid,"BUDDY"); 
    PreloadAnimLib(playerid,"BUS");   
    PreloadAnimLib(playerid,"CAMERA");
    PreloadAnimLib(playerid,"CAR");   
    PreloadAnimLib(playerid,"CARRY"); 
    PreloadAnimLib(playerid,"CAR_CHAT");      
    PreloadAnimLib(playerid,"CASINO");
    PreloadAnimLib(playerid,"CHAINSAW");      
    PreloadAnimLib(playerid,"CHOPPA");
    PreloadAnimLib(playerid,"CLOTHES");       
    PreloadAnimLib(playerid,"COACH"); 
    PreloadAnimLib(playerid,"COLT45");
    PreloadAnimLib(playerid,"COP_AMBIENT");   
    PreloadAnimLib(playerid,"COP_DVBYZ");     
    PreloadAnimLib(playerid,"CRACK"); 
    PreloadAnimLib(playerid,"CRIB");  
    PreloadAnimLib(playerid,"DAM_JUMP");      
    PreloadAnimLib(playerid,"DANCING");       
    PreloadAnimLib(playerid,"DEALER");
    PreloadAnimLib(playerid,"DILDO"); 
    PreloadAnimLib(playerid,"DODGE"); 
    PreloadAnimLib(playerid,"DOZER"); 
    PreloadAnimLib(playerid,"DRIVEBYS");      
    PreloadAnimLib(playerid,"FAT");   
    PreloadAnimLib(playerid,"FIGHT_B");       
    PreloadAnimLib(playerid,"FIGHT_C");       
    PreloadAnimLib(playerid,"FIGHT_D");       
    PreloadAnimLib(playerid,"FIGHT_E");       
    PreloadAnimLib(playerid,"FINALE");
    PreloadAnimLib(playerid,"FINALE2");       
    PreloadAnimLib(playerid,"FLAME"); 
    PreloadAnimLib(playerid,"Flowers");       
    PreloadAnimLib(playerid,"FOOD");  
    PreloadAnimLib(playerid,"Freeweights");   
    PreloadAnimLib(playerid,"GANGS"); 
    PreloadAnimLib(playerid,"GHANDS");
    PreloadAnimLib(playerid,"GHETTO_DB");     
    PreloadAnimLib(playerid,"goggles");       
    PreloadAnimLib(playerid,"GRAFFITI");      
    PreloadAnimLib(playerid,"GRAVEYARD");     
    PreloadAnimLib(playerid,"GRENADE");       
    PreloadAnimLib(playerid,"GYMNASIUM");     
    PreloadAnimLib(playerid,"HAIRCUTS");      
    PreloadAnimLib(playerid,"HEIST9");
    PreloadAnimLib(playerid,"INT_HOUSE");     
    PreloadAnimLib(playerid,"INT_OFFICE");    
    PreloadAnimLib(playerid,"INT_SHOP");      
    PreloadAnimLib(playerid,"JST_BUISNESS");  
    PreloadAnimLib(playerid,"KART");  
    PreloadAnimLib(playerid,"KISSING");       
    PreloadAnimLib(playerid,"KNIFE"); 
    PreloadAnimLib(playerid,"LAPDAN1");       
    PreloadAnimLib(playerid,"LAPDAN2");       
    PreloadAnimLib(playerid,"LAPDAN3");       
    PreloadAnimLib(playerid,"LOWRIDER");      
    PreloadAnimLib(playerid,"MD_CHASE");      
    PreloadAnimLib(playerid,"MD_END");
    PreloadAnimLib(playerid,"MEDIC"); 
    PreloadAnimLib(playerid,"MISC");  
    PreloadAnimLib(playerid,"MTB");   
    PreloadAnimLib(playerid,"MUSCULAR");      
    PreloadAnimLib(playerid,"NEVADA");
    PreloadAnimLib(playerid,"ON_LOOKERS");    
    PreloadAnimLib(playerid,"OTB");   
    PreloadAnimLib(playerid,"PARACHUTE");     
    PreloadAnimLib(playerid,"PARK");  
    PreloadAnimLib(playerid,"PAULNMAC");      
    PreloadAnimLib(playerid,"ped");   
    PreloadAnimLib(playerid,"PLAYER_DVBYS");  
    PreloadAnimLib(playerid,"PLAYIDLES");     
    PreloadAnimLib(playerid,"POLICE");
    PreloadAnimLib(playerid,"POOL");  
    PreloadAnimLib(playerid,"POOR");  
    PreloadAnimLib(playerid,"PYTHON");
    PreloadAnimLib(playerid,"QUAD");  
    PreloadAnimLib(playerid,"QUAD_DBZ");      
    PreloadAnimLib(playerid,"RAPPING");       
    PreloadAnimLib(playerid,"RIFLE"); 
    PreloadAnimLib(playerid,"RIOT");  
    PreloadAnimLib(playerid,"ROB_BANK");      
    PreloadAnimLib(playerid,"ROCKET");
    PreloadAnimLib(playerid,"RUSTLER");       
    PreloadAnimLib(playerid,"RYDER"); 
    PreloadAnimLib(playerid,"SCRATCHING");    
    PreloadAnimLib(playerid,"SHAMAL");
    PreloadAnimLib(playerid,"SHOP");  
    PreloadAnimLib(playerid,"SHOTGUN");       
    PreloadAnimLib(playerid,"SILENCED");      
    PreloadAnimLib(playerid,"SKATE"); 
    PreloadAnimLib(playerid,"SMOKING");       
    PreloadAnimLib(playerid,"SNIPER");
    PreloadAnimLib(playerid,"SPRAYCAN");      
    PreloadAnimLib(playerid,"STRIP"); 
    PreloadAnimLib(playerid,"SUNBATHE");      
    PreloadAnimLib(playerid,"SWAT");  
    PreloadAnimLib(playerid,"SWEET"); 
    PreloadAnimLib(playerid,"SWIM");  
    PreloadAnimLib(playerid,"SWORD"); 
    PreloadAnimLib(playerid,"TANK");  
    PreloadAnimLib(playerid,"TATTOOS");       
    PreloadAnimLib(playerid,"TEC");   
    PreloadAnimLib(playerid,"TRAIN"); 
    PreloadAnimLib(playerid,"TRUCK"); 
    PreloadAnimLib(playerid,"UZI");   
    PreloadAnimLib(playerid,"VAN");   
    PreloadAnimLib(playerid,"VENDING");       
    PreloadAnimLib(playerid,"VORTEX");
    PreloadAnimLib(playerid,"WAYFARER");      
    PreloadAnimLib(playerid,"WEAPONS");       
    return PreloadAnimLib(playerid,"WUZI");
}

stock PreloadAnimLib(playerid, animlib[])
	return ApplyAnimation(playerid,animlib,"null",0.0,0,0,0,0,0);