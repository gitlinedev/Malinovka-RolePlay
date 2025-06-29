static const Moder_Names[4][5] = {"None","JM","M","SM"};

cmd:mhelp(playerid)
{
	if(!CheckAccess(playerid, 1)) 
        return false;

	global_str = "";

	for new i = 1; i < 9; i++ do
		strcat(global_str, (str_f("\n{FFFFFF}%d.{%s} %s", i, PI[playerid][pAdmin] >= i ? "FFFFFF":"AFAFAF", Moder_Names[i])));
    
	return SPD(playerid, dModerCMD, DIALOG_STYLE_LIST, !"{EE3366}Команды игрового модератора", global_str, !"Выбрать", !"Отмена");
}

stock GetMaxAmountMHelp(level)
{
	new count;

	for new i; i < sizeof AdminCommandList; i++ do {

		if !(AdminCommandList[i][moderLevel] == level) *then 
			continue;
	
		count ++;
	}

	return floatround(float(count) / 35, floatround_ceil);
}

stock print_ModerCommand(playerid, level, page = 0)
{
	spdList(playerid, 1, page);

	global_str = "{FFFFFF}";

	new count;

	for new i; i < sizeof AdminCommandList; i++ do {

		if !(AdminCommandList[i][moderLevel] == level) *then 
			continue;
		
		count ++;

		if 35 * page < count <= 35 * (page + 1) *then
			strcat(global_str, (str_f("%s — %s\n", AdminCommandList[i][adminCommand], AdminCommandList[i][adminCommandInfo])));
	}

	return SPD(playerid, dModerCMDList, DIALOG_STYLE_MSGBOX, (str_f("{EE3366}%s [%d/%d]", Moder_Names[level], page + 1, GetMaxAmountAHelp(level))), global_str, !"Далее", !"Назад");
}
