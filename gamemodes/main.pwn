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

//======================================[ modules ]================================================//

#include modules/remove_build.pwn // удаление зданий
#include modules/data.pwn // массивы и цвета

//=====================================[ global server settings ]==================================//

#define Mode_Names 					   "Malinovka"
#define Mode_Text                      "Malinovka | Игра про Россию"

#define Mode_Site 		               "server-site.com"
#define Mode_Forum 					   "forum.server-site.com"

// MySQL
#define DB_HOST						   "localhost"
#define DB_USER						   "root"
#define DB_TABLE					   "malinovka"
#define DB_PASSWORD					   ""
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

	printf("ilya.amx was database connect_id [%d]", logs_skill_high = CallRemoteFunction("@CONNECTION_LOG_BASE", "d", Global_Time));

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
	GetPlayerName(playerid, PlayerName[playerid], MAX_PLAYER_NAME);

	if !IsValidNickName(PlayerName[playerid]) *then
		return Kick(playerid);

	GetPlayerIp(playerid, PlayerIp[playerid], 16);
	SetPlayerVirtualWorld(playerid, 1228);
	SetPlayerWeather(playerid, WeatherServer);
	ClearChatForPlayer(playerid);
	ClearPlayerData(playerid);

	f(global_str, 150, "SELECT `ID`, `Mail` FROM accounts WHERE NickName = '%s' LIMIT 1;", PlayerName[playerid]);
    mysql_tquery(mysql, global_str, "GetPlayerDataMysql", "d", playerid);

	RemoveBuildings(playerid);

	return 1;
}

stock ShowLoginDialog(playerid)
	return SPDF(playerid, 2, DIALOG_STYLE_PASSWORD, !"Авторизация", !"Принять", !"Контекст", "{FFFFFF}Добро пожаловать\n\nВведите свой пароль\n{FFFFFF}Попыток для ввода пароля: {28910B}%d", gPlayerLogTries{playerid});

public: GetPlayerDataMysql(playerid)
{	
	if( cache_get_row_count(mysql) > 0 ) 
		PI[playerid][pID] = cache_get_row_int(0, 0, mysql),
		cache_get_row(0, 1, PlayerMail[playerid], mysql, 50);
		
	else PI[playerid][pID] = -1;
	
	if(PI[playerid][pID] != -1)
	{
		ShowLoginDialog(playerid);
    }
	else
	{
		RegisterState[playerid] = 1;
	   	ShowRegisterDialog(playerid, RegisterState[playerid]);
	}
	
	TogglePlayerSpectating(playerid, true);
	InterpolateCameraPos(playerid, 2172.266601, -1044.046997, 73.755760, 2172.266601, -1044.046997, 73.755760, 10000000);
	InterpolateCameraLookAt(playerid, 2168.682861, -1047.527832, 73.553215, 2168.682861, -1047.527832, 73.553215, 1000);
	
	f(global_str, 150, "SELECT * FROM `banip` WHERE `IP` = '%s' LIMIT 1", PlayerIp[playerid]);
    mysql_tquery(mysql, global_str, "MysqlCheckPlayerBanIP", "d", playerid);
	
	return true;
}
stock Autorisation(playerid)
{
    SetPlayerVirtualWorld(playerid, 567);
	if(PI[playerid][pID] != -1) ShowLoginDialog(playerid);
	else
	{
	    RegisterState[playerid] = 1;
	   	ShowRegisterDialog(playerid, RegisterState[playerid]);
	}
	return 1;
}
stock ShowGrandRegiserDialog(playerid)
{
	f(global_str, 400, "{FFFFFF}Добро пожаловать, %s\n\nАккаунт не зарегистрирован.\nВведите пароль для регистрации.\nОн потребуется для входа на сервер.\n\n{FF0000}\tПримечания:\n\t- 6–30 символов\n\t- Только буквы и цифры\n\t- Учитывается регистр", PN(playerid));
	return SPD(playerid, 1, DIALOG_STYLE_INPUT, "Регистрация", global_str, !"Принять", !"Выход");
}
stock ShowRegisterDialog(playerid, rstate)
{
	switch rstate do  {
	    case 1: ShowGrandRegiserDialog(playerid);
	    case 2: SPD(playerid, 1, DIALOG_STYLE_LIST, !"Регистрация", "Мужчина\nЖенщина", !"Принять", !"Выход");
	    case 3: SPD(playerid, 1, DIALOG_STYLE_INPUT, !"Регистрация", "{FFFFFF}Введите ник игрока пригласившего вас.\nПример: Ivan_Ivanov\n", !"Принять", !"Выход");
        default: return 0; 
	}
	return 1;
}
public: MysqlCheckPlayerBanIP(playerid)
{
	if(cache_get_row_count(mysql) > 0)
	{
	    SCM(playerid, COLOR_RED, !"Вы заблокированы на сервере!");
		Kick(playerid);
		return 1;
	}
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
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	return 0;
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

public OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
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

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
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

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

stock CheckPassword(pass[])
{
	for(new i; i < strlen(pass); i ++)
	{
	    if( (pass[i] >= 'a' && pass[i] <= 'z') ||
		(pass[i] >= 'A' && pass[i] <= 'Z') ||
		(pass[i] >= '0' && pass[i] <= '9')  ) continue;
		else return 0;
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
						ShowRegisterDialog(playerid,RegisterState[playerid]);
					}
					case 2:
					{
					    RegisterState[playerid] = 3;
				        ShowRegisterDialog(playerid,RegisterState[playerid]);
				        RegSex[playerid] = listitem+1;
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
				else SPD(playerid, 2, DIALOG_STYLE_MSGBOX, !"{FFFFFF}Прекращение | {ae433d}Регистрация", !"{FFFFFF}Вы действительно желайте прервать регистрацию?", !"Да", !"Нет");

			}
			return 1;
		}
	}
	return 1;
}

stock SetString(param_1[], param_2[], size = 300)
{
	return strmid(param_1, param_2, 0, strlen(param_2), size);
}

public: OnPlayerRegister(playerid, const password[])
{
	if cache_get_row_count() *then
	{
		SCM(playerid, -1, !"Регистрация аккаунта прервана. Выберите другой никнейм");

		return Kick(playerid);
	}

	new y, m, d;

	getdate(y, m, d);
	
	f(mysql_string, 12, "%d-%d-%d", y, m, d);

	f(global_str, 1024, "INSERT INTO `accounts` (`NickName`,`Password`,`RegIP`,`Score`,`Sex`,`Referal`,`Mail`,`Money`, \
	`Bank`,`Donate`,`DataReg`) VALUE ('%s', '%s', '%s', '1', '%i', '%s', \
	'No Mail Adress', '1000', '0', '0', '%s')",\
	PN(playerid), MD5_Hash(password), PlayerIP(playerid), RegSex[playerid], RegReferal[playerid], mysql_string);
	
	mysql_tquery(mysql, global_str, "OnPlayerRegisterMysql", "d", playerid);
	
	return true;
}

stock PlayerIP(playerid)
{
	return PlayerIp[playerid];
}

public: OnPlayerRegisterMysql(playerid)
{
    PI[playerid][pID] = cache_insert_id(mysql);
	
	RegisterState[playerid] = 0;
    ClearChatForPlayer(playerid);

	SCM(playerid, COLOR_LIGHTYELLOW, !"Добро пожаловать на Малиновку!");
	SCM(playerid, COLOR_LIGHTYELLOW, !"Загружаем данные сессии. Пожалуйства подождите...");
	SCM(playerid, COLOR_LIGHTYELLOW, "Меню помощи - /help, стандартное управление голосовым чатом: X (англ) - говорить");

	UpdatePlayerHealth(playerid, 100);

	return OnPlayerLogin(playerid);
}

stock OnPlayerLogin(playerid)
{
    if IsPlayerLogged{playerid} || PI[playerid][pID] == -1 *then	
		return Kick(playerid);
   	
	//f(global_str, 150, "SELECT * FROM `Bans` WHERE BINARY `Name` = '%s' LIMIT 1", PN(playerid));
	//mysql_tquery(mysql, global_str, "MysqlCheckBanOnLogin", "ds", playerid, PN(playerid));

	f(global_str, 100, "SELECT * FROM `accounts` WHERE `ID` = '%i' LIMIT 1", PI[playerid][pID]);
	mysql_tquery(mysql, global_str, "OnPlayerLoadData", "d", playerid);
	
    return true;
}

stock CheckPlayerLogged(playerid, Name[])
{
	foreach(Player, i)
	{
		if playerid == i *then 
			continue; 

		if !strcmp(PlayerName[i], Name, true) *then
		{
			if IsPlayerLogged{i} *then
			{	
				return false;
			}

			return true;
		}
	}

	return 2;
}

public: OnPlayerLoadData(playerid)
{
	if !CheckPlayerLogged(playerid, PlayerName[playerid]) *then
	{
		SCM(playerid, -1, "Внутриигровая ошибка. Вы отключены от сервера ( Данный аккаунт уже авторизован ).");
		return Kick(playerid);
	}
	else if !cache_get_row_count() *then
		return Kick(playerid);

	cache_get_row(0, 1, PlayerName[playerid], mysql, MAX_PLAYER_NAME);

    PI[playerid][pID] = cache_get_row_int(0, 0, mysql);
	
    cache_get_row(0, 3, PlayerRegIP[playerid], mysql, 16);
    cache_get_row(0, 4, PlayerIp[playerid], mysql, 16);
    cache_get_row(0, 5, PlayerReferal[playerid], mysql, MAX_PLAYER_NAME);
    cache_get_row(0, 6, PlayerMail[playerid], mysql, 50);

    PI[playerid][pAdmin] = cache_get_row_int(0, 7, mysql);
    PI[playerid][pMoney] = cache_get_row_int(0, 8, mysql);
    PI[playerid][pScore] = cache_get_row_int(0, 9, mysql);
    PI[playerid][pExp] = cache_get_row_int(0, 10, mysql);
	PI[playerid][pHealth] = cache_get_row_int(0, 109, mysql);
	cache_get_row(0, 154, PI[playerid][pLastIP], mysql, 16);
	//---------
	GetPlayerIp(playerid, PI[playerid][pLastIP], 16);
	PreloadAllAnimLibs(playerid);
	return PlayerSpawn(playerid);
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
	SpawnPlayer(playerid);
	return 1;
}

stock SettingSpawn(playerid)
{
	if IsPlayerNPC(playerid) *then return 1;
	new skin;

	SetSpawnInfoEx(playerid, skin, 167.5974,-109.2371,1.5501,272.6516);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
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
	return ApplyAnimation(playerid,animlib,"null",0.0,0,0,0,0,0);