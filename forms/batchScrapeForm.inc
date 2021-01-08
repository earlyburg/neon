<?php

/**
 * page callback
 */
function neon_URL_scrape() {
  $scrapeform = backdrop_get_form('neon_URL_scrape_form');
  $ret = backdrop_render($scrapeform);
  return $ret;
}

/**
 * Implements hook_form().
 */
function neon_URL_scrape_form($form, &$form_state) {
  $form = array();
  $config = config('neon.batch.settings');
  $NeonBatch = new NeonBatch();

  $form['#config'] = 'neon.batch.settings';
  $form['neon_URL_scrape']['url_list'] = array(
    '#type' => 'textarea',
    '#title' => t('Comma separated URL list'),
    '#default_value' => $NeonBatch->fetch(),
    '#size' => 60,
    '#required' => FALSE,
  );

  $form['neon_URL_scrape']['list_save'] = array(
    '#type' => 'checkbox',
    '#title' => t('Save Batch List.'),
    '#description' => t('Save a batch list without processing it.'),
    '#default_value' => $config->get('scrp_save'),
  );

  $form['neon_URL_scrape']['run_batch'] = array(
    '#type' => 'checkbox',
    '#title' => t('Run batch.'),
    '#description' => t('Immidiately process this batch job, save the results as node content.'),
    '#default_value' => $config->get('batch_run'),
  );

  $form['neon_URL_scrape']['images'] = array(
    '#type' => 'checkbox',
    '#title' => t('Get all images.'),
    '#default_value' => $config->get('scrp_imgs'),
  );

  $form['neon_URL_scrape']['links'] = array(
    '#type' => 'checkbox',
    '#title' => t('Get all links.'),
    '#default_value' => $config->get('scrp_lnks'),
  );

  $form['neon_URL_scrape']['full'] = array(
    '#type' => 'checkbox',
    '#title' => t('Return entire page.'),
    '#default_value' => $config->get('scrp_page'),
  );

  $form['neon_URL_scrape']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['#submit'][] = 'neon_URL_scrape_form_submit';

  return $form;
}

/**
 * Impliments hook_form_validate().
 */
function neon_URL_scrape_form_validate($form, &$form_state) {

  $formValues = $form_state['values'];
  $config = config('neon.batch.settings');

  if ( $formValues['list_save'] == 1) {
    $config->set('scrp_save', 1);
  } else {
    $config->set('scrp_save', 0);
  }

  if ( $formValues['run_batch'] == 1) {
    $config->set('batch_run', 1);
  } else {
    $config->set('batch_run', 0);
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

  $config->save();
}

/**
 * Impliments hook_form_submit().
 */
function neon_URL_scrape_form_submit($form, &$form_state) {

  $formValues = $form_state['values'];
  $NeonBatch = new NeonBatch();

  if ($formValues['list_save'] == 1) {
    if($NeonBatch->check()) {
      $NeonBatch->update($formValues['url_list']);
    } else {
      $NeonBatch->create();
      $NeonBatch->update($formValues['url_list']);
    }

    if ($formValues['run_batch'] == 1) {
    neon_process_batch();
    config_set('neon.batch.settings', 'batch_run', 0);
    }
  }
  else {
    $NeonBatch->delete();
  }
}