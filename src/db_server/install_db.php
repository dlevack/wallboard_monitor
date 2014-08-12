#!/usr/bin/php
<?php
require('../include_files/colors.php');
$colors = new Colors();

// Read our database config file to get the connection information
$conf = parse_ini_file('../conf_files/db.conf',
		       TRUE);

$sting_len = 100;

// Get the root login information so that we can create the database and user
echo "Please enter the super user for the MySQL database.\n";
echo "This user will only be user for creating the database\n";
echo "and the db user from the ini file.\n";
echo "Super User ";
status_out('root',
           'cyan');
echo ": ";
$root_user = read_stdin();
if ($root_user == '') {
  $root_user = 'root';
}

echo "          Password: ";
exec('stty -echo');
$root_pass = read_stdin();
exec('stty echo');
echo "\n\n";

// Connect to the database
$mysqli    = new mysqli($conf['host'],
			$root_user,
			$root_pass,
			'mysql');

// Check to see if the database exists
$string = 'Checking if db exists';
echo str_pad($string,
             $sting_len,
             '.');
unset($string);

if (db_found()) {
  // Database already exists
  // Ask user about recreating it
  echo status_out("Found")."\n\n";
  echo "Would you like to remove the existing ".$conf['name'];
  echo " database and recreate it?\n";
  echo $colors->getColoredString("Any data in the ".$conf['name'].
				 " database will be lost!\n",
				 'red');
  echo "Recreate [yes/";
  echo $colors->getColoredString('no',
				 'cyan');
  echo "]: ";

  $recreate = read_stdin();
  if ($recreate == 'yes' or
      $recreate == 'Yes' or
      $recreate == 'YES' or
      $recreate == 'y'   or
      $recreate == 'Y') {
    // Recreate database
    // Drop existing database
    $string = 'Dropping database: '.$conf['name'];
    echo str_pad($string,
		 $sting_len,
		 '.');
    unset($string);

    $query = 'drop database '.$conf['name'];
    $mysqli->query($query);
    unset($query);
    
    if (!db_found()) {
      // Drop successful
      echo status_out("OK","green")."\n";      
      // Delete User
      $query = 'delete from user where User="'.$conf['user'].'"';
      $mysqli->query($query);
      unset($query);
      // Add the database
      add_db();
      if (db_found()) {
	// Database add successful
	echo status_out("OK","green")."\n";
	// Add user
	add_user();
        echo status_out("OK","green")."\n";
	// Create the database contents
	create_db();
      } else {
	// Database add failed
	echo status_out("Failed")."\n\n";
      }
    } else {
      // Drop failed
      echo status_out("Failed")."\n\n";
    }
  } else {
    // Do not recreate database
    echo $colors->getColoredString("Database ".$conf['name'].
				   " exists.",
				   "red");
    echo "\n";
    echo "Please re-run ./db_config.php to change the database name.\n";
  }
} else {
  // Database not found
  echo status_out("Not Found","green")."\n";
  // Add the database
  add_db();
  if (db_found()) {
    // Database add successful
    echo status_out("OK","green")."\n";
    // Add user
    add_user();
    echo status_out("OK","green")."\n";
    // Create the database contents
    create_db();
  } else {
    // Database add failed
    echo status_out("Failed")."\n\n";
  }
}

$mysqli->close();
unset($mysqli);

function add_db() {
  global $conf;
  global $sting_len;
  global $mysqli;
  $string = 'Creating database: '.$conf['name'];
  echo str_pad($string,
	       $sting_len,
	       '.');
  unset($string);
  $query = 'create database '.$conf['name'];
  $mysqli->query($query);
  unset($query);
  return;
}

function add_user() {
  global $conf;
  global $sting_len;
  global $mysqli;
  $string = 'Creating '.$conf['user'].' user';
  echo str_pad($string,
               $sting_len,
               '.');
  unset($string);
  // Add access from remote hosts
  $query  = "grant all of ".$conf['name'].".* to '".$conf['name']."'@'%' ";
  $query .= "identified by '".$conf['pass']."'";
  $mysqli->query($query);
  unset($query);
  // Add access from localhost
  $query  = "grant all of ".$conf['name'].".* to '".$conf['name']."'@'localhost' ";
  $query .= "identified by '".$conf['pass']."'";
  $mysqli->query($query);
  unset($query);
  // Flush privs
  $query  = "flush privileges";
  $mysqli->query($query);
  unset($query);
  return;
}

function create_db() {
  global $conf;
  global $sting_len;
  global $mysqli;
  
  $string = 'Creating tables and adding default data';
  echo str_pad($string,
               $sting_len,
               '.');
  unset($string);
  
  $mysqli->select_db($conf['name']);
  $query  = 'create table Host_Table (HOST_ID int auto_increment not null,';
  $query .= 'HOST_NAME varchar(50) not null,';
  $query .= 'HOST_IP varchar(15) not null,';
  $query .= 'HOST_STATUS int not null default 1,';
  $query .= 'Primary Key(HOST_ID))';
  $mysqli->query($query);
  unset($query);
  
  $query  = 'create table Status_Table (STATUS_ID int auto_increment not null,';
  $query .= 'STATUS_NAME varchar(10) not null,';
  $query .= 'STATUS_COLOR varchar(10) not null,';
  $query .= 'Primary Key(STATUS_ID))';
  $mysqli->query($query);
  unset($query);
  
  $query  = "insert into Status_Table values (1,'Unknown','clear')";
  $mysqli->query($query);
  unset($query);
  $query  = "insert into Status_Table values (2,'Disabled','blue')";
  $mysqli->query($query);
  unset($query);
  $query  = "insert into Status_Table values (3,'OK','green')";
  $mysqli->query($query);
  unset($query);
  $query  = "insert into Status_Table values (4,'Warning','yellow')";
  $mysqli->query($query);
  unset($query);
  $query  = "insert into Status_Table values (5,'Critical','red')";
  $mysqli->query($query);
  unset($query);
  
  $query  = 'create table Page_Table (PAGE_ID int auto_increment not null,';
  $query .= 'PAGE_NAME varchar(50) not null,';
  $query .= 'PAGE_DESC varchar(255) not null,';
  $query .= 'Primary Key(PAGE_ID))';
  $mysqli->query($query);
  unset($query);
  
  $query  = "insert into Page_Table values (1,";
  $query .= "'Default',";
  $query .= "'Default page - Displayed if no page is specified')";
  $mysqli->query($query);
  unset($query);
  
  $query  = 'create table Category_Table (CAT_ID int auto_increment not null,';
  $query .= 'CAT_NAME varchar(50) not null,';
  $query .= 'CAT_DESC varchar(255) not null,';
  $query .= 'Primary Key(CAT_ID))';
  $mysqli->query($query);
  unset($query);
  
  $query  = "insert into Category_Table values (1,";
  $query .= "'Wallboard Servers',";
  $query .= "'Servers that are part of the monitoring system')";
  $mysqli->query($query);
  unset($query);
  
  $query  = 'create table Page_Category_Table (PAGE_ID int not null,';
  $query .= 'CAT_ID int not null,';
  $query .= 'Primary Key(PAGE_ID,CAT_ID))';
  $mysqli->query($query);
  unset($query);
  
  $query  = 'insert into Page_Category_Table values (1,1)';
  $mysqli->query($query);
  unset($query);
  
  $query  = 'create table Category_Host_Table (CAT_ID int not null,';
  $query .= 'HOST_ID int not null,';
  $query .= 'Primary Key(CAT_ID,HOST_ID))';
  $mysqli->query($query);
  unset($query);
  
  echo status_out("OK","green")."\n";
  return;
}

function db_found() {
  global $conf;
  global $mysqli;
  $query = 'show databases';
  if ($mysqli->multi_query($query)) {
    do {
      if ($result = $mysqli->use_result()) {
	while ($row = $result->fetch_assoc()) {
	  if ($row['Database'] == $conf['name']) {
	    return(TRUE);
	  }
	}
      }
    } while ($mysqli->next_result());
  }
  unset($query);
  return(FALSE);
}

function read_stdin() {
  $fr = fopen("php://stdin","r"); // open our file pointer to read from stdin
  $input = fgets($fr,128);        // read a maximum of 128 characters
  $input = rtrim($input);         // trim any trailing spaces.
  fclose ($fr);                   // close the file handle
  return $input;                  // return the text entered
}

function status_out($text,
                    $color = 'red') {
  global $colors;
  echo "[";
  echo $colors->getColoredString($text,
                                 $color);
  echo "]";
  return;
}
?>
