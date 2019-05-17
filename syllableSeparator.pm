package syllableSeparator;
use strict;
use warnings;
use utf8;
use Exporter 'import';
our $VERSION = '1.00';
our @ISA= qw( Exporter );

# these CAN be exported.
our @EXPORT_OK = qw( loadDatabase );
our @EXPORT = qw( loadDatabase );

sub loadDatabase{
 my $database = shift;
 print $database, "\n";
 my $line;
 my %dict;
 my $count = 0;
 my $key;
 open(DATA, "<".$database) or die "Couldn't open file $database, $!";
 while(<DATA>){
  $count++;
  $line = $_;
  chomp($line);
  ($key = $line) =~ s/\s/_/g;
  #assume que a busca de palavras como "a priori" sera feita buscando a chave a_priori, ja que usaremos espaco para separar palavras
  $key =~ s/¥//g;
  $key = substr $key,0,((length $key) - 1);
  print "-$key--\n";
  $line =~ s/¥/ /g;
  $dict{$key} = $line;
 } 
 close(DATA) || die "Couldn't close file properly";
 print "Total dict lines: ",$count,"\n";
 print \%dict;
 return \%dict;
}

1;
