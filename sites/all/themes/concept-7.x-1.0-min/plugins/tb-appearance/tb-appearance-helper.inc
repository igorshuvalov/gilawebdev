<?php

/**
 * _set_rgba function
 *
 * @return rgba color string
 **/
function _set_rgba($rgb,$opacity = NULL){
  if (!$rgb) {
    return false;
  }

  $r = $rgb[0];
  $g = $rgb[1];
  $b = $rgb[2];
  if (!$opacity) {
    $opacity = 1;
  }

  return "rgba({$r}, {$g}, {$b}, $opacity )";
}

/**
 * _set_rgb function
 *
 * @return rgb color string
 **/
function _set_rgb($rgb){
  if (!$rgb) {
    return false;
  }

  $r = $rgb[0];
  $g = $rgb[1];
  $b = $rgb[2];

  return "rgb({$r}, {$g}, {$b} )";
}


/**
 * _get_google_font_css function
 *
 * @return void
 * @author
 **/
function _get_appearance_css(){

  // Load node.admin.inc from the node module.
  module_load_include('module', 'color');

  $theme_settings = variable_get('theme_bootstrap_settings');
  $RegionCSS = array();

  if (!isset($theme_settings)) {
    # code...
    return false;
  }

  foreach (array_keys($theme_settings) as $k) {
    if (preg_match('/\w*status_region$/', $k)) {

      // $setting = theme_get_setting($k);
      if ( theme_get_setting($k) ) {
        $set = explode("_", $k,3);
        $RegionName = $set[0];
        $RegionType = $set[1];
        $RegionSelector = theme_get_setting($RegionName."_selector");

        switch ($RegionType) {

          case 'txt':
            $RegionCSS["#".$RegionType][$RegionName] = array(
              'selector' => $RegionSelector,
              'text'  => theme_get_setting($RegionName."_text_color"),
              'link'  => theme_get_setting($RegionName."_link_color"),
              'hover' => theme_get_setting($RegionName."_link_hover_color"),
            );
            break;

          case 'menu':
            # code...
            $RegionCSS["#".$RegionType][$RegionName] = array(
              'selector' => $RegionSelector,
              'link'  => theme_get_setting($RegionName."_link_color"),
              'hover' => theme_get_setting($RegionName."_link_hover_color"),
              'hoverbg'  => theme_get_setting($RegionName."_link_hoverbg_color"),
              'active'  => theme_get_setting($RegionName."_active_color"),
              'activebg'  => theme_get_setting($RegionName."_activebg_color"),
              'activehover'  => theme_get_setting($RegionName."_active_hover_color"),
            );
            break;

          case 'bg':
            $type  = theme_get_setting($k);

            /* Solid Background */
            if ($type=="color") {
              $vv = _color_unpack( theme_get_setting($RegionName."_solid_color") );
              $RegionCSS["#".$RegionType][$type][$RegionName]['selector'] = $RegionSelector;
              $RegionCSS["#".$RegionType][$type][$RegionName]['solid'] =  $vv;//theme_get_setting($RegionName."_solid_color");


              $RegionCSS["#".$RegionType][$type][$RegionName]['opacity'] = theme_get_setting($RegionName."_solid_opacity");

            }

            /* Gradient Background */
            if ($type=="gradient") {
              $RegionCSS["#".$RegionType][$type][$RegionName]['selector'] = $RegionSelector;
              $RegionCSS["#".$RegionType][$type][$RegionName]['top'] = theme_get_setting($RegionName."_gradient_top");
              $RegionCSS["#".$RegionType][$type][$RegionName]['bottom'] = theme_get_setting($RegionName."_gradient_bottom");
            }

            /* Pattern Background */
            if ($type=="pattern") {
              $RegionCSS["#".$RegionType][$type][$RegionName]['selector'] = $RegionSelector;
              $RegionCSS["#".$RegionType][$type][$RegionName]['path'] = theme_get_setting($RegionName."_pattern");
            }

            /* Custom upload Background */
            if ($type=="custom") {
              $RegionCSS["#".$RegionType][$type][$RegionName]['selector'] = $RegionSelector;
              $RegionCSS["#".$RegionType][$type][$RegionName]['behave'] = theme_get_setting($RegionName."_custom_behave");
              $RegionCSS["#".$RegionType][$type][$RegionName]['uri'] = theme_get_setting($RegionName."_custom_path");
              $RegionCSS["#".$RegionType][$type][$RegionName]['fid'] = theme_get_setting($RegionName."_custom_upload");
            }

            break;

          case 'htag':
            $RegionCSS["#".$RegionType][$RegionName] = array(
              'selector' => $RegionSelector,

              'blocktitle'  => theme_get_setting($RegionName."_bt_color"),
              'pagetitle'  => theme_get_setting($RegionName."_pt_color"),
              'border'  => theme_get_setting($RegionName."_border_color"),

              'h1'  => theme_get_setting($RegionName."_h1_text_color"),
              'h2'  => theme_get_setting($RegionName."_h2_text_color"),
              'h3'  => theme_get_setting($RegionName."_h3_text_color"),
              'h4'  => theme_get_setting($RegionName."_h4_text_color"),
              'h5'  => theme_get_setting($RegionName."_h5_text_color"),
              'h6'  => theme_get_setting($RegionName."_h6_text_color"),

              'h1l'  => theme_get_setting($RegionName."_h1_link_color"),
              'h2l'  => theme_get_setting($RegionName."_h2_link_color"),
              'h3l'  => theme_get_setting($RegionName."_h3_link_color"),
              'h4l'  => theme_get_setting($RegionName."_h4_link_color"),
              'h5l'  => theme_get_setting($RegionName."_h5_link_color"),
              'h6l'  => theme_get_setting($RegionName."_h6_link_color"),

              'h1h'  => theme_get_setting($RegionName."_h1_hover_color"),
              'h2h'  => theme_get_setting($RegionName."_h2_hover_color"),
              'h3h'  => theme_get_setting($RegionName."_h3_hover_color"),
              'h4h'  => theme_get_setting($RegionName."_h4_hover_color"),
              'h5h'  => theme_get_setting($RegionName."_h5_hover_color"),
              'h6h'  => theme_get_setting($RegionName."_h6_hover_color"),
            );
            break;

          default:
            # code...
            break;
        }


      }

    }
  }
  // krumo($RegionCSS);
  return $RegionCSS;
}
