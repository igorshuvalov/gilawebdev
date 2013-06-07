<?php
if ($action_type == 'create'):
  drupal_add_js(drupal_get_path('module', 'deal') . '/js/jquery.timer.js');
  drupal_add_js(drupal_get_path('module', 'deal') . '/js/deal-live-action.js');
?>
    <input type="checkbox" id="live_post" checked /> Posts
    <input type="checkbox" id="live_comment" checked /> Comments
    <input type="checkbox"  id="live_vote" checked /> Votes
    <input type="hidden" id="live_timestamp" value="<?php echo $timestamp; ?>" />
    <BR><BR>
    <table id="live_events" width="100%">
      <thead>
        <th align="left">Time</th>
        <th align="left">User</th>
        <th >Action</th>
        <th align="left">Subject</th>
        <th align="left">Type</th>
      </thead>
      <tbody>
<?php
  echo $content;
?>
      </tbody>
    </table>
<?php 
elseif ($action_type == 'filter'):
  echo $content;
elseif ($action_type == 'update'):
  echo $content;
endif;