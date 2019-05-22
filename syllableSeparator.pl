use strict;
use warnings;
use utf8;

sub loadDatabase{
 my $database = shift;
 #print $database, "\n";
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
  #print "-$key--\n";
  $line =~ s/¥/ /g;
  $dict{$key} = $line;
 } 
 close(DATA) || die "Couldn't close file properly";
 #print "Total dict lines: ",$count,"\n";
 #print \%dict;
 return \%dict;
}


my $key;
my $value;
my $data = loadDatabase("mhyph.txt");
print $data;
#while(($key, $value) = each(%$data)) {
#    print "$key => $value\n";
#}
my $var = "a_cappella";
my @aux = split(/\s/,$data->{$var});
print "a cappella = " . @aux . "\n";
print "a cappella last syllable= " . $aux[(scalar @aux) - 1] . "\n";
