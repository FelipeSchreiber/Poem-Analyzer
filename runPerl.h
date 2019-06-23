#ifndef RUN_PERL
#define RUN_PERL
#include <fcntl.h>
#include <string>
#include "heap.h"
#include "perlWrapper.h"
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <dirent.h>

int ShowMenu();
int ls(string path);
int detRimasMenu();
int runStats(perlWrapper &perlwrapper,vector<int> *fileStats, int fd);
int runIsSonet(perlWrapper &perlwrapper);
int runRepetitions(perlWrapper &perlwrapper,Heap<myClass> &palavras);
void runDetRima(perlWrapper &perlwrapper,vector<vector<string> > &retorno);
vector<string> getLastWords(Heap<int> *estrofes,string filename,int todasAsEstrofes);
void getEstrofes(Heap<int> &estrofes);
#endif
