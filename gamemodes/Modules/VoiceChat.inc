new SV_GSTREAM:gstream = SV_NULL;
new SV_LSTREAM:lstream[MAX_PLAYERS] = { SV_NULL, ... };

/*new SV_GSTREAM:radio_army[MAX_PLAYERS] = { SV_NULL, ... };
new SV_GSTREAM:radio_police[MAX_PLAYERS] = { SV_NULL, ... };
new SV_GSTREAM:radio_gov[MAX_PLAYERS] = { SV_NULL, ... };
new SV_GSTREAM:radio_skinhead[MAX_PLAYERS] = { SV_NULL, ... };
new SV_GSTREAM:radio_gopota[MAX_PLAYERS] = { SV_NULL, ... };
new SV_GSTREAM:radio_kavkaz[MAX_PLAYERS] = { SV_NULL, ... };
new SV_GSTREAM:radio_hospital[MAX_PLAYERS] = { SV_NULL, ... };*/


public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    if(keyid == 0x58 && lstream[playerid]) SvAttachSpeakerToStream(lstream[playerid], playerid); // X
	/*if(keyid == 0x5A && PI[playerid][pMember] >= 1) 
	{
		if(PI[playerid][pMember] == 1) SvAttachSpeakerToStream(radio_gov[playerid], playerid);
        if(PI[playerid][pMember] == 2) SvAttachSpeakerToStream(radio_army[playerid], playerid);
        if(PI[playerid][pMember] == 3) SvAttachSpeakerToStream(radio_police[playerid], playerid);
        if(PI[playerid][pMember] == 4) SvAttachSpeakerToStream(radio_hospital[playerid], playerid);
        if(PI[playerid][pMember] == 5) SvAttachSpeakerToStream(radio_skinhead[playerid], playerid);
        if(PI[playerid][pMember] == 6) SvAttachSpeakerToStream(radio_gopota[playerid], playerid);
        if(PI[playerid][pMember] == 7) SvAttachSpeakerToStream(radio_kavkaz[playerid], playerid);
	}*/
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    if(keyid == 0x58 && lstream[playerid]) SvDetachSpeakerFromStream(lstream[playerid], playerid); // X
}

/*stock GivePlayerRadio(playerid)
{
    if(PI[playerid][pMember] == 1)
    {
        if((radio_gov[playerid] = SvCreateDLStreamAtPlayer(40.0, SV_INFINITY, playerid, 0xff0000ff, "")))
        {
            if (radio_gov) SvAttachListenerToStream(radio_gov, playerid);
            SvAddKey(playerid, 0x58);
            SvAddKey(playerid, 0x5A);
            CheckStatus(playerid);
        }
    }
    if(PI[playerid][pMember] == 2)
    {
        if((radio_army[playerid] = SvCreateDLStreamAtPlayer(40.0, SV_INFINITY, playerid, 0xff0000ff, "")))
        {
            if (radio_army) SvAttachListenerToStream(radio_army, playerid);
            SvAddKey(playerid, 0x58);
            SvAddKey(playerid, 0x5A);
            CheckStatus(playerid);
        }
    }
    if(PI[playerid][pMember] == 3)
    {
        if((radio_police[playerid] = SvCreateDLStreamAtPlayer(40.0, SV_INFINITY, playerid, 0xff0000ff, "")))
        {
            if (radio_police) SvAttachListenerToStream(radio_police, playerid);
            SvAddKey(playerid, 0x58);
            SvAddKey(playerid, 0x5A);
            CheckStatus(playerid);
        }
    }
    if(PI[playerid][pMember] == 4)
    {
        if((radio_gov[playerid] = SvCreateDLStreamAtPlayer(40.0, SV_INFINITY, playerid, 0xff0000ff, "")))
        {
            if (radio_gov) SvAttachListenerToStream(radio_gov, playerid);
            SvAddKey(playerid, 0x58);
            SvAddKey(playerid, 0x5A);
            CheckStatus(playerid);
        }
    }
    if(PI[playerid][pMember] == 5)
    {
        if((radio_gov[playerid] = SvCreateDLStreamAtPlayer(40.0, SV_INFINITY, playerid, 0xff0000ff, "")))
        {
            if (radio_gov) SvAttachListenerToStream(radio_gov, playerid);
            SvAddKey(playerid, 0x58);
            SvAddKey(playerid, 0x5A);
            CheckStatus(playerid);
        }
    }
    if(PI[playerid][pMember] == 6)
    {
        if((radio_gov[playerid] = SvCreateDLStreamAtPlayer(40.0, SV_INFINITY, playerid, 0xff0000ff, "")))
        {
            if (radio_gov) SvAttachListenerToStream(radio_gov, playerid);
            SvAddKey(playerid, 0x58);
            SvAddKey(playerid, 0x5A);
            CheckStatus(playerid);
        }
    }
}*/