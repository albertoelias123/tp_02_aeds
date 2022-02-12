#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *arquivoDeEntrada;
/* Funcao que retorna verdadeiro se
 * `num' nao contem algarismos repetidos
 * e zero caso contrario. */

void lerArquivo()
{
    char numeroArquivoDeEntrada[5];
    printf("Digite o numero do arquivo de entrada: ");
    scanf("%s", &numeroArquivoDeEntrada);

    char nomeArquivoDeEntrada[100] = "./entradas/";
    char extensaoArquivo[10] = ".txt";

    strcat(nomeArquivoDeEntrada, numeroArquivoDeEntrada);
    strcat(nomeArquivoDeEntrada, extensaoArquivo);

    if ((arquivoDeEntrada = fopen(nomeArquivoDeEntrada, "r")) == NULL)
    {
        printf("Arquivo nao encontrado!");
        return -1;
    }
    
}
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
void imprimirDados(int quantidadeCidade, int *cidades, int capacidadeCaminhao, int quantidadeCaminhao, int *demandaCidades, int (*distanciaEntreCidades)[quantidadeCidade])
{
    int i, j;

    printf("\n\n\nInformacoes obtidas do arquivo:\n");
    printf("\tQuantidade Cidades: %d\n", quantidadeCidade);
    printf("\n\tVetor de Cidades:\n\t\t");

    for(int i = 0; i < quantidadeCidade - 1; i++){
        printf("%d ", cidades[i]);
    }
    printf("\n\tCapacidade de cada caminhao: %d\n", capacidadeCaminhao);
    printf("\tQuantidade de Caminhao: %d", quantidadeCaminhao);
    printf("\tDemanda das Cidades: ");
    for(int i = 0; i < quantidadeCidade; i++)
    {
        printf("%d ", demandaCidades[i]);
    }
        
    printf("\n\tMatriz de distancia entre as cidades:");
    for(int i = 0; i < quantidadeCidade; i++){
        printf("\n\t\t");
        for(int j = 0; j < quantidadeCidade; j++){
            printf("%-3d ", distanciaEntreCidades[i][j]);
        }
    }
}

int main() {
    printf("TP 02\n");

    lerArquivo();

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
    // if (quantidadeCidade % 2 != 0){
    //     quantidadeCidadePermuta = quantidadeCidade - 2;
    // }
    // else{
    //     quantidadeCidadePermuta = quantidadeCidade - 1;
    // }
    quantidadeCidadePermuta = quantidadeCidade - 1;
    /*
     * Aloca um vetor para representar as cidades permutadas
     */
    cidadesPermutadas = (int *)calloc(quantidadeCidadePermuta, sizeof(int)) ;
    if (cidadesPermutadas == NULL ) {
        perror("malloc") ;
        return -1;
    }
   
    // printf("\ncidadesPermutadas[0]: %d\n", cidadesPermutadas[0]);
    // printf("\ncidadesPermutadas[1]: %d\n", cidadesPermutadas[1]);
    // printf("\ncidadesPermutadas[2]: %d\n", cidadesPermutadas[2]);
    // printf("\ncidadesPermutadas[3]: %d\n", cidadesPermutadas[3]);
    // printf("\ncidadesPermutadas[%d]: %d\n", quantidadeCidadePermuta,cidadesPermutadas[quantidadeCidadePermuta]);
    // printf("\n================== ignora esse\n");
    /* Inicio do algoritmo. */
    int qntdPermutacao;
    int n = quantidadeCidade - 1;
    int aux = 0;
    int menor2 = 0;
    int menor = 0;
    int armzPosicaoMenor;
    int linha, col;
    int a;
    int armzCidadeVetor[quantidadeCidade];

    for (qntdPermutacao = 1; n > 1; n = n - 1)
    {
        qntdPermutacao = qntdPermutacao * n;
    }
    int armzCidades[qntdPermutacao][quantidadeCidade];

    // for (linha = 0; linha < qntdPermutacao; linha++)
    // {
    //     for (col = 0; col < quantidadeCidade - 1; col++)
    //     {

    //         armzCidades[linha][col] = -1;
    //     }
    // }

    int armazenaDistanciaPercorritaTotal[qntdPermutacao];
    while (cidadesPermutadas[quantidadeCidadePermuta] == 0 ) {
        for(iPermuta=0; iPermuta < quantidadeCidadePermuta; iPermuta++) {
            /* Mostra a permutacao na tela se
             * e somente se `cidadesPermutadas' nao contem
             * algarismos repetidos. */
            if ( eh_sem_repeticao(cidadesPermutadas, quantidadeCidadePermuta) ) {
               
                int distanciaPercorrida = 0;
                int cidadeAnterior = 0;
                int armzVetor[qntdPermutacao];
                

                /*printf("(C[0] D[0] T[0]) ");*/
                // printf("0 ");
                for(jPermuta=0; jPermuta < quantidadeCidadePermuta; jPermuta++) {
                    distanciaPercorrida += distanciaEntreCidades[cidadeAnterior][cidades[cidadesPermutadas[jPermuta]]];
                    
                    /*printf("(C[%d] D[%d] T[%d]) ",
                           cidades[cidadesPermutadas[jPermuta]],
                           distanciaEntreCidades[cidadeAnterior][cidades[cidadesPermutadas[jPermuta]]],
                           distanciaPercorrida) ;*/
                    // printf("%d ", cidades[cidadesPermutadas[jPermuta]]); 

                    cidadeAnterior = cidades[cidadesPermutadas[jPermuta]];
                    armzCidadeVetor[aux] = cidadeAnterior;
                    armzCidades[aux][jPermuta] = cidades[cidadesPermutadas[jPermuta]];


                    /*
                        0   1  2  3
                    0  p1  p2  p3 dT
                    1
                    2
                    3
                    4
                    5
                    */

                    // printf("\n matriz[%d][%d] = %d ", iPermuta, jPermuta, matriz[iPermuta][jPermuta]);
                    // printf("[%d] = %d ", jPermuta, cidadeAnterior);
                   
                }
                distanciaPercorrida += distanciaEntreCidades[cidadeAnterior][0];
                armzCidades[aux][3] = distanciaPercorrida;

                /*printf("(C[0] D[%d] T[%d]) ",
                       distanciaEntreCidades[cidadeAnterior][0],
                       distanciaPercorrida) ;*/
                int teste;
                armazenaDistanciaPercorritaTotal[aux] = distanciaPercorrida;

                if(aux == 0){
                    menor = armazenaDistanciaPercorritaTotal[aux];
                }
                else if(armazenaDistanciaPercorritaTotal[aux] < menor){
                    menor = armazenaDistanciaPercorritaTotal[aux];
                    armzPosicaoMenor = aux;
                }
                // printf("\nMenor: %d", menor);
                // printf("\nDistancia percorrida total pelo array: %d", armazenaDistanciaPercorritaTotal[aux]);
                // printf("0");
                // printf("\nArmazena Cidades: %d", armzCidades[aux]);
                // printf("\tDistancia Percorrida Total = %d\n", distanciaPercorrida);
                aux++;
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
    int x;
    int armazenaLinhaMenorDistancia;
    int vetorAux[quantidadeCidade - 1];

    int tamanhoArrayFinal = quantidadeCaminhao + quantidadeCidade;
    int array[tamanhoArrayFinal];
    array[0] = 0;
    array[tamanhoArrayFinal - 1] = 0;


    for (linha = 0; linha < qntdPermutacao; linha++)
    {
        for (col = 0; col < quantidadeCidade; col++)
        {
            if ((armzCidades[linha][quantidadeCidade - 1] == menor))
            {
                armazenaLinhaMenorDistancia = linha;
            }
        }
    }

    int p;
    for (linha = 0; linha < qntdPermutacao; linha++)
    {
        for (col = 0; col < quantidadeCidade; col++)
        {
            vetorAux[col] = armzCidades[armazenaLinhaMenorDistancia][col];
        }
    }
    int somaCarga = 0;
    int count = 0;
    printf("\n ==Saida== \n");
    printf("\nS = ");
    for (x = 1; x <= tamanhoArrayFinal; x++)
    {
        if ( somaCarga + demandaCidades[vetorAux[count]] <= capacidadeCaminhao){
            somaCarga += demandaCidades[vetorAux[count]];
            array[x] = vetorAux[count];
            count++;
        }
        else{
            somaCarga = 0;
            array[x] = 0;
        }
        printf("%d ", array[x-1]);
    }
    printf("\n\n");
    printf("\n ==Petalas== \n");
    for (x = 0; x < tamanhoArrayFinal; x++){
        if( (x > 0) && (array[x] != 0)){
            printf("%d ", array[x]);
        }
        else if(x==0){
            printf("0 ");
        }
        else if( (x!=0) && (array[x] == 0)){
            printf("%d\n", array[x]);
            printf("0 ");
        }
    }

        // int vetorcu[3] = { 1, 3, 2 };
    //     int demandaAux;
    // int *vetorSaida = malloc(quantidadeCidade * sizeof(int));
    // int *vetorSaida = realloc(vetorSaida, quantidadeCidade);

    // printf("\nCapacidade Caminhao: %d\n", capacidadeCaminhao);
     
    // for (p = 0; p < quantidadeCidade; p++)
    // {
    //     if (demandaCidades[vetorAux[p]] <= capacidadeCaminhao){
    //         demandaAux = capacidadeCaminhao - demandaCidades[vetorAux[p]]; //demanda - 2 = sobra 4

    //     }
    //     printf("%d\n", demandaCidades[vetorAux[p]]);
    // }
    //  for (p = 0; p < quantidadeCidade; p++)
    // {
    //     printf("\n Demanda[%d]: %d", p,demandaCidades[p]);
    // }


    // printf("\nQuantidade de caminhoes: %d\n", quantidadeCaminhao);
    // for (p = 0; p < quantidadeCidade - 1; p++){
    //     printf(" %d", vetorAux[p]);
    // }


    // printf("\narmazenaLinha = %d\n", armazenaLinhaMenorDistancia);
    // for (linha = 0; linha < qntdPermutacao; linha++)
    // {
    //     for (col = 0; col < quantidadeCidade;  col++)
    //     {
    //         printf("%-3d", armzCidades[linha][col]);
    //     }
    //     printf("\n\n");
    // }
  

    // printf("\nQuantidade de permutacoes: %d", qntdPermutacao);
    // printf("\nMenor: %d",  menor);
    // int k;
    // for (k = 0; k < qntdPermutacao; k++){
    //     printf("\nDistancia percorrida total pelo array[%d]: %d", k, armazenaDistanciaPercorritaTotal[k]);
    // }
    
    free(cidadesPermutadas);

    // imprimirDados(quantidadeCidade, cidades, capacidadeCaminhao, quantidadeCaminhao, demandaCidades, distanciaEntreCidades);
   
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