package fileStats;
use strict;
use warnings;
use Exporter 'import';
our $VERSION = '1.00';
our @ISA= qw( Exporter );
# these CAN be exported.
our @EXPORT_OK = qw(fileStats);
our @EXPORT = qw(fileStats);

sub fileStats {
 my $fd = shift;
 my $fDescriptor;
 open($fDescriptor, "<&=$fd");
 my $line;
 my @words;
 my $totalWords = 0;
 my $totalEstrofes = 0;
 my $totalVersos = 0;
 my @stats;
 while($line = <$fDescriptor>){
  if(length($line) eq 1)
  {
   $totalEstrofes = $totalEstrofes + 1;
  }
  else
  {
   chomp($line);
   @words = split(/\s/,$line);
   $totalWords =  $totalWords + scalar @words;
   $totalVersos = $totalVersos + 1; 
  }
 }
 $totalEstrofes = $totalEstrofes + 1;
 push @stats,$totalWords;
 push @stats,$totalVersos;
 push @stats,$totalEstrofes;
 close($fDescriptor) || die "Couldn't close file properly";
 return @stats;
}
1;
