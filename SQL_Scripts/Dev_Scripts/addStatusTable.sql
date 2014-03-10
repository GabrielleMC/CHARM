USE testCHARM;

CREATE TABLE `Status` (
	`device_id` int NOT NULL,
	`battery_level` int,
	`current_state` varchar(255),
	PRIMARY KEY (device_id)
);