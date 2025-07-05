new InfoHouse[MAX_PLAYERS],
	HouseEntered[MAX_PLAYERS];

enum hInfo
{
	hID,
	Float:hEnter_X,
	Float:hEnter_Y,
	Float:hEnter_Z,
	Float:hExit_X,
	Float:hExit_Y,
	Float:hExit_Z,
	hCost,
	hLevel,
	hOwner[24],
	hInt,
	hLock,
	hMoney,
	hDrugs,
	hAmmo,
    hMetall,
	hSkin[3],
	hNalog,
	hKlass,
	hMed,

	hDays,
	hLocation,
	hParkPlaces,

	hObjectCount[2],
	H_PICKUP_ID,
	H_AREA_ID
};

new HouseIcon[MAX_HOUSES] = {-1, ...};

static const houseKlass[2][23 + 1] = {
	"Избушка",
	"Средний класс"
};
static const houseLocation[2][23 + 1] = {
	"пгт. Батырево",
	"с. Роговичи"
};

new
	HouseInfo[MAX_HOUSES][hInfo];

stock LoadHouses()
{
	new ID, Cache:result = mysql_query(mysql, "SELECT * FROM `houses`");
	
	LoadedHouses = cache_get_row_count(mysql);
	
	for new i; i < LoadedHouses; i++ do
	{
		ID = cache_get_row_int(i, 0, mysql);
		HouseInfo[ID][hID] = ID;

		HouseInfo[ID][hEnter_X] = cache_get_row_float(i, 1, mysql);
		HouseInfo[ID][hEnter_Y] = cache_get_row_float(i, 2, mysql);
		HouseInfo[ID][hEnter_Z] = cache_get_row_float(i, 3, mysql);

		HouseInfo[ID][hExit_X] = cache_get_row_float(i, 4, mysql);
		HouseInfo[ID][hExit_Y] = cache_get_row_float(i, 5, mysql);
		HouseInfo[ID][hExit_Z] = cache_get_row_float(i, 6, mysql);
		cache_get_row(i, 7, HouseInfo[ID][hOwner], mysql, 24);
		
		HouseInfo[ID][hLevel] = cache_get_row_int(i, 8, mysql);
		HouseInfo[ID][hCost] = cache_get_row_int(i, 9, mysql);
		HouseInfo[ID][hLock] = cache_get_row_int(i, 10, mysql);
		HouseInfo[ID][hInt] = cache_get_row_int(i, 11, mysql);
		HouseInfo[ID][hMoney] = cache_get_row_int(i, 12, mysql);
		HouseInfo[ID][hDrugs] = cache_get_row_int(i, 13, mysql);
		HouseInfo[ID][hAmmo] = cache_get_row_int(i, 14, mysql);
		HouseInfo[ID][hSkin][0] = cache_get_row_int(i, 15, mysql);
		HouseInfo[ID][hSkin][1] = cache_get_row_int(i, 16, mysql);
		HouseInfo[ID][hSkin][2] = cache_get_row_int(i, 17, mysql);
		HouseInfo[ID][hNalog] = cache_get_row_int(i, 18, mysql);
		HouseInfo[ID][hKlass] = cache_get_row_int(i, 19, mysql);
		HouseInfo[ID][hMed] = cache_get_row_int(i, 20, mysql);

		HouseInfo[ID][hDays] = cache_get_row_int(i, 21, mysql);
		HouseInfo[ID][hLocation] = cache_get_row_int(i, 22, mysql);
		HouseInfo[ID][hParkPlaces] = cache_get_row_int(i, 23, mysql);
		
	    if(isnull(HouseInfo[ID][hOwner])) SetString(HouseInfo[ID][hOwner], "The State");
	}
	cache_delete(result, mysql);
	
	return true;
}

stock SaveHouse(houseid)
{
	if(!IsValidHouse(houseid)) return 0;
	static str[256];
	global_str = "";
	f(str, sizeof(str), "UPDATE `houses` SET");
	strcat(global_str, str);

	f(str, sizeof(str), "`Enter_X` = '%.4f',`Enter_Y` = '%.4f',`Enter_Z` = '%.4f', ",
		HouseInfo[houseid][hEnter_X],
		HouseInfo[houseid][hEnter_Y],
		HouseInfo[houseid][hEnter_Z]);

	strcat(global_str, str);

	f(str, sizeof(str), "`Exit_X` = '%.4f', `Exit_Y` = '%.4f', `Exit_Z` = '%.4f', ",
	 	HouseInfo[houseid][hExit_X],
		HouseInfo[houseid][hExit_Y],
		HouseInfo[houseid][hExit_Z]);

	strcat(global_str, str);

	f(str, sizeof(str), "`Owner` = '%s',",
		HouseInfo[houseid][hOwner]);

	strcat(global_str, str);

	f(str, sizeof(str), "`Level` = '%d', `Cost` = '%d', `Lock` = '%d', ",
		HouseInfo[houseid][hLevel],
		HouseInfo[houseid][hCost],
		HouseInfo[houseid][hLock]);

	strcat(global_str, str);

	f(str, sizeof(str), "`Interior` = '%d', `Money` = '%d', `Drugs` = '%d', `Ammo` = '%d', ",
		HouseInfo[houseid][hInt],
		HouseInfo[houseid][hMoney],
		HouseInfo[houseid][hDrugs],
		HouseInfo[houseid][hAmmo]);

	strcat(global_str, str);

	f(str, sizeof(str), "`Skin_1` = '%d', `Skin_2` = '%d', `Skin_3` = '%d', ",
		HouseInfo[houseid][hSkin][0],
		HouseInfo[houseid][hSkin][1],
        HouseInfo[houseid][hSkin][2]);

	strcat(global_str, str);

	f(str, sizeof(str), "`Nalog` = '%d', `Klass` = '%d', ",
		HouseInfo[houseid][hNalog],
		HouseInfo[houseid][hKlass],
		HouseInfo[houseid][hMed]);

	strcat(global_str, str);

	f(str, sizeof(str), "`Days` = '%d', `Location` = '%d', `ParkPlaces` = '%d', ",
		HouseInfo[houseid][hDays],
		HouseInfo[houseid][hLocation],
		HouseInfo[houseid][hParkPlaces]);

	strcat(global_str, str);

	f(str, sizeof(str), "`Med` = '%d' WHERE `ID` = '%i'",
		HouseInfo[houseid][hMed],
		HouseInfo[houseid][hID]);

	strcat(global_str, str);
	
	mysql_tquery(mysql, global_str);
	return 1;
}

stock UpdateHouse(house)
{
	if(IsValidDynamicMapIcon(HouseIcon[house]) && GetString(HouseInfo[house][hOwner], "The State") == 0) {
		DestroyDynamicMapIcon(HouseIcon[house]);
		HouseIcon[house] = INVALID_STREAMER_ID;
	}
	
	if IsValidDynamicPickup(HouseInfo[house][H_PICKUP_ID]) *then
		DestroyDynamicPickup(HouseInfo[house][H_PICKUP_ID]);
		
	if IsValidDynamicArea(HouseInfo[house][H_AREA_ID]) *then
		DestroyDynamicArea(HouseInfo[house][H_AREA_ID]);

	HouseInfo[house][H_AREA_ID] = CreateDynamicSphere(HouseInfo[house][hEnter_X], HouseInfo[house][hEnter_Y], HouseInfo[house][hEnter_Z], 2.25, -1);

	HouseInfo[house][H_PICKUP_ID] = CreateDynamicPickup( !GetString(HouseInfo[house][hOwner], "The State") ? 19522 : 1273, 23, HouseInfo[house][hEnter_X], HouseInfo[house][hEnter_Y], HouseInfo[house][hEnter_Z],-1);
	if(GetString(HouseInfo[house][hOwner], "The State")) HouseIcon[house] = CreateDynamicMapIcon(HouseInfo[house][hEnter_X], HouseInfo[house][hEnter_Y], HouseInfo[house][hEnter_Z], 31, -1, 0, -1, -1, 100.0);

	return SaveHouse(house);
}

stock ShowInfoMenu(playerid, id, type) // 0 biz, 1 house
{
	//new SELLING = !type ? GetString(BizData[id][bOwner], "The State"):GetString(HouseInfo[id][hOwner], "The State"), 
	//	LOCK = (!type ? (!BizData[id][bLock] && !IsNoEnterBiz(id)):!HouseInfo[id][hLock]);

	new SELLING = GetString(HouseInfo[id][hOwner], "The State");
		//LOCK = HouseInfo[id][hLock];

	switch type do
	{
		case 1:
		{
			InfoHouse[playerid] = id;
			
			pTemp[playerid][pShowDialog] = 1;

		    if SELLING *then
			{		
				return SPDF(playerid, dHouseSelling, 0, !"{EE3366}Дом продаётся", !"Купить", !"Закрыть",\
					"{FFFFFF}Номер дома:\t\t%d\n\
					Название:\t\t%s\n\
					Расположение:\tс. Роговичи\n\
					Стоимость:\t\t%d руб\n\
					Квартплата:\t\t%d руб / день\n\n\
					Вы желаете купить этот дом?", id, houseKlass[HouseInfo[id][hKlass]], HouseInfo[id][hCost], HouseInfo[id][hNalog]);
			}
			else 
			{
				pTemp[playerid][pShowDialog] = 1;

				return SPDF(playerid, dHouseOwned, 0, !"{EE3366}Дом куплен", !"Войти", !"Закрыть",\
					"{FFFFFF}Номер дома:\t\t%d\n\
					Владелец:\t\t{3377CC}%s\n\
					{FFFFFF}Название:\t\t%s\n\
					Расположение:\tс. Роговичи\n\
					Стоимость:\t\t%d руб\n\
					Квартплата:\t\t%d руб / день\n\n\
					Вы желаете войти в этот дом?", id, HouseInfo[id][hOwner], houseKlass[HouseInfo[id][hKlass]], HouseInfo[id][hCost], HouseInfo[id][hNalog]);
			}
		}
	}
	return false;
}

stock IsValidHouse(id)
{
	if(id <= LoadedHouses && id > 0) return 1;
	return 0;
}

stock house_OnDialogResponse(playerid, dialogid, response, listitem, inputtextsave[])
{
	pTemp[playerid][pShowDialog] = 0;

	switch dialogid do
	{
		case dHouseSelling:
		{
			if !response *then return 1;
			if response *then
			{
				new house = InfoHouse[playerid];
				InfoHouse[playerid] = -1;

				if(!strcmp(HouseInfo[house][hOwner], "The State"))
				{
					if getPlayerMoney(playerid) < HouseInfo[house][hCost] *then return SCM(playerid, COLOR_LIGHTGREY, !"У Вас недостаточно денег на руках");

					f(global_str, 30, "Покупка дома (ID: %d)", house);
					GivePlayerMoneyLog(playerid, -HouseInfo[house][hCost], global_str);

					HouseEntered[playerid] = house;

					PI[playerid][pHouseKey] = house;

					SCM(playerid, 0x367074FF, !"Поздравляем! Вы купили дом. Не забудьте оплатить его в банке - {d3cfb6}/gps 1 8 {367074}или {d3cfb6}/gps 7");

					SPD(playerid, 0, 0, !"{EE3366}Покупка жилья",\
						!"{FFFFFF}Для управления недвижимостью используйте команду /home\n\
						Оплатите жильё в банке {3366cc}(/gps 1 8 и /gps 7){FFFFFF} или в Мобильном банке {3366cc}(клавиша P){FFFFFF}.\n\
						Не забывайте вовремя платить за него, в противном случае он будет опечатан!\n\n\
						{FFFF00}Посетите Центр недвижимости (/gps 7) для повышения удобства пользования жильём", !"Закрыть", !"");
					
					f(global_str, 10, "-%d руб", HouseInfo[house][hCost]);
					cef_emit_event(playerid, "show-notifications:radar", CEFINT(16), CEFINT(5), CEFSTR("red"), CEFSTR("Покупка дома"), CEFSTR(global_str), CEFINT(0));
            
					SetString(HouseInfo[house][hOwner], PN(playerid));
					UpdateHouse(house);

					SaveAccount(playerid);
				}
				else SCM(playerid, COLOR_LIGHTGREY, !"Этот дом уже куплен");
			}
		}
		case dHouseOwned:
		{
			if !response *then return pTemp[playerid][pShowDialog] = 0;
			if response *then
			{	
				new house = InfoHouse[playerid];
				InfoHouse[playerid] = -1;

                if(!PlayerToPoint(2.5, playerid, HouseInfo[house][hEnter_X], HouseInfo[house][hEnter_Y], HouseInfo[house][hEnter_Z])) return 1;
                if(HouseInfo[house][hLock] == 0 || !strcmp(PN(playerid), HouseInfo[house][hOwner], true)) 
				{
					SetPlayerInterior(playerid, HouseInfo[house][hInt] + 1);

	                SetPlayerPosEx(playerid, HouseInfo[house][hExit_X], HouseInfo[house][hExit_Y], HouseInfo[house][hExit_Z]);
	                SetCameraBehindPlayer(playerid);

	                FreezePlayer(playerid);
	            }
	            else cef_emit_event(playerid, "show-notifications:center", CEFINT(3000), CEFINT(2), CEFSTR("Этот дом закрыт"));
			}
		}
		case dHouseMenuBack:
		{
			if !response *then return callcmd::home(playerid);
			if response *then return 1;
		}
		case dHouseMenu:
		{
			if !response *then return 1;
			if response *then
			{
				new house = PI[playerid][pHouseKey];

				switch listitem do
				{	
					case 0:
					{
						SPDF(playerid, dHouseMenuBack, DIALOG_STYLE_MSGBOX, !"{EE3366}Информация о доме", !"Закрыть", !"Назад", "\
						{FFFFFF}Название:\t\t {3366cc}%s\n\
						{FFFFFF}Номер дома:\t\t %d\n\
						Владелец:\t\t %s\n\
						Расположение:\t %s\n\
						Стоимость:\t\t %d руб\n\
						{FFFFFF}Квартплата:\t\t {4acc6c} %d руб / день\n\
						{FFFFFF}Статус оплаты:\t\t %d дн {FFFF99}(оплата в Банке - /gps или Мобильном Банке - клавиша P)\n\
						{FFFFFF}Кол-во парк. мест:\t %d {FFFF99}(купить в Центре недвижимости - /gps 7)\n\
						{FFFFFF}Статус:\t\t\t {4acc6c}%s", 
							houseKlass[HouseInfo[house][hKlass]],
							house,
							HouseInfo[house][hOwner],
							houseLocation[HouseInfo[house][hLocation]],
							HouseInfo[house][hCost],
							HouseInfo[house][hNalog],
							HouseInfo[house][hDays],
							HouseInfo[house][hParkPlaces],
							HouseInfo[house][hLock] ? ("{4ccd73}Дом открыт") : ("{FF6347}Дом закрыт"));
					}
					case 1:
					{
						return 1;
					}
					case 2:
					{
						return 1;
					}
					case 3:
					{
						HouseInfo[house][hLock] = !HouseInfo[house][hLock];

						if HouseInfo[house][hLock] == 1 *then cef_emit_event(playerid, "show-notifications:radar", CEFINT(15), CEFINT(3), CEFSTR("icon-red"), CEFSTR("Дом закрыт"), CEFSTR(""), CEFINT(2));
						else cef_emit_event(playerid, "show-notifications:radar", CEFINT(17), CEFINT(3), CEFSTR("icon-green"), CEFSTR("Дом открыт"), CEFSTR(""), CEFINT(3));
						return callcmd::home(playerid);
					}
				}
			}
		}
		case dAddHouse:
		{
			if !response *then return callcmd::as(playerid);
			if response *then
			{
				switch(listitem)
				{
					case 0:
					{
						SPD(playerid, dAddHouseCost, DIALOG_STYLE_INPUT, !"{EE3366}Создание дома", 
							!"{FFFFFF}Укажите цену которая будет использоваться при продаже дома\n\n{FFFF99}Данная сумма не может привышать 100 млн, а также быть меньше 1 тыс.", !"Далее", !"Назад");
					}
					case 1:
					{
						SPD(playerid, dAddHouseNalog, DIALOG_STYLE_INPUT, !"{EE3366}Создание дома", 
							!"{FFFFFF}Укажите налог на дом.\n\n{FFFF99}Данная сумма не может привышать 1 млн, а также быть меньше 1 тыс.", !"Далее", !"Назад");
					}
					case 2:
					{
						SPD(playerid, dAddHouseLocation, DIALOG_STYLE_LIST, !"{EE3366}Создание дома", 
							!"пгт. Батырево\nс. Роговичи", !"Далее", !"Назад");
					}
					case 3:
					{
						SPD(playerid, dAddHouseEnter, DIALOG_STYLE_MSGBOX, !"{EE3366}Создание дома", 
							!"{FFFFFF}Вы уверены что хотите установить место входа в этом месте?", !"Далее", !"Назад");
					}
					case 4:
					{
						SPD(playerid, dAddHouseCar, DIALOG_STYLE_MSGBOX, !"{EE3366}Создание дома", 
							!"{FFFFFF}Вы уверены что хотите установить место буксировки машины в этом месте?", !"Далее", !"Назад");
					}
					case 5:
					{
						if (IsAllHouseStepsComplete(playerid)) 
						{
							SCM(playerid, -1, !"Вы успешно создали дом");
							ClearCreateHouse(playerid);
						} 
						else 
						{
							SCM(playerid, -1, !"Вы ещё не заполнили все пункты");
						}
					}
					case 6:
					{
						SCM(playerid, -1, !"Вы отменили создание нового дома");
						ClearCreateHouse(playerid);
					}
				}
			}
		}
		case dAddHouseCost:
		{
			if !response *then return callcmd::addhouse(playerid);
			if response *then
			{
				if pTemp[playerid][AddHouse] == 0 *then 
					return SCM(playerid, -1, !"Вы не начали создание дома");

				if strval(inputtextsave) < 1000 or strval(inputtextsave) > 100000000 *then 
					return SCM(playerid, -1, !"Государственная стоимость дома не может привышать 100 млн, и не может быть меньше 1 тыс");
				
				pTemp[playerid][AHouseCost] = strval(inputtextsave);

				pTemp[playerid][AHouseStep][0] = 1;

				return callcmd::addhouse(playerid);
			}
		}
		case dAddHouseNalog:
		{
			if !response *then return callcmd::addhouse(playerid);
			if response *then
			{
				if pTemp[playerid][AddHouse] == 0 *then 
					return SCM(playerid, -1, !"Вы не начали создание дома");

				if strval(inputtextsave) < 1000 or strval(inputtextsave) > 100000000 *then 
					return SCM(playerid, -1, !"Налог на дом не может привышать 1 млн, и не может быть меньше 1 тыс");
				
				pTemp[playerid][AHouseNalog] = strval(inputtextsave);

				pTemp[playerid][AHouseStep][1] = 1;

				return callcmd::addhouse(playerid);
			}
		}
		case dAddHouseLocation:
		{
			if !response *then return callcmd::addhouse(playerid);
			if response *then
			{
				if pTemp[playerid][AddHouse] == 0 *then 
					return SCM(playerid, -1, !"Вы не начали создание дома");

				pTemp[playerid][AHouseLocation] = listitem;

				pTemp[playerid][AHouseStep][2] = 1;

				return callcmd::addhouse(playerid);
			}
		}
		case dAddHouseEnter:
		{
			if !response *then return callcmd::addhouse(playerid);
			if response *then
			{
				if pTemp[playerid][AddHouse] == 0 *then 
					return SCM(playerid, -1, !"Вы не начали создание дома");

				GetPlayerPos(playerid, pTemp[playerid][AHouseEnterX] , pTemp[playerid][AHouseEnterY], pTemp[playerid][AHouseEnterZ]);
				
				pTemp[playerid][AHouseStep][3] = 1;

				return callcmd::addhouse(playerid);
			}
		}
		case dAddHouseCar:
		{
			if !response *then return callcmd::addhouse(playerid);
			if response *then
			{
				if pTemp[playerid][AddHouse] == 0 *then 
					return SCM(playerid, -1, !"Вы не начали создание дома");

				GetPlayerPos(playerid, pTemp[playerid][AHouseCarX], pTemp[playerid][AHouseCarY], pTemp[playerid][AHouseCarZ]);

				pTemp[playerid][AHouseStep][4] = 1;

				return callcmd::addhouse(playerid);
			}
		}
		case dStartAHouse:
		{
			if !response *then return 1;
			if response *then
			{
				pTemp[playerid][AddHouse] = 1;
				callcmd::addhouse(playerid);

				return SCM(playerid, -1, !"Вы начали создание дома");
			}
		}
	}
	return 1;
}

stock IsAllHouseStepsComplete(playerid)
{
    for (new i = 0; i < 4; i++) {
        if (pTemp[playerid][AHouseStep][i] == 0) return false;
    }
    return true;
}

cmd:home(playerid)
{
	new house = PI[playerid][pHouseKey];

	if house > 0 && GetString(HouseInfo[house][hOwner], PN(playerid)) *then
	{
		SPDF(playerid, dHouseMenu, DIALOG_STYLE_LIST, !"{EE3366}Управление домом", !"Далее", !"Закрыть", "\
		1. Информация\n\
		2. Информация об улучшениях\n\
		3. Парковочные места\n\
		4. %s дом\n\
		5. Построить маршрут на навигаторе\n\
		6. Продать дом", HouseInfo[house][hLock] ? ("Открыть") : ("Закрыть"));
	}
	else SCM(playerid, COLOR_GREY, !"У Вас нет дома или квартиры");

	return 1;
}

cmd:addhouse(playerid)
{
	if(!CheckAccess(playerid, 8))
		return 0;
	
	if pTemp[playerid][AddHouse] == 0 *then SPD(playerid, dStartAHouse, DIALOG_STYLE_MSGBOX, !"{ee3366}Создание дома", !"{FFFFFF}Вы действительно хотите начать создание дома?", !"Да", !"Нет");
	else 
	{
		SPDF(playerid, dAddHouse, DIALOG_STYLE_TABLIST_HEADERS, !"{ee3366}Создание дома", !"Далее", !"Назад", "Пункт\tЗначение\n\
			{FFFFFF}Стоимость дома\t{FFFF99}%d\n\
			{FFFFFF}Налоговая ставка\t{FFFF99}%d\n\
			{FFFFFF}Расположение\t{FFFF99}%s\n\
			{FFFFFF}Точка входа в дом\t{FFFF99}%.2f %.2f %.2f\n\
			{FFFFFF}Место появления автомобиля\t{FFFF99}%.2f %.2f %.2f\n\
			{FFFF99}Создать дом\n\
			{FF6347}Отменить создание дома", pTemp[playerid][AHouseCost], pTemp[playerid][AHouseNalog], houseLocation[pTemp[playerid][AHouseLocation]],
			pTemp[playerid][AHouseEnterX], pTemp[playerid][AHouseEnterY], pTemp[playerid][AHouseEnterZ],
			pTemp[playerid][AHouseCarX], pTemp[playerid][AHouseCarY], pTemp[playerid][AHouseCarZ]);
	}
	return 1;
}

cmd:undocreate(playerid)
{
	if(!CheckAccess(playerid, 8))
		return 0;
	
	if pTemp[playerid][AddHouse] == 0 *then return SCM(playerid, -1, !"Вы не начали создание дома");

	ClearCreateHouse(playerid);
	
	return SCM(playerid, -1, !"Вы отменили создание дома");
}

stock ClearCreateHouse(playerid)
{
	pTemp[playerid][AHouseCost] =
	pTemp[playerid][AddHouse] =
	pTemp[playerid][AHouseNalog] =
	pTemp[playerid][AHouseLocation] = 0;

	pTemp[playerid][AHouseEnterX] =
	pTemp[playerid][AHouseEnterY] =
	pTemp[playerid][AHouseEnterZ] =
	pTemp[playerid][AHouseCarX] =
	pTemp[playerid][AHouseCarY] =
	pTemp[playerid][AHouseCarZ] = 0.0;

	for (new i = 0; i < 4; i++)
    {
        pTemp[playerid][AHouseStep][i] = 0;
    }
}