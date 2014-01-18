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
<h3>User Options: </h3>
<button id="changepw">Change Password</button>

<br/ >

<h3>Home Options: </h3>
<div id="dialog">	
	<form id="changepw" action="changepw.php" method="post">
		<label for="password"> Old Password: </label>
		<input type="password" name="password" id="password"><br/>
		<label for="newpw">New Password: </label>
		<input type="password" name="newpw" id="newpw"><br />
		<label for="confirm">Confirm Password: </label>
		<input type="password" name="confirm" id="confirm">	
		<button type="button" id="submit" name="submit">Submit</button>
	</form>
	<div id="alert"></div>
	<script type="text/javascript">
	$("#submit").click(function getItem(){
		xmlhttp=new XMLHttpRequest();
		xmlhttp.onreadystatechange=function(){
			if (xmlhttp.readyState==4 && xmlhttp.status==200){
				document.getElementById("alert").innerHTML=xmlhttp.responseText;
			}
		};
		xmlhttp.open("GET","Processing/changepw.php",true);
		xmlhttp.send();
	});	
	</script>
</div>
<script type="text/javascript">
	$( "#dialog" ).dialog({ 
		autoOpen: false, 
		modal: true,
		width: 500,
		buttons: {
			"Cancel": function() {
				$(this).dialog("close");
			}
		}
	});	
	$( "#changepw" ).button().click(function() {
		$( "#dialog" ).dialog( "open" );
	});
</script>