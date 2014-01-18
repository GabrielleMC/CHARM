<?php
	session_start();
	session_destroy();
	$_SESSION= array();
?>
<!DOCTYPE html>
<html>
<head>
	<style type="text/css"> 
	h1 {font-family: Verdana,Arial,sans-serif; color: #ffffff; font-weight: normal}
	a,p {font-family: Verdana,Arial,sans-serif; right: 50px}
	body {background: url("jquery-ui-1.10.3.custom/css/start/images/ui-bg_gloss-wave_75_2191c0_500x100.png") repeat-x scroll 50% 50% #2191C0;}
	div {top: 50px;}
	td {padding:3px 30px 3px 3px;}
    </style>
    
	<script type="text/javascript" src="jquery-1.10.2.min.js"></script>
	<script type="text/javascript" src="jquery-ui-1.10.3.custom/js/jquery-ui-1.10.3.custom.js"></script>
	<link href="jquery-ui-1.10.3.custom/css/start/jquery-ui-1.10.3.custom.css" rel="stylesheet" type="text/css" />
</head>	
<body>
	<h1>Logged Out</h1>
	<br />
	<div id="logout" class="ui-widget-content ui-corner-bottom ui-corner-top">
		<p>You have now logged out of the CHARM dashboard. For security reasons, you should close your browser after using CHARM.</p>
		<a href = "CHARMindex.php"> Return to Home</a> 
</body>
</html>	