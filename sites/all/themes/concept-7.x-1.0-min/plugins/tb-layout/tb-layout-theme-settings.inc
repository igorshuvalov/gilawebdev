<?php
include_once(dirname(__FILE__) . '/tb-layout-helper.inc');


$form['tb']['tb_layout'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Layout'),
  // '#description'   => t("Layout parameters are configured here."),
  '#weight'        => 2,
);

$form['tb']['tb_layout']['tb_scaffolding'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Scaffolding'),
  '#weight'        => 0,
);


$form['tb']['tb_layout']['tb_scaffolding']['layout_mode'] = array(
  '#type' => 'radios',
  '#title' => t('Layout mode'),
  '#options' => array(
    'static' => t('Static'),
    'responsive' => t('Responsive')
  ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#default_value' => theme_get_setting('layout_mode'),
);

// TODO:
// $form['tb']['tb_layout']['tb_scaffolding']['layout_style'] = array(
//   '#type' => 'radios',
//   '#title' => t('Layout style'),
//   '#options' => array(
//     'fixed' => t('Fixed'),
//     'fluid' => t('Fluid')
//   ),
//   '#attributes'    => array( 'class' => array('tb-inline-radios') ),
//   '#default_value' => theme_get_setting('layout_style'),
// );

$form['tb']['tb_layout']['tb_scaffolding']['layout_type'] = array(
  '#type' => 'radios',
  '#title' => t('Layout type'),
  '#options' => array(
    'wide' => t('Wide'),
    'boxed' => t('Boxed')
  ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#default_value' => theme_get_setting('layout_type'),
);

$form['tb']['tb_layout']['tb_scaffolding']['layout_top_margin'] = array(
  '#type' => 'textfield',
  '#title' => t('Top margin'),
  '#default_value' => (theme_get_setting('layout_top_margin')) ? theme_get_setting('layout_top_margin') : 0,
  '#field_suffix' => t('px'),
  '#size' => 3,
  '#maxlength' => 4,
  '#attached' => array(
    'js' => array(
      array(
      'data' => array('layout_top_margin' => array(
        'max'  => (theme_get_setting('layout_top_margin') > 100) ? theme_get_setting('layout_top_margin') : 100,
        'min'  => 0,
        'step' => 5
        )
      ),
      'type' => 'setting',
      ),
    ),
  ),
  // '#disabled' => TRUE,
  '#attributes'    => array( 'class' => array('tb-slider-field') ),
  '#description'   => t("Top margin must be a positive number greater than zero and valid CSS unit is <b>px</b>"),
  '#states' => array(
    'visible' => array(
      ':input[name="layout_type"]' => array('value' =>  'boxed'),
    ),
  ),
);

// ----------------------------------------------------------------------------
// Header Layout
// ----------------------------------------------------------------------------

$form['tb']['tb_layout']['tb_header_layout'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Header layout'),
  // '#description'   => t("Logo, Main menu grid parameters are configured here."),
  '#weight'        => 2,
);

/**
 * Brand Settings
 */
$form['tb']['tb_layout']['tb_header_layout']['tb_brand'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Brand'),
);

$form['tb']['tb_layout']['tb_header_layout']['tb_brand']['brand_span'] = array(
  '#type' => 'textfield',
  '#title' => t('Brand width'),
  '#default_value' => theme_get_setting('brand_span'),
  '#field_prefix' => t('span'),
  '#size' => 2,
  '#maxlength' => 2,
  '#attributes'    => array( 'class' => array('tb-slider-field') ),
  '#attached' => array(
    'js' => array(
      array(
      'data' => array('brand_span' => array(
        'max'  => 12,
        'min'  => 1,
        'step' => 1
        )
      ),
      'type' => 'setting',
      ),
    ),
  )
);


$form['tb']['tb_layout']['tb_header_layout']['tb_brand']['brand_classes'] = array(
  '#type' => 'select',
  '#multiple' => TRUE,
  '#title' => t('Custom Brand classes'),
  '#options' => custom_classes(),
  // '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#default_value' => theme_get_setting('brand_classes'),
);


/**
 * Main menu
 */
$form['tb']['tb_layout']['tb_header_layout']['tb_mainmenu'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Main menu'),
);

$form['tb']['tb_layout']['tb_header_layout']['tb_mainmenu']['mainmenu_span'] = array(
  '#type' => 'textfield',
  '#title' => t('Main menu width'),
  '#default_value' => theme_get_setting('mainmenu_span'),
  '#field_prefix' => t('span'),
  '#size' => 2,
  '#maxlength' => 2,
  '#attributes'    => array( 'class' => array('tb-slider-field') ),
  '#attached' => array(
    'js' => array(
      array(
      'data' => array('mainmenu_span' => array(
        'max'  => 12,
        'min'  => 1,
        'step' => 1
        )
      ),
      'type' => 'setting',
      ),
    ),
  )
);

$form['tb']['tb_layout']['tb_header_layout']['tb_mainmenu']['mainmenu_classes'] = array(
  '#type' => 'select',
  '#multiple' => TRUE,
  '#title' => t('Custom Main menu classes'),
  '#options' => custom_classes(),
  // '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#default_value' => theme_get_setting('mainmenu_classes'),
);


$form['tb']['tb_layout']['tb_header_layout']['tb_mainmenu']['mainmenu_tinynav'] = array(
  '#type' => 'radios',
  '#title' => t('Tinynav support'),
  '#options' => array(
    1 => t('On'),
    0 => t('Off')
  ),
  '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#default_value' => theme_get_setting('mainmenu_tinynav'),
  '#description' => t("TinyNav is a tiny jQuery plugin that converts main navigations to a select dropdowns for small screen.")
);

$form['tb']['tb_layout']['tb_header_layout']['tb_mainmenu']['tinynav_classes'] = array(
  '#type' => 'select',
  '#multiple' => TRUE,
  '#title' => t('TinyNav classes'),
  '#options' => custom_classes(),
  // '#attributes'    => array( 'class' => array('tb-inline-radios') ),
  '#default_value' => theme_get_setting('tinynav_classes'),
  '#states' => array(
    'visible' => array(
      ':input[name="mainmenu_tinynav"]' => array('value' =>  '1'),
    ),
  ),
);
