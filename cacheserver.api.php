<?php
// $Id:

/**
 * @file
 * Hooks provided by the cacheserver module.
 */

/**
 * Allows Cache Server to use specific cache engines and settings.
 * If APC is selected for cache_page, the bin will be using class apc
 * (that implements DrupalCacheInterface )
 *
 * @return
 *   An array of strings that describe the engine and the options.
 */
function hook_cacheserver() {
  $cacheserver = array();
  $cacheserver['apc'] = array(
    '#class' => 'apc', // If not set, get the value of the key
    '#name' => t('Advanced PHP Cache'), // The name of the engine displayed on Cache Server settings page
    '#enabled' => extension_loaded('apc'), // Default is TRUE
    '#options' => array(), // Default is an empty array
    '#options type' => CACHESERVER_OPTIONS_NONE, // No option selection will appear
  );
  $cacheserver['redis'] = array(
    '#class' => 'redis',
    '#name' => t('Redis'),
    '#enabled' => my_custom_callback(),
    '#options' => array(
      'all' => t('Use all Redis servers'),
      's1' => t('Use Redis server 1'),
      's2' => t('Use Redis server 2'),
    ),
    '#options type' => CACHESERVER_OPTIONS_UNIQUE, // Option selection with radios if #options is not empty
  );
  $cacheserver['memcache'] = array(
    '#class' => 'memcache',
    '#name' => t('Memcache'),
    '#enabled' => my_custom_callback(),
    '#options' => array(
      's1' => t('Use Memcache server 1'),
      's2' => t('Use Memcache server 2'),
    ),
    '#options type' => CACHESERVER_OPTIONS_MULTIPLE,// Option selection with checkboxes if #options is not empty
  );  
  return $cacheserver;
}