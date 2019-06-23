use detRima;

my @lastWords = [ "fiddle","Peshito", "trimmer","blue-collar", "collar", "programmer", "system","carpenter","bottle","handler", "SUMMUM", "\n", "petto", "Paramaribo", "Ovambo", "overdear","MISDIAGNOSE","palm sugar","ENCLOSE","wing","shake","eight","thumb","weight","summer","one" ,"wait","caring","hate","awake","rate","hammer","flake"];
my $operation = 1;
my ($padraoVer, $rimasEncPtr) = determinaRima(@lastWords,$operation);
my %rimasEnc = %{$rimasEncPtr}; undef $rimasEncPtr;
foreach my $key (sort keys %rimasEnc){
	print"\n$key: ";
	foreach my $word (@{$rimasEnc{$key}}){
		print"\t$word";
	}
}
print"\n$padraoVer\n";
