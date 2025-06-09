enum AdminInfo
{
	admID,
    admGoto,
	admGethere,
	admSpectate,
	admInfoNewPlayer,
	admKillList,
	admIP,
	Float:admPos[3],
	admMember,
	admMemberRank,
	admWorld,
	admInterior
}
new AInfo[MAX_PLAYERS][AdminInfo];
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
static const AdminPassword[8] = {5673, 4657, 1345, 9755, 7367, 2556, 8086, 6769};
static const Admin_Names[9][5] = {"None","NGM","JRGM","GM","GM+","LGM","SGM","SGM+","DEV"};
static const Moder_Names[4][5] = {"None","JM","M","SM"};

new Iterator:Admin<MAX_PLAYERS>;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
cmd:as(playerid)
{
    if(CheckAccess(playerid, 1)) return 1;

	if !ALogin{playerid} *then return 
		SPD(playerid, 4, DIALOG_STYLE_PASSWORD, !"{EE3366}Авторизация", !"{FFFFFF}Для получения доступа к правам {EE3366}игрового мастера{FFFFFF}\n необходимо подтвердить личность, введя пароль.", !"Далее", !"Отмена");
    
    SCM(playerid, -1, !"В разработке!");
    return 1;
}

stock admin_OnDialogResponse(playerid, dialogid, response, listitem, inputtextsave[])
{
    switch dialogid do
    {
        case 4: 
		{
			if !response *then
		    	return 1;

			if !strlen(inputtextsave) *then
			    	return SPD(playerid, 5, DIALOG_STYLE_PASSWORD, !"{EE3366}Авторизация", !"{FFFFFF}Для получения доступа к правам {EE3366}игрового мастера{FFFFFF}\n необходимо подтвердить личность, введя пароль.", !"Далее", !"Отмена");

			mysql_format(mysql, global_str, 150, "SELECT * FROM accounts WHERE NickName = '%s' LIMIT 1", PN(playerid));
			mysql_tquery(mysql, global_str, "AloginAuth", "id", playerid, strval(inputtextsave));
		}
        case 5:
        {
            if(!response) return pTemp[playerid][targetID] = INVALID_PLAYER_ID;
            if(response) 
			{
                PI[pTemp[playerid][targetID]][pAdmin] = listitem;

                if listitem == 0 *then
                { 
                    SCMF(playerid, COLOR_YELLOW, "Вы изменили уровень игрового мастера для %s[%d], теперь он '%s'", Admin_Names[listitem - 1], PN(pTemp[playerid][targetID]), pTemp[playerid][targetID]);
                    SCM(pTemp[playerid][targetID], COLOR_YELLOW, "Игровой мастер изменил ваш уровень до %s");
                    callcmd::as(pTemp[playerid][targetID]);
                }
                else 
                {
                    SCM(playerid, COLOR_YELLOW, !"Вы были сняты с поста игрового мастера!");
                    SCMF(pTemp[playerid][targetID], COLOR_YELLOW, "Игровой мастер %s снял Вас с должности игрового мастера", PN(playerid));
                }
                ALogin{pTemp[playerid][targetID]} = false;
                UpdatePlayerDataInt(pTemp[playerid][targetID], "Admin", PI[pTemp[playerid][targetID]][pAdmin]);

                return pTemp[playerid][targetID] = INVALID_PLAYER_ID;
            }
        }
    }
    return 1;
}
public: AloginAuth(playerid, password)
{
    if cache_get_row_count(mysql) > 0 *then
    {
        PI[playerid][pAdmin] = cache_get_row_int(0, 2);

        if password == AdminPassword[PI[playerid][pAdmin] - 1] *then
        {

            AInfo[playerid][admInterior] = -1;
            
            f(global_str, 128, "[%s #%d] %s[%d] вошел на сервер", Admin_Names[PI[playerid][pAdmin]], PI[playerid][pAdminNumber], PN(playerid), playerid);
            SendAdminsMessage(-1, global_str);

            SCMF(playerid, -1, "Вы успешно авторизовались как {EE3366}%s{FFFFFF}!", Admin_Names[PI[playerid][pAdmin]]);
        
            //for new i; i < 53; i++ do EnableAntiCheatForPlayer(playerid, i, 0); 

            Iter_Add(Admin, playerid);
            ALogin{playerid} = true;
        }
    }
    else 
    {
        SCM(playerid, -1, !"Вы ввели неверный пароль от {EE3366}админ-панели{FFFFFF}!");
        f(global_str, 128, "[%s #%d] %s[%d] ввел неверный пароль от админ-панели", Admin_Names[PI[playerid][pAdmin]], PI[playerid][pAdminNumber], PN(playerid), playerid);
        SendAdminsMessage(-1, global_str);
        return Kick(playerid);
    }
	return 1;
}
stock CheckAccess(playerid, adminLvl = 1, modLvl = 0)
{
    if (modLvl >= 1 && PI[playerid][pModer] >= modLvl) return 0;
    if (PI[playerid][pAdmin] < adminLvl) 
    {
        if !ALogin{playerid} *then return SendClientMessage(playerid, COLOR_LIGHTGREY, !"Вы не авторизованы как игровой мастер");
        return SendClientMessage(playerid, COLOR_LIGHTGREY, !"У Вас нет доступа к этой команде");
    }
    return 0;
}
CMD:makegm(playerid, params[]) 
{
    if(CheckAccess(playerid, 8)) return 1;

    if(sscanf(params,"u",params[0])) 
        return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /makegm [ID игрока]");

	if params[0] == INVALID_PLAYER_ID *then return 0;

    if params[0] == playerid *then return 0;

	if !IsPlayerLogged{params[0]} *then return SCM(playerid, COLOR_GREY, !"Игрок не авторизован");

    pTemp[playerid][targetID] = params[0];

	return SPD(playerid, 5, DIALOG_STYLE_LIST, !"{ee3366}Выдача прав игрового мастера", !"Снять права игрового мастера\n1. NGM\n2. JRGM\n3. GM\n4. GM+\n5. LGM\n6. SGM\n7. SGM+\n8. DEV", !"Далее", !"Отмена");
}

cmd:a(playerid, params[])
{
    if(CheckAccess(playerid, 8)) return 1;

    if sscanf(params, "s[150]", params[0]) *then
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /a [текст]");

    return SAMF(COLOR_BLUE, "[%s #%d] %s[%d]: %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, params[0]);
}
CMD:admins(playerid)
{
 	if(CheckAccess(playerid, 1, 1)) return 0;

	SCMF(playerid, COLOR_BLUE, "Игровые мастера онлайн (в сети: %d, из них в АФК: NaN)", Iter_Count(Admin));

	foreach(Admin, i)
	{
		if !PI[i][pAdmin] *then continue;

		f(global_str, 90, "[%s #%d] - %s[%d]", StaffTag(playerid), PI[i][pAdminNumber], PN(i), i);
		SCM(playerid, COLOR_JOBYELLOW, global_str);
	}
	return 1;
}
stock StaffTag(playerid)
{

    if PI[playerid][pAdmin] *then return Admin_Names[PI[playerid][pAdmin] - 1];
    else if PI[playerid][pModer] *then return Moder_Names[PI[playerid][pModer] - 1];
    
    return Admin_Names[0]; // "None"
}
