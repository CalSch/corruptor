#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define BUFFER_SIZE 8

unsigned char buffer[BUFFER_SIZE];

int currentPosition = 0;
int totalChunks = 0;
int mutations = 0;
int mutationChance = 100;

bool debug = true;

int readBuffer(FILE* ptr) {
	size_t objs = fread(buffer,sizeof(buffer[0]),BUFFER_SIZE,ptr);
	if (debug)
		printf("Read %ld objs\n",objs);
	totalChunks++;
	currentPosition += objs;
	return objs;
}

void writeBuffer(FILE* ptr, int bytes) {
	fwrite(buffer,sizeof(buffer[0]),bytes,ptr);
}

void mutateBuffer(int maxByte) {
	if (rand() % mutationChance != 0)
		return;
	int byte = rand() % maxByte;
	int bit = rand() % 8;
	int flipNum = 1 << bit;
	printf("[0x%08x] ",currentPosition);
	printf("Changing buffer[%d]=%02x ",byte,buffer[byte]);
	buffer[byte] = buffer[byte] ^ flipNum;
	printf("to %02x\n",buffer[byte]);

	mutations++;
}

void printBuffer() {
	for (int i=0;i<BUFFER_SIZE;i++) {
		printf("%02x ",buffer[i]);
	}
	printf("\n");
}

int main(int argc, char **argv) {
	srand((unsigned)time(NULL));
	printf("hola\n");
	char* filename;
	for (int i=0;i<argc;i++) {
		printf("argv[%d] = '%s'\n",i,argv[i]);
		switch (i) {
		case 1:
			filename = argv[i];
			printf("filename='%s'\n",filename);
			break;
		case 2:
			mutationChance=atoi(argv[i]);
			printf("mutationChance='%d'\n",mutationChance);
			break;
		
		default:
			break;
		}
	}

	char* outfilename = malloc(strlen(filename)+4);
	strcpy(outfilename,"out/");
	strcat(outfilename,filename);

	printf("Opening infile ('%s')\n",filename);
	FILE *infile = fopen(filename,"rb");
	printf("Opening outfile ('%s')\n",outfilename);
	FILE *outfile = fopen(outfilename,"wb");

	bool running = true;
	// for (int i=10;i--;) {
	while (running) {
		int objs = readBuffer(infile);
		printBuffer();
		mutateBuffer(objs);
		writeBuffer(outfile,objs);
		if (objs != BUFFER_SIZE) {
			running = false;
		}
	}

	printf("Closing infile\n");
	fclose(infile);
	printf("Closing outfile\n");
	fclose(outfile);

	printf("Closed\n");
	printf("%d chunks\n",totalChunks);
	printf("%d mutations\n",mutations);

	return 0;
}
