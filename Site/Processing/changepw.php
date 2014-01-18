<?php
session_start();
if (isset($_SESSION['auth'])) {
    if ($_SESSION["auth"] != 1) {
        header("Location: CHARMindex.php");
    }
} else {
    header("Location: CHARMindex.php");
}
header("Cache-Control: private, must-revalidate, max-age=0");
header("Pragma: no-cache");
header("Expires: Fri, 4 Jun 2010 12:00:00 GMT");
if (!empty($_POST['password'])) {
	$host = "localhost";
	$user = "CHARM";
	$pass = "5*Hotel";
	mysql_connect($host, $user, $pass) or die("Could not connect: " . mysql_error());
	mysql_select_db("CHARM");
    $username = $_SESSION["username"];
	$password = trim(mysql_real_escape_string($_POST['password']));
    $hash = crypt($password,  PASSWORD_DEFAULT);
    $checklogin = mysql_query("SELECT * FROM User WHERE username = '$username' AND password = '$hash'");
	if (mysql_num_rows($checklogin) == 1 && !empty($_POST['newpw'])){ //our user exists and entered a new password
		$newpw = trim(mysql_real_escape_string($_POST['newpw']));
		$confirm = trim(mysql_real_escape_string($_POST['confirm']));
		$hash1 = crypt($newpw,  PASSWORD_DEFAULT);
		$hash2 = crypt($confirm,  PASSWORD_DEFAULT);
		if (strcmp($hash1, $hash2) == 0){
			$query = mysql_query("UPDATE User SET password = '$hash1' WHERE username = '$username'");
			echo "Successfully changed your password!";
			}
		else{
			echo "Password and Confirm password must match. Please try again.";
		}	
	}
	else{
		echo "Password incorrectly entered. Please try again.";
	}
}
else{
	echo "No password entered. Please try again.";
}
exit();
?>