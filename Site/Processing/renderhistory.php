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
    
    $date = mysql_real_escape_string($_GET['date']);
    $server = PHP_OS;
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
    
    //WAMP does NOT allow you to have any writable files in the www folder, making it effectively impossible to create a relative filepath that's guaranteed to work in Windows
    //We might want to not use WAMP in any future development/deployment, but for now, creating this CHARMCharts directory in the server user's root is an acceptable workaround
    //On Mac and Windows, this shouldn't be a problem,  but I will check
    if ($server = "Windows"){
        $fp = fopen('C:\CHARMCharts\historychart.csv', 'w') or die("Error opening file: " . print_r(error_get_last()));
    }
    else {
        $fp = fopen('C:\CHARMCharts\historychart.csv', 'w') or die("Error opening file: " . print_r(error_get_last()));
    }

    foreach ($data as $pointstr){
        echo $pointstr;
        $point = trim($pointstr, '\"[]');
        $point = str_replace("\"",'', $point);
        echo $point;
        fputcsv($fp, explode("," ,$point)) or die("Error writing file: " . print_r(error_get_last()));
    }

    fclose($fp);
    
    mysql_free_result($result);
    mysql_free_result($result2);
    mysql_free_result($result3);
    
?>
