#!/usr/bin/php
<?php
/**
  * Require our include files.
  */
require('../include_files/ini_files.php');
$ini = new ini_files('../conf_files/db.conf');

if (!isset($ini->CONFIG['host']) or
    $ini->CONFIG['host'] == '') {
  $ini->CONFIG['host'] = 'localhost';
}
if (!isset($ini->CONFIG['name']) or
    $ini->CONFIG['name'] == '') {
  $ini->CONFIG['name'] = 'wallboard_db';
}
if (!isset($ini->CONFIG['user']) or
    $ini->CONFIG['user'] == '') {
  $ini->CONFIG['user'] = 'wallboard_user';
}
if (!isset($ini->CONFIG['pass']) or
    $ini->CONFIG['pass'] == '') {
  $ini->CONFIG['pass'] = 'wallboard_pass';
}

echo "Host [".$ini->CONFIG['host']."]: ";
$host = trim(fgets(STDIN));
if ($host != '') {
  $ini->CONFIG['host'] = $host;
}
unset($host);

echo "Database [".$ini->CONFIG['name']."]: ";
$name = trim(fgets(STDIN));
if ($name != '') {
  $ini->CONFIG['name'] = $name;
}
unset($name);

echo "User [".$ini->CONFIG['user']."]: ";
$user = trim(fgets(STDIN));
if ($user != '') {
  $ini->CONFIG['user'] = $user;
}
unset($user);

echo "Pass [".$ini->CONFIG['pass']."]: ";
system('stty -echo');
$pass = trim(fgets(STDIN));
system('stty echo');
echo "\n";
if ($pass != '') {
  $ini->CONFIG['pass'] = $pass;
}
unset($pass);

$ini->write_ini_file();
unset($ini);

?>
