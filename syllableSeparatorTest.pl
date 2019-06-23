use syllableSeparator;
my $key;
my $value;
my $data = loadDatabase("mhyph.txt");
print $data;
my $var = "a_cappella";
my @aux = split(/\s/,$data->{$var});
print "a cappella = " . @aux . "\n";
print "a cappella last syllable= " . $aux[(scalar @aux) - 1] . "\n";
