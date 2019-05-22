use isSonet;
my$fd;
open($fd, "<", "file2.txt") or die "Couldn't open the file, $!";
#print "\nFD: ".$fd."\n";
my $mode = 1;
if(isSonnet($fd,$mode) == 1)
{
 print "\nIS SONNET\n";
}
