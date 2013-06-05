<?php

/**
 * Validation Function to enforce numeric values
 */
function _tb_is_number($formelement, &$form_state) {
  $title = $formelement['#title'];
  if (!is_numeric($formelement['#value'])) {
    form_error($formelement, t("@title must be a number.", array('@title' => "<em>$title</em>")));
  }
}

/**
 * Validation Function to enforce hexadecimal values
 * @todo make the regex for the hex color recognition
 */
function _tb_is_hex_color($formelement, &$form_state) {
  return TRUE;
}
