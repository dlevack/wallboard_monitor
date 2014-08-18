<?php
/**
 * Provides methods for reading and writing INI files.
 *
 * This is the ini_files.php file. It will contain classes for accessing
 * INI files.
 *
 * @author Dan Levack <dan@levack.net>
 * @version 1.1
 */

/**
 * This is the ini_files class. It will be used to access and modify all INI
 * files.
 */

class ini_files {
  
  /**
   * @var string $FILE Name and path to INI file
   */
  public $FILE     = '';
  
  /**
   * @var bool $SECTIONS TRUE if INI file contains sections FALSE if not
   */
  public $SECTIONS = FALSE;
  
  /**
   * @var array $CONFIG Array that will contain the config data from the INI file
   */
  public $CONFIG   = array();
  
  /**
   * Conctructor method, called when class is called.
   *
   * The constructor will set the FILE and SECTIONS variables,
   * and then parse the INI file into the CONFIG array.
   *
   * @param string $file         Path to INI file
   * @param bool   $has_sections TRUE if INI file contains sections FALSE if not
   */
  public function __construct($file         = '',
			      $has_sections = FALSE) {
    $this->FILE     = $file;
    $this->SECTIONS = $has_sections;
    $this->CONFIG   = @parse_ini_file($file,
				      $has_sections);
    return;
  }
  
  /**
   * This is the write_ini_file function. It will be used to write changes to
   * the INI files.
   * 
   * @return bool TRUE if INI file successfully writen otherwise FALSE
   */
  public function write_ini_file() {
    $content = "";
    if ($this->SECTIONS) {
      foreach ($this->CONFIG as $key=>$elem) {
	$content .= "[".$key."]\n";
	foreach ($elem as $key2=>$elem2) {
	  if (is_array($elem2)) {
	    for ($i = 0;$i < count($elem2);$i++) {
	      $content .= $key2."[] = \"".$elem2[$i]."\"\n";
	    }
	  } else if ($elem2 == "") {
	    $content .= $key2." = \n";
	  } else {
	    $content .= $key2." = \"".$elem2."\"\n";
	  }
	}
      }
    } else {
      foreach ($this->CONFIG as $key=>$elem) {
	if(is_array($elem)) {
	  for ($i = 0;$i < count($elem);$i++) {
	    $content .= $key."[] = \"".$elem[$i]."\"\n";
	  }
	} else if ($elem == "") {
	  $content .= $key." = \n";
	} else {
	  $content .= $key." = \"".$elem."\"\n";
	}
      }
    }
    
    if (!$handle = fopen($this->FILE,
			 'w')) {
      return false;
    }
    if (!fwrite($handle,
		$content)) {
      fclose($handle);
      return false;
    }
    fclose($handle);
    return true;
  }
}
?>
