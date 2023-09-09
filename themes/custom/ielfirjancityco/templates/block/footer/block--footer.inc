<?php 
function ielfirjancityco_preprocess_block__footer(&$variables) {
    $variables['horarios'] = theme_get_setting('horarios');
    $variables['contatos'] = theme_get_setting('contatos');

    if(theme_get_setting('new_logo')) {
        $fid = theme_get_setting('new_logo')[0];
        if($fid) {
            $file = \Drupal\file\Entity\File::load($fid);
            if($file) {
                $variables['logo'] = file_create_url($file->getFileUri());
            }
        }        
    }
}