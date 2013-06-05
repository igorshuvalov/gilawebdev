<?php

  $form['tb']['tb_development'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Theme development settings'),
    '#weight'        => 99,
  );

  $form['tb']['tb_development']['welcome_tab'] = array(
    '#type' => 'checkbox',
    '#title' => t('Welcome tab'),
    '#description' => t('You can hide here, if you don\'t want to see "Welcome" tab anymore.'),
    '#default_value' => theme_get_setting('welcome_tab'),
  );

  $form['tb']['tb_development']['bootstrap_rebuild_registry'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Rebuild theme registry on every page.'),
    '#default_value' => theme_get_setting('bootstrap_rebuild_registry'),
    '#description'   => t('During theme development, it can be very useful to continuously <a href="!link">rebuild the theme registry</a>.') . '<div class="alert alert-error">' . t('WARNING: this is a huge performance penalty and must be turned off on production websites. ') . l('Drupal.org documentation on theme-registry.', 'http://drupal.org/node/173880#theme-registry'). '</div>',
  );


$form['tb']['tb_development']['custom_css'] = array(
  '#type' => 'textarea',
  '#title' => t('Custom css'),
  '#default_value' => theme_get_setting('custom_css'),
  '#description' => t("You can write your own css codes here. Please be careful. There is no  any malicious code control and malicious code can cause unexpected results."),
);


  // $form['tb']['tb_development']['cdn'] = array(
  //   '#type'          => 'fieldset',
  //   '#title'         => t('Theme cdn settings'),
  // );

  // $form['tb']['tb_development']['cdn']['cdn_bootstrap'] = array(
  //   '#type'          => 'checkbox',
  //   '#title'         => t('Use CDN to load in the bootstrap files'),
  //   '#default_value' => theme_get_setting('cdn_bootstrap'),
  //   '#description'   => t('Use cdn (a third party hosting server) to host the bootstrap files, Bootstrap Theme will not use the local CSS files anymore and instead the visitor will download them from ') . l('bootstrapcdn.com', 'http://bootstrapcdn.com')
  //                       .'<div class="alert alert-error">' . t('WARNING: this technique will give you a performance boost but will also make you dependant on a third party who has no obligations towards you concerning uptime and service quality.') . '</div>',
  // );

  // $form['tb']['tb_development']['cdn']['cdn_jquery'] = array(
  //   '#type'          => 'checkbox',
  //   '#title'         => t('Use CDN to load in a newer version of jQuery using the no-conflict solution.'),
  //   '#default_value' => theme_get_setting('cdn_jquery'),
  //   '#description'   => t('Use cdn to host the latest version of jquery and load the newer version using the ') . l('no-conflict', 'http://api.jquery.com/jQuery.noConflict/') . t(' solution.')
  //                         . '<div class="alert alert-error">' .
  //                           ('WARNING: this technique will load 2 versions of jQuery, which is bad for front-end performance and adds an extra whopping 90kb (not gziped) to your download (aka not mobile friendly).
  //                            Also this solution uses CDN and this will make you dependant on a third party who has no obligations towards you concerning uptime and service quality.') . '</div>',
  // );
