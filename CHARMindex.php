<!DOCTYPE html>
<html>
<head>
	
	<script type="text/javascript" src="jquery-1.10.2.min.js"></script>
	<script type="text/javascript" src="jquery-ui-1.10.3.custom/js/jquery-ui-1.10.3.custom.js"></script>
	<link href="jquery-ui-1.10.3.custom/css/start/jquery-ui-1.10.3.custom.css" rel="stylesheet" type="text/css" />
	<style>
	h1 {font-family: Verdana,Arial,sans-serif; color: #ffffff;}
	a {font-family: Verdana,Arial,sans-serif;}
	body {background-color: #2191c0;}
	div > div > table {border-collapse:collapse;}
	td {padding:3px 30px 3px 3px;}
    </style>
    
	<script>
	$(function() {
		$( "#tabs" ).tabs();
	});
	</script>
</head> 
<body>

<h1>CHARM Project Home</h1>
<div id = "tabs">
	<ul>
		<li> <a href="#tabs-1">Home</a></li>
		<li> <a href="#tabs-2">About CHARM</a></li>
		<li> <a href="#tabs-3">Features</a></li>
	</ul>
	<div id="tabs-1">
		<p>Welcome to the CHARM homepage! Login or learn more</p>
	</div>
	<div id="tabs-2">
		<div id="accordion">
			<h3>The Goal</h3>
			<div>First content panel</div>
			<h3>The Team</h3>
			<div>Lucas, Gaby, Dave and Brandon :D</div>
		</div>
		<script>
		$( "#accordion" ).accordion();
		</script>
	</div>
	<div id="tabs-3">
		<p>So just what are we doing? Currently, our project may feature wireless monitoring of the following home systems:
		<ul>
		<li>Thermistors</li>
		<li>Lights</li>
		<li>Occupancy sensors</li>
		<li>Ambient light sensor</li>
		</ul>
		We can provide historical trend data for all of this information, and a detailed breakdown of power usage in your house!<br><br>
		Stretch goal: be able to send control signals back to some systems
		</p>
	</div>
</div>		
<button id="Login">Log into the CHARM dashboard</button>
<div id="dialog">
	<form id="login" action="checkUser.php" method="post">
		<label for="username">Username: </label>
		<input type="text" name="username" id="username"><br>
		<label for="password">Password: </label>
		<input type="password" name="password" id="id">
    </form>
</div>
<script type="text/javascript">
	$( "#dialog" ).dialog({ 
		autoOpen: false, 
		modal: true,
		width: 500,
		buttons: {
			"Submit": function(){
				$("form#login").submit();
				$(this).dialog("close");
                            
			},
			"Cancel": function() {
				$(this).dialog("close");
			}
		}
	});	
	$( "#Login" ).button().click(function() {
		$( "#dialog" ).dialog( "open" );
	});
</script>
</body>
</html>