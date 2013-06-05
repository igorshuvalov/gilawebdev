<?php
include_once(dirname(__FILE__) . '/tb-typography-helper.inc');

/**
 * Google Fonts
 */
$Googlefontstyles = _get_google_font_css();
if ($Googlefontstyles) {
  foreach ($Googlefontstyles as $key => $value) {

    $font     = $value['font'];
    $size     = $value['size'];
    $weight   = $value['weight'];
    $italic   = $value['italic'];
    $selector =  $value['selector'];
    if($italic) {
      $fontitalic = "font-style:italic;";
    }else{
      $fontitalic = "";
    }

$CSS .= <<< CSS
/* Google - {$key} */
.wf-active {$selector} {
  font-family: "{$font}";
  font-weight: {$weight};
  font-size: {$size}px;
  {$fontitalic}
}\n
CSS;

  }
}


/**
 * Websafe Fonts
 */
$Websafefontstyles = _get_websafe_font_css();
if ($Websafefontstyles) {
  foreach ($Websafefontstyles as $key => $value) {

    $font     = $value['font'];
    $size     = $value['size'];
    $weight   = $value['weight'];

    $italic   = $value['italic'];
    $selector =  $value['selector'];
    if($italic) {
      $fontitalic = "font-style:italic;";
    }else{
      $fontitalic = "";
    }

$CSS .= <<< CSS
/* Websafe - {$key} */
{$selector} {
  font-family: {$font};
  font-weight: {$weight};
  font-size: {$size}px;
  {$fontitalic}
}\n
CSS;

  }
}
