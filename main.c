#include <stdio.h>
#include "elf.h"
#include "pe.h"

#define PE  		1
#define ELF  	 	2
#define MACHO 	 	3


int get_image_type(FILE *fp);

int main(int argc, char **argv)
{
	FILE *fp;
	char *fname;
	int ftype;
	void (*analyzer)(FILE *);

	if ( argc < 2 )
	{
		printf( "Usage: %s: <executable>\n", argv[0] );
		return 1;
	}
	fname = argv[1];
	fp = fopen( fname, "rb" );
	
	ftype = get_image_type(fp);
	if(  	 ftype == PE    ) analyzer = &analyze_pe; 
	else if( ftype == ELF   ) analyzer = &analyze_elf; 
	else if( ftype == MACHO ) printf( "Mach-O file detected.\n" ); 
	else {
		printf("Unknown file type.\n");
		return 1;
	}
	analyzer(fp);


	fclose( fp );
	return 0;
}





int get_image_type(FILE *fp)
{
	unsigned char sig[4];
	size_t 	size;
	
	size = fread( &sig, 1, 4, fp );
	if( size != 4 )
	{
		fprintf(stderr, "[-] Error reading file header.\n");
		return -1;
	}
	
	/* Debug output for the header */
	fprintf(stderr, "0x");
	for( int i = 0; i < 4; i++ )
	{
		fprintf(stderr, "%2x", sig[i]);
	}
	fprintf(stderr, "\n");

	 if( sig[0] == 0x4D &&
		 sig[1] == 0x5A &&
		 sig[2] == 0x90 &&
		 sig[3] == 0x00   )
	{
		return PE;
	}
	else if( sig[0] == 0x7F &&
			 sig[1] == 0x45 &&
			 sig[2] == 0x4C &&
			 sig[3] == 0x46   )
	{
		return ELF;
	}

	return 0;
}
