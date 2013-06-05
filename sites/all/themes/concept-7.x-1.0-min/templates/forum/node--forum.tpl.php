<div id="node-<?php print $node->nid; ?>" class="forum-node <?php print $classes; ?> clearfix"<?php print $attributes; ?>>


  <header>
    <?php print render($title_prefix); ?>
    <?php if (!$page && $title): ?>
      <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
  </header>

<div class="row-fluid">

  <?php if($user_picture): ?>
  <div class="hidden-phone span2">
    <?php if ($display_submitted): ?>
      <span class="submitted">
        <?php print $user_picture; ?>
      </span>
    <?php endif; ?>
  </div>
  <?php endif; ?>

  <div class="<?php print ($user_picture) ? "span9" : "span12" ; ?>">
    <?php if ($display_submitted): ?>
      <div class="submitted clearfix marginB10">
        <div class="visible-phone pull-left marginR10">
          <?php print $user_picture; ?>
        </div>
        <?php print $submitted; ?>
      </div>
    <?php endif; ?>
  <?php
    // Hide comments, tags, and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
    hide($content['field_tags']);
    hide( $content['taxonomy_forums'] );
    print render($content);
  ?>

  </div>
</div>

  <?php if (!empty($content['field_tags']) || !empty($content['links'])): ?>
    <footer>
      <?php print render($content['field_tags']); ?>
      <?php print render($content['links']); ?>
    </footer>
  <?php endif; ?>

  <hr>

  <?php print render($content['comments']); ?>

</div> <!-- /.node -->
