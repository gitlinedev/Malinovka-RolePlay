#include KeyListener

public OnPlayerKeyDown(playerid, KeyID)
{
    //SCMF(playerid, -1, "You PressKey (down) -< %d", KeyID);

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
}
public OnPlayerKeyUp(playerid, KeyID)
{
	//SCMF(playerid, -1, "You PressKey (up) -< %d", KeyID);
}