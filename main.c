#include <stdio.h>
#include <stdlib.h>
#include "matriz_esparsa.h"

int main(){
    int aux;
    MATRIZ_ESPARSA *matriz;
	MATRIZ_ESPARSA *matriz1;
	MATRIZ_ESPARSA *soma;
	MATRIZ_ESPARSA *transposta;
	MATRIZ_ESPARSA *produto;


matriz=criar_matriz(2,2);
set_matriz(matriz,1,1,5);
set_matriz(matriz,1,2,1);
set_matriz(matriz,2,1,3);
set_matriz(matriz,2,2,2);

printf("Matriz\n");
print_matriz(matriz);
printf("\n");
matriz1=criar_matriz(2,2);
set_matriz(matriz1,1,1,0);
set_matriz(matriz1,1,2,5);
set_matriz(matriz1,2,1,1);
set_matriz(matriz1,2,2,6);

printf("Matriz\n");
print_matriz(matriz1);

printf("Transposta\n");
transposta = transposta_matriz(matriz1);
print_matriz(transposta);

printf("Produto\n");
produto = multiplicar_matriz(matriz, matriz1);
print_matriz(produto);

soma = somar_matriz(matriz, matriz1);
print_matriz(soma);


}