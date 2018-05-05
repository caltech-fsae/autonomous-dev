#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char ch;

    FILE *target, *source;   /* file pointer */
    source = fopen("point.proto", "r");

    int count = 0;
    char count_str[sizeof(int) * 4 + 1];
    sprintf(count_str, "%d", count);
    char *fN = malloc(strlen("point") + strlen(count_str) + 1);
    char fName[256] = "";
    strncpy(fName, fN, 256);
    fName[255] = '\0';

    count ++;

    /*creating (open) a file*/
    target = fopen(fName,"w");
    /*check file created or not*/
    if(target == NULL || source == NULL)
    {
        exit(0); /* exit from program, file error. */
    }


    while(( ch = fgetc(source)) != EOF )
      fputc(ch, target);

    fclose(source);
    fclose(target);
}
