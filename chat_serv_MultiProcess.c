#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define MAX_CLNT 256
#define BUF_SIZE 100

int clntCnt = 0, clntSocks[MAX_CLNT];
pthread_mutex_t mutex;

void errHandle(char* message) {
	perror(message);
	exit(1);
}

void* handleClnt(void* arg) {
	int clntSock = *((int*)arg);

	while(1) {
		char buf[BUF_SIZE];
		int strLen = read(clntSock, buf, sizeof(buf));

		if(strLen == -1)
			errHandle("read() error");
		else if(strLen > 0) {
			pthread_mutex_lock(&mutex);
			for(int i = 0; i < clntCnt; ++i) {
				if(clntSocks[i] != clntSock) // 不发送回声
					write(clntSocks[i], buf, strLen);
			}
			pthread_mutex_unlock(&mutex);
		}
		else if(strLen == 0) {
			pthread_mutex_lock(&mutex);
			for(int i = 0; i < clntCnt; ++i) {
				if(clntSocks[i] == clntSock){
					do {
						clntSocks[i] = clntSocks[i + 1];
					} while(++i < clntCnt - 1);
				}
				break;
			}
			--clntCnt;
			printf("Client %d disconnected\n", clntSock);

			printf("Now the clntSocks[]: ");
			for(int i = 0; i < clntCnt; ++i)
				printf("[%d]%d ", i, clntSocks[i]);
			putc('\n', stdout);
			pthread_mutex_unlock(&mutex);

			close(clntSock);
			break;
		}
	}

	return NULL;	
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	int servSock = socket(PF_INET, SOCK_STREAM, 0); 
	if(servSock == -1)
		errHandle("socket() error");

	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	if(bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1)
		errHandle("bind() error");
	if(listen(servSock, 5) == -1)
		errHandle("listen() error");

	pthread_mutex_init(&mutex, NULL);
	while(1) {
		struct sockaddr_in clntAddr;
		socklen_t clntAddrSz = sizeof(clntAddr);
		int clntSock = accept(servSock, (struct sockaddr*)&clntAddr, &clntAddrSz);
		if(clntSock == -1)
			errHandle("accept() error");

		pthread_mutex_lock(&mutex);
		clntSocks[clntCnt++] = clntSock;
		pthread_mutex_unlock(&mutex);

		pthread_t t_id;
		pthread_create(&t_id, NULL, handleClnt, (void*)&clntSock);
		pthread_detach(t_id);

		printf("Client %d with IP %s connected\n", clntSock, inet_ntoa(clntAddr.sin_addr));

		printf("Now the clntSocks[]: ");
		for(int i = 0; i < clntCnt; ++i)
			printf("[%d]%d ", i, clntSocks[i]);
		putc('\n', stdout);
	}

	pthread_mutex_destroy(&mutex);
	close(servSock);

	return 0;
}
