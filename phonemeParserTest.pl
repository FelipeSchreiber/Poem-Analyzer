use phonemeParser;

my $key;
my $value;
my $data = loadPhonemes("cmudict-0.7b");
my %vowels;
my $phones = loadPhonemes("cmudict.0.7a.phones");
while ( ($key, $value) = each(%{$phones})) {
 if($value eq "vowel") 
 {
  $vowels{$key} = $value; #coloca todas as vogais num dicionario a parte
 }
}
print $data;
my $var = uc "programmer";
my $var2 = uc "hammer";
my @aux = split(/\s/,$data->{$var});
print "programmer = " . @aux . "\n";
print "programmer last pronounce= " . $aux[(scalar @aux) - 1] . "\n";
my $mode = 2;
if(rhymeFound($var2,$var,$data,\%vowels,$mode) )
{
 print "Rhyme found!\n";
}
$var = uc "shake";
$var2 = uc "rate";
$var = $data->{$var};
$var2 = $data->{$var2};
my @difPronounces;
my @difPronounces2;
push(@difPronounces,$var);
push(@difPronounces2,$var2);
if(checkAliteration(\@difPronounces,\@difPronounces2))
{
 print "\nALLITERATION FOUND\n";
}

