/**
 * Given a deal, this determines if the current user has access to it. Returns
 * true if so, false otherwise. This function implementation is incomplete, use
 * with caution.
 */
function deal_access(deal) {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_access()');
      console.log(JSON.stringify(arguments));
    }
    if (deal.uid == drupalgap.user.uid) {
      return true;
    }
    else {
      return false;
    }
  }
  catch (error) {
    alert('deal_access - ' + error);
  }
}

/**
 * Page call back for deal/add.
 */
function deal_add_page() {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_add_page()');
    }
    var content = {};
    content['header'] = {'markup':'<h2>Submit Deal</h2>'};
    drupalgap.services.drupalgap_content.content_types_user_permissions.call({
        'async':false,
        'success':function(data){
          var items = [];
          $.each(data,function(type,permissions){
            if (permissions.create) {
              items.push(l(type, 'deal/add/' + type));
            }
          });
          if (items.length > 0) {
            content['content_type_list'] = {'theme':'jqm_item_list', 'items':items};
          }
          else {
            content['content_type_list'] = '<p>Sorry, you do not have permission to add content!</p>';
          }
        },
    });
    return content;
  }
  catch (error) {
    alert('deal_add_page - ' + error);
  }
}

/**
 * Page call back function for deal/add/[type].
 */
function deal_add_page_by_type(type) {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_add_page_by_type(' + type + ')');
    }
    return drupalgap_get_form('deal_edit', {'type':type});
  }
  catch (error) {
    alert('deal_add_page_by_type - ' + error);
  }
}

/**
 * The deal edit form.
 */
function deal_edit(deal) {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_edit()');
      console.log(JSON.stringify(arguments));
    }
    // Setup form defaults.
    // TODO - Always having to declare the default submit and validate
    //          function names is lame. Set it up to be automatic, then update
    //          all existing forms to inherit the automatic goodness.
    var form = {
      'id':'deal_edit',
      'submit':['deal_edit_form_submit'],
      'validate':['deal_edit_form_validate'],
      'elements':{},
      'buttons':{},
      'entity_type':'deal',
    };
    
    // Add the entity's core fields to the form.
    drupalgap_entity_add_core_fields_to_form('deal', deal.type, form, deal);
    
    // Add the fields for this content type to the form.
    drupalgap_field_info_instances_add_to_form('deal', deal.type, form, deal);
    
    // Add submit to form.
    form.elements.submit = {
      'type':'submit',
      'value':'Save',
    };
    
    // Add cancel button to form.
    form.buttons['cancel'] = {
      'title':'Cancel',
    };
    
    // Add delete button to form if we're editing a deal.
    if (deal && deal.nid) {
      form.buttons['delete'] = {
        'title':'Delete',
      };
    }
    
    return form;
  }
  catch (error) {
    alert('deal_edit - ' + error);
  }
}

/**
 * The deal edit form's validation function.
 */
function deal_edit_validate(form, form_state) {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_edit_validate()');
      console.log(JSON.stringify(arguments));
    }
  }
  catch (error) {
    alert('deal_edit_validate - ' + error);
  }
}

/**
 * The deal edit form's submit function.
 */
function deal_edit_submit(form, form_state) {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_edit_submit()');
      console.log(JSON.stringify(arguments));
    }
    var deal = drupalgap_entity_build_from_form_state(form, form_state);
    drupalgap_entity_form_submit(form, form_state, deal);
  }
  catch (error) {
    alert('deal_edit_submit - ' + error);
  }
}

/**
 * Loads a deal object and returns it. Returns false if the deal load fails.
 */
function deal_load(nid) {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_load()');
      console.log(JSON.stringify(arguments));
    }
    var deal = false;
    drupalgap.services.node.retrieve.call({
      'nid':nid,
      'async':false,
      'success':function(data){
        node = data;
      }
    });
    return node;
  }
  catch (error) {
    alert('deal_load - ' + error);
  }
}


/**
 * Implements hook_menu().
 */
function deal_menu() {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_menu()');
    }
    var items = {
      'deal':{
        'title':'Deals',
        'page_callback':'deal_page_list',
        'page_arguments':['deal_listing_items'],
        'pageshow':'deal_page',
      },
      'deal/today_best':{
        'title':'Today\'s Best Deals',
        'page_callback':'deal_page_list',
        'page_arguments':['deal_today_best_items'],
        'pageshow':'deal_today_best',
      },
      'deal/new':{
        'title':'New Deals',
        'page_callback':'deal_page_list',
        'page_arguments':['deal_new_items'],
        'pageshow':'deal_new',
      },
      'deal/popular':{
        'title':'Popular Deals',
        'page_callback':'deal_page_list',
        'page_arguments':['deal_popular_items'],
        'pageshow':'deal_popular',
      },
      'deal/category_items':{
        'title':'Deal Categories',
        'page_callback':'deal_page_list',
        'page_arguments':['deal_category_items_items'],
        'pageshow':'deal_category_items',
      },
      'deal/location_items':{
        'title':'Deal Locations',
        'page_callback':'deal_page_list',
        'page_arguments':['deal_location_items_items'],
        'pageshow':'deal_location_items',
      },
      'deal_category/%':{
        'title':'Deal Items for Specified Category',
        'page_callback':'deal_page_list',
        'page_arguments':['deal_category_items_by_category'],
        'pageshow':'deal_items_by_category',
      },
      'deal/location_items':{
        'title':'Deal Locations',
        'page_callback':'deal_page_list',
        'page_arguments':['deal_location_items_items'],
        'pageshow':'deal_location_items',
      },
      'deal_location/%':{
        'title':'Deal Items for Specified Location',
        'page_callback':'deal_page_list',
        'page_arguments':['deal_location_items_by_location'],
        'pageshow':'deal_items_by_location',
      },
      'deal/add':{
        'title':'Add content',
        'page_callback':'deal_add_page',
      },
      'deal/add/%':{
        'title':'Add content',
        'page_callback':'deal_add_page_by_type',
        'page_arguments':[2],
      },
      'deal/%':{
        'title':'deal',
        'page_callback':'deal_page_view',
        'page_arguments':[1],
        'pageshow':'deal_page_view_pageshow',
      },
      'deal/%/view':{
        'title':'View',
        'type':'MENU_DEFAULT_LOCAL_TASK',
        'weight':-10,
      },
      'deal/%/edit':{
        'title':'Edit',
        'page_callback':'drupalgap_get_form',
        'page_arguments':['deal_edit', 1],
        'weight':0,
        'type':'MENU_LOCAL_TASK',
        'access_callback':'deal_access',
        'access_arguments':[1],
      },
    };
    return items;
  }
  catch (error) {
    alert('deal_menu - ' + error);
  }
}

/**
 * Show deal list
 */
function deal_page_list(content_id) {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_page_list()');
      console.log(JSON.stringify(arguments));
    }
    var content = {
      'deal_listing':{
        'theme':'jqm_item_list',
        'title':'Deal Page',
        'items':[],
        'attributes':{'id':content_id},
      }
    };
    
    // Return the content.
    return content;
  }
  catch (error) {
    alert('deal_page_list - ' + error);
  }
}

/**
 * Page callback for deal.
 */
function deal_page() {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_page()');
      console.log(JSON.stringify(arguments));
    }
    var items = [];
    items.push(l('Today\'s Best Deals', 'deal/today_best'));
    items.push(l('New Deals', 'deal/new'));
    items.push(l('Popular Deals', 'deal/popular'));
    items.push(l('Deals by Category', 'deal/category_items'));
    items.push(l('Deals by Location', 'deal/location_items'));
    drupalgap_item_list_populate("#deal_listing_items", items);
  }
  catch (error) {
    alert('deal_page - ' + error);
  }
}

/**
 * The jQM pageshow callback for today's best deal listing page.
 */
function deal_today_best() {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_today_best()');
    }
    drupalgap.views_datasource.call({
      'path':'drupalgap/drupalgap_deal/today_best',
      'type':'post',
      'success':function(data) {
        var items = [];
        $.each(data, function(index, object){
            items.push(l(object.title, 'node/' + object.dnid));
        });
        drupalgap_item_list_populate("#deal_today_best_items", items);
      },
    });
  }
  catch (error) {
    alert('deal_today_best - ' + error);
  }
}

/**
 * The jQM pageshow callback for new deal listing page.
 */
function deal_new() {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_new()');
    }
    drupalgap.views_datasource.call({
      'path':'drupalgap/drupalgap_deal/new',
      'type':'post',
      'success':function(data) {
        var items = [];
        $.each(data, function(index, object){
            items.push(l(object.title, 'node/' + object.dnid));
        });
        drupalgap_item_list_populate("#deal_new_items", items);
      },
    });
  }
  catch (error) {
    alert('deal_new - ' + error);
  }
}

/**
 * The jQM pageshow callback for popular deal listing page.
 */
function deal_popular() {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_popular()');
    }
    drupalgap.views_datasource.call({
      'path':'drupalgap/drupalgap_deal/popular',
      'type':'post',
      'success':function(data) {
        var items = [];
        $.each(data, function(index, object){
            items.push(l(object.title, 'node/' + object.dnid));
        });
        drupalgap_item_list_populate("#deal_popular_items", items);
      },
    });
  }
  catch (error) {
    alert('deal_popular - ' + error);
  }
}

/**
 * The jQM pageshow callback for deal categories page.
 */
function deal_category_items() {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_category_items()');
    }
    drupalgap.views_datasource.call({
      'path':'drupalgap/drupalgap_deal/category_items',
      'type':'post',
      'success':function(data) {
        var items = [];
        $.each(data, function(index, object){
            items.push(l(object.name, 'deal_category/' + object.id));
        });
        drupalgap_item_list_populate("#deal_category_items_items", items);
      },
    });
  }
  catch (error) {
    alert('deal_category_items - ' + error);
  }
}

/**
 * The jQM pageshow callback for deal locations page.
 */
function deal_location_items() {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_location_items()');
    }
    drupalgap.views_datasource.call({
      'path':'drupalgap/drupalgap_deal/location_items',
      'type':'post',
      'success':function(data) {
        var items = [];
        $.each(data, function(index, object){
            items.push(l(object.name, 'deal_location/' + object.id));
        });
        drupalgap_item_list_populate("#deal_location_items_items", items);
      },
    });
  }
  catch (error) {
    alert('deal_location_items - ' + error);
  }
}

/**
 * The jQM pageshow callback for deal items by specified category.
 */
function deal_items_by_category() {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_items_by_category()');
    }
    drupalgap.views_datasource.call({
      'path':'drupalgap/drupalgap_deal/category/' + arg(1),
      'type':'post',
      'success':function(data) {
        var items = [];
        $.each(data, function(index, object){
            items.push(l(object.title, 'node/' + object.dnid));
        });
        drupalgap_item_list_populate("#deal_category_items_by_category", items);
      },
    });
  }
  catch (error) {
    alert('deal_items_by_category - ' + error);
  }
}

/**
 * The jQM pageshow callback for deal items by specified location.
 */
function deal_items_by_location() {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_items_by_location()');
    }
    drupalgap.views_datasource.call({
      'path':'drupalgap/drupalgap_deal/location/' + arg(1),
      'type':'post',
      'success':function(data) {
        var items = [];
        $.each(data, function(index, object){
            items.push(l(object.title, 'node/' + object.dnid));
        });
        drupalgap_item_list_populate("#deal_location_items_by_location", items);
      },
    });
  }
  catch (error) {
    alert('deal_items_by_location - ' + error);
  }
}

/**
 * Page callback for deal/%.
 */
function deal_page_view(node) {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_page_view()');
      console.log(JSON.stringify(arguments));
    }
    if (node) {
      var build = {
        'theme':'deal',
        'deal':deal, // TODO - is this line of code doing anything?
        'title':{'markup':node.title}, // TODO - this is a core field and should probably by fetched from entity.js
        'content':{'markup':node.deal.description},
      };
      // If the comments are hidden, do nothing.
      if (node.comment == 0) { }
      // If the comments are closed or open, show the comments.
      else if (node.comment == 1 || node.comment == 2) {
        
        // Build an empty list for the comments
        build.comments = {
          'theme':'jqm_item_list',
          'title':'Comments',
          'items':[],
          'attributes':{'id':'comment_listing_items'},
        };
        
        // If the comments are open, show the comment form.
        if (node.comment == 2) {
          build.comments_form = {
            'markup':
              '<h2>Add comment</h2>' +
                drupalgap_get_form('comment_edit', {'nid':node.nid})
          };
        }
      }
      
      return build;
    }
    else {
      alert('deal_page_view - failed to load deal (' + nid + ')');
    }
  }
  catch (error) {
    alert('deal_page_view - ' + error);
  }
}

/**
 * jQM pageshow handler for deal/% pages.
 */
function deal_page_view_pageshow() {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_page_view_pageshow()');
    }
    // Grab some recent comments and display it.
    if ($('#comment_listing_items')) {
      drupalgap.views_datasource.call({
        'path':'drupalgap/views_datasource/drupalgap_comments/' + arg(1),
        'success':function(data) {
          // Extract the comments into items, then drop them in the list.
          var items = [];
          $.each(data.comments, function(index, object){
              var html = '';
              if (drupalgap_user_access({'permission':'administer comments'})) {
                html += l('Edit', 'comment/' + object.comment.cid + '/edit');
              }
              html += object.comment.created + "<br />" +
                'Author: ' + object.comment.name + "<br />"+ 
                'Subject: ' + object.comment.subject + "<br />" +
                'Comment:<br />' + object.comment.comment_body + "<hr />"; 
              items.push(html);
          });
          drupalgap_item_list_populate("#comment_listing_items", items);
        },
      });
    }
  }
  catch (error) {
    alert('deal_page_view_pageshow - ' + error);
  }
}

/**
 * Implements hook_theme().
 */
function deal_theme() {
  try {
    if (drupalgap.settings.debug) {
      console.log('deal_theme()');
    }
    return {
      'deal':{
        'template':'deal',
      },
    };
  }
  catch (error) {
    alert('deal_theme - ' + error);
  }
}

