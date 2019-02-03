#include <mpi.h>
#include <stdio.h>
#define MAX 10
#define RANK_MESTRE 0
#define TAG_OPERACOES 50


int main(int argc, char** argv){
    int vetor[9] = {1, 2, 3,4, 5, 6, 7, 8, 9};
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

    //Condição para identifica o processo do mestre
    if(rank_processo == RANK_MESTRE){
        int x;
        //Para enviar a operação para os escravos
        for(x = 1; x < num_processo; x++){

        }

        //Para receber o resultado processado de cada um dos escravos
        for(x = 1; x < num_processo; x++){

        }
    }
    else{

    }

    selectionSort(vetor);
    MPI_Finalize();
}


void selectionSort(vetor){
    for (int x = 0; x < MAX; x++){
        int menor = vetor[x];
        for (int y = x+1; y < MAX; y++){
            if (vetor[y] < menor){
                int aux =  menor;
                menor = vetor[y];
                vetor[y] = aux;
            }
        }
        vetor[x]=menor;
    }
    printar();
};