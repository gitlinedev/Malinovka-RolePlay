/* Типы: no-n - будет без кнопки N | no-y - будет без кнопки Y | none - стандартное уведомление */
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

cmd:test_cef(playerid, data[])
{
    if(sscanf(data, "u", data[0])) 
        return SCM(playerid, COLOR_LIGHTGREY, !"Используйте /test_cef [ id ]"); 

    if playerid == data[0] *then return 0;

    ShowCEF_ForPlayer
    (
        playerid, data[0], "Да", "Отмена", "Предложение от игрока", "none", 45, 1, 2, 1
    ); 

    ShowCEF_ForSender
    (
        playerid, "", "Отмена", "Отменить предложение", "no-y", 45
    );

    return 1;
}

stock ShowCEF_ForPlayer(playerid, targetid, btn_1[], btn_2[], header[], ui_type[], time, val1, val2, type)
{
    cef_emit_event
    (
        targetid, 
        "show-notifications:proposal", 
        CEFINT(time), 
        CEFSTR(header), 
        CEFSTR(btn_1), 
        CEFSTR(btn_2), 
        CEFSTR(ui_type)
    );
    
    OfferTimer[playerid] = SetTimerEx("ClearProposition", time*1000, false, "d", playerid);
	OfferTimer[targetid] = SetTimerEx("ClearProposition", time*1000, false, "d", playerid);

    pTemp[targetid][pFromID] = playerid;

    pTemp[playerid][pToID] = targetid;
    pTemp[playerid][pVal1] = val1;
    pTemp[playerid][pVal2] = val2;
    pTemp[playerid][pType] = type;
    
    return 1;
}

stock ShowCEF_ForSender(playerid, btn_1[], btn_2[], header[], ui_type[], time)
{
    cef_emit_event
    (
        playerid, 
        "show-notifications:proposal", 
        CEFINT(time), 
        CEFSTR(header), 
        CEFSTR(btn_1), 
        CEFSTR(btn_2), 
        CEFSTR(ui_type)
    );

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

stock OnPlayerAccept(playerid) // обрабатывает pTemp[FromID] -> ToID (то есть тот кто принимает и кому отправили)
{
    new FromID = pTemp[playerid][pFromID], 
        Type = pTemp[FromID][pType];

    new Val1 = pTemp[FromID][pVal1], 
        Val2 = pTemp[FromID][pVal2];

    switch(Type)
    {
        case 1:
        {
            SCMF(playerid, COLOR_LIGHTYELLOW, "Вы приняли предложение от -> %s, Val1 %d, Val2 %d", PN(FromID), Val1, Val2);
            SCMF(FromID, COLOR_LIGHTYELLOW, "Принял ваше предложение -> %s, Val1 %d, Val2 %d", PN(playerid), Val1, Val2);
        }
        default:
        {
            return CancelRequest(playerid);
        }
    }
    ClearProposition(FromID);
    ClearProposition(playerid);
    return 1;
}

stock OnPlayerUseBtn(playerid, KeyID)
{
    if(KeyID == 89) // Y
    {
        if(pTemp[playerid][pFromID] != INVALID_PLAYER_ID)
        {
            OnPlayerAccept(playerid);
        }
    }
    else if(KeyID == 78) // N
    {
        CancelRequest(playerid);
    }
}

public: ClearProposition(playerid)
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