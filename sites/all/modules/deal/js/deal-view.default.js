jQuery(document).ready(function() {
  var clip = new ZeroClipboard(jQuery('.coupon-code'), {
    moviePath: "/sites/all/modules/deal/ZeroClipboard/ZeroClipboard.swf"
  });
  clip.on('complete', function(client, args) {
    window.open('http://' + jQuery('.coupon-code').attr('deal-url'), '_blank');
  });
  clip.on('noFlash', function(client) {
    jQuery('.coupon-code').click(function() {
      window.open('http://' + jQuery(this).attr('deal-url'), '_blank');
    });
	 jQuery('.clicktocopy').hide();
  });
  
  jQuery('.vote-plus').click(function() {
    var _this = this;
    jQuery.ajax({
      url: '/deal/vote',
      type: 'POST',
      data: {
        id: jQuery(_this).attr('oid'),
        type: 'plus',
        object: jQuery(_this).attr('object')
      },
      dataType: 'json',
      success: function(rsp) {
        switch(rsp.result) {
          case 'NO AUTHENTICATED':
            window.location.href = rsp.redirect;
            break;
          case 'FAILURE':
            alert('Your vote was not processed.');
            break;
          case 'SUCCESS':
            jQuery(_this).text(rsp.state.plus + ' +');
            jQuery(_this).next().text(rsp.state.minus + ' -');
            var voteContentClass = '.vote-content-' + jQuery(_this).attr('object') + '-' + jQuery(_this).attr('oid');
            var voteStateClass = voteContentClass + ' .vote-state';
            jQuery(voteStateClass + ' .vote-result').text('You voted "+" for this' + ' ' + rsp.state.voted_state.date_posted);
            jQuery(voteStateClass).fadeIn('fast');
            jQuery(voteStateClass + ' .vote-cancel').show();
            break;
          default:
            break;
        }
      }
    });
  });
  
  jQuery('.vote-minus').click(function() {
    var _this = this;
    jQuery.ajax({
      url: '/deal/vote',
      type: 'POST',
      data: {
        id: jQuery(_this).attr('oid'),
        type: 'minus',
        object: jQuery(_this).attr('object')
      },
      dataType: 'json',
      success: function(rsp) {
        switch(rsp.result) {
          case 'NO AUTHENTICATED':
            window.location.href = rsp.redirect;
            break;
          case 'FAILURE':
            alert('Your vote was not processed.');
            break;
          case 'SUCCESS':
            jQuery(_this).text(rsp.state.minus + ' -');
            jQuery(_this).prev().text(rsp.state.plus + ' +');
            var voteContentClass = '.vote-content-' + jQuery(_this).attr('object') + '-' + jQuery(_this).attr('oid');
            var voteStateClass = voteContentClass + ' .vote-state';
            jQuery(voteStateClass + ' .vote-result').text('You voted "-" for this content' + ' ' + rsp.state.voted_state.date_posted);
            jQuery(voteStateClass).fadeIn('fast');
            jQuery(voteStateClass + ' .vote-cancel').show();
            break;
          default:
            break;
        }
      }
    });
  });
  
  jQuery('.vote-cancel').click(function() {
    var _this = this;
    jQuery.ajax({
      url: '/deal/vote/cancel',
      type: 'POST',
      data: {
        id: jQuery(_this).attr('oid'),
        object: jQuery(_this).attr('object')
      },
      dataType: 'json',
      success: function(rsp) {
        switch(rsp.result) {
          case 'NO AUTHENTICATED':
            window.location.href = rsp.redirect;
            break;
          case 'FAILURE':
            alert('Your vote was not processed.');
            break;
          case 'SUCCESS':
            var voteContentClass = '.vote-content-' + jQuery(_this).attr('object') + '-' + jQuery(_this).attr('oid');
            jQuery(voteContentClass + ' .vote-minus').text(rsp.state.minus + ' -');
            jQuery(voteContentClass + ' .vote-plus').text(rsp.state.plus + ' +');
            jQuery(voteContentClass + ' .vote-state .vote-result').text('You cancelled your vote');
            jQuery(voteContentClass + ' .vote-state').fadeIn('fast');
            jQuery(voteContentClass + ' .vote-state .vote-cancel').hide();
            break;
          default:
            break;
        }
      }
    });
  });
  
});
