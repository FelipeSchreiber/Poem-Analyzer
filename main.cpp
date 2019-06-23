#include <iostream>
#include <string>
#include "heap.h"
#include <vector>
#include "runPerl.h"
#include "perlWrapper.h"

using namespace std;
int main(){
	bool Quit = false;
	perlWrapper perlwrapper;
	int choice = 7;
	while(!Quit) {
		   choice = ShowMenu();
		   switch (choice) {
		          case 1:
							{
									string path;
									printf("\e[1;1H\e[2J");		
									cout<<"\nDigite o caminho até o diretorio desejado: \n"<<endl;
									getline(cin,path);
									ls(path);							
							}
		          break;

		          case 2:
              {
									printf("\e[1;1H\e[2J");
		              if( runIsSonet(perlwrapper) )
									{
										cout<<"\nÉ soneto\n"<<endl;
									}
									else
									{
										cout<<"\nNao é soneto\n"<<endl;
									}
              }
		          break;

		          case 3:
		          {
									printf("\e[1;1H\e[2J");									
									vector<int> fileStats;
									if( runStats(perlwrapper,&fileStats,-1) )
									{
										cout<<"\nTotal de palavras: "<<fileStats[2]<<" Total de versos: "<<fileStats[1]<<" Total de estrofes: "<<fileStats[0]<<endl;
									}
							}
		          break;

		          case 4:
		          {	
									printf("\e[1;1H\e[2J");
									vector<vector<string> > retorno;
									runDetRima(perlwrapper,retorno);
                  cout<<"\nPadrao de rimas encontrado: "<<retorno[0][0]<<endl;
									cout<<"\nRimas encontradas: "<<endl;
									for(int i = 1;i<retorno.size();i++)	
									{
										for(int j = 0; j<retorno[i].size(); j++)
											cout<<retorno[i][j]<<"||";
										cout<<"\n";
									}
									cout<<"\n";
							}
		          break;
							
		          case 5:
		          {
									printf("\e[1;1H\e[2J");
               		Heap<myClass> palavras;
									if( runRepetitions(perlwrapper, palavras) )
									{								
										while(!palavras.is_empty())
										{
													myClass *ptr = palavras.pop();
													cout<<ptr->vertexId<<": "<<ptr->value<<endl;
										}
									}
							}
		          break;
							
		          case 6:
							{
										printf("\e[1;1H\e[2J");
										cout<<"Saindo..."<<endl;			
			               Quit = true;
							}
		          break;

		          default:
							{
										
										printf("\e[1;1H\e[2J");
		                cout << "Bad Input, Try again " << endl;
							}
		          break;
		   }

	}

return 0;
} //end of main


