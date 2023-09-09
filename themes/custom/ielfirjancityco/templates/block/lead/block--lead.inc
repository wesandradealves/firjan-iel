<?php 
use Drupal\node\Entity\Node;
use Drupal\webform\WebformInterface;
use Drupal\webform\Plugin\WebformHandlerBase;
use Drupal\webform\WebformSubmissionInterface;
use Drupal\webform\Entity\WebformSubmission;
use Drupal\Core\Form\FormStateInterface;

function ielfirjancityco_preprocess_block__lead(&$variables) {
    $entity = $variables['content']['#block_content'];
    $user = \Drupal::currentUser();

    $variables['user'] = clone $user;
    // Remove password and session IDs, since themes should not need nor see them.
    unset($variables['user']->pass, $variables['user']->sid, $variables['user']->ssid);
  
    $variables['is_admin'] = $user->hasPermission('access administration pages');

    if($user->isAuthenticated()) {
      $variables['logged_in'] = $user->isAuthenticated();
    }
    
    if($entity->get('field_data_layer')) {
      $html = '
        <script type="text/javascript">
            const form = document.getElementsByClassName("contact-form")[0];
            function submit(e) {';
              $html .= htmlspecialchars_decode($entity->get('field_data_layer')->value);
      $html .= '}                            
            form.addEventListener("submit", submit);
        </script>
      ';

      $variables['data_layer'] = $html;
    }

    if($entity->get('field_formulario')) {
        $form = $entity->get('field_formulario')->first()->get('entity')->getTarget()->getValue();

        // $message = \Drupal::entityTypeManager()
        // ->getStorage('contact_message')
        // ->create(array(
        //     'contact_form' => $form->id(),
        //     'recipient' => ''
        // ));
        // $variables['form'] = \Drupal::service('entity.form_builder')->getForm($message);
        
        $variables['form'] = $form->id();
    }

    $variables['message'] = $entity->get('field_lead_mensagem')->value ? $entity->get('field_lead_mensagem')->value : 'Cadastrado com sucesso';
}

function ielfirjancityco_form_webform_submission_lead_add_form_alter(&$form) {  
  if(theme_get_setting('termos')) {
    $fid = theme_get_setting('termos')[0];
    if($fid) {
      $file = \Drupal\file\Entity\File::load($fid);
      if($file) {
        $variables['termos'] = file_create_url($file->getFileUri());
      }
    }
  }

  $form['elements']['concordo_com_os_termos']['#description']['#markup'] = $form['elements']['concordo_com_os_termos']['#title'] = "<label for='concordo_com_os_termos' class='ps-2'>Concordo com os ".(isset($variables['termos']) ? "<a download href='".$variables['termos']."' title='termos de privacidade'>termos de privacidade</a>" : "termos de privacidade").' *</label>';

  // foreach (array_keys($form['actions']) as $action) {
  //   if ($action != 'preview' && isset($form['actions'][$action]['#type']) && $form['actions'][$action]['#type'] === 'submit') {
  //           $form['actions'][$action]['#submit'][] = 'ielfirjancityco_form_submit';
  //   }
  // }  
}

// function ielfirjancityco_form_submit(array &$form, FormStateInterface $form_state, WebformSubmissionInterface $webform_submission){
//   $values = $webform_submission->getElementData();

//   $field_lead_nome = $values['nome_completo'];
//   $field_lead_email = $values['e_mail'];
//   $field_lead_telefone = $values['telefone_para_contato'];
//   $field_lead_cnpj = $values['cnpj_da_empresa'];
//   $field_lead_empresa = $values['razao_social'];
//   $field_lead_localiza = $values['onde_sua_empresa_se_localiza_'];
//   $field_lead_intencoes = $values['escolha_seu_interesse'];
//   $field_lead_concordo = $values['concordo_com_os_termos'];

//   // $field_lead_nome = $form_state->getFormObject()->getEntity()->get('nome_completo')->value;
//   // $field_lead_email = $form_state->getFormObject()->getEntity()->get('e_mail')->value;
//   // $field_lead_telefone = $form_state->getFormObject()->getEntity()->get('telefone_para_contato')->value;
//   // $field_lead_cnpj = $form_state->getFormObject()->getEntity()->get('cnpj_da_empresa')->value;
//   // $field_lead_empresa = $form_state->getFormObject()->getEntity()->get('razao_social')->value;
//   // $field_lead_localiza = $form_state->getFormObject()->getEntity()->get('onde_sua_empresa_se_localiza_')->value;
//   // $field_lead_intencoes = $form_state->getFormObject()->getEntity()->get('escolha_seu_interesse')->value;
//   // $field_lead_concordo = $form_state->getFormObject()->getEntity()->get('concordo_com_os_termos')->value;

//   $el = \Drupal::entityQuery('node')->condition('field_lead_cnpj', $field_lead_cnpj)->sort('nid', 'DESC')->execute();

//   if($el) {
//     $new_node = Node::load(reset($el));
//     $new_node_op = 'SAVED_UPDATED';
//     \Drupal::service('messenger')->addMessage('Cadastro atualizado com sucesso');
//   } else {
//     $new_node = Node::create([
//       'type' => 'lead',
//       'title' => $field_lead_nome
//     ]);
//     $new_node_op = 'SAVED_NEW';
//     \Drupal::service('messenger')->addMessage(theme_get_setting('form_confirm') ? theme_get_setting('form_confirm') : 'Cadastrado com sucesso');
//   }

//   $new_node->set('title', $field_lead_nome);
//   $new_node->set('field_lead_nome', $field_lead_nome);
//   $new_node->set('field_lead_email', $field_lead_email);
//   $new_node->set('field_lead_telefone', $field_lead_telefone);
//   $new_node->set('field_lead_cnpj', $field_lead_cnpj);
//   $new_node->set('field_lead_empresa', $field_lead_empresa);
//   $new_node->set('field_lead_localiza', $field_lead_localiza);
//   $new_node->set('field_lead_intencoes', $field_lead_intencoes);
//   $new_node->set('field_lead_concordo', $field_lead_concordo);

//   $new_node->save();

//   \Drupal::logger('ielfirjancityco_form_submit')->notice($new_node_op);  
// }  
