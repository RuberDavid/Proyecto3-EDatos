#include <stdio.h>
#include <errno.h> 
#include <string.h>

FILE *open_file(const char *file_name, char * mode)
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

int main()
{
	FILE* new= open_file("miarchivo.txt", "rb+");
	init_random_acces_file( new, 100, 0 );
	int val;

	while( !feof( new ) )
	{
		fread( &val, sizeof(val), 1, new );  
		printf("%d ", val);
	}
}

