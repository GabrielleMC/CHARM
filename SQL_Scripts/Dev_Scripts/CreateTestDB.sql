CREATE DATABASE `testCHARM` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE testCHARM;

CREATE TABLE `t1` (
  `value` double DEFAULT NULL,
  `logtime` datetime NOT NULL,
  PRIMARY KEY (logtime)
); 

CREATE TABLE `t1_day` (
  `logdate` date NOT NULL,
  `total` double DEFAULT NULL,
  PRIMARY KEY (logdate)
); 

CREATE TABLE `t2` (
  `logtime` datetime NOT NULL,
  `value` double DEFAULT NULL,
  PRIMARY KEY (logtime)
);

CREATE TABLE `t2_day` (
  `logdate` date NOT NULL,
  `total` double DEFAULT NULL,
  PRIMARY KEY (logdate)
);

CREATE TABLE `t3` (
  `logtime` datetime NOT NULL,
  `value` double DEFAULT NULL,
  PRIMARY KEY (logtime)
);

CREATE TABLE `t3_day` (
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

GRANT ALL ON testCHARM.* TO 'CHARM'@'localhost' IDENTIFIED BY '5*Hotel';
INSERT INTO User (username, password) VALUES ("project", "PAARrW8xhJhdM");
