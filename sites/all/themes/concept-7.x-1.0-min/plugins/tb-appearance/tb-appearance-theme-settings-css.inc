<?php
include_once(dirname(__FILE__) . '/tb-appearance-helper.inc');

$elements = _get_appearance_css();

if ($elements) {

  if (isset($elements['#txt'])) {
    # code...

      /**
       * Text CSS
       * @param  $elements['#txt']
       *         selector => css selector
       *         text     => text color
       *         link     => link color
       *         hover    => link hover color
       */
      foreach ($elements['#txt'] as $key => $value) {

        $selector = $value['selector'];
        $color = $value['text'];
        $link = $value['link'];
        $hover = $value['hover'];


        $CSS .= <<< CSS
/* {$key} - text css */
{$selector} { color:{$color}; }
{$selector} a:not(.btn) { color:{$link}; }
{$selector} a:not(.btn):hover { color:{$hover}; }\n
CSS;

      }
  } // if end


  if (isset($elements['#bg'])) {

      /**
       * Background CSS
       * @param $element['#bg']
       *        selector     => css selector
       *        type         => color, gradient, pattern, custom
       *          color      =>
       *            solid    => background solid color
       *          gradient   =>
       *            top      => background top gradident color
       *            bottom   => background bottom graident color
       *          pattern    =>
       *            path     => background pattern file path
       *          custom     =>
       *            selector => css selector
       *            behave   => background Image behavior
       *            uri      => image path "public://"
       *            fid      => managed file fid
       */
      foreach ($elements['#bg'] as $key => $value) {

        if ($key=="color") {
          # code...
            foreach ($value as $k => $v) {
              $selector = $v['selector'];
              $color    = $v['solid'];
              $opacity  = $v['opacity'];

              $rgb  = _set_rgb($color); /* Color Fallback */
              $rgba = _set_rgba($color,$opacity);

              if($k=="comments") {
                $selector .= " .well";
              }

              $CSS .= <<< CSS
/* {$k} - background css ({$key}) */
{$selector} { background-color:{$rgb}; /* Color Fallback */ background-color:{$rgba}; }\n
CSS;
            }
        }



        if ($key=="gradient") {

            foreach ($value as $k => $v) {
              $selector = $v['selector'];
              $top      = $v['top'];
              $bottom   = $v['bottom'];

              if($k=="comments") {
                $selector .= " .well";
              }

              $CSS .= <<< CSS
      /* {$k} - background css ({$key}) */
{$selector} {
  background: -moz-linear-gradient({$top}, {$bottom});
  background: -ms-linear-gradient({$top}, {$bottom});
  background: -webkit-gradient(linear, left top, left bottom, color-stop(0%, {$top}), color-stop(100%, {$bottom}));
  background: -webkit-linear-gradient({$top}, {$bottom});
  background: -o-linear-gradient({$top}, {$bottom});
  filter: progid:DXImageTransform.Microsoft.gradient(startColorstr='{$top}', endColorstr='{$bottom}')progid:DXImageTransform.Microsoft.Alpha(Opacity=50);
  -ms-filter: "progid:DXImageTransform.Microsoft.gradient(startColorstr='{$top}', endColorstr='{$bottom}')progid:DXImageTransform.Microsoft.Alpha(Opacity=50)";
  background: linear-gradient({$top}, {$bottom});
}\n
CSS;
            }


        } // Gradient end


        if ($key=="pattern") {

          foreach ($value as $k => $v) {
            if (!$v['path']) {
              return false;
            }

            $selector = $v['selector'];
            $path      = $v['path'];
            $bg_img = $base_path . drupal_get_path('theme', 'bootstrap') . '/assets/images/patterns/' . $path;
            $bg_behave = 'top left repeat';

            if($k=="comments") {
              $selector .= " .well";
            }

            $CSS .= <<<CSS
/* {$k} - background css ({$key}) */
{$selector} {
  background: url('{$bg_img}') {$bg_behave};
}
CSS;
          }
        } // Pattern end


        if ($key=="custom") {

          foreach ($value as $k => $v) {

            $selector = $v['selector'];
            $behave   = $v['behave'];
            if($k=="comments") {
              $selector .= " .well";
            }
            if($behave =='repeat') {
              $behave='repeat left top';
            }elseif ($behave=='cover') {
              $behave='no-repeat center center scroll';
            }
            $uri   = $v['uri'];
            $fid   = $v['fid'];
            $path   = "";
            if ($uri && !$fid) {
              $path = file_create_url("public://".$uri);
            }elseif ($fid && !$uri) {
              $custom_fid = file_load( $fid );
              $path = file_create_url( $custom_fid->uri );
            }else{
              $message = t("Concept : Theme settings > Appearance > ".strtoupper($k)." > Background style <br/>
                An error occurred and processing did not complete. Please check your Custom Background file <br/>
                <em>Path and Uploader can be defined at the same time. Please note that you can use only one</em>
              ");
              drupal_set_message($message, 'error');
              break;
            }

            $CSS .= <<<CSS
/* {$k} - background css ({$key}) */
{$selector} {
  background: url('{$path}') {$behave};
}
CSS;
        }

        }// cutom end

      } // end Background CSS foreach
  }// if $elements['#bg'] end


  if (isset($elements['#htag'])){

      /**
       * HTag CSS
       * @param  $elements['#htag']
       *         selector   => css selector
       *         h1 to h6   => text color
       *         h1l to h6l => link color
       *         h1h to h6h => link hover color
       */
      foreach ($elements['#htag'] as $key => $value) {

        $selector = $value['selector'];

        if(isset( $value['blocktitle']  )) {
          $val = $value['blocktitle'];
          $CSS .= <<< CSS
{$selector} h3.block-title { color: {$val}; }\n
CSS;
        }

        if(isset( $value['pagetitle']  )) {
          $val = $value['pagetitle'];
          $CSS .= <<< CSS
{$selector} h1.page-title { color: {$val}; }
{$selector} h1.page-header { color: {$val}; }\n
CSS;
        }

        if(isset( $value['border']  )) {
          $val = $value['border'];

          if($k=="comments") {
          $CSS .= <<< CSS
{$selector} .well { border-color: {$val}; }
{$selector} .indented { border-color: {$val}; }
CSS;
          }

          $CSS .= <<< CSS
{$selector} { border-color: {$val}; }
{$selector} h1.page-title { border-color: {$val}; }
{$selector} h1.page-header { border-color: {$val}; }
{$selector} .divider { border-bottom-color: {$val}; }
{$selector} .line:after { border-color: {$val}; }
{$selector} .menu li { border-bottom-color: {$val}; }
{$selector} hr { border-top-color: {$val}; border-bottom-color: {$val}; }
{$selector} .thumbnail { border-color: {$val}; }
{$selector} .nav-tabs { border-bottom-color: {$val}; }\n
CSS;
        }


        $i= 1;
        do {
          // ${'h'.$i} = $value['h'.$i];
          // ${'h'.$i.'l'} = $value['h'.$i.'l'];
          // ${'h'.$i.'h'} = $value['h'.$i.'h'];

          if(isset( $value['h'.$i]  )) {
            $tag = "h".$i;
            $val = $value['h'.$i];
            $CSS .= <<< CSS
{$selector} {$tag} { color: {$val}; }\n
CSS;
          }

          if(isset( $value['h'.$i.'l']  )) {
            $tag = "h".$i;
            $val = $value['h'.$i.'l'];
            $CSS .= <<< CSS
{$selector} {$tag} a { color: {$val}; }\n
CSS;
          }

          if(isset( $value['h'.$i.'h']  )) {
            $tag = "h".$i;
            $val = $value['h'.$i.'h'];
            $CSS .= <<< CSS
{$selector} {$tag} a:hover { color: {$val}; }\n
CSS;
          }


          $i++;
        } while ( $i <= 6);

      }


  }

  if (isset($elements['#menu'])){

    foreach ($elements['#menu'] as $key => $value) {

        $selector = $value['selector'];
        $link = $value['link'];
        $hover = $value['hover'];
        $hoverbg = $value['hoverbg'];
        $active = $value['active'];
        $activebg = $value['activebg'];
        $activehover = $value['activehover'];


        $CSS .= <<< CSS
/* {$key} - custom css */
#tbHeaderBox {$selector} > li > a { color:{$link}; }
#tbHeaderBox {$selector} > li > a:hover { color:{$hover}; background-color:{$hoverbg}; }
#tbHeaderBox {$selector} > li.open .dropdown-toggle,
#tbHeaderBox {$selector} li > a.active { color:{$active}; background-color:{$activebg}; }

#tbHeaderBox {$selector} > li.open .dropdown-toggle:hover,
#tbHeaderBox {$selector} > li > a.active:hover { color: {$activehover}; }

#tbHeaderBox {$selector} .dropdown-menu > li > a:hover,
#tbHeaderBox {$selector} .dropdown-menu > li > a:focus,
#tbHeaderBox {$selector} .dropdown-submenu:hover > a,
#tbHeaderBox {$selector} .dropdown-submenu:focus > a {
  color: {$active};
  background: {$activebg};
}\n
CSS;

    }

  } // end if


}// if $elements end
