<?php 
use Drupal\Core\Form\FormStateInterface;

function ielfirjancityco_form_user_login_form_alter(&$form, FormStateInterface $form_state, $form_id) {
    $form['#attributes'] = array('class' => 'wrapper-form form');
  
    if ($form_id == 'user_login_form' || $form_id == 'user_login' || $form_id == 'user_login_block') {
      $form['name']['#attributes']['placeholder'] = t('Usuário');
      $form['pass']['#attributes']['placeholder'] = t('Senha');
      $form['actions']['submit']['#value'] = 'Entrar';
      $form['name']['#description'] = FALSE;
      $form['pass']['#description'] = FALSE;
    }
}