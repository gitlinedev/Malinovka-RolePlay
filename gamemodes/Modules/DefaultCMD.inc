// if !IsPlayerLogged{playerid} *then return false;
// #define COLOR_PURPLE           	 	0xFF99CCFF

cmd:me(playerid, params[])
{
	if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);
	if sscanf(params,"s[100]",params[0]) *then return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /me [текст]");
	if IsAIP(params[0]) *then return 0;
	f(global_str, 300,"%s %s",PN(playerid),params[0]);
	ProxDetector(25,playerid,global_str,COLOR_PURPLE);
	SetPlayerChatBubble(playerid, params[0], COLOR_PURPLE, 10.0, 5000);
	return 1;
}
cmd:do(playerid, params[])
{
	if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);
	if sscanf(params,"s[100]",params[0]) *then return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /do [текст]");
	if IsAIP(params[0]) *then return 0;
	f(global_str, 300,"%s %s",params[0], PN(playerid));
	ProxDetector(25,playerid,global_str,COLOR_PURPLE);
	SetPlayerChatBubble(playerid, params[0], COLOR_PURPLE, 10.0, 5000);
	return 1;
}
cmd:todo(playerid, params[])
{
	if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);
	if sscanf(params,"p<*>s[128]s[128]",params[0],params[1]) *then return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /todo [Сообщение]*[Действие]");
	if IsAIP(params[0]) *then return 0;
	f(global_str, 400,"\"%s\", - сказал %s,{FF99FF} %s.",params[0], PN(playerid), params[1]);
	ProxDetector(25,playerid,global_str,COLOR_PURPLE);
	SetPlayerChatBubble(playerid, params[0], COLOR_PURPLE, 10.0, 5000);
	return 1;
}
cmd:c(playerid, params[])
{
	if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);
	if sscanf(params,"s[100]",global_str) *then return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /c [текст]");
	if IsAIP(global_str) *then return 0;
	f(global_str,150, "%s[%d] говорит шепотом: {FFFFFF}%s",PN(playerid),playerid,global_str);
	ProxDetector(2,playerid, global_str, COLOR_BLUE);
	return 1;
}
cmd:b(playerid, params[])
{
	if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);
	if sscanf(params,"s[100]",global_str) *then return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /b [OOC (nonRP) сообщение]");
	if IsAIP(global_str) *then return 0;
	f(global_str,150, "(( %s[%d]: %s ))", PN(playerid), playerid, global_str);
	ProxDetector(2,playerid, global_str, COLOR_BLUE);
	return 1;
}
cmd:s(playerid, params[])
{
    if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);
	if sscanf(params,"s[100]",global_str) *then return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /s [текст]");
    if IsAIP(global_str) *then return 0;
	SetPlayerChatBubble(playerid, params[0], -1, 25.0, 5000);
    f(global_str, 200, "%s[%d] крикнул: %s", PN(playerid), playerid, params[0]);
	ProxDetector(25, playerid, global_str, -1);
	if(!IsPlayerInAnyVehicle(playerid))	ApplyAnimationEx(playerid, "ON_LOOKERS", "shout_01",1000.0,0,0,0,0,0,1);
	return 1;
}
cmd:menu(playerid)
{
	return ShowPlayerDialog(playerid, 6, DIALOG_STYLE_LIST, !"{EE3366}Меню игрока", 
	!"{FFFFFF}1. Статистика\n\
	{FFFFFF}2. Команды сервера\n\
	{FFFFFF}3. Горячие клавиши\n\
	{FFFFFF}4. Помощь / жалоба\n\
	{FFFFFF}5. Настройки аккаунта\n\
	{FFFFFF}6. Общие правила\n\
	{FFFFFF}7. Ресурсы игры\n\
	{FFFFFF}8. Изменить никнейм\n\
	{FFFFFF}9. Чёрный список организаций\n\
	{5fc2f1}10. Дополнительные услуги", !"Выбрать", !"Отмена");
}

stock k_OnDialogResponse(playerid, dialogid, response, listitem)
{
    switch dialogid do
	{
        case 6:
        {
            if (response)
            {
                switch (listitem)
                {
                    case 0: ShowPlayerStats(playerid);
                    case 1: ShowServerCommands(playerid);
                    case 2: ShowHotKeys(playerid);
                    case 3: ShowHelpDialog(playerid);
                    case 4: ShowPlayerSettings(playerid);
                    case 5: ShowServerRules(playerid);
                    case 6: ShowServerResources(playerid);
                    case 8: ChangePlayerName(playerid);
                    case 9: ShowBlacklistDialog(playerid);
                    case 10: ShowDonate(playerid);
                }
            }
        }
    }
    return 1;
}