#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAM 29
#define RANK_MESTRE 0
#define TAG_OPERACOES 50


int main(int argc, char** argv){
    int primos[TAM] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 26, 28, 29, 30};
    int x;

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

    int response[TAM];
    
    //Condição para identifica o processo do mestre
    if(rank_processo == RANK_MESTRE){
        int x;

        

        //Para enviar a operação para os escravos
        for(x = 1; x < num_processo; x++){
            if(x == 1){
                MPI_Send(primos, TAM, MPI_INT, x, TAG_OPERACOES, MPI_COMM_WORLD);
            }
        }
        printf("Processo mestre executando em: %s \n", nome_processo);

        //Para receber o resultado processado de cada um dos escravos
        for(x = 1; x < num_processo; x++){
            MPI_Recv(response, TAM, MPI_INT, x, TAG_OPERACOES, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for(int y = 0; y < TAM; y++){
                printf("Resultado: %d \n", response[y]);
            }
        }
    }
    else{
        MPI_Recv(response, TAM, MPI_INT, RANK_MESTRE, TAG_OPERACOES, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(int x = 0; x < TAM; x++){
            printf("Processo escravo %d executando em %s e recebeu %d \n", rank_processo, nome_processo, primos[x]);
        }

        // Escravo 1 calcula o primeiro bloco
        if(rank_processo == 1){
            response[0] = 1;
            for(int x = 2; x < 9; x++){
                if(primos[x] % x == 0){
                    response[x] = primos[x];
                    printf("\nRESPONSE 1: %d\n\n", response[x]);
                }
            }
        }

        //Escravo 2 calcula o segundo bloco
        else if(rank_processo == 2){
            response[0] = 2;
            for(int x = 10; x < 19; x++){
                if(primos[x] % x == 0){
                    response[x] = primos[x];
                    printf("\nRESPONSE 2: %d\n\n", response[x]);
                }
            }
        }

        //Escravo 3 calcula o terceiro bloco
        else if(rank_processo == 2){
            response[0] = 3;
            
            for(int x = 20; x < 29; x++){
                if(primos[x] % x == 0){
                    response[x] = primos[x];
                    printf("\nRESPONSE 3: %d\n\n", response[x]);
                }
            }
        }
        MPI_Send(&response, TAM, MPI_INT, RANK_MESTRE, TAG_OPERACOES, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}