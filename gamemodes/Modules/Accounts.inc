public: OnPlayerLoadData(playerid)
{
	if !CheckPlayerLogged(playerid, PlayerName[playerid]) *then
	{
		SCM(playerid, -1, "Внутриигровая ошибка. Вы отключены от сервера ( Данный аккаунт уже авторизован ).");
		return PrepareKickCamera(playerid);
	}
	else if !cache_get_row_count() *then
		return PrepareKickCamera(playerid);

	cache_get_row(0, 1, PlayerName[playerid], mysql, MAX_PLAYER_NAME);

    PI[playerid][pID] = cache_get_row_int(0, 0, mysql);
	
    cache_get_row(0, 4, PlayerRegIP[playerid], mysql, 16);
    cache_get_row(0, 4, PlayerIp[playerid], mysql, 16);
	cache_get_row(0, 4, PI[playerid][pLastIP], mysql, 16);
    cache_get_row(0, 9, PlayerReferal[playerid], mysql, MAX_PLAYER_NAME);
    cache_get_row(0, 10, PlayerMail[playerid], mysql, 50);

    PI[playerid][pAdmin] = cache_get_row_int(0, 2, mysql);
    PI[playerid][pMoney] = cache_get_row_int(0, 11, mysql);
    PI[playerid][pLevel] = cache_get_row_int(0, 6, mysql);
    PI[playerid][pExp] = cache_get_row_int(0, 7, mysql);
	PI[playerid][pSex] = cache_get_row_int(0, 8, mysql);
	PI[playerid][pHealth] = cache_get_row_int(0, 15, mysql);
	PI[playerid][pArmour] = cache_get_row_int(0, 16, mysql);
	PI[playerid][pMute] = cache_get_row_int(0, 17, mysql);
	PI[playerid][pMuteTime] = cache_get_row_int(0, 18, mysql);
	PI[playerid][pWarns] = cache_get_row_int(0, 19, mysql);
	PI[playerid][pWarnsTime] = cache_get_row_int(0, 20, mysql);
	PI[playerid][pJail] = cache_get_row_int(0, 21, mysql);
	PI[playerid][pJailTime] = cache_get_row_int(0, 22, mysql);
	PI[playerid][pHospital] = cache_get_row_int(0, 23, mysql);
	PI[playerid][pSkin] = cache_get_row_int(0, 24, mysql);
	PI[playerid][pWanted] = cache_get_row_int(0, 25, mysql);
	PI[playerid][pAdminNumber] = cache_get_row_int(0, 26, mysql);
	//new
	PI[playerid][pLeader] = cache_get_row_int(0, 27, mysql);
	PI[playerid][pMember] = cache_get_row_int(0, 28, mysql);
	PI[playerid][pOrgSkin] = cache_get_row_int(0, 29, mysql);
	PI[playerid][pRang] = cache_get_row_int(0, 30, mysql);
	PI[playerid][pSpawnSetting] = cache_get_row_int(0, 31, mysql);
	PI[playerid][pDemorgan] = cache_get_row_int(0, 32, mysql);
	//PI[playerid][pDemorganTime] = cache_get_row_int(0, 33, mysql);
	PI[playerid][pShowFPS] = cache_get_row_int(0, 34, mysql);
	PI[playerid][pShowNameTags] = cache_get_row_int(0, 39, mysql);
	PI[playerid][pCinemaMode] = cache_get_row_int(0, 40, mysql);
	PI[playerid][pVoiceChat] = cache_get_row_int(0, 41, mysql);
	PI[playerid][pShowRain] = cache_get_row_int(0, 42, mysql);
	PI[playerid][pDamageMP3] = cache_get_row_int(0, 43, mysql);
	PI[playerid][pVMute] = cache_get_row_int(0, 44, mysql);
	PI[playerid][pVMuteTime] = cache_get_row_int(0, 45, mysql);

	SetPlayerTeam(playerid, 4);

	if PI[playerid][pDemorgan] >= 1 *then
		cef_emit_event(playerid, "show-notifications:hud", CEFINT(101), CEFSTR("red-time"), CEFSTR("Заключение"), CEFINT(PI[playerid][pDemorgan]));

	if PI[playerid][pWanted] >= 1 *then 
		cef_emit_event(playerid, "execute.event:search", CEFINT(PI[playerid][pWanted]), CEFSTR("none"));

	if (WeatherServer >= 7 && WeatherServer <= 9)
	{
		if (PI[playerid][pShowRain] == 1)
		{
			SCM(playerid, COLOR_GREEN, !"[Подсказка] Вы можете отключить дождь в /mn > Настройки аккаунта, если он снижает производительность и FPS");
			SetPlayerWeather(playerid, WeatherServer);
		}
		else
		{
			SetPlayerWeather(playerid, 18);
		}
	}
	else
	{
		SetPlayerWeather(playerid, WeatherServer);
	}

	IsPlayerLogged{playerid} = true;

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	ShowInterface(playerid, true);

	foreach(new i: Player) ShowPlayerNameTagForPlayer(playerid, i, PI[playerid][pShowNameTags]);
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	f(global_str, 150, "UPDATE `accounts` SET `OldIP` = '%s',`OnlineStatus`='1',`LastLogin` = NOW(), `PlayerID` = '%d' WHERE `ID` = '%i'", PlayerIp[playerid], playerid, PI[playerid][pID]);
    mysql_tquery(mysql, global_str);

	SetPlayerScore(playerid, PI[playerid][pLevel]);
	GivePlayerMoney(playerid, PI[playerid][pMoney]);

	if(GetTeamID(playerid) != 0) SetPlayerColor(playerid, TeamColors[GetTeamID(playerid)][ColorInt]);
	else SetPlayerColor(playerid, 0xFFFFFFFF);

	//---------
	GetPlayerIp(playerid, PI[playerid][pLastIP], 16);
	PreloadAllAnimLibs(playerid);
	return PlayerSpawn(playerid);
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
stock OnPlayerLogin(playerid, Reg = 0)
{
    if IsPlayerLogged{playerid} || PI[playerid][pID] == -1 *then	
		return PrepareKickCamera(playerid);

	SCM(playerid, COLOR_LIGHTYELLOW, !"Меню помощи - /help, стандартное управление голосовым чатом: X (англ) - говорить, O (англ) - настройки");

	if(Reg == 1)
	{
		SCM(playerid, 0xCC6666FF, !"Для комфортной игры используйте команды {ffff99}/help /menu /gps");
		SCM(playerid, 0xCC6666FF, !"Ваш дальнейший путь ограничен только Вашей фантазией и мотивацией");
		SCM(playerid, 0xCC6666FF, !"Предлагаем небольшую подсказку возможных действий для быстрого развития:");
		SCM(playerid, 0xCC6666FF, !"Для начала рекомендуем Вам отправиться на одну из временных работ {ffff99}(/gps 2 1-4)");
		SCM(playerid, 0xCC6666FF, !"Для водительских прав и трудоустройства на работу требуется медицинская справка из БЦРБ {ffff99}(/gps 4 1)");
		SCM(playerid, 0xCC6666FF, !"Заработав немного денег, Вы сможете сдать на права в автошколе {ffff99}(/gps 1 10)");
		SCM(playerid, 0xCC6666FF, !"На сервере можно арендовать транспорт за небольшую сумму на срок до трёх дней {ffff99}(/gps 1 10)");
		SCM(playerid, 0xCC6666FF, !"Перейдя на 2 уровень не забудьте посетить любую мэрию {ffff99}(/gps 3 1-3){cc6666}, там можно устроиться на работу");
		SCM(playerid, 0xCC6666FF, !"Желаем приятной игры. При возникновении вопросов смело задавайте их игровым мастерам {ffff99}(/report или /menu > 6)");
	}

	f(global_str, 150, "SELECT * FROM `bans` WHERE BINARY `Name` = '%s' LIMIT 1", PN(playerid));
	mysql_tquery(mysql, global_str, "MysqlCheckBanOnLogin", "ds", playerid, PN(playerid));
	
    return true;
}
public: MysqlCheckBanOnLogin(playerid, namez[])
{
    new seconds;

    if cache_get_row_count(mysql) > 0 *then
    {
		sql_get_row(0, {0, 1, 2, 4, 6});
		
		seconds = cache_get_row_int(0, 3, mysql);
		
		if Global_Time < seconds *then
		{
			global_str = "{FFFFFF}Никнейм: {396cac}\t\t%s\n\
			{FFFFFF}ID аккаунта: {396cac}\t\t%s\n\
			{FFFFFF}Номер наказания:\t{19993c}%s\n\
			{FFFFFF}Сервер:\t\tСервер #1\n\
			{FFFFFF}Дата:\t\t\t%s\n\
			{FFFFFF}Причина: {FFFFFF}\t\t%s\n\
			{FFFFFF}Количество дней: {FFFFFF}\t%d дня/дней\n\n\
			{d6d886}Советуем сделать скриншот (клавиша F8), чтобы иметь\n\
			{d6d886}возможность обжаловать бан на forum.m-bonus.com";

			SPDF(playerid, 0, DIALOG_STYLE_MSGBOX, !"{EE3366}Блокировка аккаунта", !"Закрыть", !"", global_str, SQL_GET_ROW_STR[1], SQL_GET_ROW_STR[2], SQL_GET_ROW_STR[0], SQL_GET_ROW_STR[4], SQL_GET_ROW_STR[3], UNIX_TO_DAY(seconds));
			
			return PrepareKickCamera(playerid);
		}
		else
			SQL("UPDATE `accounts` SET `Warns` = '0' WHERE `ID` = '%d' LIMIT 1", PI[playerid][pID]),
		    SQL("DELETE FROM `bans` WHERE `Name` = '%s' LIMIT 1", PN(playerid));
    }
//	global_str = "{FFFFFF}Выберите место повяления:\n\
//				Место выхода из игры\n\
//				Автовокзал\n\
//				Дом/квартира\n\
	//			База организации";
//
	//SPDF(playerid, 18, DIALOG_STYLE_TABLIST_HEADERS, !"{ee3366}Выход", !"Войти", !"", global_str);

	f(global_str, 100, "SELECT * FROM `accounts` WHERE `ID` = '%i' LIMIT 1", PI[playerid][pID]);
	mysql_tquery(mysql, global_str, "OnPlayerLoadData", "d", playerid);
	return true;
}
public: OnPlayerRegisterMysql(playerid)
{
    PI[playerid][pID] = cache_insert_id(mysql);
	
	RegisterState[playerid] = 0;
    ClearChatForPlayer(playerid);

	UpdatePlayerHealth(playerid, 100);

	return OnPlayerLogin(playerid, 1);
}
public: OnPlayerRegister(playerid, const password[])
{
	if cache_get_row_count() *then
	{
		SCM(playerid, -1, !"Регистрация аккаунта прервана. Выберите другой никнейм");

		return PrepareKickCamera(playerid);
	}

	new y, m, d;

	getdate(y, m, d);
	
	f(mysql_string, 12, "%d-%d-%d", y, m, d);

	f(global_str, 1024, "INSERT INTO `accounts` (`NickName`,`Password`,`RegIP`,`Level`,`Sex`,`Referal`,`Mail`,`Money`, \
	`Bank`,`Donate`,`DataReg`) VALUE ('%s', '%s', '%s', '1', '%i', '%s', \
	'No Mail Adress', '1000000', '0', '0', '%s')",\
	PN(playerid), MD5_Hash(password), PlayerIP(playerid), RegSex[playerid], RegReferal[playerid], mysql_string);
	
	mysql_tquery(mysql, global_str, "OnPlayerRegisterMysql", "d", playerid);
	
	return true;
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

public: LoginDialogMysql(playerid, inputtext[])
{
	static password[50];
 	cache_get_row(0, 0, password, mysql);

	if strcmp(MD5_Hash(inputtext), password, true) == 0 *then
	{
		OnPlayerLogin(playerid);
	}
	else
	{
		gPlayerLogTries{playerid} --;
		
		if (gPlayerLogTries{playerid} <= 0)
			return SCM(playerid, -1, !"Вы исчерпали количество попыток. Вы отключены от сервера"), PrepareKickCamera(playerid);
			
	    f(global_str, 270,"\
	    {FFFFFF}Добро пожаловать на игровой сервер {EE3366}Malinovka RolePlay{FFFFFF}\nВведите свой пароль чтобы зайти на сервер:\n\n{FFFFFF}Попыток для ввода пароля: {EE3366}%d",gPlayerLogTries{playerid});
	    return SPD(playerid, dLogin, 3, !"{EE3366}Авторизация", global_str, !"Далее", !"Отмена");
	}
	return 1;
}

stock ShowLoginDialog(playerid)
	return SPDF(playerid, dLogin, DIALOG_STYLE_PASSWORD, !"{EE3366}Авторизация", !"Далее", !"Отмена", "{FFFFFF}Добро пожаловать\n\nВведите свой пароль\n{FFFFFF}Попыток для ввода пароля: {EE3366}%d", gPlayerLogTries{playerid});

public: GetPlayerDataMysql(playerid)
{	
	if( cache_get_row_count(mysql) > 0 ) 
		PI[playerid][pID] = cache_get_row_int(0, 0, mysql),
		cache_get_row(0, 1, PlayerMail[playerid], mysql, 50);
		
	else PI[playerid][pID] = -1;
	
	LoadSession(playerid);
	
	SpecPl(playerid, true);
	InterpolateCameraPos(playerid, 1864.6229, 2067.9146, 25.7431, 1864.6229, 2067.9146, 25.7431, 10000000);
	InterpolateCameraLookAt(playerid, 1821.6516, 2095.7375, 16.1631, 1821.6516, 2095.7375, 16.1631, 1000);
	
	SCM(playerid, COLOR_BLACKBLUE, !"Добро пожаловать в Малиновку!");
	SCM(playerid, COLOR_LIGHTYELLOW, !"Загружаем данные сессии. Пожалуйста, подождите...");

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
	f(global_str, 400, "{FFFFFF}Добро пожаловать на игровой серрвер {EE3366}Malinovka RolePlay{FFFFFF}\nДля начала игры необходимо зарегистрировать аккаунт.\n\nПожалуйста, придумайте пароль, который в дальнейшем\nбудет использоваться для авториации на сервере.\n\nВнимание! Не используйте простые и короткие пароли\nВведите будущий пароль в поле ниже и нажмите \"Далее\"");
	return SPD(playerid, dRegister, DIALOG_STYLE_INPUT, "{EE3366}Регистрация", global_str, !"Далее", !"Отмена");
}
stock ShowRegisterDialog(playerid, rstate)
{
	switch rstate do  {
	    case 1: ShowGrandRegiserDialog(playerid);
	    case 2: SPD(playerid, dSex, DIALOG_STYLE_MSGBOX, !"{EE3366}Пол", !"{FFFFFF}Выберите пол Вашего будущего персонажа", !"Мужской", !"Женский");
	    case 3: SPD(playerid, dRegister, DIALOG_STYLE_INPUT, !"{EE3366}Ник пригласившего игрока", !"{FFFFFF}Если Вы попали на наш сервер благодаря своему\nдругу, то напишите его игровой никнейм в поле ниже", !"Ввести", !"Пропустить");
        default: return 0; 
	}
	return 1;
}
public: MysqlCheckPlayerBanIP(playerid)
{
	if(cache_get_row_count(mysql) > 0)
	{
	    SCM(playerid, COLOR_RED, !"Вы заблокированы на сервере!");
		PrepareKickCamera(playerid);
		return 1;
	}
	return 1;
}
stock accounts_OnDialogResponse(playerid, dialogid, response, inputtextsave[])
{
	switch dialogid do
	{
		case dRegister:
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
						mysql_format(mysql, global_str, 256, "SELECT `ID` FROM `accounts` WHERE `NickName` = '%s' LIMIT 1", inputtextsave);
				        mysql_tquery(mysql, global_str, "MysqlCheckNickReferal", "ds", playerid, inputtextsave);
				    }
				    default: return 0;
				}
			}
			else
			{
				if (RegisterState[playerid] == 3)
				{
					SetString(RegReferal[playerid],"No Referal"),
					mysql_tquery(mysql, (str_f("SELECT `ID` FROM accounts WHERE NickName = BINARY('%s') LIMIT 1;", PlayerName[playerid])), "OnPlayerRegister", "ds", playerid, RegPass[playerid]);
				}
		        else if(RegisterState[playerid] > 1)
		        {
		       	 	RegisterState[playerid] --;
					ShowRegisterDialog(playerid,RegisterState[playerid]);
				}
				else SPD(playerid, 2, DIALOG_STYLE_MSGBOX, !"{EE3366}Регистрация", !"{FFFFFF}Вы действительно желайте прервать регистрацию?", !"Да", !"Нет");

			}
			return 1;
		}
		case dLogin:
		{
			if !response *then return PrepareKickCamera(playerid);
			else if !strlen(inputtextsave) *then  return ShowLoginDialog(playerid);

			f(global_str, 150, "SELECT `Password` FROM `accounts` WHERE `NickName` = '%s' LIMIT 1", PN(playerid));
			mysql_tquery(mysql, global_str, "LoginDialogMysql", "ds", playerid, inputtextsave);
			return true;
		}
		case dSex: 
		{
			if(response) RegSex[playerid] = 1;
			else if(!response) RegSex[playerid] = 2;
			RegisterState[playerid] = 3;
			ShowRegisterDialog(playerid, RegisterState[playerid]);
		}
	}
	return 1;
}
public: MysqlCheckNickReferal(playerid, inputtext[])
{
	if(!strlen(inputtext) || ( cache_get_row_count(mysql)>0 && !GetString(inputtext, PlayerName[playerid]) ) )
    {

		mysql_tquery(mysql, (str_f("SELECT `ID` FROM accounts WHERE NickName = BINARY('%s') LIMIT 1;", PlayerName[playerid])), "OnPlayerRegister", "ds", playerid, RegPass[playerid]);

		if(!strlen(inputtext)) SetString(RegReferal[playerid],"No Referal");
		else
		{
			mysql_real_escape_string(inputtext, RegReferal[playerid]);
			SCMF(playerid, COLOR_HINT, "[Информация]: {FFFFFF}Вы указали игрока {6699ff}%s{FFFFFF} в качестве пригласившего Вас игрока.", RegReferal[playerid]);
		}
   	}
   	else
   	{
		SCM(playerid, COLOR_GREY, !"Игрок не найден.");
   	    ShowRegisterDialog(playerid, RegisterState[playerid]);
   	}
   	return 1;
}

stock SaveAccount(playerid)
{
    if !IsPlayerOnline(playerid) *then return false;
	
	new ORM:orm = orm_create("accounts");
	
	// Integer
	orm_addvar_int(orm, PI[playerid][pID], "ID");
	
	orm_addvar_int(orm, PI[playerid][pLevel], "Level");
	orm_addvar_int(orm, PI[playerid][pExp], "Exp");
	orm_addvar_int(orm, PI[playerid][pSex], "Sex");
	orm_addvar_int(orm, PI[playerid][pAdmin], "Admin");
	orm_addvar_int(orm, PI[playerid][pMoney], "Money");
	orm_addvar_int(orm, PI[playerid][pBank], "Bank");
	orm_addvar_int(orm, PI[playerid][pDonate], "Donate");
	orm_addvar_int(orm, PI[playerid][pMute], "Mute");
	orm_addvar_int(orm, PI[playerid][pMuteTime], "MuteTime");
	orm_addvar_int(orm, PI[playerid][pJail], "Jail");
	orm_addvar_int(orm, PI[playerid][pJailTime], "JailTime");
	orm_addvar_int(orm, PI[playerid][pWarns], "Warns");
	orm_addvar_int(orm, PI[playerid][pWarnsTime], "WarnsTime");
	orm_addvar_int(orm, PI[playerid][pHospital], "Hospital");
	orm_addvar_int(orm, PI[playerid][pSkin], "Skin");
	orm_addvar_int(orm, PI[playerid][pWanted], "Wanted");
	orm_addvar_int(orm, PI[playerid][pAdminNumber], "AdminNumber");
	orm_addvar_int(orm, PI[playerid][pLeader], "Leader");
	orm_addvar_int(orm, PI[playerid][pMember], "Member");
	orm_addvar_int(orm, PI[playerid][pOrgSkin], "OrgSkin");
	orm_addvar_int(orm, PI[playerid][pRang], "Rang");
	orm_addvar_int(orm, PI[playerid][pSpawnSetting], "SpawnSetting");
	orm_addvar_int(orm, PI[playerid][pDemorgan], "Demorgan");
	//orm_addvar_int(orm, PI[playerid][pDemorganTime], "DemorganTime");
	orm_addvar_int(orm, PI[playerid][pVoiceChat], "VoiceChat");
	orm_addvar_int(orm, PI[playerid][pShowFPS], "ShowFPS");
	orm_addvar_int(orm, PI[playerid][pShowNameTags], "ShowNameTags");
	orm_addvar_int(orm, PI[playerid][pCinemaMode], "CinemaMode");
	orm_addvar_int(orm, PI[playerid][pDamageMP3], "DamageMP3");
	orm_addvar_int(orm, PI[playerid][pShowRain], "ShowRain");
	orm_addvar_int(orm, PI[playerid][pVMute], "VMute");
	orm_addvar_int(orm, PI[playerid][pVMuteTime], "VMuteTime");

	//Float
	orm_addvar_float(orm, PI[playerid][pHealth], "Health");
	orm_addvar_float(orm, PI[playerid][pArmour], "Armour");
	
	//String
	orm_addvar_string(orm, PlayerMail[playerid], 50, "Mail");
	orm_addvar_string(orm, PI[playerid][pLastIP], 16, "LastIP");
	
	orm_setkey(orm, "ID");
	
	orm_update(orm);
	orm_destroy(orm);

	return true;
}