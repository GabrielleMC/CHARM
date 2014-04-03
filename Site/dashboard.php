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

</head>

<body>
<script src="Highcharts-3.0.5/js/highcharts.js"></script>
<script src="Highcharts-3.0.5/js/modules/data.js"></script>
<script src="Highcharts-3.0.5/js/modules/exporting.js"></script>
<h1>Welcome to the CHARM Dashboard</h1>
<div id = "tabs" class = "stylable">
	<ul>
		<li> <a href="CHARM_overview.php">My Home</a></li>
		<li> <a href="history.php">History</a></li>
		<li> <a href="Settings.php">System Settings</a></li>
		<li> <a href="#tabs-4">CHARM School (Help)</a></li>
	</ul>
	<div id = "tabs-1" class ="overview">
	</div>
	<div id = "tabs-2">
	</div>
	<div id = "tabs-3">
	</div>
	<div id = "tabs-4">
		<p style = "color:#2191C0;font-weight:bold">Frequently Asked Questions</p>
		<div id="accordion">
			<h3>How do I add a device to the system?</h3>
			<div>Simply connect the device to the circuit you would like to monitor and turn it on. Once this device connects to the network, your CHARM server will automatically detect it and begin tracking information from it</div>
			<h3>What if I want to remove a device?</h3>
			<div>First, disconnect the device you'd like to remove from your system. Then, clear the device's tables and information using the Remove Devices form in the Settings tab</div>
			<h3>Can I add another user to the CHARM website?</h3>
			<div>Unfortunately, adding additional website users is currently not supported. Look for this feature in a future release!</div>
		</div>	
		<script>
		$( "#accordion" ).accordion();
		</script>
	</div>
</div>		
		
<a href = "logout.php">Logout</a>
</body>
</html>