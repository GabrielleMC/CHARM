<!DOCTYPE html>
<html>
    <head>
		<title>Login to CHARM Dashboard</title>
		<style type="text/css">
			p {font-family: Verdana,Arial,sans-serif; color: #ffffff;}
			a {font-family: Verdana,Arial,sans-serif;}
			body {background-color: #2191c0;}
	    </style>
        <!--Gaby Comeau, January 3, 2014-->
		<script type="text/javascript" src="jquery-1.10.2.min.js"></script>
		<script type="text/javascript" src="jquery-ui-1.10.3.custom/js/jquery-ui-1.10.3.custom.js"></script>
		<link href="jquery-ui-1.10.3.custom/css/start/jquery-ui-1.10.3.custom.css" rel="stylesheet" type="text/css" />
		
    </head> 
    <body>
        <div class="ui-widget">
            <form action="checkUser.php" method="post">
                <label for="username">Username: </label>
                <input type="text" name="username" id="username">
				<br>
                <label for="password">Password: </label>
                <input type="password" name="password" id="id">
				<br>
                <button type="submit" name="submit" id="submit">Login</button>
				<script type="text/javascript">
				$(function() {
					$( "#submit" ).button();
				});
				</script>
            </form>
            <br>
            <button name="return" id="return" onclick="location.href = 'CHARMindex.php'">Return to Index</button>
			<script type="text/javascript">
			$(function() {
				$( "#return" ).button();
			});
			</script>
        </div>
    </body>
</html>
