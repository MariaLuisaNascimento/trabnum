#include <stdio.h>
#include <stdlib.h>
#include "matriz_esparsa.h"
/*
int* cria_vetor(MATRIZ_ESPARSA* matriz,int linha, int tamanho){
		float vetor_b[tamanho];
		for(int j = 1; j <= tamanho; j++){
			vetor_b[j-1] = get_matriz(matriz,j,j);
			printf("%.1f ", vetor_b[j-1]);
		}
		printf("\n\n");
	}
	*/

int main(){

	int tamanho = 6;
	int i;
	MATRIZ_ESPARSA *matriz;
	matriz = criar_matriz(6,6);
	for(i=1; i<= tamanho; i++){
		set_matriz(matriz,i,i,4.5);
		set_matriz(matriz,i,i+1,-1);
		set_matriz(matriz,i+1,i,-1);
		set_matriz(matriz,i,i+3,-1);
		set_matriz(matriz,i+3,i,-1); 
	}

	float vetor_b[tamanho];
	for(int j = 1; j <= tamanho; j++){
		vetor_b[j-1] = 0;
		for(int k = 1; k<= tamanho; k++){
			vetor_b[j-1] += get_matriz(matriz,j,k);
		}
		printf("%.1f ", vetor_b[j-1]);
	}
	printf("\n\n");

	float vetor_x[tamanho];

	int j;

	for(i=1; i<=tamanho; i++){
		vetor_x[i-1] = (vetor_b[i-1]/get_matriz(matriz,i,i));
		for(j=1; j<= tamanho; j++){
			vetor_x[j-1] -= (vetor_x[j-2]/get_matriz(matriz,j,j));
		}
		printf("%.3f \n\n", vetor_x[i-1]);
		printf("%d\n", i);
	}
}