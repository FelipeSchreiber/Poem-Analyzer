//#include <EXTERN.H>
#include "/usr/lib/x86_64-linux-gnu/perl/5.22.1/CORE/EXTERN.h"
#include <perl.h>
#include <string>
#include <iostream>

using namespace std;

class perlWrapper{
	public:
		perlWrapper();
		~perlWrapper();
		void runInterpreterWithPerlFile(char *filename);
		int getSonetAnalysis(int fd, int mode);
		int getInputFileInfo(string inputFile, string perlFunc);
	private:
		PerlInterpreter *my_perl;
		char *my_argv[2];
};