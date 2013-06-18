<?php
if ($action_type == 'create'):
  drupal_add_js(drupal_get_path('module', 'deal') . '/js/jquery.timer.js');
  drupal_add_js(drupal_get_path('module', 'deal') . '/js/deal-live-action.js');
?>
<div class="live-filters">
<span class="live-filters-label">Show:</span>
    <input type="checkbox" id="live_post" checked /> <label for="live_post">Posts</label>
    <input type="checkbox" id="live_comment" checked /> <label for="live_comment">Comments</label>
    <input type="checkbox"  id="live_vote" checked /> <label for="live_vote">Votes</label>
    <input type="hidden" id="live_timestamp" value="<?php echo $timestamp; ?>" />
</div>


    <div id="live_events" class="live-events">
      <div class="live-events-head">
            <div class="live-column column-time">Time</div>
            <div class="live-column column-user">User</div>
            <div class="live-column column-action">Action</div>
            <div class="live-column column-subject">Subject</div>
            <div class="live-column column-type">Type</div>
          </div>
      <div class="live-events-list">
      <?php echo $content; ?>
      </div>
    </div>
<?php 
elseif ($action_type == 'filter'):
  echo $content;
elseif ($action_type == 'update'):
  echo $content;
endif;