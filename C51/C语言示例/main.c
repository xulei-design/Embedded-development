#include <stdio.h>
include <stdlib.h>
include <string.h>
#define MAX_COLD 20
#define MAX_INPUT 1000

int read_column_number(int columns[],int max);
void rearrange(char *output, char const *intput, int n_columns, int const columns[]);

int main(void)
{
    int n_columns;
    int columns[MAX_COLS];
    char input[MAX_INPUT];
    char output[MAX_INPUT];
    
    n_columns = read_column_number(columns,MAX_COLS);
    
    while(gets(input) != NULL)
    {
        printf("Original input : %s\n",input);
        rearrange(output, input, n_columns,columns);
        printf("Rearranged lint: %s\n" , output);
    }
    return EXIT_SUCCESS;
}
    