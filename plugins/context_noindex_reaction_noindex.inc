<?php

class context_noindex_reaction_noindex extends context_reaction {
  function options_form($context) {
    return array('noindex' => array('#type' => 'value', '#value' => TRUE));
  }

  /**
   * Options form submit handler.
   */
  function options_form_submit($values) {
    return array('noindex' => 1);
  }

  function execute() {
    $contexts = $this->get_contexts();
    foreach ($contexts as $context) {
      if (!empty($context->reactions[$this->plugin])) {
        foreach ($context->reactions[$this->plugin] as $crid => $enabled) {
          if ($enabled) {
            $this->noindex();
          }
        }
      }
    }
  }

  function noindex() {
    global $user;
    if ($user->uid == 1) {
      drupal_set_message(t('This page will not be indexed by search engines.'), 'warning');
    }

    $meta_robots = array(
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'robots',
        'value' => 'noindex, nofollow',
      ),
    );

    drupal_add_html_head($meta_robots, 'context_noindex_robots');
  }
}
