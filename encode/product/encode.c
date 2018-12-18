#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void createNibbles(char text, FILE* wfp);
void calculateParity(u_int8_t val, FILE* wpf);
int readFromFile(const char *filename, const char *savefile);
int countSetBits(u_int8_t n);

int main(int argc, char* argv[]) 
{
    if (argc == 3) 
    {
        int check = 0;
        check = readFromFile(argv[1],argv[2]);
        if (check == -1)
        {
            printf("File not Found\n");
            return check;
        }
        printf("Success: File has been encoded\n");
        return 0;
    }
    printf("Something whent wrong!\n");
    return -1;
}

int readFromFile(const char *filename, const char *savefile)
{
    FILE *fp;
    char text;
    fp = fopen(filename, "r");
    int res;
    if (fp == NULL)
        return -1;
    FILE *wfp;
    wfp = fopen(savefile,"a");
    if (wfp == NULL)
        wfp = fopen(savefile,"w");
    if (wfp == NULL)
        return -1;
    res = fread(&text,1,1,fp);
    while (res != 0)
    {
        createNibbles(text,wfp);
        res = fread(&text,1,1,fp);
    }
    fclose(wfp);
    fclose(fp);
    return 0;
}

void createNibbles(char text, FILE* wfp)
{
    u_int8_t xm, xl;
    xl = text & 0x0F;
    xm = (text & 0xF0) >> 4;
    calculateParity(xm,wfp);
    calculateParity(xl,wfp);
}

void calculateParity(u_int8_t val, FILE* wfp)
{
    u_int8_t cpy = val;
    int counts[3];
    cpy &= ~(1UL << 3);
    counts[0] = countSetBits(cpy);
    cpy = val;
    cpy &= ~(1UL << 2);
    counts[1] = countSetBits(cpy);
    cpy = val;
    cpy &= ~1UL;
    counts[2] = countSetBits(cpy);
    cpy = val;
    cpy <<= 3;
    for (int i = 0; i < 3; i++)
    {
        if (counts[i] == 1)
            cpy |= 1UL << i;
    }
    fwrite(&cpy,1,1,wfp);
}

int countSetBits(u_int8_t n)
{
    int count = 0;
    while (n)
    {
        count += n & 1;
        n >>= 1;
    }
    return count%2; 
}