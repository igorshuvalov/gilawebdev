jQuery('document').ready(function() {
  var liveUpdateInterval = jQuery.timer(function() {
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
        jQuery('#live_events tbody').html(rsp.html);
        jQuery('#live_timestamp').val(rsp.timestamp);
        //jQuery('#live_events tbody tr.new').css({backgroundColor:'#ff0'}).animate({backgroundColor: '#fff'});
      }
    });
  });
  liveUpdateInterval.set({
    time: 60000,
    autostart: true
  });
  jQuery('#live_post, #live_comment, #live_vote').change(function() {
    liveUpdateInterval.stop();
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
        jQuery('#live_events .live-events-list').html(rsp.html);
        jQuery('#live_timestamp').val(rsp.timestamp);
        //jQuery('#live_events tbody tr.new').css({backgroundColor:'#ff0'}).animate({backgroundColor: '#fff'});
        liveUpdateInterval.play(true);
      }
    });
  });
});