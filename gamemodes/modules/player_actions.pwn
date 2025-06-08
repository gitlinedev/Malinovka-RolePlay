public: OnPlayerLoadData(playerid)
{
	if !CheckPlayerLogged(playerid, PlayerName[playerid]) *then
	{
		SCM(playerid, -1, "������������� ������. �� ��������� �� ������� ( ������ ������� ��� ����������� ).");
		return Kick(playerid);
	}
	else if !cache_get_row_count() *then
		return Kick(playerid);

	cache_get_row(0, 1, PlayerName[playerid], mysql, MAX_PLAYER_NAME);

    PI[playerid][pID] = cache_get_row_int(0, 0, mysql);
	
    cache_get_row(0, 4, PlayerRegIP[playerid], mysql, 16);
    cache_get_row(0, 4, PlayerIp[playerid], mysql, 16);
    cache_get_row(0, 9, PlayerReferal[playerid], mysql, MAX_PLAYER_NAME);
    cache_get_row(0, 10, PlayerMail[playerid], mysql, 50);

    PI[playerid][pAdmin] = cache_get_row_int(0, 2, mysql);
    PI[playerid][pMoney] = cache_get_row_int(0, 11, mysql);
    PI[playerid][pScore] = cache_get_row_int(0, 6, mysql);
    PI[playerid][pExp] = cache_get_row_int(0, 7, mysql);
	PI[playerid][pHealth] = cache_get_row_int(0, 15, mysql);
	cache_get_row(0, 4, PI[playerid][pLastIP], mysql, 16);
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
		return Kick(playerid);
   	
	//f(global_str, 150, "SELECT * FROM `Bans` WHERE BINARY `Name` = '%s' LIMIT 1", PN(playerid));
	//mysql_tquery(mysql, global_str, "MysqlCheckBanOnLogin", "ds", playerid, PN(playerid));

	SCM(playerid, COLOR_BLACKBLUE, !"����� ���������� �� ���������!");
	SCM(playerid, COLOR_LIGHTYELLOW, !"��������� ������ ������. ����������� ���������...");
	SCM(playerid, COLOR_LIGHTYELLOW, !"���� ������ - /help, ����������� ���������� ��������� �����: X (����) - ��������");

	if(Reg == 1)
	{
		SCM(playerid, 0xCC6666FF, !"��� ���������� ���� ����������� ������� {ffff99}/help /menu /gps");
		SCM(playerid, 0xCC6666FF, !"��� ���������� ���� ��������� ������ ����� ��������� � ����������");
		SCM(playerid, 0xCC6666FF, !"���������� ��������� ��������� ��������� �������� ��� �������� ��������:");
		SCM(playerid, 0xCC6666FF, !"��� ������ ����������� ��� ����������� �� ���� �� ��������� ����� {ffff99}(/gps 2 1-4)");
		SCM(playerid, 0xCC6666FF, !"��� ������������ ���� � ��������������� �� ������ ��������� ����������� ������� �� ���� {ffff99}(/gps 4 1)");
		SCM(playerid, 0xCC6666FF, !"��������� ������� �����, �� ������� ����� �� ����� � ��������� {ffff99}(/gps 1 10)");
		SCM(playerid, 0xCC6666FF, !"�� ������� ����� ���������� ��������� �� ��������� ����� �� ���� �� ��� ���� {ffff99}(/gps 1 10)");
		SCM(playerid, 0xCC6666FF, !"������� �� 2 ������� �� �������� �������� ����� ����� {ffff99}(/gps 3 1-3){cc6666}, ��� ����� ���������� �� ������");
		SCM(playerid, 0xCC6666FF, !"������ �������� ����. ��� ������������� �������� ����� ��������� �� ������� �������� {ffff99}(/report ��� /menu > 6)");
	}

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
		SCM(playerid, -1, !"����������� �������� ��������. �������� ������ �������");

		return Kick(playerid);
	}

	new y, m, d;

	getdate(y, m, d);
	
	f(mysql_string, 12, "%d-%d-%d", y, m, d);

	f(global_str, 1024, "INSERT INTO `accounts` (`NickName`,`Password`,`RegIP`,`Score`,`Sex`,`Referal`,`Mail`,`Money`, \
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
			return SCM(playerid, -1, "�� ��������� ���������� �������. �� ��������� �� �������"), Kick(playerid);
			
	    f(global_str, 270,"\
	    {FFFFFF}����� ���������� �� ������� ������ {EE3366}Malinovka RolePlay{FFFFFF}\n������� ���� ������ ����� ����� �� ������:\n\n{FFFFFF}������� ��� ����� ������: {EE3366}%d",gPlayerLogTries{playerid});
	    return SPD(playerid, 2, 3, !"{EE3366}�����������", global_str, !"�����", !"������");
	}
	return 1;
}

stock ShowLoginDialog(playerid)
	return SPDF(playerid, 2, DIALOG_STYLE_PASSWORD, !"{EE3366}�����������", !"�����", !"������", "{FFFFFF}����� ����������\n\n������� ���� ������\n{FFFFFF}������� ��� ����� ������: {EE3366}%d", gPlayerLogTries{playerid});

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
	
	SpecPl(playerid, true);
	InterpolateCameraLookAt(playerid, 1819.755981, 2093.590820, 20.097853, 1819.755981, 2093.590820, 20.097853, 150000, CAMERA_MOVE);
	
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
	f(global_str, 400, "{FFFFFF}����� ���������� �� ������� ������� {EE3366}Malinovka RolePlay{FFFFFF}\n��� ������ ���� ���������� ���������������� �������.\n\n����������, ���������� ������, ������� � ����������\n����� �������������� ��� ���������� �� �������.\n\n��������! �� ����������� ������� � �������� ������\n������� ������� ������ � ���� ���� � ������� \"�����\"");
	return SPD(playerid, 1, DIALOG_STYLE_INPUT, "{EE3366}�����������", global_str, !"�����", !"������");
}
stock ShowRegisterDialog(playerid, rstate)
{
	switch rstate do  {
	    case 1: ShowGrandRegiserDialog(playerid);
	    case 2: SPD(playerid, 3, DIALOG_STYLE_MSGBOX, !"{EE3366}���", !"{FFFFFF}�������� ��� ������ �������� ���������", !"�������", !"�������");
	    case 3: SPD(playerid, 1, DIALOG_STYLE_INPUT, !"{EE3366}��� ������������� ������", !"{FFFFFF}���� �� ������ �� ��� ������ ��������� ������\n�����, �� �������� ��� ������� ������� � ���� ����", !"������", !"����������");
        default: return 0; 
	}
	return 1;
}
public: MysqlCheckPlayerBanIP(playerid)
{
	if(cache_get_row_count(mysql) > 0)
	{
	    SCM(playerid, COLOR_RED, !"�� ������������� �� �������!");
		Kick(playerid);
		return 1;
	}
	return 1;
}