use detRima;
use fileStats;
use syllableSeparator;

sub isSonnet{
 my $fd = shift;
 open(my $fDescriptor, "<&=$fd");
 my $mode = shift;#modo de achar rimas
 my @words;
 my @aux;
 my @fileInfo = fileStats($fDescriptor);
 my @lastWords;
 my $isSonet = 1;
 my $lineSyllablesCounter;
 if ($fileInfo[1] != 14)#todo soneto possui 14 versos
 {
  print "\n\n-----------------------NOT SONNET STATS\n\n";
  $isSonet = 0;
 }
 seek $fDescriptor, 0, 0;#retorna para o inicio do arquivo
 my $data = loadDatabase("mhyph.txt");#carrega o dicionario de hyphenation(que usaremos pra se aproximar da silabificacao)
 #print "\n\n";
 while(my $line = <$fDescriptor>)
 {
  $line =~ s/[^a-zA-Z "\-"\s]//g; #remove todos os caracteres diferentes de letras, espaco ou hifen
  $line = lc $line;
  #print $line;
  @words = split(/\s/,$line);
  push(@lastWords,$words[$#words]); #coloca as ultimas palavras de cada linha num array
  $lineSyllablesCounter = 0;
  for my $var (0 .. $#words)
  {
   #print $words[$var]."-";
   if(exists $data->{$words[$var]})
   {
     @aux = split(/\s/,$data->{$words[$var]});#aux contem as silabas da palavra que esta sendo analisada
   }
   else#caso em que a palavra nao foi achada
   {
    #print "NOT FOUND: ".$#aux."-".substr($words[$var],0,scalar($words[$var]) - 1)."\n";
    @aux = ();
    if(substr($words[$var],-1,1) eq "s")
    {
     if(exists $data->{substr($words[$var],0,length($words[$var]) - 1)} )
     {
      @aux = split(/\s/,$data->{(substr($words[$var],0,(length($words[$var]) - 1)))});#tenta ver se encontra a palavra no singular
     }
    }

    if(substr($words[$var],-2,2) eq "ed")
    {
     if(exists $data->{substr($words[$var],0,length($words[$var]) - 1)} )
     {
      @aux = split(/\s/,$data->{substr($words[$var],0,length($words[$var]) - 1)});#caso em que o verbo terminado em "-e" foi acrescido do "d" ex: loved
     }
		 if(exists $data->{substr($words[$var],0,length($words[$var]) - 2)} )
     {
      @aux = split(/\s/,$data->{substr($words[$var],0,length($words[$var]) - 2)});#caso em que o verbo foi acrescido de"-ed" ex: locked
     }
     if(exists $data->{substr($words[$var],0,length($words[$var]) - 3)} )
     {
      @aux = split(/\s/,$data->{substr($words[$var],0,length($words[$var]) - 3)});#caso em que alem do "-ed" acrescentado a ultima consoante foi duplicada ex: stopped
     }
     if(exists $data->{substr($words[$var],0,length($words[$var]) - 3)."y"} )
     {
      @aux = split(/\s/,$data->{substr($words[$var],0,length($words[$var]) - 3)."y"});#caso em que o verbo termina em "y" ex: studied. Tambem contempla o caso de palavras terminadas em y com vogal antes. Ex: enjoyed
     }    	
	  }

    if(substr($words[$var],-3,3) eq "ing")
    {
     if(exists $data->{substr($words[$var],0,length($words[$var]) - 3)})
     {
      @aux = split(/\s/,$data->{substr($words[$var],0,length($words[$var]) - 3)});#tenta achar verbo conjugado no infinitivo ex.listening
     }
     if(exists $data->{substr($words[$var],0,length($words[$var]) - 3)."e"} )
     {
      @aux = split(/\s/,$data->{substr($words[$var],0,length($words[$var]) - 3)."e"});#caso em que o "E" foi substituido por "ing" ex.racing
     }
     if(exists $data->{substr($words[$var],0,length($words[$var]) - 4)} )
     {
      @aux = split(/\s/,$data->{substr($words[$var],0,length($words[$var]) - 4)});#caso em que a ultima letra eh duplicada ex.hitting
     }
    }
   }
   $lineSyllablesCounter = $lineSyllablesCounter + $#aux;#soma com o ultimo indice do array. Como ele comeca em 0 tem que somar mais 1 depois
   $lineSyllablesCounter++;
   #print "\nLSC: ".$lineSyllablesCounter."\n";
  }
  #print "\n";
  if(abs($lineSyllablesCounter) < 7 or abs($lineSyllablesCounter) > 13)#como devemos contar silabas poeticas e nao silabas em geral, essa eh uma aproximacao que admite um erro de 30% pra mais e pra menos
  {
   #print "\n==========================================================FAILLED: ".$lineSyllablesCounter."\n";
   $isSonet = 0;
  }
  @words = ();
 }
 my ($padraoVer, $rimasEncPtr) = determinaRima(\@lastWords,$mode);
 $padraoVer = uc $padraoVer;
 if($padraoVer eq  "ABBAABBACDECDE" or $padraoVer eq "ABBAABBACDCCDC" or  $padraoVer eq "ABBAABBACDCDCD")
 {
  print "\nPETRARCHAN SONNET\n";
 }
 if($padraoVer eq  "ABBACDDCEFGEFG")
 {
  print "\nCRYBIN VARIANT OF PETRARCHAN\n";
 }
 if($padraoVer  eq "ABABCDCDEFEFGG")
 {
  print "\nENGLISH SONNET\n";
 }
 if($padraoVer eq "ABABBCBCCDCD")
 {
  print "\nSPENSERIAN SONNET\n";
 }
 #print "\n".$padraoVer."\n";
 close($fDescriptor) || die "Couldn't close file properly";
 return $isSonet;
}

#my$fd;
#open($fd, "<", "file2.txt") or die "Couldn't open the file, $!";
#print "\nFD: ".$fd."\n";
#my $mode = 2;
#if(isSonnet($fd,$mode) == 1)
#{
# print "\nIS SONNET\n";
#}

