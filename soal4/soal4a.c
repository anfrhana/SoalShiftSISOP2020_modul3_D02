#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int matA[4][2] = {{1, 2}, 
		  {3, 4}, 
		  {1, 1},
		  {1, 6}};
int matB[2][5] = {{5, 6, 7, 8, 1},
		  {9, 1, 8, 1, 1}};
int matC[4][5];

struct matriks
{
    int i;
    int j; 
};

void *mult(void *ptr)
{    
    struct matriks *data = ptr;
    int i, sum = 0;
    
    for(i = 0; i < 2; i++)
    {  
//	printf("%d %d\n", data->i, data->j); 
        sum += matA[data->i][i] * matB[i][data->j];
    }
    
    matC[data->i][data->j] = sum;
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    int i, j ,n = 0,cnt = 0, *nilai;
    key_t key = 1234;

    printf ("Matriks A\n");
    for (i = 0; i < 4; i++){
	for (j = 0; j < 2; j++){
        printf ("%d\t", matA[i][j]);
    }
	printf("\n");
    }

    printf ("\nMatriks B\n");
    for (i = 0; i < 2; i++){
	for (j = 0; j < 5; j++){
        printf ("%d\t", matB[i][j]);
    }
	printf("\n");
    }

    int shmid = shmget(key, 20, IPC_CREAT | 0666);
    nilai = (int *)shmat(shmid, 0, 0);

    pthread_t tid;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++) 
        {
            struct matriks *data = (struct matriks *) malloc(sizeof(struct matriks));
            data->i = i;
            data->j = j;
	
            pthread_create(&tid, NULL, mult, data);
            pthread_join(tid, NULL);
        }
    }

    printf ("\nHasil perkalian matriks\n");
    for(i = 0; i < 4; i++)
    { 
        for(j = 0; j < 5; j++)
        { 
            printf("%d\t", matC[i][j]);
            nilai[n] = matC[i][j];
            n++;
        }
        printf("\n");
    }

//	n = 0;
//	for(i = 0; i < 20; i++)
//   {  
//            nilai[n] = matC[i][j];
//            printf("%d", nilai[n])
//	      n++;
//    }

    shmdt((void *) nilai);

    return 0;
}

