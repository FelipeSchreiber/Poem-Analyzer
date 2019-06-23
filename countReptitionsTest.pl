use countReptitions;

open(my $fd, "<", "file.txt") or die "Couldn't open the file, $!";
my $resPtr = contPalavras($fd);
my %resultado = %{$resPtr}; undef $resPtr;
foreach my $key (keys %resultado){
	print"\n$key: @{%resultado{$key}}[0]";
}
close $fd;
print"\n";
