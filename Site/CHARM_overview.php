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
	
	date_default_timezone_set("America/Edmonton");
	//$date = "2014-02-05"; test date 
	$date = Date("Y-m-d");
	
	//Code to check for missing devices and low batteries goes here 
	$num_devices = mysql_query("SELECT device_id FROM Status");
	while ($row = mysql_fetch_row($num_devices)){
		$i = $row[0];
		$stat_data_r = mysql_query("SELECT battery_level, current_state FROM Status WHERE device_id = $row[0]");
		$stat_data = mysql_fetch_row($stat_data_r);
		if ($stat_data[0] <= 20){
			echo "<div class=\"ui-state-highlight ui-corner-all\" style=\"padding: 0 .7em;\"><p><span class=\"ui-icon ui-icon-alert\" style=\"float: left; margin-right: .3em;\"></span><strong>Alert: </strong>Current battery level for device $i is $stat_data[0]</p></div>";
		}
		else if ($stat_data[1] == 1){
			echo "<div class=\"ui-state-error ui-corner-all\" style=\"padding: 0 .7em;\"><p><span class=\"ui-icon ui-icon-alert\" style=\"float: left; margin-right: .3em;\"></span><strong>Alert: </strong>Device $i is missing</p></div>";
		}
		else if ($stat_data[1] == 2){
			echo "<div class=\"ui-state-error ui-corner-all\" style=\"padding: 0 .7em;\"><p><span class=\"ui-icon ui-icon-alert\" style=\"float: left; margin-right: .3em;\"></span><strong>Alert: </strong>Device $i has reached critical battery level and was shut down</p></div>";
		}
	}
	
	
	$result = mysql_query("SELECT device_id AS devices FROM Status");
	$day = array();
	$week = array();
	$month = array();
	while ($row = mysql_fetch_row($result)){
		$i = $row[0];
		$table = "Device_$i";
		$result1 = mysql_query("SELECT AVG(value) FROM $table WHERE DATE(logtime) = '$date'");
		$row1 = mysql_fetch_row($result1);
		$day[$i] = $row1[0];	
		$result2 = mysql_query("SELECT AVG(value) FROM $table  WHERE DATE(logtime) >= DATE(DATE_SUB('$date', INTERVAL 7 DAY))");
		$row2 = mysql_fetch_row($result2);
		$week[$i] = $row2[0];
		$result3 = mysql_query("SELECT AVG(value) FROM $table WHERE DATE(logtime) >= DATE(DATE_SUB('$date', INTERVAL 30 DAY))");
		$row3 = mysql_fetch_row($result3);
		$month[$i] = $row3[0];
	}

	echo "<p style = \"color:#2191C0;font-weight:bold\">Last 24 hours - Average Readings</p>";
	echo "<table border=\"1\">";
	$result = mysql_query("SELECT device_id AS devices FROM Status");
	$it = 0;
	while ($row = mysql_fetch_row($result)){
		echo "<tr>";
		$i = $row[0];
		$table = "Device_$i";
		echo "<td>$table</td>";
		echo "<td>$day[$it]</td>";
		echo "</tr>";
		$it++;
	}
	echo "</table>";
	echo "<br>";
	echo "<p style = \"color:#2191C0;font-weight:bold\">Last Week - Average Readings</p>";
	echo "<table border=\"1\">";
	$result = mysql_query("SELECT device_id AS devices FROM Status");
	$it = 0;
	while ($row = mysql_fetch_row($result)){
		echo "<tr>";
		$i = $row[0];
		$table = "Device_$i";
		echo "<td>$table</td>";
		echo "<td>$week[$it]</td>";
		echo "</tr>";
		$it++;
	}
	echo "</table>";
	echo "<br>";
	echo "<p style = \"color:#2191C0;font-weight:bold\">Last Month - Average Readings</p>";
	echo "<table border=\"1\">";
	$result = mysql_query("SELECT device_id AS devices FROM Status");
	$it = 0;
	while ($row = mysql_fetch_array($result)){
		echo "<tr>";
		$i = $row[0];
		$table = "Device_$i";
		echo "<td>$table</td>";
		echo "<td>$month[$it]</td>";
		echo "</tr>";
		$it++;
	}
	echo "</table>";
?>
