<?php

function scfw_menu() {
	add_options_page('sexyCycle for WordPress', 'sexyCycle', 'manage_options', 'sexycycle-for-wordpress-menu', 'scfw_options');
}

// Setup form
$scfw_pluginname = "sexyCycle for WordPress";
$scfw_shortname = "scfw";
$scfw_options = array();

// Build form
$scfw_options['paragraph-1'] = array(
	"value" => "sexyCycle for WordPress created and maintained by <a href=\"http://unwise.se/\">Linus Lundahl</a>.<br />
              <a href=\"http://suprb.com/apps/sexyCycle/\">sexyCycle jQuery plugin</a> created by <a href=\"http://suprb.com/\">Andreas Pihlstr&ouml;m</a>.<br />
              Contributions by <a href=\"http://thewebpreneur.com/\">Nick O'Neill</a>.<br />",
	"type" => "paragraph"
);

$scfw_options['title-1'] = array(
	"name" => "Instructions",
	"type" => "title"
);

$scfw_options['paragraph-2'] = array(
	"value" => "You can choose to override the default <strong>[gallery]</strong> shortcode, or you can use the shortcode <strong>[sexy-gallery]</strong>, and still have the regular galleries enabled.
              Galleries are created the same way <em>(Add an image -> Gallery)</em> even if you use the default <strong>[gallery]</strong> shortcode or the <strong>[sexy-gallery]</strong> shortcode,
              but pasting a <strong>[sexy-gallery]</strong> shortcode must be done manually in HTML mode.<br /><br />
              If the default shortcode is overriden, these settings affects <strong>all galleries</strong>
              in <strong>all posts and pages</strong>, though custom settings can be added with <a href=\"http://wordpress.org/extend/plugins/sexycycle-for-wordpress/installation/\">shortcode variables</a>.<br />
              Pasting both shortcodes in a single post or page is not recommended, but it works if you don't override the default shortcode.<br /><br />
              When images are linked to the original image, this plugin works together with plugins such as <a href=\"http://wordpress.org/extend/plugins/shadowbox-js/\">Shadowbox JS</a> and
              <a href=\"http://wordpress.org/extend/plugins/jquery-lightbox-balupton-edition/\">jQuery Lightbox</a>. It might also work with other similar plugins, but there are no guarantees.",
	"type" => "paragraph"
);

$scfw_options['title-2'] = array(
	"name" => "Gallery Settings",
	"type" => "title"
);

$scfw_options['start-1'] = array(
	"type" => 'start-table'
);

$scfw_options['override'] = array(
	"name" => "Override default gallery",
	"desc" => "If checked, all [gallery] shortcode tags will be overridden.",
	"id" => $scfw_shortname . "_override",
	"type" => "checkbox",
	"std" => 0
);

$scfw_options['image-size'] = array(
	"name" => "Image size",
	"desc" => "Select what image size the galleries should use.",
	"id" => $scfw_shortname . "_img_size",
	"type" => "select",
	"options" => array(
		'thumbnail' => 'thumbnail',
		'medium' => 'medium',
		'large' => 'large',
		'full' => 'full'
	),
	"std" => 'large'
);

$scfw_options['animation'] = array(
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
);

$scfw_options['speed'] = array(
	"name" => "Speed",
	"desc" => "The speed of the animation. (milliseconds)",
	"id" => $scfw_shortname . "_speed",
	"type" => "text",
	"std" => '400',
	"size" => 4
);

$scfw_options['interval'] = array(
	"name" => "Auto cycle speed",
	"desc" => "Leave empty to disable auto cycling. (milliseconds)",
	"id" => $scfw_shortname . "_interval",
	"type" => "text",
	"size" => 4
);

$scfw_options['controls'] = array(
	"name" => "Type of controls",
	"desc" => "Select if you would like to add PREV and NEXT buttons.",
	"id" => $scfw_shortname . "_controls",
	"type" => "select",
	"options" => array(
		'none' => 0,
		'Above image' => 'above',
		'Under image' => 'under',
		'Before / After image' => 'beforeafter'
	),
	"std" => 0
);

$scfw_options['controls_stop'] = array(
	"name" => "Use stop button",
	"desc" => "If checked, a button to stop auto cycling will be added.",
	"id" => $scfw_shortname . "_controls_stop",
	"type" => "checkbox",
	"std" => 0
);

$scfw_options['imgclick'] = array(
	"name" => "Image click",
	"desc" => "Select what clicking the gallery image should default to.",
	"id" => $scfw_shortname . "_imgclick",
	"type" => "select",
	"options" => array(
		'Swap to next image' => 0,
		'Link original image' => 'link',
		'Do nothing' => 'nothing'
	),
	"std" => 0
);

$scfw_options['prev'] = array(
	"name" => "PREV title",
	"desc" => "Choose a different title.",
	"id" => $scfw_shortname . "_prev",
	"type" => "text",
	"size" => 4,
	"std" => 'Prev'
);

$scfw_options['next'] = array(
	"name" => "NEXT title",
	"desc" => "Choose a different title.",
	"id" => $scfw_shortname . "_next",
	"type" => "text",
	"size" => 4,
	"std" => 'Next'
);

$scfw_options['stop'] = array(
	"name" => "STOP title",
	"desc" => "Choose a different title.",
	"id" => $scfw_shortname . "_stop",
	"type" => "text",
	"size" => 4,
	"std" => 'Stop'
);

$scfw_options['caption'] = array(
	"name" => "Caption",
	"desc" => "Choose which field to use as caption.",
	"id" => $scfw_shortname . "_caption",
	"type" => "select",
	"options" => array(
		'none' => 0,
		'Use caption' => 'caption',
		'Use description' => 'desc'
	),
	"std" => 0
);

$scfw_options['counter'] = array(
	"name" => "Slide counter",
	"desc" => "If checked, slideshow will include a slide counter.",
	"id" => $scfw_shortname ."_counter",
	"type" => "checkbox",
	"std" => 0
);

$scfw_options['cycle'] = array(
	"name" => "Disable cycling",
	"desc" => "Prevent the gallery from cycling",
	"id" => $scfw_shortname . "_cycle",
	"type" => "checkbox",
	"std" => 0
);

$scfw_options['end-1'] = array(
	'type' => 'end-table'
);

$scfw_options['title-3'] = array(
	'name' => 'CSS Classes',
	'type' => 'title'
);

$scfw_options['paragraph-3'] = array(
	"value" => "Adding your own CSS classes can come in handy if you for example use a 960 based layout.<br />Add multiple classes separated by a space: <em>grid-2 my-class</em>",
	"type" => "paragraph"
);

$scfw_options['start-2'] = array(
	'type' => 'start-table'
);

$scfw_options['class-1'] = array(
	"name" => "<code>.gallery</code>",
	"id" => $scfw_shortname . "_class_gallery",
	"type" => "text",
	"size" => 20,
	"std" => ''
);

$scfw_options['class-2'] = array(
	"name" => "<code>.gallery-wrapper</code>",
	"id" => $scfw_shortname . "_class_galleryw",
	"type" => "text",
	"size" => 20,
	"std" => ''
);

$scfw_options['class-3'] = array(
	"name" => "<code>.controllers.above</code>",
	"id" => $scfw_shortname . "_class_cabove",
	"type" => "text",
	"size" => 20,
	"std" => ''
);

$scfw_options['class-4'] = array(
	"name" => "<code>.controllers.under</code>",
	"id" => $scfw_shortname . "_class_cunder",
	"type" => "text",
	"size" => 20,
	"std" => ''
);

$scfw_options['class-5'] = array(
	"name" => "<code>.controllers.before</code>",
	"id" => $scfw_shortname . "_class_cbefore",
	"type" => "text",
	"size" => 20,
	"std" => ''
);

$scfw_options['class-6'] = array(
	"name" => "<code>.controllers.after</code>",
	"id" => $scfw_shortname . "_class_cafter",
	"type" => "text",
	"size" => 20,
	"std" => ''
);

$scfw_options['end-2'] = array(
	'type' => 'end-table'
);

$scfw_options['title-4'] = array(
	'name' => 'Other',
	'type' => 'title'
);

$scfw_options['start-3'] = array(
	'type' => 'start-table'
);

$scfw_options['jquery'] = array(
	"name" => "Disable jQuery",
	"desc" => "Don't load latest version of jQuery from Google Libraries API<strong>*</strong>",
	"id" => $scfw_shortname . "_jquery",
	"type" => "checkbox",
	"std" => 0
);

$scfw_options['end-3'] = array(
	'type' => 'end-table'
);

$scfw_options['paragraph-4'] = array(
	'value' => '<small><strong>*</strong> sexyCycle depends on jQuery 1.4+ and if you disable it from loading here, make sure it\'s loaded elsewhere.</small>',
	'type' => 'paragraph'
);


function scfw_options() {
	global $scfw_pluginname, $scfw_shortname, $scfw_options;

	if ( 'save' == $_REQUEST['action'] ) {

		$values = array();
		foreach ($scfw_options as $value) {
			if ($value['id']) {
				$values[$value['id']] = $_REQUEST[$value['id']];
			}
		}

		if ($values[$scfw_shortname . '_interval']) {
			// Disable controls if an interval is set
			$values[$scfw_shortname . '_controls'] = '';
			unset($scfw_options['controls']);
			unset($scfw_options['prev']);
			unset($scfw_options['next']);
			unset($scfw_options['imgclick']);
		}
		else {
			// Otherwise disable stop function
			$values[$scfw_shortname . '_controls_stop'] = NULL;
			unset($scfw_options['controls_stop']);
			unset($scfw_options['stop']);
		}

		update_option($scfw_shortname . '_settings', $values);
	}

	$scfw_settings = get_settings('scfw_settings');

	if ($scfw_settings[$scfw_shortname . '_interval']) {
		// Disable controls if an interval is set
		unset($scfw_options['controls']);
		unset($scfw_options['prev']);
		unset($scfw_options['next']);
		unset($scfw_options['imgclick']);
	}
	else {
		// Otherwise disable stop function
		unset($scfw_options['controls_stop']);
		unset($scfw_options['stop']);
	}

	if ( $_REQUEST['save'] ) echo '<div id="message" class="updated fade"><p><strong>' . __( 'Options saved.' ) . '</strong></p></div>';
	if ( $_REQUEST['reset'] ) echo '<div id="message" class="updated fade"><p><strong>' . __( 'Options restored.' ) . '</strong></p></div>';
?>

<div class="wrap">
<h2><?php echo $scfw_pluginname; ?> settings</h2>

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
<h3><?php echo __($value['name']); ?></h3>
<?php
break;

case 'paragraph':
?>
<p><?php echo $value['value']; ?></p>
<?php
break;

case 'text':
$set_value = $scfw_settings[$value['id']] ? $scfw_settings[$value['id']] : $value['std'];
?>
	<tr valign="top">
		<th scope="row"><label for="<?php echo $value['id']; ?>"><?php echo $value['name']; ?></label></th>
		<td>
			<input size="<?php echo $value['size']; ?>" name="<?php echo $value['id']; ?>" id="<?php echo $value['id']; ?>" type="<?php echo $value['type']; ?>" value="<?php echo htmlspecialchars(stripslashes($set_value)); ?>" />
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