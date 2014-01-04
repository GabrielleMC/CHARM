<?php
session_start();
if (!empty($_POST['username']) && !empty($_POST['password'])) {
    //$username = trim(mysql_real_escape_string($_POST['username']));
    //$password = password_hash(trim(mysql_real_escape_string($_POST['password'])),  PASSWORD_DEFAULT);
    $username = trim($_POST['username']);
	$password = trim($_POST['password']);
    $hash = crypt($password,  PASSWORD_DEFAULT);
	//password is 'password' ...we should fix this at some point lol
	if($username == "project" && crypt($password, $hash) == "PAzNeZcFJV3Vk"){
    //$checklogin = mysql_query("SELECT * FROM User WHERE username = '$username' AND password = '$password'");
    //if (mysql_num_rows($checklogin) == 1) 
        //$row = mysql_fetch_array($checklogin);
        //$username = $row['username'];
        $_SESSION['username'] = $username;
        $_SESSION['loggedIn'] = 1;
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