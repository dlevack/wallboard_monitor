<?php
/**
 * This is the db.inc file it will provide the wall_db class.
 * 
 * @author  Dan Levack <dan@levack.net>
 * @package wallboard_monitor
 */

/**
 * This is the wall_db class. It will provide methods for interacting with the
 * MySQL database for the wallboard_monitor system.
 */

class wall_db {
  
  /**
   * @var handler $CONN Database connection handler
   */
  public $CONN;
  
  /**
   * @var array $INFO Array of connection information for the database
   */
  public $INFO = array();
  
  /**
   * This is the constructor. It will read the config file and create the
   * database connection.
   */
  public function __construct() {
    $this->INFO = parse_ini_file('/opt/wallboard_monitor/conf/db.conf',
				 TRUE);
    error_reporting(0);
    $this->CONN = new mysqli($this->INFO['host'],
			     $this->INFO['user'],
			     $this->INFO['pass'],
			     $this->INFO['name']);
    return;
  }
  
  /**
   * Returns the id for a given status name
   * 
   * @param  string $name Name of status to lookup
   * @return int    $id   ID of status
   */
  public function get_status_id_by_name($name = '') {
    $id = 0;
    $query  = 'select STATUS_ID from Status_Table where STATUS_NAME="'.$name.'"';
    $result = $this->CONN->query($query);
    unset($query);
    $row = $result->fetch_assoc();
    unset($result);
    $id = $row['STATUS_ID'];
    return($id);
  }
  
  /**
   * Returns the id for a given status color
   *
   * @param  string $color Color of status to lookup
   * @return int    $id    ID of status
   */
  public function get_status_id_by_color($color = '') {
    $id = 0;
    $query  = 'select STATUS_ID from Status_Table where STATUS_COLOR="'.$color.'"';
    $result = $this->CONN->query($query);
    unset($query);
    $row = $result->fetch_assoc();
    unset($result);
    $id = $row['STATUS_ID'];
    return($id);
  }
  
  /**
   * Returns the name for a given status id
   *
   * @param  int    $id   ID of status to lookup
   * @return string $name Name of status
   */
  public function get_status_name_by_id($id = 0) {
    $name = '';
    $query  = 'select STATUS_NAME from Status_Table where STATUS_ID='.$id.'';
    $result = $this->CONN->query($query);
    unset($query);
    $row = $result->fetch_assoc();
    unset($result);
    $name = $row['STATUS_NAME'];
    return($name);
  }
  
  /**
   * Returns the color for a given status id
   *
   * @param  int    $id    ID of status to lookup
   * @return string $color color of status
   */
  public function get_status_color_by_id($id = 0) {
    $color = '';
    $query  = 'select STATUS_COLOR from Status_Table where STATUS_ID='.$id.'';
    $result = $this->CONN->query($query);
    unset($query);
    $row = $result->fetch_assoc();
    unset($result);
    $color = $row['STATUS_COLOR'];
    return($color);
  }
  
  /**
   * Returns an array of status
   *
   * @return array $status_list Array of status
   */
  public function get_status_list() {
    $status_list = array();
    $query  = 'select STATUS_ID,STATUS_NAME,STATUS_COLOR from Status_Table';
    if ($this->CONN->multi_query($query)) {
      do {
	if ($result = $this->CONN->use_result()) {
	  while ($row = $result->fetch_assoc()) {
	    $status_list[$row['STATUS_NAME']] = array('id'    => $row['STATUS_ID'],
						      'color' => $row['STATUS_COLOR']);
	  }
	  $result->close();
	}
      } while ($this->CONN->next_result());
    }
    unset($query);
    return($status_list);
  }
  
  /**
   * This is the destructor. It will close the database connection.
   */
  public function __destruct() {
    $this->CONN->close();
    return;
  }
}
?>
