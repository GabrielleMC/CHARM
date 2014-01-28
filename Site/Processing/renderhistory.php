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

    $result = mysql_query("SELECT UNIX_TIMESTAMP(logtime)as time, value FROM t1");
    $result2 = mysql_query("SELECT UNIX_TIMESTAMP(logtime)as time, value FROM t2");
    $result3 = mysql_query("SELECT UNIX_TIMESTAMP(logtime)as time, value FROM t3");

    while ($row = mysql_fetch_array($result)) {
        extract($row);
        $time *= 1000;
        $data[] = "[$time, $value]";
    }
    
    while ($row2 = mysql_fetch_array($result2)) {
        extract($row2);
        $time *= 1000;
        $data2[] = "[$time, $value]";
    }
    
    while ($row3 = mysql_fetch_array($result3)) {
        extract($row3);
        $time *= 1000;
        $data3[] = "[$time, $value]";
    }
    
    $fp = fopen('file.csv', 'w');

    foreach ($data as $point) {
        fputcsv($fp, $point);
    }

    fclose($fp);
    
    mysql_free_result($result);
    mysql_free_result($result2);
    mysql_free_result($result3);
    
?>

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

