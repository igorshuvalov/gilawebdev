<?php 
  global $user; 
  $node = node_load($item->dnid);
?>
<div class="deal-page">
  <div class="deal-content">
  <?php if (time() > $item->date_expiry): ?>
    <span class="deal-expired"><?php echo t('EXPIRED'); ?></span><br/>
  <?php endif; ?>

    <div class="deal-photo">
    <?php 
      if ($item->photo): 

        $photo = file_load($item->photo);
        $image_item = array(
          'style_name' => 'deal_thumbnail',
          'path' => $photo->uri,
          'width' => '120',
          'height' => '90',
          'alt' => $item->title,
          'title' => $item->title,
        );
        echo '<a href="' . file_create_url($photo->uri) . '" target="_blank">' . theme('image_style', $image_item) . '</a>';
        
      else: 

        $options = array(
          'url' => 'http://www.' . $item->deal_url,
          'link' => 'http://www.' . $item->deal_url,
          'size' => 's',
          'image_options' => array(
          ),
          'url_options' => array(
            'attributes' => array(
              'class' => array(''),
              'title' => $item->title,
              'target' => '_blank',
            )
          )
        );

        echo theme_pagepeeker_image($options);
        
      endif;
    ?>
    </div>
    
    <div class="deal-metadata">
      <small class="deal-submitted">
        <?php 
          echo 'Submitted by ' . l($item->name, 'user/' . $item->uid) . ', ' . date('j M Y - g:i a', $item->date_posted);
        ?>
      </small>
      <div class="deal-url"><strong>URL:</strong> <a href="http://www.<?php echo $item->deal_url; ?>" target="_blank">http://www.<?php echo $item->deal_url; ?></a></div>

      <?php if ($item->coupon_code): ?>
        <div class="section-coupon-code">
          <strong>Coupon Code:</strong> 
	      <span class="coupon-code-value">
	          <button class="coupon-code" id="coupon-code-<?php echo $item->did; ?>" data-clipboard-text="<?php echo $item->coupon_code; ?>" title="Click to copy me." deal-url="<?php echo $item->deal_url; ?>"><?php echo $item->coupon_code; ?></button>
	          <span class="clicktocopy">(click to copy)</span>
	      </span>
        </div>
      <?php endif; ?>
      
      <p class="deal-description"><?php echo nl2br($item->description); ?></p>
      
      <div class="deal-representative"><strong>Store Representative:</strong> <?php if ($item->representative): ?>Yes<?php else: ?>No<?php endif; ?></div>

      <?php if ($item->date_start): ?>
      <div class="deal-start"><strong>Start Date:</strong> <?php echo date('Y-m-d', $item->date_start); ?></div>
      <?php endif; ?>

      <?php if ($item->date_expiry): ?>
      <div class="deal-expiry"><strong> Expiry Date:</strong> <?php echo date('Y-m-d', $item->date_expiry); ?></div>
      <?php endif; ?>

      <div class="deal-category"><strong>Category:</strong> <a href="<?php echo url('deal/category/' . deal_url_encode(deal_get_category_name($item->category))); ?>"><?php echo deal_get_category_name($item->category); ?></a></div>
      <div class="deal-location"><strong>Location:</strong> <a href="<?php echo url('deal/location/' . deal_url_encode(deal_get_location_name($item->location))); ?>"><?php echo deal_get_location_name($item->location); ?></a></div>
      <br/>
      <div class="deal-tags"><span class="icon-tag"></span><strong>Tags:</strong> 
        <?php 
          $tags = deal_get_tags_array($item->tags);
          foreach ($tags as $k => $tag) {
            if ($k != 0) {
              echo ' | ';
            }
            echo '<a href="' . url('deal/tag/' . deal_url_encode($tag)) . '">' . $tag . '</a>';
          }
        ?>
      </div>
    </div>

    <div class="vote-content-deal-<?php echo $item->did; ?>">
      <?php 
        $rate_state = deal_load_rate($item->did, 'deal');
      ?>
      <div class="vote-state" <?php if ($rate_state['voted_state']['rate'] === FALSE): ?>style="display:none;"<?php endif; ?>>
        <strong><?php echo t('Your Vote'); ?>:</strong>
        <div class="vote-result">
          <?php 
            if ($rate_state['voted_state']['rate'] == 1) {
              $rate = '+';
            }
            else {
              $rate = '-';
            }
          ?>
          <?php if ($rate_state['voted_state']['status'] == -1): ?>
            <?php echo t('You cancelled your vote.'); ?>
          <?php else: ?>
            <?php echo t('You voted "' . $rate . '" for this content') . ' ' . $rate_state['voted_state']['date_posted']; ?>
          <?php endif; ?>      
        </div>
        <div><button class="vote-cancel" oid="<?php echo $item->did; ?>" object="deal" <?php if ($rate_state['voted_state']['votable'] && $rate_state['voted_state']['status'] !== FALSE): ?>style="display: none;"<?php endif; ?>><?php echo t('Cancel your vote'); ?></button></div>
      </div>
      <div class="vote-action">
        <strong><?php echo t('Vote'); ?>:</strong>
        <button class="vote-plus" oid="<?php echo $item->did; ?>" object="deal">+ <?php echo $rate_state['plus']; ?></button> 
        <button class="vote-minus" oid="<?php echo $item->did; ?>"  object="deal">- <?php echo $rate_state['minus']; ?></button>
        <a class="view-votes" href="<?php echo url('deal/' . $item->did . '/votes/deal') ?>"><?php echo t('View Votes'); ?></a>
        <div class="votes-content" style="display: none;"></div>
      </div>
    </div>

  </div>

</div>
