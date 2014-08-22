wallboard_monitor
=================

This is a project that was inspired by my previous job. I Wrote a system based on the Big Brother monitoring system. I had always been
a fan of the Big Brother system due to the way it displays the data. The graphics cause the page to draw your attention from accross
the room when there is an issue that needs to be looked at.

What I was not a huge fan of was the way that it handles updated information. Basicly the data it recieves from the systems that it is
monitoring is stored in text files and then another script runs on a schedule to regenerate statis html pages based off of the data in
the text files. Then once the html page is regenerated the meta refresh will cause the page to display the updated information. By default
the system regenerates the html pages every five minutes. While you can tweak the settings to get better performace, it is extra work to
get your monitoring system displaying closer to realtime information.

Basicly, this system does a lot of the same things. The big difference is the data being stored in a MySQL database with PHP pages displaying
the information and pulling realtime data from the database. Once the system recieves an update that information is displayed once the page
refreshes.

Unfortunatly, all of the code written for my previous job is still there and I am not. So, I will be rewriting it from scratch.

One upside of rewriting it from scratch is the ability to write better code. Originally the system was writen Perl, PHP, and bash scripts. For this
rewite I am attemting to write portions in C++ which should provide improved performance.

Requirements
------------

Tested with the following. May work on earlier versions but has not been tested.

- IE 10 or higher (If using IE to view site)
- Apache 2.2
- MySQL 5.1.73-3
- Perl 5.10.1-136
- PHP 5.3.3-27
- Perl Modules
 - Config::Simple
 - DBI
 - Image::Magick
