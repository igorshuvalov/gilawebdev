    <?php 
    $node = node_load($item->dnid);
    
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

      echo '<a href="' . url('node/' . $node->nid) . '">' . theme('image_style', $image_item) . '</a>';
      
    else: 
      
      if (substr($item->deal_url, 0, 7) != 'http://' && substr($item->deal_url, 0, 8) != 'https://') {
        $item->deal_url = 'http://' . $item->deal_url;
      }
      $options = array(
        'url' => $item->deal_url,
        'link' => 'node/' . $node->nid,
        'size' => 's',
        'image_options' => array(
        ),
        'url_options' => array(
          'attributes' => array(
            'class' => array(''),
            'title' => $item->title,
          )
        )
      );

      echo theme_pagepeeker_image($options);
      
    endif; 
    ?>
    <h2>
      <a href="<?php echo url('node/' . $node->nid);?>">
        <?php echo $item->title ?>
      </a>
      <?php if (time() > $item->date_expiry): ?>
      <span class="deal-expired"><?php echo t('EXPIRED'); ?></span>
      <?php endif; ?>
    </h2>
    <small>
      <?php 
        echo 'Submitted by ' . l($item->name, 'user/' . $item->uid) . ', ' . date('j M Y - g:i a', $item->date_posted) . ', <a href="' . url('node/' . $node->nid) . '#comments">' . $node->comment_count . ' comment(s)</a>';
      ?>
    </small>
	
    <p class="description">
    <?php 
      $desc = $item->description;
      if (strlen($desc) <= 150) {
        echo $desc;
      }
      else {
        $sub_desc = substr($desc, 0, 150);
        echo substr($sub_desc, 0, strrpos($sub_desc, ' ')) . '... ' . '<a href="' . url('node/' . $node->nid) . '">' . t('Read More') . '</a>';
      }
    ?>
    </p>
	
    <div class="category">
      <strong><?php echo t('Category'); ?>:</strong>
      <a href="<?php echo url('deal/category/' . deal_url_encode(deal_get_category_name($item->category))); ?>"><?php echo deal_get_category_name($item->category); ?></a>
    </div>
	
    <div class="location">
      <strong><?php echo t('Location'); ?>:</strong>
      <a href="<?php echo url('deal/location/' . deal_url_encode(deal_get_location_name($item->location))); ?>"><?php echo deal_get_location_name($item->location); ?></a>
    </div>
	
	<br/>
	
    <div class="tag">
      <span class="icon-tag"></span><strong><?php echo t('Tags'); ?>:</strong>
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
	
    <div class="vote-content-<?php echo $item->did; ?>">
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
        <div><button class="vote-cancel" did="<?php echo $item->did; ?>" <?php if ($rate_state['voted_state']['votable'] && $rate_state['voted_state']['status'] !== FALSE): ?>style="display: none;"<?php endif; ?>><?php echo t('Cancel Your Vote'); ?></button></div>
      </div>
      <div class="vote-action">
        <strong><?php echo t('Vote'); ?>:</strong>
        <button class="vote-plus" did="<?php echo $item->did; ?>">+ <?php echo $rate_state['plus']; ?></button> 
        <button class="vote-minus" did="<?php echo $item->did; ?>">- <?php echo $rate_state['minus']; ?></button>
      </div>
    </div>
    
    <hr>