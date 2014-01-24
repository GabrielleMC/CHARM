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

    $result = mysql_query("SELECT logtime, value FROM t1");
    $result2 = mysql_query("SELECT logtime, value FROM t2");
    $result3 = mysql_query("SELECT logtime, value FROM t3");

    while ($row = mysql_fetch_array($result)) {
        extract($row);
        $data[] = "[$value]";
        $time[] = "$logtime";
    }
    
    while ($row2 = mysql_fetch_array($result2)) {
        extract($row2);
        $data2[] = "[$value]";
        //$time[] = "$logtime";
    }
    
    while ($row3 = mysql_fetch_array($result3)) {
        extract($row3);
        $data3[] = "[$value]";
        //$time[] = "$logtime";
    }
    
    mysql_free_result($result);
    mysql_free_result($result2);
    mysql_free_result($result3);
    
?>

<script type="text/javascript">
    $(function () {
        var t = "<?php echo $time[0] ?>".split(/[- :]/);
        var d = Date(t[0], t[1]-1, t[2], t[3], t[4], t[5]);
        $('#container').highcharts({
            title: {
                text: 'Sample Home Data',
                style: {
                    color: '#2191C0',
                    fontWeight: 'bold'
                }
            },
            xAxis: {
                type: 'datetime',
                dateTimeLabelFormats: {
                    day: '%e of %b'
                }
            },
            yAxis: { // left y axis
                title: {
                    style: {
                        color: '#2191C0',
                        fontWeight: 'bold'
                    },
                    text: 'Function results'
                },
                plotLines: [{
                    value: 0,
                    width: 1,
                    color: '#808080'
                }]
            },
            legend: {
                align: 'left',
                verticalAlign: 'top',
                y: 50,
                x: 70,
                floating: true,
                borderWidth: 0
            },
            tooltip: {
                shared: true,
                crosshairs: true
            },
            	
            series: [{
                data :[<?php echo join($data, ',') ?>],
                pointInterval: 60*10, // ten minutes
                color: '#2191C0'
            },
            {
                data :[<?php echo join($data2, ',') ?>],
                pointInterval: 60*10, // ten minutes
                color: '#FF3030'
            },
            {
                data :[<?php echo join($data3, ',') ?>],
                pointInterval: 60*10, // ten minutes
                color: '#33cc33'
            }]
        });
    });

</script>
<div id="container" style="min-width: 1500px; height: 500px; margin: 0 auto"></div>