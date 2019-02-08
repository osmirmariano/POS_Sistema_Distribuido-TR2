#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAM 3
#define RANK_MESTRE 0
#define TAG_OPERACOES 50


int main(int argc, char** argv){
    int primos[TAM] = {7, 5, 13};
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
            MPI_Send(&primos[x], TAM, MPI_INT, x, TAG_OPERACOES, MPI_COMM_WORLD);
        }
        printf("Processo mestre executando em: %s \n", nome_processo);

        //Para receber o resultado processado de cada um dos escravos
        for(x = 1; x < num_processo; x++){
            MPI_Recv(&response[0], TAM, MPI_INT, x, TAG_OPERACOES, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Resultado de %d: %d \n", response[0], response[1]);
        }
    }
    else{
        MPI_Recv(&primos, TAM, MPI_INT, RANK_MESTRE, TAG_OPERACOES, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processo escravo %d executando em %s recebeu %d \n", rank_processo, nome_processo, primos[0]);
        int contador = 0;
        // Escravo 1 calcula o primeiro bloco
        if(rank_processo == 1){
            response[0] = 1;
            // for(int y = 2; y <= primos[0]; y++){
                if(primos[0] % 2 == 0){
                    contador++;
                    // response[1] = primos[0];
                    // printf("\nRESPONSE PRIMO 1");
                    // response[x] = primos[x];
                }
                else{
                    response[1] = 0;
                }
            // }

            // if(contador == 2){
            //     response[1] = primos[0];
            //     printf("\nRESPONSE PRIMO 1: %d\n\n", response[1]);
            // }
            // else{
            //     response[1] = 0;
            // }
            
        }

        //Escravo 2 calcula o segundo bloco
        else if(rank_processo == 2){
            response[0] = 2;
            // for(int y = 2; y <= primos[1]; y++){
                printf("OI 2");
                if(primos[1] % 2 == 0){
                    contador++;
                    // response[x] = primos[x];
                    // response[1] = primos[1];
                    // printf("\nRESPONSE PRIMO 2");
                }
                else{
                    response[1] = 0;
                }
            // }

            // if(contador == 2){
            //     response[1] = primos[1];
            //     printf("\nRESPONSE PRIMO 2: %d\n\n", response[1]);
            // }
            // else{
            //     response[1] = 0;
            // }
        }

        //Escravo 3 calcula o terceiro bloco
        else if(rank_processo == 2){
            response[0] = 3;
            
            // for(int y = 2; y <= primos[2]; y++){
                if(primos[2] % 2 == 0){
                    response[1] = primos[2];
                    // printf("\nRESPONSE PRIMO 3");
                    // contador++;
                    // response[x] = primos[x];
                }
                else{
                    response[1] = 0;
                }

            // }

            // if(contador == 2){
            //     response[1] = primos[2];
            //     printf("\nRESPONSE PRIMO 3: %d\n\n", response[1]);
            // }
            // else{
            //     response[1] = 0;
            // }
        }
        MPI_Send(&response[0], TAM, MPI_INT, RANK_MESTRE, TAG_OPERACOES, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}