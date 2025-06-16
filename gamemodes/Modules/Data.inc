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
	targetID
}
new pTemp[MAX_PLAYERS][_temp_];

enum PlayerInfo {
    pID,
    pAdmin,
	pAdminNumber,
	pModer,
    pMoney,
    pScore,
	pSex,
    pExp,
	Float:pHealth,
	Float:pArmour,
	pLastIP[16],
	pBank,
	pDonate,

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
	PI[playerid][pMuteTime] = 0;
	
    PI[playerid][pAdmin] =
	PI[playerid][pAdminNumber] =
    PI[playerid][pMoney] =
    PI[playerid][pScore] =
	PI[playerid][pDonate] =
	PI[playerid][pBank] =
	PI[playerid][pHospital] =
	PI[playerid][pSkin] =
	PI[playerid][pWarns] =
	PI[playerid][pJail] =
	PI[playerid][pMute] =
	PI[playerid][pWanted] =
	PI[playerid][pSex] = 0;
	PI[playerid][pModer] =
    PI[playerid][pExp] = 0;

	PI[playerid][pArmour] =
	PI[playerid][pHealth] = 0.0;

	ALogin{playerid} =
	AnimPlayed{playerid} =
	pTemp[playerid][SpectPlayer] = false;

	pTemp[playerid][targetID] = INVALID_PLAYER_ID;

    gPlayerLogTries{playerid} = 3;
	return 1;
}