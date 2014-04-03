<?php
	session_start();
	if (isset($_SESSION['auth'])) {
    	if ($_SESSION["auth"] != 1) {
        	header("Location: CHARMindex.php");
    }
	} else {
    	header("Location: CHARMindex.php");
	}
	$host = "localhost";
	$user = "CHARM";
	$pass = "5*Hotel";
	mysql_connect($host, $user, $pass) or die("Could not connect: " . mysql_error());
	mysql_select_db("testCHARM");
	
	$id = (mysql_real_escape_string($_POST['devices']));
	
	$result = mysql_query("DROP TABLE Device_$id");
	$result = mysql_query("DROP TABLE Device_Day_$id");
	$result = mysql_query("DELETE FROM Status WHERE device_id = $id");
	
	mysql_free_result($result);
	?>