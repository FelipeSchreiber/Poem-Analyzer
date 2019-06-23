#include "perlWrapper.h"

perlWrapper::perlWrapper(){
	PERL_SYS_INIT3(NULL,NULL,NULL);
	my_perl = perl_alloc();
	perl_construct(my_perl);
	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
}

perlWrapper::~perlWrapper(){
	perl_destruct(my_perl);
	perl_free(my_perl);
	PERL_SYS_TERM();
}

void perlWrapper::runInterpreterWithPerlFile(char *filename){
	my_argv[0] = "";
	my_argv[1] = filename;
	perl_parse(my_perl,0,2,my_argv,(char**)NULL);
	perl_run(my_perl);
}

int perlWrapper::getSonetAnalysis(int fd, int mode){
	dSP;				//inicializa o ponteiro da pilha
	ENTER;
	SAVETMPS;		//variavel temporaria
	PUSHMARK(SP);	//lembra ponteiro na pilha
	XPUSHs(sv_2mortal(newSViv(fd)));
	XPUSHs(sv_2mortal(newSViv(mode)));
	PUTBACK;
	//string func("isSonnet");
	string func("interfaceIsSonet");
	call_pv(func.c_str(),G_SCALAR);
	SPAGAIN;

	int res = POPi;
	PUTBACK;
	FREETMPS;
	LEAVE;

	return res;
}

int perlWrapper::getFileStats(int fd,vector<int>*save){
	dSP;				//inicializa o ponteiro da pilha
	ENTER;
	SAVETMPS;		//variavel temporaria
	PUSHMARK(SP);	//lembra ponteiro na pilha
	XPUSHs(sv_2mortal(newSViv(fd)));
	PUTBACK;
	//string func("fileStats");
	string func("interfaceFileStats");
	call_pv(func.c_str(),G_ARRAY);
	SPAGAIN;
  for(int j = 0; j<3; j++)
	{
		save->push_back(POPi);		
		//cout<<"\nOK\n";
	}
	PUTBACK;
	FREETMPS;
	LEAVE;
  return 0;
}

int perlWrapper::getRepetitions(int fd,Heap<myClass>*palavras){
	dSP;				//inicializa o ponteiro da pilha
	ENTER;
	SAVETMPS;		//variavel temporaria
	PUSHMARK(SP);	//lembra ponteiro na pilha
	XPUSHs(sv_2mortal(newSViv(fd)));
	PUTBACK;
	string func("interfaceCountRep");
	call_pv(func.c_str(),G_ARRAY);
	SPAGAIN;
	int vectorLength = POPi;
  for(int j = 0; j<vectorLength/2; j++)
	{
		STRLEN len;
    const char *s = SvPVx(POPs, len);
		string temp(s);
    myClass *palavra = new myClass(temp,POPi);
		palavras->insert(palavra);
	}
	PUTBACK;
	FREETMPS;
	LEAVE;
  return 0;
}

int perlWrapper::getRima(vector<vector<string> >*retorno, vector<string> &palavras,int mode){
	dSP;				//inicializa o ponteiro da pilha
	ENTER;
	SAVETMPS;		//variavel temporaria
	PUSHMARK(SP);	//lembra ponteiro na pilha
	for(unsigned int i = 0;i<palavras.size();i++)
	{
		XPUSHs(sv_2mortal(newSVpv(palavras[i].c_str(),palavras[i].length())));
	}	
	XPUSHs(sv_2mortal(newSViv(mode)));
	PUTBACK;
	string func("interfaceDetRima");
	int vectorLength = call_pv(func.c_str(),G_ARRAY);//obtem o tamanho da pilha
	SPAGAIN;
	vector<string> padraoVer;
	STRLEN len;
  const char *s = SvPVx(POPs, len);
	string temp(s);
	padraoVer.push_back(temp);
	(*retorno).push_back(padraoVer);//retorno 0 contem o padrao da rima
	vectorLength--;//foi retirado um elemento da pilha
	int i = 0;
	int curState = 0;//usado para fazer uma maquina de estados
	int curKeyLength = 0;//variavel que determina quantas palavras possui a chave atual no hash
	vector<string> *str;//variavel que contem chave do hash pelo perl e o array correspondente
	while(i<vectorLength)	
	{		
		switch (curState) 
		{
								case 0://lê a chave atual passada e o tamanho do vetor associado a ela
								{
									str = new vector<string>;
									STRLEN len;
  								const char *s = SvPVx(POPs, len);
									string chave(s);
									str->push_back(chave);//coloca a chave do hash no novo vetor
									curKeyLength = POPi;//lê qual o tamanho do vetor associado aquela chave
									i += 2;//retiramos dois elementos do vetor passado pelo perl
									curState = 1;
								}
				        break;

				        case 1://coloca as palavras do vetor recem criado
								{
									for(int j = 0; j<curKeyLength; j++)
									{
										STRLEN len;
										const char *s = SvPVx(POPs, len);
										string newWord(s);
										str->push_back(newWord);
										i++;
									}
									(*retorno).push_back(*str);
									curState = 0;
								}
				     		break;
		}
	}
	PUTBACK;
	FREETMPS;
	LEAVE;
  return 0;
}

