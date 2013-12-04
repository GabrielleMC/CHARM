create database CHARM;
use CHARM;

create table Systems(
	sysName varchar(255),
	sysStatus varchar(50),
	system_type varchar(255),
	logging_interval int,
	data_unit varchar(50),
	primary key(sysName)
);
create table Electrical(
	logDate date,
	logTime time,
	logValue double,
	primary key(logDate, logTime)
);

create table Electrical_Day(
	logDate date,
	logAvg double,
	primary key(logDate)
);

create table HVAC(
	logDate date,
	logTime time,
	logValue double,
	primary key(logDate, logTime)
);

create table HVAC_Day(
	logDate date,
	logAvg double,
	primary key(logDate)
);

create table Dongle(
	logDate date,
	logTime time,
	logValue double,
	primary key(logDate, logTime)
);

create table Dongle_Day(
	logDate date,
	logAvg double,
	primary key(logDate)
);

	