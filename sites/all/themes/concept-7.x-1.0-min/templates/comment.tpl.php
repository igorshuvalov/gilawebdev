<div class="forum-comment well <?php print $classes . ' ' . $zebra; ?>"<?php print $attributes; ?>>

   <div class="comment-avatar"><?php print $picture; ?></div>
   <div class="comment-body">
   <div class="comment-author"><?php print $submitted; ?> <span class="comment-permalink"><?php print $permalink; ?></span></div>
   <div class="comment-text cmtbox">
    <header>
      <?php // debug($variables) ;?>
      <?php if ($new): ?>
        <mark class="new label label-important"><?php print $new; ?></mark>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
    </header>

    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['links']);
      print render($content);
    ?>
	
    <?php if ($signature): ?>
      <div class="user-signature"><?php print $signature; ?></div>
    <?php endif; ?>
    </div>
	<div class="comment-links"><?php print render($content['links']); ?></div>
    </div>

</div> <!-- /.comment -->