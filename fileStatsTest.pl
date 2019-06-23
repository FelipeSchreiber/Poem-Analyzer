use fileStats;

open(my $fd, "<", "file.txt") or die "Couldn't open the file, $!";
@fileInfo = fileStats($fd);
close $fd || die "Couldn't close file properly";
foreach my $data (@fileInfo){
 print $data, "\n";
}
