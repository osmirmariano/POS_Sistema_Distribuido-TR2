#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAM 92
#define RANK_MESTRE 0
#define TAG_OPERACOES 50


int main(int argc, char** argv){
    int *primos;
    //Inicialização do MPI
    MPI_Init(NULL, NULL);
    //Obter o número de processo
    int num_processo;
	MPI_Comm_size(MPI_COMM_WORLD, &num_processo);

    //Obter o rank do processo
	int rank_processo;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank_processo);

	//Obter o nome do processo
	int tam_processo;
	char nome_processo[MPI_MAX_PROCESSOR_NAME];
	MPI_Get_processor_name(nome_processo, &tam_processo);

    primos = malloc(TAM*sizeof(int));
    int x;
    for(x = 2; x < TAM; x++){
        primos[x] = x;
    }
    int response[TAM];
    //Condição para identifica o processo do mestre
    if(rank_processo == RANK_MESTRE){
        printf("MESTRE\n");
        int x;
        //Para enviar a operação para os escravos
        for(x = 1; x < num_processo; x++){

            MPI_Send(primos, 90, MPI_INT, x, TAG_OPERACOES, MPI_COMM_WORLD);
        }
        printf("Processo mestre executando: %s \n", nome_processo);

        //Para receber o resultado processado de cada um dos escravos
        for(x = 1; x < num_processo; x++){
            MPI_Recv(&primos, 30, MPI_INT, x, TAG_OPERACOES, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for(int y = 0; y < 30; y++){
                printf("Resultado: %d \n", response[y]);
            }
        }
    }
    else{
        printf("ESCRAVOS\n");
        MPI_Recv(&primos, 30, MPI_INT, x, TAG_OPERACOES, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(int x = 0; x < 30; x++){
            printf("Processo escravo %d executando em %s e %d. \n", rank_processo, nome_processo, primos[x]);
        }

        // Escravo 1 calcula o primeiro bloco
        if(rank_processo == 1){
            response[0] = 1;
            for(int x = 0; x < 30; x++){
                if(primos[x] % x == 0){
                    response[x] = primos[x];
                }
            }
        }

        //Escravo 2 calcula o segundo bloco
        else if(rank_processo == 2){
            response[0] = 2;
            for(int x = 0; x < 30; x++){
                if(primos[x] % x == 0){
                    response[x] = primos[x];
                }
            }
        }

        //Escravo 3 calcula o terceiro bloco
        else if(rank_processo == 2){
            response[0] = 3;
            for(int x = 0; x < 30; x++){
                if(primos[x] % x == 0){
                    response[x] = primos[x];
                }
            }
        }
    }

    MPI_Finalize();
}