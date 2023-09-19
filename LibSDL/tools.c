#include <stdlib.h>
#include <stdio.h>
#include <string.h>



// convertion strtoL strtod



// Saisie securise
char *input_read(char *str, int size){
    char *data;

    data = fgets(str, size, stdin);

    if(data){
        size_t len = strlen(str) - 1;

        if(str[len] == '\n'){
            str[len] = '\0';
        } 
        else {
            // vide tempons de lecture
            fscanf(stdin, "%*[^\n]");
            fgetc(stdin);
        }
    
    }

    return data;
}

void flush_input_buffer(void)
{
    int c = 0;

    while (c != '\n' && c != EOF){
        c = getchar();
    }
}

int main(void){
    char buffer[6];

    printf("Mot de 5 lettre : ");
    input_read(buffer, 6);
    printf("%s\n", buffer);

    printf("-----------------------------------n");

    printf("Mot de 5 lettre : ");
    input_read(buffer, 6);
    printf("%s\n", buffer);

    return 0;
}
