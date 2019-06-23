sub fileStats {
 my $fd = shift;
 my $fDescriptor;
 open($fDescriptor, "<&=$fd");
 my $line;
 my @words;
 my $totalWords = 0;
 my $totalEstrofes = 0;
 my $totalVersos = 0;
 my @stats;
 while($line = <$fDescriptor>){
  if(length($line) eq 1)
  {
   $totalEstrofes = $totalEstrofes + 1;
  }
  else
  {
   chomp($line);
   @words = split(/\s/,$line);
   $totalWords =  $totalWords + scalar @words;
   $totalVersos = $totalVersos + 1; 
  }
 }
 $totalEstrofes = $totalEstrofes + 1;
 push @stats,$totalWords;
 push @stats,$totalVersos;
 push @stats,$totalEstrofes;
 close($fDescriptor) || die "Couldn't close file properly";
 return @stats;
}


#open(my $fd, "<", "file.txt") or die "Couldn't open the file, $!";
#@fileInfo = fileStats($fd);
#close $fd || die "Couldn't close file properly";
#foreach my $data (@fileInfo){
# print $data, "\n";
#}
