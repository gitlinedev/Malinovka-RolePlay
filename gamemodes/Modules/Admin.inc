enum AdminInfo
{
	admID,
    admGoto,
	admGethere,
	admSpectate,
	admInfoNewPlayer,
	admKillList,
	admIP,
	Float:admPos[3],
	admMember,
	admMemberRank,
	admWorld,
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
	ModLevel,
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
	{"ans", 1, 1, "Ответить игроку"},

	//level 2
	{"slap", 2, 1, "Подбросить игрока в воздух"},
	{"vw", 2, 2, "Перейти в виртуальный мир"},
	{"goto", 2, 3, "Телепортироваться к игроку"},
	{"gethere", 2, 2, "Телепортировать игрока к себе"},
	{"jail", 2, 3, "Посадить игрока в ДеМорган"},

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

	//level 4
	{"atw", 4, 0, "Забрать оружие у игроков в радиусе"},
	{"ahp", 4, 0, "Выдать ХП игрокам в радиусе"},

	//level 5
	{"msg", 5, 0, "Написать на весь сервер"},

	//level6
	{"setsex", 6, 0, "Изменить пол персонажа игроку"},

	//level7
	{"banip", 7, 0, "Заблокировать IP игрока"},
	{"unbanip", 7, 0, "Разблокировать IP игрока"},

    //level 8
    {"makegm", 8, 0, "Выдать права игрового мастера"}
};

new Iterator:Admin<MAX_PLAYERS>;
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
cmd:jail(playerid, params[])
{
	if(!CheckAccess(playerid, 2, 3)) 
        return false;

    new time;
    if(sscanf(params,"uds[100]",params[0],time,params[1])) return SCM(playerid, COLOR_LIGHTGREY, !"Используй: /jail [ID игрока] [время] [причина]");

	if !IsPlayerOnline(params[0]) *then return false;

    if(strlen(params[1]) > 30) 
		return SCM(playerid,COLOR_LIGHTGREY, !"Причина не может быть больше 30 символов");

    if(PI[params[0]][pJailTime] > 0)
		return SCM(playerid, COLOR_LIGHTGREY,!"Этот игрок уже в КПЗ!");

    if(PI[params[0]][pDemorgan] > 0)
		return SCM(playerid, COLOR_LIGHTGREY,!"Этот игрок уже в ДеМоргане!");

    if(time == 0) 
		return SCM(playerid, COLOR_LIGHTGREY, "Нельзя посадить на 0 минут");

    if(time> 900) 
		return SCM(playerid, COLOR_LIGHTGREY, "Нельзя посадить больше чем на 900 минут");

    if(PI[params[0]][pDemorgan]>0 && PI[playerid][pAdmin] < 4) return SCM(playerid, COLOR_LIGHTGREY, !"Ваш уровень не дает возможность менять время отсидки этого игрока.");
	//
	SetSpawnInfo(params[0], 255, 8, 100.000, 100.000, 100.000, 90.0, 6, 6, 6, 6, 6, 6);

	SCMF(playerid, COLOR_TOMATO, "Вы посадили в тюрьму игрока %s на %d минут. Причина: %s", PN(params[0]), time, params[1]);
	SCMF(params[0], COLOR_TOMATO, "%s посадил Вас в тюрьму на %d минут. Причина: %s", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор", time, params[1]);
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] посадил игрока %s в тюрьму на %d минут. Причина: %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid),playerid, PN(params[0]), time,params[1]);
	//
	_ResetPlayerWeapons(params[0]);
	PI[params[0]][pDemorgan] = time*60;
	PI[params[0]][pWanted] = 0;
	PI[params[0]][pHospital] = 0;
	UpdatePlayerHealth(params[0], 100);
	PlayerSpawn(params[0]);
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
    Kick(id);

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
		CarInfo[VehId][cFuel] = dd;
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
	return Kick(params[0]);
}

cmd:as(playerid)
{
    if PI[playerid][pAdmin] < 1 *then
        return 0;

	if !ALogin{playerid} *then return 
		SPD(playerid, 4, DIALOG_STYLE_PASSWORD, !"{EE3366}Авторизация", !"{FFFFFF}Для получения доступа к правам {EE3366}игрового мастера{FFFFFF}\n необходимо подтвердить личность, введя пароль.", !"Далее", !"Отмена");
    
    SCM(playerid, -1, !"В разработке!");
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

	return SPD(playerid, 5, DIALOG_STYLE_LIST, !"{EE3366}Выдача прав игрового мастера", !"Снять права игрового мастера\n1. NGM\n2. JRGM\n3. GM\n4. GM+\n5. LGM\n6. SGM\n7. SGM+\n8. DEV", !"Далее", !"Отмена");
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
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] изменил уровень брони игрока %s[%d] на %d.0", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[0], params[1]);
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

    SetPlayerVirtualWorld(id,GetPlayerVirtualWorld(playerid)), SetPlayerInterior(id,GetPlayerInterior(playerid));

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

	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] починил транспорт игрока %s[%d]", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[0]);
	return SCMF(params[0], -1, "%s починил Вам транспорт", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
}

cmd:ans(playerid,params[]) 
{
    if(!CheckAccess(playerid, 1, 1)) 
        return false;
	if sscanf(params,"us[90]", params[0], params[1])  *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /ans [ID игрока] [текст]");

	if !IsPlayerOnline(params[0]) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Игрок не в сети");

	if params[0] == playerid *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Вы не можете ответить самому себе");

    SCMF(params[0], 0x906868FF, "%s ответил Вам: {FFFFFF}%s", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор", params[1]);
	SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] написал игроку %s[%d]:{FFFFFF} %s", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[0], params[1]);
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
	GetPlayerPos(params[0],X,Y,Z), SetPlayerPos(params[0],X,Y,Z+3);
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
    CarInfo[VehID][cFuel] = 100.0;
    CarInfo[VehID][cCreate] = 1;

	new VehModel = GetVehicleModel(VehID);
    SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] создал %s[%d] (id: %d, цвет: %d, %d)", StaffTag(playerid), PI[playerid][pAdminNumber], PI[playerid][pAdminNumber], PN(playerid), playerid, Vehicle_Names[VehModel-400], VehID, params[1], params[2], params[3]);
	return 1;
}

cmd:dveh(playerid) 
{
    if(!CheckAccess(playerid, 3, 3)) 
		return false;

    if !IsPlayerInAnyVehicle(playerid) *then 
		return SCM(playerid, COLOR_LIGHTGREY, !"Нужно находиться в транспорте");

    new CarID = GetPlayerVehicleID(playerid);
	
	if CarInfo[CarID][cCreate] == 0 *then 
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

	if(params[1] > 300) 
		return false;

	if(params[2] < 0 || params[2] > 1) return 0;
	
	if(params[2] == 1)
	{
		PI[params[0]][pSkin] = params[1];

		SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] выдал вечный скин игроку %s[%d] (ID %d)", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[0], params[1]);
		SCMF(params[0], -1, "%s Игровой мастер выдал Вам вечный скин.", PI[playerid][pAdmin] ? "Игровой мастер" : "Игровой модератор");
	}
	else
	{
		SAMF(COLOR_ADMINCHAT, "[%s #%d] %s[%d] выдал временный скин игроку %s[%d] (ID %d)", StaffTag(playerid), PI[playerid][pAdminNumber], PN(playerid), playerid, PN(params[0]), params[0], params[1]);
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
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(target)), SetPlayerInterior(playerid, GetPlayerInterior(target));
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
    
	return SPD(playerid, 6, DIALOG_STYLE_LIST, !"{EE3366}Команды администратора", global_str, !"Выбрать", !"Отмена");
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

	return SPD(playerid, 7, DIALOG_STYLE_MSGBOX, (str_f("{EE3366}%s [%d/%d]", Admin_Names[level], page + 1, GetMaxAmountAHelp(level))), global_str, !"Далее", !"Назад");
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
        case 4: 
		{
			if !response *then
		    	return 1;

			if !strlen(inputtextsave) *then
			    	return SPD(playerid, 5, DIALOG_STYLE_PASSWORD, !"{EE3366}Авторизация", !"{FFFFFF}Для получения доступа к правам {EE3366}игрового мастера{FFFFFF}\n необходимо подтвердить личность, введя пароль.", !"Далее", !"Отмена");

			mysql_format(mysql, global_str, 150, "SELECT * FROM accounts WHERE NickName = '%s' LIMIT 1", PN(playerid));
			mysql_tquery(mysql, global_str, "AloginAuth", "id", playerid, strval(inputtextsave));
		}
        case 5:
        {
            if(!response) return pTemp[playerid][targetID] = INVALID_PLAYER_ID;
            if(response) 
			{
                PI[pTemp[playerid][targetID]][pAdmin] = listitem;

                if listitem == 0 *then
                { 
					SCM(playerid, COLOR_YELLOW, !"Вы были сняты с поста игрового мастера!");
                    SCMF(pTemp[playerid][targetID], COLOR_YELLOW, "Игровой мастер %s снял Вас с должности игрового мастера", PN(playerid));
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
        case 6:
		{
			if !response *then
				return false;

			listitem++;
			spdList(playerid, 0, listitem);

			return print_AdminCommand(playerid, listitem);
		}

		case 7:
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
            
            f(global_str, 128, "[%s #%d] %s[%d] вошел на сервер", Admin_Names[PI[playerid][pAdmin]], PI[playerid][pAdminNumber], PN(playerid), playerid);
            SendAdminsMessage(-1, global_str);

            SCMF(playerid, -1, "Вы успешно авторизовались как {EE3366}%s{FFFFFF}!", Admin_Names[PI[playerid][pAdmin]]);
        
            //for new i; i < 53; i++ do EnableAntiCheatForPlayer(playerid, i, 0); 

            Iter_Add(Admin, playerid);
            ALogin{playerid} = true;
        }
    }
    else 
    {
        SCM(playerid, -1, !"Вы ввели неверный пароль от {EE3366}админ-панели{FFFFFF}!");
        f(global_str, 128, "[%s #%d] %s[%d] ввел неверный пароль от админ-панели", Admin_Names[PI[playerid][pAdmin]], PI[playerid][pAdminNumber], PN(playerid), playerid);
        SendAdminsMessage(-1, global_str);
        return Kick(playerid);
    }
	return 1;
}

stock CheckAccess(playerid, adminLvl = 1, modLvl = 0)
{
    if PI[playerid][pAdmin] < adminLvl *then 
	{
		return 0;
	}
    else if modLvl >= 1 && PI[playerid][pModer] >= modLvl && modLvl != 0 *then 
    {
        return 0;
    }
	else if !ALogin{playerid} *then
	{
		SCM(playerid, COLOR_LIGHTGREY, !"Вы не авторизованы как игровой мастер");
		return 0;
	}
    return 1;
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
	mysql_tquery(mysql, !cache_get_row_count() ? (str_f("INSERT INTO `bans` (`Name`, `BanAdmin`, `BanSeconds`, `BanReason`) VALUE ('%s', '%s', '%d', '%s')", player_name, ban_admin, Global_Time+days*60*60*24, reason)):(str_f("UPDATE `bannames` SET `BanAdmin` = '%s', `BanSeconds` = %d, `BanReason` = '%s' WHERE `Name` = BINARY('%s') LIMIT 1;", ban_admin, Global_Time+days*60*60*24, reason, player_name)));
	
    return true;
}