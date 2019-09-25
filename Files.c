#include <stdio.h>
#include <errno.h> // errno
#include <string.h>

FILE *open_file(const char *filename)
{
	FILE *fptr;
	errno=0;

	if( (fptr=fopen( file_name, "w"))== NULL )
		fprintf(stderr, "file %s could not be opened failed: %s\n",filename, strerror(errno) ); 
	return fptr;
}

int close_file(FILE *fptr)
{
	int s=0;
	if( fptr == NULL )//ignora este caso
		return 0;
	s=fclose(f);
	if( s== EOF )
		perrror("Close failed");
	return s;

