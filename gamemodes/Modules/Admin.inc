enum AdminInfo
{
	admInfoNewPlayer,
	admKillList,
	admIP,
	admACMsg,
	admJoin,
	admFlySpeed,
	admHide,
	admShowReport,
    admGethere,
    admGoto,
    admInterior
}
new AInfo[MAX_PLAYERS][AdminInfo];
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
static const AdminPassword[8] = {5673, 4657, 1345, 9755, 7367, 2556, 8086, 6769};
static const Admin_Names[9][5] = {"None","NGM","JRGM","GM","GM+","LGM","SGM","SGM+","DEV"};
static const Moder_Names[4][5] = {"None","JM","M","SM"};

static const stock Vehicle_Names[][] = {
	"Car400", "Car401", "Car402", "Car403", "Car404", "Car405", "Car406", "Car407", "Car408", "Car409", "Car410", "Car411",
	"Car412", "Car413", "Car414", "Car415", "Car416", "Car417", "Car418", "Car419", "Car420", "Car421", "Car422", "Car423", "Car424",
	"Car425", "Car426", "Car427", "Car428", "Car429", "Car430", "Car431", "Car432", "Car433", "Car434", "Car435", "Car436", "Car437",
	"Car438", "Car439", "Car440", "Car441", "Car442", "Car443", "Car444", "Car445", "Car446", "Car447", "Car448", "Car449", "Car450",
	"Car451", "Car452", "Car453", "Car454", "Car455", "Car456", "Car457", "Car458", "Car459", "Car460", "Car461", "Car462", "Car463",
	"Car464", "Car465", "Car466", "Car467", "Car468", "Car469", "Car470", "Car471", "Car472", "Car473", "Car474", "Car475", "Car476",
	"Car477", "Car478", "Car479", "Car480", "Car481", "Car482", "Car483", "Car484", "Car485", "Car486", "Car487", "Car488", "Car489",
	"Car490", "Car491", "Car492", "Car493", "Car494", "Car495", "Car496", "Car497", "Car498", "Car499", "Car500", "Car501", "Car502",
	"Car503", "Car504", "Car505", "Car506", "Car507", "Car508", "Car509", "Car510", "Car511", "Car512", "Car513", "Car514", "Car515",
	"Car516", "Car517", "Car518", "Car519", "Car520", "Car521", "Car522", "Car523", "Car524", "Car525", "Car526", "Car527", "Car528",
	"Car529", "Car530", "Car531", "Car532", "Car533", "Car534", "Car535", "Car536", "Car537", "Car538", "Car539", "Car540", "Car541",
	"Car542", "Car543", "Car544", "Car545", "Car546", "Car547", "Car548", "Car549", "Car550", "Car551", "Car552", "Car553", "Car554",
	"Car555", "Car556", "Car557", "Car558", "Car559", "Car560", "Car561", "Car562", "Car563", "Car564", "Car565", "Car566", "Car567",
	"Car568", "Car569", "Car570", "Car571", "Car572", "Car573", "Car574", "Car575", "Car576", "Car577", "Car578", "Car579", "Car580",
	"Car581", "Car582", "Car583", "Car584", "Car585", "Car586", "Car587", "Car588", "Car589", "Car590", "Car591", "Car592", "Car593",
	"Car594", "Car595", "Car596", "Car597", "Car598", "Car599", "Car600", "Car601", "Car602", "Car603", "Car604", "Car605", "Car606",
	"Car607", "Car608", "Car609", "Car610", "Car611"
};
// WeaponNames[ID][0] — Названия оружия по ID (0-46)
new const WeaponNames[][] = {
    /*  0 */ {"Кулак"},                      // Безоружие
    /*  1 */ {"Кастет"},
    /*  2 */ {"Клюшка для гольфа"},
    /*  3 */ {"Полицейская дубинка"},
    /*  4 */ {"Нож"},
    /*  5 */ {"Бейсбольная бита"},
    /*  6 */ {"Лопата"},
    /*  7 */ {"Кий"},
    /*  8 */ {"Катана"},
    /*  9 */ {"Бензопила"},
    /* 10 */ {"Большой дилдо"},
    /* 11 */ {"Малый дилдо"},
    /* 12 */ {"Большой вибратор"},
    /* 13 */ {"Малый вибратор"},
    /* 14 */ {"Цветы"},
    /* 15 */ {"Трость"},
    /* 16 */ {"Граната"},
    /* 17 */ {"Слезоточивый газ"},
    /* 18 */ {"Коктейль Молотова"},
    /* 19 */ {""},                           // Не используется
    /* 20 */ {""},                           // Не используется
    /* 21 */ {""},                           // Не используется
    /* 22 */ {"ТТ"},                         // Пистолет ТТ (замена стандартного пистолета)
    /* 23 */ {"Тайзер"},                     // Электрошокер
    /* 24 */ {"ПЛ-15"},                      // Пистолет ПЛ-15
    /* 25 */ {"Дробовик"},
    /* 26 */ {"Обрез"},
    /* 27 */ {"Автоматический дробовик"},
    /* 28 */ {"Узи"},
    /* 29 */ {"MP5"},
    /* 30 */ {"АК-47"},
    /* 31 */ {"M4"},
    /* 32 */ {"TEC-9"},
    /* 33 */ {"Винтовка"},
    /* 34 */ {"Снайперская винтовка"},
    /* 35 */ {"Гранатомёт"},
    /* 36 */ {"Самонаводящийся гранатомёт"},
    /* 37 */ {"Огнемёт"},
    /* 38 */ {"Пулемёт"},
    /* 39 */ {"Взрывпакет"},
    /* 40 */ {"Детонатор"},
    /* 41 */ {"Баллончик с краской"},
    /* 42 */ {"Огнетушитель"},
    /* 43 */ {"Фотоаппарат"},
    /* 44 */ {"Прибор ночного видения"},
    /* 45 */ {"Тепловизор"},
    /* 46 */ {"Парашют"}
};

enum AdminCommand
{
	adminCommand[30],
	adminLevel,
	moderLevel,
	adminCommandInfo[100]
};
new const AdminCommandList[][AdminCommand] = {

	//level 1
	{"as", 1, 0, "Панель игрового мастера"},
	{"a", 1, 1, "Чат игровых-мастеров"},
    {"admins", 1, 1, "Список игровых мастеров"},
    {"ahelp", 1, 0, "Список команд игровых мастеров"},
	{"spawn", 1, 1, "Заспавнить игрока"},
	{"tpcor", 1, 2, "Телепортироваться по координатам"},
	{"freeze", 1, 1, "Заморозить игрока"},
	{"unfreeze", 1, 1, "Разморозить игрока"},
	{"flip", 1, 1, "Починить транспорт игрока"},
	{"ask", 1, 1, "Ответить игроку"},
	{"tpg", 1, 1, "Телепортироваться по метке в GPS"},

	//level 2
	{"slap", 2, 1, "Подбросить игрока в воздух"},
	{"vw", 2, 2, "Перейти в виртуальный мир"},
	{"goto", 2, 3, "Телепортироваться к игроку"},
	{"gethere", 2, 2, "Телепортировать игрока к себе"},
	{"jail", 2, 3, "Посадить игрока в ДеМорган"},
	{"unjail", 2, 3, "Выпустить игрока из ДеМоргана"},
	{"mute", 2, 3, "Выдать блокировку текстового чата"},
	{"unmute", 2, 3, "Снять блокировку текстового чата"},
	{"vmute", 2, 3, "Выдать блокировку голосового чата"},
	{"unvmute", 2, 3, "Снять блокировку голосового чата"},

	//level 3
	{"skin", 3, 3, "Выдать игроку скин (временный/вечный)"},
	{"veh", 3, 3, "Создать транспорт"},
	{"dveh", 3, 3, "Удалить транспорт"},
	{"setarm", 3, 3, "Выдать игроку бронежилет"},
	{"kick", 3, 3, "Кикнуть игрока"},
	{"cc", 3, 3, "Очистить чат"},
	{"setfuel", 3, 3, "Установить уровень топлива в транспорте"},
	{"spawncar", 3, 3, "Заспавнить транспорт"},
	{"gun", 3, 3, "Выдать оружие"},
	{"aclear", 3, 3, "Снять розыск игроку"},
	{"resgun", 3, 3, "Забрать оружие"},
	{"warn", 3, 3, "Выдать предупреждение игроку"},
	{"unwarn", 3, 3, "Снять предупреждение игроку"},	
	
	//level 4
	{"atw", 4, 0, "Забрать оружие у игроков в радиусе"},
	{"ahp", 4, 0, "Выдать ХП игрокам в радиусе"},
	{"setmp", 4, 0, "Установить точку телепорта на мероприятие"},
	{"editmp", 4, 0, "Настроить мероприятие"},
	{"ban", 4, 0, "Заблокировать игрока"},
	{"unban", 4, 0, "Разблокировать игрока"},

	//level 5
	{"msg", 5, 0, "Написать на весь сервер"},
	{"skick", 5, 0, "Кикнуть игрока с сервера без уведомления"},
	// 5 лвл добавить /setleader, /setmember, /auninvite
	

	//level6
	{"setsex", 6, 0, "Изменить пол персонажа игроку"},
	{"makemoder", 6, 0, "Выдать права игрового модератора"},
	{"givemoney", 6, 0, "Выдать игроку деньги"},

	//level7
	{"banip", 7, 0, "Заблокировать IP игрока"},
	{"unbanip", 7, 0, "Разблокировать IP игрока"},
	{"banpc", 7, 0, "Заблокировал игрок по HWID/UUID"},
	{"unbanpc", 7, 0, "Разблокировать игрока по HWID"},
	{"setstat", 7, 0, "Изменить параметры игроку"},

    //level 8
    {"makegm", 8, 0, "Выдать права игрового мастера"},
	{"givedonate", 8, 0, "Выдать донат игроку"}
	// /givemoneyall
	// /givedonateall
	// /givevipall
};

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
cmd:givedonate(playerid, params[])
{
	if(!CheckAccess(playerid, 8))
		return 0;

	new targetid, value;

	if (sscanf(params, "ud", targetid, value))
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /givedonate [ID игрока] [количество]");
	
	if (!IsPlayerOnline(targetid)) 
        return 0;
	
	if (value > 1000)
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /givedonate [ID игрока] [ 1 < 1000]");
	
	SCMF(targetid, -1, "Игровой мастер выдал Вам %d малинки", value);
    SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] выдал %d малинки игроку %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, value, PN(targetid));

	PI[playerid][pDonate] += value;

	f(global_str, 15, "+%d мал.", value);
	cef_emit_event(playerid, "show-notifications:radar", CEFINT(43), CEFINT(5), CEFSTR("green"), CEFSTR("Начисление"), CEFSTR(global_str), CEFINT(""));

	return true;
}

cmd:setstat(playerid, params[])
{
    if(CheckAccess(playerid, 7)) return 1;

    new id, idf, amount;

    if(sscanf(params, "udd", id, idf, amount)) {
        SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /setstat [ID] [ID-функции] [кол-во]");
        return ShowSetStats(playerid);
    }

    if(idf == 0)
		return ShowSetStats(playerid);

    if(idf < 1 || idf > 3) 
		return SCM(playerid, COLOR_LIGHTGREY, !"Неверный ID-функции");

	static fName[35];

    if(idf == 1)
    {
        GivePlayerMoney(playerid, amount);
	    PI[playerid][pMoney] = amount;
		UpdatePlayerDataInt(playerid, "Money", PI[playerid][pMoney]);

		fName = "деньги";
    }
    else if(idf == 2)
    {
        PI[id][pLevel] = amount;
        SetPlayerScore(id, PI[id][pLevel]);

		fName = "уровень";
    }

	else if(idf == 3)
    {
        PI[id][pExp] = amount;
		fName = "опыт";
    }

    SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] изменил игроку %s параметр '%s' на %d",\
        StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(id), fName, amount);

    return SaveAccount(id);
}


cmd:givemoney(playerid, params[])
{
	if(!CheckAccess(playerid, 6))
		return 0;

	new targetid, value;

	if (sscanf(params, "ud", targetid, value))
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /givemoney [ID игрока] [количество]");
	
	if (!IsPlayerOnline(targetid)) 
        return 0;
	
	if (value > 10000000)
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /givemoney [ID игрока] [ 1 < 10.000.000]");
	
	SCMF(targetid, -1, "%s выдал Вам %d рублей", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор", value);
    SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] выдал %d рублей игроку %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, value, PN(targetid));

	f(global_str, 30, "Выдача от ИМ #%d", PI[playerid][pAdminNumber]);
	GivePlayerMoneyLog(targetid, value, global_str);

	f(global_str, 15, "+%d руб.", value);
	cef_emit_event(playerid, "show-notifications:radar", CEFINT(43), CEFINT(5), CEFSTR("green"), CEFSTR("Начисление"), CEFSTR(global_str), CEFINT(""));

	return true;
}

cmd:unwarn(playerid, params[])
{
    if (!CheckAccess(playerid, 2, 3)) 
        return 0;

    new targetid;
    if (sscanf(params, "u", targetid)) 
        return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /unwarn [ID игрока]");

    if (!IsPlayerOnline(targetid)) 
        return 0;

    if (PI[targetid][pWarns] <= 0)
        return SCM(playerid, COLOR_LIGHTGREY, !"У игрока нет активных варнов.");

    RemovePlayerWarn(targetid, 0);

    SCMF(targetid, COLOR_TOMATO, "%s снял Вам предупреждение", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
    SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] снял игроку %s предупреждение", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(targetid));

    return 1;
}

cmd:warn(playerid, params[])
{
	if (!CheckAccess(playerid, 2, 3)) return 0;

	new targetid, reason[100];
	if (sscanf(params, "us[100]", targetid, reason)) 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /warn [ID игрока] [причина]");

	if (!IsPlayerOnline(targetid)) return 0;

	if (strlen(reason) > 30) 
		return SCM(playerid, COLOR_LIGHTGREY, !"Причина не может быть больше 30 символов");
	
	if (PI[targetid][pWarns] < 2)
	{
		new slot = PI[targetid][pWarns]++;
		PI[targetid][pWarnsTimers][slot] = 21600;

		new pid = CreatePunishment(targetid, playerid, 6, 3, reason);

		SAMF(COLOR_ADMINCHAT, "[%s #%d] %s выдал предупреждение игроку %s [%d/3]. Причина: %s",\
			StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), PN(targetid), PI[targetid][pWarns], reason);

		SCMF(targetid, COLOR_TOMATO, "%s выдал Вам предупреждение [%d/3]. Причина: %s", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор", PI[targetid][pWarns], reason);
		SCMF(targetid, COLOR_LIGHTGREY, "Номер наказания: {00912D}#%d{CCCCCC} (для обжалования на {F87031}forum.m-bonus.com{CCCCCC})", pid);
		SCM(targetid, COLOR_LIGHTGREY, !"До снятия всех предупреждений запрещено вступать во фракции");
	}
	else
	{
		PI[targetid][pWarns] = 0;
		for (new i; i < 3; i++) PI[targetid][pWarnsTimers][i] = 0;

		new pid = CreatePunishment(targetid, playerid, 2, 7, reason);

		BanName(PN(targetid), PN(playerid), 7, reason);

		SAMF(COLOR_TOMATO, "[%s #%d] %s заблокировал %s на 7 дней. Причина: 3 предупреждения",\
			StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), PN(targetid));

		ShowBanDialog(targetid, pid, reason);
		PI[targetid][pLeader] = PI[targetid][pAdmin] = PI[targetid][pAdminNumber] = 0;

		SaveAccount(targetid);
		SCM(targetid, COLOR_BLACK, !"Ваш аккаунт заблокирован, для выхода введите /q");
	}
	SpecPl(targetid, true);
	return PrepareKickCamera(targetid);
}

cmd:makemoder(playerid, params[]) 
{
    if(!CheckAccess(playerid, 6)) 
        return false;

    if sscanf(params,"u",params[0]) *then 
        return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /makemoder [ID игрока]");

	if params[0] == INVALID_PLAYER_ID *then return 0;

    if params[0] == playerid *then return 0;

	if !IsPlayerLogged{params[0]} *then return SCM(playerid, COLOR_LIGHTGREY, !"Игрок не авторизован");

    pTemp[playerid][targetID] = params[0];

	return SPD(playerid, dMakeGameModer, DIALOG_STYLE_LIST, !"{EE3366}Выдача прав игрового модератора", !"Снять права игрового модератора\n1. Junior Moderator\n2. Moderator\n3. Senior Moderator", !"Далее", !"Отмена");
}

cmd:vmute(playerid, params[])
{
	if(!CheckAccess(playerid, 2, 3)) 
        return false;

    new time;
    if(sscanf(params,"uds[100]", params[0], time, params[1])) return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /vmute [ID игрока] [время] [причина]");

	if !IsPlayerOnline(params[0]) *then return false;

    if(strlen(params[1]) > 30) 
		return SCM(playerid,COLOR_LIGHTGREY, !"Причина не может быть больше 30 символов");

    if(PI[params[0]][pVMute] == 1)
		return SCM(playerid, COLOR_LIGHTGREY, !"Этот игрок уже имеет блокировку текстового чата");

    if(time == 0) 
		return SCM(playerid, COLOR_LIGHTGREY, !"Нельзя заблокировка текстовый чат на 0 минут");

    if(time> 900) 
		return SCM(playerid, COLOR_LIGHTGREY, !"Нельзя заблокировать текстовый чат больше чем на 900 минут");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	SetSpawnInfoEx(params[0], GetSkinOfPlayer(playerid), -1764.1515, -2889.2085, 14.3141, 240.8832);

	new punishmentID = CreatePunishment(params[0], playerid, 5, time, params[1]);
	SCMF(playerid, COLOR_TOMATO, "Вы заблокировали голосовой чат игрока %s на %d минут. Причина: %s", PN(params[0]), time, params[1]);
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] заблокировал голосовой чат игроку %s на %d минут. Причина: %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid),playerid, PN(params[0]), time,params[1]);

	SCMF(params[0], COLOR_TOMATO, "Использование голосового чата заблокировано на %d мин. Причина: %s", time, params[1]);
	SCMF(params[0], COLOR_LIGHTGREY, "Номер наказания: {00912D}#%d{CCCCCC} (для обжалования на {F87031}forum.m-bonus.com{CCCCCC})", punishmentID);
	SCM(params[0], COLOR_LIGHTGREY, !"Время до разблокировки отображается в правом верхнем углу");
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	PI[params[0]][pVMuteTime] = time*60;
	PI[params[0]][pVMute] = 1;
	SvMutePlayerEnable(params[0]);

	cef_emit_event(params[0], "show-notifications:hud", CEFINT(103), CEFSTR("red-time"), CEFSTR("Блокировка голосового чата"), CEFINT(PI[params[0]][pDemorgan]));

	return 1;
}

cmd:mute(playerid, params[])
{
	if(!CheckAccess(playerid, 2, 3)) 
        return false;

    new time;
    if(sscanf(params,"uds[100]", params[0], time, params[1])) return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /mute [ID игрока] [время] [причина]");

	if !IsPlayerOnline(params[0]) *then return false;

    if(strlen(params[1]) > 30) 
		return SCM(playerid,COLOR_LIGHTGREY, !"Причина не может быть больше 30 символов");

    if(PI[params[0]][pMute] == 1)
		return SCM(playerid, COLOR_LIGHTGREY, !"Этот игрок уже имеет блокировку текстового чата");

    if(time == 0) 
		return SCM(playerid, COLOR_LIGHTGREY, !"Нельзя заблокировка текстовый чат на 0 минут");

    if(time> 900) 
		return SCM(playerid, COLOR_LIGHTGREY, !"Нельзя заблокировать текстовый чат больше чем на 900 минут");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	SetSpawnInfoEx(params[0], GetSkinOfPlayer(playerid), -1764.1515, -2889.2085, 14.3141, 240.8832);

	new punishmentID = CreatePunishment(params[0], playerid, 4, time, params[1]);
	SCMF(playerid, COLOR_TOMATO, "Вы заблокировали текстовый чат игрока %s на %d минут. Причина: %s", PN(params[0]), time, params[1]);
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] заблокировал текстовый чат игроку %s на %d минут. Причина: %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid),playerid, PN(params[0]), time,params[1]);

	SCMF(params[0], COLOR_TOMATO, "Использование чата заблокировано на %d мин. Причина: %s", time, params[1]);
	SCMF(params[0], COLOR_LIGHTGREY, "Номер наказания: {00912D}#%d{CCCCCC} (для обжалования на {F87031}forum.m-bonus.com{CCCCCC})", punishmentID);
	SCM(params[0], COLOR_LIGHTGREY, !"Время до разблокировки отображается в правом верхнем углу");
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	PI[params[0]][pMuteTime] = time*60;
	PI[params[0]][pMute] = 1;

	cef_emit_event(params[0], "show-notifications:hud", CEFINT(102), CEFSTR("red-time"), CEFSTR("Блокировка текстового чата"), CEFINT(PI[params[0]][pDemorgan]));

	return 1;
}

cmd:unvmute(playerid, params[])
{
	if(!CheckAccess(playerid, 2, 3)) 
        return false;

    if(sscanf(params,"u", params[0])) return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /unvmute [ID игрока]");

	if !IsPlayerOnline(params[0]) *then return false;

    if(PI[params[0]][pMute] <= 0)
		return SCM(playerid, COLOR_LIGHTGREY, !"Этот игрок не имеет блокировки голосового чата");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	SCMF(params[0], COLOR_TOMATO, "%s снял Вам блокировку голосового чата", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] снял игроку %s блокировку голосового чата", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid),playerid, PN(params[0]));
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	PI[params[0]][pVMute] = 0;
	PI[params[0]][pVMuteTime] = 0;
	SvMutePlayerDisable(params[0]);

	RemoveActivePunishment(params[0], 5);

	cef_emit_event(playerid, "remove-notifications:radar", CEFINT(103));
	return 1;
}

cmd:unmute(playerid, params[])
{
	if(!CheckAccess(playerid, 2, 3)) 
        return false;

    if(sscanf(params,"u", params[0])) return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /unmute [ID игрока]");

	if !IsPlayerOnline(params[0]) *then return false;

    if(PI[params[0]][pMute] <= 0)
		return SCM(playerid, COLOR_LIGHTGREY, !"Этот игрок не имеет блокировки текстового чата");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	SCMF(params[0], COLOR_TOMATO, "%s снял Вам блокировку текстового чата", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] снял игроку %s блокировку текстового чата", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid),playerid, PN(params[0]));
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	PI[params[0]][pMute] = 0;
	PI[params[0]][pMuteTime] = 0;

	RemoveActivePunishment(params[0], 4);

	cef_emit_event(playerid, "remove-notifications:radar", CEFINT(102));
	return 1;
}

cmd:unjail(playerid, params[])
{
	if(!CheckAccess(playerid, 2, 3)) 
        return false;

    if(sscanf(params,"u", params[0])) return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /unjail [ID игрока]");

	if !IsPlayerOnline(params[0]) *then return false;

    if(PI[params[0]][pDemorgan] <= 0)
		return SCM(playerid, COLOR_LIGHTGREY, !"Этот игрок не в ДеМоргане");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	SCMF(params[0], COLOR_TOMATO, "%s выпустил Вас из тюрьмы", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] выпустил игрока %s из тюрьмы", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid),playerid, PN(params[0]));
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	PI[params[0]][pDemorgan] = 0;
	UpdatePlayerHealth(params[0], 100);
	PlayerSpawn(params[0]);

	RemoveActivePunishment(params[0], 1);

	cef_emit_event(playerid, "remove-notifications:radar", CEFINT(101));
	return 1;
}

cmd:unbanpc(playerid, data[])
{
	if(!CheckAccess(playerid, 7)) 
        return false;

	new name[MAX_PLAYER_NAME];

	if(sscanf(data, "s[24]", name))
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /unbanpc [имя]");

    if !IsBannedNamePC(name) *then
		return SCM(playerid, -1, !"Этот игрок не заблокирован по железу");

	UnBanNamePC(name);
	SCMF(playerid, -1, !"Игрок %s разблокирован", name);

	f(global_str, 256, "[%s #%d] %s разблокировал ПК игроку %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), name);
	return SendAdminsMessage(COLOR_ADMINCHAT, global_str);
}

cmd:banpc(playerid, data[])
{
	if(!CheckAccess(playerid, 7)) 
        return false;

	new id;

    if sscanf(data, "u", id) *then
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /banpc [ID игрока]");

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	global_str = "";
	global_str = GenerateBanCode(7);

	BanPlayerPC(PN(id), PI[id][pHWID], PI[id][pUUID], global_str);
	CreatePunishment(id, playerid, 3, 9999, "NoReason (pc ban)");

	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] заблокировал игрока %s по ПК", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(id));

	SaveAccount(id);

	SCM(id, COLOR_BLACK, !"Ваш аккаунт заблокирован навсегда, для выхода введите /q");
	SpecPl(id, true);
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    PrepareKickCamera(id);
	return 1;
}

cmd:unban(playerid, data[])
{
	if(!CheckAccess(playerid, 4)) 
        return false;

	new
		name[MAX_PLAYER_NAME],
		reason[64];

	if(sscanf(data, "s[24]s[64]", name, reason))
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /unban [имя] [причина]");

    if !IsBannedName(name) *then
		return SCM(playerid, -1, !"Этот игрок не заблокирован на сервере");

	UnBanName(name);
	SCMF(playerid, -1, !"Игрок %s разблокирован", name);

	if strlen(global_str) *then f(global_str, 256, "[%s #%d] %s разблокировал игрока %s, причина: %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), name, reason);
	else f(global_str, 256, "[%s #%d] %s разблокировал игрока %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), name);
	
	return SendAdminsMessage(COLOR_ADMINCHAT, global_str);
}

cmd:ban(playerid, data[])
{
	if(!CheckAccess(playerid, 4)) 
        return false;

	new id, days, reason[30];

    if sscanf(data, "uds[30]", id, days, reason) *then
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /ban [ID игрока] [Дни 1-30] [Причина]");

	if id == INVALID_PLAYER_ID *then
		return 0;

	if strlen(reason) > 30 *then
		return SCM(playerid, COLOR_LIGHTGREY, !"Причина блокировки не может быть больше 30 символов");

	if !(1 <= days <= 30) *then
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /ban [ID игрока] [Дни 1-30] [Причина]");
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	BanName(PN(id), PN(playerid), days, reason);
	new punishmentID = CreatePunishment(id, playerid, 2, days, reason);

	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] заблокировал %s на %d дней. Причина: %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(id), days, reason);
	SCMF(id, COLOR_TOMATO, "Ваш аккаунт заблокирован на %d дн. Причина: %s", days, reason);
	SCMF(id, COLOR_LIGHTGREY, "Номер наказания: {00912D}#%d{CCCCCC} (для обжалования на {F87031}forum.m-bonus.com{CCCCCC})", punishmentID);


	new year, mounth, day, hour, minute, second;
	getdate(year, mounth, day);
	gettime(hour, minute, second);

	SPDF(id, 0, DIALOG_STYLE_MSGBOX, !"{EE3366}Блокировка аккаунта", !"Закрыть", !"", "\
	{FFFFFF}Никнейм:\t\t{3366CC}%s\n\
	{FFFFFF}ID аккаунта:\t\t{3366CC}%d\n\
	{FFFFFF}Номер наказания:\t{00912D}%d\n\
	{FFFFFF}Сервер:\t\tСервер #1\n\
	Дата:\t\t\t%02d.%02d.%04d\n\
	Время:\t\t\t%02d:%02d:%02d\n\
	Причина:\t\t%s\n\
	Количество дней:\t%d дн\n\n\
	{FFFF99}Советуем сделать скриншот (клавиша F8), чтобы иметь\n\
	возможность обжаловать бан на forum.m-bonus.com", PN(id), PI[id][pID], punishmentID, day, mounth, year, hour, minute, second, reason, days);

	PI[id][pLeader] = 0;
	PI[id][pAdmin] = 0;
	PI[id][pAdminNumber] = 0;

	SaveAccount(id);

	SCM(id, COLOR_BLACK, !"Ваш аккаунт заблокирован, для выхода введите /q");
	SpecPl(id, true);
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    PrepareKickCamera(id);
	return 1;
}

cmd:editmp(playerid) 
{
    if(!CheckAccess(playerid, 4)) 
        return false;

	if(eSettings[IsEventStart] == false) return SCM(playerid, COLOR_LIGHTGREY, !"Мероприятие не создано. Запустите мероприятие используя команду /setmp");
	
	f(global_str, 512, "1. Изменить позицию телепорта\t{FFFF99}...\n\
						2. Телепорт на мероприятие:\t\t{FFFF99}%s\n\
						3. Завершить мероприятие\t\t{FFFF99}...\n\
						{FFFF99}Игроков на мероприятии: %d", eSettings[TeleportEnable] ? ("Включен") : ("Выключен"), Iter_Count(Event));
    return SPD(playerid, dEventSettings, DIALOG_STYLE_LIST, !"{EE3366}Настройки МП", global_str, !"Далее", !"Закрыть");
}
cmd:setmp(playerid)
{
    if(!CheckAccess(playerid, 4)) 
        return false;

	if(eSettings[IsEventStart] == false) 
	{
        eSettings[IsEventStart] = true;
		eSettings[TeleportEnable] = false;

		GetPlayerPos(playerid, eSettings[TeleportX], eSettings[TeleportY], eSettings[TeleportZ]);
		eSettings[TeleportInt] = GetPlayerInterior(playerid);
		eSettings[TeleportVW] = GetPlayerVirtualWorld(playerid);

		SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] создал место для телепорта на мероприятие", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid);
	}
	else SCM(playerid, COLOR_LIGHTGREY, !"Точка телепорта уже создана, для управления мероприятием используйте: /editmp");

	return 1;
}
cmd:tpg(playerid)
{
	if(!CheckAccess(playerid, 1, 1)) 
        return false;

	if !IsPlayerOnline(playerid) *then return false;

	if pTemp[playerid][pMarker] == 0 *then return SCM(playerid, COLOR_LIGHTGREY, !"У Вас не установлен маркер в GPS");

	return SetPlayerPosEx(playerid, pTemp[playerid][pMarkerX], pTemp[playerid][pMarkerY], pTemp[playerid][pMarkerZ]);
}
cmd:jail(playerid, params[])
{
	if(!CheckAccess(playerid, 2, 3)) 
        return false;

    new time;
    if(sscanf(params,"uds[100]", params[0], time, params[1])) return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /jail [ID игрока] [время] [причина]");

	if !IsPlayerOnline(params[0]) *then return false;

    if(strlen(params[1]) > 30) 
		return SCM(playerid,COLOR_LIGHTGREY, !"Причина не может быть больше 30 символов");

    if(PI[params[0]][pJailTime] > 0)
		return SCM(playerid, COLOR_LIGHTGREY,!"Этот игрок уже в КПЗ!");

    if(PI[params[0]][pDemorgan] > 0)
		return SCM(playerid, COLOR_LIGHTGREY,!"Этот игрок уже в ДеМоргане!");

    if(time == 0) 
		return SCM(playerid, COLOR_LIGHTGREY, !"Нельзя посадить на 0 минут");

    if(time> 900) 
		return SCM(playerid, COLOR_LIGHTGREY, !"Нельзя посадить больше чем на 900 минут");

    if(PI[params[0]][pDemorgan] > 0 && PI[playerid][pAdmin] < 4) return SCM(playerid, COLOR_LIGHTGREY, !"Ваш уровень не дает возможность менять время отсидки этого игрока.");
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	SetSpawnInfoEx(params[0], GetSkinOfPlayer(playerid), -1764.1515, -2889.2085, 14.3141, 240.8832);

	SCMF(playerid, COLOR_TOMATO, "Вы посадили в тюрьму игрока %s на %d минут. Причина: %s",\
		PN(params[0]), time, params[1]);
	
	SCMF(params[0], COLOR_TOMATO, "%s посадил Вас в тюрьму на %d минут. Причина: %s",\
		PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор", time, params[1]);

	new punishmentID = CreatePunishment(params[0], playerid, 1, time, params[1]);

	SCMF(params[0], COLOR_LIGHTGREY, "Номер наказания: {00912D}#%d{CCCCCC} (для обжалования на {F87031}forum.m-bonus.com{CCCCCC})", punishmentID);
	
	SCM(params[0], COLOR_LIGHTGREY, !"Время до выхода из тюрьмы отображается в правом верхнем углу");
	
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] посадил игрока %s в тюрьму на %d минут. Причина: %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid),playerid, PN(params[0]), time,params[1]);
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	_ResetPlayerWeapons(params[0]);
	PI[params[0]][pDemorgan] = time*60;
	PI[params[0]][pWanted] = 0;
	PI[params[0]][pHospital] = 0;
	UpdatePlayerHealth(params[0], 100);
	PlayerSpawn(params[0]);

	cef_emit_event(params[0], "show-notifications:hud", CEFINT(101), CEFSTR("red-time"), CEFSTR("Заключение"), CEFINT(PI[params[0]][pDemorgan]));

	return 1;
}
cmd:setsex(playerid, params[])
{
    if(!CheckAccess(playerid, 6)) 
        return false;

	if sscanf(params, "u", params[0]) *then  
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /setsex [ID игрока]");

	switch(PI[params[0]][pSex])
	{
		case 1:
		{
			SCMF(playerid, -1, "Вы изменили пол игроку %s на женский", PN(params[0]));
			SCM(params[0], -1, !"Игровой мастер изменил ваш пол на женский");
			PI[params[0]][pSex] = 2;
		}
		case 2:
		{
			SCMF(playerid, -1, "Вы изменили пол игроку %s на мужской", PN(params[0]));
			SCM(params[0], -1, !"Игровой мастер изменил ваш пол на мужской");
			PI[params[0]][pSex] = 1;
		}
	}
	return 1;
}
cmd:unbanip(playerid, data[])
{
	if(!CheckAccess(playerid, 7)) 
        return false;

	extract data -> new string:ip[16]; else
		return SCM(playerid, COLOR_LIGHTGREY, !"Используй: /unbanip [ip]");

	SQL("DELETE FROM `banip` WHERE `IP` = '%s'", ip);

	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s разблокировал IP %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), ip);
	return 1;
}
cmd:banip(playerid, params[])
{
	if(!CheckAccess(playerid, 7)) 
        return false;

    new id, reason[30];
    if sscanf(params, "us[30]", id, reason) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используй: /banip [id] [Причина]");

	if id == INVALID_PLAYER_ID *then 
		return 0;

	PI[id][pWarns] = 0;
    BanIP(PlayerIP(id));
    BanName(PN(id), PN(playerid), 666, reason);
    PrepareKickCamera(id);

	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s заблокировал IP адрес игрока %s [%s]. Причина: %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), PN(id), PlayerIP(id), reason);
	return 1;
}
CMD:msg(playerid, params[]) 
{
    if(!CheckAccess(playerid, 5)) 
        return false;

	if sscanf(params,"s[144]",params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /msg [текст]");

    return SCMALLF(COLOR_BLACKRED, "Игровой мастер: %s", params[0]);
}

CMD:getcar(playerid, params[])
{
    if(!CheckAccess(playerid, 3, 3)) 
        return false;

	if sscanf(params, "i", params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /getcar [Car ID]");

	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	SetVehiclePos(params[0], x+2, y+2, z);
	return 1;
}

CMD:atw(playerid, params[])
{
	if(!CheckAccess(playerid, 4)) 
        return false;

    new Float:id,Float:x,Float:y,Float:z;
    if sscanf(params,"f",id) *then 
		 return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /ahp [радиус]");
    if id<1 || id > 100 *then 
	 	return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /ahp [радиус > 0 или < 100]");

	new num;
    foreach(new i: Player)
    {
        if(IsPlayerLogged{i})
        {
	        GetPlayerPos(playerid,x,y,z);
	        if(IsPlayerInRangeOfPoint(i,id,x,y,z))
	        {
				SCM(i, -1, !"Игровой мастер изъял Ваше оружие");
	            ResetPlayerWeapons(i);
	            num++;
	        }
		}
    }
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s изъял оружие у %d игрока(-ов)", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), num);
	return 1;
}
cmd:ahp(playerid, params[])
{
	if(!CheckAccess(playerid, 4)) 
        return false;

    new Float:id,Float:x,Float:y,Float:z;
    if sscanf(params,"f",id) *then 
		 return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /ahp [радиус]");
    if id<1 || id > 100 *then 
	 	return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /ahp [радиус > 0 или < 100]");

    new num;
    foreach(new i: Player)
    {
        if(IsPlayerLogged{i})
        {
	        GetPlayerPos(playerid,x,y,z);
	        if(IsPlayerInRangeOfPoint(i,id,x,y,z))
	        {
				SCM(i, -1, !"Игровой мастер изменил Вам здоровье");
	            UpdatePlayerHealth(i,100);
	            num++;
	        }
		}
    }
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s выдал здоровье у %d игрока(-ов)", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), num);
    return 1;
}

cmd:resgun(playerid, params[]) 
{
    if(!CheckAccess(playerid, 3, 3)) 
        return false;

    if sscanf(params,"u",params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /resgun [ID игрока]");

	if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Игрок не в сети");

	_ResetPlayerWeapons(params[0]);

	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s забрал оружие у %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), PN(params[0]));
	SCMF(params[0], -1, "%s забрал у Вас оружие", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
    return 1;
}

cmd:aclear(playerid, params[]) 
{
    if(!CheckAccess(playerid, 3, 3)) 
        return false;

	if sscanf(params, "u", params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /aclear [ID игрока]");

    if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Игрок не в сети");

    if PI[params[0]][pWanted] == 0 *then 
		return SCM(playerid, COLOR_GREY, !"У игрока нет розыска");

	PI[params[0]][pWanted] = 0;
	SetPlayerWantedLevel(params[0],PI[params[0]][pWanted]);
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s обнулил розыск %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), PN(params[0]));
	SCMF(params[0], -1, "%s обнулил Вам розыск", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
	return 1;
}

cmd:gun(playerid, params[])
{
	if(!CheckAccess(playerid, 3, 3)) 
        return false;

	if sscanf(params, "udd", params[0], params[1], params[2]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /gun [ID игрока] [оружие] [патроны]");

	if(params[0] == INVALID_PLAYER_ID)
	    return 0;

    if(params[1] == 35 || params[1] == 36 || params[1] == 37 || params[1] == 38 || params[1] == 39 || params[1] == 40) return SCM(playerid, COLOR_GREY, !"Это оружие запрещен разработчиками сервера");
	_GiveGun(params[0], params[1], params[2]);

	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] выдал %s[%d] %s[%d] (%d пт)", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[0], WeaponNames[params[1]], params[1], params[2]);
	SCMF(params[0], -1, "%s выдал Вам %s (+%d пт)", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор", WeaponNames[params[1]], params[2]);
	return 1;
}

cmd:setfuel(playerid,params[]) 
{
    if(!CheckAccess(playerid, 3, 3)) 
        return false;

	new Float:dd;
    if sscanf(params, "f", dd) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /setfuel [кол-во]");

    if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER) 
	{
		new VehId = GetPlayerVehicleID(playerid);
		VehicleInfo[VehId][vFuel] = dd;
		SCM(playerid, -1, !"Уровень топлива в автомобиле изменен");
	}
	else SCM(playerid, COLOR_LIGHTGREY, !"Нужно находиться на водительском месте");
	return 1;
}
cmd:spawncar(playerid) 
{
    if(!CheckAccess(playerid, 3, 3)) 
        return false;

	new VehId = GetPlayerVehicleID(playerid);

	if GetPlayerState(playerid) != PLAYER_STATE_DRIVER *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Нужно находиться за рулем транспорта");

	SetVehicleToRespawn(VehId);
	return SCM(playerid, -1, !"Автомобиль был заспавнен");
}
cmd:cc(playerid)
{
	if(!CheckAccess(playerid, 3, 3)) 
        return false;
		
    for(new i; i < 20; i++)
		SCMALL(-1, !" ");

    SCMALL(-1, !"Игровой мастер очистил чат");
	return 1;
}

cmd:skick(playerid,params[]) 
{
    if(!CheckAccess(playerid, 3, 3)) 
        return false;

	if sscanf(params,"us[32]",params[0],params[1]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /skick [ID игрока] [причина]");
		
	if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Игрок не в сети");

	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] тихо кикнул игрока %s. Причина: %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[1]);
	return PrepareKickCamera(params[0]);
}

cmd:kick(playerid,params[]) 
{
    if(!CheckAccess(playerid, 3, 3)) 
        return false;

	if sscanf(params,"us[32]",params[0],params[1]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /kick [ID игрока] [причина]");
		
	if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Игрок не в сети");

	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] кикнул игрока %s. Причина: %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[1]);
	SCMF(params[0], COLOR_TOMATO, "%s кикнул Вас. Причина: %d", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор", params[1]);
	return PrepareKickCamera(params[0]);
}

cmd:as(playerid)
{
    if PI[playerid][pAdmin] < 1 *then
        return 0;

	if !ALogin{playerid} *then return 
		SPD(playerid, dALogin, DIALOG_STYLE_PASSWORD, !"{EE3366}Авторизация", !"{FFFFFF}Для получения доступа к правам {EE3366}игрового мастера{FFFFFF}\n необходимо подтвердить личность, введя пароль.", !"Далее", !"Отмена");

	f(global_str, 1000, "\
		1. Оповещения анти-чита\t%s\n\
		2. Вывод списка смертей\t%s\n\
		3. Входы / выходы ИМ\t%s\n\
		4. Входы / выходы игроков\t%s\n\
		5. Скорость полёта (/fly)\t%d\n\
		6. Изменить никнейм\t\tВручную\n\
		7. Скрыть ник\t\t\t%s\n\
		8. Отображение репорта\t%s\n\
		9. IP адреса в сообщениях\t%s\n\
		10. Телепорт к себе\t%s\n\
		11. Телепорт себя к ИМ\t%s",\
		AInfo[playerid][admACMsg] ? ("{4eaa77}Все{FFFFFF}") : ("{ce6c4f}Выключены{FFFFFF}"),\
		AInfo[playerid][admKillList] ? ("{4eaa77}Включен{FFFFFF}") : ("{ce6c4f}Выключен{FFFFFF}"),\
		AInfo[playerid][admJoin] ? ("{4eaa77}Включены{FFFFFF}") : ("{ce6c4f}Выключены{FFFFFF}"),\
		AInfo[playerid][admInfoNewPlayer] ? ("{4eaa77}Включены{FFFFFF}") : ("{ce6c4f}Выключены{FFFFFF}"),\
		AInfo[playerid][admFlySpeed],\
		AInfo[playerid][admHide] ? ("{4eaa77}Включено{FFFFFF}") : ("{ce6c4f}Выключено{FFFFFF}"),\
		AInfo[playerid][admShowReport] ? ("{4eaa77}Включено{FFFFFF}") : ("{ce6c4f}Выключено{FFFFFF}"),\
		AInfo[playerid][admIP] ? ("{4eaa77}Включены{FFFFFF}") : ("{ce6c4f}Выключены{FFFFFF}"),\
		AInfo[playerid][admGoto] ? ("{4eaa77}Включен{FFFFFF}") : ("{ce6c4f}Выключен{FFFFFF}"),\
		AInfo[playerid][admGethere] ? ("{4eaa77}Включен{FFFFFF}") : ("{ce6c4f}Выключен{FFFFFF}"));
	
	SPD(playerid, dAdminPanel, DIALOG_STYLE_LIST, !"{EE3366}Настройки игрового мастера", global_str, !"Изменить", !"Назад");
    return 1;
}

cmd:makegm(playerid, params[]) 
{
    if(!CheckAccess(playerid, 8)) 
        return false;

    if sscanf(params,"u",params[0]) *then 
        return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /makegm [ID игрока]");

	if params[0] == INVALID_PLAYER_ID *then return 0;

    if params[0] == playerid *then return 0;

	if !IsPlayerLogged{params[0]} *then return SCM(playerid, COLOR_LIGHTGREY, !"Игрок не авторизован");

    pTemp[playerid][targetID] = params[0];

	return SPD(playerid, dMakeGameMaster, DIALOG_STYLE_LIST, !"{EE3366}Выдача прав игрового мастера", !"Снять права игрового мастера\n1. NGM\n2. JRGM\n3. GM\n4. GM+\n5. LGM\n6. SGM\n7. SGM+\n8. DEV", !"Далее", !"Отмена");
}

cmd:freeze(playerid, params[])
{
	if(!CheckAccess(playerid, 1, 1)) 
        return false;

	if sscanf(params, "u", params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используй: /freeze [ID игрока]");

	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] заморозил игрока %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]));
	TogglePlayerControllable(params[0], false);
	return 1;
}

cmd:setarm(playerid, params[]) 
{
    if(!CheckAccess(playerid, 2, 3)) 
        return false;

	if sscanf(params, "ud", params[0], params[1]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /setarm [ID игрока] [кол-во]");

	if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Игрок не в сети");

	SetPlayerArmourEx(params[0], params[1]);
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] изменил броню %s[%d] на %d.0", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[0], params[1]);
	SCMF(params[0], -1, "%s мастер выдал Вам бронижелет",  PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
	return 1;
}

cmd:gethere(playerid, params[])
{
	if(!CheckAccess(playerid, 2, 2)) 
        return false;

	new id, Float:X, Float:Z, Float:Y, Float:A;

    if sscanf(params,"u",id) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используй: /gethere [id]");
		
    if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Игрок не в сети");

	if AInfo[id][admGethere] *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Данный администратор запретил телепортировать его к себе");

    GetPlayerPos(playerid,X,Y,Z);
    GetPlayerFacingAngle(playerid, A);
    ShiftCords(0, X, Y, A, 3.0);

    SetPlayerVirtualWorld(id,GetPlayerVirtualWorld(playerid)), SetPlayerInteriorEx(id,GetPlayerInterior(playerid));

    if(GetPlayerState(id) != 2) UpdatePlayerPos(id, X, Y, Z);
    else SetVehiclePos(GetPlayerVehicleID(id), X, Y, Z);
    
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] телепортировал к себе %s[%d]", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid),playerid, PN(params[0]), params[0]);
	SCMF(params[0], COLOR_LIGHTGREY, "Вы были телепортированы %s",  PI[playerid][pAdmin] ? "игровым мастером" : "игровым модератором");
    return SCMF(playerid, -1, "Вы телепортировали к себе игрока %s", PN(id));
}

cmd:unfreeze(playerid, params[])
{
	if(!CheckAccess(playerid, 1, 1)) 
        return false;

	if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Игрок не в сети");

	if sscanf(params, "u", params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используй: /unfreeze [ID игрока]");

	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] разморозил игрока %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]));
	TogglePlayerControllable(params[0], true);
	return 1;
}

cmd:flip(playerid, params[]) 
{
    if(!CheckAccess(playerid, 1, 1)) 
        return false;

	if sscanf(params, "d", params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /flip [ID игрока]");

	if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Игрок не в сети");

	if !IsPlayerInAnyVehicle(params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Игрок не в машине");

	new car = GetPlayerVehicleID(params[0]), Float:X, Float:Y, Float:Z, Float:A;
    GetVehiclePos(car, X, Y,Z);
    GetVehicleZAngle(car, A);
    SetVehiclePos(car, X, Y, Z+1.0);
    SetVehicleZAngle(car, A);
    RepairVehicle(car);

	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] перевернул транспорт ID %d", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, car);
	return SCMF(params[0], -1, "%s починил Вам транспорт", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
}

cmd:ask(playerid,params[]) 
{
    if(!CheckAccess(playerid, 1, 1)) 
        return false;
	if sscanf(params,"us[90]", params[0], params[1])  *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /ans [ID игрока] [текст]");

	if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Игрок не в сети");

	if params[0] == playerid *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Вы не можете ответить самому себе");

    SCMF(params[0], COLOR_ANS, "%s ответил Вам: {FFFFFF}%s", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор", params[1]);
	SAMF(COLOR_ANS, "[%s #%d] %s[%d] > %s[%d]:{FFFFFF} %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[0], params[1]);
    return 1;
}

cmd:a(playerid, params[])
{
    if(!CheckAccess(playerid, 1, 1)) 
        return false;

    if sscanf(params, "s[150]", params[0]) *then
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /a [текст]");

    return SAMF(COLOR_BLUE, "[%s #%d] %s[%d]: %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, params[0]);
}

cmd:slap(playerid, params[])
{
	if(!CheckAccess(playerid, 2, 1)) 
		return false;

	if sscanf(params,"u", params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /slap [ID игрока]");

	if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_GREY, !"Игрок не в сети");

	new Float:X,Float:Y,Float:Z;
	GetPlayerPos(params[0],X,Y,Z), SetPlayerPosEx(params[0],X,Y,Z+3);
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] подбросил игрока %s[%d]", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[0]);
	return SCMF(params[0], -1, "%s подкинул Вас", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
}

cmd:spawn(playerid, params[]) 
{
    if(!CheckAccess(playerid, 1, 1)) 
		return false;

    if sscanf(params,"u",params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /spawn [ID игрока]");

    if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_GREY, !"Игрок не в сети");

	PlayerSpawn(params[0]);

	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] заспавнил игрока %s[%d]", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[0]);
	return SCMF(params[0], -1, "%s заспавнил Вас", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
}

cmd:vw(playerid, params[]) 
{
    if(!CheckAccess(playerid, 2, 2)) 
		return false;

	if sscanf(params, "d", params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /vw [ID виртуального мира] (0 - стандартный)");

	if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_GREY, !"Игрок не в сети");

	if params[0] > 100 || params[0] < 0 *then 
		return SCM(playerid, COLOR_GREY, !"ID виртуального мира должен быть в пределах от 0 до 100.");

	SetPlayerVirtualWorld(playerid, params[0]);
	return SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] перешёл в виртуальный мир №%d", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, params[0]);
}

cmd:veh(playerid, params[]) 
{
    if(!CheckAccess(playerid, 3, 3)) 
		return false;

    if sscanf(params, "dddd", params[0], params[1], params[2], params[3]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /veh [ID игрока] [ID машины] [цвет] [цвет]");

    if params[1] < 400 || params[1] > 611 && params[0] *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Номер Транспортного средства не может быть ниже 400 или выше 611 !");

	if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_GREY, !"Игрок не в сети");

    new Float:pos[3]; GetPlayerPos(params[0], pos[0], pos[1], pos[2]);
    new VehID = CreateVehicle(params[1], pos[0], pos[1], pos[2], 0, params[2], params[3], -1);

    SetVehicleVirtualWorld(VehID, GetPlayerVirtualWorld(playerid));
	PutPlayerInVehicle(params[0], VehID, 0);

    ClearCarData(VehID);

    VehicleInfo[VehID][vFuel] = 100.0;
    VehicleInfo[VehID][vAdminCar] = 1;

	new VehModel = GetVehicleModel(VehID);
    SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] создал %s[%d] (id: %d, цвет: %d, %d)", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, Vehicle_Names[VehModel-400], VehID, params[1], params[2], params[3]);
	return 1;
}

cmd:dveh(playerid) 
{
    if(!CheckAccess(playerid, 3, 3)) 
		return false;

    if !IsPlayerInAnyVehicle(playerid) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Нужно находиться в транспорте");

    new CarID = GetPlayerVehicleID(playerid);
	
	if VehicleInfo[CarID][vAdminCar] == 0 *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Данный транспорт нельзя удалить");
	
	ClearCarData(CarID);
	DestroyVehicle(CarID);
    return 1;
}

cmd:skin(playerid, params[]) 
{
    if(!CheckAccess(playerid, 3, 3)) 
		return false;

	if(sscanf(params,"udd", params[0], params[1], params[2])) 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /skin [ID игрока] [номер скина] [0/1]");

	if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_GREY, !"Игрок не в сети");

	if(PI[playerid][pAdmin] < 6 && params[1] > 311) 
		return false;

	if(params[2] < 0 || params[2] > 1) return 0;
	
	if(params[2] == 1)
	{
		PI[params[0]][pSkin] = params[1];

		SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] выдал %s[%d] вечный скин ID %d", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[0], params[1]);
		SCMF(params[0], -1, "%s Игровой мастер выдал Вам вечный скин.", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
	}
	else
	{
		SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] выдал %s[%d] временный скин ID %d", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[0], params[1]);
		SCMF(params[0], -1, "%s выдал Вам временный скин.", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
	}
	SetPlayerSkinEx(params[0], params[1]);
    return 1;
}

cmd:goto(playerid, params[])
{
	if(!CheckAccess(playerid, 2, 3)) 
		return false;

	extract params -> new player:target; else
		return SCM(playerid, COLOR_LIGHTGREY, !"Используй: /goto [id]");

	if(target == INVALID_PLAYER_ID)
	    return 1;

	if(PI[target][pAdmin] && AInfo[target][admGoto])
		return SCM(playerid, COLOR_LIGHTGREY, !"Данный игровой мастер запретил к себе телепорт");

	new Float:X, Float:Z, Float:Y;
    GetPlayerPos(target, X, Y, Z);
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(target)), SetPlayerInteriorEx(playerid, GetPlayerInterior(target));
    if(GetPlayerState(playerid) != 2) UpdatePlayerPos(playerid, X+2, Y+2, Z);
    else SetVehiclePos(GetPlayerVehicleID(playerid), X+2, Y+2, Z);

	return SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] телепортировался к игроку %s[%d]", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[0]);
}

cmd:tpcor(playerid, data[])
{
	if(!CheckAccess(playerid, 1, 2)) 
		return false;

	extract data -> new Float:x, Float:y, Float:z; else 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /tpcor [X] [Y] [Z]");
	
	return UpdatePlayerPos(playerid, x, y, z);
}

cmd:admins(playerid)
{
 	if(!CheckAccess(playerid, 1, 1)) 
        return false;

	SCMF(playerid, COLOR_BLUE, "Игровые мастера онлайн (в сети: %d, из них в АФК: NaN)", Iter_Count(Admin));

	foreach(Admin, i)
	{
		if !PI[i][pAdmin] *then continue;

		f(global_str, 90, "[%s #%d] - %s[%d]", StaffTag(playerid), PI[i][pAdminNumber], PN(i), i);
		SCM(playerid, COLOR_JOBYELLOW, global_str);
	}
	return 1;
}

cmd:ahelp(playerid)
{
	if(!CheckAccess(playerid, 1)) 
        return false;

	global_str = "";

	for new i = 1; i < 9; i++ do
		strcat(global_str, (str_f("\n{FFFFFF}%d.{%s} %s", i, PI[playerid][pAdmin] >= i ? "FFFFFF":"AFAFAF", Admin_Names[i])));
    
	return SPD(playerid, dAdminCMD, DIALOG_STYLE_LIST, !"{EE3366}Команды игрового мастера", global_str, !"Выбрать", !"Отмена");
}

stock GetMaxAmountAHelp(level)
{
	new count;

	for new i; i < sizeof AdminCommandList; i++ do {

		if !(AdminCommandList[i][adminLevel] == level) *then 
			continue;
	
		count ++;
	}

	return floatround(float(count) / 35, floatround_ceil);
}

stock print_AdminCommand(playerid, level, page = 0)
{
	spdList(playerid, 1, page);

	global_str = "{FFFFFF}";

	new count;

	for new i; i < sizeof AdminCommandList; i++ do {

		if !(AdminCommandList[i][adminLevel] == level) *then 
			continue;
		
		count ++;

		if 35 * page < count <= 35 * (page + 1) *then
			strcat(global_str, (str_f("%s — %s\n", AdminCommandList[i][adminCommand], AdminCommandList[i][adminCommandInfo])));
	}

	return SPD(playerid, dAdminCMDList, DIALOG_STYLE_MSGBOX, (str_f("{EE3366}%s [%d/%d]", Admin_Names[level], page + 1, GetMaxAmountAHelp(level))), global_str, !"Далее", !"Назад");
}

stock StaffTag(playerid)
{

    if PI[playerid][pAdmin] *then return Admin_Names[PI[playerid][pAdmin]];
    else if PI[playerid][pModer] *then return Moder_Names[PI[playerid][pModer]];
    
    return Admin_Names[0]; // "None"
}

stock admin_OnDialogResponse(playerid, dialogid, response, listitem, inputtextsave[])
{
    switch dialogid do
    {
		case dAdminPanel:
		{
			if(!response) return callcmd::menu(playerid);
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						AInfo[playerid][admACMsg] = !AInfo[playerid][admACMsg];
						callcmd::as(playerid);
					}
					case 1:
					{
						AInfo[playerid][admKillList] = !AInfo[playerid][admKillList];
						callcmd::as(playerid);
					}
					case 2:
					{
						AInfo[playerid][admJoin] = !AInfo[playerid][admJoin];
						callcmd::as(playerid);
					}
					case 3:
					{
						AInfo[playerid][admInfoNewPlayer] = !AInfo[playerid][admInfoNewPlayer];
						callcmd::as(playerid);
					}
					case 4:
					{
						SPD(playerid, dAdminFlySpeed, DIALOG_STYLE_INPUT, !"{EE3366}Изменить скорость полёта", !"{FFFFFF}Введите желаемую скорость от 50 до 300:", !"Изменить", !"Назад");
					}
					case 5: return 1;
					case 6:
					{
						AInfo[playerid][admHide] = !AInfo[playerid][admHide];

						if !AInfo[playerid][admHide] *then
						{
							SCM(playerid, COLOR_HINT, !"[AS]: {FFFFFF}скрытие никнейма выключено");
							UpdatePlayerHealth(playerid, 100.0);

							foreach(new i: Player)
							{
								if(IsPlayerLogged{i})
									ShowPlayerNameTagForPlayer(i, playerid, true);
							}
						}
						else 
						{
							SCM(playerid, COLOR_HINT, !"[AS]: {FFFFFF} скрытие никнейма включено");
							UpdatePlayerHealth(playerid, 176.0);

							foreach(new i: Player)
							{
								if(IsPlayerLogged{i})
									ShowPlayerNameTagForPlayer(i, playerid, false);
							}
						}
						callcmd::as(playerid);
					}
					case 7:
					{	
						AInfo[playerid][admShowReport] = !AInfo[playerid][admShowReport];
						callcmd::as(playerid);
					}
					case 8:
					{	
						AInfo[playerid][admIP] = !AInfo[playerid][admIP];
						callcmd::as(playerid);
					}
					case 9:
					{	
						AInfo[playerid][admGoto] = !AInfo[playerid][admGoto];
						callcmd::as(playerid);
					}
					case 10:
					{	
						AInfo[playerid][admGethere] = !AInfo[playerid][admGethere];
						callcmd::as(playerid);
					}
				}
				SaveAdminSettings(playerid);
			}
		}
		case dAdminFlySpeed:
		{
			if(!response) return callcmd::as(playerid);
			if(response)
			{
				new Speed = strval(inputtextsave);

				if Speed > 300 || Speed < 50 *then return SPD(playerid, dAdminFlySpeed, DIALOG_STYLE_INPUT, !"{EE3366}Изменить скорость полёта", !"{FFFFFF}Введите желаемую скорость от 50 до 300:", !"Изменить", !"Назад");
				
				AInfo[playerid][admFlySpeed] = Speed;

				callcmd::as(playerid);
			}
		}
		case dEventSettings:
		{
			if(!response) return 1;
			if(response)
			{
				switch(listitem)
				{
					case 0:
					{
						GetPlayerPos(playerid, eSettings[TeleportX], eSettings[TeleportY], eSettings[TeleportZ]);
						eSettings[TeleportInt] = GetPlayerInterior(playerid);
						eSettings[TeleportVW] = GetPlayerVirtualWorld(playerid);


						SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] изменил место для телепорта на мероприятие", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid);

						callcmd::editmp(playerid);
					}
					case 1:
					{
						eSettings[TeleportEnable] = !eSettings[TeleportEnable];

						SAMF(COLOR_ADMINCHAT, "[%s #%d] %s телепорт на мероприятие", StaffTag(playerid), PI[playerid][pAdminNumber], eSettings[TeleportEnable] ? ("включил") : ("выключил"));

						callcmd::editmp(playerid);
					}
					case 2:
					{
						eSettings[IsEventStart] = false;
						eSettings[TeleportEnable] = false;

						foreach(new i: Event)
						{
							pTemp[i][pOnEvent] = 0;
							SetPlayerPosEx(i, pTemp[i][pOldX], pTemp[i][pOldY], pTemp[i][pOldZ] + 1.5);
							SetPlayerInterior(i, 0);
							SetPlayerVirtualWorld(i, 0);

							SCM(i, COLOR_BLACKRED, !"Игровой мастер завершил мероприятие");
						}

						SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] завершил мероприятие", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid);

						Iter_Free(Event);
					}
				}
			}
		}
        case dALogin: 
		{
			if !response *then
		    	return 1;

			if !strlen(inputtextsave) *then
			    	return SPD(playerid, dALogin, DIALOG_STYLE_PASSWORD, !"{EE3366}Авторизация", !"{FFFFFF}Для получения доступа к правам {EE3366}игрового мастера{FFFFFF}\n необходимо подтвердить личность, введя пароль.", !"Далее", !"Отмена");

			mysql_format(mysql, global_str, 150, "SELECT * FROM accounts WHERE NickName = '%s' LIMIT 1", PN(playerid));
			mysql_tquery(mysql, global_str, "AloginAuth", "id", playerid, strval(inputtextsave));
		}
        case dMakeGameMaster:
        {
            if(!response) return pTemp[playerid][targetID] = INVALID_PLAYER_ID;
            if(response) 
			{
                PI[pTemp[playerid][targetID]][pAdmin] = listitem;

                if listitem == 0 *then
                { 
					SCM(playerid, COLOR_YELLOW, !"Вы были сняты с поста игрового мастера!");
                    SCMF(pTemp[playerid][targetID], COLOR_YELLOW, "Игровой мастер %s снял Вас с должности игрового мастера", PN(playerid));

					if Iter_Contains(Admin, pTemp[playerid][targetID]) *then Iter_Remove(Admin, pTemp[playerid][targetID]);
                }
                else 
                {
					SCMF(playerid, COLOR_YELLOW, "Вы изменили уровень игрового мастера для %s[%d], теперь он '%s'", Admin_Names[listitem - 1], PN(pTemp[playerid][targetID]), pTemp[playerid][targetID]);
                    SCM(pTemp[playerid][targetID], COLOR_YELLOW, "Игровой мастер изменил ваш уровень до %s");
                    callcmd::as(pTemp[playerid][targetID]);
                }
                ALogin{pTemp[playerid][targetID]} = false;
                UpdatePlayerDataInt(pTemp[playerid][targetID], "Admin", PI[pTemp[playerid][targetID]][pAdmin]);

                return pTemp[playerid][targetID] = INVALID_PLAYER_ID;
            }
        }
		case dMakeGameModer:
        {
            if(!response) return pTemp[playerid][targetID] = INVALID_PLAYER_ID;
            if(response) 
			{
                PI[pTemp[playerid][targetID]][pModer] = listitem;

                if listitem == 0 *then
                { 
					SCM(playerid, COLOR_YELLOW, !"Вы были сняты с поста игрового модератора!");
                    SCMF(pTemp[playerid][targetID], COLOR_YELLOW, "Игровой мастер %s снял Вас с должности игрового модератора", PN(playerid));

					if Iter_Contains(Moder, pTemp[playerid][targetID]) *then Iter_Remove(Moder, pTemp[playerid][targetID]);
                }
                else 
                {
					SCMF(playerid, COLOR_YELLOW, "Вы изменили уровень игрового модератора для %s[%d], теперь он '%s'", Moder_Names[listitem - 1], PN(pTemp[playerid][targetID]), pTemp[playerid][targetID]);
                    SCMF(pTemp[playerid][targetID], COLOR_YELLOW, "Игровой мастер изменил ваш уровень до %s", Moder_Names[listitem - 1]);
                    Iter_Add(Moder, playerid);
                }
                ALogin{pTemp[playerid][targetID]} = false;
                UpdatePlayerDataInt(pTemp[playerid][targetID], "Admin", PI[pTemp[playerid][targetID]][pModer]);

                return pTemp[playerid][targetID] = INVALID_PLAYER_ID;
            }
        }
        case dAdminCMD:
		{
			if !response *then
				return false;

			listitem++;
			spdList(playerid, 0, listitem);

			return print_AdminCommand(playerid, listitem);
		}

		case dAdminCMDList:
		{
			new level = gpdList(playerid, 0), page = gpdList(playerid, 1);

			if !response *then
			{
				if page *then
					return print_AdminCommand(playerid, level, page - 1);
				else
					return callcmd::ahelp(playerid);
			}

			if !(page + 1 == GetMaxAmountAHelp(level)) *then
				page ++;

			return print_AdminCommand(playerid, level, page);
		}

		case dModerCMD:
		{
			if !response *then
				return false;

			listitem++;
			spdList(playerid, 0, listitem);

			return print_ModerCommand(playerid, listitem);
		}

		case dModerCMDList:
		{
			new level = gpdList(playerid, 0), page = gpdList(playerid, 1);

			if !response *then
			{
				if page *then
					return print_ModerCommand(playerid, level, page - 1);
				else
					return callcmd::ahelp(playerid);
			}

			if !(page + 1 == GetMaxAmountMHelp(level)) *then
				page ++;

			return print_ModerCommand(playerid, level, page);
		}
    }
    return 1;
}

public: AloginAuth(playerid, password)
{
    if cache_get_row_count(mysql) > 0 *then
    {
        PI[playerid][pAdmin] = cache_get_row_int(0, 2);

        if password == AdminPassword[PI[playerid][pAdmin] - 1] *then
        {

            AInfo[playerid][admInterior] = -1;
            
			foreach(Admin, i) {
                if(PI[i][pAdmin] && ALogin{i} && AInfo[i][admJoin]) 
                    SCMF(i, COLOR_ADMINCHAT, "[%s #%d] %s[%d] вошел на сервер", Admin_Names[PI[playerid][pAdmin]], PI[playerid][pAdminNumber], PN(playerid), playerid);
            }

            SCMF(playerid, -1, "Вы успешно авторизовались как {EE3366}%s{FFFFFF}!", Admin_Names[PI[playerid][pAdmin]]);
        
            for new i; i < 53; i++ do EnableAntiCheatForPlayer(playerid, i, 0); 

            Iter_Add(Admin, playerid);
            ALogin{playerid} = true;

			callcmd::as(playerid);
        }
    }
    else 
    {
        SCM(playerid, -1, !"Вы ввели неверный пароль от {EE3366}админ-панели{FFFFFF}!");
        f(global_str, 128, "[%s #%d] %s[%d] ввел неверный пароль от админ-панели", Admin_Names[PI[playerid][pAdmin]], PI[playerid][pAdminNumber], PN(playerid), playerid);
        SendAdminsMessage(-1, global_str);
        return PrepareKickCamera(playerid);
    }
	return 1;
}

stock CheckAccess(playerid, adminLvl = 1, modLvl = 0)
{
    new bool:hasAdminAccess = false;
    new bool:hasModerAccess = false;

    if (adminLvl > 0 && PI[playerid][pAdmin] >= adminLvl)
    {
        if (!ALogin{playerid})
        {
            SCM(playerid, COLOR_LIGHTGREY, !"Вы не авторизованы как игровой мастер");
            return 0;
        }
        hasAdminAccess = true;
    }

    if (modLvl > 0 && PI[playerid][pModer] >= modLvl)
    {
        hasModerAccess = true;
    }

    if (hasAdminAccess || hasModerAccess)
    {
        return 1;
    }
	
    if (PI[playerid][pAdmin] || PI[playerid][pModer]) SCM(playerid, COLOR_LIGHTGREY, !"У вас нет доступа к этой команде");

    return 0;
}

stock BanIP(IP[])
{
    f(global_str, 100, "INSERT INTO `banip` (`IP`) VALUE ('%s')",IP);
	mysql_tquery(mysql, global_str);
	return 1;
}
stock BanName(const name[], const namez[], days, reason[])
{
	mysql_tquery(mysql, (str_f("SELECT * FROM bans WHERE BINARY `Name` = '%s' LIMIT 1;", name)), "@BanName", "ssds", name, namez, days, reason);

	return true;
}

public: @BanName(player_name[], ban_admin[], days, reason[])
{
	mysql_tquery(mysql, !cache_get_row_count() ? (str_f("INSERT INTO `bans` (`Name`, `GameMaster`, `BanSeconds`, `BanReason`) VALUE ('%s', '%s', '%d', '%s')", player_name, ban_admin, Global_Time+days*60*60*24, reason)):(str_f("UPDATE `bannames` SET `GameMaster` = '%s', `BanSeconds` = %d, `BanReason` = '%s' WHERE `Name` = BINARY('%s') LIMIT 1;", ban_admin, Global_Time+days*60*60*24, reason, player_name)));
	
    return true;
}

stock BanPlayerPC(const NickName[], const HWID[], const UUID[], const BanCode[])
{
	mysql_tquery(mysql, (str_f("SELECT * FROM banpc WHERE BINARY `NickName` = '%s' LIMIT 1;", NickName)), "@BanPlayerPC", "ssss", NickName, HWID, UUID, BanCode);

	return true;
}

public: @BanPlayerPC(NickName[], HWID[], UUID[], BanCode[])
{
	mysql_tquery(mysql, !cache_get_row_count() 
			? 
	(str_f("INSERT INTO `banpc` (`NickName`, `HWID`, `UUID`, `BanCode`, `Date`) VALUE ('%s', '%s', '%s', '%s', NOW())", NickName, HWID, UUID, BanCode))
			:
	(str_f("UPDATE `banpc` SET `HWID` = '%s', `UUID` = '%s' WHERE `NickName` = BINARY('%s') LIMIT 1;", HWID, UUID, NickName)));
	
    return true;
}

stock IsBannedName(name[])
{
	f(global_str, 200, "SELECT `Name` FROM `bans` WHERE BINARY `Name` = '%s' LIMIT 1", name);
	new Cache:result = mysql_query(mysql, global_str);
	new i = cache_get_row_count(mysql);
    cache_delete(result, mysql);
	return i;
}

stock UnBanName(name[])
{
	if(IsBannedName(name))
	{
        f(global_str, 150, "DELETE FROM `bans` WHERE BINARY `Name` = '%s'",name);
        mysql_tquery(mysql, global_str);
	}
	return 1;
}

stock IsBannedNamePC(name[])
{
	f(global_str, 200, "SELECT `NickName` FROM `banpc` WHERE BINARY `NickName` = '%s' LIMIT 1", name);
	new Cache:result = mysql_query(mysql, global_str);
	new i = cache_get_row_count(mysql);
    cache_delete(result, mysql);
	return i;
}

stock UnBanNamePC(name[])
{
	if(IsBannedNamePC(name))
	{
        f(global_str, 150, "DELETE FROM `banpc` WHERE BINARY `NickName` = '%s'",name);
        mysql_tquery(mysql, global_str);
	}
	return 1;
}

stock RemovePlayerWarn(playerid, slot)
{
    for (new i = slot; i < 2; i++)
    {
        PI[playerid][pWarnsTimers][i] = PI[playerid][pWarnsTimers][i + 1];
    }

    PI[playerid][pWarnsTimers][2] = 0;
    if (PI[playerid][pWarns] > 0) PI[playerid][pWarns]--;
}

stock ShowBanDialog(playerid, punishmentID, const reason[])
{
	new year, month, day, hour, minute, second;
	getdate(year, month, day);
	gettime(hour, minute, second);

	SCM(playerid, COLOR_TOMATO, "Ваш аккаунт заблокирован на 7 дн. Причина: 3 предупреждения");
	SCMF(playerid, COLOR_LIGHTGREY, "Номер наказания: {00912D}#%d{CCCCCC} (для обжалования на {F87031}forum.m-bonus.com{CCCCCC})", punishmentID);

	SPDF(playerid, 0, DIALOG_STYLE_MSGBOX, !"{EE3366}Блокировка аккаунта", !"Закрыть", !"", "\
	{FFFFFF}Никнейм:\t\t{3366CC}%s\n\
	{FFFFFF}ID аккаунта:\t\t{3366CC}%d\n\
	{FFFFFF}Номер наказания:\t{00912D}%d\n\
	{FFFFFF}Сервер:\t\tСервер #1\n\
	Дата:\t\t\t%02d.%02d.%04d\n\
	Время:\t\t\t%02d:%02d:%02d\n\
	Причина:\t\t%s\n\
	Количество дней:\t7 дн\n\n\
	{FFFF99}Советуем сделать скриншот (клавиша F8), чтобы иметь\n\
	возможность обжаловать бан на forum.m-bonus.com",
		PN(playerid), PI[playerid][pID], punishmentID,
		day, month, year,
		hour, minute, second,
		reason);
}

stock ShowSetStats(playerid)
{
	return SPD(playerid, 0, DIALOG_STYLE_MSGBOX, !"{EE3366}Параметры", 
	"Код #1 -> отвечает за деньги\n\
	Код #2 -> отвечает за LvL\n\
	Код #3 -> отвечает за Exp", 
	!"Закрыть", !"");
}