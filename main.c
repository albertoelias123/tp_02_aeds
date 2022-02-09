#include <stdio.h>
#include <string.h>

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
    }else{
        printf("Arquivo encontrado!\n");
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

        int quantidadeCaminhao = somatorioDemandaCidades / capacidadeCaminhao;

        int distanciaEntreCidades[quantidadeCidade][quantidadeCidade];
        for(int i = 0; i < quantidadeCidade * quantidadeCidade; i++){
            int posI, posJ, val;
            fscanf (arquivoDeEntrada, "%d %d %d", &posI, &posJ, &val);
            distanciaEntreCidades[posI][posJ] = val;
        }




        // Print Arquivo
        printf("Informacoes obtidas do arquivo:\n");
        printf("\tQuantidade Cidades: %d\n", quantidadeCidade);
        printf("\tCapacidade de cada caminhao: %d\n", capacidadeCaminhao);
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
    }
    return 0;
}

/*
 * Entradas:
 * N -> Quantidade de cidades
 * Qv -> Capacidade suportada pelos caminhões
 * Qn -> Demanda de cada cidade (N entradas na msm linha)
 * i j Dij -> Distância cidade I para J
 */