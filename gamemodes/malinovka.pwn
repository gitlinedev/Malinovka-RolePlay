// доработать

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
#define MAX_PLAYERS 100
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#include streamer
#include Pawn.CMD
#include a_mysql
#include sscanf2
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#define DEBUG
#include nex-ac_ru.lang
#include nex-ac
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#include foreach
#include sampvoice
#include md5
#include cef
#include fmt
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
	return Kick(playerid);

#define Kick(%0) CallTimeOutFunction("PlayKick", 1000, false, "d", %0)

stock sql_get_row(id_0, _:id_1[], array_size = sizeof(id_1)) 
{
	for new i; i < array_size; i++ do
		cache_get_row(id_0, id_1[i], SQL_GET_ROW_STR[i], mysql);
}

new PlayerDialogList[MAX_PLAYERS][64];

#define spdList(%0,%1,%2) PlayerDialogList[%0][%1] = %2
#define gpdList(%0,%1) PlayerDialogList[%0][%1]

//======================================[ limits ]================================================//
#define Max_Cars 					   2000
//======================================[ modules ]================================================//

#include Modules/dialogData // ид диалогов
#include Modules/Data // массивы и цвета
#include Modules/AntiCheat // анти-чит
#include Modules/Accounts // авторизация и регистрация
#include Modules/DefaultCMD // команды по умолчанию
#include Modules/Admin // система админов
#include Modules/SQL // работа с базой данных
#include Modules/VoiceChat // работа с базой данных
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
#define DB_USER						   "gs99002"
#define DB_TABLE					   "gs99002"
#define DB_PASSWORD					   "983Orange1MySQL152SQls399PHP"
#define DB_PORT						   3306

main()
{
	return 1;
}

public OnGameModeInit()
{
	new inittime = GetTickCount();

	Global_Time = gettime();
	MapAndreas_Init(MAP_ANDREAS_MODE_MINIMAL);

    SetTimer("CheckGrassSpeed", 500, true);

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	mysql = mysql_connect(DB_HOST, DB_USER, DB_TABLE, DB_PASSWORD, DB_PORT);

	if !mysql_errno(mysql) *then
		print("[Data Base]: Ошибок не выявлено, загрузка продолжается!");
	else
		printf("[Data Base]: Найденна ошибка '%d', повторяем подключение.", mysql_errno(mysql));

	mysql_log(LOG_ERROR | LOG_WARNING);
	mysql_set_charset("cp1251", mysql);
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
		//GetSkinOfPlayer(playerid); доработать
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
		return Kick(playerid);

	GetPlayerIp(playerid, PlayerIp[playerid], 16);
	SetPlayerVirtualWorld(playerid, 1228);
	SetPlayerWeather(playerid, WeatherServer);
	//ClearChatForPlayer(playerid);

	if SvGetVersion(playerid) == SV_NULL *then SCM(playerid, 0xEE83F0AA, !"[VoiceChat] {FFFFFF}загрузка плагина произошла {FFFF33}неуспешно (NULL)");
    else if SvHasMicro(playerid) == SV_FALSE *then SCM(playerid, 0xEE83F0AA, !"[VoiceChat] {FFFFFF}загрузка плагина произошла {FFFF33}c ошибкой (MIC)");
    else if ((lstream[playerid] = SvCreateDLStreamAtPlayer(40.0, 0xEE83F0AA, playerid, 0xff0000ff, !"")))
    {
        if (gstream) SvAttachListenerToStream(gstream, playerid);
        SvAddKey(playerid, 0x58);
    }

	f(global_str, 150, "SELECT `ID`, `Mail` FROM accounts WHERE NickName = '%s' LIMIT 1;", PlayerName[playerid]);
    mysql_tquery(mysql, global_str, "GetPlayerDataMysql", "d", playerid);

	//RemoveBuildings(playerid);

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
	if IsPlayerLogged{playerid} *then
	{
		if Iter_Contains(Admin, playerid) *then Iter_Remove(Admin, playerid);

		DPlayerData(playerid, !"vr");

		SaveAccount(playerid);
		IsPlayerLogged{playerid} = false;
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

 	if(GetString(text, "xD"))
	{
		f(global_str, 18 + MAX_PLAYER_NAME, "%s валяется от смеха", PN(playerid));
		ProxDetector(25, playerid, global_str, COLOR_PURPLE);
		return 0;
	}
	if(GetString(text, "("))
	{
		f(global_str, 36, "%s грустит", PN(playerid));
		ProxDetector(25, playerid, global_str, COLOR_PURPLE);
		return 0;
	}
	if(GetString(text, "(("))
	{
		f(global_str, 50, "%s сильно расстроился", PN(playerid));
		ProxDetector(25, playerid, global_str, COLOR_PURPLE);
		return 0;
	}
	if(GetString(text, "чВ"))
	{
		f(global_str, 48, "%s валяется от смеха", PN(playerid));
		ProxDetector(25, playerid, global_str, COLOR_PURPLE);
		return 0;
	}
	if(GetString(text, ")"))
	{
		f(global_str, 39, "%s улыбается", PN(playerid));
		ProxDetector(25, playerid, global_str, COLOR_PURPLE);
		return 0;
	}
	if(GetString(text, "))"))
	{
		f(global_str, 39, "%s смеётся", PN(playerid));
		ProxDetector(25, playerid, global_str, COLOR_PURPLE);
		return 0;
	}

	f(global_str, 300, "- %s {FF0000}(%s)[%d]", text, PN(playerid), playerid);
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
	new skin = GetSkinOfPlayer(playerid);

	if PI[playerid][pJailTime] > 0 *then // отправка в тюрягу
	{	
		SetSpawnInfoEx(playerid, skin, 100.000, 100.000, 100.000, 0.0);
						
		SetPlayerInterior(playerid, 0);
		UpdatePlayerHealth(playerid, 100);
		return 1;
	}
	else if PI[playerid][pDemorgan] > 0 *then // отправка в деморган
	{
		SetSpawnInfoEx(playerid, skin, 100.000, 100.000, 100.000, 180.0);
		UpdatePlayerHealth(playerid, 100);
		SetPlayerInterior(playerid, 6);
		SetPlayerVirtualWorld(playerid, 6);
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
			SetPlayerInterior(playerid, 2);
        }
		else
		{
			SetSpawnInfoEx(playerid, skin, 100.000, 100.000, 100.000,90.000); // дефолт болька для всех
			SetPlayerVirtualWorld(playerid, 1);
  			SetPlayerInterior(playerid, 2);
			return 1;
		}
	    UpdatePlayerHealth(playerid, 25);
	    return 1;
	}
	else if PI[playerid][pSpawnSetting] == 1 && !IsAArmy(playerid) *then // дом/квартира
	{
		return 1;
	}
	else if PI[playerid][pSpawnSetting] == 2 && !IsAArmy(playerid) *then // вокзал
	{
		if PI[playerid][pLevel] < 3 *then
		{
			switch random(2) do
			{
				case 0: SetSpawnInfoEx(playerid, skin, 100.000, 100.000, 100.000,90.000); // спавн 1 (батырево)
				case 1: SetSpawnInfoEx(playerid, skin, 100.000, 100.000, 100.000,90.000); // спавн 2 (батырево)
			}
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			return true;
		}

		else if(PI[playerid][pLevel] >= 3 && PI[playerid][pLevel] < 8)
		{
			SetSpawnInfoEx(playerid, skin, 100.000, 100.000, 100.000,90.000); // спавн 1 (бусаево)
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			return 1;
		}
		else if(PI[playerid][pLevel] >= 5 && PI[playerid][pLevel] < 20)
		{
			SetSpawnInfoEx(playerid, skin, 100.000, 100.000, 100.000,90.000); // спавн 1 (южка)
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			return 1;
		}
		return 1;
	}
	else if PI[playerid][pSpawnSetting] == 3 && GetTeamID(playerid) != 0 *then // орга
	{
		SetPlayerFacingAngle(playerid,SpawnInfo[PI[playerid][pMember]][3]);
		SetPlayerInterior(playerid,SpawnIntWorld[PI[playerid][pMember]][0]);
		SetPlayerVirtualWorld(playerid,SpawnIntWorld[PI[playerid][pMember]][1]);
		SetSpawnInfoEx(playerid, skin, SpawnInfo[PI[playerid][pMember]][0], SpawnInfo[PI[playerid][pMember]][1], SpawnInfo[PI[playerid][pMember]][2], SpawnInfo[PI[playerid][pMember]][3]);
		return 1;
	}

	// если нет спавна то спавним на дефолт респе
	SetSpawnInfoEx(playerid, skin, 1802.0438, 2505.7705, 15.8725, 304.8401); // батырево вокзал
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
stock ClearCarData(car) 
{
	CarInfo[car][cID] = INVALID_VEHICLE_ID;

	CarInfo[car][cFuel] =
	CarInfo[car][cCreate] = 0;
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

stock SendDebug(playerid, const text[], type = 0)
{
	if(type == 1)
	{
		printf("[DEBUG] %s", text), SCM(playerid, -1, text);
		return 1;
	}
	return 1;
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
				if(PI[playerid][pDemorgan] > 0)
				{
					PI[playerid][pDemorgan] --;

					if(!IsPlayerInRangeOfPoint(playerid, 50.0, 100.000, 100.000, 100.000)) PlayerSpawn(playerid); // проверка что игрок не убежал с деморгана
					
					if !PI[playerid][pDemorgan] *then
					{
						SCM(playerid, COLOR_LIGHTGREY, !"Вы отсидели свое время в ДеМоргане.");
						SetPlayerSkinEx(playerid, GetSkinOfPlayer(playerid));
					}
				}
			}
		}
	}
}
stock GetSkinOfPlayer(playerid)
{
	new skin, org = PI[playerid][pMember];
	if(!org) skin = PI[playerid][pSkin];
	else
	{
	    skin = PI[playerid][pOrgSkin];
	}
	return skin;
}