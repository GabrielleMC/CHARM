CREATE DATABASE `CHARM` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE CHARM;

CREATE TABLE `Device_0` (
  `value` double DEFAULT NULL,
  `logtime` datetime NOT NULL,
  PRIMARY KEY (logtime)
);

CREATE TABLE `Device_0_day` (
  `logdate` date NOT NULL,
  `total` double DEFAULT NULL,
  PRIMARY KEY (logdate)
);

CREATE TABLE `Device_1` (
  `logtime` datetime NOT NULL,
  `value` double DEFAULT NULL,
  PRIMARY KEY (logtime)
);

CREATE TABLE `Device_1_Day` (
  `logdate` date NOT NULL,
  `total` double DEFAULT NULL,
  PRIMARY KEY (logdate)
);

CREATE TABLE `User` (
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  PRIMARY KEY (username)
);

CREATE TABLE `Status` (
	`device_id` int NOT NULL,
	`battery_level` int,
	`current_state` varchar(255),
	PRIMARY KEY (device_id)
);

CREATE USER 'CHARM'@'localhost' IDENTIFIED BY '5*Hotel';
GRANT ALL ON CHARM.* TO 'CHARM'@'localhost' IDENTIFIED BY '5*Hotel';
INSERT INTO User (username, password) VALUES ("project", "PAARrW8xhJhdM");