#include <stdio.h>

int main(int argc, char* argv[])
{    
    FILE* fp;
    int i;
    char linea[200];
    char palabras[2000][200];
   
    /*fopen_s(&fp, argv[1], "w");
    for (i = 0; i < argc; i++)
        sprintf("%s", argv[i]);

    fclose(fp);*/
    printf("Leyendo la info...\n");
    fopen_s(&fp, argv[1], "r");
    int numDatos;
    //fscanf_s(fp, "%i", &numDatos);
    //for (i=0; i < numDatos; i++)
    i = 0;
    while (!feof(fp)) // file end of file
    {
        printf("leyendo palabra palabra: %i\n", i);
        fscanf_s(fp, "%s", palabras[i++], 200);
        
    }
    fclose(fp);
    printf("Num palabras: %i", i);

    for (int j = 0; j < i-1; j++)
        printf("%s", palabras[j]);

}

