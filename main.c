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

	int tamanho = 200;
	int itmax = 12;
	int i;
	MATRIZ_ESPARSA *matriz;
	matriz = criar_matriz(tamanho,tamanho);
	for(i=1; i<= tamanho; i++){
		set_matriz(matriz,i,i,4.5);
		set_matriz(matriz,i,i+1,-1);
		set_matriz(matriz,i+1,i,-1);
		set_matriz(matriz,i,i+3,-1);
		set_matriz(matriz,i+3,i,-1); 
	}

	float vetor_b[tamanho];
	printf("Vetor b\n");
	for(int j = 1; j <= tamanho; j++){
		vetor_b[j-1] = 0;
		for(int m = 1; m <= tamanho; m++){
			vetor_b[j-1] += get_matriz(matriz,j,m);
		}
		printf("%.3f ", vetor_b[j-1]);
	}
	printf("\n\n");

	printf("Vetor x zerado\n");
	double vetor_x[tamanho];
	for(int l = 0; l < tamanho; l++){
		vetor_x[l] = 0.0;
		printf("%.3f ", vetor_x[l]);
	}
	printf("\n\n");

	int j;
	for(int k = 0; k  < 86; k++){
		//printf("\nk = %d ", k);
		for(i = 1; i <= tamanho; i++){
			/*for(int l = 0; l < tamanho; l++){
				printf("%lf ", vetor_x[l]);
			}
			printf("\n");*/
			vetor_x[i-1] = (vetor_b[i-1]/get_matriz(matriz,i,i));
			for(int j = 1; j <= tamanho; j++){
				//printf("j = %d %.3f ", j, vetor_x[j-i]);
				if(i!= j){
					vetor_x[i-1] -= (get_matriz(matriz, i, j)*vetor_x[j-1]/get_matriz(matriz,i,i));
				}
			}
			//printf("\n\ni = %d -> %.6f  ", i, vetor_x[i-1]);
		}
		//printf("\nVetor x final\n");
		for(int l = 0; l < tamanho; l++){
		printf("%.2lf ", vetor_x[l]);
		}
	}

	printf("\n");
}