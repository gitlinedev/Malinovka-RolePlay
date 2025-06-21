//======================[ Anti - Cheat ]======================//
#define AC_MAX_CODES 53 // Количество кодов анти-чита (на данный момент их 53)
#define AC_MAX_CODE_LENGTH (3 + 1) // Максимальное количество символов в "коде" анти-чита (001/002/003, etc.)
#define AC_MAX_CODE_NAME_LENGTH (33 + 1) // Максимальное количество символов в полном названии чита, за который отвечает какой-либо код

#define AC_MAX_TRIGGER_TYPES 3 // Количество типов срабатываний (наказаний) анти-чита. По мере добавления типов срабатываний (наказаний), увеличивайте данное значение.
#define AC_MAX_TRIGGER_TYPE_NAME_LENGTH (8 + 1) // Максимальное количество символов в названии типа срабатывания (наказания) анти-чита

#define AC_GLOBAL_TRIGGER_TYPE_PLAYER 0
#define AC_GLOBAL_TRIGGER_TYPE_IP 1

// Типы срабатываний объявлены макросами, чтобы было проще ориентироваться в OnCheatDetected.
#define AC_CODE_TRIGGER_TYPE_DISABLED 0 // AC_CODE_TRIGGER_TYPE_DISABLED - Тип наказания: Отключён
#define AC_CODE_TRIGGER_TYPE_WARNING 1 // AC_CODE_TRIGGER_TYPE_WARNING - Тип наказания: Warning
#define AC_CODE_TRIGGER_TYPE_KICK 2 // AC_CODE_TRIGGER_TYPE_KICK - Тип наказания: Kick

#define AC_TRIGGER_ANTIFLOOD_TIME 20 // Время для анти-флуда срабатываниями (в секундах)
//======================[ Anti - Cheat ]======================//

stock AC_Kick(playerid, code) return SAMF(COLOR_ADMINCHAT, "[Анти-чит (Особый варнинг)] %s[%d] (op-code: #%d)", PN(playerid), playerid, code);


static const AC_CODE_NAME[AC_MAX_CODES][AC_MAX_CODE_NAME_LENGTH] = {
    "AirBreak (пешком)",
    "AirBreak (в транспорте)",
    "Телепорт (пешком)",
    "Телепорт (в транспорте)",
    "Телепорт между транспортом",
    "Телепорт транспорта к себе",
    "Телепорт к предмету (pickup)",
    "FlyHack (пешком)",
    "FlyHack (в транспорте)",
    "SpeedHack (пешком)",
    "SpeedHack (в транспорте)",
    "Жизни игрока (в транспорте)",
    "Жизни игрока",
    "Взлом брони",
    "Взлом денег",
    "Взлом оружия",
    "Взлом патронов ++",
    "Взлом патронов (бесконечный)",
    "Неопределённый взлом",
    "Бессмертие (пешком)",
    "Бессмертие (в транспорте)",
    "Невидимость",
    "Подделка лагкомпенсации",
    "Взлом тюнинга",
    "Паркур-мод",
    "Быстрая очередь стрельбы",
    "Быстрая стрельба",
    "Фейковое возрождение",
    "Фейковое убийство",
    "АимБот",
    "Хак бега",
    "Выстрел из автомобиля",
    "Угон автомобиля",
    "Разморозка",
    "Режим призрака (AFK)",
    "Полный автоприцел",
    "Фейковый NPC",
    "Переподключение",
    "Искусственный высокий пинг",
    "Взлом диалога",
    "Взлом песочницы",
    "Ошибка версии клиента",
    "Взлом SR-Rcon",
    "Крашер тюнинга",
    "Крашер сидений",
    "Крашер диалога",
    "Крашер объектов",
    "Крашер оружия",
    "Подключение к одному слоту",
    "Флуд функциями",
    "Флуд сменой мест",
    "DDoS-атака",
    "Удаление кода (NOP)"
};
new AC_CODE_TRIGGER_TYPE[AC_MAX_CODES] = {
    AC_CODE_TRIGGER_TYPE_WARNING, // Airbreak (onfoot)
    AC_CODE_TRIGGER_TYPE_WARNING, // Airbreak (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Teleport (onfoot)
    AC_CODE_TRIGGER_TYPE_WARNING, // Teleport (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Teleport (into/between vehicles)
    AC_CODE_TRIGGER_TYPE_WARNING, // Teleport (vehicle to player)
    AC_CODE_TRIGGER_TYPE_WARNING, // Teleport (pickups)
    AC_CODE_TRIGGER_TYPE_WARNING, // FlyHack (onfoot)
    AC_CODE_TRIGGER_TYPE_WARNING, // FlyHack (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // SpeedHack (onfoot)
    AC_CODE_TRIGGER_TYPE_WARNING, // SpeedHack (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Health hack (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Health hack (onfoot)
    AC_CODE_TRIGGER_TYPE_WARNING, // Armour hack
    AC_CODE_TRIGGER_TYPE_WARNING, // Money hack
    AC_CODE_TRIGGER_TYPE_WARNING, // Weapon hack
    AC_CODE_TRIGGER_TYPE_WARNING, // Ammo hack (add)
    AC_CODE_TRIGGER_TYPE_WARNING, // Ammo hack (infinite)
    AC_CODE_TRIGGER_TYPE_WARNING, // Special actions hack
    AC_CODE_TRIGGER_TYPE_WARNING, // GodMode from bullets (onfoot)
    AC_CODE_TRIGGER_TYPE_WARNING, // GodMode from bullets (in vehicle)
    AC_CODE_TRIGGER_TYPE_WARNING, // Invisible hack
    AC_CODE_TRIGGER_TYPE_WARNING, // Lagcomp-spoof
    AC_CODE_TRIGGER_TYPE_WARNING, // Tuning hack
    AC_CODE_TRIGGER_TYPE_WARNING, // Parkour mod
    AC_CODE_TRIGGER_TYPE_WARNING, // Quick turn
    AC_CODE_TRIGGER_TYPE_WARNING, // Rapid fire
    AC_CODE_TRIGGER_TYPE_WARNING, // FakeSpawn
    AC_CODE_TRIGGER_TYPE_WARNING, // FakeKill
    AC_CODE_TRIGGER_TYPE_WARNING, // Pro Aim
    AC_CODE_TRIGGER_TYPE_WARNING, // CJ run
    AC_CODE_TRIGGER_TYPE_WARNING, // CarShot
    AC_CODE_TRIGGER_TYPE_WARNING, // CarJack
    AC_CODE_TRIGGER_TYPE_WARNING, // UnFreeze
    AC_CODE_TRIGGER_TYPE_WARNING, // AFK Ghost
    AC_CODE_TRIGGER_TYPE_WARNING, // Full Aiming
    AC_CODE_TRIGGER_TYPE_WARNING, // Fake NPC
    AC_CODE_TRIGGER_TYPE_WARNING, // Reconnect
    AC_CODE_TRIGGER_TYPE_WARNING, // High Ping
    AC_CODE_TRIGGER_TYPE_DISABLED, // Dialog Hack
    AC_CODE_TRIGGER_TYPE_WARNING, // Sandbox
    AC_CODE_TRIGGER_TYPE_WARNING, // Invalid Version
    AC_CODE_TRIGGER_TYPE_WARNING, // Rcon hack
    AC_CODE_TRIGGER_TYPE_WARNING, // Tuning crasher
    AC_CODE_TRIGGER_TYPE_WARNING, // Invalid seat crasher
    AC_CODE_TRIGGER_TYPE_WARNING, // Dialog crasher
    AC_CODE_TRIGGER_TYPE_WARNING, // Attached object crasher
    AC_CODE_TRIGGER_TYPE_WARNING, // Weapon crasher
    AC_CODE_TRIGGER_TYPE_WARNING, // Connects to one slot
    AC_CODE_TRIGGER_TYPE_WARNING, // Flood callback functions
    AC_CODE_TRIGGER_TYPE_WARNING, // Flood change seat
    AC_CODE_TRIGGER_TYPE_WARNING, // DDos
    AC_CODE_TRIGGER_TYPE_WARNING // NOP`s
};
public: OnCheatDetected(playerid, const ip_address[], type, code)
{	
    if (!IsPlayerOnline(playerid)) return 0;

    if (pTemp[playerid][ACWarnings] >= 5)
    {
        SCMF(playerid, COLOR_BLACK, "Вы были кикнуты по подозрению в читерстве (#%03d)", code),
        Kick(playerid);
        return 1;
    }
    
    switch AC_CODE_TRIGGER_TYPE[code] do
    {
        case AC_CODE_TRIGGER_TYPE_WARNING:
        {
            pTemp[playerid][ACWarnings]++;
            SAMF(COLOR_ADMINCHAT, "[Анти-чит] Подозрение %s[%d] (#%d/%d: %s).", PN(playerid), playerid, type, code, AC_CODE_NAME[code]);
        }
        case AC_CODE_TRIGGER_TYPE_KICK: 
		{
            SAMF(COLOR_ADMINCHAT, "[Анти-чит] %s[%d] кикнут (%s #%d/%d).", PN(playerid), playerid, AC_CODE_NAME[code], type, code);
			SCMF(playerid, COLOR_BLACK, "Вы были кикнуты по подозрению в читерстве (#%03d)", code);
			return Kick(playerid);
		}
        default: return false;
    }
    return 1;
}
stock AC_OnPlayerKeyStateChange(playerid, newkeys)
{
    if (newkeys & KEY_FIRE)
    {
        new weaponid = GetPlayerWeapon(playerid);
        
        if (weaponid == 38)
        {
            if (PI[playerid][pAdmin] <= 0)
            {
                SCM(playerid, COLOR_BLACK, !"Вы были кикнуты по подозрению в читерстве (#991)");
                return Kick(playerid);
            }
        }
    }
    return 1;
}