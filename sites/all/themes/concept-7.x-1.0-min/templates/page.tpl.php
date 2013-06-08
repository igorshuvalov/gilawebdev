<div class="<?php print  (theme_get_setting('layout_type') == "boxed") ? "container-boxed" : "container-wide" ;  ?>">

<header id="tbHeaderBox" role="banner" class="main-nav">

  <div id="tbHeadWrapper" class="wrapper">
    <div class="container">

      <div id="tbHeader" class="row">

        <div class="span<?php print ( theme_get_setting('brand_span') ) ? theme_get_setting('brand_span') : "6" ; ?>">
        <div id="brand-area" class="<?php print $custom_brand_classes; ?>">
          <?php if ($logo): ?>
            <a class="pull-left logo" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
              <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
            </a>
          <?php endif; ?>

          <?php if ($site_name): ?>
            <h1 id="site-name" class="<?php print $pullClass = ($logo) ? "pull-left" : "" ; ?>">
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" class="brand"><?php print $site_name; ?></a>

            <?php if ( $site_slogan ): ?>
              <small class="slogan"><?php print $site_slogan; ?></small>
            <?php endif; ?>

            </h1>
          <?php endif; ?>
        </div><!-- end .brand-area -->


        </div><!-- end .span<?php print ( theme_get_setting('brand_span') ) ? theme_get_setting('brand_span') : "6" ; ?> -->

        <div class="span<?php print ( theme_get_setting('mainmenu_span') ) ? theme_get_setting('mainmenu_span') : "6" ; ?>">
          <?php if ($primary_nav): ?>
            <?php print render($primary_nav); ?>
          <?php endif; ?>
        </div><!-- end .span<?php print ( theme_get_setting('mainmenu_span') ) ? theme_get_setting('mainmenu_span') : "6" ; ?>-->

      </div><!-- end #tbHeader -->


    </div><!-- end .ccontainer -->
  </div><!-- end #tbHeadWrapper -->

    <div class="container">

      <?php if ($page['header']): ?>
        <header role="banner" id="page-header">
          <?php print render($page['header']); ?>
        </header> <!-- /#header -->
      <?php endif; ?>

    </div><!-- end .container -->

</header>

<?php if ($page['info']): ?>
<div id="tbInfo" class="wrapper">
  <div class="container">
    <div class="row">
      <?php print render($page['info']); ?>
    </div>
  </div>
</div>
<?php endif; ?>


<?php


if ( !empty($page['raw_top']) ||
  !empty($messages) || !empty($page['headerbottom']) || !empty($page['sidebar_first']) || !empty($page['highlighted']) || !empty($title) || !empty($page['help']) || !empty($tabs['#secondary']) || !empty($tabs['#primary'])|| !empty($action_links) || !empty($page['content']) || !empty($page['sidebar_second']) ):

?>

<div id="tbContentBG">

<?php if ($page['raw_top']): ?>
<!-- Raw Top Content
================================================== -->
<div id="tbRawTop" class="wrapper">
  <?php print render($page['raw_top']); ?>
</div>
<?php endif; ?>


<div id="tbContent" class="paddingT30 container">

  <?php if($messages): ?>
  <!-- Messages
  ================================================== -->
  <div id="tb-messages" class="">
    <?php print $messages; ?>
  </div>
  <?php endif; ?>

  <?php if ($page['headerbottom']): ?>
  <div id="tbHeaderBottom" class="box marginB30">
    <div class="row">
      <?php print render($page['headerbottom']); ?>
    </div>
  </div>
  <?php endif; ?>

<?php 
  if (
    theme_get_setting('breadcrumb') 
    || $_GET['q'] == 'forum'
    || strpos($breadcrumb, '/forum')
    || @$node->type == 'forum' 
  ):
    if ($breadcrumb) : 
?>
<div class="row">
  <div class="span12">
  <?php if ($breadcrumb){ print $breadcrumb; }  ?>
  </div>
</div>
<?php 
    endif;
  endif;  
?>


  <div class="row">

    <?php if ($page['sidebar_first']): ?>
      <aside id="tbSidebarFirst" class="sidebar span3" role="complementary">
        <?php print render($page['sidebar_first']); ?>
      </aside>  <!-- /#sidebar-first -->
    <?php endif; ?>

    <section class="<?php print _bootstrap_content_span($columns); ?>">
      <?php if ($page['highlighted']): ?>
        <div class="highlighted hero-unit"><?php print render($page['highlighted']); ?></div>
      <?php endif; ?>
      <a id="main-content"></a>
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h1 class="page-header"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php if ($tabs): ?>
        <?php print render($tabs); ?>
      <?php endif; ?>
      <?php if ($page['help']): ?>
        <div class="well"><?php print render($page['help']); ?></div>
      <?php endif; ?>
      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']);  ?>
    </section>

    <?php if ($page['sidebar_second']): ?>
      <aside id="tbSidebarSecond" class="sidebar span3" role="complementary">
        <?php print render($page['sidebar_second']); ?>
      </aside>  <!-- /#sidebar-second -->
    <?php endif; ?>

  </div><!-- .row -->

</div><!-- end #tbContent -->
</div><!-- end #tbContentBG -->

<?php endif; ?>

<?php if ($page['raw']): ?>
<!-- Raw Content
================================================== -->
<div id="tbRaw" class="wrapper">
  <?php print render($page['raw']); ?>
</div>
<?php endif; ?>



<?php if ( $page['footer_top'] ): ?>
<!-- Footer Top
================================================== -->
<div id="tbFooterTop" class="wrapper">
  <div class="container">
    <div class="row">

      <?php if ($page['footer_top']): ?>
      <footer class="footer-top">
        <?php print render($page['footer_top']); ?>
      </footer>
      <?php endif; ?>

    </div>
  </div>
</div>
<?php endif; ?>

<?php if ( $page['footer'] || $page['footer_bottom'] ): ?>
<!-- Footer
================================================== -->
<div id="tbFooter" class="wrapper <?php // print  ($page['footer_top']) ? "" : "marginT50" ; ?>">
  <div class="container">
    <div class="row">

      <?php if ($page['footer']): ?>
      <footer class="footer">
        <?php print render($page['footer']); ?>
      </footer>
      <?php endif; ?>

      <?php if ($page['footer_bottom']): ?>
      <section class="clearfix">
        <div class="span12">
          <div class="marginTB10 divider"></div>
        </div>

        <footer class="footer-bottom">
          <?php print render($page['footer_bottom']); ?>
        </footer>
      </section>
      <?php endif; ?>

    </div>
  </div>
</div>
<?php endif; ?>

</div>

<a style="display:none;" href="<?php echo url('blackhole/'); ?>" rel="nofollow">Do NOT follow this link or you will be banned from the site!</a>