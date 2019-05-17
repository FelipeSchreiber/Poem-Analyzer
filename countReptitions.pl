#! /usr/bin/perl

sub turnLower{
	my $word = ${$_[0]};
	do{
		my $aux = substr $word, -1;
		if ($aux eq "."){
			chop $word;
		}
	}while($aux eq ".");
	if ($word =~ /^[A-Z]+/){
		$word =~ s/([A-Z])/\L$1/g;
	}

	return $word;
}

sub contPalavras{
	my $fDescriptor = shift;
	my %countRes = ("NULL" => [-1]);
	while(my $line = <$fDescriptor>){
		my @words = split /\s+/,$line;
		foreach my $word (@words){
			my $found = 0;
			$word = turnLower(\$word);
			foreach my $key (%countRes){
				if ($word eq $key){
					++@{%countRes{$key}}[0];
					$found = 1;
					break;
				}
			}
			if ($found == 0){
				%countRes = (%countRes, $word => [1]);
			}
		}
	}

	delete $countRes{"NULL"};
	return \%countRes;
}

open(my $fd, "<", "file.txt") or die "Couldn't open the file, $!";
my $resPtr = contPalavras($fd);
my %resultado = %{$resPtr}; undef $resPtr;
foreach my $key (keys %resultado){
	print"\n$key: @{%resultado{$key}}[0]";
}
close $fd;
print"\n";
