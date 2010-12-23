<?php
// $Id$

/**
 * @file
 * Administrative page callbacks for the Cache Server module.
 */

/**
 * Administration settings form.
 *
 * @see system_settings_form()
 */
function cacheserver_admin_settings() {
  $form = array();

  $bins     = _cacheserver_bins();
  $classes  = _cacheserver_cacheservers_classes();
  $disabled = count($classes) < 2;
  $options  = _cacheserver_cacheservers_options();

  $settings = variable_get('cacheserver_settings');

  foreach ($bins as $bin) {
    $form['bins'][$bin] = array(
      '#type' => 'fieldset',
      '#title' => $bin,
    );

    $form['bins'][$bin][$bin . '_class'] = array(
      '#type' => 'select',
      '#options' => $classes,
      '#default_value' => isset($settings[$bin]['class']) && class_exists($settings[$bin]['class']) ? $settings[$bin]['class'] : 'DrupalDatabaseCache',
      '#disabled' => $disabled,
    );

    foreach ($options as $class => $class_options) {
      $form['bins'][$bin][$bin . '_class_container_' . $class] = array(
        '#type' => 'container',
        '#states' => array(
          'visible' => array(
            ':input[name="' . $bin . '_class"]' => array('value' => $class),
          ),
        ),
      );

      $form['bins'][$bin][$bin . '_class_container_' . $class]['options_' . $bin . '_' . $class] = array(
        '#type' => $options[$class]['type'],
        '#options' => $options[$class]['options'],
        '#default_value' => isset($settings[$bin]['options']) ? $settings[$bin]['options'] : array(),
      );
    }
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#disabled' => $disabled,
  );

  $form['actions']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to defaults'),
    '#submit' => array('cacheserver_admin_settings_reset_submit'),
    '#disabled' => $disabled,
  );

  $form['#submit'][] = 'cacheserver_admin_settings_submit';

  return $form;
}

