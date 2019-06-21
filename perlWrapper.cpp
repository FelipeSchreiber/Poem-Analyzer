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
	string func("isSonnet");
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
	string func("fileStats");
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

int perlWrapper::getRepetitions(int fd,vector<string>*palavras,vector<int>*frequencia){
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
    palavras->push_back(temp);
		frequencia->push_back(POPi);
	}
	PUTBACK;
	FREETMPS;
	LEAVE;
  return 0;
}

int perlWrapper::getInputFileInfo(string inputFile, string perlFunc){
	dSP;				//inicializa o ponteiro da pilha
	ENTER;
	SAVETMPS;		//variavel temporaria
	PUSHMARK(SP);	//lembra ponteiro na pilha
	XPUSHs(sv_2mortal(newSVpv(inputFile.c_str(),inputFile.length())));
	PUTBACK;
	call_pv(perlFunc.c_str(),G_SCALAR);
	SPAGAIN;

	int res = POPi;
	PUTBACK;
	FREETMPS;
	LEAVE;

	return res;
}
