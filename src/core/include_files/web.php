<?php
/**
 * This is the web.inc file it will provide the wall_web class.
 *
 * @author  Dan Levack <dan@levack.net>
 * @package wallboard_monitor
 */

/**
 * This is the wall_web class. It will provide methods for generating
 * web pages for the wallboard_monitor system.
 */

class wall_web {
  
  /**
   * This is the constructor. It generate the html header for the page.
   */
  public function __construct() {
    echo "<html>\n";
    echo "  <head>\n";
    echo "    <link rel = 'stylesheet'\n";
    echo "         type = 'text/css'\n";
    echo "         href = '/css/wallboard.css'>\n";
    echo "  </head>\n";
    if (preg_match('|/admin/|',
		   $_SERVER['REQUEST_URI'])) {
      $this->admin_page();
    }
    return;
  }
  
  /**
   * Setup the page as an admin page.
   */
  public function admin_page() {
    session_start();
    echo "  <body class = 'admin'>\n";
    echo "    <div class = 'menu'>\n";
    if (isset($_SESSION['user'])) {
      echo "      <a href = 'logout.php'>Logout</a><br>\n";
    } else {
      echo "      <a href = 'login.php'>Login</a><br>\n";
    }
    echo "    </div>\n";
    echo "    <div class = 'admin'>\n";
    return;
  }

  /**
   * This is the destructor. It will generate the html footer.
   */
  public function __destruct() {
    echo "    </div>\n";
    echo "  </body>\n";
    echo "</html>\n";
    return;
  }
}
?>
