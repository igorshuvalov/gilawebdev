<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

<?php print render($content['field_tbportfolio_images']); ?>

<hr>

<div class="row-fluid">

  <header class="tbPortfolio-full-submitted hidden-phone txt-right span3">
    <?php if ($display_submitted): ?>
      <span class="submitted">
        <?php print $user_picture; ?>
        <?php print $submitted; ?>
      </span>
    <?php endif; ?>


    <footer>
      <?php
      print render($content['field_tbportfolio_client']);
      print render($content['field_tbportfolio_categories']);
      print render($content['field_tbportfolio_skills']);
      ?>
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

  <?php
    // Hide comments, tags, and links now so that we can render them later.
    hide( $content['comments'] );
    hide( $content['links'] );
    hide( $content['field_tags'] );

    hide( $content['field_tbportfolio_images'] );
    hide( $content['field_tbportfolio_project_url'] );
    hide( $content['field_tbportfolio_skills'] );
    hide( $content['field_tbportfolio_categories'] );
    hide( $content['field_tbportfolio_client'] );

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
