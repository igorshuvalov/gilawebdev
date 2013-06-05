<?php

/**
 * Custom theme settings might need a lot of CSS
 * So we put it in a file for optimzal performance
 */
function bootstrap_css_cache_build($theme,$delta="") {

  global $files_path, $base_path, $base_theme_info;

  // We're being called as form submit callback:
  if (isset($theme['theme_settings']) && is_array($theme['theme_settings'])) {
    $theme = arg(count(arg()) - 1);
  }

  // $themes = list_themes();
  // $theme_chain = array($theme);
  // foreach ($themes[$theme]->base_themes as $base_theme => $base_theme_name) {
  //   $theme_chain[] = $base_theme;
  // }

  $tb_css_file = $files_path . '/tb-cache-'.$theme.'.css';
  //Construct CSS file:
  $CSS = '';

  if (isset($delta)) {
    $tb_css_file = $files_path . '/tb-cache-'.$delta.'.css';
  }

  // Load Features CSS
  foreach (file_scan_directory(drupal_get_path('theme', $theme) . '/plugins', '/css.inc/i') as $file) {
    include($file->uri);
  }

  $fh = fopen($tb_css_file, 'w');
  if ($fh) {
    fwrite($fh, $CSS); // write css to file
    watchdog('Concept', 'Concept CSS file cache built for %theme', array('%theme' => $theme));
  }
  else {
    drupal_set_message(t('Cannot write theme-settings file, please check your file system. (See status report page)'), 'error');
  }

  fclose($fh);
  // If the CSS & JS aggregation are enabled we need to clear the caches
  drupal_clear_css_cache();
  drupal_clear_js_cache();
}


/**
 * _tb_module_tests function
 *
 * @return void
 * @author
 **/
function _tb_module_tests(&$form){
  global $files_path, $base_path, $base_url ,$base_theme_info;
  $contrib = array(
    'admin_menu',
    'block_class',
    'colorbox',
    'empty_page',
    'exclude_node_title',
    'libraries',
    'submitted_by',
    'wysiwyg',
    'imce',
    'imce_wysiwyg',
    'ace_editor'
  );
  asort($contrib);

  $mods = array();
  $defaults = array();
  foreach ($contrib as $key => $value) {
    $mods[] = array(
      'mid' => $key+1,
      'name' => $value,
      'status' => (module_exists($value)) ? "Enable" : "Disable"
    );
    if (module_exists($value)) {
      $defaults[$key+1] = TRUE;
    }

  }

  $header = array(
    'name' => t('Module Name'),
    'status' => t('Status'),
    'info'  => t('Info')
  );

  $options = array();
  $attributes['target'] = "_blank";
  $Enable['path'] = $base_url."/misc/watchdog-ok.png";
  $Disable['path'] = $base_url."/misc/watchdog-error.png";
  $txtEnable = "Info";
  $txtDisable= "Download";
  foreach($mods as $mod){
    $options[$mod['mid']] =array(
      'name' => $mod['name'],
      'status' => theme('image', ${$mod['status']} ) ,
      'info'   => t('<a target="_blank" href="http://drupal.org/project/@name">@text</a>', array('@text'=>${"txt".$mod['status']},'@name' => $mod['name'] ))
    );
  }

  $form['tb']['general']['mymodules'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#default_value' => $defaults,
    '#disabled' => TRUE,
    '#empty' => t('No module found'),
  );
  // $form['tb']['general']['preview'] = array(
  //   '#type' =>'button',
  //   '#value' => t('Preview'),
  // );


  return $form;
}

/**
 * welcome_message function
 *
 * @return void
 * @author
 **/
function _tb_welcome_message(){


$message = <<< OTL
<h1>Welcome</h1>

<p>Thank you for purchasing the theme.
For any questions or concerns please feel free to email via my user page contact form <a target="_blank"  href="http://themeforest.net/user/themebiotic">here</a>. Thanks so much!</p>

<h3>Contrib modules</h3>
<p>For stand-alone installations, you will need to use some contrib modules for use as live preview. There is no obligation to use these modules, but we strongly recommend you to use a more flexible.</p>
<p>Below you will find a list of these modules. If these modules are already installed on your system, they will appear as checked.</p>
OTL;

  return $message;

}
