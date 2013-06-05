<ul>
<?php 
  foreach ($list as $id => $item) {
?>
  <li>
    <a href="<?php echo url('deal/category/' . deal_url_encode($item)); ?>"><?php echo $item; ?></a>
  </li>
<?php
  }
?>
</ul>