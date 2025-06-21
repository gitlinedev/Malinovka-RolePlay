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
    f(global_str, 150, "SELECT `NickName`, `UUID`, `HWID`, `Path` FROM client WHERE `NickName` = '%s' LIMIT 1;", PlayerName[playerid]);
    mysql_tquery(mysql, global_str, "GetPlayerSessionData", "d", playerid);
    return 1;
}

public: GetPlayerSessionData(playerid)
{	
	if( cache_get_row_count(mysql) > 0 ) 

    	SCM(playerid, COLOR_BLACKBLUE, !"Добро пожаловать в Малиновку!"),
	    SCM(playerid, COLOR_LIGHTYELLOW, !"Загружаем данные сессии. Пожалуйста, подождите..."),
        printf("*[Sessions]* Player %s has gained access", PlayerName[playerid]),
		cache_get_row(0, 1, PI[playerid][pUUID], mysql, 70),
        cache_get_row(0, 2, PI[playerid][pHWID], mysql, 35),
        cache_get_row(0, 3, PI[playerid][pPath], mysql, 150);
	else {
        printf("*[Sessions]* Player %s did not receive access", PlayerName[playerid]),
        global_str = "{FFFFFF}Не удалось получить данные сессии (#11). Попробуйте зайти позже.\n\
                    Если проблема повторяется, обратитесь к игровым мастерам.\n\n\
                    Выберите {FFFFFF}'{3377cc}Закрыть{FFFFFF}', чтобы выйти из игры.";

        SPD(playerid, 0, DIALOG_STYLE_MSGBOX, !"{ff5511}Критическая ошибка", global_str, !"Лаунчер", !"Закрыть");
        
        return Kick(playerid);
    }
	
    //SCMF(playerid, -1, "Path -> %s", PI[playerid][pPath]);
    //SCMF(playerid, -1, "HWID -> %s", PI[playerid][pHWID]);
    //SCMF(playerid, -1, "UUID -> %s", PI[playerid][pUUID]);
	
	return true;
}