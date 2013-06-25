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
  
  $nodes = node_load_multiple(array(), array('type' => 'forum', 'status' => 1));
  parse_forum_info($nodes);
  
  return $nodes;
  
}

/**
* Pull the comments list.
* 
*/
function _comments($id) {
  
  $node = node_load($id);
  
  $comments = NULL;
  if ($cids = comment_get_thread($node, COMMENT_MODE_THREADED, 50)) {
    $comments = comment_load_multiple($cids);
    $comments_threaded = array();
    foreach ($cids as $id => $cid) {
      $comments_threaded[$id] = $comments[$cid];
    }
  }
  
  if ($comments_threaded) {
    foreach ($comments_threaded as &$comment) {
      if ($comment->pid) {
        $parent  = comment_load($comment->pid);
        $parent_body = $parent->comment_body['und'][0]['value'];
        $comment->submitted = t('Comment by !username in reply to "!parent_body !parent_user" on !datetime', array('!username' => $comment->name, '!parent_body' => $parent_body, '!parent_user' => $parent->name, '!datetime' => date('Y-m-d H:ia', $comment->created)));
      }
      else {
        $comment->submitted = t('Comment by !username on !datetime', array('!username' => $comment->name, '!datetime' => date('Y-m-d H:ia', $comment->created)));
      }
    }
  }
  
  return array('comments' => $comments_threaded);
  
}

/**
* Submit comment
* 
*/
function _comment_submit() {
  
  global $user;
  
  if (!$user->uid) {
    return array('result' => 'NO AUTHENTICATED');
  }
  else {
    $comment = (object) array(
      'nid' => $_POST['nid'],
      'cid' => 0,
      'pid' => $_POST['pid'],
      'uid' => $user->uid,
      'mail' => '',
      'is_anonymous' => 0,
      'homepage' => '',
      'status' => COMMENT_PUBLISHED,
      'subject' => $_POST['comment'],
      'language' => LANGUAGE_NONE,
      'comment_body' => array(
        LANGUAGE_NONE => array(
          0 => array (
            'value' => $_POST['comment'],
            'format' => 'filtered_html'
          )
        )
      ),
    );

    comment_submit($comment);
    comment_save($comment);
    
    return array('result' => 'SUCCESS');
  }
  
}

/**
* Submit deal
* 
*/
function _deal_submit() {
  
  global $user;
  
  if (!$user->uid) {
    return array('result' => 'NO AUTHENTICATED');
  }
  else {
    $errors = array();
    
    $deal_url = str_replace('http://', '', $_POST['deal_url']);
    $deal_url = str_replace('https://', '', $deal_url);
    $deal_url = str_replace('www.', '', $deal_url);
    
    $deal_domain = @parse_url('http://' . $deal_url, PHP_URL_HOST);
    $alias = 'deals/' . $deal_domain . '/' . deal_url_encode($_POST['title']);
    
    $query = db_select('{url_alias}', 'ua')
      ->condition('alias', $alias);
    $query->addExpression('COUNT(pid)');
    $has_alias = $query
      ->execute()
      ->fetchField();
    if ($has_alias) {
      $errors['Deal Page URL'] = t("Deal Page URL alias has been duplicated. Please check the Deal Title and Deal Page URL again.");
    }
    
    if (!$_POST['photo_automatic']) {
      // If required, validate the uploaded photo.
      $validator_photo = array(
        'file_validate_is_image'          => array(),
        'file_validate_image_resolution'  => array(),
        'file_validate_size'              => array(500 * 1024),
        'file_validate_extensions'        => array('png gif jpg jpeg'),
      );
      
      $photo_upload = file_save_upload('photo_upload', $validator_photo);
      if ($photo_upload === FALSE) {
        $errors['Upload Deal Photo'] = t("Failed to upload image. Please confirm file extension and size meets requirements and try again.");
      }
      elseif ($photo_upload !== NULL) {
        $_POST['photo_upload'] = $photo_upload;
      }
      else {
        $_POST['photo_upload'] = '';
      }
    }
    else {
      $_POST['photo_upload'] = '';
    }
    
    if ($_POST['coupon_code'] && !preg_match('/[a-zA-Z]/', $_POST['coupon_code'])) {
      $errors['Coupon Code'] = t("Coupon Code is invalid. Please put one or more alphanumeric characters.");
    }
    
    if (@strtotime($_POST['date_expiry']) < @strtotime($_POST['date_start'])) {
      $errors['Deal Expiry Date'] = t("Deal Expiry Date must be after the Deal Start Date.");
    }
    
    if (preg_match('/[^a-zA-Z0-9,\s]/', $_POST['tags'])) {
      $errors['Deal Tags'] = t("Tag/s entered are invalid. Please remove any special characters and re-submit.");
    }
    
    if (count($errors)) {
      return array(
        'result' => 'FAILED VALIDATION',
        'errors' => $errors,
      );
    }
    else {
      if ($_POST['representative'] == 'yes') {
        $_POST['representative'] = 1;
      }
      else {
        $_POST['representative'] = 0;
      }
      $form_state = array('values' => $_POST);
      deal_create_submit(null, $form_state);
      return array(
        'result' => 'SUCCESS',
      );
    }
  }
  
}

/**
* Prepare some the deal information
* 
* @param mixed $deals
*/
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

/**
* Prepare some the forum information
* 
* @param mixed $forum
*/
function parse_forum_info(&$forums) {
  
  foreach ($forums as &$item) {
    $item->submitted = 'Submitted by ' . $item->name . ', ' . date('j M Y - g:i a', $item->created);
    $item->description = nl2br($item->body['und'][0]['value']);    
  }
  
}
