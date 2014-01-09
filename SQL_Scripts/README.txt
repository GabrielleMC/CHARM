Read me first!

Setting up the CHARM Database. 

You'll need MySQLServer (http://dev.mysql.com/downloads/mysql/) in order to run these scripts. For ease of use, I would advise getting MySQL Workbench as well (http://dev.mysql.com/downloads/tools/workbench/). 

In order to run the scripts in MySQL workbench, you'll simply have to set up a connection to your server. Then, run CreateDB.sql before running AddUser.sql. CreateDB creates our sample CHARM database, and AddUser sets up both the site user and the SQL user that we'll use to access the tables. 

If I make any changes to tables, etc, scripts to update those will be posted here in Dev Scripts. Dev Scripts is for stuff we won't want to include in the final build (I'll also be modifying creation scripts, etc, as needed, but for development purposes it'll be far easier to run scripts to modify the database rather than having to rebuild it/drop a table every time :))

-Gaby