CREATE DATABASE `testCHARM` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE testCHARM;

CREATE TABLE `t1` (
  `total` double DEFAULT NULL,
  `logtime` datetime NOT NULL,
  PRIMARY KEY (logtime)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `t1_day` (
  `logdate` date NOT NULL,
  `total` double DEFAULT NULL,
  PRIMARY KEY (logdate)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `t2` (
  `logtime` datetime NOT NULL,
  `value` double DEFAULT NULL,
  PRIMARY KEY (logtime)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `t2_day` (
  `logdate` date NOT NULL,
  `total` double DEFAULT NULL,
  PRIMARY KEY (logdate)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `t3` (
  `logtime` datetime NOT NULL,
  `value` double DEFAULT NULL,
  PRIMARY KEY (logtime)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `t3_day` (
  `logdate` date NOT NULL,
  `total` double DEFAULT NULL,
  PRIMARY KEY (logdate)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
