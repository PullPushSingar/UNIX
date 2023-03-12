#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define N_AGENTS 20
#define N_ITEMS 20
#define OPENING_BID 100
#define MAX_RAISE 10
#define BIDDING_ROUNDS 100000
#define SHM_ID  259550 
#define MEM_SIZE  4096

static clock_t st_time;
static clock_t en_time;
static struct tms st_cpu;
static struct tms en_cpu;

#define GNIAZDKO_SERWERA "/tmp/QWERTYuiop123"


void start_clock()
{
	st_time = times(&st_cpu);
}

void end_clock()
{
	en_time = times(&en_cpu);
	

	float RTC_TIME =  (float)(en_time - st_time)/(float)sysconf(_SC_CLK_TCK);
	float CPU_TIME =  (float)(en_cpu.tms_utime + en_cpu.tms_cutime)/(float)sysconf(_SC_CLK_TCK);
	float CPU_SYSTEM = (float)(en_cpu.tms_stime + en_cpu.tms_cstime)/(float)sysconf(_SC_CLK_TCK);


	printf("Czas RTC: %.3f s\nCzas CPU USER %.3f s\nCzas CPU SYSTEM: %.3f s\n",RTC_TIME,CPU_TIME,CPU_SYSTEM);

}

int main(int argc , char *argv[]) 
{
	int i, j, k,sock,serv_len, cli_len;
	long int sum = 0, sum_Bids = 0;
	srand((unsigned int)getpid());
	int num,wart;

	struct sockaddr_un serv_addrstr, cli_addrstr;
	char buf[BUFSIZ]; /* bufor o domysl.rozm.*/
	struct timespec timeout = {0, 100000000};
	

	sock = socket(PF_UNIX, SOCK_DGRAM, 0);
	serv_addrstr.sun_family = AF_UNIX;
	strcpy(serv_addrstr.sun_path, GNIAZDKO_SERWERA);
	serv_len = sizeof(serv_addrstr);

	start_clock();


	for (int l = 0; l < N_AGENTS; l++)
	{
		if (fork() == 0)
		{
			for (j = 0; j < BIDDING_ROUNDS; j ++)
			{
				int  num = rand() %  N_ITEMS ;
				int  wart = rand() % (MAX_RAISE + 1);
				memcpy((void*)buf,(void*)&num,sizeof(int));
                                memcpy((void*)buf+sizeof(int),(void*)&wart, sizeof(int));
				sendto(sock,buf,2*sizeof(int),0,(struct sockaddr *) &serv_addrstr,serv_len);

			}
			exit(0);
		}
	}


	for (int m = 0 ; m < N_AGENTS; m++)
        {
                wait(NULL);
        }
	num = -1;
	memcpy((void*)buf,(void*)&num,sizeof(int));
	sendto(sock,buf,sizeof(int),0,(struct sockaddr *) &serv_addrstr,serv_len);


	
	end_clock();

	return 0;
}




