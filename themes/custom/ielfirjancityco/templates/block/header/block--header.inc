<?php 
function ielfirjancityco_preprocess_block__header(&$variables) {
    $route = \Drupal::routeMatch()->getRouteName();
    $config = \Drupal::config('system.site');
    $variables['site']['name'] = $config->get('name');
    
    if(theme_get_setting('new_logo')) {
        $fid = theme_get_setting('new_logo')[0];
        if($fid) {
            $file = \Drupal\file\Entity\File::load($fid);
            if($file) {
                $variables['logo'] = file_create_url($file->getFileUri());
            }
        }        
    }

    if(\Drupal::routeMatch()->getParameter('user')) {
        $variables['is_profile'] = \Drupal::routeMatch()->getParameter('user');
    } elseif($route) {
        $variables['is_system'] = str_contains( $route, "system" );    
        $variables['is_login'] = str_contains( $route, "login" ); 
        $variables['lead'] = str_contains( $route, "lead" );   
    } elseif(\Drupal::requestStack()->getCurrentRequest()->attributes->get('exception')->getStatusCode()) {
        $variables['exception'] = \Drupal::requestStack()->getCurrentRequest()->attributes->get('exception')->getStatusCode();   
    }
}