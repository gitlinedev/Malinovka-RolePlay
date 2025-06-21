new SV_GSTREAM:GlobalStream = SV_NULL;
new SV_LSTREAM:LocalStream[MAX_PLAYERS] = { SV_NULL, ... };


public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid)
{
    if(keyid == 0x58 && LocalStream[playerid]) SvAttachSpeakerToStream(LocalStream[playerid], playerid); // X
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    if(keyid == 0x58 && LocalStream[playerid]) SvDetachSpeakerFromStream(LocalStream[playerid], playerid); // X
}