package Wallboard::DB;
use strict;
use warnings;
use Config::Simple;
use DBI;

use Exporter qw(import);

our @EXPORT = qw($cfg
                 get_status_id_by_name
                 get_status_id_by_color
                 get_status_name_by_id
                 get_status_color_by_id
                 get_status_color_list);

our $cfg = new Config::Simple('/opt/wallboard_monitor/conf_files/db.conf');

sub get_status_id_by_name {
    my $name  = shift(@_);
    my $id    = 0;
    my $query = 'select STATUS_ID from Status_Table where STATUS_NAME="'.$name.'"';
    my $dbh = DBI->connect('dbi:mysql:'.$cfg->param('name'),
			   $cfg->param('user'),
			   $cfg->param('pass'));
    my $sth = $dbh->prepare($query);
    $sth->execute;
    ($id)   = $sth->fetchrow_array;
    $sth->finish();
    $dbh->disconnect();
    return $id;
}

sub get_status_id_by_color {
    my $color = shift(@_);
    my $id    = 0;
    my $query = 'select STATUS_ID from Status_Table where STATUS_COLOR="'.$color.'"';
    my $dbh = DBI->connect('dbi:mysql:'.$cfg->param('name'),
                           $cfg->param('user'),
                           $cfg->param('pass'));
    my $sth = $dbh->prepare($query);
    $sth->execute;
    ($id)   = $sth->fetchrow_array;
    $sth->finish();
    $dbh->disconnect();
    return $id;
}

sub get_status_name_by_id {
    my $id    = shift(@_);
    my $name  = '';
    my $query = 'select STATUS_NAME from Status_Table where STATUS_ID='.$id;
    my $dbh = DBI->connect('dbi:mysql:'.$cfg->param('name'),
                           $cfg->param('user'),
                           $cfg->param('pass'));
    my $sth = $dbh->prepare($query);
    $sth->execute;
    ($name) = $sth->fetchrow_array;
    $sth->finish();
    $dbh->disconnect();
    return $name;
}

sub get_status_color_by_id {
    my $id    = shift(@_);
    my $color = '';
    my $query = 'select STATUS_COLOR from Status_Table where STATUS_ID='.$id;
    my $dbh = DBI->connect('dbi:mysql:'.$cfg->param('name'),
                           $cfg->param('user'),
                           $cfg->param('pass'));
    my $sth = $dbh->prepare($query);
    $sth->execute;
    ($color) = $sth->fetchrow_array;
    $sth->finish();
    $dbh->disconnect();
    return $color;
}

sub get_status_color_list {
    my @colors;
    my $query = 'select STATUS_COLOR from Status_Table';
    my $dbh = DBI->connect('dbi:mysql:'.$cfg->param('name'),
                           $cfg->param('user'),
			   $cfg->param('pass'));
    my $sth = $dbh->prepare($query);
    $sth->execute;
    while (my @row = $sth->fetchrow_array) {
	push(@colors,
	     $row[0]);
    }
    $sth->finish();
    $dbh->disconnect();
    return @colors;
}
1;
