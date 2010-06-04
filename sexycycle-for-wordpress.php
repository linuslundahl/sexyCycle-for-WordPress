<?php

/* 
Plugin Name: sexyCycle for WordPress
Plugin URI: http://github.com/linuslundahl/sexyCycle-for-WordPress/
Description: Uses <a href="http://suprb.com/apps/sexyCycle/">sexyCycle jQuery plugin</a> to cycle through gallery images. (sexyCycle created by <a href="http://suprb.com/">Andreas Pihlström</a>)
Version: 0.4
Author: Linus Lundahl
Author URI: http://unwise.se
*/

require_once(dirname(__FILE__).'/inc/admin.inc');

$scfw_settings = get_settings('scfw_settings');

if (!defined('SCFW_PLUGIN_BASENAME')) {
  define('SCFW_PLUGIN_BASENAME', plugin_basename(__FILE__));
}

if (is_admin()) {
  add_action('admin_menu', 'scfw_menu', -999);
}
else {
  add_action('wp_head', 'scfw_add_css');
  if (!$scfw_settings['scfw_jquery']) {
    wp_deregister_script('jquery');
    wp_enqueue_script('jquery', 'http://ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js', false, '1.4+', false);
  }
  wp_enqueue_script('easing', WP_PLUGIN_URL . '/' . plugin_basename(dirname(__FILE__)) . "/inc/jquery.easing-packed.js", false, '1.3', false);
  wp_enqueue_script('sexycycle', WP_PLUGIN_URL . '/' . plugin_basename(dirname(__FILE__)) . "/inc/jquery.sexyCycle-packed.js", false, '0.3', false);
  if ($scfw_settings['scfw_override']) {
    add_filter('post_gallery', 'scfw_gallery_shortcode', 10, 2);
  }
  add_shortcode('sexy-gallery', 'scfw_sexy_gallery_shortcode');
}

// Add CSS
function scfw_add_css() {
  echo '<link rel="stylesheet" href="' . WP_PLUGIN_URL . '/' . plugin_basename(dirname(__FILE__)) . '/inc/sexyCycle.css' . '" type="text/css" media="screen" />'."\n";
}

// Custom sexy-gallery output
function scfw_sexy_gallery_shortcode($attr) {
  return scfw_gallery_shortcode(NULL, $attr);
}

// Custom gallery output
function scfw_gallery_shortcode($null, $attr = array()) {
  global $post, $wp_locale, $scfw_settings;

  extract(shortcode_atts(array(
    'order'         => 'ASC',
    'orderby'       => 'menu_order ID',
    'id'            => $post->ID,
    'itemtag'       => 'ul',
    'icontag'       => 'li',
    'captiontag'    => 'span',
    'size'          => $scfw_settings['scfw_img_size'] ? $scfw_settings['scfw_img_size'] : 'large',
    'prev'          => $scfw_settings['scfw_prev'] ? stripslashes($scfw_settings['scfw_prev']) : 'Prev',
    'counter'       => $scfw_settings['scfw_counter'] ? $scfw_settings['scfw_counter'] : NULL,
    'next'          => $scfw_settings['scfw_next'] ? stripslashes($scfw_settings['scfw_next']) : 'Next',
    'stop'          => $scfw_settings['scfw_stop'] ? $scfw_settings['scfw_stop'] : 'Stop',
    'animation'     => $scfw_settings['scfw_animation'] ? $scfw_settings['scfw_animation'] : 'easeOutExpo',
    'controls'      => $scfw_settings['scfw_controls'] ? $scfw_settings['scfw_controls'] : '0',
    'controls_stop' => $scfw_settings['scfw_controls_stop'] ? $scfw_settings['scfw_controls_stop'] : NULL,
    'speed'         => $scfw_settings['scfw_speed'] ? $scfw_settings['scfw_speed'] : '400',
    'interval'      => $scfw_settings['scfw_interval'] ? $scfw_settings['scfw_interval'] : '',
    'caption'       => $scfw_settings['scfw_caption'] ? $scfw_settings['scfw_caption'] : '0',
    'counter'       => $scfw_settings['scfw_counter'] ? $scfw_settings['scfw_counter'] : '0',
    'cycle'         => $scfw_settings['scfw_cycle'] ? $scfw_settings['scfw_cycle'] : NULL,
    'imgclick'      => $scfw_settings['scfw_imgclick'] ? $scfw_settings['scfw_imgclick'] : '0'
  ), $attr));

  $id = intval($id);

  $attachments = get_children(array(
    'post_parent'     => $id,
    'post_status'     => 'inherit',
    'post_type'       => 'attachment',
    'post_mime_type'  => 'image',
    'order'           => $order,
    'orderby'         => $orderby,
  ));

  if (empty($attachments)) {
    return '';
  }

  if (is_feed()) {
    $ret = "\n";
    foreach ( $attachments as $att_id => $attachment ) {
      $ret .= wp_get_attachment_link($att_id, 'small', true) . "\n";
    }
  }

  if (!$ret) {
    $itemtag = tag_escape($itemtag);

    // Build JS settings
    if ($speed || $animation || $controls || $cycle) {
      $js = "{";

      if ($speed) {
        $js .= "speed: " . $speed . "," ;
      }

      if ($animation) {
        $js .= "easing: '" . $animation . "',";
      }

      if ($controls) {
        $js .= "next: '#next-$id',prev: '#prev-$id',";
      }

      if ($cycle) {
        $js .= "cycle: false,";
      }

      if ($interval) {
        $js .= "interval: " . $interval . ",";
      }

      if ($controls_stop) {
        $js .= "stop: '#stop-$id',";
      }

      if ($imgclick == 'nothing') {
        $js .= "imgclick: false,";
      }
	  
	  if ($counter) {
		$js .= "counter: '#counter-$id',";
	  }
      $js = rtrim($js, ',');

      $js .= "}";
    }

    // Get user defined classes
    $class_gallery  = $scfw_settings['scfw_class_gallery'] ? ' ' . str_replace('.', '', $scfw_settings['scfw_class_gallery']) : '';
    $class_galleryw = $scfw_settings['scfw_class_galleryw'] ? ' ' . str_replace('.', '', $scfw_settings['scfw_class_galleryw']) : '';
    $class_cabove   = $scfw_settings['scfw_class_cabove'] ? ' ' . str_replace('.', '', $scfw_settings['scfw_class_cabove']) : '';
    $class_cunder   = $scfw_settings['scfw_class_cunder'] ? ' ' . str_replace('.', '', $scfw_settings['scfw_class_cunder']) : '';
    $class_cbefore  = $scfw_settings['scfw_class_cbefore'] ? ' ' . str_replace('.', '', $scfw_settings['scfw_class_cbefore']) : '';
    $class_cafter   = $scfw_settings['scfw_class_cafter'] ? ' ' . str_replace('.', '', $scfw_settings['scfw_class_cafter']) : '';

    // Begin gallery output
    $ret .= "<div class=\"gallery" . $class_gallery . "\">\n";

    // Add JS for each gallery
    $ret .= apply_filters('gallery_style', "<script type=\"text/javascript\">jQuery(function($) { $(\"#box-$id\").sexyCycle($js); });</script>\n");

    // Controls (prev)
    if ($counter) {
      $ret .= "  <div id=\"counter-$id\" class=\"counter\"></div>\n";
    }
    if ($controls == 'above') {
      $ret .= "  <div class=\"controllers above" . $class_cabove . "\"><span id=\"prev-$id\" class=\"prev cursor\">" . $prev . "</span><span id=\"next-$id\" class=\"next cursor\">" . $next . "</span></div>\n";
    }
    if ($controls == 'beforeafter') {
      $ret .= "  <div class=\"controllers before" . $class_cbefore . "\"><span id=\"prev-$id\" class=\"prev cursor\">" . $prev . "</span></div>\n";
    }

    $ret .= "<div class=\"gallery-wrapper" . $class_galleryw . "\">\n";

    $ret .= "<div class=\"sexyCycle\" id=\"box-$id\">\n";
    $ret .= "  <div class=\"sexyCycle-wrap\">\n";
    $ret .= "  <{$itemtag} class=\"sexyCycle-content\">\n";

    // Create list items with images
    foreach ( $attachments as $gallery_id => $attachment ) {
      $link = wp_get_attachment_image($gallery_id, $size, true, false);
      $ret .= "    <{$icontag}>";

      // Image link
      if ($imgclick == 'link') {
        $ret .= "<a href=\"" . $attachment->guid . "\" alt=\"" . $attachment->post_name . "\">";
      }

      $ret .= "$link";

      // Caption
      if ($caption == 'caption' && trim($attachment->post_excerpt)) {
        $ret .= "<{$captiontag} class='gallery-caption'>" . wptexturize($attachment->post_excerpt) . "</{$captiontag}>";
      }
      else if ($caption == 'desc' && trim($attachment->post_content)) {
        $ret .= "<{$captiontag} class='gallery-caption'>" . wptexturize($attachment->post_content) . "</{$captiontag}>";
      }

      // End image link
      if ($imgclick == 'link') {
        $ret .= "</a>";
      }

      $ret .= "</{$icontag}>\n";
    }

    $ret .= "  </{$itemtag}>\n";
    $ret .= "  </div>\n";
    $ret .= "</div>\n";

    // Controls (prev / next)
    if ($controls == 'under') {
      $ret .= "  <div class=\"controllers under" . $class_cunder . "\"><span id=\"prev-$id\" class=\"prev cursor\">" . $prev . "</span><span id=\"next-$id\" class=\"next cursor\">" . $next . "</span></div>";
    }

    // Controls (stop)
    if ($controls_stop) {
      $ret .= "  <div class=\"controllers stop\"><span id=\"stop-$id\" class=\"stop cursor\">" . $stop . "</span></div>";
    }

    $ret .= "</div>\n";

    // Controls (next)
    if ($controls == 'beforeafter') {
      $ret .= "  <div class=\"controllers after" . $class_cafter . "\"><span id=\"next-$id\" class=\"next cursor\">" . $next . "</span></div>\n";
    }

    // End gallery output
    $ret .= "</div>\n";

  }

  return $ret;
}

?>