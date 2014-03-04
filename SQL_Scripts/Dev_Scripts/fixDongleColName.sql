#You only need to run this if you ran CreateDB before January 22, 2014. Otherwise, your value column in the dongle table is correctly named
#SQL script to fix dongle value name to be consistent with other tables.

USE CHARM;

ALTER TABLE dongle DROP COLUMN total;
ALTER TABLE dongle ADD value double DEFAULT NULL;