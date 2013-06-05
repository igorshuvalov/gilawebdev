jQuery(document).ready(function() {
  jQuery('.vote-plus').click(function() {
    var _this = this;
    jQuery.ajax({
      url: '/deal/vote',
      type: 'POST',
      data: {
        id: jQuery(_this).attr('did'),
        type: 'plus',
        object: 'deal'
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
            jQuery(_this).text('+ ' + rsp.state.plus);
            jQuery(_this).next().text('- ' + rsp.state.minus);
            var votecontentClass = '.vote-content-' + jQuery(_this).attr('did');
            jQuery(votecontentClass + ' .vote-state .vote-result').text('You voted "+" for this content' + ' ' + rsp.state.voted_state.date_posted);
            jQuery(votecontentClass + ' .vote-state').fadeIn('fast');
            jQuery(votecontentClass + ' .vote-state .vote-cancel').show();
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
        id: jQuery(_this).attr('did'),
        type: 'minus',
        object: 'deal'
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
            jQuery(_this).text('- ' + rsp.state.minus);
            jQuery(_this).prev().text('+ ' + rsp.state.plus);
            var votecontentClass = '.vote-content-' + jQuery(_this).attr('did');
            jQuery(votecontentClass + ' .vote-state .vote-result').text('You voted "-" for this content' + ' ' + rsp.state.voted_state.date_posted);
            jQuery(votecontentClass + ' .vote-state').fadeIn('fast');
            jQuery(votecontentClass + ' .vote-state .vote-cancel').show();
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
        id: jQuery(_this).attr('did'),
        object: 'deal'
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
            var votecontentClass = '.vote-content-' + jQuery(_this).attr('did');
            jQuery(votecontentClass + ' .vote-minus').text('- ' + rsp.state.minus);
            jQuery(votecontentClass + ' .vote-plus').text('+ ' + rsp.state.plus);
            jQuery(votecontentClass + ' .vote-state .vote-result').text('You cancelled your vote');
            jQuery(votecontentClass + ' .vote-state').fadeIn('fast');
            jQuery(votecontentClass + ' .vote-state .vote-cancel').hide();
            break;
          default:
            break;
        }
      }
    });
  });
  
});