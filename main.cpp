#include <iostream>
#include <fcntl.h>
#include <string>
#include "perlWrapper.h"

using namespace std;

void ShowMenu(); 
int main(){
	bool Quit = false;
	string userInput;
	perlWrapper perlwrapper;
	string filename;
	int choice = 7;
	while(!Quit) {
		   ShowMenu();
		   getline(cin,userInput);
			 if(userInput.length() == 1)
			 {
       		choice = *(userInput.c_str() ) - '0';//converte char para inteiro
       	  if(choice <= 0 || choice >= 7)
						choice = 7;//em caso da conversao nao ser possivel coloca um valor fora do intervalo [1,6]
			 }
			 else
       {
					choice = 7;
       }
		   switch (choice) {
		          case 1:
							{

							}
		          break;

		          case 2:
              {
		              perlwrapper.runInterpreterWithPerlFile("isSonet.pl");
                  cout<<"\nDigite o nome do arquivo que deseja abrir: "<<endl;
									getline(cin,filename);
									int fileDescriptor = open (filename.c_str(), O_RDONLY);
                  if(fileDescriptor > 0)//open retorna -1 em caso de erro 
                  {
											cout<<"\nFD: "<<fileDescriptor<<endl;
											if( perlwrapper.getSonetAnalysis(fileDescriptor,2) )
                  	  {
													cout<<"\nIS SONNET\n"<<endl;
                  	  }
                  }
               }
		           break;

		          /*case 3:
		               //your code here
		               break;

		          case 4:
		               //your code here
		               break;

		          case 5:
		               //your code here
		               break;
							*/
		          case 6:
							{
									 //user wants to quit
		               Quit = true;  //execution continues after the switch
		                //or do this to end program
		               //return 0;
							}
		          break;

		          default:
							{
		                std::cout << "Bad Input, Try again " << std::endl;
							}
		          break;
		   }

	}

return 0;
} //end of main

void ShowMenu() {
cout << "-------------------------OPCOES--------------------------------------\n";
		cout << "1 - Listar poemas\n";
		cout << "2 - Classificar poema: Soneto?\n";
		cout << "3 - Dados gerais do poema (numero de palavras, versos e estrofes)\n";
		cout << "4 - Achar Rimas\n";
    cout << "5 - Achar Repeticoes\n";
		cout << "6 - Sair\n";
		cout << "Digite o numero correspondente a operacao desejada: " << endl;
}
