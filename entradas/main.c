#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funcao que retorna verdadeiro se
 * `num' nao contem algarismos repetidos
 * e zero caso contrario. */
char eh_sem_repeticao(int *num, int n) {
    int i, j ;

    for(i=0; i < n; i++) {
        for(j=0; j < n && i != j; j++) {
            if(num[i] == num[j]) {
                return 0;
            }
        }
    }

    return 1 ;
}

int main() {
    printf("TP 02\n");
    printf("Digite o numero do arquivo de entrada: ");
    char numeroArquivoDeEntrada[5];
    scanf("%s", &numeroArquivoDeEntrada);
    char nomeArquivoDeEntrada[100] = "../entradas/";
    char extensaoArquivo[10] = ".txt";
    strcat(nomeArquivoDeEntrada, numeroArquivoDeEntrada);
    strcat(nomeArquivoDeEntrada, extensaoArquivo);

    FILE * arquivoDeEntrada;
    if ((arquivoDeEntrada = fopen (nomeArquivoDeEntrada, "r")) == NULL){
        printf("Arquivo nao encontrado!");
        return -1;
    }

    int quantidadeCidade;
    int capacidadeCaminhao;

    fscanf (arquivoDeEntrada, "%d", &quantidadeCidade);
    fscanf (arquivoDeEntrada, "%d", &capacidadeCaminhao);

    int demandaCidades[quantidadeCidade];
    int somatorioDemandaCidades = 0;
    for(int i = 0; i < quantidadeCidade; i++){
        fscanf (arquivoDeEntrada, "%d", &demandaCidades[i]);
        somatorioDemandaCidades += demandaCidades[i];
    }

    int cidades[quantidadeCidade - 1];
    for(int i = 0; i < quantidadeCidade -1; i++) {
        cidades[i] = i+1;
    }

    int quantidadeCaminhao = somatorioDemandaCidades / capacidadeCaminhao;

    int distanciaEntreCidades[quantidadeCidade][quantidadeCidade];
    for(int i = 0; i < quantidadeCidade * quantidadeCidade; i++){
        int posI, posJ, val;
        fscanf (arquivoDeEntrada, "%d %d %d", &posI, &posJ, &val);
        distanciaEntreCidades[posI][posJ] = val;
    }


    int *cidadesPermutadas; /* cidades que representara cada permutacao. */
    int quantidadeCidadePermuta; /* quantidade de elementos do cidades. */
    int iPermuta, jPermuta; /* controle de loop. */

    // Desconsiderar a cidade 0, pois ela é o deposito
    quantidadeCidadePermuta = quantidadeCidade - 1;

    /*
     * Aloca um vetor para representar as cidades permutadas
     */
    cidadesPermutadas = (int *)calloc(quantidadeCidadePermuta, sizeof(int)) ;
    if (cidadesPermutadas == NULL ) {
        perror("malloc") ;
        return -1;
    }

    /* Inicio do algoritmo. */
    while (cidadesPermutadas[quantidadeCidadePermuta] == 0 ) {
        for(iPermuta=0; iPermuta < quantidadeCidadePermuta; iPermuta++) {
            /* Mostra a permutacao na tela se
             * e somente se `cidadesPermutadas' nao contem
             * algarismos repetidos. */
            if ( eh_sem_repeticao(cidadesPermutadas, quantidadeCidadePermuta) ) {
                int distanciaPercorrida = 0;
                int cidadeAnterior = 0;
                /*printf("(C[0] D[0] T[0]) ");*/
                printf("0 ");
                for(jPermuta=0; jPermuta < quantidadeCidadePermuta; jPermuta++) {
                    distanciaPercorrida += distanciaEntreCidades[cidadeAnterior][cidades[cidadesPermutadas[jPermuta]]];

                    /*printf("(C[%d] D[%d] T[%d]) ",
                           cidades[cidadesPermutadas[jPermuta]],
                           distanciaEntreCidades[cidadeAnterior][cidades[cidadesPermutadas[jPermuta]]],
                           distanciaPercorrida) ;*/
                    printf("%d ", cidades[cidadesPermutadas[jPermuta]]);
                    cidadeAnterior = cidades[cidadesPermutadas[jPermuta]];
                }
                distanciaPercorrida += distanciaEntreCidades[cidadeAnterior][0];
                /*printf("(C[0] D[%d] T[%d]) ",
                       distanciaEntreCidades[cidadeAnterior][0],
                       distanciaPercorrida) ;*/
                printf("0");
                printf("\tDistancia Percorrida Total = %d\n", distanciaPercorrida);
            }

            /* incrementa o algarismo menos
             * significativo. */
            cidadesPermutadas[0]++ ;
        }

        /* distribui os vai-uns. */
        for(iPermuta=0; iPermuta < quantidadeCidadePermuta; iPermuta++) {
            if(cidadesPermutadas[iPermuta] == quantidadeCidadePermuta) {
                cidadesPermutadas[iPermuta] = 0;
                cidadesPermutadas[iPermuta + 1]++ ;
            }
        }
    }

    free(cidadesPermutadas) ;



    // Print Arquivo
    printf("\n\n\nInformacoes obtidas do arquivo:\n");
    printf("\tQuantidade Cidades: %d\n", quantidadeCidade);
    printf("\n\tVetor de Cidades:\n\t\t");
    for(int i = 0; i < quantidadeCidade - 1; i++)
        printf("%d ", cidades[i]);
    printf("\n\tCapacidade de cada caminhao: %d\n", capacidadeCaminhao);
    printf("\tQuantidade de Caminhao: %d", quantidadeCaminhao);
    printf("\tDemanda das Cidades: ");
    for(int i = 0; i < quantidadeCidade; i++)
        printf("%d ", demandaCidades[i]);
    printf("\n\tMatriz de distancia entre as cidades:");
    for(int i = 0; i < quantidadeCidade; i++){
        printf("\n\t\t");
        for(int j = 0; j < quantidadeCidade; j++)
            printf("%-3d ", distanciaEntreCidades[i][j]);
    }

    fclose(arquivoDeEntrada);
    return 0;
}

/*
 * Entradas:
 * N -> Quantidade de cidades
 * Qv -> Capacidade suportada pelos caminhões
 * Qn -> Demanda de cada cidade (N entradas na msm linha)
 * i j Dij -> Distância cidade I para J
 */