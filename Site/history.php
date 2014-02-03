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
            console.log("Launching chart AJAX call");
            var opt = document.getElementById("ChartType").value;
            if(opt == "day"){
                console.log("Day view selected");
                var datestr = document.getElementById("datepicker").value;
                var datearr = datestr.split("/");
                var dateconv = datearr[2]+"-"+datearr[0]+"-"+datearr[1];
                var date = new Date(dateconv).getTime() / 1000
                console.log("Date: "+ datestr);
                console.log("Converted date: "+ dateconv);
                console.log("Timestamp: "+ date);
                xmlhttp=new XMLHttpRequest();
                xmlhttp.onreadystatechange=function(){
                    console.log("Status:" + xmlhttp.readyState+', '+xmlhttp.status);
                    if (xmlhttp.readyState==4 && xmlhttp.status==200){
                        document.getElementById("container").innerHTML=xmlhttp.responseText;
                    }
                }
             console.log("WHEEEEE");
             xmlhttp.open("GET","Processing/renderhistory.php?type="+opt+"&date="+date,true);
             console.log("File opened: renderhistory.php");
             xmlhttp.send();  
             console.log("data sent");
             }
            else if (opt=="range"){
                var from = document.getElementById("from").value;
                var to = document.getElementById("to").value;
                xmlhttp=new XMLHttpRequest();
                xmlhttp.onreadystatechange=function(){
                    if (xmlhttp.readyState==4 && xmlhttp.status==200){
                        document.getElementById("modify").innerHTML=xmlhttp.responseText;
                    };
                    xmlhttp.open("GET","Processing/renderhistory.php?type="+opt+"&from="+from+"&to="+to,true);
                    xmlhttp.send();  
                }
            }
            console.log("DONE");
         });  
</script>