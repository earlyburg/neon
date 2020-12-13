<?php

class NeonSimpleRequest {

  function __construct( $url, $options ) {
    # if the site is htpasswd protected, add the auth header to the request
// @TODO test for webserver types so we use the correct hash encoding
    $conf1 = config_get('neon.settings', 'htpasswd');
    $raw_u = config_get('neon.settings', 'htpasswd_uname');
    $raw_p = config_get('neon.settings', 'htpasswd_pword');
    $this->hash = base64_encode($raw_u . ":" . $raw_p);
    if ($conf1 === 1) {
      $string = "Basic " . $this->hash;
      $options['headers'] += ['Authorization' => $string];
    }
    $this->response = backdrop_http_request(url($url, array('absolute' => TRUE)), $options);
  }


  function response() {
    return $this->response;
  }


  function okReturn200() {
    if ($this->response->code == '200') {
      return TRUE;
    } else {
      return FALSE;
    }
  }


  function fetchResponseHeaders() {
    $headers = array();
    if ($this->response->code == '200') {
      $headers = $this->response->headers;
      return $headers;
    } else {
      return FALSE;
    }
  }


  function getContentType($headers = array()) {
    if (isset($headers['content-type']) === TRUE && empty($headers['content-type']) === FALSE) {
      return $headers['content-type'];
    } else {
      return FALSE;
    }
  }


  function getContents() {
    if ($this->response->code == '200') {
      return $this->response->data;
    } else {
      $responseCode = $this->response->code;
      watchdog('neon', 'The request returned a response code of ' . $responseCode, array(), WATCHDOG_NOTICE);
      return "The request returned a response code of " . $responseCode;
    }
  }
}
