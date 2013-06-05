<?php

if (theme_get_setting('layout_type') == "boxed" && (theme_get_setting('layout_top_margin') > 0)) {
$marginTop = theme_get_setting('layout_top_margin');
$CSS .= <<<EOT
.container-boxed {
  margin-top: {$marginTop}px;
}
EOT;
}

