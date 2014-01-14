<?php
session_start();
header("Cache-Control: private, must-revalidate, max-age=0");
header("Pragma: no-cache");
header("Expires: Fri, 4 Jun 2010 12:00:00 GMT");
if (!empty($_POST['username']) && !empty($_POST['password'])) {
	$host = "localhost";
	$user = "CHARM";
	$pass = "5*Hotel";
	mysql_connect($host, $user, $pass) or die("Could not connect: " . mysql_error());
	mysql_select_db("CHARM");
    $username = trim(mysql_real_escape_string($_POST['username']));
	$password = trim(mysql_real_escape_string($_POST['password']));
    $hash = crypt($password,  PASSWORD_DEFAULT);
	//password is 5*Hotel, username is project
    $checklogin = mysql_query("SELECT * FROM User WHERE username = '$username' AND password = '$hash'");
    if (mysql_num_rows($checklogin) == 1){
        $row = mysql_fetch_array($checklogin);
        $username = $row['username'];
        $_SESSION['auth'] = 1;
        header('Location: dashboard.php'); //<-- comment it to see debug info
    } 
	else {
        header("Location: CHARMindex.php");//make this give an error stating username or password is not correct
    }
}
else {
	header("Location: CHARMindex.php");
}
exit();
?>