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
  
  return $deals;
  
}

/**
* Create a deal
* 
* @param object $data
*/
function _deal_create($data) {
  
  return $data;
  
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
