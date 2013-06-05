<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($content['field_tbblog_images']); ?>

<div class="row-fluid">

  <header class="hidden-phone <?php echo ($user_picture) ? "marginT25" : "marginT75" ; ?> txt-right span3">
    <?php if ($display_submitted): ?>
      <span class="submitted">
        <?php print $user_picture; ?>
        <?php print $submitted; ?>
      </span>
    <?php endif; ?>


    <footer>
      <?php print render($content['field_tags']); ?>
    </footer>


  </header>



  <div class="span9">

    <header>
      <?php print render($title_prefix); ?>
      <?php if (!$page && $title): ?>
        <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
    </header>

    <?php if( theme_get_setting('layout_mode') == "responsive"  ): ?>
    <div class="visible-phone">
      <?php if ($display_submitted): ?>
      <em>Submitted by <?php print $name; ?>  </em>
      <em><?php print format_date($created); ?></em>
      <?php print render($content['field_tags']); ?>
      <?php endif; ?>
    </div>
  <?php endif; ?>

  <?php
    // Hide comments, tags, and links now so that we can render them later.
    hide( $content['comments'] );
    hide( $content['links'] );
    hide( $content['field_tags'] );
    hide( $content['field_tbblog_images'] );
    print render($content);
  ?>

  <?php if (!empty($content['links'])): ?>
    <footer>
      <?php print render($content['links']); ?>
    </footer>
  <?php endif; ?>


  </div>
</div>


<hr>

</article> <!-- /.node -->
