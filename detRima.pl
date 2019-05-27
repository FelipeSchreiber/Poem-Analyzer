#! /usr/bin/perl
use warnings;
use utf8;
use diagnostics;
use phonemeParser;

sub getHighestKey{
	my %hash = %{$_[0]};
	my $max = "a";			#compare -1 with a
	foreach my $key (keys %hash){
		if ($max lt $key){
			$max = $key;
		}
	}
	return $max;
}

sub determinaRima{
	my @palavras = @{$_[0]};
  my @palavras2;
  my $firstWordToInclude;
  my @notFound;
  my $mode = $_[1];#determina o tipo de operacao conforme explicitado em rhymeFound
	#aqui entra o divisor ou estrator da ultima silaba
  my $dictionary = loadPhonemes("cmudict-0.7b");
  my %vowels;
  my $phones = loadPhonemes("cmudict.0.7a.phones");
  while (my ($key, $value) = each(%{$phones})) {
   if($value eq "vowel") 
   {
    $vowels{$key} = $value; #coloca todas as vogais num dicionario a parte
   }
  }
  my $aux;#essa variavel armazena a palavra com a qual esta sendo comparada e ja esta no hash
	my $curChar = "a";
	my $divEst = " ";
	my $igCharSml = -1;
	my $string = "a";
  foreach $firstWordToInclude (@palavras)#preprocessa retirando todas as palavras que nao estao presentes no dicionario
  {
   if($firstWordToInclude ne "\n")
   {
    $firstWordToInclude = uc $firstWordToInclude;#no dicionario as palavras sao maiusculas 
    if(not exists $dictionary->{$firstWordToInclude})
    {
     $firstWordToInclude =~ s/-//g; #caso em que o hifen foi retirado no dicionario
    }
    if (not exists ($dictionary->{$firstWordToInclude}))
    {
     push(@notFound,$firstWordToInclude);
     #print "\n\n#################### PALAVRA ADCIONADA A NOT FOUND: $firstWordToInclude #######################################\n\n";
    }
    else
    {
      push (@palavras2,$firstWordToInclude);
    }
   }
   else
   {
    push (@palavras2,$firstWordToInclude);
   }
  }
  my %hashRimas = ($curChar => [$palavras2[0]]);
  shift @palavras2;
	foreach my $palavra (@palavras2){
		my $inserted = 0;
    if ($palavra eq "\n"){
			 $string = $string.$divEst;
			 $igCharSml = getHighestKey(\%hashRimas);
		 }
    else{
			foreach my $key (keys %hashRimas){
				if ($key gt $igCharSml or $igCharSml == -1)
				{
         $aux =  @{$hashRimas{$key}}[0];
         if( (exists $dictionary->{$palavra}) )
         {
          if(rhymeFound($palavra,$aux,$dictionary,\%vowels,$mode) eq 1)
          {
            push (@{$hashRimas{$key}}, $palavra);
						$string = $string.$key;
						$inserted = 1;
					}
         }#if( (exists $dictionary->{$aux}) )
			 }#if ($key gt $igCharSml or $igCharSml == -1)
			}
			if ($inserted != 1){
				++$curChar;
        #print "NEW TABLE: ".$curChar." FOR WORD: ".$palavra."\n" ;
				%hashRimas = (%hashRimas, $curChar => [$palavra]);
				$string = $string.$curChar;
			}
		}
	}
  print "\n\n------------------------WORDS NOT FOUND--------------------------\n";
  foreach (@notFound) { 
    print "-".$_."-\n";
  }
  print "-----------------------------------------------------------------\n\n";
  return ($string,\%hashRimas);
}

my @lastWords = [ "fiddle","Peshito", "trimmer","blue-collar", "collar", "programmer", "system","carpenter","bottle","handler", "SUMMUM", "\n", "petto", "Paramaribo", "Ovambo", "overdear","MISDIAGNOSE","palm sugar","ENCLOSE","wing","shake","eight","thumb","weight","summer","one" ,"wait","caring","hate","awake","rate","hammer","flake"];
my $operation = 1;
my ($padraoVer, $rimasEncPtr) = determinaRima(@lastWords,$operation);
my %rimasEnc = %{$rimasEncPtr}; undef $rimasEncPtr;
foreach my $key (sort keys %rimasEnc){
	print"\n$key: ";
	foreach my $word (@{$rimasEnc{$key}}){
		print"\t$word";
	}
}
print"\n$padraoVer\n";
 
