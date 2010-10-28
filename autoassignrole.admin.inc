<?php
// $Id$

/**
 * @file
 *
 * Administrative functionality for auto assign role.
 */


/**
 * Provide a single block from the administration menu as a page.
 * This function is often a destination for these blocks.
 * For example, 'admin/structure/types' needs to have a destination to be valid
 * in the Drupal menu system, but too much information there might be
 * hidden, so we supply the contents of the block.
 *
 * @return
 *   The output HTML.
 */
function autoassignrole_admin_block_page() {
  $item = menu_get_item();
  if ($content = system_admin_menu_block($item)) {
    $output = theme('admin_block_content', array('content' => $content));
  }
  else {
    $output = t('You do not have any administrative items.');
  }
  return $output;
}

/**
 * Form builder; The settings form for automatic role assignment.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function autoassignrole_auto_settings() {
  $form['autoassignrole_auto_active'] = array(
    '#type' => 'radios',
    '#title' => t('Automatic role assignment'),
    '#default_value' => variable_get('autoassignrole_auto_active', 0),
    '#description' => t('Automatic role assignment occurs when the user first
      logins to the account.  This happens without the users knowledge.  Set to
      Enabled to allow this functionality or Disabled to not allow.'),
    '#options' => array(1 => t('Enabled'), 0 => t('Disabled')),
  );

  $form['autoassignrole_admin_active'] = array(
    '#type' => 'radios',
    '#title' => t('Automatic role assignment for admin created accounts'),
    '#default_value' => variable_get('autoassignrole_admin_active', 0),
    '#description' => t('Automatic role assignment occurs when the user first
      logins to the account.  This happens without the users knowledge.  Set to
      Enabled to allow this functionality or Disabled to not allow.'),
    '#options' => array(1 => t('Enabled'), 0 => t('Disabled')),
  );

  // We can disregard the authenticated user role since it is assigned to each
  // user by Drupal.
  $roles = user_roles(TRUE);
  unset($roles[DRUPAL_AUTHENTICATED_RID]);

  if ($roles) {
    $form['autoassignrole_auto_roles'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Roles'),
      '#default_value' => variable_get('autoassignrole_auto_roles', array()),
      '#description' => t('Check the specific roles the user will automatically
        be assigned to when created by an administrator or through the new user
        registration process.  The Authenticated User role is automatically
        assigned by Drupal core and can not be edited.'),
      '#options' => $roles,
    );
  }

  return system_settings_form($form);
}

/**
 * Form builder; The settings form for user selectable role assignment.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function autoassignrole_user_settings() {
  $form['autoassignrole_user_active'] = array(
    '#type' => 'radios',
    '#title' => t('User role assignment'),
    '#default_value' => variable_get('autoassignrole_user_active', 0),
    '#description' => t('Toggles allowing end users to select roles when creating their accounts.'),
    '#options' => array(1 => t('Enabled'), 0 => t('Disabled')),
  );

  // We can disregard the authenticated user role since it is assigned to each
  // user by Drupal.
  $roles = user_roles(TRUE);
  unset($roles[DRUPAL_AUTHENTICATED_RID]);

  if ($roles) {
    $form['autoassignrole_user_roles'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Roles'),
      '#default_value' => variable_get('autoassignrole_user_roles', array()),
      '#description' => t('Check the specific roles the user will have the option of choosing.  The Authenticated User role is automatically assigned by Drupal core and can not be edited.'),
      '#options' => $roles,
    );
  }

  $form['autoassignrole_user_multiple'] = array(
    '#type' => 'radios',
    '#title' => t('User role selection'),
    '#default_value' => variable_get('autoassignrole_user_multiple', 0),
    '#description' => t('Should the end user be allowed to choose a single role or can they choose multiple roles?'),
    '#options' => array(0 => t('Single Role'), 1 => t('Multiple Roles')),
  );

  $form['autoassignrole_user_selection'] = array(
    '#type' => 'radios',
    '#title' => t('Selection method'),
    '#default_value' => variable_get('autoassignrole_user_selection', 0),
    '#description' => t('The type of form elements the end user will be presented with.'),
    '#options' => array(0 => t('Radio Buttons'), 1 => t('Selection Box'), 2 => t('Check Boxes')),
  );

  $form['autoassignrole_user_required'] = array(
    '#type' => 'radios',
    '#title' => t('Required'),
    '#default_value' => variable_get('autoassignrole_user_required', 0),
    '#description' => t('Should the end user be required to choose a role?'),
    '#options' => array(0 => t('No'), 1 => t('Yes')),
  );

  $form['autoassignrole_user_sort'] = array(
    '#type' => 'radios',
    '#title' => t('Sorting'),
    '#default_value' => variable_get('autoassignrole_user_selection', 'SORT_ASC'),
    '#description' => t('Default sort order of roles the user will see.'),
    '#options' => array(
      'SORT_ASC' => t('Ascending'),
      'SORT_DESC' => t('Descending')
    ),
  );

  return system_settings_form($form);
}
