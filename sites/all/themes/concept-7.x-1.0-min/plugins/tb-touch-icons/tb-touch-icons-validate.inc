<?php


/**
 * Validate custom plain touch icon settings
 */
function _bootstrap_plain_validate($element, &$form_state, $form) {
  // If the user provided a path for plain touch icon
  // make sure a file exists at that path.
  if ($form_state['values']['touch_icon_path_plain']) {
    $path = _validate_path($form_state['values']['touch_icon_path_plain']);
    if (!$path) {
      form_set_error('touch_icon_path_plain', t('The custom plain-touch-icon path is invalid.'));
      return;
    }
  }

  // Handle file uploads.
  $validators = array('file_validate_is_image' => array());

  // Check for a new uploaded plain touch icon.
  $file = file_save_upload('touch_icon_upload_plain', $validators);
  if (isset($file)) {
    // File upload was attempted.
    if ($file) {
      // If the user uploaded a new plain touch-icon, save it to a permanent
      // location and use it in place of the default theme-provided file.
      $filename = file_unmanaged_copy($file->uri);
      $form_state['values']['touch_icon_path_plain'] = $filename;
      $form_state['values']['default_touch_icon_plain'] = 0;
      $form_state['values']['toggle_touch_icon_plain'] = 1;
      unset($form_state['values']['touch_icon_upload_plain']);
    }
    else {
      // File upload failed.
      form_set_error('touch_icon_upload_plain', t('The touch icon (plain) could not be uploaded.'));
      return;
    }
  }

  // If the user entered a path relative to the system files directory for a
  // plain touch icon, store a public:// URI so the theme system can handle it.
  if (!empty($form_state['values']['touch_icon_path_plain'])) {
    $form_state['values']['touch_icon_path_plain'] = _validate_path($form_state['values']['touch_icon_path_plain']);
  }
}

/**
 * Validate custom precomposed touch icon settings
 */
function _bootstrap_precomp_validate($element, &$form_state) {
  // If the user provided a path for precomposed touch icon
  // make sure a file exists at that path.
  if ($form_state['values']['touch_icon_path_precomp']) {
    $path = _validate_path($form_state['values']['touch_icon_path_precomp']);
    if (!$path) {
      form_set_error('touch_icon_path_precomp', t('The custom precomp-touch-icon path is invalid.'));
      return;
    }
  }

  // Handle file uploads.
  $validators = array('file_validate_is_image' => array());

  // Check for a new uploaded precomposed touch icon.
  $file = file_save_upload('touch_icon_upload_precomp', $validators);
  if (isset($file)) {
    // File upload was attempted.
    if ($file) {
      // If the user uploaded a new plain touch-icon, save it to a permanent
      // location and use it in place of the default theme-provided file.
      $filename = file_unmanaged_copy($file->uri);
      $form_state['values']['touch_icon_path_precomp'] = $filename;
      $form_state['values']['default_touch_icon_precomp'] = 0;
      $form_state['values']['toggle_touch_icon_precomp'] = 1;
      unset($form_state['values']['touch_icon_upload_precomp']);
    }
    else {
      // File upload failed.
      form_set_error('touch_icon_upload_precomp', t('The touch icon (precomposed) could not be uploaded.'));
      return;
    }
  }

  // If the user entered a path relative to the system files directory for
  // a precomposed touch icon, store a public:// URI so the theme system can
  // handle it.
  if (!empty($form_state['values']['touch_icon_path_precomp'])) {
    $form_state['values']['touch_icon_path_precomp'] = _validate_path($form_state['values']['touch_icon_path_precomp']);
  }
}
