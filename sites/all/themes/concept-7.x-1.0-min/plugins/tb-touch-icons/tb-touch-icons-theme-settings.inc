<?php

$form['tb']['tb_touch_icon'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('iOS touch icon'),
  // '#description'   => t("iOS touch icon parameters are configured here."),
  '#weight'        => 4,
);


// display toggles
$form['tb']['tb_touch_icon']['toggle_touch_icon_plain'] = array(
  '#type' => 'checkbox',
  '#title' => t('iOS touch icon'),
  '#default_value' => theme_get_setting('toggle_touch_icon_plain'),
);
$form['tb']['tb_touch_icon']['toggle_touch_icon_precomp'] = array(
  '#type' => 'checkbox',
  '#title' => t('iOS touch icon (precomposed)'),
  '#default_value' => theme_get_setting('toggle_touch_icon_precomp'),
);


// plain touch icon settings
$form['tb']['tb_touch_icon']['plain'] = array(
  '#type'        => 'fieldset',
  '#title'       => t('iOS touch icon'),
  '#description' => t('Most iOS devices can display this kind of icon. Rounded corners and a glass-effect overlay are applied by the iOS device.'),
  '#collapsible' => TRUE,
  '#collapsed'   => FALSE,
  // '#element_validate' => array('_bootstrap_plain_validate'),

  '#states' => array(
    'visible' => array(
      ':input[name="toggle_touch_icon_plain"]' => array('checked' => TRUE),
    ),
  ),

);
$form['tb']['tb_touch_icon']['plain']['default_touch_icon_plain'] = array(
  '#type' => 'checkbox',
  '#title' => t('Use the default iOS touch icon.'),
  '#default_value' => theme_get_setting('default_touch_icon_plain'),
  '#tree' => FALSE,
  '#description' => t('Check here if you want the theme to use the touch icon supplied with it.'),
);
$form['tb']['tb_touch_icon']['plain']['settings'] = array(
  '#type' => 'container',
  '#states' => array(
    // Hide the plain icon settings when using the default plain icon.
    'invisible' => array(
      'input[name="default_touch_icon_plain"]' => array('checked' => TRUE),
    ),
  ),
);
$touch_icon_path_plain = theme_get_setting('touch_icon_path_plain');
// If $touch_icon_path_plain is a public:// URI, display the path relative
// to the files directory; stream wrappers are not end-user friendly.
if (file_uri_scheme($touch_icon_path_plain) == 'public') {
  $touch_icon_path_plain = file_uri_target($touch_icon_path_plain);
}
$form['tb']['tb_touch_icon']['plain']['settings']['touch_icon_path_plain'] = array(
  '#type' => 'textfield',
  '#title' => t('Path to custom icon'),
  '#default_value' => $touch_icon_path_plain,
  '#description' => t('The path to the file you would like to use as your touch icon instead of the default touch icon.'),
);

// $form['tb']['tb_touch_icon']['plain']['settings']['touch_icon_upload_plain'] = array(
//   '#type' => 'file',
//   '#title' => t('Upload icon image'),
//   '#description' => t("If you don't have direct file access to the server, use this field to upload your touch icon."),
// );


// If there is already an uploaded image display the image here.
if ( $touch_icon_upload_plain_fid = theme_get_setting('touch_icon_upload_plain') ) {

  $image = file_load($touch_icon_upload_plain_fid);
  if (!empty($image)) {
    $options = array(
      'style_name' => 'thumbnail',
      'path' => $image->uri,
    );

    $form['tb']['tb_touch_icon']['plain']['settings']['touch_icon_upload_plain_image']  = array(
      '#type' => 'container',
      '#children' => theme('image_style', $options),
      // '#states' => array(
      //   'visible' => array(
      //     ':input[name="background_custom_enable"]' => array('checked' => TRUE),
      //   ),
      // ),
    );
  }
}



// Use the #managed_file FAPI element to upload an image file.
$form['tb']['tb_touch_icon']['plain']['settings']['touch_icon_upload_plain'] = array(
  '#title' => t('Upload icon image'),
  '#type' => 'managed_file',
  '#description' => t('If you don\'t have direct file access to the server, use this field to upload your touch icon.'),
  '#default_value' => theme_get_setting('touch_icon_upload_plain'),
  '#upload_location' => 'public://',
    // '#states' => array(
    //     'visible' => array(
    //       ':input[name="default_touch_icon_plain"]' => array('checked' => TRUE),
    //     ),
    // ),
);


/*
    <!-- precomposed touch icon settings
    ================================================== -->
*/

$form['tb']['tb_touch_icon']['precomp'] = array(
  '#type'        => 'fieldset',
  '#title'       => t('iOS touch icon (precomposed)'),
  '#description' => t('Using a &apos;precomposed&apos; touch icon allows more control over the icon&apos;s appearance. iOS devices do not apply any special effects to these icons. It is <em>highly recommended</em> that you also enable a plain version, as early iOS versions do not support precomposed icons.'),
  '#collapsible' => TRUE,
  '#collapsed'   => FALSE,
// '#element_validate' => array('_bootstrap_precomp_validate'),

  '#states' => array(
    'visible' => array(
      ':input[name="toggle_touch_icon_precomp"]' => array('checked' => TRUE),
    ),
  ),

);
$form['tb']['tb_touch_icon']['precomp']['default_touch_icon_precomp'] = array(
  '#type' => 'checkbox',
  '#title' => t('Use the default precomposed iOS touch icon.'),
  '#default_value' => theme_get_setting('default_touch_icon_precomp'),
  '#tree' => FALSE,
  '#description' => t('Check here if you want the theme to use the precomposed touch icon supplied with it.'),
);
$form['tb']['tb_touch_icon']['precomp']['settings'] = array(
  '#type' => 'container',
  '#states' => array(
    // Hide the precomp icon settings when using the default precomp icon.
    'invisible' => array(
      'input[name="default_touch_icon_precomp"]' => array('checked' => TRUE),
    ),
  ),
);
$touch_icon_path_precomp = theme_get_setting('touch_icon_path_precomp');
// If $touch_icon_path_precomp is a public:// URI, display the path relative
// to the files directory; stream wrappers are not end-user friendly.
if (file_uri_scheme($touch_icon_path_precomp) == 'public') {
  $touch_icon_path_precomp = file_uri_target($touch_icon_path_precomp);
}
$form['tb']['tb_touch_icon']['precomp']['settings']['touch_icon_path_precomp'] = array(
  '#type' => 'textfield',
  '#title' => t('Path to custom precomposed icon'),
  '#default_value' => $touch_icon_path_precomp,
  '#description' => t('The path to the file you would like to use as your precomposed touch icon instead of the default precomposed touch icon.'),
);

// $form['tb']['tb_touch_icon']['precomp']['settings']['touch_icon_upload_precomp'] = array(
//   '#type' => 'file',
//   '#title' => t('Upload precomposed icon image'),
//   '#description' => t("If you don't have direct file access to the server, use this field to upload your precomposed touch icon."),
// );

// If there is already an uploaded image display the image here.
if ( $touch_icon_upload_precomp_fid = theme_get_setting('touch_icon_upload_precomp') ) {

  $image = file_load($touch_icon_upload_precomp_fid);
  if (!empty($image)) {
    $options = array(
      'style_name' => 'thumbnail',
      'path' => $image->uri,
    );

    $form['tb']['tb_touch_icon']['precomp']['settings']['touch_icon_upload_precomp_image']  = array(
      '#type' => 'container',
      '#children' => theme('image_style', $options),
      // '#states' => array(
      //   'visible' => array(
      //     ':input[name="background_custom_enable"]' => array('checked' => TRUE),
      //   ),
      // ),
    );
  }
}



// Use the #managed_file FAPI element to upload an image file.
$form['tb']['tb_touch_icon']['precomp']['settings']['touch_icon_upload_precomp'] = array(
  '#title' => t('Upload icon image'),
  '#type' => 'managed_file',
  '#description' => t('If you don\'t have direct file access to the server, use this field to upload your touch icon.'),
  '#default_value' => theme_get_setting('touch_icon_upload_precomp'),
  '#upload_location' => 'public://',
    // '#states' => array(
    //     'visible' => array(
    //       ':input[name="default_touch_icon_plain"]' => array('checked' => TRUE),
    //     ),
    // ),
);
