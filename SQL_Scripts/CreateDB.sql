CREATE DATABASE `CHARM` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE CHARM;

CREATE TABLE `Dongle` (
  `total` double DEFAULT NULL,
  `logtime` datetime NOT NULL,
  PRIMARY KEY (logtime)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `Dongle_day` (
  `logdate` date NOT NULL,
  `total` double DEFAULT NULL,
  PRIMARY KEY (logdate)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `Electrical` (
  `logtime` datetime NOT NULL,
  `value` double DEFAULT NULL,
  PRIMARY KEY (logtime)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `Electrical_day` (
  `logdate` date NOT NULL,
  `total` double DEFAULT NULL,
  PRIMARY KEY (logdate)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `Modbus` (
  `logtime` datetime NOT NULL,
  `value` double DEFAULT NULL,
  PRIMARY KEY (logtime)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `Modbus_day` (
  `logdate` date NOT NULL,
  `total` double DEFAULT NULL,
  PRIMARY KEY (logdate)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `User` (
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  PRIMARY KEY (username)
);