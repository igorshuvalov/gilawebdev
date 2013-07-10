localStorage.site_path = "http://192.168.0.10/gilawebdev";
localStorage.default_services_endpoint = "drupalgap";
localStorage.service_path = localStorage.site_path + "/" + localStorage.default_services_endpoint;

var build_vote_plus_event = function(object) {
  
  var result_function = function() {
    $.mobile.showPageLoadingMsg();
    $.ajax({
      url: localStorage.site_path + '/deal/vote',
      type: 'POST',
      data: {
        id: object.did,
        type: 'plus',
        object: 'deal'
      },
      dataType: 'json',
      success: function(rsp) {
        $.mobile.hidePageLoadingMsg();
        switch(rsp.result) {
          case 'NO AUTHENTICATED':
            alert("You have to login to vote.");
            break;
          case 'FAILURE':
            alert('Your vote was not processed.');
            break;
          case 'SUCCESS':
            object.rate_state = rsp.state;
            $("#deal_info_page a.vote-plus .ui-btn-text").text(rsp.state.plus);
            $("#deal_info_page a.vote-plus").addClass("ui-btn-active").addClass("ui-disabled");
            $("#deal_info_page a.vote-minus .ui-btn-text").text(rsp.state.minus);
            $("#deal_info_page a.vote-minus").addClass("ui-disabled");
            if ($("#deal_info_page a.vote-cancel").length > 0) {
              $("#deal_info_page a.vote-cancel").removeClass("ui-disabled");
            }
            else {
              var vote_cancel_btn = $("<a>")
                .attr("data-role", "button")
                .attr("data-icon", "delete")
                .attr("data-mini", "true")
                .addClass("vote-cancel")
                .click(build_vote_cancel_event(object))
                .text("Cancel");
              $("#deal_info_page .vote-actions .ui-controlgroup-controls").append(vote_cancel_btn);
              try {
                vote_cancel_btn.button();
                $("#deal_info_page .vote-actions").controlgroup();
              } catch(e) { }
            }
            break;
          default:
            break;
        }
      },
      error: function(err) {
        $.mobile.hidePageLoadingMsg();
      }
    });
  }
  
  return result_function;
  
}

var build_vote_minus_event = function(object) {
  
  var result_function = function() {
    $.mobile.showPageLoadingMsg();
    $.ajax({
      url: localStorage.site_path + '/deal/vote',
      type: 'POST',
      data: {
        id: object.did,
        type: 'minus',
        object: 'deal'
      },
      dataType: 'json',
      success: function(rsp) {
        $.mobile.hidePageLoadingMsg();
        switch(rsp.result) {
          case 'NO AUTHENTICATED':
            alert("You have to login to vote.");
            break;
          case 'FAILURE':
            alert('Your vote was not processed.');
            break;
          case 'SUCCESS':
            object.rate_state = rsp.state;
            $("#deal_info_page a.vote-plus .ui-btn-text").text(rsp.state.plus);
            $("#deal_info_page a.vote-plus").addClass("ui-disabled");
            $("#deal_info_page a.vote-minus .ui-btn-text").text(rsp.state.minus);
            $("#deal_info_page a.vote-minus").addClass("ui-btn-active").addClass("ui-disabled");
            if ($("#deal_info_page a.vote-cancel").length > 0) {
              $("#deal_info_page a.vote-cancel").removeClass("ui-disabled");
            }
            else {
              var vote_cancel_btn = $("<a>")
                .attr("data-role", "button")
                .attr("data-icon", "delete")
                .attr("data-mini", "true")
                .addClass("vote-cancel")
                .click(build_vote_cancel_event(object))
                .text("Cancel");
              $("#deal_info_page .vote-actions .ui-controlgroup-controls").append(vote_cancel_btn);
              try {
                vote_cancel_btn.button();
                $("#deal_info_page .vote-actions").controlgroup();
              } catch(e) { }
            }
            break;
          default:
            break;
        }
      },
      error: function(err) {
        $.mobile.hidePageLoadingMsg();
      }
    });
  }
  
  return result_function;
  
}

var build_vote_cancel_event = function(object) {
  
  var result_function = function() {
    $.mobile.showPageLoadingMsg();
    $.ajax({
      url: localStorage.site_path + '/deal/vote/cancel',
      type: 'POST',
      data: {
        id: object.did,
        object: 'deal'
      },
      dataType: 'json',
      success: function(rsp) {
        $.mobile.hidePageLoadingMsg();
        switch(rsp.result) {
          case 'NO AUTHENTICATED':
            alert("You have to login to cancel this vote.");
            break;
          case 'FAILURE':
            alert('Your vote was not processed.');
            break;
          case 'SUCCESS':
            object.rate_state = rsp.state;
            $("#deal_info_page a.vote-plus .ui-btn-text").text(rsp.state.plus);
            $("#deal_info_page a.vote-plus").removeClass("ui-disabled").removeClass("ui-btn-active");
            $("#deal_info_page a.vote-minus .ui-btn-text").text(rsp.state.minus);
            $("#deal_info_page a.vote-minus").removeClass("ui-disabled").removeClass("ui-btn-active");
            $("#deal_info_page a.vote-cancel").addClass("ui-disabled");
            break;
          default:
            break;
        }
      },
      error: function(err) {
        $.mobile.hidePageLoadingMsg();
      }
    });
  }
  
  return result_function;
  
}

var build_comment_submit_event = function(object) {
  var result_function = function() {
    $.mobile.showPageLoadingMsg();
    $.ajax({
      type: "post",
      async: false,
      dataType: "json",
      data: {
        nid: object.nid,
        pid: object.pid,
        comment: $(object.comment_input).val(),
      },
      url: localStorage.service_path + "/drupalgap_deal/comment_submit",
      beforeSend: function(request) {
        request.setRequestHeader("X-CSRF-Token", localStorage.token);
      },
      success: function(rsp) {
        switch(rsp.result) {
          case "NO AUTHENTICATED":
            alert("You have to sign in to comment.")
            break;
          case "SUCCESS":
            build_comment_section(object.nid)();
            break;
          default:
            break;
        }
      },
      error: function(err) {
        $.mobile.hidePageLoadingMsg();
        alert("Comment was not submitted.");
      }
    });
  };
  
  return result_function;
}

var build_comment_section = function(node_id) {
  var result_function = function() {
    $.ajax({
      type: "post",
      async: false,
      dataType: "json",
      url: localStorage.service_path + "/drupalgap_deal/comments/" + node_id,
      beforeSend: function(request) {
        request.setRequestHeader("X-CSRF-Token", localStorage.token);
      },
      success: function(rsp) {
        $.mobile.hidePageLoadingMsg();
        var comments_content = $("<div>")
          .attr("data-role", "collapsible-set")
          .attr("data-collapsed-icon", "arrow-r")
          .attr("data-expanded-icon", "arrow-d")
          .addClass("ui-corner-all");
        if (rsp.comments) {
          $.each(rsp.comments, function(id, comment) {
            var comment_item_comment = $("<h2>")
              .html(comment.comment_body.und[0].value);
            var comment_item_submitted = $("<p>")
              .html(comment.submitted);
              
            var comment_item_reply_input = $("<input>")
              .attr("type", "text")
              .attr("name", "reply" + comment.cid)
              .attr("id", "reply" + comment.cid)
              .attr("value", "");
            var comment_item_reply_submit = $("<button>")
              .attr("data-theme", "c")
              .html("Reply")
              .click(build_comment_submit_event({
                  nid: node_id,
                  pid: comment.cid,
                  comment_input: "#reply" + comment.cid
              })
            );
            
            var comment_item = $("<div>")
              .attr("data-role", "collapsible")
              .attr("data-theme", "c")
              .attr("data-content-theme", "c")
              .append(comment_item_comment)
              .append(comment_item_submitted);
            if (localStorage.user_id != 0) {
              comment_item
                .append(
                  $("<label>")
                  .attr("for", "reply" + comment.cid)
                  .html("Comment")
                )
                .append(comment_item_reply_input)
                .append(comment_item_reply_submit);
            }
            
            comments_content.append(comment_item);
            
            try {
              comment_item_reply_input.textinput();
              comment_item_reply_submit.button();
              comment_item.collapsible({refresh:true});
            } catch(e) { }
          });
          comments_content.find(">:first-child").addClass("ui-first-child");
          comments_content.find(">:last-child").addClass("ui-last-child");
        }
        $("#deal_info_page .comments-content")
          .html("")
          .append(comments_content);
        
        try {
          comments_content.collapsibleset("refresh");
        } catch (e) { }
        
        var comment_item_comment_input = $("<input>")
          .attr("type", "text")
          .attr("name", "comment_new")
          .attr("id", "comment_new")
          .attr("value", "");
        var comment_item_comment_submit = $("<button>")
          .attr("data-theme", "c")
          .html("Submit")
          .click(build_comment_submit_event({
              nid: node_id,
              pid: 0,
              comment_input: "#comment_new"
          })
        );
          
        $("#deal_info_page .comment-create-content").html("");
        if (localStorage.user_id == 0) {
          $("#deal_info_page .comment-create-content")
            .append(
              $("<label>")
              .html("You have to sign in to comment for this content")
            );
        }
        else {
          $("#deal_info_page .comment-create-content")
            .append(
              $("<label>")
              .attr("for", "comment_new")
              .html("Comment")
            )
            .append(comment_item_comment_input)
            .append(comment_item_comment_submit);
        }
        
        try {
          comment_item_comment_input.textinput();
          comment_item_comment_submit.button();
        } catch(e) { }
      },
      error: function(err) {
        $.mobile.hidePageLoadingMsg();
      }
    });
  }
  
  return result_function;
}

var build_deal_page = function(object) {
  var result_function = function() {
    $("#deal_info_page h1.title").text(object.title);
    $("#deal_info_page .content .deal-info").html(
      "<p>" + (object.expired == "true" ? "<h4>EXPIRED</h4>" : "") + "</p>"
      + "<p>" + object.submitted + "</p>"
      + "<p>" + object.photo + "</p>"
      + "<p class='vote-content'>" + "</p>"
      + (object.coupon_code ? "<p>Coupon Code: " + object.coupon_code + "</p>" : "")
      + "<p>" + "URL: <a href='" + object.deal_url + "' target='_blank'>" + object.deal_url + "</a></p>"
      + "<p>" + object.description + "</p>"
      + "<p>" + "Store Representative: " + (object.representative == "true" ? "YES" : "NO") + "</p>"
      + "<p>" + "Start Date: " + object.date_start + "</p>"
      + "<p>" + "Expiry Date: " + object.date_expiry + "</p>"
      + "<p>" + "Category: " + object.category + "</p>"
      + "<p>" + "Location: " + object.location + "</p>"
      + "<p>" + "Tag: " + object.tags + "</p>"
    );
    
    var vote_plus_btn = $("<a>")
      .attr("data-role", "button")
      .attr("data-icon", "plus")
      .attr("data-mini", "true")
      .addClass("vote-plus")
      .click(build_vote_plus_event(object))
      .text(object.rate_state.plus);
    var vote_minus_btn = $("<a>")
      .attr("data-role", "button")
      .attr("data-icon", "minus")
      .attr("data-mini", "true")
      .addClass("vote-minus")
      .click(build_vote_minus_event(object))
      .text(object.rate_state.minus);
    var vote_cancel_btn = null;
    var vote_actions = $("<div>")
      .attr("data-role", "controlgroup")
      .attr("data-type", "horizontal")
      .addClass("vote-actions");
    
    if (object.rate_state.voted_state.rate != "false") {
      if (object.rate_state.voted_state.status == "1") {
        vote_plus_btn.addClass("ui-disabled");
        vote_minus_btn.addClass("ui-disabled");
        if (object.rate_state.voted_state.rate == "1") {
          vote_plus_btn.addClass("ui-btn-active");
        }
        else {
          vote_minus_btn.addClass("ui-btn-active");
        }
      }
      else if (localStorage.user_id == 0) {
        vote_plus_btn.addClass("ui-disabled");
        vote_minus_btn.addClass("ui-disabled");
      }
      if (object.rate_state.voted_state.votable == false && object.rate_state.voted_state.status == 1) {
        vote_cancel_btn = $("<a>")
          .attr("data-role", "button")
          .attr("data-icon", "delete")
          .attr("data-mini", "true")
          .addClass("vote-cancel")
          .click(build_vote_cancel_event(object))
          .text("Cancel");
      }
    }
    
    vote_actions
      .append(vote_plus_btn)
      .append(vote_minus_btn)
      .append(vote_cancel_btn);
    
    $("#deal_info_page .content .vote-content").append(
      vote_actions
    );
    
    try{
      vote_actions.find("a").button();
      vote_actions.controlgroup();
    } catch(e) {}
    
    $.mobile.showPageLoadingMsg();
    build_comment_section(object.dnid)();
  };
  
  return result_function;
}

var build_forum_page = function(object) {
  var result_function = function() {
    $("#deal_info_page h1.title").text(object.title);
    $("#deal_info_page .content .deal-info").html(
      "<p>" + object.submitted + "</p>"
      + "<p>" + object.description + "</p>"
    );
    
    $.mobile.showPageLoadingMsg();
    build_comment_section(object.nid)();
  };
  
  return result_function;
}

var build_deal_list_item = function(object) {
  return $("<li>")
    .append(
      $("<a>")
      .attr("href", "#deal_info_page")
      .attr("data-transition", "slide")
      .html(object.title)
      .click(build_deal_page(object))
    );
};

var build_deal_category_list_item = function(object) {
  return $("<li>")
    .append(
      $("<a>")
      .attr("href", "#deal_list_page")
      .attr("data-transition", "slide")
      .html(object.name)
      .click(build_deal_menu_event("category", object.id, object.name))
    );
};

var build_deal_location_list_item = function(object) {
  return $("<li>")
    .append(
      $("<a>")
      .attr("href", "#deal_list_page")
      .attr("data-transition", "slide")
      .html(object.name)
      .click(build_deal_menu_event("location", object.id, object.name))
    );
};

var build_deal_menu_event = function(class_name) {
  var 
    _title = "",
    _type = "post",
    _async = false,
    _dataType = "json",
    _url = "",
    _beforeSend = function(request) {
      request.setRequestHeader("X-CSRF-Token", localStorage.token);
    },
    _success = function(rsp) {
      $.mobile.hidePageLoadingMsg();
      $("#deal_list_page .deal-list").html("");
      $.each(rsp, function(index, object){
        $("#deal_list_page .deal-list").append(
          build_deal_list_item(object)
        );
      });
      try {
        $("#deal_list_page .deal-list").listview("refresh", true);
      } catch(e) {}
    },
    _error = function(err) {};
    
  switch(class_name) {
    case "today-best":
      _title = "Today's Best Deals";
      _url = localStorage.service_path + "/drupalgap_deal/today_best";
      break;
    case "new":
      _title = "New Deals";
      _url = localStorage.service_path + "/drupalgap_deal/new";
      break;
    case "popular":
      _title = "Popular Deals";
      _url = localStorage.service_path + "/drupalgap_deal/popular";
      break;
    case "category":
      _title = arguments[2];
      _url = localStorage.service_path + "/drupalgap_deal/category/" + arguments[1];
      break;
    case "location":
      _title = arguments[2];
      _url = localStorage.service_path + "/drupalgap_deal/location/" + arguments[1];
      break;
    default:
      break;
  }
  
  var result_function = function() {
    $.mobile.showPageLoadingMsg();
    $("#deal_list_page h1.title").text(_title);
    $.ajax({
      type: _type,
      async: _async,
      dataType: _dataType,
      url: _url,
      beforeSend: _beforeSend,
      success: _success,
      error: _error
    });
  };
  
  return result_function;
  
};

var build_forum_list_item = function(object) {
  return $("<li>")
    .append(
      $("<a>")
      .attr("href", "#deal_info_page")
      .attr("data-transition", "slide")
      .html(object.title)
      .click(build_forum_page(object))
    );
};

var initialize_deal_submit_form = function() {
  var monthNames = [ "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December" ];
  $("#title").val("");
  $("#deal_url").val("");
  $("#photo_automatic")
    .attr("checked", false)
    .next()
    .removeClass("ui-checkbox-on")
    .addClass("ui-checkbox-off")
    .attr("data-icon", "checkbox-off")
    .find(".ui-icon")
    .removeClass("ui-icon-checkbox-on")
    .addClass("ui-icon-checkbox-off");
  $("#coupon_code").val("");
  $("#description").val("");
  $("#representative")
    .val("no")
    .next()
    .find(".ui-slider-label-a")
    .css({width: "0%"});
  $("#representative")
    .next()
    .find(".ui-slider-label-b")
    .css({width: "100%"});
  $("#representative")
    .next()
    .find(".ui-slider-handle")
    .attr("aria-valuenow", "no")
    .attr("aria-valuetext", "No")
    .attr("title", "No")
    .css({left: "0%"});
  var date = new Date();
  $("#date_start_year")
    .val(date.getFullYear())
    .prev()
    .find(".ui-btn-text")
    .html("<span>" + date.getFullYear() + "</span>");
  $("#date_start_month")
    .val(date.getMonth() + 1)
    .prev()
    .find(".ui-btn-text")
    .html("<span>" + monthNames[date.getMonth()] + "</span>");
  $("#date_start_day")
    .val(date.getDate())
    .prev()
    .find(".ui-btn-text")
    .html("<span>" + date.getDate() + "</span>");
  $("#date_expiry_year")
    .val(date.getFullYear())
    .prev()
    .find(".ui-btn-text")
    .html("<span>" + date.getFullYear() + "</span>");
  $("#date_expiry_month")
    .val(date.getMonth() + 1)
    .prev()
    .find(".ui-btn-text")
    .html("<span>" + monthNames[date.getMonth()] + "</span>");
  $("#date_expiry_day")
    .val(date.getDate())
    .prev()
    .find(".ui-btn-text")
    .html("<span>" + date.getDate() + "</span>");
  $("#category")
    .val(1)
    .prev()
    .find(".ui-btn-text")
    .html("<span>Accessories</span>");
  $("#location")
    .val(1)
    .prev()
    .find(".ui-btn-text")
    .html("<span>Online Only</span>");
  $("#tags").val("");
}

var build_deal_menu = function() {
  var result_function = function() {
    $(this).addClass("ui-state-persist");
    $("#index_page a.forum_list").removeClass("ui-state-persist");
    $("#index_page .main-list-view").html("");
    $("#index_page .main-list-view")
    .append(
      $("<li>")
      .append(
        $("<a>")
        .attr("href", "#deal_list_page")
        .attr("data-transition", "slide")
        .html("Today's Best Deals")
        .click(build_deal_menu_event("today-best"))
      )
    )
    .append(
      $("<li>")
      .append(
        $("<a>")
        .attr("href", "#deal_list_page")
        .attr("data-transition", "slide")
        .html("New Deals")
        .click(build_deal_menu_event("new"))
      )
    )
    .append(
      $("<li>")
      .append(
        $("<a>")
        .attr("href", "#deal_list_page")
        .attr("data-transition", "slide")
        .html("Popular Deals")
        .click(build_deal_menu_event("popular"))
      )
    )
    .append(
      $("<li>")
      .append(
        $("<a>")
        .attr("href", "#categories_page")
        .attr("data-transition", "slide")
        .html("Deals by Location")
        .click(function() {
          $.mobile.showPageLoadingMsg();
          $("#categories_page h1.title").text("Locations");
          $.ajax({
            type: "post",
            async: false,
            dataType: "json",
            url: localStorage.service_path + "/drupalgap_deal/location_items",
            beforeSend: function(request) {
              request.setRequestHeader("X-CSRF-Token", localStorage.token);
            },
            success: function(rsp) {
              $.mobile.hidePageLoadingMsg();
              $("#categories_page .category-list").html("");
              $.each(rsp, function(index, object){
                $("#categories_page .category-list").append(
                  build_deal_location_list_item(object)
                );
              });
              try{
                $("#categories_page .category-list").listview("refresh", true);
              } catch(e) { }
            },
            error: function(err) {}
          });
        })
      )
    )
    .append(
      $("<li>")
      .append(
        $("<a>")
        .attr("href", "#categories_page")
        .attr("data-transition", "slide")
        .html("Deals by Category")
        .click(function() {
          $.mobile.showPageLoadingMsg();
          $("#categories_page h1.title").text("Categories");
          $.ajax({
            type: "post",
            async: false,
            dataType: "json",
            url: localStorage.service_path + "/drupalgap_deal/category_items",
            beforeSend: function(request) {
              request.setRequestHeader("X-CSRF-Token", localStorage.token);
            },
            success: function(rsp) {
              $.mobile.hidePageLoadingMsg();
              $("#categories_page .category-list").html("");
              $.each(rsp, function(index, object){
                $("#categories_page .category-list").append(
                  build_deal_category_list_item(object)
                );
              });
              try{
                $("#categories_page .category-list").listview("refresh", true);
              } catch(e) { }
            },
            error: function(err) {}
          });
        })
      )
    );
    
    try {
      $("#index_page .main-list-view").listview("refresh", true);
    } catch(e) {};
  };
  
  return result_function;
}

var build_login_link_event = function() {
  var result_function = function() {
    if ($("#username").val() == "") {
      $("#username").focus();
      return false;
    }
    if ($("#password").val() == "") {
      $("#password").focus();
      return false;
    }
    $.mobile.showPageLoadingMsg();
    $.ajax({
      type: "post",
      async: false,
      dataType: "json",
      data: {
        username: $("#username").val(),
        password: $("#password").val(),
      },
      url: localStorage.service_path + "/drupalgap_user/login",
      beforeSend: function(request) {
        request.setRequestHeader("X-CSRF-Token", localStorage.token);
      },
      success: function(rsp) {
        $("#username").val("");
        $("#password").val("");
        localStorage.user_id = rsp._user_resource_login.user.uid;
        localStorage.user_name = rsp._user_resource_login.user.name;
        $('.ui-dialog').dialog('close');
        $("#index_page a.login-btn")
          .attr("href", "#my_account")
          .find("span.ui-btn-text")
          .html("My Account");
        $("#index_page a.register-btn")
          .removeAttr("href")
          .click(build_logout_link_event())
          .find("span.ui-btn-text")
          .html("Logout");
          
        $.ajax({
          type: "get",
          async: false,
          dataType: "text",
          url: localStorage.site_path + "/services/session/token",
          success: function(rsp) {
            $.mobile.hidePageLoadingMsg();
            localStorage.token = rsp;
          },
          error: function(err) { $.mobile.hidePageLoadingMsg(); }
        });
      },
      error: function(err) {
        $.mobile.hidePageLoadingMsg();
        $("#login .message").html("Wrong username or password.");
      }
    });
  };
  
  return result_function;
}

var build_register_link_event = function() {
  var result_function = function() {
    var reg_user = new RegExp(/^[a-z0-9_-]{1,60}$/);
    var reg_mail = new RegExp(/^\w+@[a-zA-Z_]+?\.[a-zA-Z]{2,3}$/);
    
    if ($("#user").val() == "") {
      $("#register .message").html("You must enter a username.");
      $("#user").focus();
      return false;
    }
    if ($("#user").val().substring(0, 1) == " ") {
      $("#register .message").html("The username cannot begin with a space.");
      $("#user").focus();
      return false;
    }
    if ($("#user").val().substring($("#user").val().length - 1) == " ") {
      $("#register .message").html("The username cannot end with a space.");
      $("#user").focus();
      return false;
    }
    if ($("#user").val().search("  ") !== -1) {
      $("#register .message").html("The username cannot contain multiple spaces in a row.");
      $("#user").focus();
      return false;
    }
    if ($("#user").val().length > 60) {
      $("#register .message").html("The username is too long: it must be 60 characters or less.");
      $("#user").focus();
      return false;
    }
    if ($("#user").val().match(reg_user) == null) {
      $("#register .message").html("The username contains an illegal character.");
      $("#user").focus();
      return false;
    }
    
    if ($("#mail").val().match(reg_mail) == null) {
      $("#register .message").html("Email validation is failed.");
      $("#mail").focus();
      return false;
    }
    
    if ($("#pass").val() == "") {
      $("#register .message").html("You must enter the password.");
      $("#pass").focus();
      return false;
    }
    if ($("#pass").val() != $("#confirm_pass").val()) {
      $("#register .message").html("The confirm password is not same with password. Please check the confirm password again.");
      $("#confirm_pass").focus();
      return false;
    }
    $.mobile.showPageLoadingMsg();
    $.ajax({
      type: "post",
      async: false,
      dataType: "json",
      data: {
        name: $("#user").val(),
        mail: $("#mail").val(),
        pass: $("#pass").val(),
        gender: $("#gender").val(),
        city: $("#city").val(),
        category: $("#favourite_category").val(),
      },
      url: localStorage.service_path + "/drupalgap_user/register",
      beforeSend: function(request) {
        request.setRequestHeader("X-CSRF-Token", localStorage.token);
      },
      success: function(rsp) {
        $.mobile.hidePageLoadingMsg();
        $("#register .message")
        .html("Your account has been created successfully. <BR>Your account will be activated soon. Please check your email box.")
        .show();
      },
      error: function(err) {
        $.mobile.hidePageLoadingMsg();
        $("#register .message")
        .html("Errors are occurring while creating new account. <BR>Please contact administrator for this problem.")
        .show();
      }
    });
    return false;
  }
  
  return result_function;
}

var build_logout_link_event = function() {
  var result_function = function() {
    $.mobile.showPageLoadingMsg();
    $.ajax({
      type: "post",
      async: false,
      dataType: "json",
      url: localStorage.service_path + "/drupalgap_user/logout",
      beforeSend: function(request) {
        request.setRequestHeader("X-CSRF-Token", localStorage.token);
      },
      success: function(rsp) {
        $.mobile.hidePageLoadingMsg();
        localStorage.user_id = 0;
        localStorage.user_name = "";
        $("#index_page a.login-btn")
          .attr("href", "#login")
          .find("span.ui-btn-text")
          .html("Login");
        $("#index_page a.register-btn")
          .attr("href", "#register")
          .unbind('click')
          .find("span.ui-btn-text")
          .html("Register");
      },
      error: function(err) { }
    });
    return false;
  };
  
  return result_function;
}

$(document).ready(function() {
  $.mobile.showPageLoadingMsg();
  
  $.ajax({
    type: "get",
    async: false,
    dataType: "text",
    url: localStorage.site_path + "/services/session/token",
    success: function(rsp) {
      localStorage.token = rsp;
      $.ajax({
        type: "post",
        async: false,
        dataType: "json",
        url: localStorage.service_path + "/drupalgap_system/connect.json",
        beforeSend: function (request) {
          request.setRequestHeader("X-CSRF-Token", localStorage.token);
        },
        success: function(rsp) {
          $.mobile.hidePageLoadingMsg();
          localStorage.user_id = rsp.system_connect.user.uid;
          localStorage.user_name = rsp.system_connect.user.name;
          localStorage.user_mail = rsp.system_connect.user.mail;
          if (localStorage.user_id != 0) {
            $("#index_page a.login-btn")
              .attr("href", "#my_account")
              .find("span.ui-btn-text")
              .html("My Account");
            $("#index_page a.register-btn")
              .removeAttr("href")
              .click(build_logout_link_event())
              .find("span.ui-btn-text")
              .html("Logout");
            $("#my_account .content")
              .html(
                "Name: " + localStorage.user_name + "<BR>" +
                "Email: " + localStorage.user_mail
              );
          }
          else {
            $("#index_page a.login-btn")
              .attr("href", "#login")
              .find("span.ui-btn-text")
              .html("Login");
            $("#index_page a.register-btn")
              .attr("href", "#register")
              .unbind('click')
              .find("span.ui-btn-text")
              .html("Register");
          }
          $("#login_action")
            .click(build_login_link_event());
          $("#register_action")
            .click(build_register_link_event());
          
          $("#index_page a.deals-menu").click(build_deal_menu());
          
          $("#index_page a.forum_list").click(function() {
            $(this).addClass("ui-state-persist");
            $("#index_page a.deals-menu").removeClass("ui-state-persist");
            $.mobile.showPageLoadingMsg();
            $("#deal_list_page h1.title").text("Forums");
            $.ajax({
              type: "post",
              async: false,
              dataType: "json",
              url: localStorage.service_path + "/drupalgap_forum/retrieve",
              beforeSend: function(request) {
                request.setRequestHeader("X-CSRF-Token", localStorage.token);
              },
              success: function(rsp) {
                $.mobile.hidePageLoadingMsg();
                $("#index_page .main-list-view").html("");
                $.each(rsp, function(index, object){
                  $("#index_page .main-list-view").append(
                    build_forum_list_item(object)
                  );
                });
                try {
                  $("#index_page .main-list-view").listview("refresh", true);
                } catch(e) {};
              },
              error: function(err) { }
            });
          });
          
          $("#index_page a.submit-deal").click(function() {
            if (localStorage.user_id == 0) {
              alert("You have to sign in to post new deal.");
              return false;
            }
          });
          
          $("#submit_deal_action").click(function() {
            if (localStorage.user_id == 0) {
              $("#submit_deal .message").html("You have to sign in to post new deal.").show().focus();
            }
            else {
              var error = false;
              if ($("#title").val() == "") {
                $("#title").focus();
                return false;
              }
              
              if ($("#deal_url").val() == "") {
                $("#title").focus();
                return false;
              }
              
              if ($("#description").val() == "") {
                $("#title").focus();
                return false;
              }
              
              if ($("#category").val() == "") {
                $("#title").focus();
                return false;
              }
              
              if ($("#location").val() == "") {
                $("#title").focus();
                return false;
              }
              
              if ($("#tags").val() == "") {
                $("#title").focus();
                return false;
              }
              
              $.mobile.showPageLoadingMsg();
              $.ajax({
                type: "post",
                async: false,
                dataType: "json",
                data: {
                  title: $("#title").val(),
                  deal_url: $("#deal_url").val(),
                  photo_automatic: $("#photo_automatic").val(),
                  coupon_code: $("#coupon_code").val(),
                  description: $("#description").val(),
                  representative: $("#representative").val(),
                  date_start: $('#date_start_year').val() + '-' + $('#date_start_month').val() + '-' + $('#date_start_day').val(),
                  date_expiry: $('#date_expiry_year').val() + '-' + $('#date_expiry_month').val() + '-' + $('#date_expiry_day').val(),
                  category: $('#category').val(),
                  location: $('#location').val(),
                  tags: $('#tags').val(),
                },
                url: localStorage.service_path + "/drupalgap_deal/deal_submit",
                beforeSend: function(request) {
                  request.setRequestHeader("X-CSRF-Token", localStorage.token);
                },
                success: function(rsp) {
                  $.mobile.hidePageLoadingMsg();
                  switch(rsp.result) {
                    case "NO AUTHENTICATED":
                      $("#submit_deal .message").html("You have to sign in to post new deal.").show();
                      $("html, body").animate({ scrollTop: 50 }, "slow");
                      break;
                    case "FAILED VALIDATION":
                      var error_msg = "";
                      $.each(rsp.errors, function(key, message) {
                        error_msg += "<p>" + key + " : " + message + "</p>";
                      });
                      $("#submit_deal .message").html(error_msg).show();
                      $("html, body").animate({ scrollTop: 50 }, "slow");
                      break;
                    case "SUCCESS":
                      $("#submit_deal .message").html("New deal has been created.").show();
                      $("html, body").animate({ scrollTop: 50 }, "slow");
                      initialize_deal_submit_form();
                      break;
                  }
                },
                error: function(err) {}
              });
            }
          });
          
          build_deal_menu()();
          initialize_deal_submit_form();
        },
        error: function(err) {
          $.mobile.hidePageLoadingMsg();
          alert("Service Connnection is failed.");
          $("#index_page").hide();
        }
      });
    },
    error: function(err) {
      $.mobile.hidePageLoadingMsg();
      alert("Network Connnection is failed.");
      $("#index_page").hide();
    }
  });
});