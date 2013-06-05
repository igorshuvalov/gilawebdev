<?php

include_once(dirname(__FILE__) . '/includes/bootstrap.inc');

/**
 * Implements hook_form_system_theme_settings_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */
require_once dirname(__FILE__) . '/includes/theme-functions.inc';


/**
 * Cannot run as submit function because  it will set outdated values by
 * using theme_get_setting to retrieve settings from database before the db is
 * updated. Cannot put cache builder in form scope and use $form_state because
 * it also needs to initialize default settings by reading the .info file.
 * By calling the cache builder here it will run twice: once before the
 * settings are saved and once after the redirect with the updated settings.
 */

if (!isset($files_path)) { // in case admin theme is used
  global $files_path;
  $files_path = variable_get('file_public_path', conf_path() . '/files');
}

if (arg(count(arg()) - 1)=="bootstrap") {
  bootstrap_css_cache_build(arg(count(arg()) - 1),NULL);
}elseif (arg(2)=="delta") {
  /*
  @todo
  Delta module Support */
  global $deltaname;
  $deltaname = arg(count(arg()) - 2);
  bootstrap_css_cache_build("bootstrap",$deltaname);
}


function bootstrap_form_system_theme_settings_alter(&$form, $form_state, $form_id = NULL) {

  global $theme, $base_path, $theme_path, $concept_theme_path, $deltaname ;
  $theme = $GLOBALS['theme_key'];
  $themes = list_themes();
  $concept_theme_path = drupal_get_path('theme', 'bootstrap');
  // $theme = $GLOBALS['theme_key'];
  // Work-around for a core bug affecting admin themes. See issue #943212.
  if (isset($form_id)) {
    return;
  }

  $themes = list_themes();

  // System Libraries
  drupal_add_library('system', 'ui');
  drupal_add_library('system', 'ui.slider');
  drupal_add_library('system', 'farbtastic');

  drupal_add_css( drupal_get_path('theme','bootstrap'). "/assets/css/admin.css"  );
  drupal_add_js( drupal_get_path('theme','bootstrap'). "/assets/js/theme-settings.js", 'file' );
  drupal_add_js( drupal_get_path('theme','bootstrap'). "/assets/js/vendor/jquery.scrollfollow.js", 'file' );

  $form['tb'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => -10,
    '#prefix' => t('<div id="tb-header"><h2 id="theme-name">Concept <small>v1.0.0</small></h2></div> <div class="tb-farbtastic-wrapper"></div>'),
  );

  if (theme_get_setting('welcome_tab')) {

    $form['tb']['general'] = array(
      '#type'          => 'fieldset',
      '#title'         => t('Welcome'),
      // '#description'   => t("General theme parameters are configured here."),
      '#weight'        => -1,
    );

    $form['tb']['general']['welcome_message'] = array(
      '#markup' => _tb_welcome_message()
    );

    /* Module test table */
    _tb_module_tests($form);

    $form['tb']['general']['welcome_message_note'] = array(
      '#markup' => t("<p><b>Note:</b> You can hide welcome tab under <em>theme development settings</em>, if you don't want to see anymore.</p>
")
    );

  }

/* <!-- Load Plugins
================================================== --> */
foreach (file_scan_directory($concept_theme_path . '/plugins', '/theme-settings.inc/i') as $file) {
  require_once($file->uri);
}


$form['tb']['tb_drupal'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Drupal Core'),
  '#description'   => t("Drupal Core parameters are configured here."),
  '#weight'        => 10,
);

$form['tb']['tb_drupal']['theme_settings'] = $form['theme_settings'];
$form['tb']['tb_drupal']['logo'] = $form['logo'];
$form['tb']['tb_drupal']['favicon'] = $form['favicon'];

$form['tb']['tb_drupal']['theme_settings']['breadcrumb'] = array(
  '#type' => 'checkbox',
  '#title' => t("Breadcrumb"),
  '#default_value' => theme_get_setting('breadcrumb')
);


/* Delta Support */
if (isset($deltaname)) {
  $form['delta_css'] = array('#type' => 'value', '#value' => $deltaname);
}else{
  $form['delta_css'] = array('#type' => 'value', '#value' => NULL);
}


unset($form['theme_settings']);
unset($form['logo']);
unset($form['favicon']);


$form_state['build_info']['files'][] = str_replace("/$theme.info", '', $themes[$theme]->filename) . '/theme-settings.php';

return $form;
}


// function bootstrap_form_system_theme_settings_submit($form, &$form_state) {
//   // find the textarea value in $form_state['values]
//   dpm("Submit callback was called");
// }

/**
 * Drupal 7.x-dev Core Bug http://drupal.org/node/1296362
 *
 * Getting AJAX Error when handling ajax request in hook_form_alter where form
 * element has #element_validate that comes from a them
 *
 * @todo : Load Validates after bug fixed...
 *

  foreach (file_scan_directory( drupal_get_path('theme', 'bootstrap')  . '/plugins', '/validate.inc/i') as $file) {
    require_once($file->uri);
  }

*/
