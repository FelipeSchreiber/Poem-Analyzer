package countReptitions;
use strict;
use warnings;
use utf8;
use Exporter 'import';
our $VERSION = '1.00';
our @ISA= qw( Exporter );

# these CAN be exported.
our @EXPORT_OK = qw( contPalavras turnLower );
our @EXPORT = qw( contPalavras );

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

1;
