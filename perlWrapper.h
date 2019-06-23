#ifndef PERL_WRAPPER
#define PERL_WRAPPER
#include "/usr/lib/x86_64-linux-gnu/perl/5.22.1/CORE/EXTERN.h"
#include <perl.h>
#include <string>
#include "heap.h"
#include <vector>
#include <iostream>

using namespace std;

class perlWrapper{
	public:
		perlWrapper();
		~perlWrapper();
		void runInterpreterWithPerlFile(char *filename);
		int getFileStats(int fd,vector<int>*save);
		int getSonetAnalysis(int fd, int mode);
		int getRepetitions(int fd,Heap<myClass>*palavras);
		int getRima(vector<vector<string> >*retorno, vector<string> &palavras,int mode);
	private:
		PerlInterpreter *my_perl;
		char *my_argv[2];
};

#endif
