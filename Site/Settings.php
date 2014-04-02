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
$host = "localhost";
$user = "CHARM";
$pass = "5*Hotel";
mysql_connect($host, $user, $pass) or die("Could not connect: " . mysql_error());
mysql_select_db("testCHARM");

date_default_timezone_set("America/Edmonton");
//$date = "2014-02-05"; test date 
$date = Date("Y-m-d");

//Code to check for missing devices and low batteries goes here 
$num_devices = mysql_query("SELECT device_id FROM Status");
?>
<h3>User Options: </h3>
<button id="changepw">Change Password</button>

<br/ >

<h3>Home Options: </h3>
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

<div id="dialog1">	
	<form id="remove" action="remove_device.php" method="post">
		<select id="devices">
		<option value="default">Select device to remove</option>
		<?php
		while ($row = mysql_fetch_row($result)){
			$i = $row[0];
			echo "<option value=\"$i\">$i</option>";
		}
		?>
		</select>
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
		xmlhttp.open("GET","Processing/remove_device.php?id="+id,true);
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
	$( "#submit" ).button();
	$( "#changepw" ).button().click(function() {
		$( "#dialog" ).dialog( "open" );
	});
	$( "#rmsys" ).button().click(function() {
		$( "#dialog1" ).dialog( "open" );
	});
</script>