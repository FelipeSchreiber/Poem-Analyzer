use strict;
use warnings;

sub loadPhonemes{
 my $database = shift;
 print $database, "\n";
 my $line;
 my %dict;
 my $count = 0;
 my $key;
 open(DATA, "<".$database) or die "Couldn't open file $database, $!";
 while(<DATA>){
  while($count < 57)
  {
   $count = $count + 1;
  }
  $line = $_;
  chomp($line);
  ($key,$line) = split (/\s+/,$line,2);
  #print "-$key--\n";
  $dict{$key} = $line;
 } 
 close(DATA) || die "Couldn't close file properly";
 print "Total dict lines skipped: ",$count,"\n";
 print \%dict;
 return \%dict;
}

sub rhymeFound{
 my $word1 = shift;
 my $word2 = shift;
 my $dict = shift;
 my @differentPronouncesOfWord1;
 my @differentPronouncesOfWord2; 
 my $index = 1;
 my @phonemes;
 my @phonemes2;
 push(@differentPronouncesOfWord1,$dict->{$word1});
 push(@differentPronouncesOfWord2,$dict->{$word2}); 
 while((exists $dict->{$word1."($index)"}))#palavras com mais de uma pronuncia aparecem no dicionario na forma palavra, palavra(1), palavra(2)...
 {
  push(@differentPronouncesOfWord1,$dict->{$word1."($index)"});
  $index++;
 }
 $index = 1;
 while((exists $dict->{$word2."($index)"}))
 {
  push(@differentPronouncesOfWord2,$dict->{$word2."($index)"});
  $index++;
 }
 foreach my $first (@differentPronouncesOfWord1) 
 { 
  (@phonemes) = split(/\s/,$first);
  foreach my $second (@differentPronouncesOfWord2) 
  { 
   (@phonemes2) = split(/\s/,$second);
   if(($phonemes[(scalar @phonemes) - 1] eq $phonemes2[(scalar @phonemes2) - 1]) and ($phonemes[(scalar @phonemes) - 2] eq $phonemes2[(scalar @phonemes2) - 2]))
   {
    print "\n\n-------------------FOUND RHYME---------------------------\n\n";
    print $first ."-".$second."\n";
    print "\n\n---------------------------------------------------------\n\n";
    return 1;
   } 
  } 
 }
 return 0;
}

my $key;
my $value;
my $data = loadPhonemes("cmudict-0.7b");
print $data;
my $var = uc "programmer";
my @aux = split(/\s/,$data->{$var});
print "programmer = " . @aux . "\n";
print "programmer last pronounce= " . $aux[(scalar @aux) - 1] . "\n";

