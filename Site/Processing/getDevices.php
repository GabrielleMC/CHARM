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
	$num_devices = mysql_query("SELECT device_id FROM Status");
	echo "<select id=\"devices\" name=\"devices\">";
	echo "<option value=\"default\">Select device to remove</option>";
	echo "<p>WARNING: This operation will remove all data that has been logged for the selected device. You will not be able to recover this data.</p>";
	while ($row = mysql_fetch_row($num_devices)){
		$i = $row[0];
		echo "<option value=\"$i\">$i</option>";
	}
	echo "</select>";
	echo "<br />";
	echo "<button type=\"submit\" name=\"submit\" id=\"submit\" value=\"Submit\">Remove Device</button>";
	echo "</form>";
	
	mysql_free_result($num_devices);
	?>