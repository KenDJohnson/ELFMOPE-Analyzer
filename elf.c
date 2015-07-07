#include <stdio.h>
#include <elf.h>
#include <elf_analyze.h>

void analyze_32(FILE *fp);
void analyze_64(FILE *fp);


void analyze_elf(FILE *fp)
{
	int class;

	class = getc(fp);

	// Check for architecture
	if(class == CLASS_32_BIT)
	{
		analyze_32(fp);
	}
	else if(class == CLASS_64_BIT)
	{
		analyze_64(fp);
	}
}


void analyze_32(FILE *fp)
{

}

void analyze_64(FILE *fp)
{
	// Reset fp to get entire header
	fseek(fp, 0, SEEK_SET);

	// ELF Header struct
	Elf64_Ehdr header;

	
	// Read the entire header (0x40 bytes) into the Elf64_Ehdr struct
	fread(&header, HEADER_SIZE_64, 1, fp);

	printf("File is a 64 bit executable");
	
	switch(header.e_ident[EI_DATA])
	{

		case ELFDATANONE:
			printf(" and does not have a valid machine archetecture\n");
			break;
		case ELFDATA2LSB:
			printf(" in little endian 2's compiment.\n");
			break;
		case ELFDATA2MSB:
			printf(" in big endian 2's compliment.\n");
			break;
		case ELFDATANUM:
			printf(" and I need to look up 0x03 spec.\n");
			break;
	}

	if(header.e_ident[EI_VERSION] == 0x01)
	{
		printf("ELF Version 1.\n");
	}
	
	printf("Target operating system: ");

	switch(header.e_ident[EI_OSABI])
	{
		case ELFOSABI_NONE:
			printf("UNIX System V ABI.\n");
			break;
		case ELFOSABI_HPUX:
			printf("HP-UX.\n");
			break;
		case ELFOSABI_NETBSD:
			printf("NetBSD.\n");
			break;
		case ELFOSABI_GNU:
			printf("GNU/Linux.\n");
			break;
	 	case ELFOSABI_SOLARIS:
			printf("Sun Solaris.\n");
			break;
		case ELFOSABI_AIX:
			printf("IBM AIX.\n");
			break;
		case ELFOSABI_IRIX:
			printf("SGI Irix.\n");
			break;
		case ELFOSABI_FREEBSD:
			printf("FreeBSD.\n");
			break;
		case ELFOSABI_TRU64:
			printf("Compaq TRU64 UNIX.\n");
			break;
		case ELFOSABI_MODESTO:
			printf("Novell Modesto.\n");
			break;
		case ELFOSABI_OPENBSD:
			printf("OpenBSD.\n");
			break;
		case ELFOSABI_ARM_AEABI:
			printf("ARM EABI.\n");
			break;
		case ELFOSABI_ARM:
			printf("ARM.\n");
			break;
		case ELFOSABI_STANDALONE:
			printf("Stanalone (embedded) application.\n");
			break;
	}
}
