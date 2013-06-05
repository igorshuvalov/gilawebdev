<?php


$patterns = array();

foreach (file_scan_directory(drupal_get_path('theme', 'bootstrap') . '/assets/images/patterns', '/\.(jpg|gif|png?)$/', array('nomask' => '/(@2X|@2x).(jpg|gif|png?)$/') ) as $file) {
  $key = $file->filename;
  $title = ucfirst(str_replace("_", " ", $file->name));
  $img = theme('image', array(
    'path' => $base_path . drupal_get_path('theme', 'bootstrap' ) . '/assets/images/patterns/'. $key,
    'attributes' => array(
      'class' => 'radio-image element-invisible'
      ),
    ));
  $patterns[$key] = $img . "<span>".$title."</span>"  ;
}
asort($patterns, SORT_STRING);
array_unshift($patterns,"<span class=''>Disable</span>");




$form['tb']['appearance'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Appearance'),
  // '#description'   => t("Appearance parameters are configured here."),
  '#weight'        => 1,
);

$form['tb']['appearance']['color_enhancements'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Color Enhancements'),
  '#weight'        => 0,
);


/**
 * Main Menu
 * ----------------------------------------------------------------------------
 */

$form['tb']['appearance']['color_enhancements']['mainmenu_region'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Main menu'),
  '#weight'        => -6,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form['tb']['appearance']['color_enhancements']['mainmenu_region']['mainmenu_selector'] = array(
  '#type' => 'hidden',
  '#value' => '#tbMainMenu',
);

$form['tb']['appearance']['color_enhancements']['mainmenu_region']['mainmenu_menu_status_region'] = array(
  '#type'          => 'radios',
  '#title'         => t('Main menu Colors'),
  '#default_value' => (theme_get_setting('mainmenu_menu_status_region')) ? theme_get_setting('mainmenu_menu_status_region') : "0",
  '#options'       => array(
    '0' => t('Default'),
    'custom' => t('Customize')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
);

$form['tb']['appearance']['color_enhancements']['mainmenu_region']['mainmenu_menu_container'] = array(
  '#type'          => 'container',
  '#attributes'    => array( 'class' => array('tb-inline-fields','six-col') ),
  '#states' => array(
    'visible' => array(
      ':input[name="mainmenu_menu_status_region"]' => array('value' =>  'custom'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['mainmenu_region']['mainmenu_menu_container']['mainmenu_link_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Link color'),
  '#default_value' => (theme_get_setting('mainmenu_link_color')) ? theme_get_setting('mainmenu_link_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
);

$form['tb']['appearance']['color_enhancements']['mainmenu_region']['mainmenu_menu_container']['mainmenu_link_hover_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Hover color'),
  '#default_value' => (theme_get_setting('mainmenu_link_hover_color')) ? theme_get_setting('mainmenu_link_hover_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
);

$form['tb']['appearance']['color_enhancements']['mainmenu_region']['mainmenu_menu_container']['mainmenu_link_hoverbg_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Hover bg'),
  '#default_value' => (theme_get_setting('mainmenu_link_hoverbg_color')) ? theme_get_setting('mainmenu_link_hoverbg_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
);

$form['tb']['appearance']['color_enhancements']['mainmenu_region']['mainmenu_menu_container']['mainmenu_active_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Active color'),
  '#default_value' => (theme_get_setting('mainmenu_active_color')) ? theme_get_setting('mainmenu_active_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
);

$form['tb']['appearance']['color_enhancements']['mainmenu_region']['mainmenu_menu_container']['mainmenu_activebg_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Active bg'),
  '#default_value' => (theme_get_setting('mainmenu_activebg_color')) ? theme_get_setting('mainmenu_activebg_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
);

$form['tb']['appearance']['color_enhancements']['mainmenu_region']['mainmenu_menu_container']['mainmenu_active_hover_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Act. hover'),
  '#default_value' => (theme_get_setting('mainmenu_active_hover_color')) ? theme_get_setting('mainmenu_active_hover_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
);

/**
 * Content Appearance parameters are configured here.
 * -----------------------------------------------------------------------------
 */

$form['tb']['appearance']['color_enhancements']['content_region'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Content Region'),
  '#weight'        => -5,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form['tb']['appearance']['color_enhancements']['content_region']['content_selector'] = array(
  '#type' => 'hidden',
  '#value' => '#tbContentBG',
);



$form['tb']['appearance']['color_enhancements']['content_region']['content_colors'] = array(
  '#type'          => 'container'
);

  $form['tb']['appearance']['color_enhancements']['content_region']['content_colors']['content_txt_status_region'] = array(
    '#type' => 'radios',
    '#title' => t('Content'),
    '#default_value' => (theme_get_setting('content_txt_status_region')) ? theme_get_setting('content_txt_status_region') : "0",
    '#attributes'    => array( 'class' => array('tb-inline-radios') ),
    '#options' => array(
      '0'     => t('Default'),
      'custom' => t('Customize'),
    )
  );

  $form['tb']['appearance']['color_enhancements']['content_region']['content_colors']['content_field_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields') ),
    '#states' => array(
      'visible' => array(
        ':input[name="content_txt_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

  $form['tb']['appearance']['color_enhancements']['content_region']['content_colors']['content_field_container']['content_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Text color'),
    '#default_value' => (theme_get_setting('content_text_color')) ? theme_get_setting('content_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['content_region']['content_colors']['content_field_container']['content_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link color'),
    '#default_value' => (theme_get_setting('content_link_color')) ? theme_get_setting('content_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['content_region']['content_colors']['content_field_container']['content_link_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link hover color'),
    '#default_value' => (theme_get_setting('content_link_hover_color')) ? theme_get_setting('content_link_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );


$form['tb']['appearance']['color_enhancements']['content_region']['content_bg_status_region'] = array(
  '#type' => 'radios',
  '#title' => t('Background'),
  '#default_value' => (theme_get_setting('content_bg_status_region')) ? theme_get_setting('content_bg_status_region') : "0",
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#options' => array(
    '0'     => t('Default'),
    'color' => t('Solid color'),
    'gradient' => t('Gradient'),
    'pattern' => t('Pattern'),
    'custom'  => t('Custom')
  )
);

$form['tb']['appearance']['color_enhancements']['content_region']['content_solid_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Content color'),
  '#default_value' => (theme_get_setting('content_solid_color')) ? theme_get_setting('content_solid_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
     ':input[name="content_bg_status_region"]' => array('value' => 'color'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['content_region']['content_gradient_top'] = array(
  '#type' => 'textfield',
  '#title' => t('Top color'),
  '#default_value' => (theme_get_setting('content_gradient_top')) ? theme_get_setting('content_gradient_top') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="content_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);
$form['tb']['appearance']['color_enhancements']['content_region']['content_gradient_bottom'] = array(
  '#type' => 'textfield',
  '#title' => t('Bottom color'),
  '#default_value' => (theme_get_setting('content_gradient_bottom')) ? theme_get_setting('content_gradient_bottom') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="content_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['content_region']['content_pattern'] = array(
  '#type'          => 'radios',
  '#title'         => t('Patterns'),
  '#default_value' => theme_get_setting('content_pattern'),
  '#options'       => $patterns,
  '#description'   => t('All Patterns is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/deed.en_US">Creative Commons Attribution-ShareAlike 3.0 Unported License</a> Please visit <a href="http://subtlepatterns.com">Subtle Patterns</a> For more resources and information'),
  '#attributes'    => array( 'class' => array('tb-pattern') ),
  '#states' => array(
    'visible' => array(
      ':input[name="content_bg_status_region"]' => array('value' => 'pattern'),
    ),
  ),

);


$form['tb']['appearance']['color_enhancements']['content_region']['content_custom_behave'] = array(
  '#type'          => 'radios',
  '#title'         => t('Background image behavior'),
  '#default_value' => theme_get_setting('content_custom_behave'),
  '#options'       => array(
    'repeat' => t('Repeating'),
    'cover' => t('Cover')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#states' => array(
    'visible' => array(
      ':input[name="content_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
);


$content_custom_path = theme_get_setting('content_custom_path');
if (file_uri_scheme($content_custom_path) == 'public') {
  $content_custom_path = file_uri_target($content_custom_path);
}
$form['tb']['appearance']['color_enhancements']['content_region']['content_custom_path'] = array(
  '#type' => 'textfield',
  '#title' => t('Path to custom Content'),
  '#default_value' => $content_custom_path,
  '#states' => array(
    'visible' => array(
      ':input[name="content_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
  '#description' => t('The path to the file you would like to use as your Content Background.'),
);



// If there is already an uploaded image display the image here.
if ( $content_custom_upload_fid = theme_get_setting('content_custom_upload') ) {

  $image = file_load($content_custom_upload_fid);
  if (!empty($image)) {
    $options = array(
      'style_name' => 'thumbnail',
      'path' => $image->uri,
    );

    $form['tb']['appearance']['color_enhancements']['content_region']['content_custom_upload_image'] = array(
      '#type' => 'container',
      '#children' => theme('image_style', $options),
      '#states' => array(
        'visible' => array(
          ':input[name="content_bg_status_region"]' => array('value' => 'custom'),
        ),
      ),
    );
  }
}

// Use the #managed_file FAPI element to upload an image file.
$form['tb']['appearance']['color_enhancements']['content_region']['content_custom_upload'] = array(
  '#title' => t('Custom image'),
  '#type' => 'managed_file',
  '#description' => t('The path to the file you would like to use as your Content Background.'),
  '#default_value' => theme_get_setting('content_custom_upload'),
  '#upload_location' => 'public://',
    '#states' => array(
      'visible' => array(
        ':input[name="content_bg_status_region"]' => array('value' => 'custom'),
      ),
  ),
);

/* Custom Htags for Content (H1,H2,H3,H4,H5,H6)
------------------------------------------------------------------------------*/

$form['tb']['appearance']['color_enhancements']['content_region']['content_htag_status_region'] = array(
  '#type'          => 'radios',
  '#title'         => t('Heading Colors'),
  '#default_value' => (theme_get_setting('content_htag_status_region')) ? theme_get_setting('content_htag_status_region') : "0",
  '#options'       => array(
    '0' => t('Default'),
    'custom' => t('Customize')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
);

  $form['tb']['appearance']['color_enhancements']['content_region']['content_htag_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields','six-col') ),
    '#states' => array(
      'visible' => array(
        ':input[name="content_htag_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

$htxt = 1;
do {
  $form['tb']['appearance']['color_enhancements']['content_region']['content_htag_container']['content_h'.$htxt.'_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$htxt.' text'),
    '#default_value' => (theme_get_setting('content_h'.$htxt.'_text_color')) ? theme_get_setting('content_h'.$htxt.'_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $htxt++;
} while ( $htxt <= 6);
unset($htxt);

$hlnk = 1;
do {
  $form['tb']['appearance']['color_enhancements']['content_region']['content_htag_container']['content_h'.$hlnk.'_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hlnk.' link'),
    '#default_value' => (theme_get_setting('content_h'.$hlnk.'_link_color')) ? theme_get_setting('content_h'.$hlnk.'_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hlnk++;
} while ( $hlnk <= 6);
unset($hlnk);

$hhvr = 1;
do {
  $form['tb']['appearance']['color_enhancements']['content_region']['content_htag_container']['content_h'.$hhvr.'_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hhvr.' hover'),
    '#default_value' => (theme_get_setting('content_h'.$hhvr.'_hover_color')) ? theme_get_setting('content_h'.$hhvr.'_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hhvr++;
} while ( $hhvr <= 6);
unset($hhvr);


  $form['tb']['appearance']['color_enhancements']['content_region']['content_htag_container']['content_bt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#default_value' => (theme_get_setting('content_bt_color')) ? theme_get_setting('content_bt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['content_region']['content_htag_container']['content_pt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Page title'),
    '#default_value' => (theme_get_setting('content_pt_color')) ? theme_get_setting('content_pt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['content_region']['content_htag_container']['content_border_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Border'),
    '#default_value' => (theme_get_setting('content_border_color')) ? theme_get_setting('content_border_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );





/**
 * Footer Appearance parameters are configured here.
 * -----------------------------------------------------------------------------
 */

$form['tb']['appearance']['color_enhancements']['footer_region'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Footer Region'),
  '#weight'        => 0,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form['tb']['appearance']['color_enhancements']['footer_region']['footer_selector'] = array(
  '#type' => 'hidden',
  '#value' => '#tbFooter',
);



$form['tb']['appearance']['color_enhancements']['footer_region']['footer_colors'] = array(
  '#type'          => 'container'
);

  $form['tb']['appearance']['color_enhancements']['footer_region']['footer_colors']['footer_txt_status_region'] = array(
    '#type' => 'radios',
    '#title' => t('Footer style'),
    '#default_value' => (theme_get_setting('footer_txt_status_region')) ? theme_get_setting('footer_txt_status_region') : "0",
    '#attributes'    => array( 'class' => array('tb-inline-radios') ),
    '#options' => array(
      '0'     => t('Default'),
      'custom' => t('Customize'),
    )
  );

  $form['tb']['appearance']['color_enhancements']['footer_region']['footer_colors']['footer_field_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields') ),
    '#states' => array(
      'visible' => array(
        ':input[name="footer_txt_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

  $form['tb']['appearance']['color_enhancements']['footer_region']['footer_colors']['footer_field_container']['footer_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Text color'),
    '#default_value' => (theme_get_setting('footer_text_color')) ? theme_get_setting('footer_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['footer_region']['footer_colors']['footer_field_container']['footer_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link color'),
    '#default_value' => (theme_get_setting('footer_link_color')) ? theme_get_setting('footer_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['footer_region']['footer_colors']['footer_field_container']['footer_link_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link hover color'),
    '#default_value' => (theme_get_setting('footer_link_hover_color')) ? theme_get_setting('footer_link_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );


$form['tb']['appearance']['color_enhancements']['footer_region']['footer_bg_status_region'] = array(
  '#type' => 'radios',
  '#title' => t('Background style'),
  '#default_value' => (theme_get_setting('footer_bg_status_region')) ? theme_get_setting('footer_bg_status_region') : "0",
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  // '#element_validate' => array('_bootstrap_header_validate'),
  '#options' => array(
    '0'     => t('Default'),
    'color' => t('Solid color'),
    'gradient' => t('Gradient'),
    'pattern' => t('Pattern'),
    'custom'  => t('Custom')
  )
);

$form['tb']['appearance']['color_enhancements']['footer_region']['footer_solid_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Footer color'),
  '#default_value' => (theme_get_setting('footer_solid_color')) ? theme_get_setting('footer_solid_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
     ':input[name="footer_bg_status_region"]' => array('value' => 'color'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['footer_region']['footer_gradient_top'] = array(
  '#type' => 'textfield',
  '#title' => t('Top color'),
  '#default_value' => (theme_get_setting('footer_gradient_top')) ? theme_get_setting('footer_gradient_top') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="footer_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);
$form['tb']['appearance']['color_enhancements']['footer_region']['footer_gradient_bottom'] = array(
  '#type' => 'textfield',
  '#title' => t('Bottom color'),
  '#default_value' => (theme_get_setting('footer_gradient_bottom')) ? theme_get_setting('footer_gradient_bottom') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="footer_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['footer_region']['footer_pattern'] = array(
  '#type'          => 'radios',
  '#title'         => t('Patterns'),
  '#default_value' => theme_get_setting('footer_pattern'),
  '#options'       => $patterns,
  '#description'   => t('All Patterns is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/deed.en_US">Creative Commons Attribution-ShareAlike 3.0 Unported License</a> Please visit <a href="http://subtlepatterns.com">Subtle Patterns</a> For more resources and information'),
  '#attributes'    => array( 'class' => array('tb-pattern') ),
  '#states' => array(
    'visible' => array(
      ':input[name="footer_bg_status_region"]' => array('value' => 'pattern'),
    ),
  ),

);


$form['tb']['appearance']['color_enhancements']['footer_region']['footer_custom_behave'] = array(
  '#type'          => 'radios',
  '#title'         => t('Background image behavior'),
  '#default_value' => theme_get_setting('footer_custom_behave'),
  '#options'       => array(
    'repeat' => t('Repeating'),
    'cover' => t('Cover')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#states' => array(
    'visible' => array(
      ':input[name="footer_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
);


$footer_custom_path = theme_get_setting('footer_custom_path');
if (file_uri_scheme($footer_custom_path) == 'public') {
  $footer_custom_path = file_uri_target($footer_custom_path);
}
$form['tb']['appearance']['color_enhancements']['footer_region']['footer_custom_path'] = array(
  '#type' => 'textfield',
  '#title' => t('Path to custom Footer'),
  '#default_value' => $footer_custom_path,
  '#states' => array(
    'visible' => array(
      ':input[name="footer_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
  '#description' => t('The path to the file you would like to use as your Footer Background.'),
);



// If there is already an uploaded image display the image here.
if ( $footer_custom_upload_fid = theme_get_setting('footer_custom_upload') ) {

  $image = file_load($footer_custom_upload_fid);
  if (!empty($image)) {
    $options = array(
      'style_name' => 'thumbnail',
      'path' => $image->uri,
    );

    $form['tb']['appearance']['color_enhancements']['footer_region']['footer_custom_upload_image'] = array(
      '#type' => 'container',
      '#children' => theme('image_style', $options),
      '#states' => array(
        'visible' => array(
          ':input[name="footer_bg_status_region"]' => array('value' => 'custom'),
        ),
      ),
    );
  }
}

// Use the #managed_file FAPI element to upload an image file.
$form['tb']['appearance']['color_enhancements']['footer_region']['footer_custom_upload'] = array(
  '#title' => t('Custom image'),
  '#type' => 'managed_file',
  '#description' => t('The path to the file you would like to use as your Footer Background.'),
  '#default_value' => theme_get_setting('footer_custom_upload'),
  '#upload_location' => 'public://',
    '#states' => array(
      'visible' => array(
        ':input[name="footer_bg_status_region"]' => array('value' => 'custom'),
      ),
  ),
);


/* Custom Htags (H1,H2,H3,H4,H5,H6)
------------------------------------------------------------------------------*/

$form['tb']['appearance']['color_enhancements']['footer_region']['footer_htag_status_region'] = array(
  '#type'          => 'radios',
  '#title'         => t('Heading Colors'),
  '#default_value' => (theme_get_setting('footer_htag_status_region')) ? theme_get_setting('footer_htag_status_region') : "0",
  '#options'       => array(
    '0' => t('Default'),
    'custom' => t('Customize')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
);

  $form['tb']['appearance']['color_enhancements']['footer_region']['footer_htag_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields','six-col') ),
    '#states' => array(
      'visible' => array(
        ':input[name="footer_htag_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

$htxt = 1;
do {
  $form['tb']['appearance']['color_enhancements']['footer_region']['footer_htag_container']['footer_h'.$htxt.'_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$htxt.' text'),
    '#default_value' => (theme_get_setting('footer_h'.$htxt.'_text_color')) ? theme_get_setting('footer_h'.$htxt.'_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $htxt++;
} while ( $htxt <= 6);
unset($htxt);

$hlnk = 1;
do {
  $form['tb']['appearance']['color_enhancements']['footer_region']['footer_htag_container']['footer_h'.$hlnk.'_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hlnk.' link'),
    '#default_value' => (theme_get_setting('footer_h'.$hlnk.'_link_color')) ? theme_get_setting('footer_h'.$hlnk.'_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hlnk++;
} while ( $hlnk <= 6);
unset($hlnk);

$hhvr = 1;
do {
  $form['tb']['appearance']['color_enhancements']['footer_region']['footer_htag_container']['footer_h'.$hhvr.'_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hhvr.' hover'),
    '#default_value' => (theme_get_setting('footer_h'.$hhvr.'_hover_color')) ? theme_get_setting('footer_h'.$hhvr.'_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hhvr++;
} while ( $hhvr <= 6);
unset($hhvr);

  $form['tb']['appearance']['color_enhancements']['footer_region']['footer_htag_container']['footer_bt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#default_value' => (theme_get_setting('footer_bt_color')) ? theme_get_setting('footer_bt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['footer_region']['footer_htag_container']['footer_pt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Page title'),
    '#default_value' => (theme_get_setting('footer_pt_color')) ? theme_get_setting('footer_pt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['footer_region']['footer_htag_container']['footer_border_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Border'),
    '#default_value' => (theme_get_setting('footer_border_color')) ? theme_get_setting('footer_border_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );




/**
 * Comments Appearance parameters are configured here.
 * -----------------------------------------------------------------------------
 */

$form['tb']['appearance']['color_enhancements']['comments_region'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Comments Region'),
  '#weight'        => -4,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form['tb']['appearance']['color_enhancements']['comments_region']['comments_selector'] = array(
  '#type' => 'hidden',
  '#value' => '#comments',
);



$form['tb']['appearance']['color_enhancements']['comments_region']['comments_colors'] = array(
  '#type'          => 'container'
);

  $form['tb']['appearance']['color_enhancements']['comments_region']['comments_colors']['comments_txt_status_region'] = array(
    '#type' => 'radios',
    '#title' => t('Content'),
    '#default_value' => (theme_get_setting('comments_txt_status_region')) ? theme_get_setting('comments_txt_status_region') : "0",
    '#attributes'    => array( 'class' => array('tb-inline-radios') ),
    '#options' => array(
      '0'     => t('Default'),
      'custom' => t('Customize'),
    )
  );

  $form['tb']['appearance']['color_enhancements']['comments_region']['comments_colors']['comments_field_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields') ),
    '#states' => array(
      'visible' => array(
        ':input[name="comments_txt_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

  $form['tb']['appearance']['color_enhancements']['comments_region']['comments_colors']['comments_field_container']['comments_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Text color'),
    '#default_value' => (theme_get_setting('comments_text_color')) ? theme_get_setting('comments_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['comments_region']['comments_colors']['comments_field_container']['comments_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link color'),
    '#default_value' => (theme_get_setting('comments_link_color')) ? theme_get_setting('comments_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['comments_region']['comments_colors']['comments_field_container']['comments_link_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link hover color'),
    '#default_value' => (theme_get_setting('comments_link_hover_color')) ? theme_get_setting('comments_link_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );


$form['tb']['appearance']['color_enhancements']['comments_region']['comments_bg_status_region'] = array(
  '#type' => 'radios',
  '#title' => t('Background'),
  '#default_value' => (theme_get_setting('comments_bg_status_region')) ? theme_get_setting('comments_bg_status_region') : "0",
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#options' => array(
    '0'     => t('Default'),
    'color' => t('Solid color'),
    'gradient' => t('Gradient'),
    'pattern' => t('Pattern'),
    'custom'  => t('Custom')
  )
);

$form['tb']['appearance']['color_enhancements']['comments_region']['comments_solid_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Comments color'),
  '#default_value' => (theme_get_setting('comments_solid_color')) ? theme_get_setting('comments_solid_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
     ':input[name="comments_bg_status_region"]' => array('value' => 'color'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['comments_region']['comments_gradient_top'] = array(
  '#type' => 'textfield',
  '#title' => t('Top color'),
  '#default_value' => (theme_get_setting('comments_gradient_top')) ? theme_get_setting('comments_gradient_top') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="comments_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);
$form['tb']['appearance']['color_enhancements']['comments_region']['comments_gradient_bottom'] = array(
  '#type' => 'textfield',
  '#title' => t('Bottom color'),
  '#default_value' => (theme_get_setting('comments_gradient_bottom')) ? theme_get_setting('comments_gradient_bottom') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="comments_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['comments_region']['comments_pattern'] = array(
  '#type'          => 'radios',
  '#title'         => t('Patterns'),
  '#default_value' => theme_get_setting('comments_pattern'),
  '#options'       => $patterns,
  '#description'   => t('All Patterns is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/deed.en_US">Creative Commons Attribution-ShareAlike 3.0 Unported License</a> Please visit <a href="http://subtlepatterns.com">Subtle Patterns</a> For more resources and information'),
  '#attributes'    => array( 'class' => array('tb-pattern') ),
  '#states' => array(
    'visible' => array(
      ':input[name="comments_bg_status_region"]' => array('value' => 'pattern'),
    ),
  ),

);


$form['tb']['appearance']['color_enhancements']['comments_region']['comments_custom_behave'] = array(
  '#type'          => 'radios',
  '#title'         => t('Background image behavior'),
  '#default_value' => theme_get_setting('comments_custom_behave'),
  '#options'       => array(
    'repeat' => t('Repeating'),
    'cover' => t('Cover')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#states' => array(
    'visible' => array(
      ':input[name="comments_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
);


$comments_custom_path = theme_get_setting('comments_custom_path');
if (file_uri_scheme($comments_custom_path) == 'public') {
  $comments_custom_path = file_uri_target($comments_custom_path);
}
$form['tb']['appearance']['color_enhancements']['comments_region']['comments_custom_path'] = array(
  '#type' => 'textfield',
  '#title' => t('Path to custom Comments'),
  '#default_value' => $comments_custom_path,
  '#states' => array(
    'visible' => array(
      ':input[name="comments_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
  '#description' => t('The path to the file you would like to use as your Comments Background.'),
);



// If there is already an uploaded image display the image here.
if ( $comments_custom_upload_fid = theme_get_setting('comments_custom_upload') ) {

  $image = file_load($comments_custom_upload_fid);
  if (!empty($image)) {
    $options = array(
      'style_name' => 'thumbnail',
      'path' => $image->uri,
    );

    $form['tb']['appearance']['color_enhancements']['comments_region']['comments_custom_upload_image'] = array(
      '#type' => 'container',
      '#children' => theme('image_style', $options),
      '#states' => array(
        'visible' => array(
          ':input[name="comments_bg_status_region"]' => array('value' => 'custom'),
        ),
      ),
    );
  }
}

// Use the #managed_file FAPI element to upload an image file.
$form['tb']['appearance']['color_enhancements']['comments_region']['comments_custom_upload'] = array(
  '#title' => t('Custom image'),
  '#type' => 'managed_file',
  '#description' => t('The path to the file you would like to use as your Comments Background.'),
  '#default_value' => theme_get_setting('comments_custom_upload'),
  '#upload_location' => 'public://',
    '#states' => array(
      'visible' => array(
        ':input[name="comments_bg_status_region"]' => array('value' => 'custom'),
      ),
  ),
);


/* Custom Htags for Comments (H1,H2,H3,H4,H5,H6)
------------------------------------------------------------------------------*/

$form['tb']['appearance']['color_enhancements']['comments_region']['comments_htag_status_region'] = array(
  '#type'          => 'radios',
  '#title'         => t('Heading Colors'),
  '#default_value' => (theme_get_setting('comments_htag_status_region')) ? theme_get_setting('comments_htag_status_region') : "0",
  '#options'       => array(
    '0' => t('Default'),
    'custom' => t('Customize')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
);

  $form['tb']['appearance']['color_enhancements']['comments_region']['comments_htag_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields','six-col') ),
    '#states' => array(
      'visible' => array(
        ':input[name="comments_htag_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

$htxt = 1;
do {
  $form['tb']['appearance']['color_enhancements']['comments_region']['comments_htag_container']['comments_h'.$htxt.'_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$htxt.' text'),
    '#default_value' => (theme_get_setting('comments_h'.$htxt.'_text_color')) ? theme_get_setting('comments_h'.$htxt.'_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $htxt++;
} while ( $htxt <= 6);
unset($htxt);

$hlnk = 1;
do {
  $form['tb']['appearance']['color_enhancements']['comments_region']['comments_htag_container']['comments_h'.$hlnk.'_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hlnk.' link'),
    '#default_value' => (theme_get_setting('comments_h'.$hlnk.'_link_color')) ? theme_get_setting('comments_h'.$hlnk.'_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hlnk++;
} while ( $hlnk <= 6);
unset($hlnk);

$hhvr = 1;
do {
  $form['tb']['appearance']['color_enhancements']['comments_region']['comments_htag_container']['comments_h'.$hhvr.'_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hhvr.' hover'),
    '#default_value' => (theme_get_setting('comments_h'.$hhvr.'_hover_color')) ? theme_get_setting('comments_h'.$hhvr.'_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hhvr++;
} while ( $hhvr <= 6);
unset($hhvr);


  $form['tb']['appearance']['color_enhancements']['comments_region']['comments_htag_container']['comments_bt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#default_value' => (theme_get_setting('comments_bt_color')) ? theme_get_setting('comments_bt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['comments_region']['comments_htag_container']['comments_pt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Page title'),
    '#default_value' => (theme_get_setting('comments_pt_color')) ? theme_get_setting('comments_pt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['comments_region']['comments_htag_container']['comments_border_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Border'),
    '#default_value' => (theme_get_setting('comments_border_color')) ? theme_get_setting('comments_border_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );



/**
 * Footertop Appearance parameters are configured here.
 * -----------------------------------------------------------------------------
 */

$form['tb']['appearance']['color_enhancements']['footertop_region'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Footer Top Region'),
  '#weight'        => 0,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_selector'] = array(
  '#type' => 'hidden',
  '#value' => '#tbFooterTop',
);



$form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_colors'] = array(
  '#type'          => 'container'
);

  $form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_colors']['footertop_txt_status_region'] = array(
    '#type' => 'radios',
    '#title' => t('Content'),
    '#default_value' => (theme_get_setting('footertop_txt_status_region')) ? theme_get_setting('footertop_txt_status_region') : "0",
    '#attributes'    => array( 'class' => array('tb-inline-radios') ),
    '#options' => array(
      '0'     => t('Default'),
      'custom' => t('Customize'),
    )
  );

  $form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_colors']['footertop_field_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields') ),
    '#states' => array(
      'visible' => array(
        ':input[name="footertop_txt_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

  $form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_colors']['footertop_field_container']['footertop_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Text color'),
    '#default_value' => (theme_get_setting('footertop_text_color')) ? theme_get_setting('footertop_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_colors']['footertop_field_container']['footertop_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link color'),
    '#default_value' => (theme_get_setting('footertop_link_color')) ? theme_get_setting('footertop_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_colors']['footertop_field_container']['footertop_link_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link hover color'),
    '#default_value' => (theme_get_setting('footertop_link_hover_color')) ? theme_get_setting('footertop_link_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );


$form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_bg_status_region'] = array(
  '#type' => 'radios',
  '#title' => t('Background'),
  '#default_value' => (theme_get_setting('footertop_bg_status_region')) ? theme_get_setting('footertop_bg_status_region') : "0",
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#options' => array(
    '0'     => t('Default'),
    'color' => t('Solid color'),
    'gradient' => t('Gradient'),
    'pattern' => t('Pattern'),
    'custom'  => t('Custom')
  )
);

$form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_solid_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Footertop color'),
  '#default_value' => (theme_get_setting('footertop_solid_color')) ? theme_get_setting('footertop_solid_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
     ':input[name="footertop_bg_status_region"]' => array('value' => 'color'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_gradient_top'] = array(
  '#type' => 'textfield',
  '#title' => t('Top color'),
  '#default_value' => (theme_get_setting('footertop_gradient_top')) ? theme_get_setting('footertop_gradient_top') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="footertop_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);
$form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_gradient_bottom'] = array(
  '#type' => 'textfield',
  '#title' => t('Bottom color'),
  '#default_value' => (theme_get_setting('footertop_gradient_bottom')) ? theme_get_setting('footertop_gradient_bottom') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="footertop_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_pattern'] = array(
  '#type'          => 'radios',
  '#title'         => t('Patterns'),
  '#default_value' => theme_get_setting('footertop_pattern'),
  '#options'       => $patterns,
  '#description'   => t('All Patterns is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/deed.en_US">Creative Commons Attribution-ShareAlike 3.0 Unported License</a> Please visit <a href="http://subtlepatterns.com">Subtle Patterns</a> For more resources and information'),
  '#attributes'    => array( 'class' => array('tb-pattern') ),
  '#states' => array(
    'visible' => array(
      ':input[name="footertop_bg_status_region"]' => array('value' => 'pattern'),
    ),
  ),

);


$form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_custom_behave'] = array(
  '#type'          => 'radios',
  '#title'         => t('Background image behavior'),
  '#default_value' => theme_get_setting('footertop_custom_behave'),
  '#options'       => array(
    'repeat' => t('Repeating'),
    'cover' => t('Cover')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#states' => array(
    'visible' => array(
      ':input[name="footertop_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
);


$footertop_custom_path = theme_get_setting('footertop_custom_path');
if (file_uri_scheme($footertop_custom_path) == 'public') {
  $footertop_custom_path = file_uri_target($footertop_custom_path);
}
$form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_custom_path'] = array(
  '#type' => 'textfield',
  '#title' => t('Path to custom Footertop'),
  '#default_value' => $footertop_custom_path,
  '#states' => array(
    'visible' => array(
      ':input[name="footertop_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
  '#description' => t('The path to the file you would like to use as your Footertop Background.'),
);



// If there is already an uploaded image display the image here.
if ( $footertop_custom_upload_fid = theme_get_setting('footertop_custom_upload') ) {

  $image = file_load($footertop_custom_upload_fid);
  if (!empty($image)) {
    $options = array(
      'style_name' => 'thumbnail',
      'path' => $image->uri,
    );

    $form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_custom_upload_image'] = array(
      '#type' => 'container',
      '#children' => theme('image_style', $options),
      '#states' => array(
        'visible' => array(
          ':input[name="footertop_bg_status_region"]' => array('value' => 'custom'),
        ),
      ),
    );
  }
}

// Use the #managed_file FAPI element to upload an image file.
$form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_custom_upload'] = array(
  '#title' => t('Custom image'),
  '#type' => 'managed_file',
  '#description' => t('The path to the file you would like to use as your Footertop Background.'),
  '#default_value' => theme_get_setting('footertop_custom_upload'),
  '#upload_location' => 'public://',
    '#states' => array(
      'visible' => array(
        ':input[name="footertop_bg_status_region"]' => array('value' => 'custom'),
      ),
  ),
);


/* Custom Htags for Footertop (H1,H2,H3,H4,H5,H6)
------------------------------------------------------------------------------*/

$form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_htag_status_region'] = array(
  '#type'          => 'radios',
  '#title'         => t('Heading Colors'),
  '#default_value' => (theme_get_setting('footertop_htag_status_region')) ? theme_get_setting('footertop_htag_status_region') : "0",
  '#options'       => array(
    '0' => t('Default'),
    'custom' => t('Customize')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
);

  $form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_htag_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields','six-col') ),
    '#states' => array(
      'visible' => array(
        ':input[name="footertop_htag_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

$htxt = 1;
do {
  $form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_htag_container']['footertop_h'.$htxt.'_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$htxt.' text'),
    '#default_value' => (theme_get_setting('footertop_h'.$htxt.'_text_color')) ? theme_get_setting('footertop_h'.$htxt.'_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $htxt++;
} while ( $htxt <= 6);
unset($htxt);

$hlnk = 1;
do {
  $form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_htag_container']['footertop_h'.$hlnk.'_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hlnk.' link'),
    '#default_value' => (theme_get_setting('footertop_h'.$hlnk.'_link_color')) ? theme_get_setting('footertop_h'.$hlnk.'_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hlnk++;
} while ( $hlnk <= 6);
unset($hlnk);

$hhvr = 1;
do {
  $form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_htag_container']['footertop_h'.$hhvr.'_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hhvr.' hover'),
    '#default_value' => (theme_get_setting('footertop_h'.$hhvr.'_hover_color')) ? theme_get_setting('footertop_h'.$hhvr.'_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hhvr++;
} while ( $hhvr <= 6);
unset($hhvr);


  $form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_htag_container']['footertop_bt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#default_value' => (theme_get_setting('footertop_bt_color')) ? theme_get_setting('footertop_bt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_htag_container']['footertop_pt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Page title'),
    '#default_value' => (theme_get_setting('footertop_pt_color')) ? theme_get_setting('footertop_pt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['footertop_region']['footertop_htag_container']['footertop_border_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Border'),
    '#default_value' => (theme_get_setting('footertop_border_color')) ? theme_get_setting('footertop_border_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );



/**
 * Highlighted Appearance parameters are configured here.
 * -----------------------------------------------------------------------------
 */

$form['tb']['appearance']['color_enhancements']['highlighted_region'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Highlighted Region'),
  '#weight'        => 0,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_selector'] = array(
  '#type' => 'hidden',
  '#value' => '.highlighted',
);



$form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_colors'] = array(
  '#type'          => 'container'
);

  $form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_colors']['highlighted_txt_status_region'] = array(
    '#type' => 'radios',
    '#title' => t('Content'),
    '#default_value' => (theme_get_setting('highlighted_txt_status_region')) ? theme_get_setting('highlighted_txt_status_region') : "0",
    '#attributes'    => array( 'class' => array('tb-inline-radios') ),
    '#options' => array(
      '0'     => t('Default'),
      'custom' => t('Customize'),
    )
  );

  $form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_colors']['highlighted_field_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields') ),
    '#states' => array(
      'visible' => array(
        ':input[name="highlighted_txt_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

  $form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_colors']['highlighted_field_container']['highlighted_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Text color'),
    '#default_value' => (theme_get_setting('highlighted_text_color')) ? theme_get_setting('highlighted_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_colors']['highlighted_field_container']['highlighted_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link color'),
    '#default_value' => (theme_get_setting('highlighted_link_color')) ? theme_get_setting('highlighted_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_colors']['highlighted_field_container']['highlighted_link_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link hover color'),
    '#default_value' => (theme_get_setting('highlighted_link_hover_color')) ? theme_get_setting('highlighted_link_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );


$form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_bg_status_region'] = array(
  '#type' => 'radios',
  '#title' => t('Background'),
  '#default_value' => (theme_get_setting('highlighted_bg_status_region')) ? theme_get_setting('highlighted_bg_status_region') : "0",
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#options' => array(
    '0'     => t('Default'),
    'color' => t('Solid color'),
    'gradient' => t('Gradient'),
    'pattern' => t('Pattern'),
    'custom'  => t('Custom')
  )
);

$form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_solid_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Highlighted color'),
  '#default_value' => (theme_get_setting('highlighted_solid_color')) ? theme_get_setting('highlighted_solid_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
     ':input[name="highlighted_bg_status_region"]' => array('value' => 'color'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_gradient_top'] = array(
  '#type' => 'textfield',
  '#title' => t('Top color'),
  '#default_value' => (theme_get_setting('highlighted_gradient_top')) ? theme_get_setting('highlighted_gradient_top') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="highlighted_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);
$form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_gradient_bottom'] = array(
  '#type' => 'textfield',
  '#title' => t('Bottom color'),
  '#default_value' => (theme_get_setting('highlighted_gradient_bottom')) ? theme_get_setting('highlighted_gradient_bottom') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="highlighted_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_pattern'] = array(
  '#type'          => 'radios',
  '#title'         => t('Patterns'),
  '#default_value' => theme_get_setting('highlighted_pattern'),
  '#options'       => $patterns,
  '#description'   => t('All Patterns is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/deed.en_US">Creative Commons Attribution-ShareAlike 3.0 Unported License</a> Please visit <a href="http://subtlepatterns.com">Subtle Patterns</a> For more resources and information'),
  '#attributes'    => array( 'class' => array('tb-pattern') ),
  '#states' => array(
    'visible' => array(
      ':input[name="highlighted_bg_status_region"]' => array('value' => 'pattern'),
    ),
  ),

);


$form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_custom_behave'] = array(
  '#type'          => 'radios',
  '#title'         => t('Background image behavior'),
  '#default_value' => theme_get_setting('highlighted_custom_behave'),
  '#options'       => array(
    'repeat' => t('Repeating'),
    'cover' => t('Cover')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#states' => array(
    'visible' => array(
      ':input[name="highlighted_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
);


$highlighted_custom_path = theme_get_setting('highlighted_custom_path');
if (file_uri_scheme($highlighted_custom_path) == 'public') {
  $highlighted_custom_path = file_uri_target($highlighted_custom_path);
}
$form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_custom_path'] = array(
  '#type' => 'textfield',
  '#title' => t('Path to custom Highlighted'),
  '#default_value' => $highlighted_custom_path,
  '#states' => array(
    'visible' => array(
      ':input[name="highlighted_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
  '#description' => t('The path to the file you would like to use as your Highlighted Background.'),
);



// If there is already an uploaded image display the image here.
if ( $highlighted_custom_upload_fid = theme_get_setting('highlighted_custom_upload') ) {

  $image = file_load($highlighted_custom_upload_fid);
  if (!empty($image)) {
    $options = array(
      'style_name' => 'thumbnail',
      'path' => $image->uri,
    );

    $form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_custom_upload_image'] = array(
      '#type' => 'container',
      '#children' => theme('image_style', $options),
      '#states' => array(
        'visible' => array(
          ':input[name="highlighted_bg_status_region"]' => array('value' => 'custom'),
        ),
      ),
    );
  }
}

// Use the #managed_file FAPI element to upload an image file.
$form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_custom_upload'] = array(
  '#title' => t('Custom image'),
  '#type' => 'managed_file',
  '#description' => t('The path to the file you would like to use as your Highlighted Background.'),
  '#default_value' => theme_get_setting('highlighted_custom_upload'),
  '#upload_location' => 'public://',
    '#states' => array(
      'visible' => array(
        ':input[name="highlighted_bg_status_region"]' => array('value' => 'custom'),
      ),
  ),
);


/* Custom Htags for Highlighted (H1,H2,H3,H4,H5,H6)
------------------------------------------------------------------------------*/

$form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_htag_status_region'] = array(
  '#type'          => 'radios',
  '#title'         => t('Heading Colors'),
  '#default_value' => (theme_get_setting('highlighted_htag_status_region')) ? theme_get_setting('highlighted_htag_status_region') : "0",
  '#options'       => array(
    '0' => t('Default'),
    'custom' => t('Customize')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
);

  $form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_htag_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields','six-col') ),
    '#states' => array(
      'visible' => array(
        ':input[name="highlighted_htag_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

$htxt = 1;
do {
  $form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_htag_container']['highlighted_h'.$htxt.'_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$htxt.' text'),
    '#default_value' => (theme_get_setting('highlighted_h'.$htxt.'_text_color')) ? theme_get_setting('highlighted_h'.$htxt.'_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $htxt++;
} while ( $htxt <= 6);
unset($htxt);

$hlnk = 1;
do {
  $form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_htag_container']['highlighted_h'.$hlnk.'_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hlnk.' link'),
    '#default_value' => (theme_get_setting('highlighted_h'.$hlnk.'_link_color')) ? theme_get_setting('highlighted_h'.$hlnk.'_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hlnk++;
} while ( $hlnk <= 6);
unset($hlnk);

$hhvr = 1;
do {
  $form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_htag_container']['highlighted_h'.$hhvr.'_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hhvr.' hover'),
    '#default_value' => (theme_get_setting('highlighted_h'.$hhvr.'_hover_color')) ? theme_get_setting('highlighted_h'.$hhvr.'_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hhvr++;
} while ( $hhvr <= 6);
unset($hhvr);


  $form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_htag_container']['highlighted_bt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#default_value' => (theme_get_setting('highlighted_bt_color')) ? theme_get_setting('highlighted_bt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_htag_container']['highlighted_pt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Page title'),
    '#default_value' => (theme_get_setting('highlighted_pt_color')) ? theme_get_setting('highlighted_pt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['highlighted_region']['highlighted_htag_container']['highlighted_border_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Border'),
    '#default_value' => (theme_get_setting('highlighted_border_color')) ? theme_get_setting('highlighted_border_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );



/**
 * Header Appearance parameters are configured here.
 * -----------------------------------------------------------------------------
 */

$form['tb']['appearance']['color_enhancements']['header_region'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Header Region'),
  '#weight'        => 0,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form['tb']['appearance']['color_enhancements']['header_region']['header_selector'] = array(
  '#type' => 'hidden',
  '#value' => '#tbHeaderBox',
);



$form['tb']['appearance']['color_enhancements']['header_region']['header_colors'] = array(
  '#type'          => 'container'
);

  $form['tb']['appearance']['color_enhancements']['header_region']['header_colors']['header_txt_status_region'] = array(
    '#type' => 'radios',
    '#title' => t('Content'),
    '#default_value' => (theme_get_setting('header_txt_status_region')) ? theme_get_setting('header_txt_status_region') : "0",
    '#attributes'    => array( 'class' => array('tb-inline-radios') ),
    '#options' => array(
      '0'     => t('Default'),
      'custom' => t('Customize'),
    )
  );

  $form['tb']['appearance']['color_enhancements']['header_region']['header_colors']['header_field_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields') ),
    '#states' => array(
      'visible' => array(
        ':input[name="header_txt_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

  $form['tb']['appearance']['color_enhancements']['header_region']['header_colors']['header_field_container']['header_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Text color'),
    '#default_value' => (theme_get_setting('header_text_color')) ? theme_get_setting('header_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['header_region']['header_colors']['header_field_container']['header_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link color'),
    '#default_value' => (theme_get_setting('header_link_color')) ? theme_get_setting('header_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['header_region']['header_colors']['header_field_container']['header_link_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link hover color'),
    '#default_value' => (theme_get_setting('header_link_hover_color')) ? theme_get_setting('header_link_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );


$form['tb']['appearance']['color_enhancements']['header_region']['header_bg_status_region'] = array(
  '#type' => 'radios',
  '#title' => t('Background'),
  '#default_value' => (theme_get_setting('header_bg_status_region')) ? theme_get_setting('header_bg_status_region') : "0",
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#options' => array(
    '0'     => t('Default'),
    'color' => t('Solid color'),
    'gradient' => t('Gradient'),
    'pattern' => t('Pattern'),
    'custom'  => t('Custom')
  )
);

$form['tb']['appearance']['color_enhancements']['header_region']['header_solid_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Header color'),
  '#default_value' => (theme_get_setting('header_solid_color')) ? theme_get_setting('header_solid_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
     ':input[name="header_bg_status_region"]' => array('value' => 'color'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['header_region']['header_gradient_top'] = array(
  '#type' => 'textfield',
  '#title' => t('Top color'),
  '#default_value' => (theme_get_setting('header_gradient_top')) ? theme_get_setting('header_gradient_top') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="header_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);
$form['tb']['appearance']['color_enhancements']['header_region']['header_gradient_bottom'] = array(
  '#type' => 'textfield',
  '#title' => t('Bottom color'),
  '#default_value' => (theme_get_setting('header_gradient_bottom')) ? theme_get_setting('header_gradient_bottom') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="header_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['header_region']['header_pattern'] = array(
  '#type'          => 'radios',
  '#title'         => t('Patterns'),
  '#default_value' => theme_get_setting('header_pattern'),
  '#options'       => $patterns,
  '#description'   => t('All Patterns is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/deed.en_US">Creative Commons Attribution-ShareAlike 3.0 Unported License</a> Please visit <a href="http://subtlepatterns.com">Subtle Patterns</a> For more resources and information'),
  '#attributes'    => array( 'class' => array('tb-pattern') ),
  '#states' => array(
    'visible' => array(
      ':input[name="header_bg_status_region"]' => array('value' => 'pattern'),
    ),
  ),

);


$form['tb']['appearance']['color_enhancements']['header_region']['header_custom_behave'] = array(
  '#type'          => 'radios',
  '#title'         => t('Background image behavior'),
  '#default_value' => theme_get_setting('header_custom_behave'),
  '#options'       => array(
    'repeat' => t('Repeating'),
    'cover' => t('Cover')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#states' => array(
    'visible' => array(
      ':input[name="header_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
);


$header_custom_path = theme_get_setting('header_custom_path');
if (file_uri_scheme($header_custom_path) == 'public') {
  $header_custom_path = file_uri_target($header_custom_path);
}
$form['tb']['appearance']['color_enhancements']['header_region']['header_custom_path'] = array(
  '#type' => 'textfield',
  '#title' => t('Path to custom Header'),
  '#default_value' => $header_custom_path,
  '#states' => array(
    'visible' => array(
      ':input[name="header_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
  '#description' => t('The path to the file you would like to use as your Header Background.'),
);



// If there is already an uploaded image display the image here.
if ( $header_custom_upload_fid = theme_get_setting('header_custom_upload') ) {

  $image = file_load($header_custom_upload_fid);
  if (!empty($image)) {
    $options = array(
      'style_name' => 'thumbnail',
      'path' => $image->uri,
    );

    $form['tb']['appearance']['color_enhancements']['header_region']['header_custom_upload_image'] = array(
      '#type' => 'container',
      '#children' => theme('image_style', $options),
      '#states' => array(
        'visible' => array(
          ':input[name="header_bg_status_region"]' => array('value' => 'custom'),
        ),
      ),
    );
  }
}

// Use the #managed_file FAPI element to upload an image file.
$form['tb']['appearance']['color_enhancements']['header_region']['header_custom_upload'] = array(
  '#title' => t('Custom image'),
  '#type' => 'managed_file',
  '#description' => t('The path to the file you would like to use as your Header Background.'),
  '#default_value' => theme_get_setting('header_custom_upload'),
  '#upload_location' => 'public://',
    '#states' => array(
      'visible' => array(
        ':input[name="header_bg_status_region"]' => array('value' => 'custom'),
      ),
  ),
);


/* Custom Htags for Header (H1,H2,H3,H4,H5,H6)
------------------------------------------------------------------------------*/

$form['tb']['appearance']['color_enhancements']['header_region']['header_htag_status_region'] = array(
  '#type'          => 'radios',
  '#title'         => t('Heading Colors'),
  '#default_value' => (theme_get_setting('header_htag_status_region')) ? theme_get_setting('header_htag_status_region') : "0",
  '#options'       => array(
    '0' => t('Default'),
    'custom' => t('Customize')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
);

  $form['tb']['appearance']['color_enhancements']['header_region']['header_htag_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields','six-col') ),
    '#states' => array(
      'visible' => array(
        ':input[name="header_htag_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

$htxt = 1;
do {
  $form['tb']['appearance']['color_enhancements']['header_region']['header_htag_container']['header_h'.$htxt.'_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$htxt.' text'),
    '#default_value' => (theme_get_setting('header_h'.$htxt.'_text_color')) ? theme_get_setting('header_h'.$htxt.'_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $htxt++;
} while ( $htxt <= 6);
unset($htxt);

$hlnk = 1;
do {
  $form['tb']['appearance']['color_enhancements']['header_region']['header_htag_container']['header_h'.$hlnk.'_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hlnk.' link'),
    '#default_value' => (theme_get_setting('header_h'.$hlnk.'_link_color')) ? theme_get_setting('header_h'.$hlnk.'_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hlnk++;
} while ( $hlnk <= 6);
unset($hlnk);

$hhvr = 1;
do {
  $form['tb']['appearance']['color_enhancements']['header_region']['header_htag_container']['header_h'.$hhvr.'_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hhvr.' hover'),
    '#default_value' => (theme_get_setting('header_h'.$hhvr.'_hover_color')) ? theme_get_setting('header_h'.$hhvr.'_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hhvr++;
} while ( $hhvr <= 6);
unset($hhvr);


  $form['tb']['appearance']['color_enhancements']['header_region']['header_htag_container']['header_bt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#default_value' => (theme_get_setting('header_bt_color')) ? theme_get_setting('header_bt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['header_region']['header_htag_container']['header_pt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Page title'),
    '#default_value' => (theme_get_setting('header_pt_color')) ? theme_get_setting('header_pt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['header_region']['header_htag_container']['header_border_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Border'),
    '#default_value' => (theme_get_setting('header_border_color')) ? theme_get_setting('header_border_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['header_region']['headerwrapper_region'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Header Wrapper'),
    '#weight'        => 0,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['tb']['appearance']['color_enhancements']['header_region']['headerwrapper_region']['headerwrapper_selector'] = array(
    '#type' => 'hidden',
    '#value' => '#tbHeadWrapper',
  );

  $form['tb']['appearance']['color_enhancements']['header_region']['headerwrapper_region'] ['headerwrapper_colors'] = array(
    '#type'          => 'container'
  );

  $form['tb']['appearance']['color_enhancements']['header_region']['headerwrapper_region'] ['headerwrapper_colors']['headerwrapper_bg_status_region'] = array(
    '#type' => 'radios',
    '#title' => t('Background'),
    '#default_value' => (theme_get_setting('headerwrapper_bg_status_region')) ? theme_get_setting('headerwrapper_bg_status_region') : "0",
    '#attributes'    => array( 'class' => array('tb-inline-radios') ),
    '#options' => array(
      '0'     => t('Default'),
      'color' => t('Solid color'),
      // 'gradient' => t('Gradient'),
      // 'pattern' => t('Pattern'),
      // 'custom'  => t('Custom')
    )
  );

  // status_region

  $form['tb']['appearance']['color_enhancements']['header_region']['headerwrapper_region'] ['headerwrapper_colors']['headerwrapper_solid_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Background color'),
  '#default_value' => (theme_get_setting('headerwrapper_solid_color')) ? theme_get_setting('headerwrapper_solid_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="headerwrapper_bg_status_region"]' => array('value' =>  'color'),
    ),
  ),
);

  $form['tb']['appearance']['color_enhancements']['header_region']['headerwrapper_region'] ['headerwrapper_colors']['headerwrapper_solid_opacity'] = array(
    '#type' => 'textfield',
    '#title' => t('Opacity'),
    // '#default_value' => theme_get_setting('carma_viit') ,
    '#default_value' => (theme_get_setting('headerwrapper_solid_opacity')) ? theme_get_setting('headerwrapper_solid_opacity') : 0,
    '#size' => 3,
    '#maxlength' => 4,
    '#attached' => array(
      'js' => array(
        array(
        'data' => array('headerwrapper_solid_opacity' => array(
          'max'  => 1,
          'min'  => 0,
          'step' => 0.01
          )
        ),
        'type' => 'setting',
        ),
      ),
    ),
    // '#disabled' => TRUE,
    '#attributes'    => array( 'class' => array('tb-slider-field') ),
    '#states' => array(
      'visible' => array(
        ':input[name="headerwrapper_bg_status_region"]' => array('value' =>  'color'),
      ),
    ),
  );



/**
 * Info Appearance parameters are configured here.
 * -----------------------------------------------------------------------------
 */

$form['tb']['appearance']['color_enhancements']['info_region'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Info Region'),
  '#weight'        => 0,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

$form['tb']['appearance']['color_enhancements']['info_region']['info_selector'] = array(
  '#type' => 'hidden',
  '#value' => '#tbInfo',
);



$form['tb']['appearance']['color_enhancements']['info_region']['info_colors'] = array(
  '#type'          => 'container'
);

  $form['tb']['appearance']['color_enhancements']['info_region']['info_colors']['info_txt_status_region'] = array(
    '#type' => 'radios',
    '#title' => t('Content'),
    '#default_value' => (theme_get_setting('info_txt_status_region')) ? theme_get_setting('info_txt_status_region') : "0",
    '#attributes'    => array( 'class' => array('tb-inline-radios') ),
    '#options' => array(
      '0'     => t('Default'),
      'custom' => t('Customize'),
    )
  );

  $form['tb']['appearance']['color_enhancements']['info_region']['info_colors']['info_field_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields') ),
    '#states' => array(
      'visible' => array(
        ':input[name="info_txt_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

  $form['tb']['appearance']['color_enhancements']['info_region']['info_colors']['info_field_container']['info_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Text color'),
    '#default_value' => (theme_get_setting('info_text_color')) ? theme_get_setting('info_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['info_region']['info_colors']['info_field_container']['info_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link color'),
    '#default_value' => (theme_get_setting('info_link_color')) ? theme_get_setting('info_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['info_region']['info_colors']['info_field_container']['info_link_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Link hover color'),
    '#default_value' => (theme_get_setting('info_link_hover_color')) ? theme_get_setting('info_link_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );


$form['tb']['appearance']['color_enhancements']['info_region']['info_bg_status_region'] = array(
  '#type' => 'radios',
  '#title' => t('Background'),
  '#default_value' => (theme_get_setting('info_bg_status_region')) ? theme_get_setting('info_bg_status_region') : "0",
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#options' => array(
    '0'     => t('Default'),
    'color' => t('Solid color'),
    'gradient' => t('Gradient'),
    'pattern' => t('Pattern'),
    'custom'  => t('Custom')
  )
);

$form['tb']['appearance']['color_enhancements']['info_region']['info_solid_color'] = array(
  '#type' => 'textfield',
  '#title' => t('Info color'),
  '#default_value' => (theme_get_setting('info_solid_color')) ? theme_get_setting('info_solid_color') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
     ':input[name="info_bg_status_region"]' => array('value' => 'color'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['info_region']['info_gradient_top'] = array(
  '#type' => 'textfield',
  '#title' => t('Top color'),
  '#default_value' => (theme_get_setting('info_gradient_top')) ? theme_get_setting('info_gradient_top') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="info_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);
$form['tb']['appearance']['color_enhancements']['info_region']['info_gradient_bottom'] = array(
  '#type' => 'textfield',
  '#title' => t('Bottom color'),
  '#default_value' => (theme_get_setting('info_gradient_bottom')) ? theme_get_setting('info_gradient_bottom') : "#ffffff",
  '#size' => 8,
  '#maxlength' => 8,
  '#attributes'    => array( 'class' => array('tb-color-field') ),
  '#states' => array(
    'visible' => array(
      ':input[name="info_bg_status_region"]' => array('value' => 'gradient'),
    ),
  ),
);

$form['tb']['appearance']['color_enhancements']['info_region']['info_pattern'] = array(
  '#type'          => 'radios',
  '#title'         => t('Patterns'),
  '#default_value' => theme_get_setting('info_pattern'),
  '#options'       => $patterns,
  '#description'   => t('All Patterns is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/3.0/deed.en_US">Creative Commons Attribution-ShareAlike 3.0 Unported License</a> Please visit <a href="http://subtlepatterns.com">Subtle Patterns</a> For more resources and information'),
  '#attributes'    => array( 'class' => array('tb-pattern') ),
  '#states' => array(
    'visible' => array(
      ':input[name="info_bg_status_region"]' => array('value' => 'pattern'),
    ),
  ),

);


$form['tb']['appearance']['color_enhancements']['info_region']['info_custom_behave'] = array(
  '#type'          => 'radios',
  '#title'         => t('Background image behavior'),
  '#default_value' => theme_get_setting('info_custom_behave'),
  '#options'       => array(
    'repeat' => t('Repeating'),
    'cover' => t('Cover')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#states' => array(
    'visible' => array(
      ':input[name="info_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
);


$info_custom_path = theme_get_setting('info_custom_path');
if (file_uri_scheme($info_custom_path) == 'public') {
  $info_custom_path = file_uri_target($info_custom_path);
}
$form['tb']['appearance']['color_enhancements']['info_region']['info_custom_path'] = array(
  '#type' => 'textfield',
  '#title' => t('Path to custom Info'),
  '#default_value' => $info_custom_path,
  '#states' => array(
    'visible' => array(
      ':input[name="info_bg_status_region"]' => array('value' => 'custom'),
    ),
  ),
  '#description' => t('The path to the file you would like to use as your Info Background.'),
);



// If there is already an uploaded image display the image here.
if ( $info_custom_upload_fid = theme_get_setting('info_custom_upload') ) {

  $image = file_load($info_custom_upload_fid);
  if (!empty($image)) {
    $options = array(
      'style_name' => 'thumbnail',
      'path' => $image->uri,
    );

    $form['tb']['appearance']['color_enhancements']['info_region']['info_custom_upload_image'] = array(
      '#type' => 'container',
      '#children' => theme('image_style', $options),
      '#states' => array(
        'visible' => array(
          ':input[name="info_bg_status_region"]' => array('value' => 'custom'),
        ),
      ),
    );
  }
}

// Use the #managed_file FAPI element to upload an image file.
$form['tb']['appearance']['color_enhancements']['info_region']['info_custom_upload'] = array(
  '#title' => t('Custom image'),
  '#type' => 'managed_file',
  '#description' => t('The path to the file you would like to use as your Info Background.'),
  '#default_value' => theme_get_setting('info_custom_upload'),
  '#upload_location' => 'public://',
    '#states' => array(
      'visible' => array(
        ':input[name="info_bg_status_region"]' => array('value' => 'custom'),
      ),
  ),
);


/* Custom Htags for Info (H1,H2,H3,H4,H5,H6)
------------------------------------------------------------------------------*/

$form['tb']['appearance']['color_enhancements']['info_region']['info_htag_status_region'] = array(
  '#type'          => 'radios',
  '#title'         => t('Heading Colors'),
  '#default_value' => (theme_get_setting('info_htag_status_region')) ? theme_get_setting('info_htag_status_region') : "0",
  '#options'       => array(
    '0' => t('Default'),
    'custom' => t('Customize')
    ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
);

  $form['tb']['appearance']['color_enhancements']['info_region']['info_htag_container'] = array(
    '#type'          => 'container',
    '#attributes'    => array( 'class' => array('tb-inline-fields','six-col') ),
    '#states' => array(
      'visible' => array(
        ':input[name="info_htag_status_region"]' => array('value' =>  'custom'),
      ),
    ),
  );

$htxt = 1;
do {
  $form['tb']['appearance']['color_enhancements']['info_region']['info_htag_container']['info_h'.$htxt.'_text_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$htxt.' text'),
    '#default_value' => (theme_get_setting('info_h'.$htxt.'_text_color')) ? theme_get_setting('info_h'.$htxt.'_text_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $htxt++;
} while ( $htxt <= 6);
unset($htxt);

$hlnk = 1;
do {
  $form['tb']['appearance']['color_enhancements']['info_region']['info_htag_container']['info_h'.$hlnk.'_link_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hlnk.' link'),
    '#default_value' => (theme_get_setting('info_h'.$hlnk.'_link_color')) ? theme_get_setting('info_h'.$hlnk.'_link_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hlnk++;
} while ( $hlnk <= 6);
unset($hlnk);

$hhvr = 1;
do {
  $form['tb']['appearance']['color_enhancements']['info_region']['info_htag_container']['info_h'.$hhvr.'_hover_color'] = array(
    '#type' => 'textfield',
    '#title' => t('H'.$hhvr.' hover'),
    '#default_value' => (theme_get_setting('info_h'.$hhvr.'_hover_color')) ? theme_get_setting('info_h'.$hhvr.'_hover_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );
  $hhvr++;
} while ( $hhvr <= 6);
unset($hhvr);


  $form['tb']['appearance']['color_enhancements']['info_region']['info_htag_container']['info_bt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#default_value' => (theme_get_setting('info_bt_color')) ? theme_get_setting('info_bt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['info_region']['info_htag_container']['info_pt_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Page title'),
    '#default_value' => (theme_get_setting('info_pt_color')) ? theme_get_setting('info_pt_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

  $form['tb']['appearance']['color_enhancements']['info_region']['info_htag_container']['info_border_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Border'),
    '#default_value' => (theme_get_setting('info_border_color')) ? theme_get_setting('info_border_color') : "#ffffff",
    '#size' => 8,
    '#maxlength' => 8,
    '#attributes'    => array( 'class' => array('tb-color-field') ),
  );

