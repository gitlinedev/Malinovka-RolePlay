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