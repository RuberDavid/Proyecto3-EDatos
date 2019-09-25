#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int data_t ;

typedef struct
Nodo{
	data_t data;
	struct Nodo *next;
} Node;

typedef Node* List;

Node* new_node(data_t );
bool empty( List );
void push_front(List*,data_t );
void pop_front(List* );

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::



Node* new_node(const data_t val)
// Crea nuevo nodo
{
	Node* res=(Node*)malloc( sizeof(Node) );

	if( res == NULL )
	{
		fprintf( stderr, "No se pudo alocar memoria\n");
		return res;
	}
	else
	{
		res->data= val;
		res->next=NULL;
	}

	return res;
}

bool empty( const List Mi_lista )
//pregunta si está vacia la lista
{
	if( Mi_lista == NULL )
		return true;
	return false;
}

void push_front(List *my_list, data_t val)
{
	Node* p= new_node(val);
	p->next= *my_list;
	*my_list= p;
}

void pop_front(List *my_list)
{
	List aux= (*my_list)->next;
	free(*my_list);
	*my_list= aux;
}
}
