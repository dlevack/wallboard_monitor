<?php

class wall_db {
  public $CONN;
  public $INFO = array();
  
  public function __construct() {
    $this->INFO = parse_ini_file('/opt/wallboard_monitor/conf/db.conf',
				 TRUE);
    $this->CONN = @mysql_connect($this->INFO['host'],
				 $this->INFO['user'],
				 $this->INFO['pass']);
    @mysql_select_db($this->INFO['name']);
    return;
  }
  
  public function get_status_id_by_name($name = '') {
    $id = 0;
    $query  = 'select STATUS_ID from Status_Table where STATUS_NAME="'.$name.'"';
    $result = @mysql_query($query);
    unset($query);
    $row = @mysql_fetch_assoc($result);
    unset($result);
    $id = $row['STATUS_ID'];
    return($id);
  }
  
  public function get_status_id_by_color($color = '') {
    $id = 0;
    $query  = 'select STATUS_ID from Status_Table where STATUS_COLOR="'.$color.'"';
    $result = @mysql_query($query);
    unset($query);
    $row = @mysql_fetch_assoc($result);
    unset($result);
    $id = $row['STATUS_ID'];
    return($id);
  }
  
  public function get_status_name_by_id($id = 0) {
    $name = '';
    $query  = 'select STATUS_NAME from Status_Table where STATUS_ID='.$id.'';
    $result = @mysql_query($query);
    unset($query);
    $row = @mysql_fetch_assoc($result);
    unset($result);
    $name = $row['STATUS_NAME'];
    return($name);
  }
  
  public function get_status_color_by_id($id = 0) {
    $color = '';
    $query  = 'select STATUS_COLOR from Status_Table where STATUS_ID='.$id.'';
    $result = @mysql_query($query);
    unset($query);
    $row = @mysql_fetch_assoc($result);
    unset($result);
    $color = $row['STATUS_COLOR'];
    return($color);
  }
  
  public function get_status_list() {
    $status_list = array();
    $query  = 'select * from Status_Table';
    $result = @mysql_query($query);
    unset($query);
    while ($row = @mysql_fetch_assoc($result)) {
      $status_list[$row['STATUS_NAME']] = array('id'    => $row['STATUS_ID'],
						'color' => $row['STATUS_COLOR']);
    }
    unset($result);
    return($status_list);
  }
  
  public function __destruct() {
    @mysql_close($this->CONN);
    return;
  }
}
?>
