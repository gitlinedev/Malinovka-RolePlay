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
CMD:s(playerid, params[])
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