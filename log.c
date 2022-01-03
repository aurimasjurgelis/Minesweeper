#include "log.h"

clock_t start;
clock_t end;

char buff[20];
struct tm *sTm;

void logProgramStart()
{
	clock_t start = clock();
	FILE *f = fopen("log.txt", "a");
	if (f == NULL) {
		printf ("Error: file log.txt was not opened for writing\n");
	}
	else
    {
    	struct tm *sTm;

    	time_t now = time (0);
    	sTm = gmtime (&now);

    	strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
    	fprintf (f,"%s %s\n", buff, "Program START.\n");
    }
}

void logProgramEnd()
{
	FILE *f = fopen("log.txt", "a");
	if (f == NULL) {
		printf ("Error: file log.txt was not opened for writing\n");
	}
	else
    {
    	time_t now = time (0);
    	sTm = gmtime (&now);

    	strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
    	fprintf (f,"%s %s\n", buff, "Program END. ");
    	clock_t end = clock();
    	float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    	fprintf(f,"Program duration: %.3f seconds\n",seconds);
       	fclose(f);
    }
}
