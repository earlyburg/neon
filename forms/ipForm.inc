<?php

/**
 * page callback
 */
function neon_IP_scrape() {
  $rows = [];
  $ret = '';
  $header = array(
    array('data' => t('IP')),
    array('data' => t('Host')),
    array('data' => t('Date')),
    array('data' => t('Domain')),
  );

  $ipQuery = db_select('visitors', 'n')
    ->extend('PagerDefault')
    ->extend('TableSort')
    ->distinct(TRUE)
    ->fields('n', array('visitors_ip'))
    ->limit(10);
  $results = $ipQuery->execute();

  foreach ($results as $data) {
    if ( long2ip($data->visitors_ip) ) {
      $ipAddress = long2ip($data->visitors_ip);
      if ( gethostbyaddr($ipAddress) ) {
        $hostName = gethostbyaddr($ipAddress);
        if ($hostName != $ipAddress) {
          $rootDomain = neon_getDomain($hostName);
        }
      }
      else {
        $hostName = 'Unknown Hostname';
      }
    }
    else {
      $ipAddress = 'Could not decode IP string';
    }
    $rows[] = array(
      '<a class="colorbox-load" href="geocode/'.$ipAddress.'?width=550&height=600">' . $ipAddress . '</a>',
      $hostName,
      date("F j, Y, g:i a", neon_getLastTimestamp($data->visitors_ip)),
      '<a class="colorbox-load" href="ip_list/'.$rootDomain.'?width=550&height=600">' . $rootDomain . '</a>'
    );
  }
  $ret = '<div class="submitted">There are ' . neon_getIpNum() . ' unique IP addresses in the database.</div>';
  $ret .= theme('table', array('header' => $header, 'rows' => $rows));
  $ret .= theme('pager');
  return $ret;
}

/**
 * @return String
 * the root domain of a FQDN with subdomains
 */
function neon_getDomain($host) {
  $myhost = strtolower(trim($host));
  $count = substr_count($myhost, '.');
  if($count === 2){
    if(strlen(explode('.', $myhost)[1]) > 3) $myhost = explode('.', $myhost, 2)[1];
  } else if($count > 2){
    $myhost = neon_getDomain(explode('.', $myhost, 2)[1]);
  }
  return $myhost;
}

/**
 * @return String
 * the timestamp of the most recent hit from any IP
 */
function neon_getLastTimestamp($ip = NULL) {
  $timeStamp = db_select('visitors', 'n')
    ->fields('n', array('visitors_date_time'))
    ->having("MAX(visitors_date_time)")
    ->condition('n.visitors_ip', $ip, '=')
    ->execute()
    ->fetchField();
  return $timeStamp;
}

/**
 * @return String
 * the number of unique IPs in the visitors table
 */
function neon_getIpNum() {
  $ipCount = db_select('visitors', 'n')
    ->fields('n', array('visitors_ip'))
    ->distinct(TRUE)
    ->execute()
    ->rowCount();
  return $ipCount;
}

/**
 * @return String
 * contains whois info and associated data about a domain name
 */
function neon_whoisLook($query) {
  $whois = new Whois();
  $result = $whois->Lookup($query,false);
  $content = '<h3>' . $query . '</h3>';
  foreach ($result['rawdata'] as $line) {
    $content .= '<div class="field-items">' . $line . '</div>';
  }
  return $content;
}

/**
 * @return String
 * contains geographic information about an IP address
 */
function neon_geoLook($query) {
  $ipLocate = 'https://www.iplocate.io/api/lookup/';
  $ret = file_get_contents($ipLocate . $query);
  $return = backdrop_json_decode($ret);
  $content='';
  foreach ($return as $index => $line) {
    $content .= '<div class="field-items"><b>' . $index .'</b>: '. $line . '</div>';
  }
  return $content;
}



// @TODO blacklist IPs get redirected to a pre-set url
