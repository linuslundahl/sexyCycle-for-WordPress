/**
 * jQuery sexyCycle v0.3 (With alterations)
 *
 * Terms of Use - jQuery sexyCycle
 * under the MIT (http://www.opensource.org/licenses/mit-license.php) License.
 *
 * Copyright 2010 suprb.com All rights reserved.
 * (http://suprb.com/apps/sexyCycle/)
 */

//Was no commenting here so it's pretty difficult to understand what each of these is referencing, going through and adding comments
(function ($) {

    $.fn.sexyCycle = function (options) {

        // default configuration properties
        var defaults = {
            easing: 'easeOutExpo',
            speed: 400,
            next: null,
            prev: null,
            start: 0,
            interval: false,
            cycle: true,
            imgclick: true,
            counter: null
        };

        var options = $.extend(defaults, options);
        var box = this;
        var click = true;
        var sexyCycle = $(".sexyCycle-wrap", this);
        var count = options.start;
        var totalw = $(box).width();

        //No idea what this block of code is accomplishing
        var img = $(".sexyCycle-content img:eq(0)", sexyCycle).attr('src'); //This sets img to the source of the first image
        $('body').append('<span class="sexycycleimgtempload"></span>');     //Creates a temporary span 
        $('.sexycycleimgtempload').hide();                                  //hides the temporary span ... why

        var _tmph = 0,
            _left = 0,
            _cn = 0;
        var _th = $(".sexyCycle-content img:eq(0)", sexyCycle).height();

        $(sexyCycle).height(_th);                                           //Sets the height of the Gallery to the height of the first image

        $('.sexycycleimgtempload').remove();                                //Now the temporary span has been removed with nothing ever being done to it ?!?!?

        var _t = $(".sexyCycle-content", sexyCycle).children().size();                      //This checks how many images are part of this gallery, I assume _t stands for "Total"
        var _p = $(".sexyCycle-content img:eq(" + options.start + ")", sexyCycle).width();  //This is the width of the starting image
        var _f = $(".sexyCycle-content img:eq(0)", sexyCycle);                              //This is setting a reference to the first image in the gallery
        var _l = $(".sexyCycle-content img:eq(" + (_t - 1) + ")", sexyCycle);               //This is setting a refernce to the last image in the gallery

        var _tmp = $(".sexyCycle-content img:eq(" + (_t - 1) + ")", sexyCycle).attr('src');
        var _tmph = $(".sexyCycle-content img:eq(" + (_t - 1) + ")", sexyCycle).height();
        var _tmpw = $(".sexyCycle-content img:eq(" + (_t - 1) + ")", sexyCycle).width();

        var _tmpe = $(".sexyCycle-content img:eq(0)", sexyCycle).attr('src');
        var _tmphe = $(".sexyCycle-content img:eq(0)", sexyCycle).height();
        var _tmpwe = $(".sexyCycle-content img:eq(0)", sexyCycle).width();

        for (_lc = 0; _lc < options.start; _lc++) {
            _left += $(".sexyCycle-content img:eq(" + _lc + ")", sexyCycle).width();
        }

        //Initiate the counter 
        if( $(options.counter).length > 0 ){
            $(options.counter).html("<span style='counter-text'>"+ (count+1) +" of "+ _t +"</span>");
        }
        //Another set of temporary spans that I'm not sure why they exist
        $('<span class="sexyCycleTempf" style="background: url(\'' + _tmp + '\'); float: left; width: ' + _tmpw + 'px; height: ' + _tmph + 'px; display: block"></span>').insertBefore($(".sexyCycle-content li:eq(0)", sexyCycle));
        $(".sexyCycleTempf", sexyCycle).css("display", "none");

        $('<span class="sexyCycleTempe" style="background: url(\'' + _tmpe + '\'); float: left; width: ' + _tmpwe + 'px; height: ' + _tmphe + 'px; display: block"></span>').insertAfter($(".sexyCycle-content li:eq(" + (_t - 1) + ")", sexyCycle));
        $(".sexyCycleTempe", sexyCycle).css("display", "none");

        var _w = _p;

        $("li", sexyCycle).css("float", "left");
        $(box).css('width', _w + 'px'); //Set the box surrounding the images to the width of the first image

        $(".sexyCycle-content", sexyCycle).animate({
            'left': '-=' + _left + 'px'
        }, {
            duration: 0
        });

        var _cap_height = 0;
        if( $(".sexyCycle-content li:eq(0)", sexyCycle).find('span').height() != null ) // If there's a caption
            _cap_height = $(".sexyCycle-content li:eq(0)", sexyCycle).find('span').height(); 

        //Set the box height
        var _h = $(sexyCycle).height() + $('.controllers', box).height() + _cap_height;
        $(box).css("height", (_h + "px")); //Set the heightof the box to the height of the first image + the controllers + caption height
        if( _cap_height > 0 ){ //If the caption height > 0, resize the box
            $(box).css('height', _h + 'px');
            $(".sexyCycle-wrap", sexyCycle).css("height", _h);
            $(".sexyCycle-content li .gallery-caption", sexyCycle).css("top", _th + 'px'); //Reposition to the height of 1st image
        }

        $(options.next).click(function () {
            slide('+');  //Set the value of clicking the next button to "+"
        });

        $(options.prev).click(function () {
            slide('-');  //Set the value of clicking the prev button to "-"
        });

        if (options.imgclick) {     //If the user selected the option in the admin to have onclick image progression, enable it here
          $(sexyCycle).click(function () {
              slide('+');
          });
        }

        if (options.interval != false) {
            var e = options.stop;
            timer(e);
        }

        $(options.stop).click(function () {
            stop(e);
        });

        function timer() {
            slide('+');
            e = setTimeout(timer, options.interval);
        }

        function stop(d) {
            clearInterval(e)
        }

        function slide(_e) {

            if (click == true) {

                click = false;
                //Clicking on next and prev, increments and decrements (respectively) the value of slideto by the width of the next or previous (respectively) image
                if (_e == "-") {
                    slideto = "+=";
                    _cn = count - 1;
                    _p = $(".sexyCycle-content img:eq(" + (_cn ) + ")", sexyCycle).width();
                } else {
                    slideto = "-=";
                    _cn = count + 1;
                    _p = $(".sexyCycle-content img:eq(" + (_cn - 1) + ")", sexyCycle).width();
                }

                if (_cn - 1 < _t - 1 && _cn - 1 >= -1) {

                    _w = $(".sexyCycle-content img:eq(" + _cn + ")", sexyCycle).width();
                    _h = $(".sexyCycle-content img:eq(" + _cn + ")", sexyCycle).height();
                    _img_h = _h;
                    _cap_height = $(".sexyCycle-content li:eq("+_cn+")", sexyCycle).find('span').height(); //Find the height of the caption
                    if(_cap_height != null){ //If there is a caption, make sure that the box is resized for it to fit and it's properly positioned
                        _h += _cap_height;
                        $(".sexyCycle-wrap", sexyCycle).css("height", _h);
                        $(".sexyCycle-content li .gallery-caption", sexyCycle).css("top", _img_h + 'px');
                    }
                    $(".sexyCycle-content", sexyCycle).animate({
                        'left': slideto + _p + 'px'
                    }, {
                        duration: options.speed,
                        easing: options.easing
                    });
                    $(box).animate({
                        'width': _w + 'px',
                        'height' : _h + 'px'
                    }, {
                        duration: options.speed,
                        easing: options.easing,
                        complete: function () {
                            click = true;
                        }
                    });

                    count = _cn;

                } else {


                    if (options.cycle == true) {

                        if (_e == "+") {

                            count = 0;
                            _cn = 0;

                            $(".sexyCycleTempf", sexyCycle).css("display", "block");
                            $(".sexyCycle-content", sexyCycle).css('left', '0px');
                            $(".sexyCycle-content", sexyCycle).animate({
                                'left': slideto + _p + 'px'
                            }, {
                                duration: options.speed,
                                easing: options.easing
                            });

                        } else {

                            count = _t - 1;
                            _cn = _t - 1;

                            $(".sexyCycleTempe", sexyCycle).css("display", "block");
                            $(".sexyCycle-content", sexyCycle).css('left', '-' + $(".sexyCycleTempe", sexyCycle).position().left + 'px');
                            $(".sexyCycle-content", sexyCycle).animate({
                                'left': slideto + _tmpw + 'px'
                            }, {
                                duration: options.speed,
                                easing: options.easing
                            });

                        }

                        _w = $(".sexyCycle-content img:eq(" + count + ")", sexyCycle).width();
                        _h = $(".sexyCycle-content img:eq(" + count + ")", sexyCycle).height();
                        _img_h = _h;
                        _cap_height = $(".sexyCycle-content li:eq("+_cn+")", sexyCycle).find('span').height(); //Find the height of the caption
                        if(_cap_height != null){ //If there is a caption, make sure that the box is resized for it to fit and it's properly positioned
                            _h += _cap_height;
                            $(".sexyCycle-wrap", sexyCycle).css("height", _h);
                            $(".sexyCycle-content li .gallery-caption", sexyCycle).css("top", _img_h + 'px');
                        }

                        $(box).animate({
                            'width': _w + 'px',
                            'height': _h + 'px'
                        }, {
                            duration: options.speed,
                            easing: options.easing,
                            complete: function () {
                                click = true;
                            }
                        });

                    } else {
                        click = true;
                    }
                }

            }
            //Update the counter 
            if( $(options.counter).length > 0 ){
                $(options.counter).html("<span style='counter-text'>"+ (count+1) +" of "+ _t +"</span>");
            }
        }
    };

})(jQuery);