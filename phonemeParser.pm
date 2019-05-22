package phonemeParser;
use strict;
use warnings;
use Exporter 'import';
our $VERSION = '1.00';
our @ISA= qw( Exporter );

# these CAN be exported.
our @EXPORT_OK = qw( loadPhonemes rhymeFound isNotVowel checkAliteration);
our @EXPORT = qw( loadPhonemes rhymeFound isNotVowel checkAliteration);

#busca por fonemas iguais de uma palavra em outra, independente da posicao
sub checkAliteration{
 my $word1 = shift;
 my $word2 = shift;
 my $dict = shift;
 my @differentPronouncesOfWord1;#palavras podem ter mais de uma pronuncia 
 my @differentPronouncesOfWord2; 
 my $index = 1;
 my $copy;
 my @phonemes;
 push(@differentPronouncesOfWord1,$dict->{$word1});
 push(@differentPronouncesOfWord2,$dict->{$word2}); 
 while((exists $dict->{$word1."($index)"}))#palavras com mais de uma pronuncia aparecem no dicionario na forma: palavra, palavra(1), palavra(2)...
 {
  push(@differentPronouncesOfWord1,$dict->{$word1."($index)"});
  $index++;
 }
 $index = 1;
 while((exists $dict->{$word2."($index)"}))
 {
  push(@differentPronouncesOfWord2,$dict->{$word2."($index)"});
  $index++;
 }
 foreach my $first (@differentPronouncesOfWord1) 
 { 
  $first =~ s/(\d)//g;#remove os digitos 0,1 e 2 que marcam o tipo de pronuncia tonica ou atona ou intermediario
  (@phonemes) = split(/\s/,$first);
  foreach my $second (@differentPronouncesOfWord2) 
  { 
   $second =~ s/(\d)//g;
   for $index (0 .. $#phonemes)
   {
    ($copy = $second) =~ s/$phonemes[$index]//g;
    if($copy ne $second) #checa se apos o regex a palavra sofreu alguma alteracao.Se sim, significa esse fonema esta presente   
    {
     #print $copy." - ".$second."\n";
     return 1;
    }
   }
  }
 }
 return 0; 
}

#condicao teste se um dos dois fonemas eh vogal. Caso a opcao (params) for um multiplo de 3, entao checa ainda se o fonema eh atono ou tonico
sub isNotVowel{
 my $phoneme = shift;
 my $phoneme2 = shift;
 my $vowels = shift;
 my $params = shift;
 if(($params % 3) != 0)
 {
  #apenas as vogais possuem numero no final do fonema. 0 significa que nao eh tonica. Para checar apenas rimas perfeitas, bastaria acrescentar:    no if a seguir.
  if( ( exists $vowels->{(substr $phoneme,0,2)} ) or ( exists $vowels->{(substr $phoneme2,0,2)} ) )
  {
   return 0;
  }
  return 1;
 }
 else
 {
  if( ( exists $vowels->{(substr $phoneme,0,2)} and (substr $phoneme,-1) ne "0") or ( exists $vowels->{(substr $phoneme2,0,2)} and (substr $phoneme2,-1) ne "0") )
  {
   return 0;
  }
  return 1;
 }
}

#determina se duas palavras rimam. Como existe varios tipos de rima, permitimos 3 modos de operacao diferentes.
sub rhymeFound{
 my $word1 = shift;
 my $word2 = shift;
 my $dict = shift;
 my $vowels = shift;
 my $params = shift;#tem varias opcoes que podem ser passadas: checa apenas a ultima vogal e em diante sao iguais por default, se for multiplo de 3, checa apenas rimas perfeitas (vogais tonicas e em diante sao iguais) e se for multiplo de 5 checa por aliteracao. Prioridade: 5>3>default
 if(($params % 5) == 0)
 {
  return checkAliteration($word1,$word2,$dict);
 }
 my @differentPronouncesOfWord1;
 my @differentPronouncesOfWord2; 
 my $index = 1;
 my @phonemes;
 my @phonemes2;
 my $aux;
 push(@differentPronouncesOfWord1,$dict->{$word1});
 ($aux = $differentPronouncesOfWord1[0]) =~ s/0 Z/0 S/g;#caso em que Z eh precedido de uma vogal atona perde forca e tem som de "S" 
 if($aux ne $dict->{$word1})
 {
  push(@differentPronouncesOfWord1,$aux);
 }
 ($aux = $differentPronouncesOfWord1[0]) =~ s/1 S/1 Z/g;#caso em que S eh precedido de uma vogal tonica e tem som de "Z"
 if($aux ne $dict->{$word1})
 {
  push(@differentPronouncesOfWord1,$aux);
 }
 push(@differentPronouncesOfWord2,$dict->{$word2});
 ($aux = $differentPronouncesOfWord2[0]) =~ s/0 Z/0 S/g;#caso em que Z eh precedido de uma vogal atona perde forca e tem som de "S"  
 if($aux ne $dict->{$word2})
 {
  push(@differentPronouncesOfWord2,$aux);
 }
 ($aux = $differentPronouncesOfWord2[0]) =~ s/1 S/1 Z/g;#caso em que S eh precedido de uma vogal tonica e tem som de "Z"
 if($aux ne $dict->{$word2})
 {
  push(@differentPronouncesOfWord2,$aux);
 }
 while((exists $dict->{$word1."($index)"}))#palavras com mais de uma pronuncia aparecem no dicionario na forma: palavra, palavra(1), palavra(2)...
 {
  push(@differentPronouncesOfWord1,$dict->{$word1."($index)"});
  ($aux = $dict->{$word1."($index)"}) =~ s/0 Z/0 S/g;#caso em que Z eh precedido de uma vogal atona perde forca e tem som de "S" 
  if($aux ne $dict->{$word1."($index)"})
  {
   push(@differentPronouncesOfWord1,$aux);
  }
  ($aux = $dict->{$word1."($index)"}) =~ s/1 S/1 Z/g;#caso em que S eh precedido de uma vogal tonica e tem som de "Z"
  if($aux ne $dict->{$word1."($index)"})
  {
   push(@differentPronouncesOfWord1,$aux);
  }
  $index++;
 }
 $index = 1;
 while((exists $dict->{$word2."($index)"}))
 {
  push(@differentPronouncesOfWord2,$dict->{$word2."($index)"});
  ($aux = $dict->{$word2."($index)"}) =~ s/0 Z/0 S/g;#caso em que Z eh precedido de uma vogal atona perde forca e tem som de "S" 
  if($aux ne $dict->{$word2."($index)"})
  {
   push(@differentPronouncesOfWord2,$aux);
  }
  ($aux = $dict->{$word2."($index)"}) =~ s/1 S/1 Z/g;#caso em que S eh precedido de uma vogal tonica e tem som de "Z"
  if($aux ne $dict->{$word2."($index)"})
  {
   push(@differentPronouncesOfWord2,$aux);
  }
  $index++;
 }
 foreach my $first (@differentPronouncesOfWord1) 
 { 
  (@phonemes) = split(/\s/,$first);
  #analisaremos a palavra de tras pra frente, buscando a ultima vogal  
  my @REVERSED_LIST1 = reverse(@phonemes);
  foreach my $second (@differentPronouncesOfWord2) 
  { 
   (@phonemes2) = split(/\s/,$second);
   my @REVERSED_LIST2 = reverse(@phonemes2);
   $index = 0;
   while(isNotVowel($REVERSED_LIST1[$index],$REVERSED_LIST2[$index],$vowels,$params) == 1)
   {
    $index++;#continua percorrendo o  array de fonemas
   }
   #chegamos na ultima vogal de uma das palavras. Ambas as palavras possuem todos os fonemas iguais depois da vogal. Para que seja rima agora basta verificar se a ultima vogal tambem sao iguais (o ultimo digito de um fonema com vogal pode ser ou 0, ou 1, ou 2, por isso excluiremos esse numero para fins de comparacao).
   if( (substr $REVERSED_LIST1[$index],0,2) eq (substr $REVERSED_LIST2[$index],0,2) )
   {
    return 1;
   } 
  } 
 }
 return 0;
}

#carrega um dicionario que converte uma palavra na sua pronuncia. O cmudict usa o padrao ARPAbet e nao o IPA
sub loadPhonemes{
 my $database = shift;
 #print $database, "\n";
 my $cmu = "cmudict-0.7b";
 my $line;
 my %dict;
 my $count = 0;
 my $key;
 open(DATA, "<".$database) or die "Couldn't open file $database, $!";
 while(<DATA>){
  if($database eq $cmu)
  {
   while($count < 57)
   {
    $count = $count + 1;
   }
  }
  $line = $_;
  chomp($line);
  ($key,$line) = split (/\s+/,$line,2);
  #print "-$key--\n";
  $dict{$key} = $line;
 } 
 close(DATA) || die "Couldn't close file properly";
 #print "Total dict lines skipped: ",$count,"\n";
 #print \%dict;
 return \%dict;
}


1;
