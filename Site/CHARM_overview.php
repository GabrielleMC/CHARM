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
	$num_devices = mysql_query("SELECT MAX(device_id) FROM Status");
	$num_devices_r = mysql_fetch_row($num_devices);
	for ($i = 0; $i <= $num_devices_r[0]; $i++){
		$stat_data_r = mysql_query("SELECT battery_level, current_state FROM Status WHERE device_id = $i");
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
	
	
	$result = mysql_query("SELECT COUNT(device_id) AS devices FROM Status");
	$row = mysql_fetch_row($result);
	$count = $row[0];
	$day = array();
	
	for ($i = 0; $i < $count; $i++){
		$table = "Device_" + i;
		$result1 = mysql_query("SELECT AVG(value) FROM $table WHERE DATE(logtime) = '$date'");
		$row1 = mysql_fetch_row($result1);
		$day[$i] = $row1[0];	
	}
	
	$result2 = mysql_query("SELECT SUM(value) AS test3 FROM t3 WHERE DATE(logtime) = '$date'");
	$row2 = mysql_fetch_row($result2);
	$result3 = mysql_query("SELECT AVG(total) FROM t1_day WHERE logdate >= DATE(DATE_SUB('$date', INTERVAL 7 DAY))");
	$row3 = mysql_fetch_row($result3);
	$result4 = mysql_query("SELECT AVG(total) FROM t2_day WHERE logdate >= DATE(DATE_SUB('$date', INTERVAL 7 DAY))");
	$row4 = mysql_fetch_row($result4);
	$result5 = mysql_query("SELECT AVG(total) FROM t3_day WHERE logdate >= DATE(DATE_SUB('$date', INTERVAL 7 DAY))");
	$row5 = mysql_fetch_row($result5);
	$result6 = mysql_query("SELECT AVG(total) FROM t1_day WHERE logdate >= DATE(DATE_SUB('$date', INTERVAL 30 DAY))");
	$row6 = mysql_fetch_row($result6);
	$result7 = mysql_query("SELECT AVG(total) FROM t2_day WHERE logdate >= DATE(DATE_SUB('$date', INTERVAL 30 DAY))");
	$row7 = mysql_fetch_row($result7);
	$result8 = mysql_query("SELECT AVG(total) FROM t3_day WHERE logdate >= DATE(DATE_SUB('$date', INTERVAL 30 DAY))");
	$row8 = mysql_fetch_row($result8);

	echo "<p style = \"color:#2191C0;font-weight:bold\">Last 24 hours</p>";
	echo "<table border=\"1\">";
	echo "<tr>";
	echo "<td>Average Power Used (W)</td>";
	echo "<td>" . $row[0] . "</td>";
	echo "</tr>";
	echo "<tr>";
	echo "<td>Average current Recorded (A)</td>";
	echo "<td>" . $row1[0] . "</td>";
	echo "</tr>";
	echo "<tr>";
	echo "<td>Total Current Recorded (A)</td>";
	echo "<td>" . $row2[0] . "</td>";
	echo "</tr>";
	echo "</table>";
	echo "<br>";
	echo "<p style = \"color:#2191C0;font-weight:bold\">Last Week</p>";
	echo "<table border=\"1\">";
	echo "<tr>";
	echo "<td>Average Power Used (W)</td>";
	echo "<td>" . $row3[0] . "</td>";
	echo "</tr>";
	echo "<tr>";
	echo "<td>Average current Recorded (A)</td>";
	echo "<td>" . $row4[0] . "</td>";
	echo "</tr>";
	echo "<tr>";
	echo "<td>Average Current Recorded (A)</td>";
	echo "<td>" . $row5[0] . "</td>";
	echo "</tr>";
	echo "</table>";
	echo "<br>";
	echo "<p style = \"color:#2191C0;font-weight:bold\">Last Month</p>";
	echo "<table border=\"1\">";
	echo "<tr>";
	echo "<td>Average Power Used (W)</td>";
	echo "<td>" . $row6[0] . "</td>";
	echo "</tr>";
	echo "<tr>";
	echo "<td>Average Current Recorded (A)</td>";
	echo "<td>" . $row7[0] . "</td>";
	echo "</tr>";
	echo "<tr>";
	echo "<td>Total Current Recorded (A)</td>";
	echo "<td>" . $row8[0] . "</td>";
	echo "</tr>";
	echo "</table>";
?>
