/**
 * @file
 * Global utilities.
 *
 */
(function ($, Drupal) {

  'use strict';

  Drupal.behaviors.patasdacasa = {
    attach: function (context, settings) {
      var init = function () {
        $("[name*='telefone']").inputmask("(99) 99999-9999"); 
        $("[name*='cnpj']").inputmask("99.999.999/9999-99"); 

        let required = $("input.required");

        for (let index = 0; index < required.length; index++) {
          const element = required[index];

          if(!$(element).hasClass('form-checkbox')) {
            $(element).parent().addClass('required');
          }
        }
      }
      window.onload = init;
    }
  };

})(jQuery, Drupal);
;
