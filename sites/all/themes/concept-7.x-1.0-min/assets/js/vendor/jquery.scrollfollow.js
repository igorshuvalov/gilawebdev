/**
 * jquery.scrollFollow.js
 * Copyright (c) 2008 Net Perspective (http://kitchen.net-perspective.com/)
 * Licensed under the MIT License (http://www.opensource.org/licenses/mit-license.php)
 *
 * @author R.A. Ray
 *
 * @projectDescription	jQuery plugin for allowing an element to animate down as the user scrolls the page.
 *
 * @version 0.4.0
 *
 * @requires jquery.js (tested with 1.2.6)
 * @requires ui.core.js (tested with 1.5.2)
 *
 * @optional jquery.cookie.js (http://www.stilbuero.de/2006/09/17/cookie-plugin-for-jquery/)
 * @optional jquery.easing.js (http://gsgd.co.uk/sandbox/jquery/easing/ - tested with 1.3)
 *
 * @param speed		int - Duration of animation (in milliseconds)
 * 								default: 500
 * @param offset			int - Number of pixels box should remain from top of viewport
 * 								default: 0
 * @param easing		string - Any one of the easing options from the easing plugin - Requires jQuery Easing Plugin < http://gsgd.co.uk/sandbox/jquery/easing/ >
 * 								default: 'linear'
 * @param container	string - ID of the containing div
 * 								default: box's immediate parent
 * @param killSwitch	string - ID of the On/Off toggle element
 * 								default: 'killSwitch'
 * @param onText		string - killSwitch text to be displayed if sliding is enabled
 * 								default: 'Turn Slide Off'
 * @param offText		string - killSwitch text to be displayed if sliding is disabled
 * 								default: 'Turn Slide On'
 * @param relativeTo	string - Scroll animation can be relative to either the 'top' or 'bottom' of the viewport
 * 								default: 'top'
 * @param delay			int - Time between the end of the scroll and the beginning of the animation in milliseconds
 * 								default: 0
 */
(function($){$.scrollFollow=function(box,options){box=$(box);var position=box.css("position");function ani(){box.queue([]);var viewportHeight=parseInt($(window).height());var pageScroll=parseInt($(document).scrollTop());var parentTop=parseInt(box.cont.offset().top);var parentHeight=parseInt(box.cont.attr("offsetHeight"));var boxHeight=parseInt(box.attr("offsetHeight")+(parseInt(box.css("marginTop"))||0)+(parseInt(box.css("marginBottom"))||0));var aniTop;if(isActive){if(options.relativeTo=="top"){if(box.initialOffsetTop>=(pageScroll+options.offset)){aniTop=box.initialTop;}else{aniTop=Math.min((Math.max((-parentTop),(pageScroll-box.initialOffsetTop+box.initialTop))+options.offset),(parentHeight-boxHeight-box.paddingAdjustment));}}else{if(options.relativeTo=="bottom"){if((box.initialOffsetTop+boxHeight)>=(pageScroll+options.offset+viewportHeight)){aniTop=box.initialTop;}else{aniTop=Math.min((pageScroll+viewportHeight-boxHeight-options.offset),(parentHeight-boxHeight));}}}if((new Date().getTime()-box.lastScroll)>=(options.delay-20)){box.animate({top:aniTop},options.speed,options.easing);}}}var isActive=true;if($.cookie!=undefined){if($.cookie("scrollFollowSetting"+box.attr("id"))=="false"){var isActive=false;$("#"+options.killSwitch).text(options.offText).toggle(function(){isActive=true;$(this).text(options.onText);$.cookie("scrollFollowSetting"+box.attr("id"),true,{expires:365,path:"/"});ani();},function(){isActive=false;$(this).text(options.offText);box.animate({top:box.initialTop},options.speed,options.easing);$.cookie("scrollFollowSetting"+box.attr("id"),false,{expires:365,path:"/"});});}else{$("#"+options.killSwitch).text(options.onText).toggle(function(){isActive=false;$(this).text(options.offText);box.animate({top:box.initialTop},0);$.cookie("scrollFollowSetting"+box.attr("id"),false,{expires:365,path:"/"});},function(){isActive=true;$(this).text(options.onText);$.cookie("scrollFollowSetting"+box.attr("id"),true,{expires:365,path:"/"});ani();});}}if(options.container==""){box.cont=box.parent();}else{box.cont=$("#"+options.container);}box.initialOffsetTop=parseInt(box.offset().top);box.initialTop=parseInt(box.css("top"))||0;if(box.css("position")=="relative"){box.paddingAdjustment=parseInt(box.cont.css("paddingTop"))+parseInt(box.cont.css("paddingBottom"));}else{box.paddingAdjustment=0;}$(window).scroll(function(){$.fn.scrollFollow.interval=setTimeout(function(){ani();},options.delay);box.lastScroll=new Date().getTime();});$(window).resize(function(){$.fn.scrollFollow.interval=setTimeout(function(){ani();},options.delay);box.lastScroll=new Date().getTime();});box.lastScroll=0;ani();};$.fn.scrollFollow=function(options){options=options||{};options.relativeTo=options.relativeTo||"top";options.speed=options.speed||500;options.offset=options.offset||0;options.easing=options.easing||"swing";options.container=options.container||this.parent().attr("id");options.killSwitch=options.killSwitch||"killSwitch";options.onText=options.onText||"Turn Slide Off";options.offText=options.offText||"Turn Slide On";options.delay=options.delay||0;this.each(function(){new $.scrollFollow(this,options);});return this;};})(jQuery);
