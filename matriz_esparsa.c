#include <stdio.h>
#include <stdlib.h>
#include "matriz_esparsa.h"

struct celula{
    // "coordenadas" da célula (linha e coluna da matriz)
    int linha;
    int coluna;

    // valor armazenado na célula
    float valor;

    // ponteiros para as céulas a direita e a abaixo
    CELULA *cel_direita; 
    CELULA *cel_abaixo;
};

struct matriz_esparsa {
    // ponteiros para os vetores de ponteiros de celulas
    CELULA **linha;
    CELULA **coluna;
    
    // número de linhas e colunas
    int nL;
    int nC;
};

MATRIZ_ESPARSA *criar_matriz (int n_linhas, int n_colunas){
    MATRIZ_ESPARSA *matriz_criada = (MATRIZ_ESPARSA *) malloc(sizeof(MATRIZ_ESPARSA));

    matriz_criada->nL = n_linhas;
    matriz_criada->nC = n_colunas;
    matriz_criada->linha = (CELULA **) malloc ( (sizeof (CELULA *)) * n_linhas); // array de ponteiros para célula para as linhas
    matriz_criada->coluna = (CELULA **) malloc ( (sizeof (CELULA *)) * n_colunas); // array de ponteiros para célula para as colunas

    int aux;
    for (aux=0; aux < n_linhas; aux++){
        matriz_criada->linha[aux] = (CELULA *) malloc (sizeof(CELULA));
        matriz_criada->linha[aux]->cel_direita = NULL;
    }for (aux=0; aux < n_colunas; aux++){
        matriz_criada->coluna[aux] = (CELULA *) malloc (sizeof(CELULA));
        matriz_criada->coluna[aux]->cel_abaixo = NULL;
    }

    return matriz_criada;
}

int set_matriz (MATRIZ_ESPARSA *matriz, int linha_set, int coluna_set, double valor_set){
    // Matrizes em C consideram o 0 como a primeira linha e coluna, mas para melhor interpretação do usuário, a linha e a coluna começarão em 1
    --linha_set;
    --coluna_set;

    if ( (linha_set < matriz->nL) && (linha_set >= 0) && (coluna_set < matriz->nC) && (coluna_set >=0) ){ // Verifica se a posição dada não é inválida
    
        // Celula a ser inserida
        CELULA *celula_set = (CELULA *) malloc (sizeof(CELULA));
        celula_set->linha=linha_set;
        celula_set->coluna=coluna_set;
        celula_set->valor=valor_set;

        CELULA *p_aux = matriz->linha[linha_set]; // ponteiro auxiliar para manipulação da matriz
        while ( (p_aux->cel_direita != NULL) && (p_aux->cel_direita->coluna < coluna_set) ){
            p_aux = p_aux->cel_direita; // se não estiver vazia, procura a posição onde a célula deve ser inserida                
        }if (p_aux->cel_direita == NULL){
            celula_set->cel_direita = NULL; 
            p_aux->cel_direita = celula_set;
        }else{
            celula_set->cel_direita = p_aux->cel_direita; 
            p_aux->cel_direita = celula_set;
        }
            

        p_aux = matriz->coluna[coluna_set];
        while ( (p_aux->cel_abaixo != NULL) && (p_aux->cel_abaixo->linha < linha_set) ){
            p_aux = p_aux->cel_abaixo; // se não estiver vazia, procura a posição onde a célula deve ser inserida                
        }if (p_aux->cel_abaixo == NULL){
            celula_set->cel_abaixo = NULL; 
            p_aux->cel_abaixo = celula_set;
        }else{
            celula_set->cel_abaixo = p_aux->cel_abaixo; 
            p_aux->cel_abaixo = celula_set;
        }

        return 1;
    }
    return 0;
}

double get_matriz(MATRIZ_ESPARSA *matriz, int linha_get, int coluna_get){
    --linha_get;
    --coluna_get;

    if ( (linha_get < matriz->nL) && (linha_get >= 0) && (coluna_get < matriz->nC) && (coluna_get >=0) ){ // Verifica se a posição dada não é inválida
        CELULA *celula_get = matriz->linha[linha_get]; // ponteiro auxiliar que recebe o endereço do nó cabeça

        while ( celula_get->cel_direita != NULL && celula_get->cel_direita->coluna <= coluna_get)
            celula_get = celula_get->cel_direita;

        if (celula_get->coluna == coluna_get)
            return celula_get->valor;        
    }
    return 0;
}

void print_matriz(MATRIZ_ESPARSA  *matriz){
    int i, j;
    for (j=1; j<=matriz->nL; j++){
        for (i=1; i<=matriz->nC; i++){
            printf("%.2lf  ", get_matriz(matriz,j,i));
        }
        printf("\n");
    }
}



MATRIZ_ESPARSA  *somar_matriz( MATRIZ_ESPARSA *m1,  MATRIZ_ESPARSA *m2){
	//condição para soma: matrizes com mesmo nº de linhas e colunas
	if (m1->nL == m2->nL && m1->nC == m2->nC){
		//cria uma matriz com mesmas dimensões das originais
		MATRIZ_ESPARSA *soma = criar_matriz( m1->nL, m2->nC);
		int i, j;
		for(j = 1; j <= m1 -> nL; j ++){
			for(i = 1; i <= m1->nC; i++){
				//caso um dos elementos for diferente de zero, ou se um não for o oposto do outro
				if(get_matriz(m1,j,i) != 0 || get_matriz(m2,j,i) != 0 || get_matriz(m1, j, i) != - get_matriz(m2,j,i)){
					//caso o elemento de m1 for zero, a soma será o elemtento de m2
					if(get_matriz(m1, j , i) == 0) set_matriz(soma, j, i, get_matriz(m2,j,i));
					//caso o elemento de m2 for zero a soma será o elemento de m1
					else if(get_matriz(m2, j , i) == 0) set_matriz(soma, j, i, get_matriz(m1,j,i));
					//caso nenhum dos elementos for zero, a soma é efetuada
					else set_matriz(soma, j, i, (get_matriz(m1,j,i) + get_matriz(m2,j,i)));
					
				}	
			}
		}
		//retorna a matriz soma
		return soma;
	}else return NULL;
}


MATRIZ_ESPARSA  * transposta_matriz(MATRIZ_ESPARSA  *matriz){
	//cria uma mtriz esparsa com nC(nº de colunas da original) linhas e nL colunas(nº de linhas da original)
	MATRIZ_ESPARSA *transposta = criar_matriz( matriz->nC, matriz->nL);
	 int i, j;
		//loops para passar por todos elementos da matriz original
	for (j=1; j<=matriz->nL; j++){
		//checa se a linha tem algum elemento (se não tiver, não precisa trocar os elementos, seria 0 por 0)
		if(matriz->linha[j-1] != NULL){
			for (i=1; i<=matriz->nC; i++){
				//coloca cada elemento de Mlc em Tcl
				set_matriz(transposta, i, j, get_matriz(matriz,j,i));
			}
		}
	}
	//retorna a matriz esparsa transposta
	return transposta;
}


MATRIZ_ESPARSA  *multiplicar_matriz( MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2){
	//condição para a multiplicação: matrizes com mesmo número de linhas e colunas
	if(m1->nC == m2->nL){
		//Faz a transposta de m2, para que possa multiplicar linha da primeira matriz por linha da tranposta da seugnda
		MATRIZ_ESPARSA *transpostam2 = transposta_matriz(m2);
		//Cria uma matriz com nº linhas igual ao da m1 e nº de colunas igual ao da m2
		MATRIZ_ESPARSA *produto = criar_matriz(m1->nL, m2->nC);
		int i, j, k;
		double aux = 0;
	    //percorre as linhas da m1
		for (j=1; j<=m1->nL; j++){
			//checa se as linhas de m1 tem algum elemento(se não tiver, o produto será zero e não é preciso realizar as operações)
			if(m1->linha[j-1] != NULL){
				//percorre as linhas da transpostam2
				for(k = 1; k<= transpostam2->nL; k++){
					//percorre as linhas de m1 e transpostam2
					for (i=1; i<=m1->nC; i++){
						//realiza a adição do produto das linhas
						aux += ((get_matriz(m1,j, i))*(get_matriz(transpostam2,k, i)));
					}
					//cria o elemento de linha i e coluna k
					if(aux != 0){
						set_matriz(produto, j, k, aux);
						aux = 0;
					}

				}
			}
		}
		//retorna a matriz produto		
		return produto;		
		
	}else return NULL;
}
		

MATRIZ_ESPARSA *ler_matriz(char name[20]){
    int x, y, i, j;
    double aux;
    FILE *file;
    file = fopen(name, "r"); 
    fscanf(file, "%d %d", &x, &y);
    printf("%d %d \n", x, y);
    MATRIZ_ESPARSA *matriz = criar_matriz (x, y);
    for(i = 0; i < x; i++){
        for (j = 0; j < y; j++){

            fscanf(file , " %lf ", &aux);
            printf("%d %d %lf \n", i, j, aux);            
            set_matriz ( matriz, (i+1), (j+1), aux);
        }
    }
            return matriz;
}

/*void resume_matriz(MATRIZ_ESPARSA *matriz){
    int i,j, k, aux;
    int x = matriz->nL;
    for(j = 0; j < x; j++){
        for(i = 0; i <matriz->nC; i++){
         aux = get_matriz(matriz, i+1, j+1);
            
          if (aux->valor != 0){
                   printf(" %d  ",aux);
          }
            
       }
    }
}*/







