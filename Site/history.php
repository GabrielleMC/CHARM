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
<p id="selectdate"></p><button id='launch'>Go!</button>
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
            if(opt == "day"){
                xmlhttp=new XMLHttpRequest();
                xmlhttp.onreadystatechange=function(){
                    if (xmlhttp.readyState==4 && xmlhttp.status==200){
                        document.getElementById("modify").innerHTML=xmlhttp.responseText;
                    };
                    xmlhttp.open("GET","Processing/renderhistory.php?type="+opt+"",true);
                    xmlhttp.send();  
                }
            }
            else if (opt=="range"){
                xmlhttp=new XMLHttpRequest();
                xmlhttp.onreadystatechange=function(){
                    if (xmlhttp.readyState==4 && xmlhttp.status==200){
                        document.getElementById("modify").innerHTML=xmlhttp.responseText;
                    };
                    xmlhttp.open("GET","Processing/renderhistory.php?type="+opt+"",true);
                    xmlhttp.send();  
                }
            }
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