(function(e,t,n){"use strict";var r=e(document),i=t.Modernizr;e(document).ready(function(){e.fn.foundationAlerts?r.foundationAlerts():null;e.fn.foundationButtons?r.foundationButtons():null;e.fn.foundationAccordion?r.foundationAccordion():null;e.fn.foundationNavigation?r.foundationNavigation():null;e.fn.foundationTopBar?r.foundationTopBar():null;e.fn.foundationCustomForms?r.foundationCustomForms():null;e.fn.foundationMediaQueryViewer?r.foundationMediaQueryViewer():null;e.fn.foundationTabs?r.foundationTabs({callback:e.foundation.customForms.appendCustomMarkup}):null;e.fn.foundationTooltips?r.foundationTooltips():null;e.fn.foundationMagellan?r.foundationMagellan():null;e.fn.foundationClearing?r.foundationClearing():null;e.fn.placeholder?e("input, textarea").placeholder():null});if(i.touch&&!t.location.hash){e(t).load(function(){setTimeout(function(){t.scrollTo(0,1)},0)})}})(jQuery,this)