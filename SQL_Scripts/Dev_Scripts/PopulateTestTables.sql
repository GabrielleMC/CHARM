USE testCHARM;
DELIMITER $$

DROP PROCEDURE IF EXISTS populate $$
CREATE PROCEDURE populate()
BEGIN
	DECLARE i INT DEFAULT 0;
	DECLARE i1 INT DEFAULT 0;
	DECLARE testtime DATETIME DEFAULT '2014-01-01 00:01:00';
	DECLARE testdate DATE DEFAULT '2014-01-01';

	WHILE i < 3500 DO
		INSERT INTO `t1`(`logtime`, `value`) VALUES ((SELECT TIMESTAMPADD(MINUTE, (30*i), testtime)), (FLOOR(RAND() * 191) + 10));
		INSERT INTO `t2`(`logtime`, `value`) VALUES ((SELECT TIMESTAMPADD(MINUTE, (30*i), testtime)), (FLOOR(RAND() * 191) + 10));
		INSERT INTO `t3`(`logtime`, `value`) VALUES ((SELECT TIMESTAMPADD(MINUTE, (30*i), testtime)), (FLOOR(RAND() * 191) + 10));		
		SET i = i + 1;
	END WHILE;

	WHILE i1 < 73 DO
		INSERT INTO `t1_day` (`logdate`, `total`) VALUES (testdate, (SELECT AVG(`value`) FROM t1  WHERE DATE(`logtime`) = testdate));
		INSERT INTO `t2_day` (`logdate`, `total`) VALUES (testdate, (SELECT AVG(`value`) FROM t2 WHERE DATE(`logtime`) = testdate));
		INSERT INTO `t3_day` (`logdate`, `total`) VALUES (testdate, (SELECT SUM(`value`) FROM t3 WHERE DATE(`logtime`) = testdate));
		SET testdate = TIMESTAMPADD(DAY, 1, testdate);
		SET i1 = i1 + 1;
	END WHILE;
END

