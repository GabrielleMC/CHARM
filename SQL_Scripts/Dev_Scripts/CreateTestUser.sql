GRANT ALL ON testCHARM.* TO 'CHARM'@'localhost' IDENTIFIED BY '5*Hotel';

USE testCHARM; 

CREATE TABLE `User` (
  `username` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  PRIMARY KEY (username)
);
