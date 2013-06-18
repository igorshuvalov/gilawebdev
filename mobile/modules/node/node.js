/**
 * Given a node, this determines if the current user has access to it. Returns
 * true if so, false otherwise. This function implementation is incomplete, use
 * with caution.
 */
function node_access(node) {
  try {
    if (drupalgap.settings.debug) {
      console.log('node_access()');
      console.log(JSON.stringify(arguments));
    }
    if (node.uid == drupalgap.user.uid) {
      return true;
    }
    else {
      return false;
    }
  }
  catch (error) {
    alert('node_access - ' + error);
  }
}

/**
 * Page call back for node/add.
 */
function node_add_page() {
  try {
    if (drupalgap.settings.debug) {
      console.log('node_add_page()');
    }
    var content = {};
    content['header'] = {'markup':'<h2>Create Content</h2>'};
    drupalgap.services.drupalgap_content.content_types_user_permissions.call({
        'async':false,
        'success':function(data){
          var items = [];
          $.each(data,function(type,permissions){
            if (permissions.create) {
              items.push(l(type, 'node/add/' + type));
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
    alert('node_add_page - ' + error);
  }
}

/**
 * Page call back function for node/add/[type].
 */
function node_add_page_by_type(type) {
  try {
    if (drupalgap.settings.debug) {
      console.log('node_add_page_by_type(' + type + ')');
    }
    return drupalgap_get_form('node_edit', {'type':type});
  }
  catch (error) {
    alert('node_add_page_by_type - ' + error);
  }
}

/**
 * The node edit form.
 */
function node_edit(node) {
  try {
    if (drupalgap.settings.debug) {
      console.log('node_edit()');
      console.log(JSON.stringify(arguments));
    }
    // Setup form defaults.
    // TODO - Always having to declare the default submit and validate
    //          function names is lame. Set it up to be automatic, then update
    //          all existing forms to inherit the automatic goodness.
    var form = {
      'id':'node_edit',
      'submit':['node_edit_form_submit'],
      'validate':['node_edit_form_validate'],
      'elements':{},
      'buttons':{},
      'entity_type':'node',
    };
    
    // Add the entity's core fields to the form.
    drupalgap_entity_add_core_fields_to_form('node', node.type, form, node);
    
    // Add the fields for this content type to the form.
    drupalgap_field_info_instances_add_to_form('node', node.type, form, node);
    
    if (node.type == 'deal') {
      var deal = node.deal;
      
      form.elements.deal_url = {
        'type':'textfield',
        'title':'Deal URL',
        'required':true,
        'default_value':deal.deal_url,
        'description':'Please enter the Website (URL) to access the Deal.',
      };
      form.elements.photo = {
        'type':'markup',
        'markup':'<label><strong>Deal Photo</strong>*</label>',
      };
      form.elements.photo_automatic = {
        'type':'checkbox',
        'title':'Option 1 - Make Automated Screenshot of Deal URL (Default)',
        'default_value':(deal.photo == 0 ? 1 : 0),
      };
      if (deal.photo_image != 0) {
        form.elements.photo_image = {
          'type':'markup',
          'markup':deal.photo_image,
        };
      }
      form.elements.photo_upload = {
        'type':'image',
        'value':'Option 2 - Upload Deal Photo',
        'description':'Upload an image (JPEG, PNG or GIF) under 500Kb.',
      };
      form.elements.coupon_code = {
        'type':'textfield',
        'title':'Coupon Code',
        'description':'If Coupon Code applies to the Deal, please enter the Coupon Code.',
        'default_value':deal.coupon_code,
      };
      form.elements.description = {
        'type':'textarea',
        'title':'Deal Description',
        'description':'Please enter a short Deal Description.',
        'required':true,
        'default_value':deal.description,
      };
      form.elements.representative = {
        'type':'checkbox',
        'title':'Store Representative',
        'description':'If you are a Store Representative, as defined in the Posting Guidelines, you must check this box.',
        'default_value':(deal.representative ? deal.representative : 0),
      };
      form.elements.date_start = {
        'type':'date',
        'title':'Deal Start Date',
        'description':'If the Deal starts on a specific date, please specify the Start Date. Format is YYYY-MM-DD.',
        'required':true,
        'default_value':deal.date_start,
      };
      form.elements.date_expiry = {
        'type':'date',
        'title':'Deal Expiry Date',
        'description':'If the Deal ends on a specific date, please specify the End Date. If you have entered a Start Date, the End Date must be after the Start Date. Format is YYYY-MM-DD.',
        'required':true,
        'default_value':deal.date_expiry,
      };
      form.elements.category = {
        'type':'select',
        'title':'Deal Category',
        'description':'Please select the best matching Deal Category.',
        'options':_deal_categories(),
        'required':true,
        'default_value':deal.category,
      };
      form.elements.location = {
        'type':'select',
        'title':'Deal Location',
        'description':'Please select the best matching Deal Location.',
        'options':_deal_locations(),
        'required':true,
        'default_value':deal.location,
      };
      form.elements.tags = {
        'type':'textfield',
        'title':'Deal Tags',
        'description':'Please enter tags to describe the Deal. Only alphanumeric characters and spaces (to separate multi-word tags) are permitted. Each tag must be separated by a comma.',
        'required':true,
        'default_value':deal.tags,
      };
      form.elements.disabled = {
        'type':'checkbox',
        'title':'Status',
        'description':'Check if this deal is disabled.',
        'default_value':deal.disabled,
      };
    }
    
    // Add submit to form.
    form.elements.submit = {
      'type':'submit',
      'value':'Save',
    };
    
    return form;
  }
  catch (error) {
    alert('node_edit - ' + error);
  }
}

/**
 * The node edit form's validation function.
 */
function node_edit_validate(form, form_state) {
  try {
    if (drupalgap.settings.debug) {
      console.log('node_edit_validate()');
      console.log(JSON.stringify(arguments));
    }
  }
  catch (error) {
    alert('node_edit_validate - ' + error);
  }
}

/**
 * The node edit form's submit function.
 */
function node_edit_submit(form, form_state) {
  try {
    if (drupalgap.settings.debug) {
      console.log('node_edit_submit()');
      console.log(JSON.stringify(arguments));
    }
    var node = drupalgap_entity_build_from_form_state(form, form_state);
    drupalgap_entity_form_submit(form, form_state, node);
  }
  catch (error) {
    alert('node_edit_submit - ' + error);
  }
}

/**
 * Loads a node object and returns it. Returns false if the node load fails.
 */
function node_load(nid) {
  try {
    if (drupalgap.settings.debug) {
      console.log('node_load()');
      console.log(JSON.stringify(arguments));
    }
    var node = false;
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
    alert('node_load - ' + error);
  }
}


/**
 * Implements hook_menu().
 */
function node_menu() {
  try {
    if (drupalgap.settings.debug) {
      console.log('node_menu()');
    }
    var items = {
      'node':{
        'title':'Content',
        'page_callback':'node_page',
        'pageshow':'node_page_pageshow',
      },
      'node/add':{
        'title':'Add content',
        'page_callback':'node_add_page',
      },
      'node/add/%':{
        'title':'Add content',
        'page_callback':'node_add_page_by_type',
        'page_arguments':[2],
      },
      'node/%':{
        'title':'Node',
        'page_callback':'node_page_view',
        'page_arguments':[1],
        'pageshow':'node_page_view_pageshow',
      },
      'node/%/view':{
        'title':'View',
        'type':'MENU_DEFAULT_LOCAL_TASK',
        'weight':-10,
      },
      'node/%/edit':{
        'title':'Edit',
        'page_callback':'drupalgap_get_form',
        'page_arguments':['node_edit', 1],
        'weight':0,
        'type':'MENU_LOCAL_TASK',
        'access_callback':'node_access',
        'access_arguments':[1],
      },
    };
    return items;
  }
  catch (error) {
    alert('node_menu - ' + error);
  }
}

/**
 * Page callback for node.
 */
function node_page() {
  try {
    if (drupalgap.settings.debug) {
      console.log('node_page()');
      console.log(JSON.stringify(arguments));
    }
    var content = {
      'create_content':{
        'theme':'button_link',
        'path':'node/add',
        'text':'Create Content',
      },
      'node_listing':{
        'theme':'jqm_item_list',
        'title':'Content List',
        'items':[],
        'attributes':{'id':'node_listing_items'},
      }
    };
    
    // Return the content.
    return content;
  }
  catch (error) {
    alert('node_page - ' + error);
  }
}

/**
 * The jQM pageshow callback for the node listing page.
 */
function node_page_pageshow() {
  try {
    if (drupalgap.settings.debug) {
      console.log('node_page_pageshow()');
    }
    // Grab some recent content and display it.
    drupalgap.views_datasource.call({
      'path':'drupalgap/views_datasource/drupalgap_content',
      'success':function(data) {
        // Extract the users into items, then drop them in the list.
        var items = [];
        $.each(data.nodes, function(index, object){
            items.push(l(object.node.title, 'node/' + object.node.nid));
        });
        drupalgap_item_list_populate("#node_listing_items", items);
      },
    });
  }
  catch (error) {
    alert('node_page_pageshow - ' + error);
  }
}

/**
 * Page callback for node/%.
 */
function node_page_view(node) {
  try {
    if (drupalgap.settings.debug) {
      console.log('node_page_view()');
      console.log(JSON.stringify(arguments));
    }
    if (node) {
      var build = {
        'theme':'node',
        'node':node, // TODO - is this line of code doing anything?
        'title':{'markup':node.title}, // TODO - this is a core field and should probably by fetched from entity.js
        'content':{'markup':node.content},
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
      alert('node_page_view - failed to load node (' + nid + ')');
    }
  }
  catch (error) {
    alert('node_page_view - ' + error);
  }
}

/**
 * jQM pageshow handler for node/% pages.
 */
function node_page_view_pageshow() {
  try {
    if (drupalgap.settings.debug) {
      console.log('node_page_view_pageshow()');
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
    alert('node_page_view_pageshow - ' + error);
  }
}

/**
 * Implements hook_theme().
 */
function node_theme() {
  try {
    if (drupalgap.settings.debug) {
      console.log('node_theme()');
    }
    return {
      'node':{
        'template':'node',
      },
    };
  }
  catch (error) {
    alert('node_theme - ' + error);
  }
}

/**
* Get category list for deal
* 
*/
function _deal_categories() {
  return [
    {'id':1, 'name':'Accessories'},
    {'id':2, 'name':'Automotive'},
    {'id':3, 'name':'Baby'},
    {'id':4, 'name':'Beauty'},
    {'id':5, 'name':'Books'},
    {'id':6, 'name':'Clothing'},
    {'id':7, 'name':'Electronics'},
    {'id':8, 'name':'Flowers'},
    {'id':9, 'name':'Food'},
    {'id':10, 'name':'Furniture'},
    {'id':11, 'name':'Gifts'},
    {'id':12, 'name':'Health'},
    {'id':13, 'name':'Home & Garden'},
    {'id':14, 'name':'Jewellery'},
    {'id':15, 'name':'Musical Instruments'},
    {'id':16, 'name':'Office Supplies'},
    {'id':17, 'name':'Party Supplies'},
    {'id':18, 'name':'Pets'},
    {'id':19, 'name':'Photography'},
    {'id':20, 'name':'Services'},
    {'id':21, 'name':'Shoes'},
    {'id':22, 'name':'Sporting Goods'},
    {'id':23, 'name':'Toys'},
    {'id':24, 'name':'Travel'}
  ];
}

/**
* Get location list for deal
* 
*/
function _deal_locations() {
  return [
    {'id':1, 'name':'Online Only'},
    {'id':2, 'name':'Jabodetabek (Jakarta, Bogor, Depok, Tangerang, Bekasi)'},
    {'id':3, 'name':'Surabaya'},
    {'id':4, 'name':'Bandung'},
    {'id':5, 'name':'Medan'},
    {'id':6, 'name':'Semarang'},
    {'id':7, 'name':'Yogyakarta'},
    {'id':8, 'name':'Palembang'},
    {'id':9, 'name':'Bandar Lampung'},
    {'id':10, 'name':'Banjarmasin'},
    {'id':11, 'name':'Pontianak'},
    {'id':12, 'name':'Balikpapan'},
    {'id':13, 'name':'Makassar'},
    {'id':14, 'name':'Ambon'},
    {'id':15, 'name':'Manado'},
    {'id':16, 'name':'Jambi'},
    {'id':17, 'name':'Padang'},
    {'id':18, 'name':'Papua'},
    {'id':19, 'name':'Papua Barat'},
    {'id':20, 'name':'Madura'},
    {'id':21, 'name':'Seluruh Indonesia'},
    {'id':22, 'name':'Batam'},
    {'id':23, 'name':'Bali'}
  ];
}