/**
 * Given a form element name and the form_id, this generates an html id
 * attribute value to be used in the DOM.
 */
function drupalgap_form_get_element_id(name, form_id) {
  try {
    if (name == null || name == '') { return ''; }
    name =
      'edit-' +
      form_id.toLowerCase().replace(/_/g, '-') + '-' +
      name.toLowerCase().replace(/_/g,'-');
    if (drupalgap.settings.debug) { console.log(name); }
    return name;
  }
  catch (error) {
    alert('drupalgap_form_get_element_id - ' + error);
  }
}

/**
 * Given a drupalgap form, this renders the form.
 */
// TODO - we may possibly colliding html element ids!!! For example, I think the
// node edit page gets an id of "node_edit" and possibly so does the node
// edit form, which also may get an id of "node_edit". We may want to prefix
// both the template page and form ids with prefixes, e.g. drupalgap_page_*
// and drupalgap_form_*, but adding these prefixes could get annoying for
// css selectors used in jQuery and CSS. What to do? But does the form even
// get an element and an id, I don't think so, there is no <form>, right?!
function drupalgap_form_render(form) {
  try {
    if (drupalgap.settings.debug) {
      console.log('drupalgap_form_render()');
      console.log(JSON.stringify(form));
    }
    // Render each form element.
    var form_elements = '';
    $.each(form.elements, function(name, element){
        // Open the element.
        form_element = '';
        // If there wasn't a default value provided, set one.
        if (!element.default_value) {
          element.default_value = '';
        }
        // Grab the html id attribute for this element name.
        element_id = drupalgap_form_get_element_id(name, form.id);
        // Depending on the element type, render the field.
        switch (element.type) {
          case "email":
            form_element += '<div>';
            form_element += '<label for="' + name + '"><strong>' + element.title + '</strong></label>';
            if (element.required) { form_element += '*'; }
            form_element += '<input type="email" id="' + element_id + '" value="' + element.default_value + '"/>';
            form_element += '</div>';
            if (element.description) { form_element += '<div><small>' + element.description + '</small></div>'; }
            form_element += '<div>&nbsp;</div>';
            break;
          case 'image':
            form_element += '<div>';
            if (element.title) {
              form_element += '<label for="' + name + '"><strong>' + element.title + '</strong></label>';
            }            
            if (element.required) { form_element += '*'; }
            // Set the default button text, and if a value was provided,
            // overwrite the button text.
            var button_text = 'Add Image';
            if (element.value) {
              button_text = element.value;
            }
            // Place variables into document for PhoneGap image processing.
            var element_id_base = element_id.replace(/-/g, '_'); 
            var image_field_source = element_id_base + '_imagefield_source';
            var imagefield_destination_type = element_id_base + '_imagefield_destination_type';
            var imagefield_data = element_id_base + '_imagefield_data';
            eval('var ' + image_field_source + ' = null;');
            eval('var ' + imagefield_destination_type + ' = null;');
            eval('var ' + imagefield_data + ' = null;');
            // Build an imagefield widget with PhoneGap. Contains a message
            // div, an image element, and button to add an image.
            form_element += '<div>' + 
              '<div id="' + element_id + '-imagefield-msg"></div>' + 
              '<img id="' + element_id + '-imagefield" />' + 
              '<a href="#" data-role="button" id="' + element_id + '">' + element.value + '</a>' + 
            '</div>';
            // Open extra javascript declaration.
            form_element += '<script type="text/javascript">';
            // Add device ready listener for PhoneGap camera.
            var event_listener = element_id_base +  '_imagefield_ready';
            form_element += '$("#' + drupalgap_get_page_id(drupalgap.path) + '").on("pageshow",function(){' +
              'document.addEventListener("deviceready", ' + event_listener + ', false);' +
            '});' + 
            'function ' + event_listener +  '() {' +
              image_field_source + ' = navigator.camera.PictureSourceType;' +
              imagefield_destination_type + ' = navigator.camera.DestinationType;' +
            '}';
            // Define error callback function.
            var imagefield_error = element_id_base + '_error';
            form_element += 'function ' + imagefield_error + '(message) {' +
              'if (message != "Camera cancelled.") {' +
                'alert("' + imagefield_error + ' - " + message);' +
              '}' +
            '}';
            // Define success callback function.
            var imagefield_success = element_id_base + '_success';
            form_element += 'function ' + imagefield_success + '(message) {' +
              'alert("success!");' +
            '}';
            // Add click handler for photo button.
            form_element += '$("#' + element_id + '").on("click",function(){' +
              'var photo_options = {' +
                'quality: 50,' +
                'destinationType: ' + imagefield_destination_type + '.DATA_URL,' +
                'correctOrientation: true' +
              '};' +
              'navigator.camera.getPicture(' + imagefield_success + ', ' + imagefield_error + ', photo_options);' +
            '});';
            // Close extra javascript declaration.
            form_element += '</script>';
            form_element += '</div>';
            if (element.description) { form_element += '<div><small>' + element.description + '</small></div>'; }
            form_element += '<div>&nbsp;</div>';
            console.log(form_element);
            break;
          case "hidden":
            form_element += '<input type="hidden" id="' + element_id + '" value="' + element.default_value + '"/>';
            break;
          case "password":
            form_element += '<div>';
            form_element += '<label for="' + name + '"><strong>' + element.title + '</strong></label>';
            if (element.required) { form_element += '*'; }
            form_element += '<input type="password" id="' + element_id + '" value="' + element.default_value + '"/>';
            form_element += '</div>';
            if (element.description) { form_element += '<div><small>' + element.description + '</small></div>'; }
            form_element += '<div>&nbsp;</div>';
            break;
          case "submit":
            form_element += '<div>';
            var submit_attributes = {
              'type':'button',
              'data-theme':'b',
              'id':element_id,
              'onclick':'_drupalgap_form_submit(\'' + form.id + '\');'
            };
            //form_element += '<button type="button" data-theme="b" id="' + element_id + '" class="drupalgap_form_submit" form_id="' + form.id + '">' + element.value + '</button>';
            form_element += '<button ' + drupalgap_attributes(submit_attributes) + '>' + element.value + '</button>';
            form_element += '</div>';
            if (element.description) { form_element += '<div><small>' + element.description + '</small></div>'; }
            form_element += '<div>&nbsp;</div>';
            break;
          case "textfield":
            form_element += '<div>';
            form_element += '<label for="' + name + '"><strong>' + element.title + '</strong></label>';
            if (element.required) { form_element += '*'; }
            form_element += '<input type="text" id="' + element_id + '" value="' + element.default_value + '"/>';
            form_element += '</div>';
            if (element.description) { form_element += '<div><small>' + element.description + '</small></div>'; }
            form_element += '<div>&nbsp;</div>';
            break;
          case "checkbox":
            form_element += '<div>';
            form_element += '<label><input type="checkbox" id="' + element_id + '" name="' + element_id + '" ';
            if (element.default_value == 1) { form_element += 'checked'; }
            form_element += '/>' + element.title;
            if (element.required) { form_element += '*'; }
            form_element += '</label>';
            form_element += '</div>';
            if (element.description) { form_element += '<div><small>' + element.description + '</small></div>'; }
            form_element += '<div>&nbsp;</div>';
            break;
          case 'textarea':
          case 'text_long':
          case "text_with_summary":
          case 'text_textarea':
            form_element += '<div>';
            form_element += '<label for="' + name + '"><strong>' + element.title + '</strong></label>';
            if (element.required) { form_element += '*'; }
            form_element += '<textarea type="text" id="' + element_id + '">' + element.default_value + '</textarea>';
            form_element += '</div>';
            if (element.description) { form_element += '<div><small>' + element.description + '</small></div>'; }
            form_element += '<div>&nbsp;</div>';
            break;
          /*case "image":
            break;
          case "taxonomy_term_reference":
            break;*/
          case 'fieldset_start':
            form_element += '<div>';
            form_element += '<div data-role="fieldcontain"><fieldset data-role="controlgroup"><legend>' + element.title;
            if (element.required) { form_element += '*'; }
            form_element += ':</legend>';
            break;
          case 'fieldset_end':
            form_element += '</fieldset></div>';
            form_element += '</div><div>&nbsp;</div>';
            break;
          case 'markup':
            form_element += '<div>' + element.markup + '</div>';
            if (element.description) { form_element += '<div><small>' + element.description + '</small></div>'; }
            form_element += '<div>&nbsp;</div>';
            break;
          case 'date':
            if (element.default_value != 0) {
              var date = new Date(element.default_value * 1000);
            }
            else {
              var date = new Date();
            }
            var year = date.getFullYear();
            var month = date.getMonth() + 1;
            var day = date.getDate();
            form_element += '<div><label><strong>' + element.title + '</strong>' + (element.required ? '*' : '') + '</label><fieldset data-role="controlgroup" data-type="horizontal">';
            form_element += '<select name="' + element_id + '-month" id="' + element_id + '-month">';
            form_element += '<option value="1"' + (month == 1 ? ' selected' : '') + '>January</option>';
            form_element += '<option value="2"' + (month == 2 ? ' selected' : '') + '>February</option>';
            form_element += '<option value="3"' + (month == 3 ? ' selected' : '') + '>March</option>';
            form_element += '<option value="4"' + (month == 4 ? ' selected' : '') + '>April</option>';
            form_element += '<option value="5"' + (month == 5 ? ' selected' : '') + '>May</option>';
            form_element += '<option value="6"' + (month == 6 ? ' selected' : '') + '>June</option>';
            form_element += '<option value="7"' + (month == 7 ? ' selected' : '') + '>July</option>';
            form_element += '<option value="8"' + (month == 8 ? ' selected' : '') + '>August</option>';
            form_element += '<option value="9"' + (month == 9 ? ' selected' : '') + '>September</option>';
            form_element += '<option value="10"' + (month == 10 ? ' selected' : '') + '>October</option>';
            form_element += '<option value="11"' + (month == 11 ? ' selected' : '') + '>November</option>';
            form_element += '<option value="12"' + (month == 12 ? ' selected' : '') + '>December</option>';
            form_element += '</select>';
            form_element += '<select name="' + element_id + '-day" id="' + element_id + '-day">';
            form_element += '<option value="1"' + (day == 1 ? ' selected' : '') + '>1</option>';
            form_element += '<option value="2"' + (day == 2 ? ' selected' : '') + '>2</option>';
            form_element += '<option value="3"' + (day == 3 ? ' selected' : '') + '>3</option>';
            form_element += '<option value="4"' + (day == 4 ? ' selected' : '') + '>4</option>';
            form_element += '<option value="5"' + (day == 5 ? ' selected' : '') + '>5</option>';
            form_element += '<option value="6"' + (day == 6 ? ' selected' : '') + '>6</option>';
            form_element += '<option value="7"' + (day == 7 ? ' selected' : '') + '>7</option>';
            form_element += '<option value="8"' + (day == 8 ? ' selected' : '') + '>8</option>';
            form_element += '<option value="9"' + (day == 9 ? ' selected' : '') + '>9</option>';
            form_element += '<option value="10"' + (day == 10 ? ' selected' : '') + '>10</option>';
            form_element += '<option value="11"' + (day == 11 ? ' selected' : '') + '>11</option>';
            form_element += '<option value="12"' + (day == 12 ? ' selected' : '') + '>12</option>';
            form_element += '<option value="13"' + (day == 13 ? ' selected' : '') + '>13</option>';
            form_element += '<option value="14"' + (day == 14 ? ' selected' : '') + '>14</option>';
            form_element += '<option value="15"' + (day == 15 ? ' selected' : '') + '>15</option>';
            form_element += '<option value="16"' + (day == 16 ? ' selected' : '') + '>16</option>';
            form_element += '<option value="17"' + (day == 17 ? ' selected' : '') + '>17</option>';
            form_element += '<option value="18"' + (day == 18 ? ' selected' : '') + '>18</option>';
            form_element += '<option value="19"' + (day == 19 ? ' selected' : '') + '>19</option>';
            form_element += '<option value="20"' + (day == 20 ? ' selected' : '') + '>20</option>';
            form_element += '<option value="21"' + (day == 21 ? ' selected' : '') + '>21</option>';
            form_element += '<option value="22"' + (day == 22 ? ' selected' : '') + '>22</option>';
            form_element += '<option value="23"' + (day == 23 ? ' selected' : '') + '>23</option>';
            form_element += '<option value="24"' + (day == 24 ? ' selected' : '') + '>24</option>';
            form_element += '<option value="25"' + (day == 25 ? ' selected' : '') + '>25</option>';
            form_element += '<option value="26"' + (day == 26 ? ' selected' : '') + '>26</option>';
            form_element += '<option value="27"' + (day == 27 ? ' selected' : '') + '>27</option>';
            form_element += '<option value="28"' + (day == 28 ? ' selected' : '') + '>28</option>';
            form_element += '<option value="29"' + (day == 29 ? ' selected' : '') + '>29</option>';
            form_element += '<option value="30"' + (day == 30 ? ' selected' : '') + '>30</option>';
            form_element += '<option value="31"' + (day == 11 ? ' selected' : '') + '>31</option>';
            form_element += '</select>';
            form_element += '<select name="' + element_id + '-year" id="' + element_id + '-year">';
            form_element += '<option value="2013"' + (year == 2013 ? ' selected' : '') + '>2013</option>';
            form_element += '<option value="2014"' + (year == 2014 ? ' selected' : '') + '>2014</option>';
            form_element += '<option value="2015"' + (year == 2015 ? ' selected' : '') + '>2015</option>';
            form_element += '<option value="2016"' + (year == 2016 ? ' selected' : '') + '>2016</option>';
            form_element += '<option value="2017"' + (year == 2017 ? ' selected' : '') + '>2017</option>';
            form_element += '<option value="2018"' + (year == 2018 ? ' selected' : '') + '>2018</option>';
            form_element += '<option value="2019"' + (year == 2019 ? ' selected' : '') + '>2019</option>';
            form_element += '<option value="2020"' + (year == 2020 ? ' selected' : '') + '>2020</option>';
            form_element += '<option value="2021"' + (year == 2021 ? ' selected' : '') + '>2021</option>';
            form_element += '<option value="2022"' + (year == 2022 ? ' selected' : '') + '>2022</option>';
            form_element += '</select>';
            form_element += '</fieldset>';
            if (element.description) { form_element += '<div><small>' + element.description + '</small></div>'; }
            form_element += '</div><div>&nbsp;</div>';
            break;
          case 'select':
            form_element += '<div>';
            form_element += '<label for="' + name + '"><strong>' + element.title + '</strong>' + (element.required ? '*' : '') + '</label>';
            form_element += '<select id="' + element_id + '">';
            $.each(element.options, function(i) {
              form_element += '<option value="' + this.id + '"' + (element.default_value == this.id ? ' selected' : '') + '>' + this.name + '</option>';
            });
            form_element += '</select>';
            if (element.description) { form_element += '<div><small>' + element.description + '</small></div>'; }
            form_element += '</div><div>&nbsp;</div>';
            break;
          default:
            form_element += '<div><em>Field ' + element.type + ' not supported, yet.</em></div>';
            form_element += '</div><div>&nbsp;</div>';
            break;
        }
        form_elements += form_element;
    });
    // Add any form buttons to the form elements html.
    if (form.buttons && form.buttons.length != 0) {
      $.each(form.buttons, function(name, button){
          form_elements += '<button type="button" id="' + drupalgap_form_get_element_id(name, form.id) + '">' +  button.title + '</button>';
      });
    }
    // Attach javascript snippet to from to call the form_loaded function. Pass
    // the drupalgap.entity_edit along to the load function.
    var form_html = '<div><div id="drupalgap_form_errors"></div>' +
      form_elements +
    '</div>';
    // Return the form html.
    return form_html;
  }
  catch (error) {
    alert('drupalgap_form_render - ' + error);
  }
}

/**
 * Given a form element name and an error message, this attaches the error
 * message to the drupalgap.form_errors array, keyed by the form element name.
 */
function drupalgap_form_set_error(name, message) {
  try {
    drupalgap.form_errors[name] = message;
  }
  catch (error) {
    alert('drupalgap_form_set_error - ' + error);
  }
}

/**
 * Given a form, this function iterates over the form's elements and assembles
 * each element and value and places them into the form state's values. This
 * is similar to $form_state['values'] in Drupal.
 */
function drupalgap_form_state_values_assemble(form) {
  try {
    if (drupalgap.settings.debug) {
      console.log('drupalgap_form_state_values_assemble()');
      console.log(JSON.stringify(arguments));
    }
    var form_state = {'values':{}};
    $.each(form.elements, function(name, element) {
      if (name == 'submit') { return; } // Always skip the form 'submit'.
      var element_id = drupalgap_form_get_element_id(name, form.id);
      switch(element.type) {
        case 'checkbox':
          if ($('#' + element_id).prev().attr('data-icon') == 'checkbox-off') {
            $('#' + element_id).removeAttr('checked');
          }
          else {
            $('#' + element_id).attr('checked', true);
          }
          form_state.values[name] = $('#' + element_id).attr('checked') ? 'on' : null;
          break;
        case 'date':
          form_state.values[name] = $('#' + element_id + '-year').val() + '-' + $('#' + element_id + '-month').val() + '-' + $('#' + element_id + '-day').val();
          break;
        default:
          form_state.values[name] = $('#' + element_id).val();
          break;
      }      
    });
    // Attach the form state to drupalgap.form_states keyed by the form id.
    drupalgap.form_states[form.id] = form_state;
    if (drupalgap.settings.debug) {
      console.log(JSON.stringify(form_state));
    }
    return form_state;
  }
  catch (error) {
    alert('drupalgap_form_state_values_assemble - ' + error);
  }
}

/**
 * Given a form id, this will render the form. Any additional arguments
 * will be sent along to the form.
 */
function drupalgap_get_form(form_id) {
  try {
    if (drupalgap.settings.debug) {
      console.log('drupalgap_get_form(' + form_id + ')');
      console.log(JSON.stringify(arguments));
    }
    var html = '';
    var form = drupalgap_form_load.apply(null, Array.prototype.slice.call(arguments));
    if (form) {
      html = drupalgap_form_render(form);
    }
    else {
      alert('drupalgap_get_form - failed to get form (' + form_id + ')');
    }
    return html;
  }
  catch (error) {
    alert('drupalgap_get_form - ' + error);
  }
}

/**
 * Given a form id, this will return the form object assembled by the form's
 * call back function. If the form fails to load, this returns false.
 */
function drupalgap_form_load(form_id) {
  try {
    if (drupalgap.settings.debug) {
      console.log('drupalgap_form_load(' + form_id + ')');
      console.log(JSON.stringify(arguments));
    }
    
    //alert('drupalgap_form_load');
    
    var form = false;
    
    // The form's call back function will be equal to the form id.
    var function_name = form_id;
    if (eval('typeof ' + function_name) == 'function') {
      
      form = {};
      
      // Grab the function.
      var fn = window[function_name];
      
      // Build the form arguments by iterating over each argument then adding
      // each to to the form arguments, afterwards remove the argument at index
      // zero because that is the form id.
      var form_arguments = [];
      $.each(arguments, function(index, argument){
            form_arguments.push(argument);
      });
      form_arguments.splice(0,1);
      
      // If there were no arguments to pass along, call the function directly to
      // retrieve the form, otherwise call the function and pass along any
      // arguments to retrieve the form.
      if (form_arguments.length == 0) { form = fn(); }
      else {
        form = fn.apply(null, Array.prototype.slice.call(form_arguments));
      }
      
      // Give modules an opportunity to alter the form.
      //module_invoke_all('form_alter', form, drupalgap.form_state, form_id);
      module_invoke_all('form_alter', form, null, form_id);
      
      // Set drupalgap.form equal to the form.
      //drupalgap.form = form;
    }
    else {
      alert('drupalgap_form_load - no callback function (' + function_name + ') available for form');
    }
    return form;
  }
  catch (error) {
    alert('drupalgap_form_load - ' + error);
  }
}

/**
 * Handles a drupalgap form's submit button click.
 */
function _drupalgap_form_submit(form_id) {
  try {
    // Load the form by grabbing the form id from the submit button's attribute.
    // TODO - we should probably be wrapping a form in a form element you
    // dumb dumb.
    // TODO - doing a form load here without passing along the arguments that
    // were sent to the form originally results in some strange behavior. One
    // for example is, we lose the form.action value because when the form
    // is fetched again here there is entity so the action when editing an entity
    // never gets set properly.
    var form = drupalgap_form_load(form_id);
    if (!form) {
      alert('_drupalgap_form_submit - click - failed to load form: ' + form_id);
    }
    
    // Assemble the form state values.
    var form_state = drupalgap_form_state_values_assemble(form);
    console.log(JSON.stringify(form_state));
    
    // Clear our previous form errors.
    drupalgap.form_errors = {};
    
    // Call drupalgap form's api validate.
    _drupalgap_form_validate(form, form_state);
    
    // Call the form's validate function.
    var validate_function = form.id + '_validate';
    if (eval('typeof ' + validate_function) == 'function') {
      if (drupalgap.settings.debug) {
        console.log(validate_function);
      }
      var fn = window[validate_function];
      fn.apply(null, Array.prototype.slice.call([form, form_state]));
    }
    else if (drupalgap.settings.debug) {
      console.log('Skipping ' + validate_function + ', does not exist.');
    }
    
    // If there were validation errors, show the form errors and stop the
    // form submission.
    if (!jQuery.isEmptyObject(drupalgap.form_errors)) {
      if (drupalgap.settings.debug) {
        console.log(JSON.stringify(drupalgap.form_errors));
      }
      var html = '';
      $.each(drupalgap.form_errors, function(name, message){
          html += message + '\n\n';
      });
      /*navigator.notification.alert(
        html,
        function(){},
        'Warning',
        'OK'
      );*/
      alert(html);
      return false;
    }
    
    // Call the form's submit function.
    var submit_function = form.id + '_submit';
    if (eval('typeof ' + submit_function) == 'function') {
      if (drupalgap.settings.debug) {
        console.log(submit_function);
      }
      var fn = window[submit_function];
      fn.apply(null, Array.prototype.slice.call([form, form_state]));
    }
    else if (drupalgap.settings.debug) {
      console.log('Skipping ' + submit_function + ', does not exist.');
    }
  }
  catch (error) {
    alert('_drupalgap_form_submit - ' + error);
  }
}

/**
 * An internal function used by the DrupalGap forms api to validate all the
 * elements on a form when. 
 */
function _drupalgap_form_validate(form, form_state) {
  try {
    if (drupalgap.settings.debug) {
      console.log('_drupalgap_form_validate()');
      console.log(JSON.stringify(arguments));
    }
    $.each(form.elements, function(name, element) {
        if (name == 'submit') { return; }
        if (element.required) {
          if (form_state.values[name] == null || form_state.values[name] == '') {
            var field_title = name;
            if (element.title) { field_title = element.title; }
            drupalgap_form_set_error(name, 'The ' + field_title + ' field is required.');
          }
        }
    });
  }
  catch (error) {
    alert('_drupalgap_form_validate - ' + error);
  }
}

