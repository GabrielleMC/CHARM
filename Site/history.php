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

    $result = mysql_query("SELECT logtime, value FROM t1 WHERE TestKey < 2000");

    while ($row = mysql_fetch_array($result)) {
        extract($row);
        $data[] = "[$TestKey, $Value]";
    }
    mysql_free_result($result);
?>

<script type="text/javascript">
    $(function () {
        $('#container').highcharts({
            title: {
                text: 'Sample Home Data',
                style: {
                    color: '#2191C0',
                    fontWeight: 'bold'
                }
            },
            xAxis: {
                tickInterval: 250
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
                color: '#2191C0'
            }]
        });
    });

</script>
<div id="container" style="min-width: 1500px; height: 500px; margin: 0 auto"></div>