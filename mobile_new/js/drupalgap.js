localStorage.site_path = "http://local.gilawebdev.com";
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
          if (localStorage.user_id != 0) {
            $("#index_page a.login-btn").attr("href", "#my_account").find("span.ui-btn-text").html("My Account");
            $("#index_page a.register-btn").attr("href", "#logout").find("span.ui-btn-text").html("Logout");
          }
          else {
            $("#index_page a.login-btn").attr("href", "#login").find("span.ui-btn-text").html("Login");
            $("#index_page a.register-btn").attr("href", "#register").find("span.ui-btn-text").html("Register");
          }
          
          $("#index_page a.today-best").click(build_deal_menu_event("today-best"));
          
          $("#index_page a.new").click(build_deal_menu_event("new"));
          
          $("#index_page a.popular").click(build_deal_menu_event("popular"));
          
          $("#index_page a.locations").click(function() {
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
          });
          
          $("#index_page a.categories").click(function() {
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
          });
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