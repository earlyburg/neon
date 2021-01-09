<?php
// @TODO test for webserver types so we use the correct hash encoding
class NeonSimpleRequest {

  function __construct( $url, $options ) {
    /* if the site is htpasswd protected, add the auth header to the request */
    $config = config('neon.settings');
    $conf1 = $config->get('htpasswd');
    $raw_u = $config->get('htpasswd_uname');
    $raw_p = $config->get('htpasswd_pword');
    $this->hash = base64_encode($raw_u . ":" . $raw_p);
    if ($conf1 == 1) {
      $string = "Basic " . $this->hash;
      $options['headers'] += ['Authorization' => $string];
    }
    try {
      $this->response = backdrop_http_request(url($url, array('absolute' => TRUE)), $options);
    }
    catch (exception $e) {
      watchdog('neon', 'The request returned an error response of ' . $e, array(), WATCHDOG_NOTICE);
    }
  }


  function response() {
    return $this->response;
  }


  function okReturn200() {
    ($this->response->code == '200') ? $return = TRUE : $return = FALSE;
    return $return;
  }


  function fetchResponseHeaders() {
    return $this->response->headers;
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
      watchdog('neon', 'The request returned a response code of ' . $this->response->code, array(), WATCHDOG_NOTICE);
      return 'The request returned a response code of ' . $this->response->code .' - '. $this->response->status_message;
    }
  }
}
