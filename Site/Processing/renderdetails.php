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
  
    //$opt = mysql_real_escape_string($_GET['opt']);
	$pot = "Pie";
    if ($opt == "Pie"){
        $result = mysql_query("SELECT AVG(value) FROM t1 WHERE TIME(logtime) > "05:00:00" AND TIME(logtime) < "08:00:00"");
		$row = mysql_fetch_row($result);
        $result1 = mysql_query("SELECT AVG(value) FROM t1 WHERE TIME(logtime) > "08:00:00" AND TIME(logtime) < "11:00:00"");
		$row1 = mysql_fetch_row($result1);
        $result2 = mysql_query("SELECT AVG(value) FROM t1 WHERE TIME(logtime) > "11:00:00" AND TIME(logtime) < "13:00:00"");
		$row2 = mysql_fetch_row($result2);
		$result3 = mysql_query("SELECT AVG(value) FROM t1 WHERE TIME(logtime) > "13:00:00" AND TIME(logtime) < "17:00:00"");
		$row3 = mysql_fetch_row($result3);
		$result4 = mysql_query("SELECT AVG(value) FROM t1 WHERE TIME(logtime) > "17:00:00" AND TIME(logtime) < "20:00:00"");
		$row4 = mysql_fetch_row($result4);
		$result5 = mysql_query("SELECT AVG(value) FROM t1 WHERE TIME(logtime) > "20:00:00" OR TIME(logtime) < "05:00:00"");
		$row5 = mysql_fetch_row($result5);
		
		$export = array();
		$export['name'] = "Average Power Use";
		$total = $row[0] + $row1[0] + $row2[0] + $row3[0] + $row4[0] + $row5[0];
		$data= array(["Early Morning", ($row[0]/$total)]);
		$export['data'][] = $data;
		$data1= array(["Early Morning", ($row[0]/$total)]);
		$export['data'][] = $data;
		$data= array(["Early Morning", ($row[0]/$total)]);
		$export['data'][] = $data;
		$data= array(["Early Morning", ($row[0]/$total)]);
		$export['data'][] = $data;
		
    }
	