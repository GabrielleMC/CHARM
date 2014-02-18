<?php
    //history.php - file to generate the history page layout
    //code by Gaby Comeau
    session_start();
    if (isset($_SESSION['auth'])) {
    if ($_SESSION["auth"] != 1) {
        header("Location: CHARMindex.php");
    }
    } else {
        header("Location: CHARMindex.php");
    }
    
?>
<select id ="ChartType" onChange="ShowDateRange()">
    <option value="default">View by...</option>
    <option value="day">Date</option>
    <option value="range">Date Range</option>
</select>
<p id="selectdate"></p><button id="launch">Go!</button>
<div id="container" style="min-width: 1500px; height: 500px; margin: 0 auto"></div>
<script type="text/javascript">
        function ShowDateRange(){
            var opt = document.getElementById("ChartType").value;
                if (opt == "day"){
                     document.getElementById("selectdate").innerHTML= "<p>Date: <input type=\"text\" id=\"datepicker\"></p>";
                     $( "#datepicker" ).datepicker({ minDate: new Date(2014, 0, 1) });
                }
                else if (opt == "range"){
                     document.getElementById("selectdate").innerHTML= "<label for=\"from\">From</label><input type=\"text\" id=\"from\" name=\"from\"><label for=\"to\">to</label><input type=\"text\" id=\"to\" name=\"to\">";
                     $( "#from" ).datepicker({
                     minDate: new Date(2014, 0, 1),
                     defaultDate: "-1w",
                     changeMonth: true,
                     numberOfMonths: 2,
                     onClose: function( selectedDate ) {
                         $( "#to" ).datepicker( "option", "minDate", selectedDate );
                     }
                     });
                     $( "#to" ).datepicker({
                     defaultDate: "-1w",
                     changeMonth: true,
                     numberOfMonths: 2,
                     onClose: function( selectedDate ) {
                         $( "#from" ).datepicker( "option", "maxDate", selectedDate );
                     }
                    });
                }
        };       
	$( "#launch" ).button().click(function() { 
            var opt = document.getElementById("ChartType").value;
            if(opt == "day"){
                var datestr = document.getElementById("datepicker").value;
                var datearr = datestr.split("/");
                var date = datearr[2]+"-"+datearr[0]+"-"+datearr[1];
                $.getJSON('Processing/renderhistory.php?opt='+opt+'&date='+date, function(json) {
                    chart = new Highcharts.Chart({
                        chart: {
                            renderTo: 'container',
                            type: 'line',
                            marginRight: 130,
                            marginBottom: 25
                        },
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
                                day: '%b %e'
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
                        series: json
                    });
                });
             }
            else if (opt=="range"){
                console.log("Selecting date range");
                var fromstr = document.getElementById("from").value;
                var tostr = document.getElementById("to").value;
                var fromarr = fromstr.split("/");
                var toarr = tostr.split("/");
                var from = fromarr[2]+fromarr[0]+fromarr[1];
                console.log ("from date:" + from);
                var to = toarr[2]+toarr[0]+toarr[1];
                console.log ("to date: " + to);
                $.getJSON('Processing/renderhistory.php?opt='+opt+'&from='+from+"&to="+to, function(json) {
                    chart = new Highcharts.Chart({
                        chart: {
                            renderTo: 'container',
                            type: 'line',
                            marginRight: 130,
                            marginBottom: 25
                        },
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
                                day: '%b %e'
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
                        series: json
                    });
                });
            }});  
</script>