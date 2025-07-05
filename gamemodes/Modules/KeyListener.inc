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
		RadialUpdate[playerid] = SetTimerEx("OnRadialUpdate", 1000, true, "d", playerid);

		pTemp[playerid][pRadialOpen] = 1;

		cef_emit_event(playerid, "execute.event:radial-show", CEFINT(true));
	}
	if(KeyID == 27)
	{
		if pTemp[playerid][pRadialOpen] == 1 *then
		{
			KillTimer(RadialUpdate[playerid]);
		}
	}
}
public OnPlayerKeyUp(playerid, KeyID)
{
	//SCMF(playerid, -1, "You PressKey (up) -< %d", KeyID);
}