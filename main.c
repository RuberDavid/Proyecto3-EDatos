#include <stdint.h>//aquí se define el tipo de dato uint16_t
#include <stdio.h>
#include <errno.h>//para manejo de errores
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define FILE_NAME_SIZE 30

typedef int data_t ;

typedef struct
Nodo{
	data_t data;
	struct Nodo *next;
} Node;

typedef Node* List;

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
Node* new_node(data_t );
bool empty( List );
void push_front(List*,data_t );
void pop_front(List* );

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
FILE *open_file(const char *file_name, const char* mode);
int close_file(FILE *fptr);
void init_random_acces_file( FILE* arch,const unsigned count,  int val);

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
unsigned seed;//semilla de la función de randomización 
//función de randomización
unsigned lfsr(void);

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

int main()
{
	FILE* archivos[4];
	char nombre[FILE_NAME_SIZE];
	List direcciones=NULL;
	unsigned int in_dir;
	unsigned int contador;
	seed=  (uint16_t) time(NULL) ;

	printf("\n\tintroduzca el nombre del archivo:\n\t");
	scanf("%30s", nombre);
	
	//inicializa una arreglo de archivos y los abre, el primero será el archivo de entrada
	archivos[0]=open_file(nombre,"r");
	archivos[1]=open_file("salida1","rb+");
	archivos[2]=open_file("salida2","rb+");
	archivos[3]=open_file("salida3","rb+");

	

	contador=0;

	//Recorre el arreglo de archivos hasta el penúltimo
	for(int i=0; i<1 ; i++)//DEBUG: aument to 4
	{
		//lee el archivo actual en una lista
		while( !feof( archivos[i] ) )
		{
			int entrada;
			fscanf( archivos[i] , "%d", &entrada );
			push_front( &direcciones, entrada);
			if( i == 0 )
				contador++;
		}

		if( i == 0 )
			//inicializar archivos
			for( int j=1; i<4 ; i++)
				init_random_acces_file( archivos[j] , contador, 0);

		//escribe aleatoriamente en el archivo siguiente los datos de la lista
		while( !empty( direcciones ) )
		{
			//función de randomización
			lfsr();
			
			//if(0 ) TODO
			pop_front( &direcciones ) ;

		}
	}

	//lee una dirección de memoria dada
	//scanf("%u" &in_dir);

	//si está en el "sistema" de archivos
	//	imprime la ubicación de este en los tres archivos de salida
	//si no
	//	imprime mensaje acerca de esto
	


	//cierra archivos
	for(int i=0; i<4 ; i++)
		close_file( archivos[i] );

}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

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

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
FILE *open_file(const char *file_name, const char* mode)
{
	FILE *fptr;
	errno=0;

	if( (fptr=fopen( file_name, mode))== NULL )
		fprintf(stderr, "file %s could not be opened failed: %s\n",file_name, strerror(errno) ); 
	return fptr;
}

int close_file(FILE *fptr)
{
	int s=0;
	if( fptr == NULL )//ignora este caso
		return 0;
	s=fclose(fptr);
	if( s== EOF )
		perror("Close failed");
	return s;
}

void init_random_acces_file( FILE* arch,const unsigned count,  int val)
{
	for(int i=0; i< count+1 ; i++)
	{
		fseek( arch, i*sizeof( int ) , SEEK_SET );
		fwrite( &val, sizeof( val ), 1, arch );

	}


}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

unsigned lfsr(void)
//función para números pseudo-aleatorios usando un Linear-feedback shift register
{
	uint16_t lfsr = seed; 
	uint16_t bit; //se define un entero de 16 bits para permitir operaciónes como <<15

	bit= ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) /* & 1u */;
	lfsr= (lfsr >> 1) | (bit << 15);
	seed= lfsr;

	return lfsr;
}


