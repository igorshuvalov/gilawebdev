<?php

$form['tb']['polyfills'] = array(
  '#title' => t('Polyfills'),
  '#type' => 'fieldset',
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  '#weight' => 5,
);

$form['tb']['polyfills']['ie_polyfills'] = array(
  '#title' => t('Polyfills for internet explorer'),
  '#type' => 'fieldset',
);

$form['tb']['polyfills']['ie_polyfills']['boxsizing_polyfill'] = array(
  '#type' => 'checkbox',
  '#title' => t('IE7 Box-sizing'),
  '#default_value' => theme_get_setting('boxsizing_polyfill'),
  '#description' => t('Polyfill that allows the usage of border-box module.'),
);

$form['tb']['polyfills']['ie_polyfills']['flexible_images_polyfill'] = array(
  '#type' => 'checkbox',
  '#title' => t('IE7 flexible images'),
  '#default_value' => theme_get_setting('flexible_images_polyfill'),
  '#description' => t('Flexible images do work in IE7 but the images look artifacted. This polyfill will enable anti-aliasing on images in IE7 and under to fix this.'),
);

$form['tb']['polyfills']['ie_polyfills']['html_polyfill'] = array(
  '#type' => 'checkbox',
  '#title' => t('IE8 HTML5 shiv'),
  '#default_value' => theme_get_setting('html_polyfill'),
  '#description' => t('Without this ie 8 and below do not recognise HTML5 tags and cannot style them. You probably do not want to turn this off.'),
);

$form['tb']['polyfills']['ie_polyfills']['responsive_polyfill'] = array(
  '#type' => 'checkbox',
  '#title' => t('IE8 Respond.js'),
  '#default_value' => theme_get_setting('responsive_polyfill'),
  '#description' => t('Respond.js is the most performant (fast) way to make ie8 and below understand simple mediaqueries. You probably do not want to turn this off, unless you want to use CSS3-MediaQueries-js.'),
);

$form['tb']['polyfills']['ie_polyfills']['responsive_polyfill2'] = array(
  '#type' => 'checkbox',
  '#title' => t('IE8 CSS3-MediaQueries-js'),
  '#default_value' => theme_get_setting('responsive_polyfill2'),
  '#description' => t('A much more elaborate but less performant polyfill for responsive design. Only enable this (and disable respond.js) when you must use advanced media queries.'),
);


$form['tb']['polyfills']['ie_polyfills']['selectivizr_polyfill'] = array(
  '#type' => 'checkbox',
  '#title' => t('CSS3 selectors for IE'),
  '#default_value' => theme_get_setting('selectivizr_polyfill'),
  '#description' => t('selectivizr.js is a JavaScript utility that emulates CSS3 pseudo-classes and attribute selectors in Internet Explorer 6-8.'),
);


// <!-- Cross Browser Polyfills
// ================================================== -->

$form['tb']['polyfills']['cross_browser_polyfills'] = array(
  '#title' => t('Cross Browser Polyfills'),
  '#type' => 'fieldset',
);


$form['tb']['polyfills']['cross_browser_polyfills']['scalefixiOS_polyfill'] = array(
  '#type' => 'checkbox',
  '#title' => t('iOS orientationchange zoom fix'),
  '#default_value' => theme_get_setting('scalefixiOS_polyfill'),
  '#description' => t('A fix for the iOS orientationchange zoom bug.'),
);
