<?php

/**
 * @file
 * The default format for adresses.
 * @author Daniel Silva
 */

$plugin = array(
  'title' => t('Address form (Portugal add-on)'),
  'format callback' => 'addressfield_format_address_pt_generate',
  'type' => 'address',
  'weight' => -100,
);

//load the data file
module_load_include('inc', 'addressfield_pt', 'plugins/format/addressfield_pt_data');

/**
 * Format callback.
 *
 * @see CALLBACK_addressfield_format_callback()
 */
function addressfield_format_address_pt_generate(&$format, $address, $context = array()) {
  if ($address['country'] == 'PT') { /* && $context['mode'] == 'form' */
    //Change Address1 name
    $format['street_block']['thoroughfare']['#title'] = t('Address');

    //Unset the Address2
    unset($format['street_block']['premise']);

    //Administrative_area will be used as Distrito
    $format['locality_block']['administrative_area'] = array(
      '#title' => t('District'),
      '#size' => 10,
      '#required' => TRUE,
      '#prefix' => ' ',
      '#attributes' => array('class' => array('administrative_area')),
      '#options' => _distritos_portugal(),
      '#weight' => 1,
    );

    //Locality will be used as Concelho
    $format['locality_block']['locality'] = array(
      '#title' => t('Locality'),
      '#size' => 10,
      '#required' => TRUE,
      '#prefix' => ' ',
      '#attributes' => array('class' => array('locality')),
      '#options' => array('' => '--'), //by default it has no options. They will
      // be set after Distrito selection
      '#access' => FALSE, //field is hidden by default
      '#weight' => 2,
    );

    //Dependent_locality will be used as Freguseia
    $format['locality_block']['dependent_locality'] = array(
      '#title' => t('Parish'),
      '#size' => 10,
      '#required' => TRUE,
      '#prefix' => ' ',
      '#attributes' => array('class' => array('dependent_locality')),
      '#options' => array('' => '--'), //by default it has no options. They will
      // be set after Conselho selection
      '#access' => FALSE, //field is hidden by defaul
      '#weight' => 3,
    );

    // STARTING CONDICIONAL #OPTION SETTING
    if (!empty($address['administrative_area'])) {
      $format['locality_block']['locality']['#options'] = _concelhos_portugal($address['administrative_area']);
      $format['locality_block']['locality']['#access'] = TRUE;

      if (!empty($address['locality'])) {
        $format['locality_block']['dependent_locality']['#options'] = _freguesias_portugal($address['administrative_area'], $address['locality']);
        $format['locality_block']['dependent_locality']['#access'] = TRUE;
      }
    }

    if ($context['mode'] == 'render') {
      $format['locality_block']['dependent_locality']['#access'] = FALSE;
      $format['locality_block']['administrative_area']['#access'] = FALSE;
    }

    //Add the ajax callbacks
    if ($context['mode'] == 'form') {
      $format['locality_block']['administrative_area']['#ajax'] = array(
        'callback' => 'addressfield_standard_widget_refresh',
        'wrapper' => $format['#wrapper_id'],
        'method' => 'replace',
      );

      $format['locality_block']['locality']['#ajax'] = array(
        'callback' => 'addressfield_standard_widget_refresh',
        'wrapper' => $format['#wrapper_id'],
        'method' => 'replace',
      );
    }

  }
  else {
    // Cancel the AJAX for forms we don't control.
    if (isset($format['locality_block']['administrative_area'])) {
      $format['locality_block']['administrative_area']['#ajax'] = array();
    }

    if (isset($format['locality_block']['locality'])) {
      $format['locality_block']['locality']['#ajax'] = array();
    }

  }//End of potugal specific settings
}
