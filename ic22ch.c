/* ic22ch.c - A tool to calculate diode vs frequency maps for the
 * Icom IC-22S 2M Radio.
 *
 * (C) 2014 - KB4OID Labs, A division of Kodetroll Heavy Industries
 * Author: Kodetroll (KB4OID)
 * Date: December 2014
 *
 * build by 'gcc -o ic22ch ic22ch.c'
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_PLL_FREQ 144390	// PLL Value for N=0 (in KHz)
#define CHANNEL_SPACING 15	// PLL Step Value (in KHz)

char ifilename[] = "diodes.txt";
char ofilename[] = "freqs.txt";
char temp[120];

int cvtbin(char * num);
char* get_frequency(char * diodes);

int cvtbin(char * num)
{
	int n = 0;
	int i,b,k;
	b = 1;
	for(k=0;k<strlen(num);k++) {
		i = 7-k;
		if ((num[i]-0x30) == 1)
			n = n + b;

		b = b * 2;

	}
	return(n);
}
char* get_frequency(char * diodes)
{
	char * pch;
	int i,N;
	long f;

	// Split the diode line into tokens based on ':'
	pch = strtok(diodes,":");

	// Use the first token to generate the channel #
	int ch = atoi(pch);

	// Get the next token (Diode matrix N)
	pch = strtok(NULL,":");

	// Calculate the PLL Divider Value (N) from the
	// diode position string (convert binary to dec)
	N = cvtbin(pch);

	// Calculate the Channel Frequency based on the
	// the PLL Divider (N) and the PLL Base Frequency
	f = (N * CHANNEL_SPACING) + BASE_PLL_FREQ;

	// Create a freqs file line - 'CH:FREQ'
	sprintf(temp,"%d: %ld",ch,f);
	return(temp);
}


int main(int argc, char * argv[])
{
	FILE *ifp,*ofp;
	char * diode;
	char * frequency;
	char buf[100];

	// Open the diode channel string file
	ifp=fopen(ifilename,"r");
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file %s!\n",ifilename);
		exit(1);
	}

	// Open the frequency channel output file
	ofp=fopen(ofilename,"w");
	if (ofp == NULL) {
		fprintf(stderr, "Can't open output file %s!\n",ofilename);
		exit(1);
	}

	// for each diode line, calculate channel frequency
	while(fscanf(ifp,"%s", diode) != EOF) {
		if (strncmp(diode,"#",1) != 0) {
			// get ch, freq
			frequency=get_frequency(diode);
			// write this to output
			fprintf(ofp,"%s\n",frequency);
		}
	}

	// Close all files
	close(ifp);
	close(ofp);

	// done!
	exit(0);
}
