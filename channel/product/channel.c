#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int readFromFile(const char *in, const char *out);
int writeToFile(const char *filename, const u_int8_t byte);

int main(int argc, char**argv) 
{
    int count;
    count = readFromFile(argv[1],argv[2]);
    if (count == -1)
    {
        printf("File not found\n");
        return 0;
    }
    printf("One flip in each byte, total bits flips: %d\n", count);
    return 0;
}

int readFromFile(const char *in, const char *out)
{
    FILE *fp;
    fp = fopen(in, "r");
    if (fp == NULL)
        return -1;
    srand(time(NULL));
    int res, random, counter = 0;
    int array[8] = {0,0,0,0,0,0,0,0};
    char byte;
    res = fread(&byte,1,1,fp);
    while (res != 0)
    {
        random = rand()%8;
        byte ^= (1 << random);
        writeToFile(out,byte);
        res = fread(&byte,1,1,fp);
        counter++;
        array[random] += 1;
    }
    for (int i = 0; i < 8; i++)
    {
        int bite = i;
        printf("%d flipped %d times\n",++bite,array[i]);
    }
    fclose(fp);
    return counter;
}

int writeToFile(const char *filename, const u_int8_t byte)
{
    FILE *fp;
    fp = fopen(filename,"a");
    if (fp == NULL)
        fp = fopen(filename,"w");
    if (fp == NULL)
        return -1;
    fwrite(&byte,1,1,fp);
    fclose(fp);
    return 0;
}