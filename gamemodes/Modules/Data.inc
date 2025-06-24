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

#define MAX_GPS_CATEGORIES 6
#define MAX_CATEGORY_NAME 32
#define MAX_GPS_ITEM_LENGTH 96

new JailZone, 
    gGangZoneId,
    SaveServer = 1800;

new Float:JailZonePos[] = {
	-1817.0,-2745.0,-1663.0,-2833.0,-1730.0,-2961.0,-1890.0,-2879.0,-1817.0,-2745.0
};

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

enum TeamColor
{
    ColorInt,
    ColorStr[8]
};

new TeamColors[][TeamColor] =
{
    {0xFFFFFFFF, "FFFFFF"}, //None
    {0xFFEB9CFF, "FFEB9C"}, //GOV
    {0x009900FF, "009900"}, //ARMY
    {0xFF99CCFF, "FF99CC"}, //MEDIC
    {0x2222FFFF, "2222FF"}, //POLICE
    {0x663399BB, "663399"}, //SKINHEAD
    {0x339933AA, "339933"}, //KAVKAZ
    {0x66CCFFFF, "66CCFF"}  //GOPOTA
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
	{"облачная погода", 7, 16},
	{"гром", 9, 17},
	{"сильный ветер", 8, 21},
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

enum vInfo
{
    vID,
    vModel,
 	Float:vFuel,
	Float:vPos_X,
	Float:vPos_Y,
	Float:vPos_Z,
	Float:vPos_A,
    vEngine,
	vLights,
	vAlarm,
	vDoors,
	vBonnet,
	vBoot,
    vColor_1,
	vColor_2,
    vLock,
	vAdminCar,
    vKey
};
new VehicleInfo[MAX_VEHICLES][vInfo];

new Engine, Lights, Alarm, Doors, Bonnet, Boot, Objective;

new gPlayerLogTries[MAX_PLAYERS char],
	bool:ALogin[MAX_PLAYERS char],
	bool:AnimPlayed[MAX_PLAYERS char],
	bool:IsPlayerLogged[MAX_PLAYERS char];

new PlayerMail[MAX_PLAYERS][50],
	PlayerName[MAX_PLAYERS][MAX_PLAYER_NAME],
	PlayerReferal[MAX_PLAYERS][24],
	PlayerRegIP[MAX_PLAYERS][16],
	PlayerIp[MAX_PLAYERS][16],
    RegisterState[MAX_PLAYERS],
    SpeedometerUpdate[MAX_PLAYERS];

new RegPass[MAX_PLAYERS][30];
new RegSex[MAX_PLAYERS];
new RegReferal[MAX_PLAYERS][24];

enum eventSettings
{
	bool:IsEventStart,
    bool:TeleportEnable,
    bool:ResetWeapons,
	Float:TeleportX,
	Float:TeleportY,
	Float:TeleportZ,
    TeleportInt,
    TeleportVW
}
new eSettings[eventSettings];

enum _temp_
{
	bool:SpectPlayer,
	targetID,
	ACWarnings,
	dialogListItem,
    pMarker,
    pLastDrunkLevel,
    pCurrentFPS,
    Float:pMarkerX,
    Float:pMarkerY,
    Float:pMarkerZ,
    pTestDrive,
    pOnEvent,
    Float:pOldX,
    Float:pOldY,
    Float:pOldZ,
    pDriver
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
    pShowNameTags,
    pCinemaMode,
	pMute,
	pMuteTime,
    pVoiceChat,
	pWarns,
	pWarnsTime,
	pJail,
	pJailTime,
    pShowFPS,
    pHouseKey,
    pDamageMP3,
    pShowRain,
	pHospital,
	pSkin,
	pWanted,
	pHWID[35],
	pUUID[70],
	pPath[150],
    pVMute,
    pVMuteTime
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


    PI[playerid][pID] = 
    PI[playerid][pHouseKey] =
	pTemp[playerid][dialogListItem] = -1;

	PI[playerid][pWarnsTime] =
	PI[playerid][pJailTime] =
    PI[playerid][pVMuteTime] =
    PI[playerid][pShowRain] =
    PI[playerid][pDamageMP3] =
	PI[playerid][pMuteTime] = 0;
	

    pTemp[playerid][pLastDrunkLevel] =
    pTemp[playerid][pCurrentFPS] =
    pTemp[playerid][pDriver] =
    pTemp[playerid][pMarker] =
    pTemp[playerid][pOnEvent] =
    pTemp[playerid][pTestDrive] =
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
    PI[playerid][pVMute] =
    PI[playerid][pShowNameTags] =
	PI[playerid][pDemorgan] =
	PI[playerid][pMute] =
    PI[playerid][pShowFPS] =
    PI[playerid][pCinemaMode] =
    PI[playerid][pVoiceChat] =
	PI[playerid][pWanted] =
	PI[playerid][pRang] =
	PI[playerid][pMember] =
	PI[playerid][pLeader] =
	PI[playerid][pSex] = 0;
	PI[playerid][pModer] =
    PI[playerid][pExp] = 0;

	PI[playerid][pArmour] =
	PI[playerid][pHealth] =
    pTemp[playerid][pOldX] =
    pTemp[playerid][pOldY] =
    pTemp[playerid][pOldZ] =
    pTemp[playerid][pMarkerX] =
    pTemp[playerid][pMarkerY] =
    pTemp[playerid][pMarkerZ] = 0.0;

	ALogin{playerid} =
	AnimPlayed{playerid} =
	pTemp[playerid][SpectPlayer] = false;

	pTemp[playerid][ACWarnings] = 0;

	pTemp[playerid][targetID] = INVALID_PLAYER_ID;

    gPlayerLogTries{playerid} = 3;
	return 1;
}

new GPS_Categories[MAX_GPS_CATEGORIES][MAX_CATEGORY_NAME] = {
    "Важные места",
    "Временные работы",
    "Основные работы",
    "Государственные организации",
    "Нелегальные организации",
    "Развлечения"
};

new GPS_Items[6][24][MAX_GPS_ITEM_LENGTH] = {
    { // Важные места
        "1. Автовокзал №1\tпгт. Батырево",
        "2. Автовокзал №2\tпгт. Батырево",
        "3. Автовокзал\tпгт. Бусаево",
        "4. Железнодорожный вокзал\tг. Южный",
        "5. Мэрия\tпгт. Батырево",
        "6. Мэрия\tпгт. Бусаево",
        "7. Мэрия\tг. Южный",
        "8. Государственный банк\tпгт. Батырево",
        "9. Военкомат\tпгт. Бусаево",
        "10. Автошкола\tпгт. Бусаево",
        "11. Автосалон (отечественный)\tпгт. Бусаево",
        "12. Автосалон (импортный)\tг. Южный",
        "13. Тюнинг ателье\tг. Южный",
        "14. Авторынок\tНижегородская обл.",
        "15. Клиника\tг. Южный",
        "16. Клиника\tпгт. Батырево",
        "17. Клиника\tНижегородская обл.",
        "18. Тир\tг. Южный",
        "19. Тир\tпгт. Батырево",
        "20. Тир\tпгт. Бусаево",
        "21. Исправительная колония\tИК «Арзамас»",
        "22. Склад вещей\tг. Южный",
        "{FFFF99}23. Сцена на аэродроме\t{FFFF99}Нижегородская обл.",
        "{FFFF99}24. Приёмная президента\t{FFFF99}пгт. Бусаево"
    },
    { // Временные работы
        "1. Ферма {FFFF99}[1+ уровень]\tс. Роговичи\n",
        "2. Лесопилка {FFFF99}[1+ уровень]\tНижегородская обл.",
        "3. Шахта {FFFF99}[1+ уровень]\tНижегородская обл.",
        "4. Технолог {FFFF99}[1+ уровень]\tпгт. Бусаево",
        "5. Автоугонщик {FFFF99}[3+ уровень]\tг. Южный",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", ""
    },
    { // Основные работы
        "{FFFF99}1. Мэрия (трудоустройство)\t{FFFF99}пгт. Батырево",
        "{FFFF99}2. Мэрия (трудоустройство)\t{FFFF99}пгт. Бусаево",
        "{FFFF99}3. Мэрия (трудоустройство)\t{FFFF99}г. Южный",
        "4. Водитель автобуса (первая стоянка)\tпгт. Батырево\n",
        "5. Водитель автобуса (вторая стоянка)\tпгт. Батырево",
        "6. Автомеханик\tпгт. Батырево\n",
        "7. Развозчик\tпгт. Бусаево\n",
        "8. Пилот\tп. Заречный\n",
        "9. Дальнобойщик\tНижегородская обл.",
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""
    },
    { // Гос. организации
        "1. БЦРБ (больница)\tпгт. Батырево",
        "2. Войсковая часть\tг. Лыткарино",
        "3. Полиция\tг. Южный",
        "4. Правительство\tг. Южный",
        "{FFFF99}5. Склад металла (ВЧ)\t{FFFF99}Нижегородская обл.",
        "{FFFF99}6. Склад патронов (ВЧ)\t{FFFF99}п. Заречный",
        "{FFFF99}7. Склад медикаментов (БЦРБ)\t{FFFF99}Нижегородская обл.",
        "{FFFF99}8. Склад боекомплектов (ВЧ)\t{FFFF99}Нижегородская обл.",
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""
    }, 
    { // Нелегальные организации
        "1. Кавказцы\t{FFFF99}пгт. Бусаево",
        "2. Скинхеды\t{FFFF99}пгт. Батырево",
        "3. Гопота\t{FFFF99}г. Южный",
        "{FFFF99}4. Склад веществ\t{FFFF99}с. Роговичи",
        "{FFFF99}5. Заброшенный завод\t{FFFF99}Нижегородская обл.",
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""
    },
    { // Развлечения
        "{FFFF99}1. Мотокросс\t{FFFF99}пгт. Бусаево",
        "{FFFF99}2. Уличные гонки\t{FFFF99}г. Южный",
        "{FFFF99}3. Картинг\t{FFFF99}Нижегородская обл.",
        "{FFFF99}4. Магазин приколов\t{FFFF99}пгт. Батырево",
        "{FFFF99}5. Аренда вертолётов\t{FFFF99}п. Заречный",
        "{FFFF99}6. Сцена около Кремля\t{FFFF99}Нижегородская обл.",
        "7. Резиденция кайфариков\tНижегородская обл.",
        "8. Трухлявый пень\tпгт. Батырево",
        "9. Пень-алкоголик\tпгт. Бусаево",
        "10. Пень-читер\tс. Роговичи",
        "11. Невидимый пень\tНижегородская обл.",
        "12. Ясен пень\tп. Заречный",
        "", "", "", "", "", "", "", "", "", "", "", ""
    }
};

new GPS_Counts[] = {
    24, // Важные места
    5,  // Временные работы
    9,  // Основные работы
    8,  // Гос. организации
    5,  // Нелегальные организации
    12, // Развлечения
};

new Float:GPS_Positions[6][24][3] = {
    { // Важные места
        {1234.0, -1234.0, 13.0},
        {1456.0, -1166.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0}
    },
    { // Временные работы
        {1234.0, -1234.0, 13.0},
        {1456.0, -1166.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}
    },
    { // Основные работы
        {1234.0, -1234.0, 13.0},
        {1456.0, -1166.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}
    },
    { // Гос. организации
        {1234.0, -1234.0, 13.0},
        {1456.0, -1166.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}
    },
    { // Нелегальные организации
        {1234.0, -1234.0, 13.0},
        {1456.0, -1166.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}
    },
    { // Развлечения
        {1234.0, -1234.0, 13.0},
        {1456.0, -1166.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {1100.0, -1300.0, 13.0},
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}
    }
};