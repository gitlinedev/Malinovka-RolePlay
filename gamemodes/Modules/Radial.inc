public: OnRadialUpdate(playerid)
{
    if pTemp[playerid][pRadialOpen] == 1 *then 
    {
        f(global_str, 50, "Подключено (%d ms, %.2f loss)", GetPlayerPing(playerid), NetStats_PacketLossPercent(playerid));

        cef_emit_event(playerid, "execute.event:radial-network", 
            CEFSTR(PN(playerid)), CEFINT(GetServerOnline()), CEFSTR(global_str), CEFSTR(global_str));

        cef_emit_event(playerid, "execute.event:radial-time", 
            CEFINT(PI[playerid][pDayOnline] / 60), CEFINT(PI[playerid][pDayAFK] / 60), CEFINT(PI[playerid][pPlayedTime] / 60));
    }
    return 1;
}

public: RadialResponce(playerid, callback[])
{
    new id;
    sscanf(callback, "i", id);
    switch(id)
    {
        case 0: 
        {
            /* загрузка транспорта  */
        }
        case 1: 
        {
            /* пассивный режим  */
        }
        case 2: 
        {
            /* анимации  */
        }
        case 3: 
        {
            /* документы  */
        }
        case 5: 
        {
            /* лечь спать  */
        }
        case 6: 
        {
            /* доп. действия  */
        }
        case 7: 
        {
            /* удост. развозчика  */
        }
        case 8: 
        {
            /* фитнес навыки  */
        }
        case 9: 
        {
            /* удост. дальнобойщика  */
        }
        case 10: 
        {
            /* статистика дуэлей  */
        }
        case 11: 
        {
            /* Навыки владения оружием */
        }
    }
    return 1;
}