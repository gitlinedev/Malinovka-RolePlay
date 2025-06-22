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
	//day_of_week,
	Global_Time;

#include <a_samp>

#undef MAX_PLAYERS
#define MAX_PLAYERS 50

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#include streamer
#include Pawn.CMD
#include a_mysql
#include sscanf2
#include foreach
#include fmt 
#include sampvoice
#include cef
#include md5

#define DEBUG
#include nex-ac_ru.lang
#include nex-ac

#include mapandreas
#include UnixConvertor

new mysql;
//======================================[ macro ]================================================//

#define public:%0(%1) forward%0(%1); public%0(%1)
#define or ||
#define f format
#define SCM	SendClientMessage
#define SCMALL	SendClientMessageToAll
#define SCMALLF	SendClientMessageToAllf
#define SCMF SendClientMessagef
#define PN(%0) PlayerName[%0]

#define SPD ShowPlayerDialog
#define SPDF ShowPlayerDialogf

#define PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define RELEASED(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
#define HOLDING(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

#define IsPlayerOnline(%0) (!(%0 == INVALID_PLAYER_ID) && IsPlayerLogged{%0} && IsPlayerConnected(%0))
#define SAMF(%0,%1,%2) format(global_str, 256, %1,%2), SendAdminsMessage(%0, global_str)
#define SQL(%0,%1) format(SQL_STRING, sizeof SQL_STRING, %0, %1), mysql_tquery(mysql, SQL_STRING)
#define str_f(%0,%1) format(SQL_STRING, sizeof SQL_STRING, %0, %1), SQL_STRING
#define CallTimeOutFunction SetTimerEx

#define float_GetPlayerData(%0,%1) GetPVarFloat(%0, %1)
#define float_SetPlayerData(%0,%1,%2) SetPVarFloat(%0, %1, %2)
#define Int_GetPlayerData(%0,%1) GetPVarInt(%0, %1)
#define Int_SetPlayerData(%0,%1,%2) SetPVarInt(%0, %1, %2)

#define DPlayerData(%0,%1) DeletePVar(%0, %1)

public: PlayKick(playerid)
{
	return Kick(playerid);
}
stock PrepareKickCamera(playerid)
{
	cef_emit_event(playerid, "execute.event:hud:active", CEFINT(1));
	SpecPl(playerid, true);
	InterpolateCameraPos(playerid, 1864.6229, 2067.9146, 25.7431, 1864.6229, 2067.9146, 25.7431, 10000000);
	InterpolateCameraLookAt(playerid, 1821.6516, 2095.7375, 16.1631, 1821.6516, 2095.7375, 16.1631, 1000);

	return CallTimeOutFunction("PlayKick", 1000, false, "d", playerid);
}

stock sql_get_row(id_0, _:id_1[], array_size = sizeof(id_1)) 
{
	for new i; i < array_size; i++ do
		cache_get_row(id_0, id_1[i], SQL_GET_ROW_STR[i], mysql);
}

new PlayerDialogList[MAX_PLAYERS][64];

#define spdList(%0,%1,%2) PlayerDialogList[%0][%1] = %2
#define gpdList(%0,%1) PlayerDialogList[%0][%1]

//======================================[ limits ]================================================//
//
//======================================[ modules ]================================================//

#include Modules/dialogData // ид диалогов
#include Modules/Data // массивы и цвета
#include Modules/VoiceChat // голосовой чат
#include Modules/AntiCheat // анти-чит
#include Modules/Accounts // авторизация и регистрация
#include Modules/Admin // система админов
#include Modules/DefaultCMD // команды по умолчанию
#include Modules/SQL // работа с базой данных
#include Modules/CEFClient // цеф
#include Modules/Session // сессии игроков
#include Modules/Moderators // модераторы

#include Modules/RemoveBuild // удаление зданий
#include Modules/Test // тестовый модуль

//=====================================[ global server settings ]==================================//

#define Mode_Names 					   "Malinovka"
#define Mode_HostName                  "Malinovka RolePlay | Сервер #1"

#define Mode_Site 		               "m-bonus.com"
#define Mode_Forum 					   "forum.m-bonus.com"

// MySQL
#define DB_HOST						   "localhost"
#define DB_USER						   "gs99874"
#define DB_TABLE					   "gs99874"
#define DB_PASSWORD					   "oupqydrv"
#define DB_PORT						   3306

main()	
{
	cef_subscribe("execute.emit:dialog-responce", "InterfaceDialogResponce");
	cef_subscribe("execute.emit:radial-responce", "RadialResponce");
	cef_subscribe("execute.emit:select-clothes", "SelectClothesResponce");
	return 1;
}

public OnGameModeInit()
{
	new inittime = GetTickCount();

	Global_Time = gettime();
	MapAndreas_Init(MAP_ANDREAS_MODE_MINIMAL);

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	mysql = mysql_connect(DB_HOST, DB_USER, DB_TABLE, DB_PASSWORD, DB_PORT);

	if !mysql_errno(mysql) *then
		print("[Data Base]: Ошибок не выявлено, загрузка продолжается!");
	else
		printf("[Data Base]: Найденна ошибка '%d', повторяем подключение.", mysql_errno(mysql));

	mysql_log(LOG_ERROR | LOG_WARNING);
	mysql_set_charset("cp1251", mysql);

	#include Modules/MysqlLoad

	EnableAntiCheat(39, 0); // отключил dialog hack 
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	format(global_str, 256, "hostname %s",  Mode_HostName);
    SendRconCommand(global_str);

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    ManualVehicleEngineAndLights();
   	EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
	LimitPlayerMarkerRadius(70.0);
	SetNameTagDrawDistance(25.0);
   	ShowPlayerMarkers(2);
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	SetGameModeText(Mode_Names);

	new hour;
	
	Global_Time = gettime(hour);
	SetWorldTime(hour);
	
	//day_of_week = getDayEx();
	
    SetTimer("ServerTimer", 1000, true);
    SetTimer("UpdatePlayer", 250, true);

	// ЗОНЫ
	JailZone = CreateDynamicPolygon(JailZonePos);

	printf("[Game Mode]: Инициализация успешно завершена! [ %d MS ]", GetTickCount() - inittime);
	return 1;
}

public: UpdatePlayer()
{
	return 1;
}

public: ServerTimer()
{
	new year,month,day,minuite,second,hour;
   	getdate(year,month,day);
   	Global_Time = gettime(hour,minuite,second);

	if minuite == 45 && second == 0 *then
	{
		SetRandomWeather();
	}

	if minuite == 30 && second == 0 *then
	{
		SCMALL(0xEE3366FF, !"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		SCMALL(0xFFFFFFFF, !"Для посещения игрового магазина посетите сайт: {EE3366}"Mode_Site"");
		SCMALL(0xFFFFFFFF, !"Общение игроков и торговая площадка - ждём тебя! {EE3366}vk.com/mbonus_free");
		SCMALL(0xFFFFFFFF, !"В нашей игре действует реферальная система. Подброности на {EE3366}"Mode_Site"/ref");
		SCMALL(0xFFFFFFFF, !"При возникновении вопросов по игре обращайтесь в тех. поддержку: {EE3366}"Mode_Site"/help");
		SCMALL(0xEE3366FF, !"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}

	if second == 0 *then
	{
		MinuteTimer();
	}
	
	UpdatePlayers();
}
stock MinuteTimer()
{
	return 1;
}

public OnGameModeExit()
{
	mysql_close(mysql);
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    SetSpawnInfo(playerid, 255, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0);
	if(IsPlayerLogged{playerid})
	{
		PlayerSpawn(playerid);
		SetPlayerSkinEx(playerid, GetSkinOfPlayer(playerid));
	}
	return 0;
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
		return PrepareKickCamera(playerid);

	GetPlayerIp(playerid, PlayerIp[playerid], 16);
	SetPlayerVirtualWorld(playerid, 1228);
	SetPlayerWeather(playerid, 18);
	//ClearChatForPlayer(playerid);

	if SvGetVersion(playerid) == SV_NULL *then SCM(playerid, 0xEE83F0AA, !"[VoiceChat] {FFFFFF}загрузка плагина произошла {FFFF33}неуспешно (NULL)");
    else if SvHasMicro(playerid) == SV_FALSE *then SCM(playerid, 0xEE83F0AA, !"[VoiceChat] {FFFFFF}загрузка плагина произошла {FFFF33}c ошибкой (MIC)");
    else if ((LocalStream[playerid] = SvCreateDLStreamAtPlayer(30.0, 0xEE83F0AA, playerid, 0xff0000ff, !"")))
    {
        if (GlobalStream) SvAttachListenerToStream(GlobalStream, playerid);
        SvAddKey(playerid, 0x58);
    }

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

	foreach(new i: Player)
	{
		if(IsPlayerLogged{i})
		{
			if(PI[i][pShowRain] == 1 && (WeatherServer == 9 || WeatherServer == 8 || WeatherServer == 7))
			{
				SCM(i, COLOR_GREEN, !"[Подсказка] Вы можете отключить дождь в /mn > Настройки аккаунта, если он снижает производительность и FPS");
				SetPlayerWeather(i, WeatherServer);
			}
			else
			{
				SetPlayerWeather(i, 18);
			}
		}
	}
	return 1;
}
public OnPlayerDisconnect(playerid, reason)
{
	if IsPlayerLogged{playerid} *then
	{
		if Iter_Contains(Admin, playerid) *then Iter_Remove(Admin, playerid);
		if Iter_Contains(Event, playerid) *then Iter_Remove(Event, playerid);

		DPlayerData(playerid, !"vr");

		SaveAccount(playerid);
		IsPlayerLogged{playerid} = false;

		f(global_str, 110, "UPDATE `accounts` SET `OnlineStatus` = '0', `PlayerID` = '65535' WHERE `ID` = '%d'", PI[playerid][pID]);
		mysql_tquery(mysql, global_str);

		f(global_str, 120, "DELETE FROM `client` WHERE `NickName` = '%s'", PN(playerid));
		mysql_tquery(mysql, global_str);
	}
	PlayerName[playerid][0] = EOS;
	
	new DisconnectReason[3][] = {
        "Таймаут/Краш",
        "Выход",
        "Кик/Бан"
    };
	printf("*[Player Disconnect]*: %s (%d) - %s", PN(playerid), playerid, DisconnectReason[reason]);
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
	if IsPlayerNPC(playerid) *then 
		return true;

    if IsPlayerLogged{playerid} *then
    {
		foreach(Player, i)
		{
			if PI[i][pAdmin] && !AInfo[i][admKillList] *then
				SendDeathMessageToPlayer(i, killerid, playerid, reason);
		}
	}
	return 1;
}

stock SendAdminsMessage(color, const text[])
{
	foreach(new i: Admin)
	{
		if PI[i][pAdmin] && ALogin{i} *then
		{
			SCM(i, color, text);
		}
	}
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


	for(new i; i < 5; i++)
	{
		if(GetString(text, sInfo[i][smInput]))
		{
			if(PI[playerid][pSex] == 1)
			{
			    f(global_str, 48, "%s %s", PN(playerid), sInfo[i][smOutput_M]);
				ProxDetector(25, playerid, global_str, COLOR_PURPLE);
			}
			else
			{
				f(global_str, 48, "%s %s", PN(playerid), sInfo[i][smOutput_F]);
				ProxDetector(25, playerid, global_str, COLOR_PURPLE);
			}
			return 0;
		}
	}

	f(global_str, 300, "- %s {%s}(%s)[%d]", text, TeamColors[GetTeamID(playerid)][ColorStr], PN(playerid), playerid);
	ProxDetector(30.0, playerid, global_str, -1);

	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && !AnimPlayed{playerid})
	{
		ApplyAnimation(playerid, !"PED", !"IDLE_CHAT", 4.1, 0, 1, 1, 1, 1, 1);
		CallTimeOutFunction("ClearAnim", 100 * strlen(text), false, "d", playerid);
	}
	SetPlayerChatBubble(playerid, text, COLOR_WHITE, 20.0, 10000);
	return 0;
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
	AC_OnPlayerKeyStateChange(playerid, newkeys);

	if(PRESSED(KEY_NO))
	{
		callcmd::engine(playerid,"");
		return 1;
	}
	return 1;
}

public OnPlayerUpdate(playerid)
{
	if !IsPlayerLogged{playerid} *then return false;
	else if IsPlayerLogged{playerid} && IsPlayerConnected(playerid) *then
	{
		if PI[playerid][pShowFPS] == 1 *then 
		{
			new getFPS = GetPlayerFPS(playerid);

			if (getFPS >= 0)
			{
				pTemp[playerid][pCurrentFPS] = getFPS;
			}
			cef_emit_event(playerid, "execute.event:fps", CEFINT(pTemp[playerid][pCurrentFPS]));
		}
	}
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

	accounts_OnDialogResponse(playerid, dialogid, response, inputtextsave);
	admin_OnDialogResponse(playerid, dialogid, response, listitem, inputtextsave);
	k_OnDialogResponse(playerid, dialogid, response, listitem, inputtextsave);

	switch dialogid do
	{

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
		SetPlayerPosEx(playerid, X ,Y, Z);
	}
	GangZoneShowForPlayer(playerid, gGangZoneId, 0xFFFF0096);

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
	new skin = GetSkinOfPlayer(playerid);

	if PI[playerid][pJailTime] > 0 *then // отправка в тюрягу
	{	
		SetSpawnInfoEx(playerid, skin, 100.000, 100.000, 100.000, 0.0);
						
		SetPlayerInteriorEx(playerid, 0);
		UpdatePlayerHealth(playerid, 100);
		return 1;
	}
	else if PI[playerid][pDemorgan] > 0 *then // отправка в деморган
	{
		SetSpawnInfoEx(playerid, skin, -1764.1515, -2889.2085, 14.3141, 240.8832);
		UpdatePlayerHealth(playerid, 100);
		SetPlayerInteriorEx(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerSkin(playerid, 100);
		return 1;
	}
	else if PI[playerid][pHospital] > 0 && !IsAtOpg(playerid) *then // отправка в больку
	{
		if !IsAArmy(playerid) *then
	    {
	        switch(random(2))
			{
				case 0: SetSpawnInfoEx(playerid, skin, 100.000, 100.000, 100.000,90.000); // казарма спавн 1
				case 1: SetSpawnInfoEx(playerid, skin, 100.000, 100.000, 100.000,90.000); // казарма спавн 2
			}
			SetPlayerVirtualWorld(playerid, 2);
			SetPlayerInteriorEx(playerid, 2);
        }
		else
		{
			SetSpawnInfoEx(playerid, skin, 100.000, 100.000, 100.000,90.000); // дефолт болька для всех
			SetPlayerVirtualWorld(playerid, 1);
  			SetPlayerInteriorEx(playerid, 2);
			return 1;
		}
	    UpdatePlayerHealth(playerid, 25);
	    return 1;
	}
	else if PI[playerid][pSpawnSetting] == 0 && !IsAArmy(playerid) *then // вокзал
	{
		if PI[playerid][pLevel] < 3 *then
		{
			switch random(2) do
			{
				case 0: SetSpawnInfoEx(playerid, skin, 1802.0438, 2505.7705, 15.8725, 304.8401); // спавн 1 (батырево)
				case 1: SetSpawnInfoEx(playerid, skin, 1802.0438, 2505.7705, 15.8725, 304.8401); // спавн 2 (батырево)
			}
			SetPlayerInteriorEx(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			return true;
		}
		//
		else if(PI[playerid][pLevel] >= 3 && PI[playerid][pLevel] < 8)
		{
			SetSpawnInfoEx(playerid, skin, 1802.0438, 2505.7705, 15.8725, 304.8401); // спавн 1 (бусаево)
			SetPlayerInteriorEx(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			return 1;
		}
		else if(PI[playerid][pLevel] >= 5 && PI[playerid][pLevel] < 20)
		{
			SetSpawnInfoEx(playerid, skin, 1802.0438, 2505.7705, 15.8725, 304.8401); // спавн 1 (южка)
			SetPlayerInteriorEx(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			return 1;
		}
		return 1;
	}
	else if PI[playerid][pSpawnSetting] == 1 && !IsAArmy(playerid) *then // дом/квартира
	{
		return 1;
	}
	else if PI[playerid][pSpawnSetting] == 2 && GetTeamID(playerid) != 0 *then // орга
	{
		SetPlayerFacingAngle(playerid,SpawnInfo[PI[playerid][pMember]][3]);
		SetPlayerInteriorEx(playerid,SpawnIntWorld[PI[playerid][pMember]][0]);
		SetPlayerVirtualWorld(playerid,SpawnIntWorld[PI[playerid][pMember]][1]);
		SetSpawnInfoEx(playerid, skin, SpawnInfo[PI[playerid][pMember]][0], SpawnInfo[PI[playerid][pMember]][1], SpawnInfo[PI[playerid][pMember]][2], SpawnInfo[PI[playerid][pMember]][3]);
		return 1;
	}

	// если нет спавна то спавним на дефолт респе
	SetSpawnInfoEx(playerid, skin, 1802.0438, 2505.7705, 15.8725, 304.8401); // батырево вокзал
	SetPlayerInteriorEx(playerid, 0);
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
	return ApplyAnimation(playerid, animlib, !"null",0.0,0,0,0,0,0);

stock SendMuteMessage(playerid)
	return SCM(playerid, COLOR_GREY, !"Ваш чат временно заблокирован");

stock IsAIP(text[])
{
	new numbers;
	for(new i = 0;i < strlen(text); i++) if('0' <= text[i] <= '9') if(!('0' <= text[i+1] <= '9')) numbers ++;
	if(numbers >= 4) return 1;
	return 0;
}

stock ApplyAnimationEx(playerid, animlib[], animname[], Float:speed = 4.0, ab = 0, abc = 0, abcd = 0, abcde = 0, abcdef = 0, abcdefg = 1)
{
	return ApplyAnimation(playerid, animlib, animname, speed, ab, abc, abcd, abcde, abcdef, abcdefg);
}
stock ClearAnimationsEx(playerid)
{
    ClearAnimations(playerid);
    ApplyAnimationEx(playerid, "BD_FIRE", "BD_Fire1", 4.1, 0, 0, 0, 0, 1, 1);
	AnimPlayed{playerid} = false;
	return true;
}
stock UpdatePlayerPos(playerid, Float:X, Float:Y, Float:Z, Float:A = -1.0)
{
	if !(A == -1.0) *then SetPlayerFacingAngle(playerid, A);

	return Streamer_UpdateEx(playerid, X,Y,Z, -1, -1, -1, 500, 1);
}

stock SetPlayerSkinEx(playerid, skin)
{
	SetPlayerSkin(playerid, skin);
	UpdatePlayerDataInt(playerid, "Skin", PI[playerid][pSkin]);
	return 1;
}
stock SetPlayerArmourEx(playerid, Float:armour)
{
	if IsPlayerNPC(playerid) *then return 1;

	PI[playerid][pArmour] = armour;
	return SetPlayerArmour(playerid, armour);
}
stock ShiftCords(style, &Float:x, &Float:y, Float:a, Float:distance)
{
	switch(style)
	{
	    case 0:
	    {
	        x += (distance * floatsin(-a, degrees));
			y += (distance * floatcos(-a, degrees));
	    }
	    case 1:
		{
		    x -= (distance * floatsin(-a, degrees));
			y -= (distance * floatcos(-a, degrees));
		}
		default: return 0;
	}
	return 1;
}
stock ClearCarData(CarID) 
{
	VehicleInfo[CarID][vID] = INVALID_VEHICLE_ID;

	VehicleInfo[CarID][vFuel] = 
	VehicleInfo[CarID][vPos_X] = 
	VehicleInfo[CarID][vPos_Y] = 
	VehicleInfo[CarID][vPos_Z] = 
	VehicleInfo[CarID][vPos_A] = 0.0;

	VehicleInfo[CarID][vModel] = -1;
	
	VehicleInfo[CarID][vColor_1] =
	VehicleInfo[CarID][vColor_2] =
	VehicleInfo[CarID][vKey] =
	VehicleInfo[CarID][vAdminCar] = 0;
}

stock IsWordsInvalid(playerid, const text[])
{
    for(new i = 0; i < MAX_INWORDS; i++)
    {
        if(strfind(text, InvalidWords[i][20]) != -1)
        {
            return true;
        }
    }
    return false;
}

stock SendDebugMessage(const debugMsg[])
{
	SAMF(COLOR_ADMINCHAT, "[Откладка] %s", debugMsg);
	printf("[Откладка]: %s", debugMsg);
}

stock _GiveGun(playerid, weaponid, ammo)
{
	GivePlayerWeapon(playerid, weaponid, ammo);
	return 1;
}

stock _ResetPlayerWeapons(playerid) 
{
    ResetPlayerWeapons(playerid);
    return 1;
}
stock GetTeamID(playerid)
{
	if(PI[playerid][pMember] > 0) return PI[playerid][pMember];
	if(PI[playerid][pLeader] > 0) return PI[playerid][pLeader];
	return 0;
}
stock IsAtOpg(playerid)
{
	new team = GetTeamID(playerid);
	switch(team)
	{
	    case TEAM_SKINHEAD,TEAM_KAVKAZ,TEAM_GOPOTA: return 1;
	    default: return 0;
	}
	return 0;
}
stock IsAArmy(playerid)
{
	new team = GetTeamID(playerid);
	switch(team)
	{
	    case TEAM_ARMY: return 1;
	}
	return 0;
}
//
stock UpdatePlayers()
{
	new year,month,day,minuite,second,hour; 
	getdate(year,month,day);
	gettime(hour,minuite,second);

	foreach(Player, playerid)
	{
		if IsPlayerLogged{playerid} *then
		{
			if(!IsPlayerNPC(playerid))
	    	{
				if PI[playerid][pDemorgan] > 0 *then
				{
					PI[playerid][pDemorgan] --;
					
					if !PI[playerid][pDemorgan] *then
					{
						SCM(playerid, COLOR_LIGHTGREY, !"Срок заключения истек, вы были автоматически освобождены");
						RemoveActivePunishment(playerid, 1);
						PlayerSpawn(playerid);
						UpdatePlayerDataInt(playerid, "Demorgan", 0);
					}
				}
				if PI[playerid][pMuteTime] > 0 *then
				{
					PI[playerid][pMuteTime] --;

					if !PI[playerid][pMuteTime] *then 
					{
						SCM(playerid, COLOR_LIGHTGREY, !"Блокировка текстового чата истекла.");
						UpdatePlayerDataInt(playerid, "MuteTime", 0);
					}
				}
				if PI[playerid][pVMuteTime] > 0 *then
				{
					PI[playerid][pVMuteTime] --;

					if !PI[playerid][pVMuteTime] *then 
					{
						SCM(playerid, COLOR_LIGHTGREY, !"Блокировка голосового чата истекла.");
						SvMutePlayerDisable(playerid);
						UpdatePlayerDataInt(playerid, "VMuteTime", 0);
					}
				}
			}
		}
	}
}
stock GetSkinOfPlayer(playerid)
{
	if !IsPlayerOnline(playerid) *then 
		return 1;

	new skin, org = PI[playerid][pMember];
	if(!org) skin = PI[playerid][pSkin];
	else
	{
	    skin = PI[playerid][pOrgSkin];
	}
	return skin;
}

stock PlayerToPoint(Float:Radius, playerid, Float:X, Float:Y, Float:Z)
{
    if (!IsPlayerOnline(playerid)) return 0;

    new Float:OldX, Float:OldY, Float:OldZ;
    GetPlayerPos(playerid, OldX, OldY, OldZ);

    new Float:dx = OldX - X;
    new Float:dy = OldY - Y;
    new Float:dz = OldZ - Z;

    new Float:distance = floatsqroot(dx * dx + dy * dy + dz * dz);

    return (distance <= Radius);
}

public OnPlayerEnterCheckpoint(playerid) 
{
	if !IsPlayerOnline(playerid) *then 
		return 1;

    if(PlayerToPoint(5.0, playerid, pTemp[playerid][pMarkerX], pTemp[playerid][pMarkerY], pTemp[playerid][pMarkerZ])) 
	{
	    pTemp[playerid][pMarkerX] =
		pTemp[playerid][pMarkerY] = 
		pTemp[playerid][pMarkerZ] = 0.0;

		DisablePlayerCheckpoint(playerid);
     	return SCM(playerid, COLOR_GREEN, !"Вы достигли точки назначения");
	}
	return 1;
}
stock SetPlayerInteriorEx(playerid, int = 0)
{
	new old = GetPlayerInterior(playerid);

	if int != 0 *then cef_emit_event(playerid, "execute.event:radar-int", CEFINT(true));
	else if old != 0 *then cef_emit_event(playerid, "execute.event:radar-int", CEFINT(false));

	SetPlayerInterior(playerid, int);
}
stock GetPlayerFPS(playerid)
{
    new drunkLevel = GetPlayerDrunkLevel(playerid);

    if (drunkLevel < 100)
    {
        SetPlayerDrunkLevel(playerid, 2000);
        return 0;
    }

    else 
    {
		if(pTemp[playerid][pLastDrunkLevel] != drunkLevel)
		{
			pTemp[playerid][pCurrentFPS] = (pTemp[playerid][pLastDrunkLevel] - drunkLevel);
        	pTemp[playerid][pLastDrunkLevel] = drunkLevel;
        	return pTemp[playerid][pCurrentFPS] - 1;
		}
    }
	
    return 0;
}
stock GetPlayerFPS2(playerid)
{
	SetPVarInt(playerid, "DrunkL", GetPlayerDrunkLevel(playerid));
	if(GetPVarInt(playerid, "DrunkL") < 100) SetPlayerDrunkLevel(playerid, 2000);
	else
	{
		if(GetPVarInt(playerid, "LDrunkL") != GetPVarInt(playerid, "DrunkL"))
		{
			SetPVarInt(playerid, "FPS", (GetPVarInt(playerid, "LDrunkL") - GetPVarInt(playerid, "DrunkL")));
			SetPVarInt(playerid, "LDrunkL", GetPVarInt(playerid, "DrunkL"));
			return GetPVarInt(playerid, "FPS") - 1;
		}
	}
	return 0;
}
stock SetPlayerPosEx(playerid, Float:x, Float:y, Float:z)
{
	return SetPlayerPos(playerid, x, y, z);
}

stock IsPlayerInAir(playerid)
{
	new Float:X, Float:Y, Float:Z, Float:CZ;
	GetPlayerPos(playerid, X, Y, Z);
	MapAndreas_FindZ_For2DCoord(X, Y, CZ);
	if(Z-1.2 > CZ) return 1;
	return 0;
}

stock SetPlayerPosAirX(playerid, Float:X, Float:Y)
{
    new Float:Z;
	MapAndreas_FindZ_For2DCoord(X, Y, Z);
	return UpdatePlayerPos(playerid, X, Y, Z + 1);
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if PI[playerid][pAdmin] *then
 	{
 	    SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 0);
  		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	   		SetVehiclePos(GetPlayerVehicleID(playerid), fX, fY, fZ+2.0);

    	else SetPlayerPosAirX(playerid, fX, fY);
    }
    return 1;
}

stock IsAVelik(vehID) 
{
	new model = GetVehicleModel(vehID);
	if(model == 481 || model == 510 || model == 509 || model == 484 || model == 454) return 1;
	return 0;
}

stock IsAPlane(vehID) 
{
	new model = GetVehicleModel(vehID);
	if(model == 417 || model == 425 || model == 447 || model == 460 || model == 469 || model == 476 || model == 487 || model == 488 || model == 497 || model == 511 || model == 512 || model == 513 || 
		model == 519 || model == 520 || model == 548 || model == 553 || model == 563 || model == 577 || model == 592 || model == 593 || model == 441 || model == 464 || model == 465 || model == 501 || model == 564) return 1;
	return 0;
}

stock GetVehicleID(vehID)
{
	if(VehicleInfo[vehID][vID] != -1 && IsValidVehicle(vehID)) return VehicleInfo[vehID][vID];
	return -1;
}
stock IsAOwnableCar(carid)
{
	if !(VehicleInfo[carid][vID] == -1) *then return 1;
	return 0;
}

stock SetEngineStatus(vehID, status, playerid)
{
	GetVehicleParamsEx(vehID, Engine, Lights, Alarm, Doors, Bonnet, Boot, Objective);
    SetVehicleParamsEx(vehID, status, Lights, Alarm, Doors, Bonnet, Boot, Objective);
    VehicleInfo[vehID][vEngine] = status;

	if playerid != INVALID_PLAYER_ID *then SCM(playerid, -1, !"Двигатель чик чирик бам бах готово");
}

stock CreatePunishment(playerid, adminID, Type, Time, Reason[])
{
	global_str[0] = EOS;

	f(global_str, 200, "INSERT INTO `punishment` ( `NickName`, `Admin`, `Type`, `Time`, `Reason`, `Date`) VALUES ( '%s', '%s', '%d', '%d', '%s', NOW())",\
		PN(playerid), PN(adminID), Type, Time, Reason);

	new Cache:result = mysql_query(mysql, global_str, true);

    if (!result)
    {
        printf("[MySQL Error] Не удалось вставить наказание для %s", PN(playerid));
        return 0;
    }
	else printf("[MySQL] Вставил наказание для %s | ID -> %d", PN(playerid), cache_insert_id(mysql));

	new insertID = cache_insert_id(mysql);

    cache_delete(result);

    return insertID;
}

stock RemoveActivePunishment(playerid, Type)
{
	global_str[0] = EOS;

	f(global_str, 200, "SELECT `ID` FROM `punishment` WHERE `NickName` = '%s' AND `Type` = '%d' AND `Status` = '1' LIMIT 1",\
		PN(playerid), Type);

	new Cache:result = mysql_query(mysql, global_str, true);

	new id;

	if (cache_get_row_count(mysql))
	{
		id = cache_get_row_int(0, 0);

		SQL("UPDATE `punishment` SET `Status` = '0' WHERE `ID` = '%d' LIMIT 1", id);
		printf("[MySQL] Сделал наказание ID: %d, неактивным", id);
	}
	else
	{
		print("[MySQL Error] Наказание не найдено.");
	}
	cache_delete(result);

	return id;
}

public OnPlayerLeaveDynamicArea(playerid, areaid) 
{ 
    if(areaid == JailZone) 
	{
		if PI[playerid][pDemorgan] > 0 *then
		{
			SaveAccount(playerid);

			SCM(playerid, COLOR_BLACK, !"Вы были кикнуты по подозрению в читерстве (#001)"),
       		return PrepareKickCamera(playerid);
		}
	}
    return 1; 
}