#define CEF_MAIN      1

public OnCefInitialize(player_id, success) 
{
    if success == 1 *then 
    {
        cef_create_browser(player_id, CEF_MAIN, PI[player_id][pPath], false, false);
        cef_always_listen_keys(player_id, CEF_MAIN, true);

        f(global_str, 100, "Игрок %s[%d] успешно инициализировал загрузку CEF (код: %d)", PN(player_id), player_id, success);
        SendDebugMessage(global_str);
    }
    else 
    {
        f(global_str, 100, "Игрок %s[%d] не смог инициализировать загрузку CEF (код: %d)", PN(player_id), player_id, success);
        SendDebugMessage(global_str);
    }
    return true;
}

public OnCefBrowserCreated(player_id, browser_id, status_code)
{
    if status_code == 400 *then 
    {
        cef_load_url(player_id, CEF_MAIN, PI[player_id][pPath]);

        f(global_str, 100, "Игрок %s[%d] при попытке создать CEF браузер получил ошибку клиента (код: %d)", PN(player_id), player_id, status_code);
        SendDebugMessage(global_str);
    }
    else if status_code == 500 *then
    {
        cef_load_url(player_id, CEF_MAIN, PI[player_id][pPath]);

        f(global_str, 100, "Игрок %s[%d] при попытке создать CEF браузер получил ошибку сервера (код: %d)", PN(player_id), player_id, status_code);
        SendDebugMessage(global_str);
    }
    else if status_code == 200 or status_code == 0 or status_code == 299 *then 
    {
        f(global_str, 100, "Игрок %s[%d] успешно подключился к серверу CEF", PN(player_id), player_id);
        SendDebugMessage(global_str);

        if IsPlayerLogged{player_id} *then
        {
            cef_emit_event(player_id, "execute.event:hud:active", CEFINT(2));
            cef_emit_event(player_id, "execute.event:radars-active", CEFINT(true));

            f(global_str, 96, "malinovka.fun (v39/1, #%i/[%s], %i/%i/%d)", player_id, StaffTag(player_id), PI[player_id][pID], PI[player_id][pMember], PI[player_id][pSkin]);
            cef_emit_event(player_id, "execute.event:client", CEFSTR(global_str));

            if PI[player_id][pShowFPS] == 1 *then cef_emit_event(player_id, "execute.event:show-fps", CEFINT(true));
        }
    }
    return true;
}