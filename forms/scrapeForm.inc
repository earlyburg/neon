<?php

/**
 * page callback
 */
function neon_scrape() {
  $scrapeform = backdrop_get_form('neon_scrape_form');
  $ret = backdrop_render($scrapeform);
  return $ret;
}

/**
 * Implements hook_form().
 */
function neon_scrape_form($form, &$form_state) {

  $config = config('neon.settings');
  $form = array();
  $form['neon_scrape']['url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => $config->get('scrp_url'),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => FALSE,
  );

  $form['neon_scrape']['depth'] = array(
    '#type' => 'textfield',
    '#title' => t('Nested Div Depth'),
    '#default_value' => $config->get('scrp_depth'),
    '#size' => 6,
    '#maxlength' => 16,
    '#required' => FALSE,
  );

  $form['neon_scrape']['specific_div'] = array(
    '#type' => 'textfield',
    '#title' => t('Specific Div'),
    '#default_value' => $config->get('scrp_spec_div'),
    '#size' => 20,
    '#maxlength' => 16,
    '#required' => FALSE,
  );

  $form['neon_scrape']['images'] = array(
    '#type' => 'checkbox',
    '#title' => t('Get all images.'),
    '#default_value' => $config->get('scrp_imgs'),
  );

  $form['neon_scrape']['links'] = array(
    '#type' => 'checkbox',
    '#title' => t('Get all links.'),
    '#default_value' => $config->get('scrp_lnks'),
  );

  $form['neon_scrape']['full'] = array(
    '#type' => 'checkbox',
    '#title' => t('Return entire page.'),
    '#default_value' => $config->get('scrp_page'),
  );

  $form['neon_scrape']['csv'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show links as CSV list.'),
    '#default_value' => $config->get('csv'),
  );

  $form['neon_scrape']['savenode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Save this data.'),
    '#default_value' => $config->get('save_node'),
  );

  $form['neon_scrape']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Implements hook_form_validate();
 */
function neon_scrape_form_validate($form, &$form_state) {

  $formValues = $form_state['values'];
  $config = config('neon.settings');

  if ( !empty($formValues['url']) ) {
    $url = $formValues['url'];
    $config->set('scrp_url', $url);
  } else {
    $config->set('scrp_url', "");
  }

  if ( !empty($formValues['depth']) ) {
    $depth = $formValues['depth'];
    $config->set('scrp_depth', $depth);
  } else {
    $config->set('scrp_depth', "");
  }

  if ( !empty($formValues['specific_div']) ) {
    $div = $formValues['specific_div'];
    $config->set('scrp_spec_div', $div);
  } else {
    $config->set('scrp_spec_div', "");
  }

  if ( $formValues['images'] == 1) {
    $config->set('scrp_imgs', 1);
  } else {
    $config->set('scrp_imgs', 0);
  }

  if ( $formValues['links'] == 1) {
    $config->set('scrp_lnks', 1);
  } else {
    $config->set('scrp_lnks', 0);
  }

  if ( $formValues['full'] == 1) {
    $config->set('scrp_page', 1);
  } else {
    $config->set('scrp_page', 0);
  }

  if ( $formValues['csv'] == 1) {
    $config->set('csv', 1);
  } else {
    $config->set('csv', 0);
  }

  if ( $formValues['savenode'] == 1) {
    $config->set('save_node', 1);
  } else {
    $config->set('save_node', 0);
  }
  $config->save();
}

/**
 * Implements hook_form_submit().
 */
function neon_scrape_form_submit($form, &$form_state) {

  $formValues = $form_state['values'];
  $return = neon_scrape_content($formValues);
  # save the content
  if ($formValues['savenode'] == 1) {
    $siteName = parse_url($formValues['url'], PHP_URL_HOST);
    $nid = neon_node_create($siteName, $return);
  }
  foreach ( $return as $element => $value) {

    switch ($element) {
        case ( 'full' ):
            dpm(array($value));
            break;
        case ( 'links' ):
            dpm($value);
            break;
        case ( 'images' ):
            dpm($value);
            break;
        case ( 'specific_div' ):
            dpm($value);
            break;
        case ( 'depth' ):
            dpm($value);
            break;
        case ( 'csv' ):
            dpm(array($value));
            break;
        default:
            dpm($value);
    }
  }
}