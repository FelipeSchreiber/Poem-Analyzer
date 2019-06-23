use detRima;
use fileStats;
use isSonet;
use countReptitions;

sub interfaceCountRep{
	my $fD = shift;	
	my $resPtr = contPalavras($fD);
	my @vector;
	my %resultado = %{$resPtr}; undef $resPtr;
	foreach my $key (keys %resultado){
		#print"\n$key: @{%resultado{$key}}[0]";
		push @vector, @{%resultado{$key}}[0];
		push @vector, $key;
	}
	return @vector,scalar @vector;
}

sub interfaceDetRima{
	my @vector;
	my @returningVector;
	foreach my $v (@_) 
	{
		push @vector,$v;
	}
	my $mode = pop @vector;
	for my $i (0 .. $#vector)
	{
      $vector[$i]=~ s/[^a-zA-Z "\-"\s]//g; #remove todos os caracteres diferentes de letras, espaco ou hifen
	}
	my ($padraoVer, $rimasEncPtr) = determinaRima(@vector,$mode);
	my %rimasEnc = %{$rimasEncPtr}; undef $rimasEncPtr;
	foreach my $key (sort keys %rimasEnc){
		foreach my $word (@{$rimasEnc{$key}}){
			push @returningVector,$word;
		}
		push @returningVector,scalar @{$rimasEnc{$key}};
		push @returningVector,$key;
	}
	push @returningVector, $padraoVer;
	return @returningVector;
}

sub interfaceFileStats{	
 	my $fd = shift;
	my @stats = fileStats($fd);
	return @stats;
}

sub interfaceIsSonet{
	my $fd = shift;
	my $mode = shift;	
	return isSonnet($fd,$mode);
}
