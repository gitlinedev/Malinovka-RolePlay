// if !IsPlayerLogged{playerid} *then return false;
// #define COLOR_PURPLE           	 	0xFF99CCFF

cmd:me(playerid, params[])
{
	if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);
	if sscanf(params,"s[100]",params[0]) *then return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /me [текст]");
	if IsAIP(params[0]) *then return 0;
	f(global_str, 300,"%s %s",PN(playerid),params[0]);
	ProxDetector(25,playerid,global_str,COLOR_PURPLE);
	SetPlayerChatBubble(playerid, params[0], COLOR_PURPLE, 10.0, 5000);
	return 1;
}
cmd:do(playerid, params[])
{
	if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);
	if sscanf(params,"s[100]",params[0]) *then return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /do [текст]");
	if IsAIP(params[0]) *then return 0;
	f(global_str, 300,"%s %s",params[0], PN(playerid));
	ProxDetector(25,playerid,global_str,COLOR_PURPLE);
	SetPlayerChatBubble(playerid, params[0], COLOR_PURPLE, 10.0, 5000);
	return 1;
}
cmd:todo(playerid, params[])
{
	if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);
	if sscanf(params,"p<*>s[128]s[128]",params[0],params[1]) *then return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /todo [Сообщение]*[Действие]");
	if IsAIP(params[0]) *then return 0;
	f(global_str, 400,"\"%s\", - сказал %s,{FF99FF} %s.",params[0], PN(playerid), params[1]);
	ProxDetector(25,playerid,global_str,COLOR_PURPLE);
	SetPlayerChatBubble(playerid, params[0], COLOR_PURPLE, 10.0, 5000);
	return 1;
}
cmd:c(playerid, params[])
{
	if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);
	if sscanf(params,"s[100]",global_str) *then return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /c [текст]");
	if IsAIP(global_str) *then return 0;
	f(global_str,150, "%s[%d] говорит шепотом: {FFFFFF}%s",PN(playerid),playerid,global_str);
	ProxDetector(2,playerid, global_str, COLOR_BLUE);
	return 1;
}
cmd:b(playerid, params[])
{
	if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);
	if sscanf(params,"s[100]",global_str) *then return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /b [OOC (nonRP) сообщение]");
	if IsAIP(global_str) *then return 0;
	f(global_str,150, "(( %s[%d]: %s ))", PN(playerid), playerid, global_str);
	ProxDetector(2,playerid, global_str, COLOR_BLUE);
	return 1;
}
cmd:s(playerid, params[])
{
    if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);
	if sscanf(params,"s[100]",global_str) *then return SCM(playerid, COLOR_LIGHTGREY, !"Используйте: /s [текст]");
    if IsAIP(global_str) *then return 0;
	SetPlayerChatBubble(playerid, params[0], -1, 25.0, 5000);
    f(global_str, 200, "%s[%d] крикнул: %s", PN(playerid), playerid, params[0]);
	ProxDetector(25, playerid, global_str, -1);
	if(!IsPlayerInAnyVehicle(playerid))	ApplyAnimationEx(playerid, "ON_LOOKERS", "shout_01",1000.0,0,0,0,0,0,1);
	return 1;
}
cmd:menu(playerid)
{
	return SPD(playerid, 6, 2, !"{EE3366}Меню игрока ",\
		"1. Список преступлений\n\
		2. Пассивный режим {66CC66}(Включён)\n\
		3. Команды сервера\n\
		4. Горячие клавиши\n\
		5. Помощь / жалоба\n\
		6. Настройки аккаунта\n\
		7. Общие правила\n\
		8. Ресурсы игры\n\
		9. Изменить никнейм\n\
		10. Чёрный список организаций\n\
		11. Активные наказания\n\
		{66CCFF}12. Дополнительные услуги", !"Выбрать ", !"Закрыть ");
}
cmd:help(playerid) return ShowServerCommands(playerid);

stock k_OnDialogResponse(playerid, dialogid, response, listitem)
{
    switch dialogid do
	{
        case 6:
        {
            if (response)
            {
                switch (listitem)
                {
                    case 0: ShowPlayerStats(playerid);
                    case 1: ShowServerCommands(playerid);
                    case 2: ShowHotKeys(playerid);
                    case 3: ShowHelpDialog(playerid);
                    case 4: ShowPlayerSettings(playerid);
                    case 5: ShowServerRules(playerid);
                    case 6: ShowServerResources(playerid);
                    case 8: ChangePlayerName(playerid);
                    case 9: ShowBlacklistDialog(playerid);
                    case 10: ShowDonate(playerid);
                }
            }
        }
		case 7:
		{
			switch (listitem)
			{
				case 0: 
				{
					return SPD(playerid, 8, 5, !"{EE3366}Основные команды", !"Команда\tОписание\n/id\tПоиск по имени / ID игрока\n/mp\tТелепортироваться на мероприятие\n/top\tТоп-лист последнего системного мероприятия\n/gps\tНавигатор\n/sex\tИстория изменений пола\n/end\tОтказаться от участия в системном мероприятии\n/bed\tЗанять койку в больнице\n/belt\tПристегнуть / отстегнуть ремень безопасности\n/plus\tВозможности {EE3366}Малиновка Плюс\n/item\tАктивировать предмет\n/help\tМеню помощи\n/bank\tМеню банка\n/back\tВернуться с мероприятия или тест-драйва\n/anim(list)\tМеню анимаций\n/menu (/mn)\tМеню игрока\n/light\tВключить / выключить фары\n/eject\tВыкинуть из транспорта\n/radio\tОнлайн-радио\n/leave\tУволиться по собственному желанию\n/throw\tВывести игрока из здания организации\n/boost\tИнформация о бусте\n/warns\tИнформация о предупреждениях\n/c(arrier)info\tИнформация о рабочем транспорте развозчиков\n/return\tСнять временный набор одежды\n/report\tОтправить сообщение игровым мастерам\n/routes\tАвтобусные маршруты\n/donate\tДополнительные возможности\n/sellsim\tПродать SIM-карту игроку\n/leaders\tЛидеры и заместители организаций\n/members\tУчастники организации онлайн\n/transfer\tПодать заявку на перевод в организацию", !"Закрыть ", !"Назад ");
				}
				case 1:
				{
					return SPD(playerid, 8, 5, !"{EE3366}Коммуникации", !"Команда\tОписание\n/c(all)\tСделать звонок\n/b (/n)\tOOC чат\n/s\tКрикнуть что-то\n/w\tСказать что-то шёпотом\n/r\tРация организации и основной работы\n/d\tРация департамента\n/rr (/rb)\tOOC рация организации и основной работы\n/dd (/db)\tOOC рация департамента\n/do\tДействие от 3-го лица\n/me\tДействие игрока\n/vm\tВыдать мут голосового чата игроку\n/try\tПопытка действия\n/gov\tЗапланировать собеседование\n/sms\tОтправить SMS\n/todo\tДействие с сообщением\n/unvm\tСнять мут голосового чата у игрока\n/phone\tМеню телефона", !"Закрыть ", !"Назад ");
				}
				case 2:
				{
					return SPD(playerid, 8, 5, !"{EE3366}Бизнес и АЗС", !"Команда\tОписание\n/seller\tВыбрать продавца [бизнес]\n{66CC66}/station\t{66CC66}Меню АЗС\n{66CC66}/business\t{66CC66}Меню бизнеса\n/buystation\tКупить АЗС\n/buybusiness\tКупить бизнес", !"Закрыть ", !"Назад ");
				}
				case 3:
				{
					return SPD(playerid, 8, 5, !"{EE3366}Основные работы ", !"Работа\tКоманда\tОписание\nАвтомеханик\t/repair\tОтремонтировать транспорт\nАвтомеханик\t/accept\tПринять вызов\nАвтомеханик\t/reflip\tПеревернуть транспорт\nРазвозчик\t/c(arrier)info\tИнформация о рабочем транспорте развозчиков", !"Закрыть ", !"Назад ");
				}
				case 4:
				{
					return SPD(playerid, 8, 2, !"{EE3366}Команды организаций ", !"1. БЦРБ\n2. Войсковая часть\n3. Полиция\n4. ОПГ", !"Просмотр ", !"Назад ");
				}
				case 5:
				{
					return SPD(playerid, 8, 5, !"{EE3366}Лидеры и заместители ", !"Команда\tОписание\n/l\tРация лидеров\n/ll (/lb)\tOOC рация лидеров\n/bl\tЧёрный список организации\n/lname\tНайти игрока по старому никнейму\n/twarn\tВыдать выговор\n/clead\tНазначить на должность смотрящего за стрелой\n/invite\tПринять игрока в организацию\n/setskin\tИзменить форму игрока\n/setrang\tИзменить ранг игрока\n/untwarn\tСнять выговор\n/uninvite\tУволить игрока из организации\n/offtwarn\tВыдать выговор оффлайн\n/setgroup\tИзменить группу игрока\n/accessint\tРазрешать вход в интерьер правительства\n/transfers\tСписок заявок на перевод\n/promotion\tУзнать информацию о заданиях игрока\n/offuntwarn\tСнять выговор оффлайн\n/allmembers\tПоказать всех участников организации\n/uninviteall\tУволить всех игроков из организации\n/uninviteoff\tУволить оффлайн игрока из организации\n/offpromotion\tУзнать информацию о заданиях игрока оффлайн", !"Закрыть ", !"Назад ");
				}
			}
		}
		case 8:
		{
			if(response) return 1;
			if(!response) callcmd::help(playerid);
		}
		case 9:
		{
			if(response) return 1;
			if(!response) callcmd::menu(playerid);
		}
		case 10:
		{
			if(response) return 1;
			if(!response) return 1;
		}
    }
    return 1;
}