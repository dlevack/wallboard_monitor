<?php
require('/opt/wallboard_monitor/include_files/web.php');
$web = new wall_web();
echo "      <form action = 'login_process.php'\n";
echo "            method = 'post'>\n";
echo "        <table border = '0'>\n";
echo "          <tr>\n";
echo "            <th align = 'right'>Username: </th>\n";
echo "            <td align = 'left'>\n";
echo "              <input name = 'username'\n";
echo "                     type = 'text'>\n";
echo "            </td>\n";
echo "          </tr>\n";
echo "          <tr>\n";
echo "            <th align = 'right'>Password: </th>\n";
echo "            <td align = 'left'>\n";
echo "              <input name = 'password'\n";
echo "                     type = 'password'>\n";
echo "            </td>\n";
echo "          </tr>\n";
echo "          <tr>\n";
echo "            <td align = 'left'>\n";
echo "              <input type = 'submit'\n";
echo "                    value = 'Login'>\n";
echo "            </td>\n";
echo "          </tr>\n";
echo "        </table>\n";
echo "      </form>\n";
unset($web);
?>