// targetID ////////////////////////////////// 
    /*

        ИД отправителя int pFromID

    */
//////////////////////////////////////////////
// PlayerID ////////////////////////////////// 
    /* 

        ИД кому отправили int pToID
        Значение 1 int pVal1
        Значение 2 int pVal2
        Что предложил (1/2/3) int pType

    */
//////////////////////////////////////////////

stock SendCEF(playerid, targetid, btn_1[], btn_2[], header[], ui_type[], time, val1, val2, type, host)
{
    /* Типы: no-n - будет без кнопки N | no-y - будет без кнопки Y | none - стандартное уведомление */

    cef_emit_event
    (
        targetid, 
        "show-notifications:proposal", 
        CEFINT(time), 
        CEFSTR(header), 
        CEFSTR(btn_1), 
        CEFSTR(btn_2), 
        CEFSTR(type)
    );

    if host == 1 *then
    {
        pTemp[targetid][pFromID] = playerid;
        pTemp[playerid][pToID] = targetid;
        pTemp[playerid][pVal1] = val1;
        pTemp[playerid][pVal2] = val2;
        pTemp[playerid][pType] = type;
    }

    return 1;
}

stock CancelRequest(playerid)
{
	if(pTemp[playerid][pToID] != INVALID_PLAYER_ID)
	{
        SCMF(pTemp[playerid][pToID], COLOR_GREY, "%s отменил свое предложение", PN(playerid));
        SCMF(playerid, COLOR_GREY, "Вы отменили свое предложение для игрока %s", PN(pTemp[playerid][pToID]));

        
        ClearProposition(pTemp[playerid][pToID]);
        ClearProposition(playerid);
    }
    else if(pTemp[playerid][pFromID] != INVALID_PLAYER_ID)
    {
        SCMF(pTemp[playerid][pFromID], COLOR_GREY, "%s отказался от Вашего предложения", PN(playerid));
        SCMF(playerid, COLOR_GREY, "Вы отказались от предложения игрока %s", PN(pTemp[playerid][pFromID]));

        ClearProposition(pTemp[playerid][pFromID]);
        ClearProposition(playerid);
    }
	return 1;
}

stock OnPlayerUseBtn(playerid, KeyID)
{
    if(KeyID == 89) // Y
    {
        if(pTemp[playerid][pFromID] != INVALID_PLAYER_ID)
        {
            // логика принятия предложения
        }
    }
    else if(KeyID == 78) // N
    {
        CancelRequest(playerid);
    }
}

stock ClearProposition(playerid)
{
    pTemp[playerid][pFromID] = INVALID_PLAYER_ID;
    pTemp[playerid][pToID] = INVALID_PLAYER_ID;
    pTemp[playerid][pVal1] = -1;
    pTemp[playerid][pVal2] = -1;
    pTemp[playerid][pType] = -1;

    KillTimer(OfferTimer[playerid]);
    if(IsPlayerLogged{playerid}) cef_emit_event(playerid, "remove-notifications:proposal");

    return 1;
}