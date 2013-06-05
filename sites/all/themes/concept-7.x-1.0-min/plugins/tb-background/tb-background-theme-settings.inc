<?php

// drupal_add_js(drupal_get_path('theme', 'bootstrap') . "/plugins/tb-background/tb-background-admin.js", 'file');
// drupal_add_css(drupal_get_path('theme', 'bootstrap') . "/plugins/tb-background/tb-background-admin.css");
//

/**
 * Pattern Images List
 * @var array
 */
$bg_patterns = array();
foreach (file_scan_directory(drupal_get_path('theme', 'bootstrap') . '/assets/images/patterns', '/\.(jpg|gif|png?)$/', array('nomask' => '/(@2X|@2x).(jpg|gif|png?)$/') ) as $file) {
  $key = $file->filename;
  $title = ucfirst(str_replace("_", " ", $file->name));
  $img = theme('image', array(
    'path' => $base_path . drupal_get_path('theme', 'bootstrap' ) . '/assets/images/patterns/'. $key,
    'attributes' => array(
      'class' => 'radio-image element-invisible'
      ),
    ));
  $bg_patterns[$key] = $img . "<span>".$title."</span>"  ;
}
asort($bg_patterns, SORT_STRING);
array_unshift($bg_patterns,"<span class=''>Disable</span>");

/**
 * Background Images List
 * [$bg_images description]
 * @var array
 */
// $bg_images = array();
// foreach (file_scan_directory(drupal_get_path('theme', 'bootstrap') . '/assets/images/backgrounds', '/\.(jpg|gif|png?)$/', array('nomask' => '/(@2X|@2x).(jpg|gif|png?)$/') ) as $file) {
//   $key = $file->filename;
//   $title = ucfirst(str_replace("_", " ", $file->name));
//   $img = theme('image', array(
//     'path' => $base_path . drupal_get_path('theme', 'bootstrap' ) . '/assets/images/backgrounds/'. $key,
//     'attributes' => array(
//       'class' => 'radio-image element-invisible'
//       ),
//     ));
//   $bg_images[$key] = $img . "<span>".$title."</span>"  ;

// }
// asort($bg_images, SORT_STRING);
// array_unshift($bg_images,"<span class=''>Disable</span>");


$form['tb']['tb_background'] = array(
  '#type'        => 'fieldset',
  '#title'       => t('Background settings'),
  // '#description'   => t("Background parameters are configured here."),
  '#weight'        => 0,
);

// <!-- Gradient Background
// ================================================== -->
$form['tb']['tb_background']['gradient_enable'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Enable background gradient'),
  '#default_value' => theme_get_setting('gradient_enable'),
);

$form['tb']['tb_background']["gradient"] = array(
  '#title' => t('Background gradient'),
  '#type' => 'fieldset',
  '#states' => array(
      // Hide the settings when the cancel notify checkbox is disabled.
      'visible' => array(
       ':input[name="gradient_enable"]' => array('checked' => TRUE),
      ),
    ),
);

$form['tb']['tb_background']["gradient"]['gradient_opacity'] = array(
  '#type' => 'textfield',
  '#title' => t('Gradient opacity'),
  '#default_value' => theme_get_setting('gradient_opacity'),
  '#size' => 3,
  '#maxlength' => 3,
  // '#disabled' => TRUE,
  '#attributes'    => array( 'class' => array('tb-slider-field') ),
  '#description' => t('Opacity of this background. If you lower the opacity the gradient will blend with the background color.'),
  // '#element_validate' => array('_tb_is_number'),
);

$form['tb']['tb_background']["gradient"]['gradient_color_top'] = array(
  '#type' => 'textfield',
  '#title' => t('Top color'),
  '#default_value' => (theme_get_setting('gradient_color_top')) ? theme_get_setting('gradient_color_top') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  // '#element_validate' => array('_tb_is_hex_color'),
);

$form['tb']['tb_background']["gradient"]['gradient_color_bottom'] = array(
  '#type' => 'textfield',
  '#title' => t('Bottom color'),
  '#default_value' => (theme_get_setting('gradient_color_bottom')) ? theme_get_setting('gradient_color_bottom') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  // '#element_validate' => array('_tb_is_hex_color'),
);

// <!-- Background Image
// ================================================== -->
$form['tb']['tb_background']['bg_image_enable'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Enable background image'),
  '#default_value' => theme_get_setting('bg_image_enable'),
);


$form['tb']['tb_background']["image"] = array(
  '#title' => t('Background image'),
  '#type' => 'fieldset',
  '#states' => array(
    // Hide the settings when the cancel notify checkbox is disabled.
    'visible' => array(
     ':input[name="bg_image_enable"]' => array('checked' => TRUE),
    ),
  ),
);

$form['tb']['tb_background']["image"]['image_opacity'] = array(
  '#type' => 'textfield',
  '#title' => t('Image opacity'),
  '#default_value' => theme_get_setting('image_opacity'),
  '#prefix' => '<div id="image-opacity-slider"></div>',
  '#size' => 3,
  // '#disabled' => TRUE,
  '#attributes'    => array( 'class' => array('tb-slider-field') ),
  '#maxlength' => 3,
  '#description' => t('Opacity of this background. If you lower the opacity the background color and/or gradient will blend with the image. Using a low opacity you can easily add textures to your background colors.'),
  // '#element_validate' => array('_tb_is_number'),
);

$form['tb']['tb_background']["image"]['bg_behave'] = array(
  '#type'          => 'radios',
  '#title'         => t('Background image behavior'),
  '#default_value' => theme_get_setting('bg_behave'),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#options'       => array(
    'repeat' => 'Repeat',
    'cover' => 'Cover'
    ),
);


$form['tb']['tb_background']["image"]['background_pattern'] = array(
  '#type'          => 'radios',
  '#title'         => t('Background Patterns'),
  '#default_value' => theme_get_setting('background_pattern'),
  '#attributes'    => array( 'class' => array('tb-pattern') ),
  '#options'       => $bg_patterns,
  '#description'   => t('All Patterns is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/deed.en_US">Creative Commons Attribution-ShareAlike 3.0 Unported License</a> Please visit <a href="http://subtlepatterns.com">Subtle Patterns</a> For more resources and information'),
  '#states' => array(
    'invisible' => array(
      ':input[name="background_custom_enable"]' => array('checked' => TRUE),
    ),
  ),
);

$form['tb']['tb_background']["image"]['background_custom_enable'] = array(
  '#type'          => 'checkbox',
  '#title'         => t('Enable Background Custom'),
  '#default_value' => theme_get_setting('background_custom_enable'),
);

// $form['tb']['tb_background']["image"]['background_images'] = array(
//   '#type'          => 'radios',
//   '#title'         => t('Background Images'),
//   '#default_value' => theme_get_setting('background_images'),
//   '#attributes'    => array( 'class' => array('tb-pattern','wide-bg') ),
//   '#options'       => $bg_images,
//   '#description'   => t('All Background images are licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/deed.en_US">Creative Commons Attribution-ShareAlike 3.0 Unported License</a>')
// );

$background_custom_path = theme_get_setting('background_custom_path');
if (file_uri_scheme($background_custom_path) == 'public') {
  $background_custom_path = file_uri_target($background_custom_path);
}
$form['tb']['tb_background']["image"]['background_custom_path'] = array(
  '#type' => 'textfield',
  '#title' => t('Path to custom background'),
  '#default_value' => $background_custom_path,
  '#states' => array(
    'visible' => array(
      ':input[name="background_custom_enable"]' => array('checked' => TRUE),
    ),
  ),
  '#description' => t('The path to the file you would like to use as your Background.'),
);

// If there is already an uploaded image display the image here.
if ( $background_custom_upload_fid = theme_get_setting('background_custom_upload') ) {

  $image = file_load($background_custom_upload_fid);
  if (!empty($image)) {
    $options = array(
      'style_name' => 'thumbnail',
      'path' => $image->uri,
    );

    $form['tb']['tb_background']["image"]['background_custom_upload_image'] = array(
      '#type' => 'container',
      '#children' => theme('image_style', $options),
      '#states' => array(
        'visible' => array(
          ':input[name="background_custom_enable"]' => array('checked' => TRUE),
        ),
      ),
    );
  }
}

// Use the #managed_file FAPI element to upload an image file.
$form['tb']['tb_background']["image"]['background_custom_upload'] = array(
  '#title' => t('Custom image'),
  '#type' => 'managed_file',
  '#description' => t('The path to the file you would like to use as your Footer Background.'),
  '#default_value' => theme_get_setting('background_custom_upload'),
  '#upload_location' => 'public://',
    '#states' => array(
      'visible' => array(
        ':input[name="background_custom_enable"]' => array('checked' => TRUE),
      ),
  ),
);
