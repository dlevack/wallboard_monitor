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

Unfortunatly, all of the code written for my previous job is still there and I am not. So, I will be rewiting it from scratch.

Requirements
------------

- MySQL 5
- Perl 5
- PHP 5
- Perl Modules
 - Config::Simple