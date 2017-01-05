<?php

/**
 * @file
 * Callbacks for viewing entities.
 */

/**
 * Show list of existing entities.
 */
function travel_list() {
  drupal_set_title(t('Travels List'));

  // Show link to the entity "Add" page.
  $output = '<br/>';
  $output .= theme_link(
    array(
      'text' => t('Add new travel'),
      'path' => 'travel/add',
      'options' => array(
        'attributes' => array(),
        'html' => TRUE,
      ),
    )
  );

  // Show list of existing entities.
  $entities = entity_load('travel');

  $items = array();
  foreach ($entities as $entity) {
    $entity_uri = entity_uri('travel', $entity);
    $items[] = l(entity_label('travel', $entity), $entity_uri['path']);
  }

  $output .= theme_item_list(
    array(
      'items' => $items,
      'title' => t('Travels List'),
      'type' => 'ul',
      'attributes' => array(),
    )
  );

  return $output;
}

/**
 * Entity view callback.
 * 
 * @param object $entity
 *   Entity to view.
 * 
 * @return array
 *   Renderable array.
 */
function travel_view($entity) {
  drupal_set_title(entity_label('travel', $entity));

  // Return automatically generated view page.
  return entity_view(
    'travel',
    array(entity_id('travel', $entity) => $entity),
    'full'
  );
}
