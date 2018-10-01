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

double modulo(double numero){
	if(numero < 0){
		numero = numero * (- 1);
	}
	return numero;
}

int main(){

	int tamanho = 100;
	int itmax = 2*tamanho;
	int i;
	double e = 0.0000000001;
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
	//printf("Vetor b\n");
	for(int j = 1; j <= tamanho; j++){
		vetor_b[j-1] = 0;
		for(int m = 1; m <= tamanho; m++){
			vetor_b[j-1] += get_matriz(matriz,j,m);
		}
		//printf("%.3f ", vetor_b[j-1]);
	}
	//printf("\n\n");

	//printf("Vetor x zerado\n");
	double vetor_x[tamanho];
	for(int l = 0; l < tamanho; l++){
		vetor_x[l] = 0.0;
		//printf("%.3f ", vetor_x[l]);
	}
	//printf("\n\n");

	int j;
	int k = 0;
	double erro = 10;
	double vetor_aux[tamanho];
	double auxiliar1;
	double auxiliar2;

	while((k < itmax) && (erro > e)){
		for(int p = 0; p < tamanho; p++){
			vetor_aux[p] = vetor_x[p];
		}
		for(i = 1; i <= tamanho; i++){
			vetor_x[i-1] = (vetor_b[i-1]/get_matriz(matriz,i,i));
			for(int j = 1; j <= tamanho; j++){
				if(i!= j){
					vetor_x[i-1] -= (get_matriz(matriz, i, j)*vetor_x[j-1]/get_matriz(matriz,i,i));
				}
			}
		}
		auxiliar2 = vetor_aux[0];
		auxiliar1 = vetor_x[0];
		for(int r = 0; r < tamanho; r++){
			if(modulo(vetor_aux[r]) > auxiliar2){
				auxiliar2 = modulo(vetor_aux[r]);
			}
			if(modulo(vetor_x[r]) > auxiliar1){
				auxiliar1 = modulo(vetor_x[r]);
			}
		}
		erro = auxiliar1 - auxiliar2;
		k++;
	}

	printf("Erro final: %.10lf\n", erro);
	printf("Vetor final: \n\n");
	for(int l = 0; l < tamanho; l++){
		printf("%.2lf ", vetor_x[l]);
	}
	printf("\n");
}