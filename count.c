#include "count.h"

int playedCount;

void savePlayed(int playedCount)
{
	FILE *f = fopen("count.bin", "wb+");
	if (f == NULL) {
		printf ("Error: file count.bin was not opened for writing\n");
	}
	if(playedCount == -1)
	{
		int x = 0;
		fwrite((&x), sizeof(int), 1, f);
		fclose(f);
	}
	else
    {
    	//critical
    	playedCount++;
        fwrite((&playedCount), sizeof(int), 1, f);
       	fclose(f);
    }
}

void loadPlayed(int * playedCount)
{
	FILE *f = fopen("count.bin", "rb");
	if (f == NULL) {
		//printf ("File data.bin is missing..\n.");
		savePlayed(-1);
	} else {
        fread((*&playedCount), sizeof(int), 1, f);
	}
}
