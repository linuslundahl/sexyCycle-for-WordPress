<?php

function scfw_menu() {
  add_options_page('SecyCycle for WordPress', 'SexyCycle', 'manage_options', 'sexycycle-for-wordpress-menu', 'scfw_options');
}

// Setup form
$scfw_themename = "SexyCycle for WordPress";
$scfw_shortname = "scfw";
$scfw_options = array(
  array(
    "value" => "<a href=\"http://suprb.com/apps/sexyCycle/\">SexyCycle jQuery plugin</a> created by <a href=\"http://suprb.com/\">Andreas Pihlstr&ouml;m</a>.<br />SexyCycle for WordPress created by <a href=\"http://unwise.se/\">Linus Lundahl</a>.<br /><br />These settings affects <strong>all galleries</strong> in <strong>all posts and pages</strong>, single gallery settings are not available.",
    "type" => "paragraph"
  ),
  array(
    "name" => "Settings",
    "type" => "title"
  ),
  array(
    "type" => 'start-table'
  ),
  array(
    "name" => "Image size",
    "desc" => "Select what image size the galleries should use.",
    "id" => $scfw_shortname . "_img_size",
    "type" => "select",
    "options" => array(
      'thumbnail' => 'thumbnail',
      'medium' => 'medium',
      'large' => 'large'
    ),
    "std" => 'large'
  ),
  array(
    "name" => "jQuery Easing animation",
    "desc" => "Slide animation that should be used.",
    "id" => $scfw_shortname . "_animation",
    "type" => "select",
    "options" => array(
      'easeInQuad' => 'easeInQuad',
      'easeOutQuad' => 'easeOutQuad',
      'easeInOutQuad' => 'easeInOutQuad',
      'easeInCubic' => 'easeInCubic',
      'easeOutCubic' => 'easeOutCubic',
      'easeInOutCubic' => 'easeInOutCubic',
      'easeInQuart' => 'easeInQuart',
      'easeOutQuart' => 'easeOutQuart',
      'easeInOutQuart' => 'easeInOutQuart',
      'easeInQuint' => 'easeInQuint',
      'easeOutQuint' => 'easeOutQuint',
      'easeInOutQuint' => 'easeInOutQuint',
      'easeInSine' => 'easeInSine',
      'easeOutSine' => 'easeOutSine',
      'easeInOutSine' => 'easeInOutSine',
      'easeInExpo' => 'easeInExpo',
      'easeOutExpo' => 'easeOutExpo',
      'easeInOutExpo' => 'easeInOutExpo',
      'easeInCirc' => 'easeInCirc',
      'easeOutCirc' => 'easeOutCirc',
      'easeInOutCirc' => 'easeInOutCirc',
      'easeInElastic' => 'easeInElastic',
      'easeOutElastic' => 'easeOutElastic',
      'easeInOutElastic' => 'easeInOutElastic',
      'easeInBack' => 'easeInBack',
      'easeOutBack' => 'easeOutBack',
      'easeInOutBack' => 'easeInOutBack',
      'easeInBounce' => 'easeInBounce',
      'easeOutBounce' => 'easeOutBounce',
      'easeInOutBounce' => 'easeInOutBounce'
    ),
    "std" => 'easeOutExpo'
  ),
  array(
    "name" => "Speed",
    "desc" => "The speed of the animation. (milliseconds)",
    "id" => $scfw_shortname . "_speed",
    "type" => "textfield",
    "std" => '400',
    "size" => 4
  ),
  // array(
  //   "name" => "Cycling interval",
  //   "desc" => "Leave empty to disable auto cycling.",
  //   "id" => $scfw_shortname . "_interval",
  //   "type" => "textfield",
  //   "size" => 4
  // ),
  array(
    "name" => "Type of controls",
    "desc" => "Select if you would like to add PREV and NEXT buttons.",
    "id" => $scfw_shortname . "_controls",
    "type" => "select",
    "options" => array(
      'none' => 0,
      'Under Image' => 'under',
      'Before / After image' => 'beforeafter'
    ),
    "std" => 0
  ),
  array(
    "name" => "Disable cycling",
    "desc" => "Prevent the gallery from cycling",
    "id" => $scfw_shortname . "_cycle",
    "type" => "checkbox",
    "std" => 0
  ),
  array(
    "name" => "Disable jQuery",
    "desc" => "Don't load latest version of jQuery <strong>*</strong>",
    "id" => $scfw_shortname . "_jquery",
    "type" => "checkbox",
    "std" => 0
  ),
  array(
    'type' => 'end-table'
  ),
  array(
    'value' => '<small><strong>*</strong> SexyCycle depends on jQuery 1.4+ and if you disable it from loading here, make sure it\'s loaded elsewhere.</small>',
    'type' => 'paragraph'
  )
);


function scfw_options() {
  global $scfw_themename, $scfw_shortname, $scfw_options;

  if ( 'save' == $_REQUEST['action'] ) {

    $values = array();
    foreach ($scfw_options as $value) {
      if ($value['id']) {
        $values[$value['id']] = $_REQUEST[$value['id']];
      }
    }

    update_option($scfw_shortname . '_settings', $values);

    echo '<div id="message" class="updated fade"><p><strong>' . __('Options saved.') . '</strong></p></div>';
  }

  $scfw_settings = get_settings('scfw_settings');
?>

<div class="wrap">
<h2><?php echo $scfw_themename; ?> settings</h2>

<form method="post" action="">

<?php foreach ($scfw_options as $value) {
switch ($value['type']) {

case "start-table":
?>
<table class="form-table">
<?php
break;

case "end-table";
?>
</table>
<?php
break;

case "title":
?>
<h3 class="title"><?php echo __($value['name']); ?></h3>
<?php
break;

case 'paragraph':
?>
<p><?php echo $value['value']; ?></p>
<?php
break;

case 'textfield':
$set_value = $scfw_settings[$value['id']] ? $scfw_settings[$value['id']] : $value['std'];
?>
  <tr valign="top">
    <th scope="row"><label for="<?php echo $value['id']; ?>"><?php echo $value['name']; ?></label></th>
    <td>
      <input size="<?php echo $value['size']; ?>" name="<?php echo $value['id']; ?>" id="<?php echo $value['id']; ?>" type="<?php echo $value['type']; ?>" value="<?php echo $set_value; ?>" />
      <span class="description"><?php echo $value['desc']; ?></span>
    </td>
  </tr>
<?php
break;

case 'textarea':
$set_value = $scfw_settings[$value['id']] ? $scfw_settings[$value['id']] : $value['std'];
?>
  <tr valign="top">
    <th scope="row"><label for="<?php echo $value['id']; ?>"><?php echo $value['name']; ?></label></th>
    <td>
      <textarea name="<?php echo $value['id']; ?>" id="<?php echo $value['id']; ?>" cols="40" rows="5"><?php echo $set_value; ?></textarea>
      <span class="description"><?php echo $value['desc']; ?></span>
    </td>
  </tr>
<?php
break;

case 'select':
?>
  <tr valign="top">
    <th scope="row"><label for="<?php echo $value['id']; ?>"><?php echo $value['name']; ?></label></th>
    <td>
      <select style="width:140px;" name="<?php echo $value['id']; ?>" id="<?php echo $value['id']; ?>">
<?php foreach ($value['options'] as $key => $item) { ?>
<?php
  $selected = '';
  $saved = $scfw_settings[$value['id']];
  if ($saved && ($saved === $item)) {
    $selected = ' selected="selected"';
  } elseif (!$saved && ($saved === $item)) {
    $selected = ' selected="selected"';
  } elseif (!$saved && ($value['std'] === $item)) {
    $selected = ' selected="selected"';
  }
?>
      <option<?php echo " value=\"$item\"" . $selected; ?>><?php echo $key; ?></option>
<?php } ?>
      </select>
      <span class="description"><?php echo $value['desc']; ?></span>
    </td>
  </tr>
<?php
break;

case "checkbox":
$checked = $scfw_settings[$value['id']] ? 'checked="checked"' : '';
?>
  <tr valign="top">
    <th scope="row"><?php echo $value['name']; ?></th>
    <td>
      <label for="<?php echo $value['id']; ?>">
        <input type="checkbox" name="<?php echo $value['id']; ?>" id="<?php echo $value['id']; ?>" value="1" <?php echo $checked; ?> />
        <?php echo $value['desc']; ?>
      </label>
    </td>
  </tr>
<?php
break;
}
}
?>

<p class="submit">
<input class="button-primary" name="save" type="submit" value="Save changes" />
<input type="hidden" name="action" value="save" />
</p>
</form>
</div>

<?php
}
?>