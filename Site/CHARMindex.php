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
		<li> <a href="#tabs-3">Meet the Team</a></li>
	</ul>
	<div id="tabs-1">
		<p>Welcome to the CHARM homepage! Login or learn more</p>
	</div>
	<div id="tabs-2">
			<p>CHARM is a lightweight, low-cost residential energy monitoring system. We designed this system so that you can either install it while constructing a new home, or integrate in an existing home with minimal renovations. </p>
			<p>We use a central server to communicate with a set of sensor monitoring devices. Each device is able to connnect to and read data from a variety of electrical systems. </p>
	</div>
	<div id="tabs-3">
		<p>Lucas Holzhaeuer</p>
		<ul>
		<li>Team Manager</li>
		<li>Honeywell Intl. Inc.</li>
		</ul>
		
		<p>Gabrielle Comeau</p>
		<ul>
		<li>Server Designer</li>
		<li>Hitachi ID Systems</li>
		</ul>
		
		<p>Brandon Crapo</p>
		<ul>
		<li>Embedded Systems</li>
		<li>General Electric</li>
		</ul>
		
		<p>David Kozuchar</p>
		<ul>
		<li>Home Integration</li>
		<li>Stantec Consulting</li>
		</ul>
	</div>
</div>		
<button id="Login">Log into the CHARM dashboard</button>
<div id="dialog">
	<form id="login" action="Processing/checkUser.php" method="post">
		<label for="username">Username: </label>
		<input type="text" name="username" id="username"><br>
		<label for="password">Password: </label>
		<input type="password" name="password" id="id">
    </form>
</div>
<script type="text/javascript">
	$( "#dialog" ).dialog({ 
		autoOpen: false, 
		title: "Login",
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
	}).bind('keypress',pressed);

function pressed(e)
{
    if(e.keyCode === 13|| e.which === 13)
    {
		$("form#login").submit();
		$(this).dialog("close");
    }
};	
	$( "#Login" ).button().click(function() {
		$( "#dialog" ).dialog( "open" );
	});
</script>
</body>
</html>