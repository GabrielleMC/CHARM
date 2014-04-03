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


<p style = "color:#2191C0;font-weight:bold">User Options </p>
<button id="changepw">Change Password</button>

<br/ >

<p style = "color:#2191C0;font-weight:bold">Home Options </p>
<button id="rmsys">Remove a Device</button>

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
                var oldp = document.getElementById("password").value;
                var newp = document.getElementById("newpw").value;
                var confirm = document.getElementById("confirm").value;
		xmlhttp=new XMLHttpRequest();
		xmlhttp.onreadystatechange=function(){
			if (xmlhttp.readyState==4 && xmlhttp.status==200){
				document.getElementById("alert").innerHTML=xmlhttp.responseText;
			}
		};
		xmlhttp.open("GET","Processing/changepw.php?old="+oldp+"&new="+newp+"&confirm="+confirm,true);
		xmlhttp.send();
	});	
	</script>
</div>

<div id="dialog1" title="Remove a Device">	
	<form id="remove" name= "remove" action="Processing/removeDevice.php" method="post">
		<button type="button" id="viewdevices" name="viewdevices">View Available Devices</button>
	</form>
	
	<script type="text/javascript">
	$("#viewdevices").click(function viewDevices(){
		xmlhttp=new XMLHttpRequest();
		xmlhttp.onreadystatechange=function(){
			if (xmlhttp.readyState==4 && xmlhttp.status==200){
				document.getElementById("remove").innerHTML=xmlhttp.responseText;
				// trigger an artificial click event
				$("#remove").click(function initNewElements(){
					$(function() {
						$( "#submit" ).button();
					});
				});
				$("#remove").trigger("click");
				}
			};
		xmlhttp.open("GET","Processing/getDevices.php",true);
		xmlhttp.send();
	});
	</script>		
</div>

<script type="text/javascript">
	$( "#dialog" ).dialog({ 
		autoOpen: false, 
		modal: true,
		width: 500,
		title: "Change Password",
		buttons: {
			"Cancel": function() {
				$(this).dialog("close");
			}
		}
	});	
	$( "#submit" ).button();
	$( "#dialog1" ).dialog({ 
		autoOpen: false, 
		modal: true,
		width: 500,
		title: "Remove a device",
		buttons: {
			"Cancel": function() {
				$(this).dialog("close");
			}
		}
	});	
	$( "#viewdevices" ).button();
	$( "#changepw" ).button().click(function() {
		$( "#dialog" ).dialog( "open" );
	});
	$( "#rmsys" ).button().click(function() {
		$( "#dialog1" ).dialog( "open" );
	});
</script>