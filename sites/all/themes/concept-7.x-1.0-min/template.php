<?php

global $theme, $base_path, $theme_path, $files_path, $base_theme_info;

$theme_path = drupal_get_path('theme', 'bootstrap');
$files_path = variable_get('file_public_path', conf_path() . '/files');

require_once $theme_path . '/includes/theme-functions.inc';
require_once $theme_path . '/includes/bootstrap.inc';
require_once $theme_path . '/includes/theme.inc';
require_once $theme_path . '/includes/pager.inc';
require_once $theme_path . '/includes/form.inc';
require_once $theme_path . '/includes/admin.inc';
require_once $theme_path . '/includes/menu.inc';

// Load module specific files in the modules directory.
$includes = file_scan_directory($theme_path . '/includes/modules', '/\.inc$/');
foreach ($includes as $include) {
  if (module_exists($include->name)) {
    require_once $include->uri;
  }
}

/**
 * Load Plugins
 */
foreach (file_scan_directory($theme_path . '/plugins', '/template.inc/i') as $file) {
  require_once($file->uri);
}

// Auto-rebuild the theme registry during theme development.
if (theme_get_setting('bootstrap_rebuild_registry') && !defined('MAINTENANCE_MODE')) {
  // Rebuild .info data.
  system_rebuild_theme_data();
  // Rebuild theme registry.
  drupal_theme_rebuild();
}

/**
 * undocumented function
 *
 * @return void
 * @author
 **/
function bootstrap_init(){
  global $base_url, $base_path;
  $theme_path = $base_url . '/' .drupal_get_path('theme','bootstrap');
  drupal_add_js(array(
      'concept' =>
        array(
          'path'  => $theme_path,
        )
  ),'setting');

  /**
   * TinyNav support
   */
  if (theme_get_setting('mainmenu_tinynav')) {
    drupal_add_js(array(
      'TinyNav' =>
        array(
          'status'  => (bool)theme_get_setting('mainmenu_tinynav'),
          'classes'   => implode(" ", theme_get_setting('tinynav_classes') )
        )
    ),'setting');
  }


  // $flexsettings = theme_get_setting('tb_flexslider');
  // _flexslider_typecast_optionset($flexsettings);
  // drupal_add_js(array(
  //   'tbflex' => $flexsettings
  // ),'setting');

  // $rw_carousel = theme_get_setting('recent_works_carousel');
  // tb_caroufredsel_typecast_optionset($rw_carousel);
  // drupal_add_js(array(
  //   'rw_carousel' => $rw_carousel
  // ),'setting');

  // $Googlefonts = _get_google_fonts();

  // if (count($Googlefonts) > 0) {

  //   drupal_add_js('http://ajax.googleapis.com/ajax/libs/webfont/1/webfont.js',
  //     array(
  //       'type' => 'external',
  //       'group' => JS_THEME,
  //       'every_page' => TRUE
  //     )
  //   );

  //   drupal_add_js(array('biotic_font_setting' => $Googlefonts), 'setting');
  // }

  /**
   * @TODO
   *
   * Background Custom with backstretch
   *
   * ---------------------------------------------------------------------------
   */

    // if (theme_get_setting('background_custom_enable') && (theme_get_setting('image_opacity') == 100)) {
    //   if (theme_get_setting('background_custom_path')) {
    //     $background_custom_path = theme_get_setting('background_custom_path');
    //       if (file_uri_scheme($background_custom_path) == 'public') {
    //         $path = file_uri_target($background_custom_path);
    //       }
    //   }
    //   else {
    //     $parts = theme_get_setting('background_images');
    //     $background_custom_upload_fid = file_load( theme_get_setting('background_custom_upload') );
    //     $path = file_create_url( $background_custom_upload_fid->uri );
    //   }

    //   drupal_add_js(array(

    //       'backstretch' =>
    //         array(
    //           'status' => TRUE,
    //           'path'  => $path,
    //         )
    //   ),'setting');

    // }



}
bootstrap_init();


if (module_exists('colorbox')) {
  # code...

  function bootstrap_colorbox_imagefield($variables) {
    $class = array('colorbox');

    $overlayer = '<div class="overlayer"><span class="icon-resize-full"></span></div>';

    if ($variables['image']['style_name'] == 'hide') {
      $image = '';
      $class[] = 'js-hide';
    }
    elseif (!empty($variables['image']['style_name'])) {
      $image = theme('image_style', $variables['image']);
    }
    else {
      $image = theme('image', $variables['image']);
    }

    $options = array(
      'html' => TRUE,
      'attributes' => array(
        'title' => $variables['title'],
        'class' => $class,
        'rel' => $variables['gid'],
      )
    );

    return l($image.$overlayer, $variables['path'], $options);
  }


}



/**
 * hook_theme()
 */
function bootstrap_theme(&$existing, $type, $theme, $path) {
  // If we are auto-rebuilding the theme registry, warn about the feature.
  if (
    // Only display for site config admins.
    function_exists('user_access') && user_access('administer site configuration')
    && theme_get_setting('bootstrap_rebuild_registry')
    // Always display in the admin section, otherwise limit to three per hour.
    && (arg(0) == 'admin' || flood_is_allowed($GLOBALS['theme'] . '_rebuild_registry_warning', 3))
  ) {
    flood_register_event($GLOBALS['theme'] . '_rebuild_registry_warning');
    drupal_set_message(t('For easier theme development, the theme registry is being rebuilt on every page request. It is <em>extremely</em> important to <a href="!link">turn off this feature</a> on production websites.', array('!link' => url('admin/appearance/settings/' . $GLOBALS['theme']))), 'warning', FALSE);
  }

  return array(
    'bootstrap_links' => array(
      'variables' => array(
        'links' => array(),
        'attributes' => array(),
        'heading' => NULL
      ),
    ),
    'bootstrap_btn_dropdown' => array(
      'variables' => array(
        'links' => array(),
        'attributes' => array(),
        'type' => NULL
      ),
    ),
  );
}

/**
 * Override theme_breadrumb().
 *
 * Print breadcrumbs as a list, with separators.
 */
function bootstrap_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    $breadcrumbs = '<ul id="breadcrumbs" class="unstyled fsize12 inline">';
      $breadcrumbs .= '<li>You are here: </li>';
    $count = count($breadcrumb) - 1;
    foreach ($breadcrumb as $key => $value) {
      if ($count != $key) {
        $breadcrumbs .= '<li>' . $value . '<span class=""> <i> &rarr; </i></span></li>';
      }
      else{
        $breadcrumbs .= '<li>' . $value . '</li>';
      }
    }
    $breadcrumbs .= '</ul>';

    return $breadcrumbs;
  }
}

/**
 * Override or insert variables in the html_tag theme function.
 */
function bootstrap_process_html_tag(&$variables) {
  $tag = &$variables['element'];

  if ($tag['#tag'] == 'style' || $tag['#tag'] == 'script') {
    // Remove redundant type attribute and CDATA comments.
    unset($tag['#attributes']['type'], $tag['#value_prefix'], $tag['#value_suffix']);

    // Remove media="all" but leave others unaffected.
    if (isset($tag['#attributes']['media']) && $tag['#attributes']['media'] === 'all') {
      unset($tag['#attributes']['media']);
    }
  }
}

/**
 * Preprocess variables for page.tpl.php
 *
 * @see page.tpl.php
 */
function bootstrap_preprocess_page(&$variables) {
  global $files_path;
  // Add information about the number of sidebars.
  if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    $variables['columns'] = 3;
  }
  elseif (!empty($variables['page']['sidebar_first'])) {
    $variables['columns'] = 2;
  }
  elseif (!empty($variables['page']['sidebar_second'])) {
    $variables['columns'] = 2;
  }
  else {
    $variables['columns'] = 1;
  }

  // Primary nav
  $variables['primary_nav'] = FALSE;
  if ($variables['main_menu']) {
    // Build links
    $variables['primary_nav'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
    // Provide default theme wrapper function
    $variables['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');
  }

  // Secondary nav
  $variables['secondary_nav'] = FALSE;
  if ($variables['secondary_menu']) {
    // Build links
    $variables['secondary_nav'] = menu_tree(variable_get('menu_secondary_links_source', 'user-menu'));
    // Provide default theme wrapper function
    $variables['secondary_nav']['#theme_wrappers'] = array('menu_tree__secondary');
  }

  // Replace tabs with drop down version
  $variables['tabs']['#primary'] = _bootstrap_local_tasks($variables['tabs']['#primary']);

  // drupal_add_js('http://ajax.googleapis.com/ajax/libs/webfont/1/webfont.js','external');
  //
  //

  // Layout Mode
  if ( theme_get_setting('layout_mode') == "responsive" ) {
    $responsiveCSS = drupal_get_path('theme','bootstrap')."/assets/css/responsive.css";
    drupal_add_css(
      $responsiveCSS, array(
        'preprocess' => variable_get('preprocess_css', '') == 1 ? TRUE : FALSE,
        'group' => CSS_THEME,
        'media' => 'all',
        'every_page' => TRUE
      )
    );
  }

  // Custom brand classes
  if (theme_get_setting('brand_classes')) {
    $Classes = theme_get_setting('brand_classes');
    asort($Classes);
    $variables['custom_brand_classes'] = implode(" ", $Classes );
  }else{
     $variables['custom_brand_classes'] = "";
  }

  // Custom Main menu classes
  if (theme_get_setting('mainmenu_classes')) {
    $Classes = theme_get_setting('mainmenu_classes');
    asort($Classes);
    $variables['custom_mainmenu_classes'] = implode(" ", $Classes );
  }else{
     $variables['custom_mainmenu_classes'] = "";
  }



  //TODO: delta support
  if ( theme_get_setting('delta_css') ) {
    $deltaCSS = theme_get_setting('delta_css');
    $file = $files_path . '/tb-cache-'.$deltaCSS.'.css';
    if (is_file($file)) {
      drupal_add_css(
        $file, array(
          'preprocess' => variable_get('preprocess_css', '') == 1 ? TRUE : FALSE,
          'group' => CSS_THEME,
          'media' => 'all',
          'every_page' => TRUE,
          'weight' => 100
        )
      );
    }
  }else{
    $globalfile = $files_path . '/tb-cache-bootstrap.css';
    if (is_file($globalfile)) {
      drupal_add_css(
        $globalfile, array(
          'preprocess' => variable_get('preprocess_css', '') == 1 ? TRUE : FALSE,
          'group' => CSS_THEME,
          'media' => 'all',
          'every_page' => TRUE,
          'weight' => 100
        )
      );
    }
  }

  /* FlexSlider Settings */
  // $flexsettings = theme_get_setting('tb_flexslider');
  // _flexslider_typecast_optionset($flexsettings);
  // drupal_add_js(array(
  //   'tbflex' => $flexsettings
  // ),'setting');

  /* Rcent works Carousel */
  // $rw_carousel = theme_get_setting('recent_works_carousel');
  // tb_caroufredsel_typecast_optionset($rw_carousel);
  // drupal_add_js(array(
  //   'rw_carousel' => $rw_carousel
  // ),'setting');


  /* Google fonts */
  $Googlefonts = _get_google_fonts();

  if (count($Googlefonts) > 0) {

    drupal_add_js('http://ajax.googleapis.com/ajax/libs/webfont/1/webfont.js',
      array(
        'type' => 'external',
        'group' => JS_THEME,
        'every_page' => TRUE
      )
    );

    drupal_add_js(array('biotic_font_setting' => $Googlefonts), 'setting');
  }

}

/**
 * Bootstrap theme wrapper function for the primary menu links
 * main menu pull-right
 */
function bootstrap_menu_tree__primary(&$variables) {

  if (theme_get_setting('mainmenu_classes')) {
    $custom_classes = implode(" ", theme_get_setting('mainmenu_classes') );
  }else{
    $custom_classes = "";
  }

  return '<ul id="tbMainMenu" class="menu nav nav-pills '.$custom_classes.' ">' . $variables['tree'] . '</ul>';
}

/**
 * Bootstrap theme wrapper function for the secondary menu links
 */
function bootstrap_menu_tree__secondary(&$variables) {
  return '<ul class="menu nav pull-right">' . $variables['tree'] . '</ul>';
}

/**
 * Returns HTML for a single local action link.
 *
 * This function overrides theme_menu_local_action() to add the icons that ship
 * with Bootstrap to the action links.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: A render element containing:
 *     - #link: A menu link array with "title", "href", "localized_options", and
 *       "icon" keys. If "icon" is not passed, it defaults to "plus-sign".
 *
 * @ingroup themeable
 *
 * @see theme_menu_local_action().
 */
function bootstrap_menu_local_action($variables) {
  $link = $variables['element']['#link'];

  // Build the icon rendering element.
  if (empty($link['icon'])) {
    $link['icon'] = 'plus-sign';
  }
  $icon = '<i class="' . drupal_clean_css_identifier('icon-' . $link['icon']) . '"></i>';

  // Format the action link.
  $output = '<li>';
  if (isset($link['href'])) {
    $options = isset($link['localized_options']) ? $link['localized_options'] : array();

    // If the title is not HTML, sanitize it.
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }

    // Force HTML so we can add the icon rendering element.
    $options['html'] = TRUE;
    $output .= l($icon . $link['title'], $link['href'], $options);
  }
  elseif (!empty($link['localized_options']['html'])) {
    $output .= $icon . $link['title'];
  }
  else {
    $output .= $icon . check_plain($link['title']);
  }
  $output .= "</li>\n";

  return $output;
}

/**
 * Preprocess variables for node.tpl.php
 *
 * @see node.tpl.php
 */
function bootstrap_preprocess_node(&$variables) {
  if ($variables['teaser']) {
    $variables['classes_array'][] = 'row-fluid';
  }

  // dpm($variables);
  $variables['content']['links']['node']['#links']['node-readmore']['attributes']['class'][] = "btn btn-small";

  $variables['theme_hook_suggestions'][] = 'node__' . $variables['type'] . '__' . $variables['view_mode'];
  $variables['title_attributes_array']['class'][] = 'node-title';
}

/**
 * Preprocess variables for region.tpl.php
 *
 * @see region.tpl.php
 */
function bootstrap_preprocess_region(&$variables, $hook) {
  if ($variables['region'] == 'content') {
    $variables['theme_hook_suggestions'][] = 'region__no_wrapper';
  }

  if ($variables['region'] == "sidebar_first") {
    // $variables['classes_array'][] = 'well';
  }

  if($variables['region'] == "header") {
    $variables['classes_array'][] = 'row';
  }
}

/**
 * Preprocess variables for block.tpl.php
 *
 * @see block.tpl.php
 */
function bootstrap_preprocess_block(&$variables, $hook) {
  //$variables['classes_array'][] = 'row';
  // Use a bare template for the page's main content.
  if ($variables['block_html_id'] == 'block-system-main') {
    $variables['theme_hook_suggestions'][] = 'block__no_wrapper';
  }
  $variables['title_attributes_array']['class'][] = 'block-title';
  $variables['title_attributes_array']['class'][] = 'fsize18';
  $variables['title_attributes_array']['class'][] = 'fbold';
  $variables['title_attributes_array']['class'][] = 'line';



  // if ($variables['block_html_id'] == 'block-user-login') {

  //   $variables['elements']['name']['#attributes']['class'][] = 'input-large';
  //   dpm($variables);
  //   # code...
  // }

}

/**
 * Override or insert variables into the block templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function bootstrap_process_block(&$variables, $hook) {
  // Drupal 7 should use a $title variable instead of $block->subject.
  $variables['title'] = $variables['block']->subject;
}

/**
 * Returns the correct span class for a region
 */
function _bootstrap_content_span($columns = 1) {
  $class = FALSE;

  switch($columns) {
    case 1:
      $class = 'span12';
      break;
    case 2:
      $class = 'span9';
      break;
    case 3:
      $class = 'span6';
      break;
  }

  return $class;
}



function bootstrap_preprocess_html(&$vars) {
  global $theme, $base_path, $theme_path;
    /**
   * If a theme wants to use advanced backgrounds these must go into their own
   * tags since they will have to use IE proprietary filters in order to work in
   * IE LTE IE8. Setting IE filters on the body tags causes problems.
   */
  $vars['page_backgrounds'] = '';
  $cond_top = $cond_bottom = '';

  if (theme_get_setting('gradient_enable') && theme_get_setting('layout_type') == "boxed" ) {
    $vars['page_backgrounds'] .= '<div class="bg-gradient"></div>';
  }

  if (theme_get_setting('bg_image_enable') && theme_get_setting('background_pattern') && theme_get_setting('layout_type') == "boxed" ) {
    $vars['page_backgrounds'] .= '<div class="bg-pattern"></div>';
  }

  if (theme_get_setting('bg_image_enable') && theme_get_setting('background_custom_upload') && theme_get_setting('layout_type') == "boxed" ) {
    $vars['page_backgrounds'] .= '<div class="bg-image"></div>';
  }

  if (theme_get_setting('html_polyfill')) {
  $cond_top .= "<!-- HTML5 element support for IE6-8 -->\n";
  $cond_top .= '<!--[if (lt IE 9) ]>'."\n".'<script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>'."\n".'<![endif]-->'."\n";
  }
  if (theme_get_setting('responsive_polyfill')) {
    $cond_top .= '<!--[if (lt IE 9) & (!IEMobile)]>'."\n".'<script src="' . $base_path.$theme_path . '/assets/js/vendor/respond.min.js"></script>'."\n".'<![endif]-->'."\n";
  }
  if (theme_get_setting('responsive_polyfill2')) {
    $cond_top .= '<!--[if (lt IE 9) & (!IEMobile)]>'."\n".'<script src="' . $base_path.$theme_path . '/assets/js/vendor/css3-mediaqueries.js"></script>'."\n".'<![endif]-->'."\n";
  }
  if (theme_get_setting('selectivizr_polyfill')) {
    $cond_top .= '<!--[if (lt IE 9) ]>'."\n".'<script src="' . $base_path.$theme_path . '/assets/js/vendor/selectivizr.min.js"></script>'."\n".'<![endif]-->'."\n";
  }
  if (theme_get_setting('flexible_images_polyfill')) {
    $cond_bottom .= '<!--[if (lt IE 8) ]>'."\n".'<script src="' . $base_path.$theme_path . '/assets/js/vendor/imgSizer.min.js"></script>'."\n".'<![endif]-->'."\n";
  }

  $vars['cond_scripts_top'] = $cond_top;
  $vars['cond_scripts_bottom'] = $cond_bottom;


  // If no key is given, use the current theme if we can determine it.
  $theme = !empty($GLOBALS['theme_key']) ? $GLOBALS['theme_key'] : '';
  if ($theme) {
    $themes = list_themes();
    $theme_object = $themes[$theme];
  }

  // build apple-touch-icon URL
  $url_plain = '';
  if (theme_get_setting('toggle_touch_icon_plain')) {  // include icon link
      if (theme_get_setting('default_touch_icon_plain')) { // use default icon from theme or module
        if (file_exists($touch_icon = dirname($theme_object->filename) . '/apple-touch-icon.png')) { // theme provides a default icon
          $url_plain = file_create_url($touch_icon);
        }
        else { // fallback to module-provided default icon
          $url_plain = file_create_url(drupal_get_path('theme', 'bootstrap') . '/apple-touch-icon.png');
        }
      }
      elseif (theme_get_setting('touch_icon_path_plain') && !theme_get_setting('touch_icon_upload_plain')) { // custom icon
        $file_uri_scheme = "public://";
        $file_path = file_create_url( $file_uri_scheme . theme_get_setting('touch_icon_path_plain'));
        if (file_exists($file_path)) {
          $url_plain = $file_path;
        }else{
          drupal_set_message(t('<b>IOS touch icon</b> file does not exist on your file system. Please make sure that the path is correct and the file is on your system.'), 'error');
        }

      }elseif (theme_get_setting('touch_icon_upload_plain') && !theme_get_setting('touch_icon_path_plain')) {
        # code...
        $touch_icon_upload_plain_fid = file_load( theme_get_setting('touch_icon_upload_plain') );
        $url_plain = file_create_url( $touch_icon_upload_plain_fid->uri );
      }
  }

  // build apple-touch-icon URL
  $url_precomp = '';
  if (theme_get_setting('toggle_touch_icon_precomp')) {  // include icon link
      if (theme_get_setting('default_touch_icon_precomp')) { // use default icon from theme or module
        if (file_exists($touch_icon = dirname($theme_object->filename) . '/apple-touch-icon-precomposed.png')) { // theme provides a default icon
          $url_precomp = file_create_url($touch_icon);
        }
        else { // fallback to module-provided default icon
          $url_precomp = file_create_url(drupal_get_path('theme', 'bootstrap') . '/apple-touch-icon-precomposed.png');
        }
      }
      elseif (theme_get_setting('touch_icon_path_precomp') && !theme_get_setting('touch_icon_upload_precomp')) { // custom icon
        $file_uri_scheme = "public://";
        $file_path = file_create_url( $file_uri_scheme . theme_get_setting('touch_icon_path_precomp'));
        if (file_exists($file_path)) {
          # code...
          $url_precomp = $file_path;
        }else{
          drupal_set_message(t('<b>IOS touch icon</b> (precomposed) file does not exist on your file system. Please make sure that the path is correct and the file is on your system.'), 'error');
        }


      }elseif (theme_get_setting('touch_icon_upload_precomp') && !theme_get_setting('touch_icon_path_precomp')) {
        # code...
        $touch_icon_upload_precomp_fid = file_load( theme_get_setting('touch_icon_upload_precomp') );
        $url_precomp = file_create_url( $touch_icon_upload_precomp_fid->uri );
      }
  }

  // output links
  if (check_url($url_plain)) { // no output if $url_plain = ''
    drupal_add_html_head_link(array(
      'rel'  => 'apple-touch-icon',
      'href' => $url_plain,
      'type' => file_get_mimetype($url_plain),
    ));
  }
  if (check_url($url_precomp)) { // no output if $url_precomp = ''
    drupal_add_html_head_link(array(
      'rel'  => 'apple-touch-icon-precomposed',
      'href' => $url_precomp,
      'type' => file_get_mimetype($url_precomp),
    ));
  }

}


/**
 * Recent works function
 *
 * @param    int  $limit Recent works visible item limit
 * @param string  $order Item order status DESC or ASC
 * @return void recen works carousel html
 * @example
 *     recentworks ($limit = '4', $order = 'DESC')
 *
 **/
function recentworks ($limit = '4', $order = 'DESC'){
  $type = "tbportfolio";
  // $result = db_query('SELECT n.nid, n.title FROM {node} n WHERE n.type = :type' , array(':type' => $type) );
  //
  $options = theme_get_setting('recent_works_carousel');

  switch ($options['items']['visible']) {
    case 2:
      $span = "span6";
      break;
    case 3:
      $span = "span4";
      break;
    case 4:
      $span = "span3";
      break;
    case 6:
      $span = "span2";
      break;
    default:
      $span = "span3";
      break;
  }


  $query = db_select('node', 'n')
    ->condition('n.type', $type, '=')
    ->condition('n.status',1,'=')
    ->fields('n', array('nid', 'title', 'status', 'created','sticky'))
    ->orderBy('n.sticky', 'DESC')
    ->orderBy('n.created', $order)
    ->range(0, $limit);

    $result = $query->execute();

  // krumo($result2);

  // Result is returned as a iterable object that returns a stdClass object on each iteration
  foreach ($result as $record) {
    // Perform operations on $record->title, etc. here.
    // in this example the available data would be mapped to object properties:
    $node = node_load($record->nid);
    // $image = $node->field_tbportfolio_images['und'][0]['uri'];
    $image       = field_get_items('node', $node, 'field_tbportfolio_images');
    $image_title = $image['0']['title'];
    $image_path  = file_create_url( $image['0']['uri']  );
    $image_output = field_view_value('node', $node, 'field_tbportfolio_images', $image[0], array(
      'type' => 'image',
      'settings' => array(
        'image_style' => '640x360',
        // 'image_link' => 'file',
      )
    ));

    $options = array(
      'html' => TRUE,
      'attributes' => array(
        'title' => $record->title,
        'class' => "",
        'rel'   => "",
      )
    );

    $overlayer = '<div class="overlayer"><span class="icon-resize-full"></span></div>';
    $image_linked = l( render($image_output).$overlayer, $image_path, $options);

    $title = $record->title;
    //$image = render($image_output);

    $image = $image_linked;
    $url = url('node/' . $record->nid, array('absolute' => TRUE) );

    /* Standart Drupal 7 */
    $body_field = field_get_items('node', $node, 'body');
    $body_value = field_view_value('node', $node, 'body', $body_field[0]);

    $body = render($body_value);
    $trim = strip_tags($body);

    // truncate_utf8($string, $max_length, $wordsafe = FALSE, $add_ellipsis = FALSE, $min_wordsafe_length = 1)
    $description = truncate_utf8( $trim, 60 ,true,"...",3);


$item = <<< CON
<li class="$span">
<div class="imagebox">$image</div>
<h5 class="fbold title"><a href="$url">$title</a></h5>
<p>$description</p>
</li>
CON;
    $output[] = $item;
  }

  $items = "";
  foreach ($output as $key => $value){ $items .= $value; }

  printf('<div class="row"><ul id="recentworks" class="tblist clearfix unstyled">%s</ul></div>', $items );

}


/**
 * Portfolio standart
 *
 * @param int $limit
 *   Item limit per page (default 10)
 * @param string $order
 *   Portfolio order (default DESC )
 * @return void $build
 *   Portfolio type of the passed-in data.
 *
 *
 **/
function portfolio($limit = '4',$order = 'DESC'){

  $type = "tbportfolio";
  $build = array();

  $query = db_select('node', 'n')->extend('PagerDefault');
  $nids = $query
    ->fields('n', array('nid', 'status', 'created','sticky'))
    ->condition('type', $type)
    ->condition('status',1)
    ->orderBy('sticky', 'DESC')
    ->orderBy('created', $order)
    ->limit($limit)
    ->addTag('node_access')
    ->execute()
    ->fetchCol();
    // ->range(0, $limit);

  if (!empty($nids)) {
    $nodes = node_load_multiple($nids);
    $build += node_view_multiple($nodes);
    $build['pager'] = array(
      '#theme' => 'pager',
      '#weight' => 5,
    );
  }else{
    drupal_set_message(t('You have not created any Portfolio entries.'));
  }

  print drupal_render($build);
}

/**
 * Portfolio Filtered
 *
 * @return void $build
 *
 **/
function portfoliofiltered(){

  $isotope = drupal_get_path('theme', 'bootstrap') ."/assets/js/vendor/jquery.isotope.min.js";
  drupal_add_js($isotope, array( 'type' => 'file', 'scope' => 'footer', 'weight' => 5 ) );

  drupal_add_js( array( 'portfoliofiltered' => array( 'filter' => true ) ), 'setting' );

  $type = "tbportfolio";
  $filters = array();

  $query = db_select('node', 'n')
    ->condition( 'type', $type )
    ->condition( 'status',1 )
    ->fields( 'n', array('nid', 'title', 'status', 'created','sticky'))
    ->orderBy( 'sticky', 'DESC' )
    ->orderBy( 'created', 'DESC' )
    ->addTag('node_access')
    ->execute()
    ->fetchCol();

  // Result is returned as a iterable object that returns a stdClass object on each iteration
  foreach ($query as $record) {
    // Perform operations on $record->title, etc. here.
    // in this example the available data would be mapped to object properties:
    $node = node_load($record);
    // $image = $node->field_tbportfolio_images['und'][0]['uri'];
    $image = field_get_items('node', $node, 'field_tbportfolio_images');
    $image_output = field_view_value('node', $node, 'field_tbportfolio_images', $image[0], array(
      'type' => 'image',
      'settings' => array(
        'image_style' => '640x360',
        'image_link' => 'file',
      ),
    ));

    $cat = field_get_items('node', $node, 'field_tbportfolio_categories');
    $categories_output = "";
    if ($cat) {
      foreach ($cat as $key=>$value) {
        $categories = field_view_value( 'node', $node, 'field_tbportfolio_categories', $cat[$key] );


        $cat_plaintext = strip_tags(drupal_render($categories));

        $clean = preg_replace("/&#?[a-z0-9]{2,8};/i","",$cat_plaintext);

        $cat_class = str_replace(" ", "-", strtolower($clean));



        $filters[$cat_plaintext] = $cat_class;

        $categories_output .= $cat_class ." ";


      }

    }



    $title = $node->title;
    $image = render($image_output);
    $url = url('node/' . $node->nid, array('absolute' => TRUE) );

    /* Standart Drupal 7 */
    $body_field = field_get_items('node', $node, 'body');
    $body_value = field_view_value('node', $node, 'body', $body_field[0]);
    $body = render($body_value);
    $trim = strip_tags($body);

    // truncate_utf8($string, $max_length, $wordsafe = FALSE, $add_ellipsis = FALSE, $min_wordsafe_length = 1)
    $description = truncate_utf8( $trim, 60 ,true,"...",3);


$item = <<< CON
<div class="portfolio span3 $categories_output">
<div class="imagebox">$image</div>
<h5 class="title"><a href="$url">$title</a></h5>
<p>$description</p>
</div>
CON;
    $output[] = $item;

}

$filter_output = "";
foreach ($filters as $key => $value) {
    $filter_output .= sprintf('<li><a href="#filter" data-option-value=".%s" >%s</a></li>',$value,$key);
}

$filter = <<< FTL
<ul id="filters" class="nav nav-pills option-set clearfix" data-option-key="filter">
  <li class="active"><a href="#filter" data-option-value="*" class="selected" >All</a></li>
  $filter_output
</ul>
FTL;

  $items = "";
  foreach ($output as $key => $value){ $items .= $value; }

$code = <<< COL
<!-- Place in the <head>, after the three links -->
<script type="text/javascript" charset="utf-8">
  (function($) {

  })(jQuery);
</script>
COL;

  // dpm($filters);

 printf('<div class="clearfix">%s<div id="PortfolioFiltered" class="row">%s</div> </div>', $filter ,$items );


}


/**
 * slideshowcontent function
 *
 *  Content Slideshow
 *
 * @param init $limit
 * Item limit per Slide (default 4)
 * @param string $taxonomy
 * Slideshow content classification
 * @param string $order
 * Slideshow order (default DESC )
 * @return $build
 * @author Themebiotic <support@themebiotic.com>
 **/
function slideshowcontent($name = 'slideshow' ,$limit = '4', $taxonomy = '', $order = 'DESC'){

  if( empty($taxonomy) ) {
    drupal_set_message(t('An error occurred and processing did not complete. Slideshow Taxonomy empty'), 'error');
    return false ;
  }

  $type = "tbslideshow";
  $cat = taxonomy_get_term_by_name($taxonomy,'slide');
  $tid = "";
    foreach ($cat as $key => $value) {
      $tid = $value->tid ;
    }
  // $nodes = taxonomy_select_nodes($tax,false);
  if ( empty($tid) ) {
    drupal_set_message(t('No Slideshow item found, Please check your taxonomy'), 'warning');
    return false ;
  }

  $nodes = taxonomy_select_nodes($tid, false, $limit, array('t.sticky' => $order, 't.created' => $order));

  $output = "";
  foreach ($nodes as $key => $nid) {

    $node = node_load($nid);
    $body_field  = field_get_items('node', $node, 'body');
    $body_output = field_view_value('node', $node, 'body', $body_field[0] );
    $body = render($body_output);

    // $image = $node->field_tbportfolio_images['und'][0]['uri'];
    //
    // $image_field = field_get_items('node', $node, 'field_tbslideshow_image');

    // if($image_field) {
    //   $image_output = field_view_value('node', $node, 'field_tbslideshow_image', $image_field[0], array(
    //     'type' => 'image',
    //     'settings' => array(
    //       // 'image_style' => '940x530',
    //       // 'image_link' => 'file',
    //     ),
    //   ));
    // }

    $output .=  sprintf('<div class="slide">%s</div>',$body);

  }

  $prev =  sprintf('<a class="prev" id="%s_prev" href="#"> <i class="fsize24 iconfont-arrow-left-7"></i> <span class="element-invisible">prev</span></a>',$name);
  $next =  sprintf('<a class="next" id="%s_next" href="#"> <i class="fsize24 iconfont-arrow-right-2"></i> <span class="element-invisible">next</span></a>',$name);


  printf('<div class="slideshow_wrapper"><div id="%s" class="slideshow">%s</div> %s %s </div>',$name,$output,$prev,$next);

}

/**
 * @TODO
 *
 * [revslider description]
 * @param  string $name     [description]
 * @param  string $limit    [description]
 * @param  string $taxonomy [description]
 * @param  string $order    [description]
 * @return [type]           [description]
 */
function revslider($name = 'revslider' ,$limit = '4', $taxonomy = '', $order = 'DESC'){

  if( empty($taxonomy) ) {
    drupal_set_message(t('An error occurred and processing did not complete. Slideshow Taxonomy empty'), 'error');
    return false ;
  }

  $type = "tbslideshow";
  $cat = taxonomy_get_term_by_name($taxonomy,'slide');
  $tid = "";
    foreach ($cat as $key => $value) {
      $tid = $value->tid ;
    }
  // $nodes = taxonomy_select_nodes($tax,false);
  if ( empty($tid) ) {
    drupal_set_message(t('No Slideshow item found, Please check your taxonomy'), 'warning');
    return false ;
  }

  $nodes = taxonomy_select_nodes($tid, false, $limit, array('t.sticky' => $order, 't.created' => $order));

  $output = "";
  foreach ($nodes as $key => $nid) {

    $node = node_load($nid);
    $body_field  = field_get_items('node', $node, 'body');
    $body_output = field_view_value('node', $node, 'body', $body_field[0] );
    $body = render($body_output);

    // $image = $node->field_tbportfolio_images['und'][0]['uri'];
    //
    // $image_field = field_get_items('node', $node, 'field_tbslideshow_image');

    // if($image_field) {
    //   $image_output = field_view_value('node', $node, 'field_tbslideshow_image', $image_field[0], array(
    //     'type' => 'image',
    //     'settings' => array(
    //       // 'image_style' => '940x530',
    //       // 'image_link' => 'file',
    //     ),
    //   ));
    // }

    $output .=  sprintf('%s',$body);

  }

  printf('<div id="%s">%s</div>',$name,$output);

}


/**
 * @TODO
 *
 * function tb_flexslider
 *
 * @param  string $name     "Slider name"
 * @param  string $limit    "Slide display limit"
 * @param  string $taxonomy "Slide taxonomy"
 * @param  string $order    "Slide order DESC or ASC
 *
 * @return void             "Flexslider html content"
 */
function tb_flexslider($name = 'flexslider' ,$limit = '5', $taxonomy = '', $order = 'DESC'){

  if( empty($taxonomy) ) {
    drupal_set_message(t('An error occurred and processing did not complete. Slideshow Taxonomy empty'), 'error');
    return false ;
  }

  $type = "tbflexslider";
  $cat = taxonomy_get_term_by_name($taxonomy,'slideshow');
  $tid = "";
    foreach ($cat as $key => $value) {
      $tid = $value->tid ;
    }
  // $nodes = taxonomy_select_nodes($tax,false);
  if ( empty($tid) ) {
    drupal_set_message(t('No Slideshow item found, Please check your taxonomy'), 'warning');
    return false ;
  }

  $nodes = taxonomy_select_nodes($tid, false, $limit, array('t.sticky' => $order, 't.created' => $order));

  $output = "";
  foreach ($nodes as $key => $nid) {

    $node = node_load($nid);
    $body_field  = field_get_items('node', $node, 'body');
    $body_output = field_view_value('node', $node, 'body', $body_field[0] );

    $title = $node->title;
    $body = render($body_output);

    $image = $node->field_flex_image['und'][0]['uri'];
    //
    $image_field = field_get_items('node', $node, 'field_flex_image');
    $caption_field = field_get_items('node', $node, 'field_show_caption');
    $placement_field = field_get_items('node', $node, 'field_caption_placement');

    $caption   = $caption_field[0]['value'];
    $placement = $placement_field[0]['value'];

    if($image_field) {

      $image_output = field_view_value('node', $node, 'field_flex_image', $image_field[0], array(
        'type' => 'image',
        'settings' => array(
          'image_style' => 'flexslide',
          // 'image_link' => 'file',
        ),
      ));

      $thumb_url = image_style_url('flexthumb',$image_field[0]['uri']);

    }
    if ($caption) {
      $placement = ($placement) ? $placement : "left-bottom" ;
      $caption_data = sprintf('<div class="flex-caption %s"><h4 class="flex-title">%s</h4> %s</div>',$placement,$title,$body);
    }else {
      $caption_data = "";
    }

    $output .=  sprintf('<li data-thumb="%s">%s %s</li>',$thumb_url,$caption_data,render($image_output));

  }

  drupal_add_js(array(
    'tbflex' => array('myselector'=> ".".$name)
  ),'setting');

  printf('<div class="flexslider %s"><ul class="slides">%s</ul></div>',$name,$output);

}
