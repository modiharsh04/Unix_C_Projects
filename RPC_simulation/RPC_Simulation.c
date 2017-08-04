/* 	GROUP : 	HARSH MODI 1457621
				PURVISH OZA 1500498
	THIS IS THE RPC USING TUPLE SPACES SIMULATION PROGRAMME USING THREADS*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


//LIST OF SERVICES THAT THE SERVER PROVIDES.
char *services[25] = {"AddTwoNumbers","SubtractTwoNumbers","MultiplyTwoNumbers","DivideTwoNumbers",
"Square","SquareRoot","Area","Volume","Perimeter","Circumference","SurfaceArea","Integrate",
"Differentiate","Power","Logarithm","StringLength","Encryption","Decryption","EdgeDetection",
"FFT","RayTracing","VolumeRendering","ZBuffer","TextureMapping","MotionBlur"};

int *request;
int **param;
int count;
char *str = "Work on this string.";

void *server_handler()		//SERVER HANDLER FOR THREAD.
{
	int j;
	printf("\n............Server is online......... \n");
	while(1){
		for (int i = 0; i < count; ++i)
		{
			pthread_mutex_lock(&mutex);		//MUTEX LOCK FOR ACCESSING GLOBAL SHARED VALUES.
			if(request[i] > 0 && request[i] < 30){			//IF SERVER FOUNDS ANYTHING IN THE SHARED MEMORY BY CLIENT.
				if (param[i][0] != -1) {
					printf("\nSERVER : Matching <%d, %d, %s", i+1, request[i], services[request[i] - 1]);
					j=1;
					while(param[i][j] != NULL){
						printf(", %d",param[i][j]);
						param[i][j] = 0;
						++j;
					}
					printf(">, which is requested by client[%d]\n", i+1);
				}else{
					printf("\nSERVER : Matching <%d, %d, %s, \"%s\">, which is requested by client[%d]\n", i+1, request[i], services[request[i] - 1],str,i+1);
				}
				request[i] = 30;		//REPLY CODE FROM SERVER.
				printf("\nSERVER : matching is done succesfully..........\n");
			}
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
		}
	}
}

void *client_handler( void *ptr )		//CLIENT HANDLER FOR THREAD.
{
	int i;
	int cli = *(int *) ptr;
	int x = cli;
	++cli;
	int parameters;
	srand((unsigned) time(NULL));
	int	z = (rand()%25);	//SELECTING OPERATION FOR RUNNING CLIENT RANDOMLY.
	z += 1;
	if((z>0 && z<5) || z==7 || z==9 || z==11 || z==14 || z==19 || z==21 || z==22){
		parameters = 2;
	}else if (z==5 || z==6 || z==10 || z==15){
		parameters = 1;
	}else if (z==16 || z==17 || z==18){
		parameters = 0;
	}else {
		parameters = 3;
	}

	pthread_mutex_lock(&mutex);		//LOCK FOR USING GLOBAL SHARED MEMORY.
	request[x] = z;
	if (parameters != 0){
		param[x] = malloc((parameters+1) * sizeof(int));
		srand((unsigned) time(NULL));
		for (i = 1; i <= parameters; ++i)
		{
			param[x][i] = (rand()%100) + 1;
		}
		printf("\nCLIENT[%d] : Request tuple created <%d, %d , %s", cli, cli, request[x], services[request[x] - 1]);
		for (i = 1; i <= parameters; ++i)
		{
			printf(", %d", param[x][i]);
		}
	printf(">\n");
	}else{
		param[x] = malloc(sizeof(int));
		param[x][0] = -1;
		printf("\nCLIENT[%d] : Request tuple created <%d, %d , %s,\"%s\">\n", cli, cli, request[x], services[request[x] - 1],str);
	}
	while(request[x] != 30){
		pthread_cond_wait(&cond,&mutex);
	}
	request[x] = 0;
	printf("\nCLIENT[%d] : I got the service.\n",cli);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[])
{
	pthread_t s, c;
	srand((unsigned) time(NULL));
	count = (rand()%15) + 1;		// GENERATING RANDOM NUMBER FOR CLIENTS.
	int i;

	request = malloc(count * sizeof(int));	//ALLOCATING DYNAMIC NUMBER FOR SHARED ARRAY.
	param = malloc(count * sizeof(int *));
	if (param == NULL){
		fprintf(stderr, "out of memory\n");
		exit(0);
	}

	if( pthread_create( &s, NULL, &server_handler, NULL) < 0)		//CREATE SERVER THREAD. IT WILL RUN CONTINUOUSLY.
	{
		perror("could not create thread");
		return 1;
	}

	for (i = 0; i < count; ++i)
	{
		if( pthread_create( &c, NULL, &client_handler, (void *) &i) < 0)	//CREATE CLIENT THREAD.
		{
			perror("could not create thread");
			return 1;
		}
		sleep(1);
		pthread_join(c, NULL);		//JOIN CLIENTS WITH MAIN THREAD.
	}

	//FREE ALL POINTERS.
	free(request);
	for(i = 0; i < count; i++)
		free(param[i]);
	free(param);
	exit(0);
}