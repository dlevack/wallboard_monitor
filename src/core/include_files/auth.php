<?php
function mysql_auth($user = '',
		    $pass = '') {
  require_once('/opt/wallboard_monitor/include_files/db.php');
  $db     = new wall_db();
  $pass   = md5($pass);
  $query  = "select USER_ID from User_Table where ";
  $query .= "USER_NAME='".$user."' and USER_PASS='".$pass."'";
  $result = $db->CONN->query($query);
  unset($query);
  $row = $result->fetch_assoc();
  unset($result);
  if (isset($row['USER_ID'])) {
    unset($query);
    unset($db);
    return(TRUE);
  }
  unset($query);
  unset($db);
  return(FALSE);
}

function openldap_auth($user = '',
		       $pass = '') {
  return(FALSE);
}

function ad_auth($user = '',
		 $pass = '') {
  return(FALSE);
}
?>
