<?php
/**
 * @file
 * haiku_custom_content.features.inc
 */

/**
 * Implements hook_views_api().
 */
function haiku_custom_content_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function haiku_custom_content_node_info() {
  $items = array(
    'portfolio_item' => array(
      'name' => t('Portfolio item'),
      'base' => 'node_content',
      'description' => t('Use to create and manage your portfolio items. '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
