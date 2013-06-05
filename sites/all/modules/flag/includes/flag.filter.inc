<?php

/**
* Filtering node flagged
* 
*/
function flag_filter_node_flagged() {
  
  $header = array(
    'flag_title'    => array('data' => t('Flag Title'), 'field' => 'f.title'),
    'flag_name'     => array('data' => t('Flag Name'), 'field' => 'f.name'),
    'content_type'  => array('data' => t('Content Type')),
    'content_title' => array('data' => t('Content')),
    'user'          => array('data' => t('User'), 'field' => 'u.uid'),
    'flagged_date'  => array('data' => t('Date')),
  );
  
  $query = db_select('{flag_content}', 'fc');
  $query->condition('fc.content_type', 'node');
  $query->innerJoin('{flags}', 'f', 'f.fid = fc.fid');
  $count_query = clone $query;
  $count_query->addExpression('COUNT(fc.fcid)');

  $query = $query->extend('PagerDefault')->extend('TableSort');
  $query->leftJoin('{node}', 'n', "fc.content_id = n.nid");
  $query
    ->fields('f', array('fid', 'name', 'title', 'options'))
    ->fields('fc', array('fcid', 'content_type', 'content_id', 'uid', 'timestamp'))
    ->fields('n', array('nid', 'type', 'title'))
    ->limit(10)
    ->orderByHeader($header)
    ->setCountQuery($count_query);
  $flags = $query->execute();
  
  $options = array();
  foreach ($flags as $flag) {
    $node = node_load($flag->nid);
    $content_title = array(
      'data' => array(
        '#type' => 'link', 
        '#title' => $node->title, 
        '#href' => drupal_lookup_path('alias',"node/".$node->nid),
      )
    );
    $content_type = $flag->type;
    
    $user = user_load($flag->uid);
    
    $options[$flag->fid] = array(
      'flag_title'    => $flag->title,
      'flag_name'     => $flag->name,
      'content_type'  => $content_type,
      'content_title' => $content_title,
      'user'          => array('data' => array('#type' => 'link', '#title' => $user->name, '#href' => "user/$user->uid")),
      'flagged_date'  => date('m/d/Y g:i a', $flag->timestamp),
    );
  }

  $output = theme('table', array('header' => $header,'rows' => $options));
  $output .= theme('pager');
  
  return $output;
  
}

/**
* Filtering comment flagged
* 
*/
function flag_filter_comment_flagged() {
  
  $header = array(
    'flag_title'    => array('data' => t('Flag Title'), 'field' => 'f.title'),
    'flag_name'     => array('data' => t('Flag Name'), 'field' => 'f.name'),
    'content_title' => array('data' => t('Content')),
    'user'          => array('data' => t('User'), 'field' => 'u.uid'),
    'flagged_date'  => array('data' => t('Date')),
  );
  
  $query = db_select('{flag_content}', 'fc');
  $query->condition('fc.content_type', 'comment');
  $query->innerJoin('{flags}', 'f', 'f.fid = fc.fid');
  $count_query = clone $query;
  $count_query->addExpression('COUNT(fc.fcid)');

  $query = $query->extend('PagerDefault')->extend('TableSort');
  $query->leftJoin('{comment}', 'c', "fc.content_id = c.cid");  
  $query
    ->fields('f', array('fid', 'name', 'title', 'options'))
    ->fields('fc', array('fcid', 'content_type', 'content_id', 'uid', 'timestamp'))
    ->fields('c', array('cid'))
    ->limit(10)
    ->orderByHeader($header)
    ->setCountQuery($count_query);
  $flags = $query->execute();
  
  $options = array();
  foreach ($flags as $flag) {
    $comment = comment_load($flag->cid);
    $comment_body = field_get_items('comment', $comment, 'comment_body');
    $content_title = array(
      'data' => array(
        '#type' => 'link',
        '#title' => $comment->subject,
        '#href' => 'comment/' . $comment->cid,
        '#options' => array('attributes' => array('title' => truncate_utf8($comment_body[0]['value'], 128)), 'fragment' => 'comment-' . $comment->cid),
      )
    );
    
    $user = user_load($flag->uid);
    
    $options[$flag->fid] = array(
      'flag_title'    => $flag->title,
      'flag_name'     => $flag->name,
      'content_title' => $content_title,
      'user'          => array('data' => array('#type' => 'link', '#title' => $user->name, '#href' => "user/$user->uid")),
      'flagged_date'  => date('m/d/Y g:i a', $flag->timestamp),
    );
  }

  $output = theme('table', array('header' => $header,'rows' => $options));
  $output .= theme('pager');
  
  return $output;
  
}
