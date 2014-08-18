#!/usr/bin/perl
use strict;
use Image::Magick;
use Wallboard::DB;

my @colors = get_status_color_list();

for (my $x = 0;$x < $#colors + 1; $x++) {
    print "Generating ".$colors[$x]." images\n";
    my $image = Image::Magick->new;
    $image->Set(size=>'5x200');
    $image->Read("gradient:".$colors[$x]."-black");
    $image->Rotate(-90);
    $image->Write("jpg:/opt/wallboard_monitor/wallboard_web/images/".$colors[$x]."-bg.jpg");
    # Clean up
    undef $image;
    
    my $image = Image::Magick->new;
    $image->Set(size=>'5x200');
    $image->Read("gradient:".$colors[$x]."-black");
    $image->Rotate(90);
    $image->Write("jpg:/opt/wallboard_monitor/wallboard_web/images/".$colors[$x]."-bg2.jpg");
    # Clean up
    undef $image;
    
    my $circle = Image::Magick->new(size=>'25x25');
    $circle->ReadImage('radial-gradient:'.$colors[$x].'-black');
    $circle->Write(filename=>'/opt/wallboard_monitor/wallboard_web/images/'.$colors[$x].'.png');
    undef $circle;
}
