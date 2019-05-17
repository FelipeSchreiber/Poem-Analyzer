sub fileStats {
 my $filename = shift;
 print $filename, "\n";
 my $line;
 my @words;
 my $totalWords = 0;
 my $totalEstrofes = 0;
 my $totalVersos = 0;
 my @stats;
 open(DATA, "<".$filename) or die "Couldn't open file file.txt, $!";
 while(<DATA>){
  $line = $_;
  if(length($line) eq 1)
  {
   print "Nova estrofe\n";
   $totalEstrofes = $totalEstrofes + 1;
  }
  else
  {
   $totalChar = $totalChar + length($line);
   chomp($line);
   @words = split(/\s/,$line);
   #print "Scalar words: ", scalar @words,"\n";
   $totalWords =  $totalWords + scalar @words;
   $totalVersos = $totalVersos + 1; 
  }
 }
 close(DATA) || die "Couldn't close file properly";
 $totalEstrofes = $totalEstrofes + 1;
 push @stats,$totalWords;
 push @stats,$totalVersos;
 push @stats,$totalEstrofes;
 return @stats;
}

@fileInfo = fileStats("file.txt");
foreach my $data (@fileInfo){
 print $data, "\n";
}
