#define COLOR_BLUE              0x33AAFFFF
#define COLOR_LIGHTBLUE 		0x6495EDFF
#define COLOR_WHITE 		    0xFFFFFFFF
#define COLOR_GREY		 		0xAFAFAFFF
#define COLOR_GREENNEW			0x00aa33FF
#define COLOR_YELLOW			0xFFFF00FF
#define COLOR_LIGHTYELLOW		0xFFFF99FF
#define COLOR_TOMATO      		0xFF6347FF
#define COLOR_BLACK             0x5e5e5eFF
#define COLOR_GREY              0xAFAFAFFF
#define COLOR_GREEN 			0x42B02CFF
#define COLOR_RED 			    0xcc3366FF
#define COLOR_PURPLE           	0xFF99CCFF
#define COLOR_BLACKBLUE			0x3366ccFF
#define COLOR_LIGHTGREY 		0xCCCCCCFF
#define COLOR_ADMINCHAT         0x8FBEDBFF
#define COLOR_JOBYELLOW 		0xFFCD00FF
#define COLOR_HINT 				0x6699FFFF
#define COLOR_BLACKRED 			0xCC3366FF
#define COLOR_ANS 				0x886A68FF
#define COLOR_REPORT 			0xFF8877FF

#define TEAM_NONE       (0)
#define TEAM_GOV 		(1)
#define TEAM_ARMY 		(2)
#define TEAM_MEDIC 		(3)
#define TEAM_POLICE		(4)
#define TEAM_SKINHEAD 	(5)
#define TEAM_KAVKAZ 	(6)
#define TEAM_GOPOTA 	(7)

new Float:SpawnInfo[8][4] =
{
	{1874.8156,2228.1123,1036.3204, 90.0},				//Int:  0 | World: 0 | None
	{-469.2832,2201.7419,1601.0879,180.0},				//Int:  10 | World: 10 | GOV
	{-469.2832,2201.7419,1601.0879,180.0},				//Int:  11 | World: 11 | ARMY
	{-2517.5935,-650.5844,1327.9659,358.1692},			//Int:  12 | World: 12 | MEDIC
	{-469.2832,2201.7419,1601.0879,180.0},				//Int:  13 | World: 13 | POLICE
	{1151.9828,-1321.5035,1019.4178,180.7741},			//Int:  14 | World: 14 | SKINHEAD
	{1495.7332,-1283.4430,113.8212,88.8265},			//Int:  15 | World: 15 | KAVKAZ
	{582.7991,1473.3457,1900.7980,94.9175}				//Int:  16 | World: 16 | GOPOTA
};

new TeamColors[8]=
{
	0xFFFFFFFF, //None
    0xffEB9CFF, //GOV
    0x009900FF, //ARMY
    0xFF99CCFF, //MEDIC
	0x2222FFFF, //POLICE
    0x663399BB, //SKINHEAD
    0x339933AA, //KAVKAZ
    0x66CCFFFF //GOPOTA
};

new SpawnIntWorld[8][2] =
{
	{0,0},				//Int: 0 | World: 0 | None
	{10,10},			//Int: 10 | World: 10 | GOV
	{11,11},			//Int: 11 | World: 11 | ARMY
	{12,12},			//Int: 12 | World: 12 | MEDIC
	{13,13},			//Int: 13 | World: 13 | POLICE
	{14,14},			//Int: 14 | World: 14 | SKINHEAD
	{15,15},			//Int: 15 | World: 15 | KAVKAZ
	{16,16}				//Int: 16 | World: 16 | GOPOTA
};

enum smInfo
{
	smInput[5],
	smOutput_M[40],
	smOutput_F[40]
}
new sInfo[5][smInfo] = {
	{")", "улыбается", "улыбается"},
	{"))", "смеётся", "смеётся"},
	{"(", "расстроился", "расстроилась"},
	{"((", "очень расстроился", "очень расстроился"},
	{"xD", "смеётся", "смеётся"}
};

new WeatherServer;

enum WeatherData {
	WeatherName[25],
	WeatherId,
	WeatherDegrees
};
new Weather[][WeatherData] = {
	{"ясная погода", 18, 31},
	{"облачная погода", 18, 16},
	{"гром", 18, 17},
	{"сильный ветер", 18, 21},
	{"ясная погода", 18, 36}
};

#define MAX_INWORDS 28

new InvalidWords[MAX_INWORDS][20] = {
    "mq",
    "сын",
    "дочь",
    "папа",
    "дед",
    "мам",
    "мама",
    "батя",
    "сестра",
    "брат",
    "мку",
    "админ",
    "игровой",
    "мастер",
    "бог",
    "гитлайн",
    "графф",
    "graff",
    "gitline",
    ".com",
    ".org",
    ".ru",
    ".net",
    ".cc",
    ".online",
    ".site",
    "сайт",
    "форум",
};

enum cInfo
{
    cID,
 	Float:cFuel,
	cCreate,
};
new CarInfo[Max_Cars][cInfo];

new gPlayerLogTries[MAX_PLAYERS char],
	bool:ALogin[MAX_PLAYERS char],
	bool:AnimPlayed[MAX_PLAYERS char],
	bool:IsPlayerLogged[MAX_PLAYERS char];

new PlayerMail[MAX_PLAYERS][50],
	PlayerName[MAX_PLAYERS][MAX_PLAYER_NAME],
	PlayerReferal[MAX_PLAYERS][24],
	PlayerRegIP[MAX_PLAYERS][16],
	PlayerIp[MAX_PLAYERS][16],
    RegisterState[MAX_PLAYERS];

new RegPass[MAX_PLAYERS][30];
new RegSex[MAX_PLAYERS];
new RegReferal[MAX_PLAYERS][24];

enum _temp_
{
	bool:SpectPlayer,
	targetID,
	ACWarnings
}
new pTemp[MAX_PLAYERS][_temp_];

enum PlayerInfo {
    pID,
    pAdmin,
	pAdminNumber,
	pModer,
    pMoney,
    pLevel,
	pSex,
    pExp,
	Float:pHealth,
	Float:pArmour,
	pLastIP[16],
	pBank,
	pDonate,
	pLeader,
	pMember,
	pOrgSkin,
	pRang,
	pSpawnSetting,
	pDemorgan,
	pDemorganTime,
	//
	pMute,
	pMuteTime,
	pWarns,
	pWarnsTime,
	pJail,
	pJailTime,

	pHospital,
	pSkin,
	pWanted,

	pHWID[35],
	pUUID[70],
	pPath[150],
};
new PI[MAX_PLAYERS][PlayerInfo];

stock ClearPlayerData(playerid)
{
	PlayerMail[playerid][0] =
	PlayerReferal[playerid][0] =
	PlayerRegIP[playerid][0] =
	PlayerIp[playerid][0] = 
	PI[playerid][pHWID][0] = 
	PI[playerid][pUUID][0] = 
	PI[playerid][pPath][0] = 
	PlayerName[playerid][0] = EOS;


    PI[playerid][pID] = -1;
	PI[playerid][pWarnsTime] =
	PI[playerid][pJailTime] =
	PI[playerid][pDemorganTime] =
	PI[playerid][pMuteTime] = 0;
	
    PI[playerid][pAdmin] =
	PI[playerid][pAdminNumber] =
    PI[playerid][pMoney] =
    PI[playerid][pLevel] =
	PI[playerid][pOrgSkin] =
	PI[playerid][pDonate] =
	PI[playerid][pBank] =
	PI[playerid][pHospital] =
	PI[playerid][pSpawnSetting] =
	PI[playerid][pSkin] =
	PI[playerid][pWarns] =
	PI[playerid][pJail] =
	PI[playerid][pDemorgan] =
	PI[playerid][pMute] =
	PI[playerid][pWanted] =
	PI[playerid][pRang] =
	PI[playerid][pMember] =
	PI[playerid][pLeader] =
	PI[playerid][pSex] = 0;
	PI[playerid][pModer] =
    PI[playerid][pExp] = 0;

	PI[playerid][pArmour] =
	PI[playerid][pHealth] = 0.0;

	ALogin{playerid} =
	AnimPlayed{playerid} =
	pTemp[playerid][SpectPlayer] = false;

	pTemp[playerid][ACWarnings] = 0;

	pTemp[playerid][targetID] = INVALID_PLAYER_ID;

    gPlayerLogTries{playerid} = 3;
	return 1;
}