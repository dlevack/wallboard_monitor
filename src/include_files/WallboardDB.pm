package WallboardDB;
use strict;
use warnings;
use Config::Simple;
use DBI;

use Exporter qw(import);

our @EXPORT = qw($cfg get_status_id_by_name);

our $cfg = new Config::Simple('../conf_files/db.conf');

sub get_status_id_by_name {
    my $name  = shift(@_);
    my $id    = 0;
    my $query = 'select STATUS_ID from Status_Table where STATUS_NAME="'.$name.'"';
    my $dbh = DBI->connect('dbi:mysql:'.$cfg->param('name'),
			   $cfg->param('user'),
			   $cfg->param('pass'));
    my $sth = $dbh->prepare($query);
    $sth->execute;
    my @row = $sth->fetchrow_array;
    $id     = $row[0];
    undef @row;
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
    my @row = $sth->fetchrow_array;
    $id     = $row[0];
    undef @row;
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
    my @row = $sth->fetchrow_array;
    $name   = $row[0];
    undef @row;
    $sth->finish();
    $dbh->disconnect();
    return $id;
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
    my @row = $sth->fetchrow_array;
    $color  = $row[0];
    undef @row;
    $sth->finish();
    $dbh->disconnect();
    return $id;
}

1;
