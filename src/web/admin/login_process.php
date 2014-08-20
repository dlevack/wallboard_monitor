<?php
require('/opt/wallboard_monitor/include_files/auth.php');
if (mysql_auth($_POST['username'],
	       $_POST['password'])) {
  session_start();
  $_SESSION['user'] = $_POST['username'];
  header('Location: /admin/');
} else {
  require('/opt/wallboard_monitor/include_files/web.php');
  $web = new wall_web();
  echo "      Authentication failed!<br>\n";
  unset($web);
}
?>
