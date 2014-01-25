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
    
    mysql_free_result($result);
    mysql_free_result($result2);
    mysql_free_result($result3);
    
?>
<select id ="ChartType" onChange="ShowDateRange()">
    <option value="default">View by...</option>
    <option value="day">Date</option>
    <option value="range">Date Range</option>
</select>
<p id="selectdate"></p><button id='launch'>Go!</button>
<div id="container" style="min-width: 1500px; height: 500px; margin: 0 auto"></div>
<script type="text/javascript">
        function ShowDateRange(){
            var opt = document.getElementById("ChartType").value;
                if (opt == "day"){
                     console.log("single date chosen");
                     document.getElementById("selectdate").innerHTML= "<p>Date: <input type=\"text\" id=\"datepicker\"></p>";
                }
                else if (opt == "range"){
                     console.log("date range chosen");
                     document.getElementById("selectdate").innerHTML= "<label for=\"from\">From</label><input type=\"text\" id=\"from\" name=\"from\"><label for=\"to\">to</label><input type=\"text\" id=\"to\" name=\"to\">";
                }
        };       
	$(function() {
            $( "#datepicker" ).datepicker({ minDate: new Date(2014, 1, 1) });
            $( "#from" ).datepicker({
            defaultDate: "+1w",
            changeMonth: true,
            numberOfMonths: 3,
            onClose: function( selectedDate ) {
                $( "#to" ).datepicker( "option", "minDate", selectedDate );
            }
            });
            $( "#to" ).datepicker({
            defaultDate: "+1w",
            changeMonth: true,
            numberOfMonths: 3,
            onClose: function( selectedDate ) {
                $( "#from" ).datepicker( "option", "maxDate", selectedDate );
            }
            });
        });
	$( "#launch" ).button().click(function() { 
            //ajax call goes here!
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