<?php


/**
 * Validate custom Header Background settings
 */
function _bootstrap_header_validate($element, &$form_state) {

  if (!$form_state['values']['header_style']) {
    $form_state['values']['header_custom_path'] = "";
    return;
  }


  if ($form_state['values']['header_style'] == 'custom') {
    $path = _system_theme_settings_validate_path($form_state['values']['header_custom_path']);
    if (!$path && $path <> "") {
      form_set_error('header_custom_path', t('The custom Header Background path is invalid.'));
      return;
    }
  }

  // Handle file uploads.
  $validators = array('file_validate_is_image' => array());

  // Check for a new uploaded Header Background.
  $file = file_save_upload('header_custom_upload', $validators);
  if (isset($file)) {
    // File upload was attempted.
    if ($file) {
      // If the user uploaded a new Header Background, save it to a permanent
      // location and use it in place of the default theme-provided file.
      $filename = file_unmanaged_copy($file->uri);
      $form_state['values']['header_custom_path'] = $filename;
      $form_state['values']['header_style'] = 'custom';
      unset($form_state['values']['header_custom_upload']);
    }
    else {
      // File upload failed.
      form_set_error('header_custom_upload', t('The Header Background could not be uploaded.'));
      return;
    }
  }

  // If the user entered a path relative to the system files directory for a
  // Header Background, store a public:// URI so the theme system can handle it.
  if (!empty($form_state['values']['header_custom_path'])) {
    $form_state['values']['header_custom_path'] = _system_theme_settings_validate_path($form_state['values']['header_custom_path']);
  }

}


/**
 * Validate custom Header Background settings
 */
function _bootstrap_footer_validate($element, &$form_state) {

  if (!$form_state['values']['footer_style']) {
    $form_state['values']['footer_custom_path'] = "";
    return;
  }


  if ($form_state['values']['footer_style'] == 'custom') {
    $path = _system_theme_settings_validate_path($form_state['values']['footer_custom_path']);
    if (!$path && $path <> "") {
      form_set_error('footer_custom_path', t('The custom Header Background path is invalid.'));
      return;
    }
  }

  // Handle file uploads.
  $validators = array('file_validate_is_image' => array());

  // Check for a new uploaded Header Background.
  $file = file_save_upload('footer_custom_upload', $validators);
  if (isset($file)) {
    // File upload was attempted.
    if ($file) {
      // If the user uploaded a new Header Background, save it to a permanent
      // location and use it in place of the default theme-provided file.
      $filename = file_unmanaged_copy($file->uri);
      $form_state['values']['footer_custom_path'] = $filename;
      $form_state['values']['footer_style'] = 'custom';
      unset($form_state['values']['footer_custom_upload']);
    }
    else {
      // File upload failed.
      form_set_error('footer_custom_upload', t('The Header Background could not be uploaded.'));
      return;
    }
  }

  // If the user entered a path relative to the system files directory for a
  // Header Background, store a public:// URI so the theme system can handle it.
  if (!empty($form_state['values']['footer_custom_path'])) {
    $form_state['values']['footer_custom_path'] = _system_theme_settings_validate_path($form_state['values']['footer_custom_path']);
  }

}
