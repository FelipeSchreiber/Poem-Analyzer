#ifndef _HEAP_H
#define _HEAP_H
#include <cstddef>
#include <exception>
#include <string>
#include <vector>
using namespace std;
 
class myClass{
		public:
		 myClass(string id,float value):value(value),vertexId(id){};
		 string vertexId;
		 myClass(myClass & m):value(m.value),vertexId(m.vertexId){};
		 int value;
     bool operator<(myClass &b)
     {
				return this->value < b.value;
     }
};

class myException: public exception
{
  virtual const char* what() const throw()
  {
		return "YOU MUST PASS A NON NULL POINTER TO \"insert\" METHOD FROM CLASS \"Heap\"";
  }
};

template <class T> class wrapper;

//essa classe prove uma abstracao dos ponteiros para o usuario. Tais ponteiros serao utilizados para estruturar o heap
template <class T>
class myPtr{
	public:
		wrapper<T> *next;
		wrapper<T> *child;		
		wrapper<T> *prev;
};

//classe que contem um ponteiro para a classe definida pelo usuario
template <class T>
class wrapper:public myPtr<T>
{
  template <class V>
  friend class Heap;
	public:
		wrapper(T*elem):member(elem){}
		const T* getMember(){return this->member;}
	private:
		T* member;
};

/*Essa estrutura eh uma estrutura container, de forma similar as outras classes containers da linguagem C++. Nela guardamos quantos nos existem, tal como um ponteiro que aponta para o topo da arvore, isto eh o elemento cuja chave eh a menor dentre todas do heap. Alem disso tem um hash que guarda o endereco de cada no dentro do heap*/
/*Class T eh a classe definida pelo usuario e U eh o tipo da chave que sera usada para identificacao*/
template <class T>
class Heap
{
 public:
	unsigned int get_size();
	const T* get_root();
	Heap();
	Heap(Heap<T> &h);
	~Heap();
	bool is_empty();
	void insert (T *elem);
	T* pop ();
 private:
	wrapper<T> *merge_right (wrapper<T> *a);
	wrapper<T> *merge_left (wrapper<T> *a);
	wrapper<T> *mergeSubheaps (wrapper<T> *a);
	wrapper<T> *merge (wrapper<T> *a, wrapper<T> *b);
	void detach_subheap (wrapper<T> *elem);
	unsigned int size;//diz quantos nos estao incluidos no heap
  wrapper<T>* root;//aponta para o elemento cuja chave eh minima
};

template <class T>
const T* Heap<T>::get_root()
{
	return this->root->member;
}

template <class T>
unsigned int Heap<T>::get_size()
{
	return this->size;
}

template <class T>
bool Heap<T>::is_empty()
{
	return (this->root == NULL);
}

template <class T>
wrapper<T> * Heap<T>::merge(wrapper<T> *a, wrapper<T> *b)
{
  if ( *(a->member) < *(b->member) ) //Retorna true caso a chave do elemento a seja menor que a chave do elemento b
    {
      if (a->child != NULL)
        a->child->prev = b;
/*Suponha a seguinte configuracao antes da linha acima ser executa, com chave A < chave B, onde "--->" representam ponteiros:
 *
 *  A 
 * |^
 * ||
 * ^| 
 * W ---> X ---> Y     B ---> K
 *   <---   <---         <---
 *
 *Sendo A e B as respectivas raizes de seus heaps. Apos a linha anterior ser executada teremos: 
 *                 A 
 *                 |
 *                 |
 *                 ^  
 * k  <--- B  <--- W ---> X ---> Y     
 *    --->           <---   <---   
 *
 * Isto eh, A continua apontando para W, no entanto o ponteiro anterior de W passa a apontar para B   
 * */
      if (b->next != NULL)
        b->next->prev = a;
/*  
 *Continuando com o exemplo:
 *     ----------->A 
 *    /            |
 *   /             |
 *  /              ^  
 * k  <--- B  <--- W ---> X ---> Y     
 *                   <---   <---   
 */    
      a->next = b->next;
/*  
 *     ---------->A ---> k
 *    /           |
 *   /            |
 *  /             ^  
 * k  <--- B <--- W ---> X ---> Y     
 *                  <---   <---   
 * 
 * (k aqui eh representado duas vezes para facilitar)     
 */    
      b->next = a->child;
/*  
 *               A ---> k
 *               | <---
 *               |
 *               ^  
 *        B <--- W ---> X ---> Y     
 *          --->   <---   <---   
 */    
         
     a->child = b;
/*  
 *               A ---> k
 *               | <---
 *               |
 *               ^  
 *               B <--- W ---> X ---> Y     
 *                  --->   <---   <---   
 */    
      b->prev = a;
/*  
 *                A ---> k
 *               ^| <---
 *               ||
 *               |^  
 *               B <--- W ---> X ---> Y     
 *                  --->   <---   <---   
 */    
      return a;
    }
  if (b->child != NULL)//Caso simetrico, isto eh, quando b <= a
    b->child->prev = a;
  if (a->prev != NULL && a->prev->child != a)
    a->prev->next = b;
  if(a->prev)
   b->prev = a->prev;
  else
   b->prev = NULL;
  a->prev = b;
  if(b->child)
   a->next = b->child;
  else
   a->next = NULL;
  b->child = a;
  return b;
}

/* Insere um elemento no heap. Para tanto compara apenas a raiz e o novo elemento a ser adcionado. A posicao do novo elemento no heap sera determinada pela funcao merge apresentada anteriormente*/
template <class T>
void Heap<T>::insert (T *elem)
{ 
	if(elem == NULL)
	{
		myException myExcpt;
    throw myExcpt;
	}
  this->size++;//incrementa o tamanho do heap
	wrapper<T> *elemento = new wrapper<T>(elem);
	elemento->prev = NULL;
  elemento->next = NULL;
  elemento->child = NULL; 
  /*Inicialmente todos os ponteiros do novo elemento sao inicializados com NULL*/
  if (this->root == NULL)
  {
   this->root = elemento;//Caso o heap esteja vazio, entao a raiz apontara para o novo elemento
  }
  
/*Na primeira vez que um elemento for inserido no heap teremos essa configuracao:
 *
 *heap           						 node a         
 {               						{
  size = 1;       						value = (valor da chave do elemento que esta sendo inserido);  
  myHash[vertexId] == &a;   
  root-----------> 
 *}                 					child = NULL; 
 *                 						prev = NULL;
 *                 						next = NULL;
 *                					}
 *               
 *Root contem o endereco para o no "a" e myHash[i] contem o endereco de memoria do no cujo vertexId eh "i"      
*/  
  else
   this->root = this->merge(elemento, this->root);//Caso o heap nao esteja vazio, eh necessario efetuar um merge entre a raiz e o novo elemento 
  
/*Suponha que ja tenha um elemento inserido no heap. Supondo que o valor da chave "a" < valor da chave "b", apos a nova insercao teremos a seguinte configuracao:
 *
 *heap           										 node a                                       node b
 {               										{                                             {
  size = 1;       										value = (valor da chave a);    								value = (valor da chave b);
  root== &a
  myHash[(vertexId de a)] == &a
  myHash[(vertexId de b)] == &b
 *}                										child == &b
 *                 										prev = NULL;                                               
 *                										next = NULL;                                 child = NULL;   
 *                                										                             prev == &a 
 *               										}                 	                           next = NULL;
 *                                              	
 *                                                      									       }   
 *Root contem o endereco para o no "a" e myHash[i] contem o endereco de memoria do no cujo vertexId eh "i"        
*/  
}

/* Essa funcao recebe como input o ponteiro child do no raiz. Apos remover a raiz, teremos uma floresta formada pelas suas subarvores, que nada mais eh do que uma lista duplamente encadeada comecando pelo filho mais a esquerda, que era apontado pelo ponteiro child do no raiz. Essa funcao efetua o merge dois a dois entre as subarvores indo da esquerda para a direita. No final teremos ainda uma floresta resultante dos merges. Um ponteiro para a ultima arvore resultante do merge eh retornado */
template <class T>
wrapper<T> * Heap<T>::merge_right (wrapper<T> *a)
{
  wrapper<T> *b;
/* Se antes tinhamos, por exemplo, a seguinte configuracao apos remover o no raiz:
 *(RAIZ -> child == A)
 *RAIZ
 *
 * A ---> B ---> C  ---> D  ---> E
 *   <---   <---    <---    <---
 * |^     |^     |^      |^      |^
 * ||     ||     ||      ||      ||
 * ^|     ^|     ^|      ^|      ^|
 * Ta     Tb     Tc      Td      Te
 *
 * Onde Ta,Tb... representam respectivamente as subarvores dos nos A,B... 
 * */
  for (b = NULL; a != NULL; a = b->next)
    {
      if ((b = a->next) == NULL)
        return a;
      b = this->merge (a, b);
    }
/*

1 iteracao: b == &B || a == &A
2 iteracao: a == &C || b == &D
3 iteracao: a == &E || b == NULL
*/


/*
 *Supondo que a chave do no A < chave do no B e chave do no D < chave do no C, apos a execucao acima teremos:
 *
 *          A  -----------------------> D  --------------> E
 *          |^ <----------------------- |^ <-------------- |^
 *          ||                          ||                 ||
 *          ^|                          ^|                 ^|
 *          B  ---> Ta                  C ---> Td          Te
 *          |^ <---                     |^ <--- 
 *          ||                          ||
 *          ^|                          ^|
 *          Tb                          Tc
 *
 * Primeiramente os heaps A e B foram passados pro merge. Em seguida D e C. Nesse momento "a" aponta pra E e portanto a->next == NULL. A funcao retorna o ponteiro para E
 *
 * Note que apos a execucao ainda nao obtemos uma arvore unica. Assim, de forma a obtermos um unico heap e por conseguinte a raiz, novas operacaoes de merge precisam ser executadas. Dessa vez comecando pela direita, efetuaremos novos merges com os heaps (arvores) consecutivos e nao em separado tal como foi feito acima na funcao merge_left 
 * */       

  return b;
}

/* Essa funcao efetua a segunda sequencia de merges indo da direita pra esquerda. Essa funcao recebe um ponteiro para o ultimo heap resultante da ultima operacao merge efetuada pela funcao merge_right*/
template <class T>
wrapper<T> * Heap<T>::merge_left (wrapper<T> *a)
{
  wrapper<T> *b;
 /* Suponha que antes de executar essa a funcao tenhamos a seguinte configuracao resultante apos merge_right
 *
 *          A  -----------------------> D  --------------> E
 *          |^ <----------------------- |^ <-------------- |^
 *          ||                          ||                 ||
 *          ^|                          ^|                 ^|
 *          B  ---> Ta                  C ---> Td          Te
 *          |^ <---                     |^ <--- 
 *          ||                          ||
 *          ^|                          ^|
 *          Tb                          Tc
 *
 *E que chave de A < chave de E < chave de D  
 *
 */

  for (b = a->prev; b != NULL; b = a->prev)
  { 
   a = this->merge (b, a);
  }  
/*
 1 iteracao: b == &D || a == &E
 2 iteracao: b == &A || a == &E
*/

 /* Apos executar essa a funcao teremos:
 *                                     
 *                                      A
 *                                      |^
 *                                      ||
 *                                      ^|
 *                                      E  ---------> B ---> Ta 
 *                                      |^ <--------- |^  <---
 *                                      ||            ||
 *                                      ^|            ^|
 *                                      D  ---> Te    Tb 
 *                                      |^ <---
 *                                      ||                 
 *                                      ^|                 
 *                                      C ---> Td          
 *                                      |^ <--- 
 *                                      ||
 *                                      ^|
 *                                      Tc
 *
 */

  return a;
}

/* Essa funcao implementa o merge dos subheaps (isto eh, um merge entre os heaps "filhos") do no a. Esse processo eh efetuado em duas etapas. Na primeira etapa o merge_right eh efetuado. Na segunda etapa o merge_left. No final um ponteiro para a nova raiz eh retornada. Essa funcao eh chamada sempre que retirarmos o elemento cuja chave eh minima.*/
template <class T>
wrapper<T> *Heap<T>::mergeSubheaps (wrapper<T> *a)
{
  a->child->prev = NULL;//o no filho nao possui mais ponteiro para o no raiz
  wrapper<T> *e;
  e = this->merge_right (a->child);
  e = this->merge_left (e);
  a->child = NULL;//o antigo no raiz eh completamente desvinculado ao novo heap
  return e;
}

/* Essa funcao desvincula o subheap do restante do heap. Sempre que formos alterar a chave de um elemento, removemos o subheap encabecado por ele e em seguida efetuamos um merge com a raiz atual a fim de obtermos a nova raiz*/
template <class T>
void Heap<T>::detach_subheap (wrapper<T> *elem)
{
  if (elem->prev->child == elem)
   elem->prev->child = elem->next;/*Caso o subheap elem a ser removido for o que comeca a lista encadeada de filhos do no pai(apontado por elem->prev), entao o novo filho que comecara a lista encadeada eh justamente o proximo da lista(apontado por elem->next).*/
  else
    elem->prev->next = elem->next;/*Se o no nao comeca a lista entao existe um no anterior, a menos que ele seja a raiz do heap. Essa linha faz com que a lista encadeada se mantenha mesmo apos a retirada de um no central*/

  if (elem->next != NULL)
    elem->next->prev = elem->prev;/*Se o no que sucede o elemento a ser retirado existir, entao o no anterior pra o qual o proximo aponta precisa ser o no anterior ao elemento a ser retirado*/

  elem->prev = NULL;
  elem->next = NULL;
}

/* Remove o elemento raiz do heap. Essa funcao retorna portanto um ponteiro que aponta para o elemento raiz. Como esse heap esta organizado na forma de arvore, a remocao do no raiz faz com que os filhos do no retirado ocupem o topo da arvore. Assim, de forma a termos um unico elemento na raiz, eh necessario efetuar um merge entre as subarvores do no retirado*/
template <class T>
T*Heap<T>::pop ()
{
  if(this->size > 0)//checa se o heap nao esta vazio
  {
   this->size -= 1;//decrementa o tamanho do heap
   wrapper<T> *r = this->root;
	 T* ptr = r->member;
	 delete r;
	 if (r->child == NULL)//checa se o no raiz possui filhos
   {
    this->root = NULL;//se nao possuir entao a raiz do heap passa a ser NULL, isto eh, o heap esta vazio
		return ptr;
   }
   //caso contrario, o no raiz possui filhos e portanto eh necessario efetuar um merge entre as subarvores do no raiz a fim de obter a nova raiz
   this->root = this->mergeSubheaps (this->root);
   return ptr;
  }
  return NULL;
}

template <class T>
Heap<T>::~Heap()
{
	while(!this->is_empty() )
  {
		this->pop();
  }
}

template <class T>
Heap<T>::Heap(Heap &h)
{
	vector<T*> vec;
	while(!h.is_empty() )
  {
		vec.push_back(h.pop());
  }
  for (typename vector<T*>::iterator it = vec.begin() ; it != vec.end(); ++it)
  { 
		h.insert(*it);
		T* copy = new T(**it);	
		this->insert(copy);
	}
}

template <class T>
Heap<T>::Heap()
{
  this->size = 0;
  this->root = NULL;//inicializa o ponteiro raiz com NULL
}


#endif /* _HEAP_H */
