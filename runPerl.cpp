#include "runPerl.h"

int detRimasMenu()
{
	printf("\e[1;1H\e[2J");
	string userInput;
	cout<<"\nDigite o modo como deseja classificar as rimas: \n"<<endl;
	cout << "1 - Rima perfeita\n";
	cout << "2 - Rima por aliteracao\n";
	cout << "3 - Padrao (analisa apenas a ultima vogal e em diante) ---recomendado\n";
	getline(cin,userInput);
	return ( *(userInput.c_str() ) - '0' );//converte char para inteiro
}

int ls(string path){
	struct dirent *entry;
	DIR *dir = opendir(path.c_str());
	if (!dir){
		cout << "Failed to open directory" << endl;
		return 1;
	}
	cout << "Files: " << endl;
	unsigned i = 0;
	while(entry = readdir(dir))
		cout << (*entry).d_name <<
			((i++ % 5 == 0) ? "\n" : "\t\t");
	cout << endl;
	closedir(dir);
	return 0;
}

int runStats(perlWrapper &perlwrapper,vector<int> *fileStats,int fd)
{
	//fileStats isSonet countReptitions detRima
	string filename;
	int fileDescriptor;
	perlwrapper.runInterpreterWithPerlFile("interfaces.pl");
	if(fd<0)
	{
  	cout<<"\nDigite o nome do arquivo do qual deseja obter dados gerais: "<<endl;
		getline(cin,filename);
		fileDescriptor = open (filename.c_str(), O_RDONLY);
	}
	else
	{	
		fileDescriptor = fd;
	}
	
  if(fileDescriptor > 0)//open retorna -1 em caso de erro 
  {
		perlwrapper.getFileStats(fileDescriptor, fileStats);	
	}
	else
  {
		cout<<"\nUm problema ocorreu na abertura do arquivo"<<endl;
		return 0;
  }
	return 1;
}

int runIsSonet(perlWrapper &perlwrapper)
{
	string filename;
	perlwrapper.runInterpreterWithPerlFile("interfaces.pl");
  cout<<"\nDigite o nome do arquivo que deseja abrir: "<<endl;
	getline(cin,filename);
	int fileDescriptor = open (filename.c_str(), O_RDONLY);
  if(fileDescriptor > 0)//open retorna -1 em caso de erro 
  {
			if( perlwrapper.getSonetAnalysis(fileDescriptor,2) )
  	  {
				return 1;
			}
  }
	else
  {
		cout<<"\nUm problema ocorreu na abertura do arquivo"<<endl;
  }
	return 0;
}

int runRepetitions(perlWrapper &perlwrapper,Heap<myClass> &palavras)
{
	string filename;
	perlwrapper.runInterpreterWithPerlFile("interfaces.pl");
  cout<<"\nDigite o nome do arquivo que deseja abrir: "<<endl;
	getline(cin,filename);
	int fileDescriptor = open (filename.c_str(), O_RDONLY);
  if(fileDescriptor > 0)//open retorna -1 em caso de erro 
  {
		perlwrapper.getRepetitions(fileDescriptor, &palavras);
		printf("\e[1;1H\e[2J");			
		return 1;
  }
	else
  {
		cout<<"\nUm problema ocorreu na abertura do arquivo"<<endl;
  }
	return 0; 
}


vector<string> getLastWords(Heap<int> *estrofes,string filename,int todasAsEstrofes)
{
	//estrofes esta ordenado em ordem crescente
	string line;
	ifstream curFile;
	curFile.open(filename.c_str());
  string lastWord;
	vector<string> lastWords;
	int curEstrofe = 1;
	int curState = (curEstrofe == *(estrofes->front()) || todasAsEstrofes)? 0:1 ;//dois estados possiveis: o de leitura da ultima palavra da linha e de ignorar a estrofe.
	char delim = ' ';
	while(!curFile.eof())
	{
		getline(curFile,line);
		if( line.empty() && !todasAsEstrofes)
		{
			curEstrofe++;
			if(!estrofes->is_empty())
			{
				if(curEstrofe > *(estrofes->front()) )
				{
					int *m = estrofes->pop();
		    }
			}

			if(!estrofes->is_empty())
			{
				if(curEstrofe < *(estrofes->front()) )
				{
					curState = 1;//ignora o proxima estrofe
				}
			}
			else
			{
				curState = 1;
			}

			if(!estrofes->is_empty())
			{
				if(curEstrofe == *(estrofes->front()) )
				{
					curState = 0;//vai para o estado de leitura
				}
			}
			else
			{
				curState = 1;
			}

		}
		else
		{
			switch(curState)
			{
				case 0:
				{			
					reverse(line.begin(),line.end());
					stringstream ss(line);
						
					getline(ss, lastWord, delim);
					reverse(lastWord.begin(),lastWord.end());
					lastWords.push_back(lastWord);
				}
				break;
		
				case 1:
				{
				}
				break;				
			}//switch
		}//else
	}//while	
	curFile.close();
	return lastWords;
}

void getEstrofes(Heap<int> &estrofes)
{
	string userIn;
	cout<<"\nDigite as estrofes que deseja analisar: "<<endl;
	getline(cin,userIn);
	stringstream ss(userIn);
	string temp;
	char delim = ' ';
	while(getline(ss, temp, delim) )
	{
		int *myInt = new int;
		*myInt = atoi( temp.c_str() );
		estrofes.insert( myInt );
	}
}

void runDetRima(perlWrapper &perlwrapper,vector<vector<string> > &retorno)
{
	string filename;
	int todasAsEstrofes = 1;
	string userIn;
	int rhymeMode;
	Heap<int> estrofes;
	cout<<"\nDigite o nome do arquivo que deseja abrir: "<<endl;
	getline(cin,filename);
	int fD = open (filename.c_str(), O_RDONLY);
	vector<int> fileStats;
	if( runStats(perlwrapper,&fileStats, fD) )
	{
		cout<<" O poema possui um total de "<<fileStats[0]<<" estrofes\n"<<endl;
	}
	cout<<"\nDeseja analisar todas as estrofes: [Y]/n\n"<<endl;
	getline(cin,userIn);
	const char *N = "N";	
	if(toupper(userIn[0]) == *N)
	{										
		todasAsEstrofes = 0;
		getEstrofes(estrofes);
	}
	else
	{
		for(int l = 1; l<=fileStats[0]; l++)
		{
			int *myInt = new int(l);
			estrofes.insert( myInt );
		}
	}
	vector<string> palavras = getLastWords(&estrofes,filename,todasAsEstrofes);
	perlwrapper.runInterpreterWithPerlFile("interfaces.pl");
	rhymeMode = detRimasMenu();
	switch(rhymeMode)
	{
		case 1:
		{
			perlwrapper.getRima(&retorno, palavras, 3);
		}
		break;
										
		case 2:
		{
			perlwrapper.getRima(&retorno, palavras, 5);
		}
		break;
							
		case 3:
		{
			perlwrapper.getRima(&retorno, palavras, 1);
		}
		break;

		default:
		{
			cout<<"\nInput fora do esperado. Usando a forma padrao..."<<endl;
			perlwrapper.getRima(&retorno, palavras, 1);
		}
		break;
	}
}

int ShowMenu() {
		string userInput;
		cout << "\n\n-------------------------OPCOES--------------------------------------\n";
		cout << "1 - Listar poemas\n";
		cout << "2 - Classificar poema: Soneto?\n";
		cout << "3 - Dados gerais do poema (numero de palavras, versos e estrofes)\n";
		cout << "4 - Achar Rimas\n";
    cout << "5 - Achar Repeticoes\n";
		cout << "6 - Sair\n";
		cout << "Digite o numero correspondente a operacao desejada: " << endl;
		getline(cin,userInput);
		return ( *(userInput.c_str() ) - '0' );//converte char para inteiro	
}
