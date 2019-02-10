#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int testeprimos(int n, int rank, int numprocessos)
{
    int max = (int) ceil(sqrt(n));//O maior divisor possivel é a raiz quadrada de n
    int min;
    int localmax;
    if(max%numprocessos == 0)//se o maximo for divisivel exatamente por numprocessos
    {
        min = (max/numprocessos)*rank + 1;
        localmax = (max/numprocessos)*(rank+1);
    }
    else//senão adiciona o resto que falta ao ultimo processo
    {
        min = (max/numprocessos)*rank + 1;
        if(rank == numprocessos -1) localmax = (max/numprocessos)*(rank+1)+max%numprocessos;
        else localmax = (max/numprocessos)*(rank+1);
    }
    if(min < 2) min = 2;
    

    for(int i = min; i<=localmax;i++)
    {
        if(n%i==0) return 1;
    }
    return 0;
}


int main(int argc, char** argv)
{
    MPI_Init(NULL,NULL);
    int n = 0;
    int numprocs, myid, resultado_escravos, result = 0;
    MPI_Comm_rank (MPI_COMM_WORLD, &myid);
    MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
    if(myid == 0)
    {
        printf("Entre com o número inicial para encontrar o proximo primo: ");
        fflush(stdout);
        scanf("%d", &n);
        fflush(stdout);
        while(1)
        {

            for(int i=1;i<numprocs;i++)
            {
                MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);//envia o n para os slaves
            }
            for(int i=1; i<numprocs;i++)
            {
                MPI_Recv(&resultado_escravos, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);//recebe o resultado dos slaves
                result += resultado_escravos;
            }
            if(result == 0)//se a soma result for zero o numero é primo
            {
                printf("O número primo mais próximo é: %d\n", n);
                for(int i=1;i<numprocs;i++)
                {
                    MPI_Send(&result, 1, MPI_INT, i, 0, MPI_COMM_WORLD);//envia result que é 0 para os slaves pararem o trabalho
                }
                break;
            }
            else result = 0;//caso contrario zerar result e adicionar 1 ou 2 dependendo se o numero é impar ou par
            if(n%2 == 0) n += 1;
            else n += 2;
        }
    }
    else
    {
        MPI_Recv(&n,1,MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);//recebe o primeiro n do master
        do 
        {
            resultado_escravos = testeprimos(n, myid-1, numprocs-1);//Diminuindo um rank e um processo para a range calculada ficar correta
            MPI_Send(&resultado_escravos, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);//Envia o resultado para o mestre
            MPI_Recv(&n,1,MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);//Recebe  o próximo n
        }   while(n != 0);
        
    }

    MPI_Finalize();
    return 0;
}