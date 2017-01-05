<?php
/**
 * Typical Entity 4 controller class.
 */
class TravelController extends EntityAPIController {
  /**
   * Build a structured array representing the entity's content.
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $wrapper = entity_metadata_wrapper('travel', $entity);

    $content['transport'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' => t('Transport'),
      '#access' => TRUE,
      '#label_display' => 'above',
      '#view_mode' => 'full',
      '#language' => LANGUAGE_NONE,
      '#field_name' => 'field_fake_transport',
      '#field_type' => 'text',
      '#entity_type' => 'travel',
      '#bundle' => $wrapper->transport->value(),  //For bundle here type has to be used.
      '#items' => array(array('value' => $wrapper->transport->value())),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($wrapper->transport->value())),
    );

    // Make "title" and "description" properties themed like default fields.
    $content['source_from'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' => t('Source From'),
      '#access' => TRUE,
      '#label_display' => 'above',
      '#view_mode' => 'full',
      '#language' => LANGUAGE_NONE,
      '#field_name' => 'field_fake_source_from',
      '#field_type' => 'text',
      '#entity_type' => 'travel',
      '#bundle' => $wrapper->source_from->value(),
      '#items' => array(array('value' => $wrapper->source_from->value())),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($wrapper->source_from->value())),
    );

    $content['destination_to'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' => t('Source From'),
      '#access' => TRUE,
      '#label_display' => 'above',
      '#view_mode' => 'full',
      '#language' => LANGUAGE_NONE,
      '#field_name' => 'field_fake_source_from',
      '#field_type' => 'text',
      '#entity_type' => 'travel',
      '#bundle' => $wrapper->destination_to->value(),
      '#items' => array(array('value' => $wrapper->destination_to->value())),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($wrapper->destination_to->value())),
    );

    return parent::buildContent($entity, $view_mode, $langcode, $content);
  }
}

/**
 * EntityTest Views Controller class.
 */
class EntityTravelViewsController extends EntityDefaultViewsController {

  /**
   * Edit or add extra fields to views_data().
   */
  public function views_data() {
    $data = parent::views_data();

    // Add your custom data here

    /* 
    * Example: change the handler of a field
    * if the 'created' field is a unix timestamp in the database, 
    * Entity API will set the handler to views_handler_field_numeric, 
    * change this to the views date handler
    */ 
    $data['travel']['created']['field']['handler'] = 'views_handler_field_date';

    return $data;
  }
}