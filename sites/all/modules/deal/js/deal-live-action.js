jQuery('document').ready(function() {
  var event_limit = 10;
  var liveUpdateInterval = function() {
    jQuery.ajax({
      url: '/live/update',
      type: 'POST',
      data: {
        post: jQuery('#live_post').attr('checked'),
        comment: jQuery('#live_comment').attr('checked'),
        vote: jQuery('#live_vote').attr('checked'),
        timestamp: jQuery('#live_timestamp').val(),
      },
      dataType: 'json',
      success: function(rsp) {
        jQuery('#live_events tbody').prepend(rsp.html);
        jQuery('#live_timestamp').val(rsp.timestamp);
        jQuery('#live_events tbody tr').each(function(i) {
          if (i >= event_limit) {
            jQuery(this).remove();
          }
        });
      }
    });
  };
  var liveUpdateTimer = window.setInterval(liveUpdateInterval, 10000);
  jQuery('#live_post, #live_comment, #live_vote').change(function() {
    window.clearInterval(liveUpdateTimer);
    jQuery.ajax({
      url: '/live/filter',
      type: 'POST',
      data: {
        post: jQuery('#live_post').attr('checked'),
        comment: jQuery('#live_comment').attr('checked'),
        vote: jQuery('#live_vote').attr('checked')
      },
      dataType: 'json',
      success: function(rsp) {
        jQuery('#live_events tbody').html(rsp.html);
        jQuery('#live_timestamp').val(rsp.timestamp);
        var liveUpdateTimer = window.setInterval(liveUpdateInterval, 10000);
      }
    });
  });
});