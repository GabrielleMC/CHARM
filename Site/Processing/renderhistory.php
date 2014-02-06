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
  
    $opt = mysql_real_escape_string($_GET['opt']);
    if ($opt == "day"){
        $date = mysql_real_escape_string($_GET['date']);
        $result = mysql_query("SELECT UNIX_TIMESTAMP(logtime)as time, value FROM t1 WHERE DATE(logtime) = '$date'");
        $result2 = mysql_query("SELECT UNIX_TIMESTAMP(logtime)as time, value FROM t2 WHERE DATE(logtime) = '$date'");
        $result3 = mysql_query("SELECT UNIX_TIMESTAMP(logtime)as time, value FROM t3 WHERE DATE(logtime) = '$date'");
    }
    else if ($opt == "range"){
        $from = mysql_real_escape_string($_GET['from']);
        $to = mysql_real_escape_string($_GET['to']);
        $result = mysql_query("SELECT UNIX_TIMESTAMP(logtime)as time, value FROM t1 WHERE (DATE(logtime) >= '$from' AND DATE(logtime) <= '$to')");
        $result2 = mysql_query("SELECT UNIX_TIMESTAMP(logtime)as time, value FROM t2 WHERE (DATE(logtime) >= '$from' AND DATE(logtime) <= '$to')");
        $result3 = mysql_query("SELECT UNIX_TIMESTAMP(logtime)as time, value FROM t3 WHERE (DATE(logtime) >= '$from' AND DATE(logtime) <= '$to')"); 
    }

    $export = array();
    $export['name'] = "test1";
    while ($row = mysql_fetch_array($result)) {
        extract($row);
        $time *= 1000;
        $data = array($time, $value);
        $export['data'][] = $data;
    }
    
    $export2 = array();
    $export2['name'] = "test1";
    while ($row2 = mysql_fetch_array($result2)) {
        extract($row2);
        $time *= 1000;
        $data2 = array($time, $value);
        $export2['data'][] = $data2;
    }
    
    $export3 = array();
    $export3['name'] = "test3";
    while ($row3 = mysql_fetch_array($result3)) {
        extract($row3);
        $time *= 1000;
        $data3 = array($time, $value);
        $export3['data'][] = $data3;
    }
    
    $final_export = array();
    array_push($final_export, $export);
    array_push($final_export, $export2);
    array_push($final_export, $export3);

    print json_encode($final_export, JSON_NUMERIC_CHECK);
    
    mysql_free_result($result);
    mysql_free_result($result2);
    mysql_free_result($result3);
    
?>
