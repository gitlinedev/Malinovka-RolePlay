stock GetPlayerHWID()
{
    if (PI[playerid][pHWID][0] == EOS) {
        f(PI[playerid][pHWID], 35, "HWID_%d", playerid);
    }
    return PI[playerid][pHWID];
}
stock GetPlayerUUID()
{
    if (PI[playerid][pUUID][0] == EOS) {
        f(PI[playerid][pUUID], 70, "UUID_%d", playerid);
    }
    return PI[playerid][pUUID];
}

stock LoadSession(playerid)
{
    f(global_str, 150, "SELECT `NickName`, `UUID`, `HWID`, `Path` FROM client WHERE `NickName` = '%s' AND `Used` = '0' LIMIT 1;", PlayerName[playerid]);
    mysql_tquery(mysql, global_str, "GetPlayerSessionData", "d", playerid);
    return 1;
}

public: GetPlayerSessionData(playerid)
{	

    global_str[0] = EOS;

	if( cache_get_row_count(mysql) > 0 ) {
        printf("*[Sessions]* Player %s has gained access", PlayerName[playerid]);

		cache_get_row(0, 1, PI[playerid][pUUID], mysql, 70);
        cache_get_row(0, 2, PI[playerid][pHWID], mysql, 35);
        cache_get_row(0, 3, PI[playerid][pPath], mysql, 150);

        f(global_str, 120, "UPDATE `client` SET `Used` = '1' WHERE `NickName` = '%s'", PN(playerid));
		mysql_tquery(mysql, global_str);

        f(global_str, 150, "SELECT * FROM `banpc` WHERE `HWID` = '%s' OR `UUID` = '%s' LIMIT 1", PI[playerid][pHWID], PI[playerid][pUUID]);
        mysql_tquery(mysql, global_str, "MysqlCheckPlayerBanPC", "d", playerid);
    }
	else {
        printf("*[Sessions]* Player %s did not receive access", PlayerName[playerid]),
        global_str = "{FFFFFF}Не удалось получить данные сессии (#11). Попробуйте зайти позже.\n\
                    Если проблема повторяется, обратитесь к игровым мастерам.\n\n\
                    Выберите {FFFFFF}'{3377cc}Лаунчер{FFFFFF}', чтобы закрыть игру и перейти в лаунчер\n\
                    Выберите {FFFFFF}'{3377cc}Закрыть{FFFFFF}', чтобы выйти из игры.";

        SPD(playerid, 0, DIALOG_STYLE_MSGBOX, !"{ff5511}Критическая ошибка", global_str, !"Лаунчер", !"Закрыть");
        
        PrepareKickCamera(playerid, 3000);
    }
	
	return true;
}

stock GenerateBanCode(size)
{
    static bigletters[26][] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"},
        numbers[10][] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"},
        code[7];
	code[0] = EOS;
    if(size > sizeof(code)) size = sizeof(code);
    for(new i = 0; i < size; i ++) {
        switch(random(2)) {
            case 0: strcat(code, bigletters[random(sizeof(bigletters))]);
            case 1: strcat(code, numbers[random(sizeof(numbers))]);
        }
    }
    return code;
}

public: MysqlCheckPlayerBanPC(playerid)
{
	if(cache_get_row_count(mysql) > 0)
	{
        sql_get_row(0, {2, 5});

	    printf("*[Sessions]* Player %s has pc banned", PlayerName[playerid]),
        f(global_str, 512, "{FFFFFF}Вы заблокированы и больше не можете играть на серверах Малиновки.\n\n\
                    {FFFFFF}ID аккаунта:{19993c}\t\t%d\n\
                    {FFFFFF}ID блокировки:{19993c}\t%s\n\
                    {FFFFFF}Дата и время:{19993c}\t\t%s\n\n\
                    {396cac}Если Вы уверены, что блокировка ошибочная - обратитесь в техническую\n\
                    {396cac}поддержку, прикрепив к своему обращению скриншот данного диалога (F8).", PI[playerid][pID], SQL_GET_ROW_STR[0], SQL_GET_ROW_STR[1]);

        SPD(playerid, 0, DIALOG_STYLE_MSGBOX, !"{EE3366}Упс", global_str, !"Ок", !"");

        SCM(playerid, COLOR_GREY, !"Введите /q, чтобы выйти из игры");

		PrepareKickCamera(playerid, 3000);
		return 1;
	}
    else 
    {
        printf("*[Sessions]* Player %s did not pc banned", PlayerName[playerid]);

        if(PI[playerid][pID] != -1)
        {
            foreach(Admin, i) {
                if(PI[i][pAdmin] && ALogin{i} && !AInfo[i][admInfoNewPlayer]) 
                    SCMF(i, COLOR_LIGHTGREY, "[Откладка]: Игрок %s[%d] успешно зашел на сервер. IP-адрес: %s", PlayerName[playerid], playerid, AInfo[i][admIP] ? "Скрыто" : PlayerIp[playerid]);      
            }

            ShowLoginDialog(playerid);
        }
        else
        {
            RegisterState[playerid] = 1;
            ShowRegisterDialog(playerid, RegisterState[playerid]);
        }
    }
	return 1;
}

