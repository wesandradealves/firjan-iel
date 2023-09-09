<?php 

use Drupal\Core\Form\FormStateInterface;
function ielfirjancityco_form_system_theme_settings_alter(&$form, FormStateInterface $form_state) {
    unset($form['logo']);

    $form['new_logo'] = array(
        '#type' => 'managed_file',
        '#upload_location' => 'public://',
        '#title' => t('Logo'),
        '#default_value' => theme_get_setting('new_logo'),
    );  
    $form['background'] = array(
        '#type' => 'managed_file',
        '#upload_location' => 'public://',
        '#title' => t('Background'),
        '#default_value' => theme_get_setting('background'),
    );       
    $form['Footer'] = array(
        '#type' => 'fieldset',
        '#title' => t('Footer'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
    );    
    $form['Footer']['horarios'] = array(
        '#type' => 'textarea',
        '#title' => t('Horários'),
        '#default_value' => theme_get_setting('horarios')
    );
    $form['Footer']['contatos'] = array(
        '#type' => 'textarea',
        '#title' => t('Contato'),
        '#default_value' => theme_get_setting('contatos')
    ); 
    $form['Termos de privacidade'] = array(
        '#type' => 'fieldset',
        '#title' => t('Termos de privacidade'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
    );   
    $form['Termos de privacidade']['termos'] = array(
        '#type' => 'managed_file',
        '#upload_location' => 'public://',
        '#title' => t('Termos de privacidade for termos.'),
        '#default_value' => theme_get_setting('termos'),
        '#description' => t('Somente .pdf'),
        '#upload_validators' => array(
            'file_validate_extensions' => array('pdf'),
        )        
    ); 
    $form['meta'] = array(
      '#type' => 'fieldset',
      '#title' => t('Meta Tags'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );   
    $form['meta']['descricao'] = array(
        '#type' => 'textarea',
        '#title' => t('Descrição'),
        '#default_value' => theme_get_setting('descricao')
    );     
    $form['meta']['scripts'] = array(
        '#type' => 'textarea',
        '#title' => t('Scripts'),
        '#default_value' => theme_get_setting('scripts')
    ); 
    $form['meta']['thumbnail'] = array(
        '#type' => 'managed_file',
        '#upload_location' => 'public://',
        '#title' => t('Thumbnail'),
        '#default_value' => theme_get_setting('thumbnail'),
    );   
    // $form['form_confirm'] = array(
    //     '#type' => 'textarea',
    //     '#title' => t('Mensagem de confirmação'),
    //     '#default_value' => theme_get_setting('form_confirm')
    // ); 
    $form['#validate'][] = 'ielfirjancityco_form_system_theme_settings_validate';
    $form['#submit'][] = 'ielfirjancityco_form_system_theme_settings_submit';
}

function ielfirjancityco_form_system_theme_settings_validate(&$form, FormStateInterface $form_state) {
    $values = $form_state->getValues();

    $termos = file_save_upload('termos');
    $new_logo = file_save_upload('new_logo');
    $background = file_save_upload('background');
    $thumbnail = file_save_upload('thumbnail');

    if (isset($termos)) {
      if ($termos) {
        $values['termos_upload'] = $termos;
      }
      else {
        form_set_error('termos', t('The file cannot be uploaded.'));
      }
    }   
    
    if (isset($new_logo)) {
      if ($new_logo) {
        $values['new_logo_upload'] = $new_logo;
      }
      else {
        form_set_error('new_logo', t('The file cannot be uploaded.'));
      }
    }   
    
    if (isset($background)) {
      if ($background) {
        $values['background_upload'] = $background;
      }
      else {
        form_set_error('background', t('The file cannot be uploaded.'));
      }
    }  
    
    
    if (isset($thumbnail)) {
      if ($thumbnail) {
        $values['thumbnail_upload'] = $thumbnail;
      }
      else {
        form_set_error('thumbnail', t('The file cannot be uploaded.'));
      }
    }      
}

function ielfirjancityco_form_system_theme_settings_submit(&$form, FormStateInterface $form_state) {
    $termos = reset($form_state->getValue('termos'));
    $termos = \Drupal\file\Entity\File::load($termos);

    $logo = reset($form_state->getValue('new_logo'));
    $logo = \Drupal\file\Entity\File::load($logo);
    
    $background = reset($form_state->getValue('background'));
    $background = \Drupal\file\Entity\File::load($background);

    $thumbnail = reset($form_state->getValue('thumbnail'));
    $thumbnail = \Drupal\file\Entity\File::load($thumbnail);    

    if($termos) {
        $termos->setPermanent();
        $termos->status = FILE_STATUS_PERMANENT;
        $termos->save();     
    }

    if($logo) {
        $logo->setPermanent();
        $logo->status = FILE_STATUS_PERMANENT;
        $logo->save();      
    }   

    if($background) {
        $background->setPermanent();
        $background->status = FILE_STATUS_PERMANENT;
        $background->save();      
    }   
    
    if($thumbnail) {
        $thumbnail->setPermanent();
        $thumbnail->status = FILE_STATUS_PERMANENT;
        $thumbnail->save();      
    }       
}