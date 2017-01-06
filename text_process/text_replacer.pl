#!/home/utils/perl-5.18/5.18.4-003/bin/perl

use strict;
use warnings;


my $filename = 'undef';
GetOptions("file=s" => \$filename);

my $data = read_file($filename);

# replace original_string and new_string before running this script
# you can repeat below code to replace mutiple strings at one time.
$data =~ ( s/<original_string>/<new_string>/g);

write_file($filename, $data);
exit;

sub read_file {
    my ($filename) = @_;

    open my $in, '<:encoding(UTF-8)', $filename or die "Could not open '$filename' for reading $!";
    local $/ = undef;
    my $all = <$in>;
    close $in;

    return $all;
}

sub write_file {
    my ($filename, $content) = @_;

    open my $out, '>:encoding(UTF-8)', $filename or die "Could not open '$filename' for writing $!";;
    print $out $content;
    close $out;

    return;
}