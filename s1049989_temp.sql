-- phpMyAdmin SQL Dump
-- version 5.2.2
-- https://www.phpmyadmin.net/
--
-- Хост: localhost:3306
-- Время создания: Окт 25 2025 г., 14:19
-- Версия сервера: 10.6.21-MariaDB-cll-lve-log
-- Версия PHP: 8.1.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `s1049989_temp`
--

-- --------------------------------------------------------

--
-- Структура таблицы `accounts`
--

CREATE TABLE `accounts` (
  `ID` int(11) NOT NULL,
  `Name` varchar(24) NOT NULL,
  `Admin` int(11) DEFAULT 0,
  `RegIP` varchar(16) DEFAULT '0.0.0.0',
  `OldIP` varchar(16) DEFAULT '0.0.0.0',
  `Referal` varchar(24) DEFAULT '',
  `Level` int(11) DEFAULT 1,
  `Exp` int(11) DEFAULT 0,
  `Sex` int(11) DEFAULT 0,
  `Mail` varchar(50) DEFAULT '',
  `Money` int(11) DEFAULT 0,
  `Health` float DEFAULT 100,
  `Armour` float DEFAULT 0,
  `Mute` int(11) DEFAULT 0,
  `MuteTime` int(11) DEFAULT 0,
  `Warns` int(11) DEFAULT 0,
  `Jail` int(11) DEFAULT 0,
  `JailTime` int(11) DEFAULT 0,
  `Hospital` int(11) DEFAULT 0,
  `Skin` int(11) DEFAULT 0,
  `Wanted` int(11) DEFAULT 0,
  `AdminNumber` int(11) DEFAULT 0,
  `Leader` int(11) DEFAULT 0,
  `Member` int(11) DEFAULT 0,
  `OrgSkin` int(11) DEFAULT 0,
  `Rang` int(11) DEFAULT 0,
  `SpawnSetting` int(11) DEFAULT 0,
  `Demorgan` int(11) DEFAULT 0,
  `ShowFPS` int(11) DEFAULT 0,
  `ShowNameTags` int(11) DEFAULT 1,
  `CinemaMode` int(11) DEFAULT 0,
  `VoiceChat` int(11) DEFAULT 1,
  `ShowRain` int(11) DEFAULT 1,
  `DamageMP3` int(11) DEFAULT 0,
  `VMute` int(11) DEFAULT 0,
  `VMuteTime` int(11) DEFAULT 0,
  `HouseKey` int(11) DEFAULT -1,
  `VKonktakeID` int(11) DEFAULT 0,
  `DayOnline` int(11) DEFAULT 0,
  `DayAFK` int(11) DEFAULT 0,
  `GlobalOnline` int(11) DEFAULT 0,
  `GlobalAFK` int(11) DEFAULT 0,
  `WarnsTimer1` int(11) DEFAULT 0,
  `WarnsTimer2` int(11) DEFAULT 0,
  `WarnsTimer3` int(11) DEFAULT 0,
  `Moder` int(11) DEFAULT 0,
  `PlayedTime` int(11) DEFAULT 0,
  `Respect` int(11) DEFAULT 0,
  `Salary` int(11) DEFAULT 0,
  `OnlineStatus` int(11) DEFAULT 0,
  `PlayerID` int(11) DEFAULT -1,
  `LastLogin` datetime DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `admin`
--

CREATE TABLE `admin` (
  `AccountID` int(11) NOT NULL,
  `admInfoNewPlayer` int(11) DEFAULT 1,
  `admKillList` int(11) DEFAULT 1,
  `admIP` int(11) DEFAULT 1,
  `admACMsg` int(11) DEFAULT 1,
  `admJoin` int(11) DEFAULT 1,
  `admFlySpeed` int(11) DEFAULT 125,
  `admHide` int(11) DEFAULT 0,
  `admShowReport` int(11) DEFAULT 1,
  `admGethere` int(11) DEFAULT 1,
  `admGoto` int(11) DEFAULT 1
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `banip`
--

CREATE TABLE `banip` (
  `ID` int(11) NOT NULL,
  `IP` varchar(16) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `banpc`
--

CREATE TABLE `banpc` (
  `ID` int(11) NOT NULL,
  `NickName` varchar(24) NOT NULL,
  `HWID` varchar(64) DEFAULT '',
  `UUID` varchar(64) DEFAULT '',
  `BanCode` varchar(64) DEFAULT '',
  `Date` datetime DEFAULT current_timestamp()
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `bans`
--

CREATE TABLE `bans` (
  `ID` int(11) NOT NULL,
  `Name` varchar(24) NOT NULL,
  `GameMaster` varchar(24) DEFAULT '',
  `BanSeconds` bigint(20) DEFAULT 0,
  `BanReason` varchar(128) DEFAULT '',
  `Date` datetime DEFAULT current_timestamp()
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `client`
--

CREATE TABLE `client` (
  `ID` int(11) NOT NULL,
  `NickName` varchar(24) NOT NULL,
  `UUID` varchar(70) DEFAULT '',
  `HWID` varchar(35) DEFAULT '',
  `Path` varchar(150) DEFAULT '',
  `Used` tinyint(1) DEFAULT 0,
  `Date` datetime DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `houses`
--

CREATE TABLE `houses` (
  `ID` int(11) NOT NULL,
  `Enter_X` float DEFAULT 0,
  `Enter_Y` float DEFAULT 0,
  `Enter_Z` float DEFAULT 0,
  `Exit_X` float DEFAULT 0,
  `Exit_Y` float DEFAULT 0,
  `Exit_Z` float DEFAULT 0,
  `Owner` varchar(24) DEFAULT 'The State',
  `Level` int(11) DEFAULT 1,
  `Cost` int(11) DEFAULT 0,
  `Lock` tinyint(1) DEFAULT 0,
  `Interior` int(11) DEFAULT 0,
  `Money` int(11) DEFAULT 0,
  `Drugs` int(11) DEFAULT 0,
  `Ammo` int(11) DEFAULT 0,
  `Skin_1` int(11) DEFAULT 0,
  `Skin_2` int(11) DEFAULT 0,
  `Skin_3` int(11) DEFAULT 0,
  `Nalog` int(11) DEFAULT 0,
  `Klass` int(11) DEFAULT 0,
  `Med` int(11) DEFAULT 0,
  `Days` int(11) DEFAULT 0,
  `Location` int(11) DEFAULT 0,
  `ParkPlaces` int(11) DEFAULT 0,
  `Car_X` float DEFAULT 0,
  `Car_Y` float DEFAULT 0,
  `Car_Z` float DEFAULT 0,
  `Grant` int(11) DEFAULT 0,
  `Fridge` int(11) DEFAULT 0,
  `Closet` int(11) DEFAULT 0,
  `Boombox` int(11) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `accounts`
--
ALTER TABLE `accounts`
  ADD PRIMARY KEY (`ID`);

--
-- Индексы таблицы `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`AccountID`);

--
-- Индексы таблицы `banip`
--
ALTER TABLE `banip`
  ADD PRIMARY KEY (`ID`),
  ADD UNIQUE KEY `IP` (`IP`);

--
-- Индексы таблицы `banpc`
--
ALTER TABLE `banpc`
  ADD PRIMARY KEY (`ID`);

--
-- Индексы таблицы `bans`
--
ALTER TABLE `bans`
  ADD PRIMARY KEY (`ID`);

--
-- Индексы таблицы `client`
--
ALTER TABLE `client`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `NickName` (`NickName`),
  ADD KEY `UUID` (`UUID`),
  ADD KEY `HWID` (`HWID`);

--
-- Индексы таблицы `houses`
--
ALTER TABLE `houses`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `accounts`
--
ALTER TABLE `accounts`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `banip`
--
ALTER TABLE `banip`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `banpc`
--
ALTER TABLE `banpc`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `bans`
--
ALTER TABLE `bans`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `client`
--
ALTER TABLE `client`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `houses`
--
ALTER TABLE `houses`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
