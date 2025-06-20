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
stock ShowPlayerStats(playerid)
{
	return SPD(playerid, dStats, 2, !"{EE3366}Стата игрока лол", !"Моя стата типа", !"Назад", !"Закрыть");
}
stock ShowServerCommands(playerid)
{
	return SPD(playerid, dCommands, 2, !"{EE3366}Команды сервера", !"1. Основные команды\n2. Коммуникации\n3. Дома и квартиры\n4. Бизнес и АЗС\n5. Основные работы\n6. Организации\n7. Лидеры и заместители", !"Просмотр ", !"Назад ");
}
stock ShowHotKeys(playerid)
{
	return SPD(playerid, dHotKeys, 5, !"{EE3366}Горячие клавиши", !"Клавиша\tТип\tОписание\nJ\t{FFFF99}Любой\tОткрыть меню лидера\nJ\t{FFFF99}Любой\tУдалить рабочий транспорт\nL\t{FFFF99}Любой\tОткрыть / закрыть транспорт\nM\t{FFFF99}Любой\tОткрыть меню игрока\nP\t{FFFF99}Любой\tОткрыть меню телефона\nO\t{FFFF99}Любой\tНастройки голосового чата (стандарт.)\nX\t{FFFF99}Любой\tГолосовой чат (стандарт.)\nB\t{FF9933}Пешеход\tЗанять койку в палате\nB\t{FF9933}Пешеход\tОткрыть меню покупок в бизнесе\nB\t{FF9933}Пешеход\tНажать на кнопку (открыть ворота, дверь)\nB\t{FF9933}Пешеход\tСесть на стул / кресло / лавку\nR\t{FF9933}Пешеход\tПерезарядить оружие\nЛевый ALT\t{FF9933}Пешеход\tЗалезть / слезть на вышку (ВЧ)\nH\t{66CC66}Водитель\tОткрыть ворота\nJ\t{66CC66}Водитель\tОткрыть меню работы\nK\t{66CC66}Водитель\tВставить / вытащить ключ\nB\t{66CC66}Водитель\tПристегнуть / отстегнуть ремень безопасности\nЛевый ALT\t{66CC66}Водитель\tВключить / выключить фары\nЛевый CTRL\t{66CC66}Водитель\tВключить / выключить двигатель\nM\t{66CCFF}Водитель / пассажир\tМегафон (в рабочем транспорте полиции)", !"Закрыть ", !"Назад ");
}
stock ShowServerRules(playerid)
{
	return SPD(playerid, dRules, 0, !"{EE3366}Общие правила", !"{FFFFFF}Правила игры расположены на форуме.\nВы хотите перейти к ним в браузере?", !"Открыть ", !"Назад ");
}
stock ShowHelpDialog(playerid)
{
	if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);

	if Int_GetPlayerData(playerid, !"report") > Global_Time *then
		return SCM(playerid, COLOR_GREY, "Эту команду можно использовать 1 раз в минуту");

	return SPD(playerid, dHelp, DIALOG_STYLE_LIST, !"{EE3366}Выберите тип", !"1. Вопрос или помощь\n2. Жалоба на игрока", !"Далее", !"Назад");
}
stock ShowPlayerSettings(playerid)
{
	return SPDF(playerid, dSettings, 4, !"{EE3366}Настройки аккаунта", !"Изменить ", !"Назад",
	"1. Размер HUD\t{FFFF99}...\n\
	2. Ники других игроков\t{FFFF99}Включены\n\
	3. Кинематографический режим\t{FFFF99}Отключён\n\
	4. Голосовой чат\t{FFFF99}Включён\n\
	5. Счетчик кадров в сек (FPS)\t{FFFF99}Включён\n\
	6. Отображение дождя\t{FFFF99}Включено\n\
	7. Рабочая голосовая рация\t{FFFF99}Включена\n\
	8. Шум в голосовой рации\t{FFFF99}Включен\n\
	9. Звук при нанесении урона\t{FFFF99}Включен\n\
	10. Индикатор источника урона\t{FFFF99}Включен");
}
stock ShowServerResources(playerid)
{
	return SPD(playerid, dResources, 4, !"{EE3366}Ресурсы игры", !"Сайт\t{FFFF99}malinovka.org\nФорум\t{FFFF99}malinovka.org/forum\nТех. поддержка\t{FFFF99}malinovka.org/help\nРеферальная система\t{FFFF99}malinovka.org/ref\nНовости и обновления\t{FFFF99}t.me/malinovka_game\nМалиновый сад\t{FFFF99}vk.com/malinovka_free", !"Перейти ", !"Назад ");
}
stock ChangePlayerName(playerid)
{
	return SPD(playerid, dChangeName, 4, !"{EE3366}Выбор типа", !"1. Изменить на случайный никнейм\t{FFFF99}Бесплатно\n2. Изменить на свой никнейм\t{3377CC}Платно", "Далее ", "Назад ");
}
stock ShowBlacklistDialog(playerid)
{
	return SPD(playerid, dBlackListMenu, 0, !"{EE3366}Чёрный список организаций ", !"{FFFFFF}Вы не состоите в чёрном списке ни одной организации", !"Закрыть ", !"Назад ");
}
stock ShowActivePunishments(playerid)
{
	return SPD(playerid, dActivePunishment, 0, !"{EE3366}Активные наказания ", !"{FFFFFF}У Вас нет активных наказаний", "Закрыть ", "Назад ");
}
stock ShowDonate(playerid)
{
	return SPD(playerid, dDonate, 4, !"{EE3366}Дополнительные услуги ", !"{FFFF99}1. Информация\t\n{FFFF99}2. Последние 10 операций\t\n{FFFF99}3. Купить малину\t\n4. Конвертация малины в рубли\t{66CCFF}(от 1 мал.)\n5. Подписка {DD3366}Малиновка Плюс\t{66CCFF}(от 249 руб)\n6. Покупка номеров на транспорт\t{66CCFF}(от 199 руб)\n7. Покупка лицензии или разрешения\t{66CCFF}(от 19 мал.)\n8. Покупка военного билета\t{66CCFF}(129 мал.)\n9. Покупка законопослушности (+10)\t{66CCFF}(19 мал.)\n10. Покупка одного навыка на оружие\t{66CCFF}(99 мал.)\n11. Покупка всех навыков на оружие\t{66CCFF}(499 мал.)\n12. Покупка 4-х значного номера телефона\t{66CCFF}(199 мал.)\n13. Изменение имени\t{66CCFF}(49 мал.)\n14. Изменение пола\t{66CCFF}(89 мал.)", "Далее ", "Закрыть ");
}
cmd:menu(playerid)
{
	return SPD(playerid, dMenu, 2, !"{EE3366}Меню игрока ",\
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
cmd:report(playerid) return ShowHelpDialog(playerid);
stock k_OnDialogResponse(playerid, dialogid, response, listitem, inputtextsave[])
{
    switch dialogid do
	{
        case dMenu:
        {
            if (response)
            {
                switch (listitem)
                {
                    case 0: ShowPlayerStats(playerid);
					case 1: return 1;
					case 2: return 1;
                    case 3: ShowServerCommands(playerid);
                    case 4: ShowHotKeys(playerid);
                    case 5: ShowHelpDialog(playerid);
                    case 6: ShowPlayerSettings(playerid);
                    case 7: ShowServerRules(playerid);
                    case 8: ShowServerResources(playerid);
                    case 9: ChangePlayerName(playerid);
                    case 10: ShowBlacklistDialog(playerid);
                    case 11: ShowDonate(playerid);
                }
            }
        }
		case dCommands:
		{
			if(!response) callcmd::help(playerid);
			if(response) 
			{
				switch (listitem)
				{
					case 0: 
					{
						return SPD(playerid, 11, 5, !"{EE3366}Основные команды", !"Команда\tОписание\n/id\tПоиск по имени / ID игрока\n/mp\tТелепортироваться на мероприятие\n/top\tТоп-лист последнего системного мероприятия\n/gps\tНавигатор\n/sex\tИстория изменений пола\n/end\tОтказаться от участия в системном мероприятии\n/bed\tЗанять койку в больнице\n/belt\tПристегнуть / отстегнуть ремень безопасности\n/plus\tВозможности {EE3366}Малиновка Плюс\n/item\tАктивировать предмет\n/help\tМеню помощи\n/bank\tМеню банка\n/back\tВернуться с мероприятия или тест-драйва\n/anim(list)\tМеню анимаций\n/menu (/mn)\tМеню игрока\n/light\tВключить / выключить фары\n/eject\tВыкинуть из транспорта\n/radio\tОнлайн-радио\n/leave\tУволиться по собственному желанию\n/throw\tВывести игрока из здания организации\n/boost\tИнформация о бусте\n/warns\tИнформация о предупреждениях\n/c(arrier)info\tИнформация о рабочем транспорте развозчиков\n/return\tСнять временный набор одежды\n/report\tОтправить сообщение игровым мастерам\n/routes\tАвтобусные маршруты\n/donate\tДополнительные возможности\n/sellsim\tПродать SIM-карту игроку\n/leaders\tЛидеры и заместители организаций\n/members\tУчастники организации онлайн\n/transfer\tПодать заявку на перевод в организацию", !"Закрыть ", !"Назад ");
					}
					case 1:
					{
						return SPD(playerid, 11, 5, !"{EE3366}Коммуникации", !"Команда\tОписание\n/c(all)\tСделать звонок\n/b (/n)\tOOC чат\n/s\tКрикнуть что-то\n/w\tСказать что-то шёпотом\n/r\tРация организации и основной работы\n/d\tРация департамента\n/rr (/rb)\tOOC рация организации и основной работы\n/dd (/db)\tOOC рация департамента\n/do\tДействие от 3-го лица\n/me\tДействие игрока\n/vm\tВыдать мут голосового чата игроку\n/try\tПопытка действия\n/gov\tЗапланировать собеседование\n/sms\tОтправить SMS\n/todo\tДействие с сообщением\n/unvm\tСнять мут голосового чата у игрока\n/phone\tМеню телефона", !"Закрыть ", !"Назад ");
					}
					case 2:
					{
						return SPD(playerid, 11, 5, !"{EE3366}Бизнес и АЗС", !"Команда\tОписание\n/seller\tВыбрать продавца [бизнес]\n{66CC66}/station\t{66CC66}Меню АЗС\n{66CC66}/business\t{66CC66}Меню бизнеса\n/buystation\tКупить АЗС\n/buybusiness\tКупить бизнес", !"Закрыть ", !"Назад ");
					}
					case 3:
					{
						return SPD(playerid, 11, 5, !"{EE3366}Основные работы ", !"Работа\tКоманда\tОписание\nАвтомеханик\t/repair\tОтремонтировать транспорт\nАвтомеханик\t/accept\tПринять вызов\nАвтомеханик\t/reflip\tПеревернуть транспорт\nРазвозчик\t/c(arrier)info\tИнформация о рабочем транспорте развозчиков", !"Закрыть ", !"Назад ");
					}
					case 4:
					{
						return SPD(playerid, 11, 2, !"{EE3366}Команды организаций ", !"1. БЦРБ\n2. Войсковая часть\n3. Полиция\n4. ОПГ", !"Просмотр ", !"Назад ");
					}
					case 5:
					{
						return SPD(playerid, 11, 5, !"{EE3366}Лидеры и заместители ", !"Команда\tОписание\n/l\tРация лидеров\n/ll (/lb)\tOOC рация лидеров\n/bl\tЧёрный список организации\n/lname\tНайти игрока по старому никнейму\n/twarn\tВыдать выговор\n/clead\tНазначить на должность смотрящего за стрелой\n/invite\tПринять игрока в организацию\n/setskin\tИзменить форму игрока\n/setrang\tИзменить ранг игрока\n/untwarn\tСнять выговор\n/uninvite\tУволить игрока из организации\n/offtwarn\tВыдать выговор оффлайн\n/setgroup\tИзменить группу игрока\n/accessint\tРазрешать вход в интерьер правительства\n/transfers\tСписок заявок на перевод\n/promotion\tУзнать информацию о заданиях игрока\n/offuntwarn\tСнять выговор оффлайн\n/allmembers\tПоказать всех участников организации\n/uninviteall\tУволить всех игроков из организации\n/uninviteoff\tУволить оффлайн игрока из организации\n/offpromotion\tУзнать информацию о заданиях игрока оффлайн", !"Закрыть ", !"Назад ");
					}
				}
			}
		}
		case dStats:
		{
			if(response) return 1;
			if(!response) callcmd::menu(playerid);
		}
		case dActivePunishment:
		{
			if(response) return 1;
			if(!response) callcmd::menu(playerid);
		}
		case dBlackListMenu:
		{
			if(response) return 1;
			if(!response) callcmd::menu(playerid);
		}
		case dResources:
		{
			if(response) return 1;
			if(!response) callcmd::menu(playerid);
		}
		case dChangeName:
		{
			if(response) return 1;
			if(!response) callcmd::menu(playerid);
		}
		case dHotKeys:
		{
			if(response) return 1;
			if(!response) callcmd::menu(playerid);
		}
		case dSettings:
		{
			if(response) return 1;
			if(!response) callcmd::menu(playerid);
		}
		case dDonate:
		{
			if(response) return 1;
			if(!response) callcmd::menu(playerid);
		}
		case dRules: // открытие ссылки
		{
			if(response) return 1;
			if(!response) return 1;
		}
		case dHelp:
		{
			if(!response) return callcmd::menu(playerid);
			if(response) 
			{
			    switch(listitem) 
				{
			        case 0: 
					{
						SPD(playerid, dHelpQuestions, DIALOG_STYLE_INPUT, !"{EE3366}Вопрос или жалоба", !"\
						{FFFFFF}Введите сообщение для игровых мастеров. Пишите кратко и по делу.\n\
						Перед тем, как задать вопрос, проверьте, нет ли ответа в меню помощи - {EE3366}/help\n\
						{696969}Обратите внимание: за оффтоп Вы можете получить блокировку чата", !"Далее", !"Отмена");
			        }
			        case 1: 
					{
						SPD(playerid, dHelpComplaints, DIALOG_STYLE_INPUT, !"{EE3366}Вопрос или жалоба", !"\
						{FFFFFF}Введите сообщение для игровых мастеров. Пишите кратко и по делу.\n\
						Перед тем, как задать вопрос, проверьте, нет ли ответа в меню помощи - {EE3366}/help\n\
						{696969}Обратите внимание: за оффтоп Вы можете получить блокировку чата", !"Далее", !"Отмена");
			        }
			    }
			}
		}
		case dHelpQuestions:
  		{
  		    if(!response) return callcmd::menu(playerid);
   			if(response)
   			{
   			    if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);

  				if strlen(inputtextsave) < 1 || strlen(inputtextsave) > 100 *then 
					return SCM(playerid, COLOR_GREY, !"Не менее 1 и не более 100 символов"), ShowHelpDialog(playerid);

   				SAMF(COLOR_LIGHTYELLOW, "Вопрос от %s[%d]:{FFFFFF} %s", PN(playerid), playerid, inputtextsave);
				SCMF(playerid, COLOR_LIGHTYELLOW, "Вопрос от %s[%d]:{FFFFFF} %s", PN(playerid), playerid, inputtextsave);

				SetPVarInt(playerid, !"report", Global_Time + 60);
			}
    	}
		case dHelpComplaints:
  		{
  		    if(!response) return callcmd::menu(playerid);
   			if(response)
   			{
				if PI[playerid][pMuteTime] *then return SendMuteMessage(playerid);

  				if strlen(inputtextsave) < 1 || strlen(inputtextsave) > 100 *then 
					return SCM(playerid, COLOR_GREY, !"Не менее 1 и не более 100 символов"), ShowHelpDialog(playerid);

	   			SAMF(COLOR_REPORT, "Жалоба от %s[%d]:{FFFFFF} %s", PN(playerid), playerid, inputtextsave);
				SCMF(playerid,COLOR_REPORT, "Жалоба от %s[%d]:{FFFFFF} %s", PN(playerid), playerid, inputtextsave);
				SCM(playerid, COLOR_REPORT, !"Вы можете заблокировать голосовой чат игрока {FFFF99}O{FF8877}");

				SetPVarInt(playerid, !"report", Global_Time + 60);
			}
    	}
		case dGPS:
		{
			if(!response) return 1;
   			if(response)
   			{
				switch(listitem)
				{
					case 0:
					{
						SPD(playerid, dGPSInfo, 0, !"{EE3366}Информация", !"{FFFFFF}Чтобы отключить навигатор зайдите в раздел Карта (ESC) и нажмите ПКМ.\n\nИспользуйте диалог или команду /gps с номером категории и места.\n{FFFF99}Например: /gps 3 6 {FFFFFF}(ввод места в разделе 'Бизнесы' станет ID бизнеса)", !"Закрыть", !"Назад");
					}
					case 1..7:
					{
						listitem = listitem - 1;

						global_str[0] = EOS;

						for (new i = 0; i < GPS_Counts[listitem]; i++) 
						{
							strcat(global_str, GPS_Items[listitem][i]);
    						strcat(global_str, "\n");
						}

						pTemp[playerid][dialogListItem] = listitem;
						
						new tempStr[30];
						f(tempStr, sizeof(tempStr), "{EE3366}%s", GPS_Categories[listitem]);

						f(global_str, 1048, "Место\tРасположение\n%s", global_str);

						SPD(playerid, dGPSSub, 5, tempStr, global_str, !"Отметить", !"Назад");
					}
					case 8..13:
					{
						SCM(playerid, -1, !"soon");
					}
					case 14:
					{
						pTemp[playerid][pMarkerX] =
						pTemp[playerid][pMarkerY] = 
						pTemp[playerid][pMarkerZ] = 0.0;

						return DisablePlayerCheckpoint(playerid);
					}
				}
			}
		}
		case dGPSInfo:
		{
			if(!response) return callcmd::gps(playerid, "");
   			if(response) return 1;
		}
		case dGPSSub:
		{
			if(!response) return callcmd::gps(playerid, "");
   			if(response)
   			{
				new cat = pTemp[playerid][dialogListItem];
				new item = listitem;

				if (item < GPS_Counts[cat]) 
				{
					SetPlayerCheckpoint(playerid, GPS_Positions[cat][item][0], GPS_Positions[cat][item][1], GPS_Positions[cat][item][2], 3.0);
					SCMF(playerid, -1, "Установлен маршрут: %s", GPS_Items[cat][item]);

					pTemp[playerid][pMarker] = 1;
					pTemp[playerid][pMarkerX] = GPS_Positions[cat][item][0];
					pTemp[playerid][pMarkerY] = GPS_Positions[cat][item][1];
					pTemp[playerid][pMarkerZ] = GPS_Positions[cat][item][2];
				}
				
				pTemp[playerid][dialogListItem] = -1;
				return 1;
			}
		}
    }
    return 1;
}

CMD:gps(playerid, params[])
{
    new cat, item;

    if (sscanf(params, "dd", cat, item)) {

		if(cat >= 1 && cat <= sizeof(GPS_Categories) && item < GPS_Counts[cat - 1]) 
			return SCMF(playerid, COLOR_LIGHTGREY, "Номер категории от 1 до %d", GPS_Counts[cat - 1]);

        global_str[0] = EOS;

        for (new i = 0; i < sizeof(GPS_Categories); i++) {
            format(global_str, 256, "%s%d. %s\n", global_str, i + 1, GPS_Categories[i]);
        }
		

        SPDF(playerid, dGPS, DIALOG_STYLE_LIST, !"{EE3366}Навигатор", !"Далее", !"Закрыть", "{FFFF99}Информация\n\
		%s{66CC99}8. Найти АЗС\n\
		{66CC99}9. Найти банкомат\n\
		{66CC99}10. Найти автобусную остановку\n\
		{66CC99}11. Найти столовую\n\
		{66CC99}12. Найти станцию зарядки\n\
		{66CC99}13. Найти магазин талисманов\n\
		{888888}14. Отключить навигатор", global_str);
        return 1;
    }

    if (cat >= 1 && cat <= sizeof(GPS_Categories) && item >= 1 && item <= GPS_Counts[cat - 1]) 
	{
        cat--; item--;
        SetPlayerCheckpoint(playerid, GPS_Positions[cat][item][0], GPS_Positions[cat][item][1], GPS_Positions[cat][item][2], 3.0);
        SCM(playerid, -1, !"Местоположение отмечено на карте.");
    } 

    return 1;
}