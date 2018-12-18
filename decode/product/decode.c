#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int readFromFile(const char *in, const char *out);
int writeToFile(const char *filename, u_int8_t byte);
void calculateParity(u_int8_t *byte);

int main(int argc, char**argv) 
{
    if (argc == 3)
    {
        int check = 0;
        check = readFromFile(argv[1],argv[2]);
        if (check == -1)
        {
            printf("No file Found\n");
            return -1;
        }
        printf("Finished\n");
        return 0;
    }
    printf("Something whent wrong\n");
    return -1;
}

int readFromFile(const char *in, const char *out)
{
    FILE *fp;
    u_int8_t byte1, byte2;
    fp = fopen(in, "r");
    int res;
    if (fp == NULL)
        return -1;
    res = fread(&byte1,1,1,fp);
    fread(&byte2,1,1,fp);
    while (res != 0)
    {
        calculateParity(&byte1);
        calculateParity(&byte2);
        byte1 <<= 4;
        const char byte = byte1 | byte2;
        writeToFile(out,byte);
        res = fread(&byte1,1,1,fp);
        fread(&byte2,1,1,fp);
    }
    fseek(fp, 0, SEEK_SET);
    fclose(fp);
    return 0;
}

int writeToFile(const char *filename, u_int8_t byte)
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

void calculateParity(u_int8_t *byte)
{
    int parity[3], p[3], problemSections[3], data[4];
    int problems = 0;
    u_int8_t dataByte = *byte >> 3;
    dataByte <<= 4;
    dataByte >>= 4;
    u_int8_t parityByte = *byte << 5;
    parityByte >>= 5;
    for (int i=0; i<3; i++)
    {
        parity[i] = (parityByte >> i) & 1;
    }
    for (int i=0; i<4; i++)
    {
        data[i] = (dataByte >> i) & 1;
    }
    p[0] = (data[1] + data[2] + data[0])%2;
    p[1] = (data[1] + data[0] + data[3])%2;
    p[2] = (data[1] + data[2] + data[3])%2;
    for (int i=0; i<3; i++)
    {
        if (p[i] != parity[i])
            problemSections[problems++] = i;
    }
    if (problems == 2)
    {
        if (problemSections[0] == 0 && problemSections[1] == 1)
            dataByte = dataByte ^(1 << 0);
        if (problemSections[0] == 0 && problemSections[1] == 2)
            dataByte = dataByte ^(1 << 2);
        if (problemSections[0] == 1 && problemSections[1] == 2)
            dataByte = dataByte ^(1 << 3);
    }
    else if (problems == 3) dataByte = dataByte ^(1 << 1);
    *byte = dataByte;
}