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

	$result = mysql_query("SELECT SUM(value) AS test1 FROM t1");
	$row = mysql_fetch_row($result);
	$result1 = mysql_query("SELECT SUM(value) AS test2 FROM t2");
	$row1 = mysql_fetch_row($result1);
	$result3 = mysql_query("SELECT AVG(total) FROM t1_day");
	$row3 = mysql_fetch_row($result3);
	$result4 = mysql_query("SELECT AVG(total) FROM t2_day");
	$row4 = mysql_fetch_row($result4);
	$result6 = mysql_query("SELECT SUM(r.Value) FROM red r");
	$row6 = mysql_fetch_row($result6);
	$result7 = mysql_query("SELECT AVG(r.Value) FROM red r");
	$row7 = mysql_fetch_row($result7);

	echo "<p style = \"color:#2191C0;font-weight:bold\">Last 24 hours</p>";
	echo "<table border=\"1\">";
	echo "<tr>";
	echo "<td>Power used (W)</td>";
	echo "<td>" . $row[0] . "</td>";
	echo "</tr>";
	echo "<tr>";
	echo "<td>Power generated (W)</td>";
	echo "<td>" . $row1[0] . "</td>";
	echo "</tr>";
	echo "</table>";
	echo "<br>";
	echo "<p style = \"color:#2191C0;font-weight:bold\">Last Week</p>";
	echo "<table border=\"1\">";
	echo "<tr>";
	echo "<td>Power used (W)</td>";
	echo "<td>" . $row3[0] . "</td>";
	echo "</tr>";
	echo "<tr>";
	echo "<td>Power generated (W)</td>";
	echo "<td>" . $row4[0] . "</td>";
	echo "</tr>";
	echo "<tr>";
	echo "</table>";
	echo "<br>";
	echo "<p style = \"color:#2191C0;font-weight:bold\">Last Month</p>";
	echo "<table border=\"1\">";
	echo "<tr>";
	echo "<td>Power used (W)</td>";
	echo "<td>" . $row6[0] . "</td>";
	echo "</tr>";
	echo "<tr>";
	echo "<td>Power generated (W)</td>";
	echo "<td>" . $row7[0] . "</td>";
	echo "</tr>";;
	echo "</table>";
?>
