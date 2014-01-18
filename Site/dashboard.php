<?php
header("Cache-Control: private, must-revalidate, max-age=0");
header("Pragma: no-cache");
header("Expires: Fri, 4 Jun 2010 12:00:00 GMT");
session_start();
if (isset($_SESSION['auth'])) {
    if ($_SESSION["auth"] != 1) {
        header("Location: CHARMindex.php");
    }
} else {
    header("Location: CHARMindex.php");
}
?>
<!DOCTYPE html>
<html>
<head>

	<style type="text/css"> 
	h1 {font-family: Verdana,Arial,sans-serif; color: #ffffff; font-weight: normal}
	a {font-family: Verdana,Arial,sans-serif;}
	body {background: url("jquery-ui-1.10.3.custom/css/start/images/ui-bg_gloss-wave_75_2191c0_500x100.png") repeat-x scroll 50% 50% #2191C0;}
	div > div > table {border-collapse:collapse;}
	td {padding:3px 30px 3px 3px;}
    </style>
    
	<script type="text/javascript" src="jquery-1.10.2.min.js"></script>
	<script type="text/javascript" src="jquery-ui-1.10.3.custom/js/jquery-ui-1.10.3.custom.js"></script>
	<link href="jquery-ui-1.10.3.custom/css/start/jquery-ui-1.10.3.custom.css" rel="stylesheet" type="text/css" />
	
	<script>
	$(function() {
		$( "#tabs" ).tabs();
	});
	</script>
	<?php
		$host = "localhost";
		$user = "CHARM";
		$pass = "5*Hotel";
		mysql_connect($host, $user, $pass) or die("Could not connect: " . mysql_error());
		mysql_select_db("CHARM");

		$result = mysql_query("SELECT TestKey, Value FROM yellow WHERE TestKey < 2000");

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
</head>

<body>
<script src="Highcharts-3.0.5/js/highcharts.js"></script>
<script src="Highcharts-3.0.5/js/modules/data.js"></script>
<script src="Highcharts-3.0.5/js/modules/exporting.js"></script>
<h1>Welcome to the CHARM Dashboard</h1>
<div id = "tabs" class = "stylable">
	<ul>
		<li> <a href="CHARM_Overview.php">My Home</a></li>
		<li> <a href="#tabs-2">History</a></li>
		<li> <a href="#tabs-3">Detailed Statistics</a></li>
		<li> <a href="Settings.php">System Settings</a></li>
		<li> <a href="#tabs-5">CHARM School (Help)</a></li>
	</ul>
	<div id = "tabs-1" class ="overview">
	</div>
	<div id = "tabs-2">
		<div id="container" style="min-width: 1500px; height: 500px; margin: 0 auto"></div>
	</div>
	<div id = "tabs-3">
		<p>More detailed graphs relating to the home go here. For example, this page could contain pie charts breaking down the house's energy use by system or appliance</p>
	</div>
	<div id = "tabs-4">
	</div>
	<div id = "tabs-5">
		<p style = "color:#2191C0;font-weight:bold">Frequently Asked Questions</p>
		<div id="accordion">
			<h3>How can I change how often data is logged from a system?</h3>
			<div>To change how often monitoring devices log data, first open the Systems tab and click on "Modify System" to open the edit window. From here, you will be able to choose the system to change from the dropdown menu. Simply select the new logging interval from the slider.</div>
			<h3>How do I add a system?</h3>
			<div>First content panel</div>
		</div>	
		<script>
		$( "#accordion" ).accordion();
		</script>
	</div>
</div>		
		
<a href = "logout.php">Logout</a>
</body>
</html>