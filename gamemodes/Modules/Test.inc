

CMD:test_dlg(playerid, params[])
{
    if(sscanf(params, "d", params[0])) return SendClientMessage(playerid, -1, !"Используйте: /test_dlg");
    switch(params[0])
    {
        case 1: ShowPlayerDialog_CEF(playerid, 0, 0, "Привет", "Привет, добро пожаловать на сервер!\n\nТут ты можешь:\n1) Найти друзей\n2)Играть без ограничений", "Далее", "Закрыть");
        case 2: ShowPlayerDialog_CEF(playerid, 0, 1, "Введите вопрос для администрации", "За нарушение правил можете получить наказание!", "Далее", "Закрыть");
        case 3: ShowPlayerDialog_CEF(playerid, 0, 2, "Меню игрока", "Статистика\nСписок команд\nПассивный режим\nНастройки аккаунта\nДополнительные услуги", "Далее", "Закрыть");
        case 4: ShowPlayerDialog_CEF(playerid, 0, 3, "Админ панель", "Введите пароль от админ панели", "Далее", "Закрыть");
        case 5: ShowPlayerDialog_CEF(playerid, 0, 5, "Список администраторов", "Номер ИМ\tУровень\n1\t8\n2\t5", "Далее", "Закрыть");
    }
    return 1;
}

CMD:reload(playerid)
{
    SendClientMessage(playerid, -1, !"CEF reload");
    return cef_load_url(playerid, 1, PI[playerid][pPath]);
}

stock ShowPlayerDialog_CEF(playerid, dialogid, style, caption[], info[], button1[], button2[])
{
    return cef_emit_event(playerid, "execute.event:show-player-dialog", CEFINT(dialogid), CEFINT(style), CEFSTR(caption), CEFSTR(info), CEFSTR(button1), CEFSTR(button2));
}

stock RemovePlayerDialog_CEF(playerid)
{
    return cef_emit_event(playerid, "execute.event:remove-player-dialog");
}

public: InterfaceDialogResponce(playerid, callback[])
{
    new id, responce, listitem, inputtext[144];
    sscanf(callback, "ddds[144]", id, responce, listitem, inputtext);
    //SendClientMessagef(playerid, -1, "OnDialogResponse(%d, %d, %d, %d, %s)", playerid, id, responce, listitem, inputtext);
    OnDialogResponse(playerid, id, responce, listitem, inputtext);
    return RemovePlayerDialog_CEF(playerid);
}

CMD:test_radial(playerid)
{
    SendClientMessagef(playerid, -1, "window.executeEvent('event.data.active.radial', '[true]');");
    return cef_emit_event(playerid, "execute.event:radial-show", CEFINT(1));
}

CMD:test_button(playerid, params[])
{
    if(sscanf(params, "dds[144]", params[0], params[1], params[2])) return SendClientMessage(playerid, -1, !"Использовать: /test_button [id] [active] [reason]");
    SendClientMessagef(playerid, -1, "window.executeEvent('event.data.button.radial', '[%d]', '[%d]', [%s]);");
    return cef_emit_event(playerid, "execute.event:radial-button", CEFINT(params[0]), CEFINT(params[1]), CEFSTR(params[2]));
}

public: InterfaceRadialResponce(playerid, callback[])
{
    new id;
    sscanf(callback, "d", id);
    return SendClientMessagef(playerid, -1, "Responce Radial Button (id: %d)", id);
}