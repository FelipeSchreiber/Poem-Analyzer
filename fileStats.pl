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
 #print "\nFD: ".$fd."\n";
 while($line = <$fDescriptor>){
  if(length($line) eq 1)
  {
   #print "Nova estrofe\n";
   $totalEstrofes = $totalEstrofes + 1;
  }
  else
  {
   chomp($line);
   @words = split(/\s/,$line);
   #print "Scalar words: ", scalar @words,"\n";
   $totalWords =  $totalWords + scalar @words;
   $totalVersos = $totalVersos + 1; 
  }
 }
 $totalEstrofes = $totalEstrofes + 1;
 push @stats,$totalWords;
 push @stats,$totalVersos;
 push @stats,$totalEstrofes;
 #print $stats[0] ."||".$stats[1] ."||".$stats[2]."\n"; 
 #print "words: ".$totalWords."\n";
 #print "versos: ".$totalVersos."\n";
 #print "estrofes: ".$totalEstrofes."\n";
 close($fDescriptor) || die "Couldn't close file properly";
 #print "\nOK perl\n";
 return @stats;
}


#open(my $fd, "<", "file.txt") or die "Couldn't open the file, $!";
#@fileInfo = fileStats($fd);
#close $fd || die "Couldn't close file properly";
#foreach my $data (@fileInfo){
# print $data, "\n";
#}
