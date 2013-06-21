<?php

/**
* Deal List for New Deals submitted in past 3 days
*/
function deal_new_items($key = NULL) {
  
  $ago_7days = strtotime('today') - 7 * 24 * 3600;
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0)
    ->condition('d.date_posted', $ago_7days, '>');
  
  switch($key) {
    case 'noexpired':
      $query->condition('d.date_expiry', strtotime('now'), '>');
      $filter_options = NULL;
      break;
    default:
      $filter_options = NULL;/*array(
        t('Hide Expired Deals') => 'deal/new/list/active',
      );*/
      break;
  }
    
  $count_query = clone $query;
  $count_query->addExpression('COUNT(d.did)');
  $query = $query->extend('PagerDefault');
  $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
  $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
  $query
    ->fields('d')
    ->fields('ua')
    ->fields('u')
    ->limit(10)
    ->orderBy('date_posted', 'DESC')
    ->setCountQuery($count_query);
  
  $deals = $query->execute()->fetchAllAssoc('did', PDO::FETCH_OBJ);
  
  return theme(
    'deal_list', 
    array(
      'list'            => $deals, 
      'pager'           => theme('pager'),
      'filter_options'  => $filter_options,
    )
  );
  
}

/**
* No expired new deals
* 
*/
function deal_new_items_noexpired() {
  
  return deal_new_items('noexpired');
  
}

/**
* Deal list for Popular Deals in the past 3 days
*/
function deal_popular_items($key = NULL) {
  
  $ago_7days = strtotime('today') - 7 * 24 * 3600;
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0);
    
  switch($key) {
    case 'noexpired':
      $query->condition('d.date_expiry', strtotime('now'), '>');
      $filter_options = NULL;
      break;
    default:
      $filter_options = array(
        t('Hide Expired Deals') => 'deal/popular/list/active',
      );
      break;
  }
  
  $query->where("(SELECT SUM(dr.rate) rates FROM deal_rate AS dr WHERE dr.droid=d.did AND dr.rate_for='deal' AND dr.status=1 AND dr.date_posted > :last_7days) > 0", array(':last_7days' => $ago_7days));
  $count_query = clone $query;
  $count_query->addExpression('COUNT(d.did)');  
  $query = $query->extend('PagerDefault');
  $query->leftJoin('{url_alias}', 'ua', 'd.url_pid=ua.pid');  
  $query->leftJoin('{deal_rate}', 'dr', "d.did=dr.droid AND dr.rate_for='deal' AND dr.status=1");
  $query->condition('dr.date_posted', $ago_7days, '>');
  $query->addExpression("SUM(dr.rate)", 'rates');
  $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
  $query
    ->fields('d')
    ->fields('ua')
    ->fields('u')
    ->limit(10)
    ->groupBy('dr.droid')
    ->orderBy('rates', 'DESC')
    ->setCountQuery($count_query);
  
  $deals = $query->execute()->fetchAllAssoc('did', PDO::FETCH_OBJ);
  
  return theme(
    'deal_list', 
    array(
      'list'            => $deals, 
      'pager'           => theme('pager'),
      'filter_options'  => $filter_options,
    )
  );
  
}

/**
* No expired popular deals
* 
*/
function deal_popular_items_noexpired() {
  
  return deal_popular_items('noexpired');
  
}

/**
* Deal List for Deals Ending Soon in next 3 days
*/
function deal_expiring_soon_items() {
  
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0)
    ->condition('d.date_expiry', time(), '>')
    ->condition('d.date_expiry', strtotime('today') + 8 * 24 * 3600, '<');
  $count_query = clone $query;
  $count_query->addExpression('COUNT(d.did)');
  $query = $query->extend('PagerDefault');
  $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
  $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
  $query
    ->fields('d')
    ->fields('ua')
    ->fields('u')
    ->limit(10)
    ->orderBy('date_posted', 'DESC')
    ->setCountQuery($count_query);
  
  $deals = $query->execute()->fetchAllAssoc('did', PDO::FETCH_OBJ);
  
  return theme('deal_list', array('list' => $deals, 'pager' => theme('pager')));
  
}

/**
* Deal List for Deals Starting Soon in the next 3 days
*/
function deal_starting_soon_items() {
  
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0)
    ->condition('d.date_start', time(), '>')
    ->condition('d.date_start', strtotime('today') + 7 * 24 * 3600, '<');
  $count_query = clone $query;
  $count_query->addExpression('COUNT(d.did)');
  $query = $query->extend('PagerDefault');
  $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
  $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
  $query
    ->fields('d')
    ->fields('ua')
    ->fields('u')
    ->limit(10)
    ->orderBy('date_posted', 'DESC')
    ->setCountQuery($count_query);
    
  $deals = $query->execute()->fetchAllAssoc('did', PDO::FETCH_OBJ);
  
  return theme('deal_list', array('list' => $deals, 'pager' => theme('pager')));
  
}

/**
* Deal categories
*/
function deal_category_view() {
  
  drupal_set_title(t('Deal Categories'));
  
  return theme('deal_category_list', array('list' => deal_categories()));
  
}

/**
* Deal list for specified category
*/
function deal_items_by_category($deal_category) {
  
  $deal_categories = deal_categories();
  foreach ($deal_categories as $id => $category) {
    if (deal_url_encode($category) == $deal_category) {
      $category_id = $id;
      $category_name = $category;
      break;
    }
  }
  
  if (!@$category_id)
    return '';
  
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0)
    ->condition('d.category', $category_id);
  $count_query = clone $query;
  $count_query->addExpression('COUNT(d.did)');
  $query = $query->extend('PagerDefault');
  $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
  $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
  $query
    ->fields('d')
    ->fields('ua')
    ->fields('u')
    ->limit(10)
    ->orderBy('date_posted', 'DESC')
    ->setCountQuery($count_query);
  
  $deals = $query->execute()->fetchAllAssoc('did', PDO::FETCH_OBJ);
  
  drupal_set_title(t('Deals for ' . $category_name));
  
  return theme('deal_list', array(
      'list' => $deals, 
      'filter_options' => array(
        t('New Deals') => 'deal/category/' . $deal_category . '/new',
        t('Popular Deals') => 'deal/category/' . $deal_category . '/popular',
        t('Deals Ending Soon') => 'deal/category/' . $deal_category . '/ending-soon',
        t('Deals Starting Soon') => 'deal/category/' . $deal_category . '/starting-soon',
      ),
      'pager' => theme('pager'),
  ));
  
}

/**
* Filtering deal items by category & (new, popular, ending soon, starting soon)
* 
* @param string $deal_category
*   Category name
* @param string $filter
*   Filter option like:
*     new, 
*     popluar
*     ending-soon
*     starting-soon
* @param string $key
*   advanced filter option like - 'noexpired'
*/
function deal_items_by_category_filter($deal_category, $filter, $key = NULL) {
  
  $deal_categories = deal_categories();
  foreach ($deal_categories as $id => $category) {
    if (deal_url_encode($category) == $deal_category) {
      $category_id = $id;
      $category_name = $category;
      break;
    }
  }
  
  if (!@$category_id)
    return '';
  
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0)
    ->condition('d.category', $category_id);
  
  switch($key) {
    case 'noexpired':
      $query->condition('d.date_expiry', strtotime('now'), '>');
      $filter_options = NULL;
      break;
    default:
      $filter_options = array(
        t('Hide Expired Deals') => 'deal/category/' . $deal_category . '/' . $filter . '/active',
      );
      break;
  }
  
  switch($filter) {
    case 'new':
      $subtitle = t('New Deals');
      $query->condition('d.date_posted', strtotime('today') - 7 * 24 * 3600, '>');
      $count_query = clone $query;
      $count_query->addExpression('COUNT(d.did)');
      $query = $query->extend('PagerDefault');
      $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
      $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
      $query
        ->fields('d')
        ->fields('ua')
        ->fields('u')
        ->limit(10)
        ->orderBy('date_posted', 'DESC')
        ->setCountQuery($count_query);
        
      $filter_options = NULL;
      break;
    case 'popular':
      $subtitle = t('Popular Deals');
      $ago_7days = strtotime('today') - 7 * 24 * 3600;
      $query->where("(SELECT SUM(dr.rate) rates FROM deal_rate AS dr WHERE dr.droid=d.did AND dr.rate_for='deal' AND dr.status=1 AND dr.date_posted > :last_7days) > 0", array(':last_7days' => $ago_7days));
      $count_query = clone $query;
      $count_query->addExpression('COUNT(d.did)');  
      $query = $query->extend('PagerDefault');
      $query->leftJoin('{url_alias}', 'ua', 'd.url_pid=ua.pid');  
      $query->leftJoin('{deal_rate}', 'dr', "d.did=dr.droid AND dr.rate_for='deal' AND dr.status=1");
      $query->condition('dr.date_posted', $ago_7days, '>');
      $query->addExpression("SUM(dr.rate)", 'rates');
      $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
      $query
        ->fields('d')
        ->fields('ua')
        ->fields('u')
        ->limit(10)
        ->groupBy('dr.droid')
        ->orderBy('rates', 'DESC')
        ->setCountQuery($count_query);
      break;
    case 'ending-soon':
      $subtitle = t('Deals Ending Soon');
      $query
        ->condition('d.date_expiry', time(), '>')
        ->condition('d.date_expiry', strtotime('today') + 8 * 24 * 3600, '<');
      $count_query = clone $query;
      $count_query->addExpression('COUNT(d.did)');
      $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
      $query = $query->extend('PagerDefault');
      $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
      $query
        ->fields('d')
        ->fields('ua')
        ->fields('u')
        ->limit(10)
        ->orderBy('date_posted', 'DESC')
        ->setCountQuery($count_query);
      break;
    case 'starting-soon':
      $subtitle = t('Deals Starting Soon');
      $query
        ->condition('d.date_start', time(), '>')
        ->condition('d.date_start', strtotime('today') + 7 * 24 * 3600, '<');
      $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
      $count_query = clone $query;
      $count_query->addExpression('COUNT(d.did)');
      $query = $query->extend('PagerDefault');
      $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
      $query
        ->fields('d')
        ->fields('ua')
        ->fields('u')
        ->limit(10)
        ->orderBy('date_posted', 'DESC')
        ->setCountQuery($count_query);
      break;
    default:
      $subtitle = '';
      $count_query = clone $query;
      $count_query->addExpression('COUNT(d.did)');
      $query = $query->extend('PagerDefault');
      $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
      $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
      $query
        ->fields('d')
        ->fields('ua')
        ->fields('u')
        ->limit(10)
        ->orderBy('date_posted', 'DESC')
        ->setCountQuery($count_query);
      break;
  }
  
  $deals = $query->execute()->fetchAllAssoc('did', PDO::FETCH_OBJ);
  
  drupal_set_title(t($subtitle . ' for ' . $category_name));
      
  return theme(
    'deal_list', 
    array(
      'list'            => $deals,
      'pager'           => theme('pager'),
      'filter_options'  => $filter_options,
    )
  );
  
}

/**
* Filtering no expired deal items by category & (new, popular, ending soon, starting soon)
* 
* @param string $deal_category
*   Category name
* @param string $filter
*   Filter option like:
*     new, 
*     popluar
*     ending-soon
*     starting-soon
*/
function deal_items_by_category_filter_noexpired($deal_category, $filter) {
  
  return deal_items_by_category_filter($deal_category, $filter, 'noexpired');
  
}

/**
* Deal locations
*/
function deal_location_view() {
  
  drupal_set_title(t('Deal Locations'));
  
  return theme('deal_location_list', array('list' => deal_locations()));

}

/**
* Deal list for specified location
*/
function deal_items_by_location($deal_location) {
  
  $deal_locations = deal_locations();
  foreach ($deal_locations as $id => $location) {
    if (deal_url_encode($location) == $deal_location) {
      $location_id = $id;
      $location_name = $location;
      break;
    }
  }
  
  if (!@$location_id)
    return '';
  
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0)
    ->condition('d.location', $location_id);
  $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
  $count_query = clone $query;
  $count_query->addExpression('COUNT(d.did)');
  $query = $query->extend('PagerDefault')->extend('TableSort');  
  $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
  $query
    ->fields('d')
    ->fields('ua')
    ->fields('u')
    ->limit(10)
    ->orderBy('date_posted', 'DESC')
    ->setCountQuery($count_query);
  
  $deals = $query->execute()->fetchAllAssoc('did', PDO::FETCH_OBJ);
  
  drupal_set_title(t('Deals for ' . $location_name));
  
  return theme('deal_list', array(
      'list' => $deals, 
      'filter_options' => array(
        t('New Deals') => 'deal/location/' . $deal_location . '/new',
        t('Popular Deals') => 'deal/location/' . $deal_location . '/popular',
        t('Deals Ending Soon') => 'deal/location/' . $deal_location . '/ending-soon',
        t('Deals Starting Soon') => 'deal/location/' . $deal_location . '/starting-soon',
      ),
      'pager' => theme('pager')
  ));
  
}

/**
* Filtering deal items by location & (new, popular, expiring soon, starting soon)
* 
* @param string $deal_location
*   Location name
* @param string $filter
*   Filter option like:
*     new, 
*     popluar
*     ending-soon
*     starting-soon
* @param string $key
*   advanced filter option like - 'noexpired'
*/
function deal_items_by_location_filter($deal_location, $filter, $key = NULL) {
  
  $deal_locations = deal_locations();
  foreach ($deal_locations as $id => $location) {
    if (deal_url_encode($location) == $deal_location) {
      $location_id = $id;
      $location_name = $location;
      break;
    }
  }
  
  if (!@$location_id)
    return '';
  
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0)
    ->condition('d.location', $location_id);
  
  switch($key) {
    case 'noexpired':
      $query->condition('d.date_expiry', strtotime('now'), '>');
      $filter_options = NULL;
      break;
    default:
      $filter_options = array(
        t('Hide Expired Deals') => 'deal/location/' . $deal_location . '/' . $filter . '/active',
      );
      break;
  }
  
  switch($filter) {
    case 'new':
      $subtitle = t('New Deals');
      $query->condition('d.date_posted', strtotime('today') - 7 * 24 * 3600, '>');
      $count_query = clone $query;
      $count_query->addExpression('COUNT(d.did)');
      $query = $query->extend('PagerDefault');
      $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
      $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
      $query
        ->fields('d')
        ->fields('ua')
        ->fields('u')
        ->limit(10)
        ->orderBy('date_posted', 'DESC')
        ->setCountQuery($count_query);
        
      $filter_options = NULL;
      break;
    case 'popular':
      $subtitle = t('Popular Deals');
      $ago_7days = strtotime('today') - 7 * 24 * 3600;
      $query->where("(SELECT SUM(dr.rate) rates FROM deal_rate AS dr WHERE dr.droid=d.did AND dr.rate_for='deal' AND dr.status=1 AND dr.date_posted > :last_7days) > 0", array(':last_7days' => $ago_7days));
      $count_query = clone $query;
      $count_query->addExpression('COUNT(d.did)');  
      $query = $query->extend('PagerDefault');
      $query->leftJoin('{url_alias}', 'ua', 'd.url_pid=ua.pid');  
      $query->leftJoin('{deal_rate}', 'dr', "d.did=dr.droid AND dr.rate_for='deal' AND dr.status=1");
      $query->condition('dr.date_posted', $ago_7days, '>');
      $query->addExpression("SUM(dr.rate)", 'rates');
      $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
      $query
        ->fields('d')
        ->fields('ua')
        ->fields('u')
        ->limit(10)
        ->groupBy('dr.droid')
        ->orderBy('rates', 'DESC')
        ->setCountQuery($count_query);
      break;
    case 'ending-soon':
      $subtitle = t('Deals Ending Soon');
      $query
        ->condition('d.date_expiry', time(), '>')
        ->condition('d.date_expiry', strtotime('today') + 8 * 24 * 3600, '<');
      $count_query = clone $query;
      $count_query->addExpression('COUNT(d.did)');
      $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
      $query = $query->extend('PagerDefault');
      $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
      $query
        ->fields('d')
        ->fields('ua')
        ->fields('u')
        ->limit(10)
        ->orderBy('date_posted', 'DESC')
        ->setCountQuery($count_query);
      break;
    case 'starting-soon':
      $subtitle = t('Deals Starting Soon');
      $query
        ->condition('d.date_start', time(), '>')
        ->condition('d.date_start', strtotime('today') + 7 * 24 * 3600, '<');
      $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
      $count_query = clone $query;
      $count_query->addExpression('COUNT(d.did)');
      $query = $query->extend('PagerDefault');
      $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
      $query
        ->fields('d')
        ->fields('ua')
        ->fields('u')
        ->limit(10)
        ->orderBy('date_posted', 'DESC')
        ->setCountQuery($count_query);
      break;
    default:
      $subtitle = '';
      $count_query = clone $query;
      $count_query->addExpression('COUNT(d.did)');
      $query = $query->extend('PagerDefault');
      $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
      $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
      $query
        ->fields('d')
        ->fields('ua')
        ->fields('u')
        ->limit(10)
        ->orderBy('date_posted', 'DESC')
        ->setCountQuery($count_query);
      break;
  }
  
  $deals = $query->execute()->fetchAllAssoc('did', PDO::FETCH_OBJ);
  
  drupal_set_title(t($subtitle . ' for ' . $location_name));
  
  return theme(
    'deal_list', 
    array(
      'list'            => $deals, 
      'pager'           => theme('pager'),
      'filter_options'  => $filter_options,
    )
  );
  
}

/**
* Filtering deal items by location & (new, popular, expiring soon, starting soon)
* 
* @param string $deal_location
*   Location name
* @param string $filter
*   Filter option like:
*     new, 
*     popluar
*     ending-soon
*     starting-soon
*/
function deal_items_by_location_filter_noexpired($deal_location, $filter) {
  
  return deal_items_by_location_filter($deal_location, $filter, 'noexpired');
  
}

/**
* Deal tags
* 
*/
function deal_tag_view() {
  
  $results = db_select('{deal}', 'd')
    ->fields('d', array('tags'))
    ->condition('d.disabled', 0)
    ->execute();
  
  $tags = array();
  foreach ($results as $tag) {
    $tags_array = explode(',', $tag->tags);
    $tags = array_merge($tags, $tags_array);
  }
  
  $tags = array_unique($tags);
  
  drupal_set_title(t('Deal Tags'));
  
  return theme('deal_tag_list', array('list' => $tags));
  
}

/**
* Deal list for specified tag
* 
* @param string $tag
*   tag name
* @param string $key
*   advanced filter option like - 'noexpired'
*/
function deal_items_by_tag($deal_tag, $key = NULL) {
  
  // Decoding deal tag alias to real tag name
  $deal_tag = str_replace('-', ' ', $deal_tag);
  
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0);
  
  switch($key) {
    case 'noexpired':
      drupal_set_title(t('Deal Tag - ' . $deal_tag . ' - Active Deals'));
      $query->condition('d.date_expiry', strtotime('now'), '>');
      $filter_options = NULL;
      break;
    default:
      drupal_set_title(t('Deal Tag - ' . $deal_tag));
      $filter_options = array(
        t('Hide Expired Deals') => 'deal/tag/' . $deal_tag . '/active',
      );
      break;
  }
  
  $query->where("CONCAT(',', d.tags, ',') LIKE :tag", array(':tag' => '%,' . $deal_tag . ',%'));
  $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
  $count_query = clone $query;
  $count_query->addExpression('COUNT(d.did)');
  $query = $query->extend('PagerDefault')->extend('TableSort');
  $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
  $query
    ->fields('d')
    ->fields('ua')
    ->fields('u')
    ->limit(10)
    ->orderBy('date_posted', 'DESC')
    ->setCountQuery($count_query);
  
  $deals = $query->execute()->fetchAllAssoc('did', PDO::FETCH_OBJ);
  
  return theme(
    'deal_list', 
    array(
      'list'            => $deals, 
      'pager'           => theme('pager'),
      'filter_options'  => $filter_options,
    )
  );
  
}

/**
* No expired deals list for specified tag
* 
* @param string $tag
*   tag name
*/
function deal_items_by_tag_noexpired($deal_tag) {
  
  return deal_items_by_tag($deal_tag, 'noexpired');
  
}

/**
* Handler of the deal vote action
* 
* @returns
*   NO AUTHENTICATED - No logged in users
*   SUCCESS - success to vote
*   FAILURE - failure to vote. In fact, that state will not be sent
*/
function deal_vote_action() {
  
  global $user;
  
  if (!$user->uid) {
    drupal_set_message(t('You must Sign In to vote.'), 'status');
    return drupal_json_output(array(
      'result' => 'NO AUTHENTICATED',
      'redirect' => url('user/login'),
    ));
  }
  
  $rates = db_select('{deal_rate}', 'dr')
    ->fields('dr')
    ->condition('dr.druid', $user->uid)
    ->condition('dr.droid', $_REQUEST['id'])
    ->condition('dr.rate_for', $_REQUEST['object'])
    ->execute()
    ->fetchAllAssoc('drid', PDO::FETCH_OBJ);
  
  if (!count($rates)) {
    $drid = db_insert('{deal_rate}')
      ->fields(array(
        'droid' => $_REQUEST['id'],
        'druid' => $user->uid,
        'rate_for'  => $_REQUEST['object'],
        'rate'      => ($_REQUEST['type'] == 'plus' ? 1 : -1),
        'date_posted' => time(),
        'status'      => 1
      ))
      ->execute();
    
    $rate_state = deal_load_rate($_REQUEST['id'], $_REQUEST['object']);
    
    return drupal_json_output(array(
      'result'  => 'SUCCESS',
      'state'  => $rate_state,
    ));
  }
  else {
    $rate = reset($rates);
    if ($rate->status == -1) { // Vote cancelled by user
      db_update('{deal_rate}')
        ->fields(array(
          'rate'        => ($_REQUEST['type'] == 'plus' ? 1 : -1),
          'date_posted' => time(),
          'status'      => 1,
        ))
        ->condition('druid', $user->uid)
        ->condition('droid', $_REQUEST['id'])
        ->condition('rate_for', $_REQUEST['object'])
        ->execute();
        
      $rate_state = deal_load_rate($_REQUEST['id'], $_REQUEST['object']);
    
      return drupal_json_output(array(
        'result'  => 'SUCCESS',
        'state'  => $rate_state,
      ));
    }
    else {
      return drupal_json_output(array(
        'result'  => 'FAILURE'
      ));
    }
  }
  
}

/**
* Handler of the deal vote cancel action
* 
* @returns
*   NO AUTHENTICATED - No logged in users
*   SUCCESS - success to vote
*/
function deal_vote_cancel_action() {
  
  global $user;
  
  if (!$user->uid) {
    drupal_set_message(t('You must Sign In to vote.'), 'status');
    return drupal_json_output(array(
      'result' => 'NO AUTHENTICATED',
      'redirect' => url('user/login'),
    ));
  }
  
  $rate = deal_load_rate_state($_REQUEST['id'], $_REQUEST['object']);
  if (!$rate) {
    return drupal_json_output(array(
      'result' => 'FAILURE'
    ));
  }
  else {
    db_update('{deal_rate}')
      ->fields(array(
        'status' => -1
      ))
      ->condition('droid', $_REQUEST['id'])
      ->condition('druid', $user->uid)
      ->condition('rate_for', $_REQUEST['object'])
      ->execute();
    
    $rate_state = deal_load_rate($_REQUEST['id'], $_REQUEST['object']);
    
    return drupal_json_output(array(
      'result'  => 'SUCCESS',
      'state'  => $rate_state,
    ));
  }
  
}

/**
* Display votes 
* 
* @param int $id
*   Deal id
* @param string $object_type
*   Object type for Deal
*/
function deal_votes_view($id, $object_type) {
  
  global $user;
  
  if (!$user->uid) {
    drupal_set_message(t('You must Sign In to vote.'), 'status');
    drupal_goto('user/login');
    return;
  }
  
  $query = db_select('{deal_rate}', 'dr');
  $query->leftJoin('{users}', 'u', 'dr.druid = u.uid');
  $query->fields('dr')
    ->fields('u', array('uid', 'name'))
    ->condition('dr.droid', $id)
    ->condition('dr.rate_for', $object_type);
  
  $rates = $query->orderBy('date_posted')
    ->execute()
    ->fetchAllAssoc('drid', PDO::FETCH_OBJ);
    
  switch($object_type) {
    case 'deal':
      $object = deal_load($id);
      drupal_set_title('Votes for : ' . $object->title);
      break;
  }
  
  $output = '<table cellpadding=0 cellspacing=0>';
  if (!count($rates)) {
    $output .= '<tr><td class="td-fourth">' . t('There are no vote/s for this content.') . '</td></tr>';
  }
  foreach ($rates as $rate) {
    $output .= '<tr>';
    $output .= '<td class="td-first" align="center">' . ($rate->rate == 1 ? '+' : '-') . '</td>';
    $output .= '<td class="td-second"><a href="' . url('user/' . $rate->uid) . '">' . $rate->name . '</a></td>';
    $output .= '<td class="td-third">' . date('j M Y - g:i a', $rate->date_posted) . '</td>';
    $output .= '<td class="td-fourth">' . ($rate->status == 1 ? 'Voted' : 'Cancelled') . '</td>';
    $output .= '</tr>';
  }
  $output .= '</table>';
  
  $output .= '
    <style>
      table {border: 1px solid #CCCCCC; border-width: 1px 1px 0px;}
      table tr {}
      table tr td {font-size: 12px; margin: 0; padding: 1px 5px 0 5px;}
      table tr td.td-first {border: 1px solid #CCCCCC;border-width: 0px 1px 1px 0px;}
      table tr td.td-second {border: 1px solid #CCCCCC; border-width: 0px 1px 1px 0px;}
      table tr td.td-third {border: 1px solid #CCCCCC; border-width: 0px 1px 1px 0px;}
      table tr td.td-fourth {border: 1px solid #CCCCCC; border-width: 0px 0px 1px 0px;}
    </style>
  ';
  
  return $output;
  
}

/**
* Display live action page for first loading
* 
*/
function deal_live_create() {
  
  return deal_live(
    'create',
    array(
      'post'    => true,
      'comment' => true,
      'vote'    => true,
      'timestamp' => 0,
    )
  );
  
}

/**
* Display live action page for type filters
* 
*/
function deal_live_filter() {
  
  return deal_live(
    'filter',
    array(
      'post'    => $_REQUEST['post'] == 'true',
      'comment' => $_REQUEST['comment'] == 'true',
      'vote'    => $_REQUEST['vote'] == 'true',
      'timestamp' => 0,
    )
  );
  
}

/**
* Display live action page for updates
* 
*/
function deal_live_update() {
  
  return deal_live(
    'update',
    array(
      'post'      => $_REQUEST['post'] == 'true',
      'comment'   => $_REQUEST['comment'] == 'true',
      'vote'      => $_REQUEST['vote'] == 'true',
      'timestamp' => $_REQUEST['timestamp'],
    )
  );
  
}

/**
* Live view feature
* 
* @param string $action_type
*   'create' : loading page first
*   'filter' : when user click filter option
*   'update' : updating timer
* @param array $action_keys
*   post : events for deal & forum & pages
*   comment : events for comment
*   vote : events for voting
*   timestamp : last updates time
*/
function deal_live($action_type, $action_keys) {
  
  $nodes = array();
  $comments = array();
  $votes = array();
  
  $event_limit = 25;
  
  if ($action_keys['post']) {
    $nodes_query = db_select('{node}', 'n');
    $nodes_query->condition('status', '1');
    if ($action_type == 'update') {
      //$nodes_query->condition('created', $action_keys['timestamp'], '>');
    }
    $nodes_query->fields('n');
    $nodes_query->range(0, $event_limit);
    $nodes_query->orderBy('created', 'DESC');
    $nodes = $nodes_query
      ->execute()
      ->fetchAllAssoc('nid', PDO::FETCH_OBJ);
  }
  
  if ($action_keys['comment']) {
    $comments_query = db_select('{comment}', 'c');
    $comments_query->condition('status', '1');
    if ($action_type == 'update') {
      //$comments_query->condition('created', $action_keys['timestamp'], '>');
    }
    $comments_query->fields('c');
    $comments_query->range(0, $event_limit);
    $comments_query->orderBy('created', 'DESC');
    $comments = $comments_query
      ->execute()
      ->fetchAllAssoc('cid', PDO::FETCH_OBJ);
  }
    
  if ($action_keys['vote']) {
    $votes_query = db_select('{deal_rate}', 'dr');
    $votes_query->condition('status', '1');
    if ($action_type == 'update') {
      //$votes_query->condition('date_posted', $action_keys['timestamp'], '>');
    }
    $votes_query->fields('dr');
    $votes_query->range(0, $event_limit);
    $votes_query->orderBy('date_posted', 'DESC');
    $votes = $votes_query
      ->execute()
      ->fetchAllAssoc('drid', PDO::FETCH_OBJ);
  }
  
  $actions = array_merge($nodes, $comments, $votes);
  
  usort($actions, '_cmp_created');
  
  $output = '';
  $last_timestamp = $action_keys['timestamp'];
  
  foreach ($actions as $key => $action) {
    if (isset($action->vid)) { // If node object
      $created = $action->created;
      $uid = $action->uid;
      $action_name = 'post';
      $node = node_load($action->nid);
      $title = '<a href="' . url('node/' . $node->nid) . '">' . $node->title . '</a>';
      $type = $action->type;
    }
    else if (isset($action->cid)) { // If comment object
      $created = $action->created;
      $uid = $action->uid;
      $action_name = 'comment';
      $node = node_load($action->nid);
      $comment = comment_load($action->cid);
      $uri = entity_uri('comment', $comment);
      $uri['options'] += array('attributes' => array('rel' => 'bookmark'));
      $title = l($node->title, $uri['path'], $uri['options']);
      $type = 'comment';
    }
    else if (isset($action->drid)) { // If vote object
      $created = $action->date_posted;
      $uid = $action->druid;
      if ($action->rate == 1) {
        $action_name = '+1';
      }
      else if ($action->rate == -1) {
        $action_name = '-1';
      }
      $deal = deal_load($action->droid);
      $title = '<a href="' . url('node/' . $deal->dnid) . '">' . $deal->title . '</a>';
      $type = 'vote';
    }
    
    $before_created = strtotime('now') - $created;
    if ($before_created < 60) {
      $time = $before_created . ' sec ago';
    }
    else if ($before_created < 3600) {
      $time = (int)($before_created / 60) . ' min ago';
    }
    else if ($created > strtotime('today')) {
      $time = 'Today ' . date('H:i', $created);
    }
    else {
      $time = date('Y/m/d H:i', $created);
    }
    
    $user_info = user_load($uid);
    $user = l($user_info->name, 'user/' . $uid);
    
    $output .= '<div class="live-item' . ($action_keys['timestamp'] < $created ? ' new' : '') . '">';
    $output .= '<div class="live-column column-time">' . $time . '</div>';
    $output .= '<div class="live-column column-user">' . $user . '</div>';
    $output .= '<div class="live-column column-action">' . $action_name . '</div>';
    $output .= '<div class="live-column column-subject">' . $title . '</div>';
    $output .= '<div class="live-column column-type">' . $type . '</div>';
    $output .= '</div>';
    
    if ($last_timestamp < $created)
      $last_timestamp = $created;
    
    if ($key == ($event_limit - 1))
      break;
  }
  
  $output .= '';
  
  switch ($action_type) {
    case 'create':
      return theme('deal_live_action',
        array(
          'action_type'   => $action_type,
          'content'       => $output,
          'timestamp'     => $last_timestamp,
        )
      );
      break;
    case 'filter':
      return drupal_json_output(
        array(
          'html' => theme('deal_live_action',
            array(
              'action_type' => $action_type,
              'content'     => $output,
            )
          ),
          'timestamp' => $last_timestamp,
        )
      );      
      break;
    case 'update':
      return drupal_json_output(
        array(
          'html' => theme('deal_live_action',
            array(
              'action_type' => $action_type,
              'content'     => $output,
            )
          ),
          'timestamp' => $last_timestamp,
        )
      );      
      break;
  }
  
}

/**
* callback for comparing action posts created date
* 
* @param mixed $action1
* @param mixed $action2
*/
function _cmp_created($action1, $action2) {
  
  $created1 = isset($action1->created) ? $action1->created : $action1->date_posted;
  $created2 = isset($action2->created) ? $action2->created : $action2->date_posted;
  
  if ($created1 > $created2) {
    return FALSE;
  }
  
  return TRUE;
  
}