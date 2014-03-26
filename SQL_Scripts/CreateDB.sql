CREATE DATABASE `CHARM` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE CHARM;

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