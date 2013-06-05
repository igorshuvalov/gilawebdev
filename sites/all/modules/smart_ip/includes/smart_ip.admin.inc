<?php

/**
 * @file
 * Admin interface callbacks/handlers to configure Smart IP.
 */

/**
 * Smart IP administration settings.
 *
 * @return
 *   Forms for store administrator to set configuration options.
 */
function smart_ip_admin_settings($form, &$form_state) {
  // Define submit handler function
  $form['#submit'][] = 'smart_ip_admin_settings_submit';
  $form['#validate'][] = 'smart_ip_admin_settings_validate';
  $smart_ip_source = variable_get('smart_ip_source', 'ipinfodb_service');
  if ($smart_ip_source == 'local_db') {
    $recover = !variable_get('smart_ip_db_update_busy', FALSE) & (variable_get('smart_ip_get_zip_done', FALSE) | variable_get('smart_ip_extract_zip_done', FALSE) | variable_get('smart_ip_store_location_csv_done', FALSE));
    // Container for database update preference forms 
    $form['smart_ip_database_update'] = array(
      '#type'        => 'fieldset',
      '#title'       => t('Manual database update'),
      '#collapsible' => FALSE,
      '#collapsed'   => FALSE,
      '#states'      => array(
        'visible' => array(
          ':input[name="smart_ip_source"]' => array('value' => 'local_db'),
        ),
      ),
    );
    $update_time = variable_get('smart_ip_last_update', 0);
    // Form for message markup
    $form['smart_ip_database_update']['smart_ip_update_message'] = array(
      '#type'   => 'item',
      '#markup' => '<div>' . t('The Smart IP database may be updated manually by pressing the "Update database now" button below. Note, this may take more or less five hours (it depends on the speed of the server). This process can recover from where it stopped or failed.') . '</div>',
      '#suffix' => isset($form_state['storage']['smart_ip_db_message']) ? '<div id="database-update" class="messages">' . $form_state['storage']['smart_ip_db_message'] . '</div>' : '<div id="database-update" class="messages">' . t('Database last updated on ') . format_date($update_time, 'custom', 'n/j/Y') . t(' at ') . format_date($update_time, 'custom', 'H:i:s T') . '</div>',
    );
    $form['smart_ip_database_update']['smart_ip_csv_source'] = array(
      '#type'          => 'textfield',
      '#title'         => t('CSV URL source'),
      '#default_value' => smart_ip_get_csv_source_filename(),
      '#description'   => t("Enter the Maxmind's CSV URL, source for updating the Smart IP database"),
      '#size'          => 120,
    );
    // Form for manual updating of the Smart IP database
    $form['smart_ip_database_update']['smart_ip_update_database'] = array(
      '#type'     => 'submit',
      '#value'    => $recover ? t('Recover database update') : t('Update database now'),
      '#submit'   => array('_smart_ip_database_update_submit'),
      '#validate' => array('_smart_ip_database_update_validate'),
      '#suffix'   => $recover ? '<div class="messages error">' . t('The previous attempt of updating Smart IP database has failed. Press the button above to continue the unfinished task.') . '</div>' : '',
    );
  }
  
  // Container for manual lookup
  $form['smart_ip_manual_lookup'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Manual lookup'),
    '#description' => t('Examine database values'),
    '#collapsible' => FALSE,
    '#collapsed'   => FALSE,
  );

  // Form for manual lookups
  $form['smart_ip_manual_lookup']['smart_ip_lookup'] = array(
    '#type'        => 'textfield',
    '#title'       => t('IP address'),
    '#description' => t('An IP address may be looked up in the database by entering the address above then pressing the %lookup button below.', array('%lookup' => t('Lookup'))),
  );

  // Form for manual updating of the IP-Country database
  $form['smart_ip_manual_lookup']['smart_ip_lookup_button'] = array(
    '#type'   => 'submit',
    '#value'  => t('Lookup'),
    '#submit' => array('_smart_ip_lookup_submit'),
    '#ajax'   => array(
      'callback' => '_smart_ip_lookup_js',
    ),
    '#suffix' => isset($form_state['storage']['smart_ip_message']) ? '<div id="lookup-message" class="messages">' . $form_state['storage']['smart_ip_message'] . '</div>' : '',
  );

  // Container for Smart IP source forms
  $form['smart_ip_source_selection'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Smart IP source'),
    '#description'   => t('Please select only one source:'),
    '#collapsible' => FALSE,
    '#collapsed'   => FALSE,
  );
  
  // Form for Smart IP source selection
  $form['smart_ip_source_selection']['smart_ip_source'] = array(
    '#type'          => 'radios',
    '#title'         => t('Select Smart IP source'),
    '#description'   => t('Please populate the appropriate fields below according to your selected Smart IP source.'),
    '#options' => array(
      'ipinfodb_service' => t('Use IPInfoDB service, IPInfoDB.com service will be used to query Geo IP information instead of Smart IP database.'),
      'maxmindgeoip_service' => t('Use Maxmind service, geoip.maxmind.com service will be used to query Geo IP information instead of Smart IP database. For using this, you need to buy a developer key.'),
      'local_db' => t("Use Smart IP database, the site's local database populated from Maxmind's CSV will be used to query Geo IP information. Note: this option is very expensive to run and it requires about 450MB database and 600MB additional database space for temporary working table."),
    ),
    '#default_value' => variable_get('smart_ip_source', 'ipinfodb_service'),
  );
  
  // Form to select IPInfoDB API version
  $form['smart_ip_source_selection']['smart_ip_use_ipinfodb_api_version'] = array(
    '#type'          => 'select',
    '#title'         => t('IPInfoDB API version'),
    '#default_value' => variable_get('smart_ip_use_ipinfodb_api_version', 3),
    '#options'       => array(2 => 2, 3 => 3),
    '#description'   => t('IPInfoDB.com version 2 do have region code, in version 3 it was removed.'),
    '#states'        => array(
      'visible' => array(
        ':input[name="smart_ip_source"]' => array('value' => 'ipinfodb_service'),
      ),
    ),
  );
  
  // Form for entering IPInfoDB key
  $form['smart_ip_source_selection']['smart_ip_ipinfodb_key'] = array(
    '#type'          => 'textfield',
    '#title'         => t('IPInfoDB key'),
    '#description'   => t('The use of IPInfoDB.com service requires API key. Registration for the new API key is free, sign up !here.', array('!here' => l(t('here'), 'http://www.ipinfodb.com/register.php'))),
    '#default_value' => variable_get('smart_ip_ipinfodb_key', ''),
    '#states'        => array(
      'visible' => array(
        ':input[name="smart_ip_source"]' => array('value' => 'ipinfodb_service'),
      ),
    ),
  );

  // Form for choosing Maxmind GeoIP service
  $form['smart_ip_source_selection']['smart_ip_maxmind_service'] = array(
    '#type'          => 'select',
    '#title'         => t('Maxmind GeoIP service'),
    '#description'   => t('Choose service. Only Country is available at the moment.'),
    '#options' => array(
        'country' => t('Country'),
        //@TODO Use other services
        /*'city' => t('City'),
        'city_isp_org' => t('City/ISP/Org'),
        'omni' => t('Omni'),*/
    ),
    '#default_value' => variable_get('smart_ip_maxmind_service', 'country'),
    '#states'        => array(
      'visible' => array(
        ':input[name="smart_ip_source"]' => array('value' => 'maxmindgeoip_service'),
      ),
    ),
  );

  // Form for entering Maxmind GeoIP key
  $form['smart_ip_source_selection']['smart_ip_maxmind_key'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Maxmind GeoIP developer key'),
    '#description'   => t('The use of geoip.maxmind.com service requires developer key.'),
    '#default_value' => variable_get('smart_ip_maxmind_key', ''),
    '#states'        => array(
      'visible' => array(
        ':input[name="smart_ip_source"]' => array('value' => 'maxmindgeoip_service'),
      ),
    ),
  );
  
  // Form to enable automatic Smart IP database update every one month
  $form['smart_ip_source_selection']['smart_ip_auto_update'] = array(
    '#type'          => 'select',
    '#title'         => t('Automatic Smart IP database update'),
    '#description'   => t('Database will be automatically updated via cron.php every one month (Maxmind updates every first day of a month). !cron must be enabled for this to work.', array('!cron' => l(t('Cron'), 'admin/config/system/cron'))),
    '#options' => array(
       TRUE  => t('Yes'),
       FALSE => t('No'),
     ),
    '#default_value' => variable_get('smart_ip_auto_update', TRUE),
    '#states'        => array(
      'invisible' => array(
        ':input[name="smart_ip_source"]' => array('value' => 'ipinfodb_service'),
      ),
    ),
  );
  
  // Container for preference forms
  $form['smart_ip_preferences'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Smart IP settings'),
    '#collapsible' => FALSE,
    '#collapsed'   => FALSE,
  );
  
  // Form to select user roles to geolocate
  drupal_add_js(drupal_get_path('module', 'smart_ip') . '/js/smart_ip-admin.js');
  $form['smart_ip_preferences']['smart_ip_roles_to_geolocate'] = array(
    '#type'          => 'checkboxes',
    '#title'         => t('Roles To Geolocate'),
    '#default_value' => variable_get('smart_ip_roles_to_geolocate', array(DRUPAL_AUTHENTICATED_RID)),
    '#options'       => user_roles(),
    '#description'   => t('Select the roles you wish to geolocate. Note that selecting the anonymous role will add substantial overhead.'),
  );
  
  // Form to turn on save user location in $user object upon registration
  $form['smart_ip_preferences']['smart_ip_save_user_location_creation'] = array(
    '#type'          => 'checkbox',
    '#title'         => t("Save user's location details upon creation"),
    '#default_value' => variable_get('smart_ip_save_user_location_creation', TRUE),
    '#description'   => t("One time storing of user's location details upon registration."),
  );
  
  // Form to turn on debugging
  $form['smart_ip_preferences']['smart_ip_debug'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Admin debug'),
    '#default_value' => variable_get('smart_ip_debug', FALSE),
    '#description'   => t('Enables administrator to spoof an IP Address for debugging purposes.'),
  );

  $form['smart_ip_preferences']['smart_ip_test_ip_address'] = array(
    '#type'          => 'textfield',
    '#title'         => t('IP address to use for testing'),
    '#default_value' => variable_get('smart_ip_test_ip_address', ip_address()),
  );
  return system_settings_form($form);
}

/**
 * Validation handler to update the Smart IP database.
 */
function _smart_ip_database_update_validate($form, &$form_state) {
  global $_smart_ip_db_update_access;
  if (variable_get('smart_ip_db_update_busy', FALSE) && !$_smart_ip_db_update_access) {
    form_set_error('smart_ip_update_database', t('Smart IP database update has already been initiated by cron'));
  }
}

/**
 * Submit handler to update the Smart IP database.
 */
function _smart_ip_database_update_submit($form, &$form_state) {
  global $_smart_ip_db_update_access;
  // Utility functions for loading database from external sources
  module_load_include('inc', 'smart_ip', 'includes/smart_ip.utility');
  if ($_smart_ip_db_update_access) {
   $watchdog_msg = 'The Smart IP database has been updated via cron.';
    $_smart_ip_db_update_access = FALSE;
  }
  else {
    $watchdog_msg = 'The Smart IP database has been manually updated.';
  }
  batch_set(smart_ip_update_db_batch(check_url($form_state['values']['smart_ip_csv_source'])));
  watchdog('smart_ip', $watchdog_msg);
  $form_state['storage']['smart_ip_db_message'] = t('The Smart IP database has been updated. @rows rows affected.', array('@rows' => smart_ip_get_count()));
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler to lookup an IP address in the database.
 *
 * @see _smart_ip_lookup_js()
 */
function _smart_ip_lookup_submit($form, &$form_state) {
  $lookup    = $form_state['values']['smart_ip_lookup'];
  // Return results of manual lookup
  $location = smart_ip_get_location($lookup);
  if ($location) {
    $message = '<p>' . t('IP Address @ip is assigned to the following location details:', array('@ip' => $lookup)) . '</p><dl>' .
      '<dt>' . t('Country:') . '</dt>' .
      '<dd>' . t('%country', array('%country' => $location['country'])) . '</dd>' .
      '<dt>' . t('Region:') . '</dt>' .
      '<dd>' . t('%region', array('%region' => $location['region'])) . '</dd>' .
      '<dt>' . t('City:') . '</dt>' .
      '<dd>' . t('%city', array('%city' => $location['city'])) . '</dd>' .
      '<dt>' . t('Postal code:') . '</dt>' .
      '<dd>' . t('%zip', array('%zip' => $location['zip'])) . '</dd>' .
      '<dt>' . t('Latitude:') . '</dt>' .
      '<dd>' . t('%latitude', array('%latitude' => $location['latitude'])) . '</dd>' .
      '<dt>' . t('Longitude:') . '</dt>' .
      '<dd>' . t('%longitude', array('%longitude' => $location['longitude'])) . '</dd>' .
    '</dl>';
  }
  else {
    $message = t('IP Address @ip is not assigned to any location.', array('@ip' => $lookup));
  }
  $form_state['storage']['smart_ip_message'] = $message;
  $form_state['rebuild'] = TRUE;
}

function smart_ip_admin_settings_validate($form, &$form_state) {
  if ($form_state['values']['smart_ip_source'] == 'ipinfodb_service' && empty($form_state['values']['smart_ip_ipinfodb_key'])) {
    form_set_error('smart_ip_ipinfodb_key', t('Please provide IPInfoDB key.'));
  }
  $ipinfodb_key = variable_get('smart_ip_ipinfodb_key', '');
  if ($form_state['values']['smart_ip_ipinfodb_key'] != $ipinfodb_key) {
    variable_set('smart_ip_correct_ipinfodb_key', FALSE);
  }
  if ($form_state['values']['smart_ip_source'] == 'maxmindgeoip_service' && empty($form_state['values']['smart_ip_maxmind_key'])) {
    form_set_error('smart_ip_maxmind_key', t('Please provide Maxmind GeoIP developer key.'));
  }
}

/**
 * AJAX callback to lookup an IP address in the database.
 *
 * @see _smart_ip_lookup_submit()
 */
function _smart_ip_lookup_js($form, $form_state) {
  $commands = array();
  $commands[] = ajax_command_remove('#lookup-message');
  $commands[] = ajax_command_after('#edit-smart-ip-lookup-button', '<div id="lookup-message" class="messages"></div>');
  $commands[] = ajax_command_html('#lookup-message', $form_state['storage']['smart_ip_message']);
  return array('#type' => 'ajax', '#commands' => $commands);  
}

/**
 * Process Forms submitted by IP to Country administration page
 */
function smart_ip_admin_settings_submit($form, &$form_state) {
  global $user;

  // Save the roles to geolocate
  $roles_to_geolocate = array();
  foreach ($form_state['values']['smart_ip_roles_to_geolocate'] as $rid => $value) {
    if($rid == $value){
      $roles_to_geolocate[] = $rid;
    }
  }
  variable_set('smart_ip_roles_to_geolocate', $roles_to_geolocate);
  // Exclude unnecessary elements from being saved in variable table
  unset(
    $form_state['values']['smart_ip_lookup'], 
    $form_state['values']['smart_ip_csv_source'],
    $form_state['values']['smart_ip_roles_to_geolocate']
  );

  // Check to see if debug set
  if ($form_state['values']['smart_ip_debug']) {
    // Debug on
    $ip = $form_state['values']['smart_ip_test_ip_address'];
    $smart_ip_session = smart_ip_session_get('smart_ip');
    $smart_ip_session['debug_mode'] = TRUE;
    smart_ip_session_set('smart_ip', $smart_ip_session);
    $location = smart_ip_get_location($ip);
  }
  else {
    // Debug off - make sure we set/reset to their real values
    $location = smart_ip_get_current_visitor_location_data();
  }
  if ($location) {
    drupal_set_message(t('Using @type IP: %ip / Country: %country / Region: %region / City: %city / Postal code: %zip / Longitude: %long / Latitude: %lat', array(
      '@type'    => $form_state['values']['smart_ip_debug'] ? 'debug' : 'actual',
      '%ip'      => $ip, 
      '%country' => $location['country'],
      '%region'  => $location['region'],
      '%city'    => $location['city'],
      '%zip'     => $location['zip'],
      '%long'    => $location['longitude'],
      '%lat'     => $location['latitude'],
    )));
    $smart_ip_session = smart_ip_session_get('smart_ip');
    // Finally if it has been determined, store the location in the $user object
    if ($form_state['values']['smart_ip_debug']) {
      smart_ip_set_user_data($user, $location);
      $smart_ip_session['location'] = $location;
      smart_ip_session_set('smart_ip', $smart_ip_session);
      if (module_exists('device_geolocation')) {
        smart_ip_session_set('device_geolocation', NULL);
        device_geolocation_get_coordinates();
      }
    }
    else {
      if (isset($smart_ip_session['debug_mode']) && !is_null($smart_ip_session['debug_mode'])) {
        unset($user->data['geoip_location'], $smart_ip_session['debug_mode']);
        $smart_ip_session['location'] = $location;
        smart_ip_session_set('device_geolocation', NULL);
        smart_ip_session_set('smart_ip', $smart_ip_session);
        smart_ip_set_user_data($user, $location);
        if (module_exists('device_geolocation')) {
          device_geolocation_get_coordinates();
        }
      }
      else {
        smart_ip_set_session_data($location);
        smart_ip_set_user_data($user, $smart_ip_session['location']);
      }
    }
  }
  else {
    drupal_set_message(t('IP Address @ip is not assigned to any location.', array('@ip' => $ip)));
  }
}