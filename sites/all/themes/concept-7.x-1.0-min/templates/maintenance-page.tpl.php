<?php

/**
 * @file
 * Override of the default maintenance page.
 *
 * This is an override of the default maintenance page.
 *
 */
?><!DOCTYPE html>
<html lang="<?php print $language->language; ?>">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php // print $cond_scripts_top; ?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>


<div class="<?php print  (theme_get_setting('layout_type') == "boxed") ? "container-boxed" : "container-wide" ;  ?>">


<header id="tbHeaderBox" role="banner" >

    <div class="container">

      <div id="tbHeader" class="row">

        <div class="span12 centered">

          <?php if ($logo): ?>
            <a class="logo pull-left" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
              <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
            </a>
          <?php endif; ?>

          <?php if ($site_name): ?>
            <h1 id="site-name">
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" class="brand"><?php print $site_name; ?></a>

            <?php if ( $site_slogan ): ?>
              <small class="slogan"><?php print $site_slogan; ?></small>
            <?php endif; ?>

            </h1>
          <?php endif; ?>



        </div>


<!--         <div class="visible-desktop span12">
          <div class="marginTB5 divider"></div>
        </div> -->


    </div>



    </div>

</header>

<div id="tbContentBG">
<div id="tbContent" class="paddingT30 padding30 container">

  <?php if($messages): ?>
  <!-- Messages
  ================================================== -->
  <div id="tb-messages" class="">
    <?php print $messages; ?>
  </div>
  <?php endif; ?>

    <section class="span12">
      <a id="main-content"></a>
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h2 class="page-header"><?php print $title; ?></h2>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if ($tabs): ?>
        <?php print render($tabs); ?>
      <?php endif; ?>

      <?php print $content ?>
    </section>



</div><!-- end #tbContent -->
</div><!-- end #tbContentBG -->


</div>



</body>
</html>
