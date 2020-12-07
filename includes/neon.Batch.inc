<?php

class NeonBatch {

  function __construct() {
    global $user;
    $this->id = $user->uid;
  }


  public function check() {
    $id = db_query('SELECT id FROM {neon_batch} WHERE id = :id', array(
      ':id' => $this->id,
    ))->fetchField();
    return $id;
  }


  public function create() {
    $ret = db_insert('neon_batch')
      ->fields(array(
        'id' => $this->id,
        'batch' => '',
      ))->execute();
    return $ret;
  }


  public function delete() {
    $ret = db_delete('neon_batch')
      ->condition('id', $this->id)
      ->execute();
    return $ret;
  }


  public function update($csv) {
    $ret = db_update('neon_batch')
      ->condition('id', $this->id)
      ->fields(array(
        'batch' => $csv,
    ))->execute();
    return $ret;
  }


  public function fetch() {
    $batch = db_query('SELECT batch FROM {neon_batch} WHERE id = :id', array(
      ':id' => $this->id,
    ))->fetchField();
    return $batch;
  }


  public function fetchBatchArray() {
    $array = array();
    $csv = db_query('SELECT batch FROM {neon_batch} WHERE id = :id', array(
      ':id' => $this->id,
    ))->fetchField();
    if($csv) {
      $array = explode(',', $csv);
    }
    return $array;
  }


}
