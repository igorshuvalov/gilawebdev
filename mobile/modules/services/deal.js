drupalgap.services.deal = {
  'create':{
    'options':{
      'type':'post',
      'path':'deal.json',
      'success':function(deal){
        // TODO - good opportunity for a hook here...
        //drupalgap.deal_edit = {};
        //drupalgap.deal = {'nid':deal.nid};
      },
    },
    'call':function(options){
      try {
        var api_options = drupalgap_chain_callbacks(drupalgap.services.deal.create.options, options);
        api_options.data = drupalgap_deal_assemble_data(options);
        drupalgap.api.call(api_options);
      }
      catch (error) {
        navigator.notification.alert(
          error,
          function(){},
          'deal Create Error',
          'OK'
        );
      }
    },
  }, // <!-- create -->
  'retrieve':{
    'options':{
      'type':'get',
      'path':'deal/%nid.json',
      'success':function(deal){
        //drupalgap.deal = deal;
        // TODO - a good opportunity for a hook to come in
        // and modify deal.content if developer wants.
        switch(deal.type) {
          case 'deal':
            deal.content = '';
            var deal = deal.deal;
            deal.content = deal.description.replace('\r\n', '<BR>');
            break;
          case 'forum':
            deal.content = '';
            if (deal.body.length != 0) {
              deal.content = deal.body[deal.language][0].safe_value;
            }
            break;
          default:
            deal.content = '';
            if (deal.body.length != 0) {
              deal.content = deal.body[deal.language][0].safe_value;
            }
            break;
        }        
      },
    },
    'call':function(options){
      try {
        if (!options.nid) {
          navigator.notification.alert(
            'No deal id provided!',
            function(){},
            'deal Retrieve Error',
            'OK'
          );
          return;
        }
        var api_options = drupalgap_chain_callbacks(drupalgap.services.deal.retrieve.options, options);
        api_options.path = 'deal/' + options.nid + '.json';
        drupalgap.api.call(api_options);
      }
      catch (error) {
        navigator.notification.alert(
          error,
          function(){},
          'deal Retrieve Error',
          'OK'
        );
      }
    },
  }, // <!-- retrieve -->
  'update':{
    'options':{
      'type':'put',
      'path':'deal/%nid.json',
      'success':function(deal){
        //drupalgap.deal_edit = {};
        //drupalgap.deal = {'nid':deal.nid};
      },
    },
    'call':function(options){
      try {
        var api_options = drupalgap_chain_callbacks(drupalgap.services.deal.update.options, options);
        api_options.data = drupalgap_deal_assemble_data(options);
        api_options.path = 'deal/' + options.deal.nid + '.json';
        drupalgap.api.call(api_options);
      }
      catch (error) {
        navigator.notification.alert(
          error,
          function(){},
          'deal Update Error',
          'OK'
        );
      }
    },
  }, // <!-- update -->
  'del':{
    'options':{
      'type':'delete',
      'path':'deal/%nid.json',
      'success':function(result){
        if (result[0]) {
          //drupalgap.deal = {};
          //drupalgap.deal_edit = {};
        }
        else {
          alert('deal delete - error - ' + JSON.stringify(result));
        }
      },
    },
    'call':function(options){
      try {
        var api_options = drupalgap_chain_callbacks(drupalgap.services.deal.del.options, options);
        api_options.path = 'deal/' + options.nid + '.json';
        drupalgap.api.call(api_options);
      }
      catch (error) {
        navigator.notification.alert(
          error,
          function(){},
          'deal Delete Error',
          'OK'
        );
      }
    },
  }, // <!-- delete -->
};

/**
 * Assembles the data uri component for deal entity service resource calls.
 */
function drupalgap_deal_assemble_data(options) {
  try {
    if (drupalgap.settings.debug) {
      console.log(JSON.stringify(options));
    }
    var data = 'deal[language]=' + encodeURIComponent(drupalgap.settings.language);
    if (options.deal.type) {
      data += '&deal[type]=' + encodeURIComponent(options.deal.type);
    }
    if (options.deal.title) {
      data += '&deal[title]=' + encodeURIComponent(options.deal.title);
    }
    if (options.deal.body) {
      data += '&deal[body][' + drupalgap.settings.language + '][0][value]=' +
        encodeURIComponent(options.deal.body[drupalgap.settings.language][0].value);
    }
    if (drupalgap.settings.debug) {
      console.log(data);
      alert('drupalgap_deal_assemble_data');
    }
    return data;
  }
  catch (error) {
    alert('drupalgap_deal_assemble_data - ' + error);
  }
}

