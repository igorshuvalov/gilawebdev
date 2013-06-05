<?php

/**
* Deal List for New Deals submitted in past 3 days
*/
function deal_new_items($key = NULL) {
  
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0)
    ->condition('d.date_posted', strtotime('today') - 3 * 24 * 3600, '>');
  
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
  
  $ago_3days = strtotime('today') - 3 * 24 * 3600;
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
  
  $query->where("(SELECT SUM(dr.rate) rates FROM deal_rate AS dr WHERE dr.droid=d.did AND dr.rate_for='deal' AND dr.status=1 AND dr.date_posted > :last_3days) > 0", array(':last_3days' => $ago_3days));
  $count_query = clone $query;
  $count_query->addExpression('COUNT(d.did)');  
  $query = $query->extend('PagerDefault');
  $query->leftJoin('{url_alias}', 'ua', 'd.url_pid=ua.pid');  
  $query->leftJoin('{deal_rate}', 'dr', "d.did=dr.droid AND dr.rate_for='deal' AND dr.status=1");
  $query->condition('dr.date_posted', $ago_3days, '>');
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
    ->condition('d.date_expiry', strtotime('today') + 4 * 24 * 3600, '<');
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
    ->condition('d.date_start', strtotime('today') + 3 * 24 * 3600, '<');
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
      $query->condition('d.date_posted', strtotime('today') - 3 * 24 * 3600, '>');
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
    case 'popular':
      $subtitle = t('Popular Deals');
      $ago_3days = strtotime('today') - 3 * 24 * 3600;
      $query->where("(SELECT SUM(dr.rate) rates FROM deal_rate AS dr WHERE dr.droid=d.did AND dr.rate_for='deal' AND dr.status=1 AND dr.date_posted > :last_3days) > 0", array(':last_3days' => $ago_3days));
      $count_query = clone $query;
      $count_query->addExpression('COUNT(d.did)');  
      $query = $query->extend('PagerDefault');
      $query->leftJoin('{url_alias}', 'ua', 'd.url_pid=ua.pid');  
      $query->leftJoin('{deal_rate}', 'dr', "d.did=dr.droid AND dr.rate_for='deal' AND dr.status=1");
      $query->condition('dr.date_posted', $ago_3days, '>');
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
        ->condition('d.date_expiry', strtotime('today') + 4 * 24 * 3600, '<');
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
        ->condition('d.date_start', strtotime('today') + 3 * 24 * 3600, '<');
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
  
  drupal_set_title(t('Deals for ' . $category_name) . ':' . $subtitle);
      
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
      $query->condition('d.date_posted', strtotime('today') - 3 * 24 * 3600, '>');
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
    case 'popular':
      $subtitle = t('Popular Deals');
      $ago_3days = strtotime('today') - 3 * 24 * 3600;
      $query->where("(SELECT SUM(dr.rate) rates FROM deal_rate AS dr WHERE dr.droid=d.did AND dr.rate_for='deal' AND dr.status=1 AND dr.date_posted > :last_3days) > 0", array(':last_3days' => $ago_3days));
      $count_query = clone $query;
      $count_query->addExpression('COUNT(d.did)');  
      $query = $query->extend('PagerDefault');
      $query->leftJoin('{url_alias}', 'ua', 'd.url_pid=ua.pid');  
      $query->leftJoin('{deal_rate}', 'dr', "d.did=dr.droid AND dr.rate_for='deal' AND dr.status=1");
      $query->condition('dr.date_posted', $ago_3days, '>');
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
        ->condition('d.date_expiry', strtotime('today') + 4 * 24 * 3600, '<');
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
        ->condition('d.date_start', strtotime('today') + 3 * 24 * 3600, '<');
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
  
  drupal_set_title(t('Deals for ' . $location_name . ':' . $subtitle));
  
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
      $query->condition('d.date_expiry', strtotime('now'), '>');
      $filter_options = NULL;
      break;
    default:
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
  
  drupal_set_title(t('Deal Tag - ' . $deal_tag));
  
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