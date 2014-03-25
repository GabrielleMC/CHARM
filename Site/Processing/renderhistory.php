<?php    
    //renderhistory.php - file to generate the history page internal data
    //code by Gaby Comeau
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
	
	$resultc = mysql_query("SELECT COUNT(device_id) AS devices FROM Status");
	$rowc = mysql_fetch_row($resultc);
	$count = $rowc[0];
  
  	$result = array();
    $opt = mysql_real_escape_string($_GET['opt']);
    if ($opt == "day"){
        $date = mysql_real_escape_string($_GET['date']);
		for ($i = 0; $i < $count; $i++){
			$table = "Device_$i";
			$result[$i] = mysql_query("SELECT UNIX_TIMESTAMP(logtime)as time, value FROM $table WHERE DATE(logtime) = '$date'");
		}
    }
    else if ($opt == "range"){
        $from = mysql_real_escape_string($_GET['from']);
        $to = mysql_real_escape_string($_GET['to']);
		for ($i = 0; $i < $count; $i++){
			$table = "Device_$i";
			$result[$i] = mysql_query("SELECT UNIX_TIMESTAMP(logtime)as time, value FROM $table WHERE (DATE(logtime) >= '$from' AND DATE(logtime) <= '$to')");
		}
    }

	$final_export = array();
	for ($i = 0; $i < $count; $i++){
	    $export = array();
	    $export['name'] = "Device_$i";
	    while ($row = mysql_fetch_array($result[$i])) {
	        extract($row);
	        $time *= 1000;
	        $data = array($time, $value);
	        $export['data'][] = $data;
	    }
		array_push($final_export, $export);
	}

    print json_encode($final_export, JSON_NUMERIC_CHECK);
	for ($i = 0; $i < $count; $i++){
    	mysql_free_result($result[$i]);
	}
    
?>
