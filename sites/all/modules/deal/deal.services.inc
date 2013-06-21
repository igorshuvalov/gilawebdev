<?php

/**
 * @file
 * This file implements the deal service resource call back functions.
 */

/**
* Pull the today's best deal list
* 
*/
function _today_best() {
  
  $ago_1day = strtotime('today') - 24 * 3600;
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0)
    ->condition('d.date_expiry', strtotime('now'), '>');
  
  $query->where("(SELECT SUM(dr.rate) rates FROM deal_rate AS dr WHERE dr.droid=d.did AND dr.rate_for='deal' AND dr.status=1 AND dr.date_posted > :ago_1day) > 0", array(':ago_1day' => $ago_1day));
  $query->leftJoin('{url_alias}', 'ua', 'd.url_pid=ua.pid');  
  $query->leftJoin('{deal_rate}', 'dr', "d.did=dr.droid AND dr.rate_for='deal' AND dr.status=1");
  $query->condition('dr.date_posted', $ago_1day, '>');
  $query->addExpression("SUM(dr.rate)", 'rates');
  $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
  $query
    ->fields('d')
    ->fields('ua')
    ->fields('u')
    ->groupBy('dr.droid')
    ->orderBy('rates', 'DESC');
  
  $deals = $query->execute()->fetchAll();
  
  _parse_deal_info($deals);
  
  return $deals;
  
}

/**
* Pull the new deal list
*/
function _new() {
  
  $ago_7days = strtotime('today') - 7 * 24 * 3600;
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0)
    ->condition('d.date_posted', $ago_7days, '>');
  $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
  $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
  $query
    ->fields('d')
    ->fields('ua')
    ->fields('u')
    ->orderBy('date_posted', 'DESC');
  
  $deals = $query->execute()->fetchAll();
  
  _parse_deal_info($deals);
  
  return $deals;
  
}

/**
* Pull the popular deal list
* 
*/
function _popular() {
  
  $ago_7days = strtotime('today') - 7 * 24 * 3600;
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0);
  $query->where("(SELECT SUM(dr.rate) rates FROM deal_rate AS dr WHERE dr.droid=d.did AND dr.rate_for='deal' AND dr.status=1 AND dr.date_posted > :ago_7days) > 0", array(':ago_7days' => $ago_7days));
  $query->leftJoin('{url_alias}', 'ua', 'd.url_pid=ua.pid');  
  $query->leftJoin('{deal_rate}', 'dr', "d.did=dr.droid AND dr.rate_for='deal' AND dr.status=1");
  $query->condition('dr.date_posted', $ago_7days, '>');
  $query->addExpression("SUM(dr.rate)", 'rates');
  $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
  $query
    ->fields('d')
    ->fields('ua')
    ->fields('u')
    ->groupBy('dr.droid')
    ->orderBy('rates', 'DESC');
  
  $deals = $query->execute()->fetchAll();
  
  _parse_deal_info($deals);
  
  return $deals;
  
}

/**
* Pull the deal's category list
* 
*/
function _category_items() {
  
  $categories = array();
  foreach (deal_categories() as $id => $category) {
    $categories[] = array(
      'id' => $id,
      'name' => $category,
    );
  }
  
  return $categories;
  
}

/**
* Pull the deal's location list
* 
*/
function _location_items() {
  
  $locations = array();
  foreach (deal_locations() as $id => $location) {
    $locations[] = array(
      'id' => $id,
      'name' => $location,
    );
  }
  
  return $locations;
  
}

/**
* Pull the deals list for specified category
* 
*/
function _category($id) {
  
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0)
    ->condition('d.category', $id);
  $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
  $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
  $query
    ->fields('d')
    ->fields('ua')
    ->fields('u')
    ->orderBy('date_posted', 'DESC');
  
  $deals = $query->execute()->fetchAll();
  
  _parse_deal_info($deals);
  
  return $deals;
  
}

/**
* Pull the deals list for specified location
* 
*/
function _location($id) {
  
  $query = db_select('{deal}', 'd')
    ->condition('d.disabled', 0)
    ->condition('d.location', $id);
  $query->leftJoin('{url_alias}', 'ua', 'd.url_pid = ua.pid');
  $query->leftJoin('{users}', 'u', 'd.duid=u.uid');
  $query
    ->fields('d')
    ->fields('ua')
    ->fields('u')
    ->orderBy('date_posted', 'DESC');
  
  $deals = $query->execute()->fetchAll();
  
  _parse_deal_info($deals);
  
  return $deals;
  
}

/**
* Pull the forums list.
* 
*/
function _forum() {
  
  $query = db_select('{node}', 'n')
    ->condition('n.status', 1)
    ->condition('n.type', 'forum');
  $query->leftJoin('{users}', 'u', 'n.uid=u.uid');
  $query
    ->fields('n')
    ->fields('u')
    ->orderBy('nid', 'ASC');
    
  $nodes = $query->execute()->fetchAll();
  
  return $nodes;
  
}

/**
* Pull the comments list.
* 
*/
function _comments($id) {
  
  $node = node_load($id);
  
  $comments = NULL;
  if ($cids = comment_get_thread($node, COMMENT_MODE_FLAT, 50)) {
    $comments = comment_load_multiple($cids);
  }
  
  return array('comments' => $comments);
  
}

function _parse_deal_info(&$deals) {
  
  foreach ($deals as &$item) {
    if (substr($item->deal_url, 0, 7) != 'http://' && substr($item->deal_url, 0, 8) != 'https://') {
      $item->deal_url = 'http://' . $item->deal_url;
    }
    
    if (time() > $item->date_expiry) {
      $item->expired = true;
    }
    
    if ($item->photo) {
      $photo = file_load($item->photo);
      $image_item = array(
        'style_name' => 'deal_thumbnail',
        'path' => $photo->uri,
        'width' => '120',
        'height' => '90',
        'alt' => $item->title,
        'title' => $item->title,
      );
      $item->photo = '<a href="' . file_create_url($photo->uri) . '" target="_blank">' . theme('image_style', $image_item) . '</a>';
    }
    else {
      $options = array(
        'url' => $item->deal_url,
        'link' => $item->deal_url,
        'size' => 's',
        'image_options' => array(
        ),
        'url_options' => array(
          'attributes' => array(
            'class' => array(''),
            'title' => $item->title,
            'target' => '_blank',
          )
        )
      );
      $item->photo = theme_pagepeeker_image($options);
    }
    
    $item->submitted = 'Submitted by ' . $item->name . ', ' . date('j M Y - g:i a', $item->date_posted);
    $item->description = nl2br($item->description);
    $item->date_start = date('Y-m-d', $item->date_start);
    $item->date_expiry = date('Y-m-d', $item->date_expiry);
    $item->category = deal_get_category_name($item->category);
    $item->location = deal_get_location_name($item->location);
    $item->rate_state = deal_load_rate($item->did, 'deal');
  }
  
}


