<?php

global $font_options, $font_variants, $font_subsets, $font_size;
include_once(dirname(__FILE__) . '/tb-typography-helper.inc');

$form['tb']['tb_typography'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Typography'),
  // '#description'   => t("Typography parameters are configured here."),
  '#weight'        => 3,
);


/**
 * Site name Typography parameters are configured here.
 * ========
 */

$form['tb']['tb_typography']['sitename_typo'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Site name Typography'),
  // '#description'   => t("Content Typography parameters are configured here."),
  '#weight'        => -2,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

  $form['tb']['tb_typography']['sitename_typo']['sitename_selector'] = array(
    '#type' => 'hidden',
    '#value' => '#site-name',
  );

  $form['tb']['tb_typography']['sitename_typo']['sitename_font_type'] = array(
    '#type' => 'radios',
    '#title' => t('Font type'),
    '#options' => array('Default','google' =>'Google'),
    '#default_value' => (theme_get_setting('sitename_font_type')) ? theme_get_setting('sitename_font_type') : "0",
    '#attributes' => array('class' =>array('tb-inline-radios'))
  );

  // $form['tb']['tb_typography']['sitename_typo']['sitename_font_websafe'] = array(
  //   '#type' => 'select',
  //   '#title' => t('Websafe Fonts'),
  //   '#default_value' => theme_get_setting('sitename_font_websafe') ,
  //   '#options' => _websafe_fonts_cache(),
  //   '#states' => array(
  //   'visible' => array(
  //     ':input[name="sitename_font_type"]' => array('value' =>'websafe')
  //   )
  //   )
  // );

  $form['tb']['tb_typography']['sitename_typo']['sitename_font_websafe_weight'] = array(
    '#type' => 'radios',
    '#title' => t('Font weight'),
    '#default_value' => theme_get_setting('sitename_font_websafe_weight') ,
    '#options' => _font_weight(),
    '#attributes' => array('class' =>array('tb-inline-radios')),
    '#states' => array(
    'visible' => array(
      ':input[name="sitename_font_type"]' => array('value' =>'websafe')
    )
    )
  );



  $selected = isset($form_state['values']['sitename_font_google']) ? $form_state['values']['sitename_font_google'] : theme_get_setting('sitename_font_google');

  $form['tb']['tb_typography']['sitename_typo']['sitename_font_google'] = array(
    '#type' => 'select',
    '#title' => t('Google WebFonts'),
    '#options' => $font_options,
    '#default_value' => $selected,
    '#ajax' => array(
    'callback' => 'font_variants_callback',
    'wrapper' => 'sitename-ajax-con',
    'method' => 'replace',
    'effect' => 'fade',
    // Don't show any throbber...
    // 'progress' => array('type' => 'none'),
    ),
    '#states' => array(
    'visible' => array(
      'input[name="sitename_font_type"]' => array('value' =>'google')
    )
    )
  );

  $form['tb']['tb_typography']['sitename_typo']['sitename_ajax_con'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => array('sitename-ajax-con')),
  );
    $form['tb']['tb_typography']['sitename_typo']['sitename_ajax_con']['sitename_font_google_style'] = array(
      '#type' => 'radios',
      '#title' => ($selected) ? $selected.t(' styles') : t('Default style'),
      '#options' => _font_style_options($selected),
      '#default_value' => theme_get_setting('sitename_font_google_style'),
      '#attributes'    => array('class' => array('tb-inline-radios')),
      '#states' => array(
        'visible' => array(
          ':input[name="sitename_font_type"]' => array('value' =>'google')
        ),
      ),
    );

    $default_subsets = array();
    if (!$default_subsets) {
      if(theme_get_setting('sitename_font_google_subset')) {
      $default_subsets = theme_get_setting('sitename_font_google_subset');
      }else{
      $default_subsets = array(
        'latin'     => 'latin',
        'greek'     => 0,
        'latin-ext' => 0
        );
      }
    }

    $form['tb']['tb_typography']['sitename_typo']['sitename_ajax_con']['sitename_font_google_subset'] = array(
      '#type' => 'checkboxes',
      '#title' => ($selected) ? $selected.t(' Subsets') : t('Default subset'),
      '#options' => _font_subset_options($selected),
      '#default_value' => $default_subsets,
      '#attributes'    => array( 'class' => array('tb-inline-checkboxes') ),
      '#states' => array(
        'visible' => array(
          'input[name="sitename_font_type"]' => array('value' =>'google')
        )
      ),
    );

$form['tb']['tb_typography']['sitename_typo']['sitename_font_size'] = array(
  '#type' => 'select',
  '#title' => t('Font size'),
  '#default_value' => theme_get_setting('sitename_font_size') ,
  '#options' => _font_size(),
  '#states' => array(
    'invisible' => array(
      'input[name="sitename_font_type"]' => array('value' =>0)
    )
  )
);


/**
 * Body Typography parameters are configured here.
 * ===============================================
 */

$form['tb']['tb_typography']['body_typo'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Body Typography'),
  // '#description'   => t("Content Typography parameters are configured here."),
  '#weight'        => -1,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

  $form['tb']['tb_typography']['body_typo']['body_selector'] = array(
    '#type' => 'hidden',
    '#value' => 'body',
  );

  $form['tb']['tb_typography']['body_typo']['body_font_type'] = array(
    '#type' => 'radios',
    '#title' => t('Font type'),
    '#options' => array('Default', 'google' =>'Google'),
    '#default_value' => (theme_get_setting('body_font_type')) ? theme_get_setting('body_font_type') : "0",
    '#attributes' => array('class' =>array('tb-inline-radios'))
  );

  // $form['tb']['tb_typography']['body_typo']['body_font_websafe'] = array(
  //   '#type' => 'select',
  //   '#title' => t('Websafe Fonts'),
  //   '#default_value' => theme_get_setting('body_font_websafe') ,
  //   '#options' => _websafe_fonts_cache(),
  //   '#states' => array(
  //   'visible' => array(
  //     ':input[name="body_font_type"]' => array('value' =>'websafe')
  //   )
  //   )
  // );

  $form['tb']['tb_typography']['body_typo']['body_font_websafe_weight'] = array(
    '#type' => 'radios',
    '#title' => t('Font weight'),
    '#default_value' => theme_get_setting('body_font_websafe_weight') ,
    '#options' => _font_weight(),
    '#attributes' => array('class' =>array('tb-inline-radios')),
    '#states' => array(
      'visible' => array(
        ':input[name="body_font_type"]' => array('value' =>'websafe')
      )
    )
  );

  $selected = isset($form_state['values']['body_font_google']) ? $form_state['values']['body_font_google'] : theme_get_setting('body_font_google');

  $form['tb']['tb_typography']['body_typo']['body_font_google'] = array(
    '#type' => 'select',
    '#title' => t('Google WebFonts'),
    '#options' => $font_options,
    '#default_value' => $selected,
    '#ajax' => array(
    'callback' => 'font_variants_callback',
    'wrapper' => 'body-ajax-con',
    'method' => 'replace',
    'effect' => 'fade',
    // Don't show any throbber...
    // 'progress' => array('type' => 'none'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="body_font_type"]' => array('value' =>'google')
      )
    )
  );

  $form['tb']['tb_typography']['body_typo']['body_ajax_con'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => array('body-ajax-con')),
  );
    $form['tb']['tb_typography']['body_typo']['body_ajax_con']['body_font_google_style'] = array(
      '#type' => 'radios',
      '#title' => ($selected) ? $selected.t(' styles') : t('Default style'),
      '#options' => _font_style_options($selected),
      '#default_value' => theme_get_setting('body_font_google_style'),
      '#attributes'    => array('class' => array('tb-inline-radios')),
      '#states' => array(
        'visible' => array(
          ':input[name="body_font_type"]' => array('value' =>'google')
        )
      ),
    );

    $default_subsets = array();
    if (!$default_subsets) {
      if(theme_get_setting('body_font_google_subset')) {
      $default_subsets = theme_get_setting('body_font_google_subset');
      }else{
      $default_subsets = array(
        'latin'     => 'latin',
        'greek'     => 0,
        'latin-ext' => 0
        );
      }
    }

    $form['tb']['tb_typography']['body_typo']['body_ajax_con']['body_font_google_subset'] = array(
      '#type' => 'checkboxes',
      '#title' => ($selected) ? $selected.t(' Subsets') : t('Default subset'),
      '#options' => _font_subset_options($selected),
      '#default_value' => $default_subsets,
      '#attributes'    => array( 'class' => array('tb-inline-checkboxes') ),
      '#states' => array(
        'visible' => array(
          ':input[name="body_font_type"]' => array('value' =>'google')
        )
      ),
    );

$form['tb']['tb_typography']['body_typo']['body_font_size'] = array(
  '#type' => 'select',
  '#title' => t('Font size'),
  '#default_value' => theme_get_setting('body_font_size') ,
  '#options' => _font_size(),
  '#states' => array(
    'invisible' => array(
      ':input[name="body_font_type"]' => array('value' =>0)
    )
  )
);


/**
 * Page Title Typography parameters are configured here.
 * ===============================================
 */

$form['tb']['tb_typography']['page_typo'] = array(
  '#type'           => 'fieldset',
  '#title'          => t('Page Title Typography'),
  // '#description' => t("Content Typography parameters are configured here."),
  '#weight'         => 0,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

  $form['tb']['tb_typography']['page_typo']['page_selector'] = array(
    '#type' => 'hidden',
    '#value' => 'h1.page-header',
  );

  $form['tb']['tb_typography']['page_typo']['page_font_type'] = array(
    '#type' => 'radios',
    '#title' => t('Font type'),
    '#options' => array('Default', 'google' =>'Google'),
    '#default_value' => (theme_get_setting('page_font_type')) ? theme_get_setting('page_font_type') : "0",
    '#attributes' => array('class' =>array('tb-inline-radios'))
  );

  // $form['tb']['tb_typography']['page_typo']['page_font_websafe'] = array(
  //   '#type' => 'select',
  //   '#title' => t('Websafe Fonts'),
  //   '#default_value' => theme_get_setting('page_font_websafe') ,
  //   '#options' => _websafe_fonts_cache(),
  //   '#states' => array(
  //   'visible' => array(
  //     ':input[name="page_font_type"]' => array('value' =>'websafe')
  //   )
  //   )
  // );

  $form['tb']['tb_typography']['page_typo']['page_font_websafe_weight'] = array(
    '#type' => 'radios',
    '#title' => t('Font weight'),
    '#default_value' => theme_get_setting('page_font_websafe_weight') ,
    '#options' => _font_weight(),
    '#attributes' => array('class' =>array('tb-inline-radios')),
    '#states' => array(
      'visible' => array(
        ':input[name="page_font_type"]' => array('value' =>'websafe')
      )
    )
  );

  $selected = isset($form_state['values']['page_font_google']) ? $form_state['values']['page_font_google'] : theme_get_setting('page_font_google');

  $form['tb']['tb_typography']['page_typo']['page_font_google'] = array(
    '#type' => 'select',
    '#title' => t('Google WebFonts'),
    '#options' => $font_options,
    '#default_value' => $selected,
    '#ajax' => array(
    'callback' => 'font_variants_callback',
    'wrapper' => 'page-ajax-con',
    'method' => 'replace',
    'effect' => 'fade',
    // Don't show any throbber...
    // 'progress' => array('type' => 'none'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="page_font_type"]' => array('value' =>'google')
      )
    )
  );

  $form['tb']['tb_typography']['page_typo']['page_ajax_con'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => array('page-ajax-con')),
  );
    $form['tb']['tb_typography']['page_typo']['page_ajax_con']['page_font_google_style'] = array(
      '#type' => 'radios',
      '#title' => ($selected) ? $selected.t(' styles') : t('Default style'),
      '#options' => _font_style_options($selected),
      '#default_value' => theme_get_setting('page_font_google_style'),
      '#attributes'    => array('class' => array('tb-inline-radios')),
      '#states' => array(
        'visible' => array(
          ':input[name="page_font_type"]' => array('value' =>'google')
        )
      ),
    );

    $default_subsets = array();
    if (!$default_subsets) {
      if(theme_get_setting('page_font_google_subset')) {
      $default_subsets = theme_get_setting('page_font_google_subset');
      }else{
      $default_subsets = array(
        'latin'     => 'latin',
        'greek'     => 0,
        'latin-ext' => 0
        );
      }
    }

    $form['tb']['tb_typography']['page_typo']['page_ajax_con']['page_font_google_subset'] = array(
      '#type' => 'checkboxes',
      '#title' => ($selected) ? $selected.t(' Subsets') : t('Default subset'),
      '#options' => _font_subset_options($selected),
      '#default_value' => $default_subsets,
      '#attributes'    => array( 'class' => array('tb-inline-checkboxes') ),
      '#states' => array(
        'visible' => array(
          ':input[name="page_font_type"]' => array('value' =>'google')
        )
      ),
    );

$form['tb']['tb_typography']['page_typo']['page_font_size'] = array(
  '#type' => 'select',
  '#title' => t('Font size'),
  '#default_value' => theme_get_setting('page_font_size') ,
  '#options' => _font_size(),
  '#states' => array(
    'invisible' => array(
      ':input[name="page_font_type"]' => array('value' =>0)
    )
  )
);


/**
 * Node Title Typography parameters are configured here.
 * ====
 */

$form['tb']['tb_typography']['node_typo'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Node Title Typography'),
  // '#description'   => t("Content Typography parameters are configured here."),
  '#weight'        => 0,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

  $form['tb']['tb_typography']['node_typo']['node_selector'] = array(
    '#type' => 'hidden',
    '#value' => 'h2.node-title',
  );

  $form['tb']['tb_typography']['node_typo']['node_font_type'] = array(
    '#type' => 'radios',
    '#title' => t('Font type'),
    '#options' => array('Default','google' =>'Google'),
    '#default_value' => (theme_get_setting('node_font_type')) ? theme_get_setting('node_font_type') : "0",
    '#attributes' => array('class' =>array('tb-inline-radios'))
  );

  // $form['tb']['tb_typography']['node_typo']['node_font_websafe'] = array(
  //   '#type' => 'select',
  //   '#title' => t('Websafe Fonts'),
  //   '#default_value' => theme_get_setting('node_font_websafe') ,
  //   '#options' => _websafe_fonts_cache(),
  //   '#states' => array(
  //     'visible' => array(
  //       ':input[name="node_font_type"]' => array('value' =>'websafe')
  //     )
  //   )
  // );

  $form['tb']['tb_typography']['node_typo']['node_font_websafe_weight'] = array(
    '#type' => 'radios',
    '#title' => t('Font weight'),
    '#default_value' => theme_get_setting('node_font_websafe_weight') ,
    '#options' => _font_weight(),
    '#attributes' => array('class' =>array('tb-inline-radios')),
    '#states' => array(
      'visible' => array(
        ':input[name="node_font_type"]' => array('value' =>'websafe')
      )
    )
  );

  $selected = isset($form_state['values']['node_font_google']) ? $form_state['values']['node_font_google'] : theme_get_setting('node_font_google');

  $form['tb']['tb_typography']['node_typo']['node_font_google'] = array(
    '#type' => 'select',
    '#title' => t('Google WebFonts'),
    '#options' => $font_options,
    '#default_value' => $selected,
    '#ajax' => array(
    'callback' => 'font_variants_callback',
    'wrapper' => 'node-ajax-con',
    'method' => 'replace',
    'effect' => 'fade',
    // Don't show any throbber...
    // 'progress' => array('type' => 'none'),
    ),
    '#states' => array(
    'visible' => array(
      ':input[name="node_font_type"]' => array('value' =>'google')
    )
    )
  );

  $form['tb']['tb_typography']['node_typo']['node_ajax_con'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => array('node-ajax-con')),
  );
    $form['tb']['tb_typography']['node_typo']['node_ajax_con']['node_font_google_style'] = array(
      '#type' => 'radios',
      '#title' => ($selected) ? $selected.t(' styles') : t('Default style'),
      '#options' => _font_style_options($selected),
      '#default_value' => theme_get_setting('node_font_google_style'),
      '#attributes'    => array('class' => array('tb-inline-radios')),
      '#states' => array(
        'visible' => array(
          ':input[name="node_font_type"]' => array('value' =>'google')
        )
      ),
    );

    $default_subsets = array();
    if (!$default_subsets) {
      if(theme_get_setting('node_font_google_subset')) {
      $default_subsets = theme_get_setting('node_font_google_subset');
      }else{
      $default_subsets = array(
        'latin'     => 'latin',
        'greek'     => 0,
        'latin-ext' => 0
        );
      }
    }

    $form['tb']['tb_typography']['node_typo']['node_ajax_con']['node_font_google_subset'] = array(
      '#type' => 'checkboxes',
      '#title' => ($selected) ? $selected.t(' Subsets') : t('Default subset'),
      '#options' => _font_subset_options($selected),
      '#default_value' => $default_subsets,
      '#attributes'    => array( 'class' => array('tb-inline-checkboxes') ),
      '#states' => array(
        'visible' => array(
          ':input[name="node_font_type"]' => array('value' =>'google')
        )
      ),
    );

$form['tb']['tb_typography']['node_typo']['node_font_size'] = array(
  '#type' => 'select',
  '#title' => t('Font size'),
  '#default_value' => theme_get_setting('node_font_size') ,
  '#options' => _font_size(),
  '#states' => array(
    'invisible' => array(
      ':input[name="node_font_type"]' => array('value' =>0)
    )
  )
);

/**
 * Block Title Typography parameters are configured here.
 * ======================================================
 */

$form['tb']['tb_typography']['block_typo'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Block Title Typography'),
  // '#description'   => t("Content Typography parameters are configured here."),
  '#weight'        => 0,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

  $form['tb']['tb_typography']['block_typo']['block_selector'] = array(
    '#type' => 'hidden',
    '#value' => '.block-title',
  );

  $form['tb']['tb_typography']['block_typo']['block_font_type'] = array(
    '#type' => 'radios',
    '#title' => t('Font type'),
    '#options' => array('Default','google' =>'Google'),
    '#default_value' => (theme_get_setting('block_font_type')) ? theme_get_setting('block_font_type') : "0",
    '#attributes' => array('class' =>array('tb-inline-radios'))
  );

  // $form['tb']['tb_typography']['block_typo']['block_font_websafe'] = array(
  //   '#type' => 'select',
  //   '#title' => t('Websafe Fonts'),
  //   '#default_value' => theme_get_setting('block_font_websafe') ,
  //   '#options' => _websafe_fonts_cache(),
  //   '#states' => array(
  //     'visible' => array(
  //       ':input[name="block_font_type"]' => array('value' =>'websafe')
  //     )
  //   )
  // );

  $form['tb']['tb_typography']['block_typo']['block_font_websafe_weight'] = array(
    '#type' => 'radios',
    '#title' => t('Font weight'),
    '#default_value' => theme_get_setting('block_font_websafe_weight') ,
    '#options' => _font_weight(),
    '#attributes' => array('class' =>array('tb-inline-radios')),
    '#states' => array(
      'visible' => array(
        ':input[name="block_font_type"]' => array('value' =>'websafe')
      )
    )
  );


  $selected = isset($form_state['values']['block_font_google']) ? $form_state['values']['block_font_google'] : theme_get_setting('block_font_google');

  $form['tb']['tb_typography']['block_typo']['block_font_google'] = array(
    '#type' => 'select',
    '#title' => t('Google WebFonts'),
    '#options' => $font_options,
    '#default_value' => $selected,
    '#ajax' => array(
    'callback' => 'font_variants_callback',
    'wrapper' => 'block-ajax-con',
    'method' => 'replace',
    'effect' => 'fade',
    // Don't show any throbber...
    // 'progress' => array('type' => 'none'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="block_font_type"]' => array('value' =>'google')
      )
    )
  );

  $form['tb']['tb_typography']['block_typo']['block_ajax_con'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => array('block-ajax-con')),
  );
    $form['tb']['tb_typography']['block_typo']['block_ajax_con']['block_font_google_style'] = array(
      '#type' => 'radios',
      '#title' => ($selected) ? $selected.t(' styles') : t('Default style'),
      '#options' => _font_style_options($selected),
      '#default_value' => theme_get_setting('block_font_google_style'),
      '#attributes'    => array('class' => array('tb-inline-radios')),
      '#states' => array(
        'visible' => array(
          ':input[name="block_font_type"]' => array('value' =>'google')
        )
      ),
    );

    $default_subsets = array();
    if (!$default_subsets) {
      if(theme_get_setting('block_font_google_subset')) {
      $default_subsets = theme_get_setting('block_font_google_subset');
      }else{
      $default_subsets = array(
        'latin'     => 'latin',
        'greek'     => 0,
        'latin-ext' => 0
        );
      }
    }

    $form['tb']['tb_typography']['block_typo']['block_ajax_con']['block_font_google_subset'] = array(
      '#type' => 'checkboxes',
      '#title' => ($selected) ? $selected.t(' Subsets') : t('Default subset'),
      '#options' => _font_subset_options($selected),
      '#default_value' => $default_subsets,
      '#attributes'    => array( 'class' => array('tb-inline-checkboxes') ),
      '#states' => array(
        'visible' => array(
          ':input[name="block_font_type"]' => array('value' =>'google')
        )
      ),
    );

$form['tb']['tb_typography']['block_typo']['block_font_size'] = array(
  '#type' => 'select',
  '#title' => t('Font size'),
  '#default_value' => theme_get_setting('block_font_size') ,
  '#options' => _font_size(),
  '#states' => array(
    'invisible' => array(
      ':input[name="block_font_type"]' => array('value' =>0)
    )
  )
);

/**
 * Heading Typography parameters are configured here
 * =================================================
 */

$form['tb']['tb_typography']['heading_sets'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('Heading Typography'),
  '#description'   => t("H1 H2 H3 H4 H5 Typography parameters are configured here."),
  '#weight'        => 0,
  '#collapsible' => TRUE,
  '#collapsed' => FALSE,
);


/**
 * h1 Typography parameters are configured here.
 * ==
 */

$form['tb']['tb_typography']['heading_sets']['h1_typo'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('h1 Typography'),
  // '#description'   => t("Content Typography parameters are configured here."),
  '#weight'        => 1,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

  $form['tb']['tb_typography']['heading_sets']['h1_typo']['h1_selector'] = array(
    '#type' => 'hidden',
    '#value' => 'h1',
  );

  $form['tb']['tb_typography']['heading_sets']['h1_typo']['h1_font_type'] = array(
    '#type' => 'radios',
    '#title' => t('Font type'),
    '#options' => array('Default','google' =>'Google'),
    '#default_value' => (theme_get_setting('h1_font_type')) ? theme_get_setting('h1_font_type') : "0",
    '#attributes' => array('class' =>array('tb-inline-radios'))
  );

  // $form['tb']['tb_typography']['heading_sets']['h1_typo']['h1_font_websafe'] = array(
  //   '#type' => 'select',
  //   '#title' => t('Websafe Fonts'),
  //   '#default_value' => theme_get_setting('h1_font_websafe') ,
  //   '#options' => _websafe_fonts_cache(),
  //   '#states' => array(
  //     'visible' => array(
  //       ':input[name="h1_font_type"]' => array('value' =>'websafe')
  //     )
  //   )
  // );

  $form['tb']['tb_typography']['heading_sets']['h1_typo']['h1_font_websafe_weight'] = array(
    '#type' => 'radios',
    '#title' => t('Font weight'),
    '#default_value' => theme_get_setting('h1_font_websafe_weight') ,
    '#options' => _font_weight(),
    '#attributes' => array('class' =>array('tb-inline-radios')),
    '#states' => array(
      'visible' => array(
        ':input[name="h1_font_type"]' => array('value' =>'websafe')
      )
    )
  );

  $selected = isset($form_state['values']['h1_font_google']) ? $form_state['values']['h1_font_google'] : theme_get_setting('h1_font_google');

  $form['tb']['tb_typography']['heading_sets']['h1_typo']['h1_font_google'] = array(
    '#type' => 'select',
    '#title' => t('Google WebFonts'),
    '#options' => $font_options,
    '#default_value' => $selected,
    '#ajax' => array(
    'callback' => 'font_variants_callback',
    'wrapper' => 'h1-ajax-con',
    'method' => 'replace',
    'effect' => 'fade',
    // Don't show any throbber...
    // 'progress' => array('type' => 'none'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="h1_font_type"]' => array('value' =>'google')
      )
    )
  );

  $form['tb']['tb_typography']['heading_sets']['h1_typo']['h1_ajax_con'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => array('h1-ajax-con')),
  );
    $form['tb']['tb_typography']['heading_sets']['h1_typo']['h1_ajax_con']['h1_font_google_style'] = array(
      '#type' => 'radios',
      '#title' => ($selected) ? $selected.t(' styles') : t('Default style'),
      '#options' => _font_style_options($selected),
      '#default_value' => theme_get_setting('h1_font_google_style'),
      '#attributes'    => array('class' => array('tb-inline-radios')),
      '#states' => array(
        'visible' => array(
          ':input[name="h1_font_type"]' => array('value' =>'google')
        )
      )
    );

    $default_subsets = array();
    if (!$default_subsets) {
      if(theme_get_setting('h1_font_google_subset')) {
      $default_subsets = theme_get_setting('h1_font_google_subset');
      }else{
      $default_subsets = array(
        'latin'     => 'latin',
        'greek'     => 0,
        'latin-ext' => 0
        );
      }
    }

    $form['tb']['tb_typography']['heading_sets']['h1_typo']['h1_ajax_con']['h1_font_google_subset'] = array(
      '#type' => 'checkboxes',
      '#title' => ($selected) ? $selected.t(' Subsets') : t('Default subset'),
      '#options' => _font_subset_options($selected),
      '#default_value' => $default_subsets,
      '#attributes'    => array( 'class' => array('tb-inline-checkboxes') ),
      '#states' => array(
        'visible' => array(
          ':input[name="h1_font_type"]' => array('value' =>'google')
        )
      )
    );

$form['tb']['tb_typography']['heading_sets']['h1_typo']['h1_font_size'] = array(
  '#type' => 'select',
  '#title' => t('Font size'),
  '#default_value' => theme_get_setting('h1_font_size') ,
  '#options' => _font_size(),
  '#states' => array(
    'invisible' => array(
      ':input[name="h1_font_type"]' => array('value' =>0)
    )
  )
);


/**
 * h2 Typography parameters are configured here.
 * =============================================
 */

$form['tb']['tb_typography']['heading_sets']['h2_typo'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('H2 Typography'),
  // '#description'   => t("Content Typography parameters are configured here."),
  '#weight'        => 2,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

  $form['tb']['tb_typography']['heading_sets']['h2_typo']['h2_selector'] = array(
    '#type' => 'hidden',
    '#value' => 'h2',
  );

  $form['tb']['tb_typography']['heading_sets']['h2_typo']['h2_font_type'] = array(
    '#type' => 'radios',
    '#title' => t('Font type'),
    '#options' => array('Default', 'google' =>'Google'),
    '#default_value' => (theme_get_setting('h2_font_type')) ? theme_get_setting('h2_font_type') : "0",
    '#attributes' => array('class' =>array('tb-inline-radios'))
  );

  // $form['tb']['tb_typography']['heading_sets']['h2_typo']['h2_font_websafe'] = array(
  //   '#type' => 'select',
  //   '#title' => t('Websafe Fonts'),
  //   '#default_value' => theme_get_setting('h2_font_websafe') ,
  //   '#options' => _websafe_fonts_cache(),
  //   '#states' => array(
  //     'visible' => array(
  //       ':input[name="h2_font_type"]' => array('value' =>'websafe')
  //     )
  //   )
  // );

  $form['tb']['tb_typography']['heading_sets']['h2_typo']['h2_font_websafe_weight'] = array(
    '#type' => 'radios',
    '#title' => t('Font weight'),
    '#default_value' => theme_get_setting('h2_font_websafe_weight') ,
    '#options' => _font_weight(),
    '#attributes' => array('class' =>array('tb-inline-radios')),
    '#states' => array(
      'visible' => array(
        ':input[name="h2_font_type"]' => array('value' =>'websafe')
      )
    )
  );

  $selected = isset($form_state['values']['h2_font_google']) ? $form_state['values']['h2_font_google'] : theme_get_setting('h2_font_google');

  $form['tb']['tb_typography']['heading_sets']['h2_typo']['h2_font_google'] = array(
    '#type' => 'select',
    '#title' => t('Google WebFonts'),
    '#options' => $font_options,
    '#default_value' => $selected,
    '#ajax' => array(
    'callback' => 'font_variants_callback',
    'wrapper' => 'h2-ajax-con',
    'method' => 'replace',
    'effect' => 'fade',
    // Don't show any throbber...
    // 'progress' => array('type' => 'none'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="h2_font_type"]' => array('value' =>'google')
      )
    )
  );

  $form['tb']['tb_typography']['heading_sets']['h2_typo']['h2_ajax_con'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => array('h2-ajax-con')),
  );
    $form['tb']['tb_typography']['heading_sets']['h2_typo']['h2_ajax_con']['h2_font_google_style'] = array(
      '#type' => 'radios',
      '#title' => ($selected) ? $selected.t(' styles') : t('Default style'),
      '#options' => _font_style_options($selected),
      '#default_value' => theme_get_setting('h2_font_google_style'),
      '#attributes'    => array('class' => array('tb-inline-radios')),
      '#states' => array(
        'visible' => array(
          ':input[name="h2_font_type"]' => array('value' =>'google')
        )
      )
    );

    $default_subsets = array();
    if (!$default_subsets) {
      if(theme_get_setting('h2_font_google_subset')) {
      $default_subsets = theme_get_setting('h2_font_google_subset');
      }else{
      $default_subsets = array(
        'latin'     => 'latin',
        'greek'     => 0,
        'latin-ext' => 0
        );
      }
    }

    $form['tb']['tb_typography']['heading_sets']['h2_typo']['h2_ajax_con']['h2_font_google_subset'] = array(
      '#type' => 'checkboxes',
      '#title' => ($selected) ? $selected.t(' Subsets') : t('Default subset'),
      '#options' => _font_subset_options($selected),
      '#default_value' => $default_subsets,
      '#attributes'    => array( 'class' => array('tb-inline-checkboxes') ),
      '#states' => array(
        'visible' => array(
          ':input[name="h2_font_type"]' => array('value' =>'google')
        )
      )
    );

$form['tb']['tb_typography']['heading_sets']['h2_typo']['h2_font_size'] = array(
  '#type' => 'select',
  '#title' => t('Font size'),
  '#default_value' => theme_get_setting('h2_font_size') ,
  '#options' => _font_size(),
  '#states' => array(
    'invisible' => array(
      ':input[name="h2_font_type"]' => array('value' =>0)
    )
  )
);



/**
 * h3 Typography parameters are configured here.
 * =============================================
 */

$form['tb']['tb_typography']['heading_sets']['h3_typo'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('H3 Typography'),
  // '#description'   => t("Content Typography parameters are configured here."),
  '#weight'        => 3,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

  $form['tb']['tb_typography']['heading_sets']['h3_typo']['h3_selector'] = array(
    '#type' => 'hidden',
    '#value' => 'h3',
  );

  $form['tb']['tb_typography']['heading_sets']['h3_typo']['h3_font_type'] = array(
    '#type' => 'radios',
    '#title' => t('Font type'),
    '#options' => array('Default', 'google' =>'Google'),
    '#default_value' => (theme_get_setting('h3_font_type')) ? theme_get_setting('h3_font_type') : "0",
    '#attributes' => array('class' =>array('tb-inline-radios'))
  );

  // $form['tb']['tb_typography']['heading_sets']['h3_typo']['h3_font_websafe'] = array(
  //   '#type' => 'select',
  //   '#title' => t('Websafe Fonts'),
  //   '#default_value' => theme_get_setting('h3_font_websafe') ,
  //   '#options' => _websafe_fonts_cache(),
  //   '#states' => array(
  //     'visible' => array(
  //       ':input[name="h3_font_type"]' => array('value' =>'websafe')
  //     )
  //   )
  // );

  $form['tb']['tb_typography']['heading_sets']['h3_typo']['h3_font_websafe_weight'] = array(
    '#type' => 'radios',
    '#title' => t('Font weight'),
    '#default_value' => theme_get_setting('h3_font_websafe_weight') ,
    '#options' => _font_weight(),
    '#attributes' => array('class' =>array('tb-inline-radios')),
    '#states' => array(
      'visible' => array(
        ':input[name="h3_font_type"]' => array('value' =>'websafe')
      )
    )
  );

  $selected = isset($form_state['values']['h3_font_google']) ? $form_state['values']['h3_font_google'] : theme_get_setting('h3_font_google');

  $form['tb']['tb_typography']['heading_sets']['h3_typo']['h3_font_google'] = array(
    '#type' => 'select',
    '#title' => t('Google WebFonts'),
    '#options' => $font_options,
    '#default_value' => $selected,
    '#ajax' => array(
    'callback' => 'font_variants_callback',
    'wrapper' => 'h3-ajax-con',
    'method' => 'replace',
    'effect' => 'fade',
    // Don't show any throbber...
    // 'progress' => array('type' => 'none'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="h3_font_type"]' => array('value' =>'google')
      )
    )
  );

  $form['tb']['tb_typography']['heading_sets']['h3_typo']['h3_ajax_con'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => array('h3-ajax-con')),
  );
    $form['tb']['tb_typography']['heading_sets']['h3_typo']['h3_ajax_con']['h3_font_google_style'] = array(
      '#type' => 'radios',
      '#title' => ($selected) ? $selected.t(' styles') : t('Default style'),
      '#options' => _font_style_options($selected),
      '#default_value' => theme_get_setting('h3_font_google_style'),
      '#attributes'    => array('class' => array('tb-inline-radios')),
      '#states' => array(
        'visible' => array(
          ':input[name="h3_font_type"]' => array('value' =>'google')
        )
      )
    );

    $default_subsets = array();
    if (!$default_subsets) {
      if(theme_get_setting('h3_font_google_subset')) {
      $default_subsets = theme_get_setting('h3_font_google_subset');
      }else{
      $default_subsets = array(
        'latin'     => 'latin',
        'greek'     => 0,
        'latin-ext' => 0
        );
      }
    }

    $form['tb']['tb_typography']['heading_sets']['h3_typo']['h3_ajax_con']['h3_font_google_subset'] = array(
      '#type' => 'checkboxes',
      '#title' => ($selected) ? $selected.t(' Subsets') : t('Default subset'),
      '#options' => _font_subset_options($selected),
      '#default_value' => $default_subsets,
      '#attributes'    => array( 'class' => array('tb-inline-checkboxes') ),
      '#states' => array(
        'visible' => array(
          ':input[name="h3_font_type"]' => array('value' =>'google')
        )
      )
    );

$form['tb']['tb_typography']['heading_sets']['h3_typo']['h3_font_size'] = array(
  '#type' => 'select',
  '#title' => t('Font size'),
  '#default_value' => theme_get_setting('h3_font_size') ,
  '#options' => _font_size(),
  '#states' => array(
    'invisible' => array(
      ':input[name="h3_font_type"]' => array('value' =>0)
    )
  )
);


/**
 * h4 Typography parameters are configured here.
 * =============================================
 */

$form['tb']['tb_typography']['heading_sets']['h4_typo'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('h4 Typography'),
  // '#description'   => t("Content Typography parameters are configured here."),
  '#weight'        => 4,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

  $form['tb']['tb_typography']['heading_sets']['h4_typo']['h4_selector'] = array(
    '#type' => 'hidden',
    '#value' => 'h4',
  );

  $form['tb']['tb_typography']['heading_sets']['h4_typo']['h4_font_type'] = array(
    '#type' => 'radios',
    '#title' => t('Font type'),
    '#options' => array('Default', 'google' =>'Google'),
    '#default_value' => (theme_get_setting('h4_font_type')) ? theme_get_setting('h4_font_type') : "0",
    '#attributes' => array('class' =>array('tb-inline-radios'))
  );

  // $form['tb']['tb_typography']['heading_sets']['h4_typo']['h4_font_websafe'] = array(
  //   '#type' => 'select',
  //   '#title' => t('Websafe Fonts'),
  //   '#default_value' => theme_get_setting('h4_font_websafe') ,
  //   '#options' => _websafe_fonts_cache(),
  //   '#states' => array(
  //     'visible' => array(
  //       ':input[name="h4_font_type"]' => array('value' =>'websafe')
  //     )
  //   )
  // );

  $form['tb']['tb_typography']['heading_sets']['h4_typo']['h4_font_websafe_weight'] = array(
    '#type' => 'radios',
    '#title' => t('Font weight'),
    '#default_value' => theme_get_setting('h4_font_websafe_weight') ,
    '#options' => _font_weight(),
    '#attributes' => array('class' =>array('tb-inline-radios')),
    '#states' => array(
      'visible' => array(
        ':input[name="h4_font_type"]' => array('value' =>'websafe')
      )
    )
  );

  $selected = isset($form_state['values']['h4_font_google']) ? $form_state['values']['h4_font_google'] : theme_get_setting('h4_font_google');

  $form['tb']['tb_typography']['heading_sets']['h4_typo']['h4_font_google'] = array(
    '#type' => 'select',
    '#title' => t('Google WebFonts'),
    '#options' => $font_options,
    '#default_value' => $selected,
    '#ajax' => array(
    'callback' => 'font_variants_callback',
    'wrapper' => 'h4-ajax-con',
    'method' => 'replace',
    'effect' => 'fade',
    // Don't show any throbber...
    // 'progress' => array('type' => 'none'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="h4_font_type"]' => array('value' =>'google')
      )
    )
  );

  $form['tb']['tb_typography']['heading_sets']['h4_typo']['h4_ajax_con'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => array('h4-ajax-con')),
  );
    $form['tb']['tb_typography']['heading_sets']['h4_typo']['h4_ajax_con']['h4_font_google_style'] = array(
      '#type' => 'radios',
      '#title' => ($selected) ? $selected.t(' styles') : t('Default style'),
      '#options' => _font_style_options($selected),
      '#default_value' => theme_get_setting('h4_font_google_style'),
      '#attributes'    => array('class' => array('tb-inline-radios')),
      '#states' => array(
        'visible' => array(
          ':input[name="h4_font_type"]' => array('value' =>'google')
        )
      )
    );

    $default_subsets = array();
    if (!$default_subsets) {
      if(theme_get_setting('h4_font_google_subset')) {
      $default_subsets = theme_get_setting('h4_font_google_subset');
      }else{
      $default_subsets = array(
        'latin'     => 'latin',
        'greek'     => 0,
        'latin-ext' => 0
        );
      }
    }

    $form['tb']['tb_typography']['heading_sets']['h4_typo']['h4_ajax_con']['h4_font_google_subset'] = array(
      '#type' => 'checkboxes',
      '#title' => ($selected) ? $selected.t(' Subsets') : t('Default subset'),
      '#options' => _font_subset_options($selected),
      '#default_value' => $default_subsets,
      '#attributes'    => array( 'class' => array('tb-inline-checkboxes') ),
      '#states' => array(
        'visible' => array(
          ':input[name="h4_font_type"]' => array('value' =>'google')
        )
      )
    );

$form['tb']['tb_typography']['heading_sets']['h4_typo']['h4_font_size'] = array(
  '#type' => 'select',
  '#title' => t('Font size'),
  '#default_value' => theme_get_setting('h4_font_size') ,
  '#options' => _font_size(),
  '#states' => array(
    'invisible' => array(
      ':input[name="h4_font_type"]' => array('value' =>0)
    )
  )
);


/**
 * h5 Typography parameters are configured here.
 * =============================================
 */

$form['tb']['tb_typography']['heading_sets']['h5_typo'] = array(
  '#type'          => 'fieldset',
  '#title'         => t('h5 Typography'),
  // '#description'   => t("Content Typography parameters are configured here."),
  '#weight'        => 5,
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
);

  $form['tb']['tb_typography']['heading_sets']['h5_typo']['h5_selector'] = array(
    '#type' => 'hidden',
    '#value' => 'h5',
  );

  $form['tb']['tb_typography']['heading_sets']['h5_typo']['h5_font_type'] = array(
    '#type' => 'radios',
    '#title' => t('Font type'),
    '#options' => array('Default','google' =>'Google'),
    '#default_value' => (theme_get_setting('h5_font_type')) ? theme_get_setting('h5_font_type') : "0",
    '#attributes' => array('class' =>array('tb-inline-radios'))
  );

  // $form['tb']['tb_typography']['heading_sets']['h5_typo']['h5_font_websafe'] = array(
  //   '#type' => 'select',
  //   '#title' => t('Websafe Fonts'),
  //   '#default_value' => theme_get_setting('h5_font_websafe') ,
  //   '#options' => _websafe_fonts_cache(),
  //   '#states' => array(
  //     'visible' => array(
  //       ':input[name="h5_font_type"]' => array('value' =>'websafe')
  //     )
  //   )
  // );

  $form['tb']['tb_typography']['heading_sets']['h5_typo']['h5_font_websafe_weight'] = array(
    '#type' => 'radios',
    '#title' => t('Font weight'),
    '#default_value' => theme_get_setting('h5_font_websafe_weight') ,
    '#options' => _font_weight(),
    '#attributes' => array('class' =>array('tb-inline-radios')),
    '#states' => array(
      'visible' => array(
        ':input[name="h5_font_type"]' => array('value' =>'websafe')
      )
    )
  );

  $selected = isset($form_state['values']['h5_font_google']) ? $form_state['values']['h5_font_google'] : theme_get_setting('h5_font_google');

  $form['tb']['tb_typography']['heading_sets']['h5_typo']['h5_font_google'] = array(
    '#type' => 'select',
    '#title' => t('Google WebFonts'),
    '#options' => $font_options,
    '#default_value' => $selected,
    '#ajax' => array(
    'callback' => 'font_variants_callback',
    'wrapper' => 'h5-ajax-con',
    'method' => 'replace',
    'effect' => 'fade',
    // Don't show any throbber...
    // 'progress' => array('type' => 'none'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="h5_font_type"]' => array('value' =>'google')
      )
    )
  );

  $form['tb']['tb_typography']['heading_sets']['h5_typo']['h5_ajax_con'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => array('h5-ajax-con')),
  );
    $form['tb']['tb_typography']['heading_sets']['h5_typo']['h5_ajax_con']['h5_font_google_style'] = array(
      '#type' => 'radios',
      '#title' => ($selected) ? $selected.t(' styles') : t('Default style'),
      '#options' => _font_style_options($selected),
      '#default_value' => theme_get_setting('h5_font_google_style'),
      '#attributes'    => array('class' => array('tb-inline-radios')),
      '#states' => array(
        'visible' => array(
          ':input[name="h5_font_type"]' => array('value' =>'google')
        )
      )
    );

    $default_subsets = array();
    if (!$default_subsets) {
      if(theme_get_setting('h5_font_google_subset')) {
      $default_subsets = theme_get_setting('h5_font_google_subset');
      }else{
      $default_subsets = array(
        'latin'     => 'latin',
        'greek'     => 0,
        'latin-ext' => 0
        );
      }
    }

    $form['tb']['tb_typography']['heading_sets']['h5_typo']['h5_ajax_con']['h5_font_google_subset'] = array(
      '#type' => 'checkboxes',
      '#title' => ($selected) ? $selected.t(' Subsets') : t('Default subset'),
      '#options' => _font_subset_options($selected),
      '#default_value' => $default_subsets,
      '#attributes'    => array( 'class' => array('tb-inline-checkboxes') ),
      '#states' => array(
        'visible' => array(
          ':input[name="h5_font_type"]' => array('value' =>'google')
        )
      )
    );

$form['tb']['tb_typography']['heading_sets']['h5_typo']['h5_font_size'] = array(
  '#type' => 'select',
  '#title' => t('Font size'),
  '#default_value' => theme_get_setting('h5_font_size') ,
  '#options' => _font_size(),
  '#states' => array(
    'invisible' => array(
      ':input[name="h5_font_type"]' => array('value' =>0)
    )
  )
);
