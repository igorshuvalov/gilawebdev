<?php

/**
* Build deal list including pagination & ordering
* 
*/
function deal_list_form() {
  
  $header = array(
    'title'       => array('data' => t('Title'), 'field' => 'd.title'),
    'rate'        => array('data' => t('Rate')),
    'user'        => array('data' => t('User'), 'field' => 'd.duid'),
    'photo'       => array('data' => t('Photo')),
    'deal_url'    => array('data' => t('Deal URL')),
    'date_posted' => array('data' => t('Posted Date'), 'field' => 'd.date_posted'),
    'date_start'  => array('data' => t('Start Date'), 'field' => 'd.date_start'),
    'date_expiry' => array('data' => t('Expiry Date'), 'field' => 'd.date_expiry'),
    'status'      => array('data' => t('Status'), 'field' => 'd.disabled'),
    'operations'  => array('data' => t('Operations')),
  );
  
  $query = db_select('{deal}', 'd');
  $query->leftJoin('{users}', 'u', 'd.duid = u.uid');
  $count_query = clone $query;
  $count_query->addExpression('COUNT(d.did)');

  $query = $query->extend('PagerDefault')->extend('TableSort');
  $query
    ->fields('d')
    ->fields('u')
    ->limit(10)
    ->orderByHeader($header)
    ->setCountQuery($count_query);
  $deals = $query->execute();
  
  $options = array();
  foreach ($deals as $deal) {
    $rate = deal_load_rate($deal->did, 'deal');
    $height = ($rate['plus'] + $rate['minus'] + $rate['plus_cancelled'] + $rate['minus_cancelled']) * 23 + 20;
    $height = ($height < 30 ? 43 : $height);
    @$photo = file_load($deal->photo);
    $options[$deal->did] = array(
      'title'       => array('data' => array('#type' => 'link', '#title' => $deal->title, '#href' => "deal/$deal->did")),
      'rate'        => l('+' . $rate['plus'] . ' -' . $rate['minus'], 'admin/deal/' . $deal->did . '/votes/deal', array('attributes' => array('rel' => 'lightframe[group|width: 520px; height: ' . $height . 'px;]'))),
      'user'        => array('data' => array('#type' => 'link', '#title' => $deal->name, '#href' => "user/$deal->duid")),
      'photo'       => $photo ? theme('image', array('path' => $photo->uri, 'alt' => $deal->title, 'title' => $deal->title, 'width' => '50')) : '',
      'deal_url'    => array('data' => array('#type' => 'link', '#title' => $deal->deal_url, '#href' => 'http://' . $deal->deal_url, '#attributes' => array('target' => '_blank'))),
      'date_posted' => date('m/d/Y', $deal->date_posted),
      'date_start'  => $deal->date_start ? date('m/d/Y', $deal->date_start) : 'N/A',
      'date_expiry' => $deal->date_expiry ? date('m/d/Y', $deal->date_expiry) : 'N/A',
      'status'      => $deal->disabled ? 'Disabled' : 'Activated',
      'operations'  => array('data' => array('#type' => 'link', '#title' => t('edit'), '#href' => "node/$deal->dnid/edit")),
    );
  }

  $output = theme('table', array('header' => $header,'rows' => $options));
  $output .= theme('pager');
  
  return $output;
  
}

/**
* Display votes popup
* 
* @param int $id
*   Deal id
* @param string $object_type
*   Object type for Deal
*/
function deal_votes_view_popup($id, $object_type) {
  
  $query = db_select('{deal_rate}', 'dr');
  $query->leftJoin('{users}', 'u', 'dr.druid = u.uid');
  $query->fields('dr')
    ->fields('u', array('uid', 'name'))
    ->condition('dr.droid', $id)
    ->condition('dr.rate_for', $object_type);
  
  $rates = $query->orderBy('date_posted')
    ->execute()
    ->fetchAllAssoc('drid', PDO::FETCH_OBJ);
  
  $output = '<table cellpadding=0 cellspacing=0>';
  if (!count($rates)) {
    $output .= '<tr><td class="td-fourth">' . t('No votes received yet - Vote now!') . '</td></tr>';
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
      table {border: 1px solid #CCCCCC; border-width: 1px 1px 0px; width: 500px; background: #FFF;}
      table tr {}
      table tr td {font-size: 12px; margin: 0; padding: 1px 5px 0 5px; height: 21px;}
      table tr td.td-first {border: 1px solid #CCCCCC;border-width: 0px 1px 1px 0px;}
      table tr td.td-second {border: 1px solid #CCCCCC; border-width: 0px 1px 1px 0px;}
      table tr td.td-third {border: 1px solid #CCCCCC; border-width: 0px 1px 1px 0px;}
      table tr td.td-fourth {border: 1px solid #CCCCCC; border-width: 0px 0px 1px 0px;}
    </style>
  ';
  
  die($output);
  
}
