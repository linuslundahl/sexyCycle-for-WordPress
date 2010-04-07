<?php

/* 
Plugin Name: SexyCycle for WordPress
Plugin URI: http://github.com/linuslundahl/SexyCycle-for-WordPress/
Description: Uses <a href="http://suprb.com/apps/sexyCycle/">SexyCycle jQuery plugin</a> to cycle through gallery images. (SexyCycle created by <a href="http://suprb.com/">Andreas Pihlström</a>)
Version: 0.1-dev
Author: Linus Lundahl
Author URI: http://unwise.se
*/

require_once(dirname(__FILE__).'/inc/admin.inc');

if (!defined('SCFW_PLUGIN_BASENAME')) {
  define('SCFW_PLUGIN_BASENAME', plugin_basename(__FILE__));
}

if (is_admin()) {
  add_action('admin_menu', 'scfw_menu', -999);
} else {
  add_action('wp_head', 'scfw_add_css');
  wp_enqueue_script('easing', WP_PLUGIN_URL . '/' . plugin_basename(dirname(__FILE__)) . "/inc/jquery.easing.js", false, '1.3', true);
  wp_enqueue_script('sexycycle', WP_PLUGIN_URL . '/' . plugin_basename(dirname(__FILE__)) . "/inc/jquery.sexyCycle-packed.js", false, '0.3', true);
  if (!get_settings('scfw_jquery')) {
    wp_deregister_script('jquery');
    wp_enqueue_script('jquery', 'http://ajax.googleapis.com/ajax/libs/jquery/1/jquery.min.js');
  }
  add_filter('post_gallery', 'scfw_gallery_shortcode', 10, 2);
}

// Add CSS
function scfw_add_css() {
  echo '<link rel="stylesheet" href="' . WP_PLUGIN_URL . '/' . plugin_basename(dirname(__FILE__)) . '/inc/sexyCycle.css' . '" type="text/css" media="screen" />'."\n";
}

// Custom gallery output
function scfw_gallery_shortcode( $output, $attr ) {
  global $post, $wp_locale;

  extract(shortcode_atts(array(
    'order'      => 'ASC',
    'orderby'    => 'menu_order ID',
    'id'         => $post->ID,
    'itemtag'    => 'ul',
    'icontag'    => 'li',
    'size'       => 'large',
  ), $attr));

  $id = intval($id);

  $attachments = get_children( array('post_parent' => $id, 'post_status' => 'inherit', 'post_type' => 'attachment', 'post_mime_type' => 'image', 'order' => $order, 'orderby' => $orderby) );

  if (empty($attachments)) {
    return '';
  }

  if (is_feed()) {
    $output = "\n";
    foreach ( $attachments as $att_id => $attachment ) {
      $output .= wp_get_attachment_link($att_id, 'small', true) . "\n";
    }
  }

  if (!$output) {
    $itemtag = tag_escape($itemtag);

    // Build JS settings
      $animation = get_settings('scfw_animation');
      $speed = get_settings('scfw_speed');
      $controls = get_settings('scfw_controls');
      $cycle = get_settings('scfw_cycle');

      if ($speed || $animation) {
        $js = "{";
        if ($speed) {
          $js .= "speed: '$speed',";
        }

        if ($animation) {
          $js .= "easing: '$animation',";
        }

        if ($controls) {
          $js .= "next: '#next-$id',prev: '#prev-$id',";
        }

        if ($cycle) {
          $js .= "cycle: false,";
        }
        $js .= "}";
      }

    // Add JS for each gallery
    $output = apply_filters('gallery_style', "<script type=\"text/javascript\">$(document).ready(function() { $(\"#box-$id\").sexyCycle($js); });</script>\n");

    // Controls (prev)
    if ($controls == 'beforeafter') {
      $output .= "<span id=\"prev-$id\" class=\"prev cursor before\">Prev</span>";
    }

    $output .= "<div class=\"sexyCycle\" id=\"box-$id\">\n";
    $output .= "  <div class=\"sexyCycle-wrap\">\n";
    $output .= "  <{$itemtag} class=\"sexyCycle-content\">\n";

    // Create list items with images
    foreach ( $attachments as $gallery_id => $attachment ) {
      $link = wp_get_attachment_image($gallery_id, $size, false, false);
      $output .= "    <{$icontag}>$link</{$icontag}>\n";
    }

    $output .= "  </{$itemtag}>\n";
    $output .= "  </div>\n";

    // Controls (prev / next)
    if ($controls == 'under') {
      $output .= "	<div class=\"controllers\"><span id=\"prev-$id\" class=\" prev cursor\">Prev</span><span id=\"next-$id\" class=\"next cursor\">Next</span></div>";
    }

    $output .= "</div>\n";

    // Controls (next)
    if ($controls == 'beforeafter') {
      $output .= "<span id=\"next-$id\" class=\"next cursor after\">Next</span>";
    }

  }

  return $output;
}

?>