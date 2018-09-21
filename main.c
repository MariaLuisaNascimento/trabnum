#include <stdio.h>
#include <stdlib.h>
#include "matriz_esparsa.h"

int main()
{
    int aux;
    MATRIZ_ESPARSA *matriz;
	MATRIZ_ESPARSA *matriz1;
	MATRIZ_ESPARSA *soma;
	MATRIZ_ESPARSA *transposta;
	MATRIZ_ESPARSA *produto;
/*	 printf("\n           MATRIZES ESPARSAS \n\n");

    printf("[0] Sair \n");
    printf("[1] Criar matriz \n");

    printf("\nO que deseja fazer? ");
    scanf("%d", &aux);

    if(aux == 1)
    {
        printf("\n[1] Criando matriz\n");
        int l, c;
        printf("Numero de linhas:"); scanf("%d", &l);
        printf("Numero de colunas:"); scanf("%d", &c);
        matriz=criar_matriz(l,c);
        printf("Matriz criada com sucesso\n\n");
    }
    else return 0;
    
    printf("         Possiveis operacoes \n");
    printf("[0] Sair \n");
    printf("[1] Inserir celula na matriz \n");
    printf("[2] Buscar elemento na matriz \n");
    printf("[3] Imprimir matriz \n");
    printf("[4] Apagar matriz \n");
    printf("[4] Criar matriz \n");
	 printf("[5] Inserir celula na m1 \n");
	 printf("[6] Imprimir m1 \n");
	 printf("[6] \n");
    printf("[7] \n");
    printf("[8] \n");

    while(1)
    {
        printf("\nPromixa acao? ");
        scanf("%d", &aux);

        switch (aux)
        {
            case 0: 
                return 0;
            break;

            case 1:
            {
                printf("\n[1] Inserindo celula na matriz\n");
                int l, c;
                double v;
                printf("Linha da celula:"); scanf("%d", &l);
                printf("Coluna da celula:"); scanf("%d", &c);
                printf("Valor da celula:"); scanf("%lf", &v);
                
                if(set_matriz(matriz,l,c,v)) printf("Celula inserida com sucesso\n\n");
                else ("Erro na insercao da celula\n\n");
            }
            break;

            case 2:
            {
                printf("\n[2] Buscando elemento na matriz\n");
                int l, c;
                double v;
                printf("Linha da celula:"); scanf("%d", &l);
                printf("Coluna da celula:"); scanf("%d", &c);
        
                v = get_matriz(matriz,l,c);
                printf("Valor da celula: %lf\n\n", v);
            }
            break;

            case 3: 
                printf("\n[3] Imprimindo matriz\n");
                print_matriz(matriz);
            break;
		case 4:
		{
        printf("\n[1] Criando matriz\n");
        int l, c;
        printf("Numero de linhas:"); scanf("%d", &l);
        printf("Numero de colunas:"); scanf("%d", &c);
        matriz1 =criar_matriz(l,c);
        printf("Matriz criada com sucesso\n\n");
		}
		break;
		  case 5:
            {
                printf("\n[1] Inserindo celula na matriz\n");
                int l, c;
                double v;
                printf("Linha da celula:"); scanf("%d", &l);
                printf("Coluna da celula:"); scanf("%d", &c);
                printf("Valor da celula:"); scanf("%lf", &v);
                
                if(set_matriz(matriz1,l,c,v)) printf("Celula inserida com sucesso\n\n");
                else ("Erro na insercao da celula\n\n");
            }
            break;
			 case 6: 
                printf("\n[3] Imprimindo matriz\n");
                print_matriz(matriz1);
            break;
			 case 7: 
                printf("\n[7] Somando matriz\n");
                soma = somar_matriz(matriz, matriz1);
                print_matriz(soma);
            break;
    		}
    }
}*/



matriz=criar_matriz(2,2);
set_matriz(matriz,1,1,5);
set_matriz(matriz,1,2,1);
set_matriz(matriz,2,1,3);
set_matriz(matriz,2,2,2);
//set_matriz(matriz,4,5,6);
//set_matriz(matriz,2,3,6);
//set_matriz(matriz,3,4,6);

printf("Matriz\n");
print_matriz(matriz);
printf("\n");
matriz1=criar_matriz(2,2);
set_matriz(matriz1,1,1,0);
set_matriz(matriz1,1,2,5);
set_matriz(matriz1,2,1,1);
set_matriz(matriz1,2,2,6);
/*set_matriz(matriz1,2,1,2);
set_matriz(matriz1,2,2,-1);
set_matriz(matriz1,2,3,4);
set_matriz(matriz1,2,4,-3);*/
//set_matriz(matriz,4,5,6);
//set_matriz(matriz,2,3,6);
//set_matriz(matriz,3,4,6);

printf("Matriz\n");
print_matriz(matriz1);
/*printf("\n");
matriz1=criar_matriz(2,2);
set_matriz(matriz1,2,2,6);
print_matriz(matriz1);*/

/*printf("Soma\n");
soma = somar_matriz(matriz, matriz1);
print_matriz(soma);*/

printf("Transposta\n");
transposta = transposta_matriz(matriz1);
print_matriz(transposta);

printf("Produto\n");
produto = multiplicar_matriz(matriz, matriz1);
print_matriz(produto);


}

