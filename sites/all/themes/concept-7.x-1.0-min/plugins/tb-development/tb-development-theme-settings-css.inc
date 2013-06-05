<?php

if( theme_get_setting('custom_css') ) {

  $customcss = theme_get_setting('custom_css');

  $CSS .= <<< EOT
\n/* Custom CSS */
$customcss\n
EOT;

}
