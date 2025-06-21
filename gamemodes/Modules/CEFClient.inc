#define CEF_MAIN      1

public OnCefInitialize(player_id, success) 
{
    if success == 1 *then 
    {
        cef_create_browser(player_id, CEF_MAIN, PI[player_id][pPath], false, false);
        cef_always_listen_keys(player_id, CEF_MAIN, true);
    }
    else 
    {
        f(global_str, 100, "CEF initialization error %s[%d] (success: %d)", PN(player_id), player_id, success);
        SendDebug(player_id, global_str, 1);
    }
    return true;
}

public OnCefBrowserCreated(player_id, browser_id, status_code)
{
    if status_code == 400 *then 
    {
        cef_load_url(player_id, CEF_MAIN, PI[player_id][pPath]);
        f(global_str, 100, "CEF client error at player %s[%d] (code: %d)", PN(player_id), player_id, status_code);
        SendDebug(player_id, global_str, 1);
    }
    else if status_code == 500 *then
    {
        cef_load_url(player_id, CEF_MAIN, PI[player_id][pPath]);
        f(global_str, 100, "CEF server error at player %s (code: %d)", PN(player_id), player_id, status_code);
        SendDebug(player_id, global_str, 1);
    }
    else if status_code == 200 or status_code == 299 *then 
    {
        f(global_str, 100, "Player %s[%d] has successfully connected to the CEF server", PN(player_id), player_id);

        if IsPlayerLogged{player_id} *then
        {
            cef_emit_event(player_id, "execute.event:hud:active", CEFINT(2));
            cef_emit_event(player_id, "execute.event:radars-active", CEFINT(true));

            f(global_str, 96, "malinovka.fun (v39/1, #%i/[%s], %i/%i/%d)", player_id, StaffTag(player_id), PI[player_id][pID], PI[player_id][pMember], PI[player_id][pSkin]);
            cef_emit_event(player_id, "execute.event:client", CEFSTR(global_str));

            if PI[player_id][pShowFPS] == 1 *then cef_emit_event(player_id, "execute.event:show-fps", CEFINT(true));
        }

        SendDebug(player_id, global_str, 1);
    }
    return true;
}