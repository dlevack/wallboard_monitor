package WallboardDB;
use strict;
use warnings;
use Config::Simple;

use Exporter qw(import);

our @EXPORT = qw($cfg);

our $cfg = new Config::Simple('../conf_files/db.conf');

1;
