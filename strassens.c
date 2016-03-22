#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "strassens.h"

int main(int argc, char **argv){

	// parse inputs 
	if(argc != 4){
		printf("Command line input should be in the form  ./strassen 0 dimension inputfile" );
		return -1; 
	}

	unsigned flag = atoi(argv[1],NULL, 10);
	unsigned dimension = atoi(argv[2], NULL, 10);
	unsigned inputfile = atoi(argv[3], NULL, 10);



}

