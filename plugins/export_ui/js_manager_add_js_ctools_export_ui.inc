<?php

/**
 * @file
 * A Ctools Export UI plugin for Javascript Manager Add JS.
 */
$plugin = array(
  'schema' => 'js_manager_add_js',
  // As defined in hook_schema().
  'access' => 'manage javascript items',
  // Define a permission users must have to access these pages.
  // Define the menu item.
  'menu' => array(
    'menu item' => 'js_manager',
    'menu title' => 'JavaScript',
    'menu description' => 'Manage inline and external JavaScript.',
  ),
  // Define user interface texts.
  'title singular' => t('JavaScript item'),
  'title plural' => t('JavaScript items'),
  'title singular proper' => t('JavaScript item'),
  'title plural proper' => t('JavaScript items'),
  'handler' => array(
    'class' => 'js_manager_add_js_ui',
    'parent' => 'ctools_export_ui',
  ),
  // Define the names of the functions that provide the add/edit forms.
  'form' => array(
    'settings' => 'js_manager_add_js_ctools_export_ui_form',
    'submit' => 'js_manager_add_js_ctools_export_ui_form_submit',
  ),
);

/**
 * Define the preset add/edit form.
 */
function js_manager_add_js_ctools_export_ui_form(&$form, &$form_state) {
  $form['js_type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => array(
      'external' => 'External',
      'inline' => 'Inline',
    ),
    '#description' => 'Type of JavaScript',
    '#default_value' => $form_state['item']->js_type,
  );

  // External Fields.
  $form['external'] = array(
    '#type' => 'fieldset',
    '#title' => t('External'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="js_type"]' => array('value' => 'external'),
      ),
      'invisible' => array(
        ':input[name="js_type"]' => array('value' => 'inline'),
      ),
    ),
  );
  $form['external']['external_js'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#description' => 'External JavaScript URL',
    '#default_value' => $form_state['item']->external_js,
  );
  $form['external']['external_js_async'] = array(
    '#type' => 'checkbox',
    '#title' => t('Load Asynchronously'),
    '#description' => 'Load external JavaScript Asynchronously',
    '#default_value' => $form_state['item']->external_js_async,
  );

  // Inline Fields.
  $form['inline'] = array(
    '#type' => 'fieldset',
    '#title' => t('Inline'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="js_type"]' => array('value' => 'inline'),
      ),
      'invisible' => array(
        ':input[name="js_type"]' => array('value' => 'external'),
      ),
    ),
  );
  $form['inline']['inline_js'] = array(
    '#type' => 'textarea',
    '#title' => t('Snippet'),
    '#description' => 'Inline JavaScript snippet',
    '#default_value' => $form_state['item']->inline_js,
  );

  $form['exclude_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Exclude on admin paths'),
    '#description' => 'Exclude on admin paths',
    '#default_value' => $form_state['item']->exclude_admin,
  );
  $form['weight'] = array(
    '#type' => 'textfield',
    '#title' => t('Weight'),
    '#description' => 'Weight to control the order of scripts.',
    '#default_value' => $form_state['item']->weight,
    '#element_validate' => array(
      'element_validate_integer',
    ),
  );
  $form['scope'] = array(
    '#type' => 'select',
    '#title' => t('Scope'),
    '#options' => array(
      'header' => 'Header',
      'footer' => 'Footer',
    ),
    '#description' => 'Where the script should be added.',
    '#default_value' => $form_state['item']->scope,
  );
}

/**
 * Submit callback.
 *
 * @param $form
 * @param $form_state
 */
function js_manager_add_js_ctools_export_ui_form_submit(&$form, &$form_state) {
  // Clear the Add JS cache.
  cache_clear_all('js_manager_add_js', 'cache', TRUE);
}
