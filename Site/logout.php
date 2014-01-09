<?php
	session_start();
	header("Location:CHARMindex.php");
	if (isset($_SESSION['auth'])) {
    	if ($_SESSION["auth"] != 0) {
        	$_SESSION['auth'] = 0;
    	}
	}
	session_destroy();
?>