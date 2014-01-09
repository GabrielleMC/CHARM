CREATE USER 'CHARM'@'localhost' IDENTIFIED BY '5*Hotel';
GRANT ALL ON CHARM.* TO 'CHARM'@'localhost' IDENTIFIED BY '5*Hotel';

USE CHARM;
INSERT INTO User (username, password) VALUES ("project", "PAARrW8xhJhdM");

