#include KeyListener

public OnPlayerKeyDown(playerid, KeyID)
{
    SCMF(playerid, -1, "You PressKey (down) -< %d", KeyID);

    if(KeyID == 17)
	{
		callcmd::engine(playerid,"");
	}
    if(KeyID == 77)
	{
		callcmd::menu(playerid);
	}
    if(KeyID == 114)
	{
		callcmd::as(playerid);
	}
	if(KeyID == 9)
	{
		//cef_emit_event(playerid, "execute.event:radial-button", 
		//	CEFINT(/* button id */), CEFINT(/* active true/false */), CEFSTR(/* если кнопка не активна тут причина, если причина не нужна - "" */));

		f(global_str, 50, "Подключено (%d ms, %.2f loss)", GetPlayerPing(playerid), NetStats_PacketLossPercent(playerid));

		cef_emit_event(playerid, "execute.event:radial-network", 
			CEFSTR(PN(playerid)), CEFINT(GetServerOnline()), CEFSTR(global_str), CEFSTR(global_str));

		cef_emit_event(playerid, "execute.event:radial-time", 
			CEFINT(PI[playerid][pDayOnline] / 60), CEFINT(PI[playerid][pDayAFK] / 60), CEFINT(PI[playerid][pPlayedTime] / 60));

		cef_emit_event(playerid, "execute.event:radial-show", CEFINT(true));
	}
}
public OnPlayerKeyUp(playerid, KeyID)
{
	//SCMF(playerid, -1, "You PressKey (up) -< %d", KeyID);
}