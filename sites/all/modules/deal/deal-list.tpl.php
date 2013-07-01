<script src="<?php echo url(drupal_get_path('module', 'deal')); ?>/js/deal-list.js"></script>

<?php
  if (!count($list)):
    echo t('No deals matching your search were found. Please try again soon.');
  else:
?>
<?php
  if (@$message):
    echo $message;
  endif;
?>
<?php 
  if (@$filter_options):
?>
<div class="filter-options">
  <?php
    $i = 0;
    foreach ($filter_options as $name => $link) {
      if ($i)
        echo ' ';
      echo "<a href='" . url($link) . "'>" . $name . "</a>";
      $i++;
    }
  ?>
</div>
<?php
  endif;
?>
<div class="content">

  <?php
  foreach ($list as $item):
  ?>
    <article class="node node-deals deal-list node-promoted node-teaser clearfix deal-list-<?php echo $item->did; ?>">
      <?php echo theme('deal_teaser', array('item' => $item)); ?>
    </article>
  <?php 
    endforeach;
  ?>
  
</div>

<div>
  <?php echo $pager; ?>
</div>

<?php endif; ?>