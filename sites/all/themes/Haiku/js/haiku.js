$(window).load(function(){$(".menu_wrap ul ul").css("display","block")});jQuery(document).ready(function(e){e("ul#quotes").quote_rotator();e(".featured").orbit({timer:false});e("#front_slide").orbit({captions:true});e(".services_content").hover(function(){e(this).children(".team_image_hover").fadeTo(400,.8).show()},function(){e(this).children(".team_image_hover").fadeTo(400,0)});e(".carousel_item_wrapper").hover(function(){e(this).children(".carousel_item_hover").fadeTo(400,.9).show()},function(){e(this).children(".carousel_item_hover").fadeTo(400,0)});e().UItoTop({easingType:"easeOutQuart"});e(".recent_post_photo a").replaceWith(function(){return e(this).contents()});e(window).load(function(){var t=e("#isotope_test");t.isotope({itemSelector:".switch"});var n=e("#options .option-set"),r=n.find("a");r.click(function(){var n=e(this);if(n.hasClass("selected")){return false}var r=n.parents(".option-set");r.find(".selected").removeClass("selected");n.addClass("selected");var i={},s=r.attr("data-option-key"),o=n.attr("data-option-value");o=o==="false"?false:o;i[s]=o;if(s==="layoutMode"&&typeof changeLayoutMode==="function"){changeLayoutMode(n,i)}else{t.isotope(i)}return false})});e("#recent_projects").carouFredSel({width:"100%",responsive:true,circular:false,infinite:false,auto:false,next:{button:"#next",key:"right"},prev:{button:"#prev",key:"left"},swipe:{onMouse:true,onTouch:false},items:{visible:{min:1,max:4}}});e("#clients_carousel").carouFredSel({width:"100%",responsive:true,circular:false,infinite:false,auto:false,next:{button:"#clients_next",key:"right"},prev:{button:"#clients_prev",key:"left"},swipe:{onMouse:true,onTouch:false},items:{visible:{min:1,max:4}}});e('input[type="submit"]').addClass("small button");e(".has-dropdown ul").addClass("dropdown");e(".top-bar ul").removeClass("menu");e(".menu_wrap ul").addClass("right");e("#recent_projects").after('<div style="clear:both;"></div>');e(".menu_wrap .dropdown").prepend('<li class="title back js-generated"><h5><a href="#">Main Menu</a></h5></li>');e("#google_map").fitMaps({w:"100%",h:"370px"});jQuery("ul.faq li").each(function(){if(jQuery(this).index()>0){jQuery(this).children(".faq-content").css("display","none")}else{jQuery(this).find(".faq-head-image").addClass("active")}jQuery(this).children(".faq-head").bind("click",function(){jQuery(this).children().addClass(function(){if(jQuery(this).hasClass("active"))return"";return"active"});jQuery(this).siblings(".faq-content").slideDown();jQuery(this).parent().siblings("li").children(".faq-content").slideUp();jQuery(this).parent().siblings("li").find(".active").removeClass("active")})})})