<?php

/**
 * @file
 * Callbacks for administrating entities.
 */

/**
 * Choose bundle of entity to add.
 * 
 * @return array
 *   Array describing a list of bundles to render.
 */
function travel_choose_bundle() {
  drupal_set_title(t('Choose type of entity to add.'));

  // Show list of all existing entity bundles.
  $entity_info = entity_get_info('travel');
  $items = array();
  foreach ($entity_info['bundles'] as $bundle_name => $bundle_data) {
    $items[] = l($bundle_data['label'], 'travel/add/' . $bundle_name);
  }
  return array(
    'list' => array(
      '#theme' => 'item_list',
      '#items' => $items,
      '#title' => t('Choose type of entity to add.'),
    ),
  );
}

/**
 * Form constructor for the entity add form.
 * 
 * @param string $type
 *   Bundle of the entity to add.
 * 
 * @return array
 *   Entity edit form.
 */
function travel_add($type) {
  drupal_set_title(t('Create new %type', array('%type' => $type)));

  // Return form for the given entity bundle.
  $entity = entity_create('travel', array('type' => $type));
  $output = entity_ui_get_form('travel', $entity);

  return $output;
}

/**
 * Form constructor for "travel_bundle_1" bundle.
 * 
 * This function is necessary for entity_ui_get_form() function.
 * 
 * @see entity_ui_get_form()
 * 
 * @param object $entity
 *   Enity to edit.
 * 
 * @return array
 *   Entity edit form.
 */
function travel_edit_public_form($form, &$form_state, $entity) {
  return travel_form($form, $form_state, $entity);
}

/**
 * Form constructor for "travel_bundle_2" bundle.
 * 
 * This function is necessary for entity_ui_get_form() function.
 * 
 * @see entity_ui_get_form()
 * 
 * @param object $entity
 *   Enity to edit.
 * 
 * @return array
 *   Entity edit form.
 */
function travel_edit_freight_form($form, &$form_state, $entity) {
  return travel_form($form, $form_state, $entity);
}

/**
 * Form constructor for the entity edit form.
 * 
 * In this form we shall manually define all form elements related to editable
 * properties of the entity.
 * 
 * @param object $entity
 *   Enity to edit.
 * 
 * @return array
 *   Entity edit form.
 */
function travel_form($form, &$form_state, $entity) {
  // Store the entity in the form.
  $form_state['travel'] = $entity;

  // Describe all properties of the entity which shall be shown on the form.
  $wrapper = entity_metadata_wrapper('travel', $entity);

  $form['transport'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Transport:'),
    '#default_value' => $wrapper->transport->value(),
    '#weight' => -20,
  );

  $form['source_from'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Source From:'),
    '#default_value' => $wrapper->source_from->value(),
    '#weight' => -16,
  );
  $form['destination_to'] = array(
    '#type' => 'textfield',
    '#title' => t('Destination To:'),
    '#default_value' => $wrapper->destination_to->value(),
    '#weight' => -10,
  );

  // Add fields of the entity to the form.
  field_attach_form('travel', $entity, $form, $form_state);

  // Add some buttons.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
    '#submit' => array('travel_form_submit'),
  );
  if (empty($entity->is_new)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 15,
      '#submit' => array('travel_form_submit_delete'),
    );
  }

  return $form;
}

/**
 * Entity edit form "Save" submit handler.
 */
function travel_form_submit(&$form, &$form_state) {
  // Automatically get edited entity from the form and save it.
  // @see entity_form_submit_build_entity()
  $entity = $form_state['travel'];

  //Binds the form state values to the entity properties.
  entity_form_submit_build_entity('travel', $entity, $form, $form_state);
  $wrapper = entity_metadata_wrapper('travel', $entity);
  $wrapper->save();

  // Redirect user to edited entity page.
  $entity_uri = entity_uri('travel', $entity);
  $form_state['redirect'] = $entity_uri['path'];
}

/**
 * Entity edit form "Delete" submit handler.
 */
function travel_form_submit_delete($form, &$form_state) {
  // Redirect user to "Delete" URI for this entity.
  $entity = $form_state['travel'];
  $entity_uri = entity_uri('travel', $entity);
  $form_state['redirect'] = $entity_uri['path'] . '/delete';
}

/**
 * Form constructor for the entity delete confirmation form.
 * 
 * @param object $entity
 *   Entity to delete.
 * 
 * @return array
 *   Confirmation form.
 */
function travel_form_delete($form, &$form_state, $entity) {
  // Store the entity in the form.
  $form_state['travel'] = $entity;

  // Show confirm dialog.
  $entity_uri = entity_uri('travel', $entity);
  $message = t('Are you sure you want to delete travel %title?', array('%title' => entity_label('travel', $entity)));
  return confirm_form(
    $form,
    $message,
    $entity_uri['path'],
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Entity "Confirm delete" form submit handler.
 */
function travel_form_delete_submit($form, &$form_state) {
  // Delete the entity.
  $entity = $form_state['travel'];
  $wrapper = entity_metadata_wrapper('travel', $entity);
  $wrapper->delete();

  // Redirect user.
  drupal_set_message(t('Custom entity v4 %title deleted.', array('%title' => entity_label('travel', $entity))));
  $form_state['redirect'] = '<front>';
}
