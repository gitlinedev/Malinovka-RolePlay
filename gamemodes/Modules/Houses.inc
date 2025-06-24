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
	hGarage,
	Float:hGarage_X,
	Float:hGarage_Y,
	Float:hGarage_Z,
	hObjectCount[2],
	H_PICKUP_ID,
	H_AREA_ID
};

new HouseIcon[MAX_HOUSES] = {-1, ...};

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

		//printf("LoadHouse -> %i", ID);

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

	HouseInfo[house][H_PICKUP_ID] = CreateDynamicPickup( !GetString(HouseInfo[house][hOwner], "The State") ? 1272 : 1273, 23, HouseInfo[house][hEnter_X], HouseInfo[house][hEnter_Y], HouseInfo[house][hEnter_Z],-1);
	if(GetString(HouseInfo[house][hOwner], "The State")) HouseIcon[house] = CreateDynamicMapIcon(HouseInfo[house][hEnter_X], HouseInfo[house][hEnter_Y], HouseInfo[house][hEnter_Z], 31, -1, 0, -1, -1, 100.0);

	return SaveHouse(house);
}

stock ShowInfoMenu(playerid, id, type) // 0 biz, 1 house
{
	//new SELLING = !type ? GetString(BizData[id][bOwner], "The State"):GetString(HouseInfo[id][hOwner], "The State"), 
	//	LOCK = (!type ? (!BizData[id][bLock] && !IsNoEnterBiz(id)):!HouseInfo[id][hLock]);

	new SELLING = GetString(HouseInfo[id][hOwner], "The State");
		//LOCK = HouseInfo[id][hLock];

	static const houseKlass[2][23 + 1] = {
		"Избушка",
		"Средний класс"
	};

	switch type do
	{
		case 1:
		{
			InfoHouse[playerid] = id;

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

stock house_OnDialogResponse(playerid, dialogid, response, listitem)
{
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
					HouseEntered[playerid] = house;

					PI[playerid][pHouseKey] = house;

					SCM(playerid, 0x367074FF, !"Поздравляем! Вы купили дом");
					SPD(playerid, 0, 0, !"{EE3366}Покупка жилья",\
						!"{FFFFFF}Для управления недвижимостью используйте команду /home\n\
						Оплата дома производится в банке (/gps 1 5). Не забудьте\n\
						вовремя платить за него, в противном случае он будет опечатан!", !"Закрыть", !"");
            
					SetString(HouseInfo[house][hOwner], PN(playerid));
					UpdateHouse(house);
				}
				else SCM(playerid, COLOR_LIGHTGREY, !"Этот дом уже куплен");
			}
		}
		case dHouseOwned:
		{
			if !response *then return 1;
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
		case dHouseMenu:
		{
			if !response *then return 1;
			if response *then
			{
				switch listitem do
				{	
					case 0:
					{
						return 1;
					}
				}
			}
		}
	}
	return 1;
}
