#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define NAME_SIZE 20
#define	BUF_SIZE 100

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

void errHandle(char* message) {
	perror(message);
	exit(1);
}

void* sndMsg(void* arg) {
	int sock = *((int*)arg);

	while(1) {
		fgets(msg, sizeof(msg), stdin); // 较scanf安全，因指定了读取上限
		//scanf("%s", msg);
		if(!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) {
			close(sock);
			exit(0);
		}

		char name_msg[NAME_SIZE + BUF_SIZE];
		sprintf(name_msg, "%s %s", name, msg);
		if(write(sock, name_msg, strlen(name_msg)) == -1)
			errHandle("write error");
	}

	return NULL;
}

void* rcvMsg(void* arg) {
	int sock = *((int*)arg);

	while(1) {
		char name_msg[NAME_SIZE + BUF_SIZE];
		int strLen = read(sock, name_msg, sizeof(name_msg) - 1);
		if(strLen == -1)
			errHandle("rcvMsg read() error");
		name_msg[strLen] = 0;

		// 不接收回声
		//if(strspn(name_msg, name) == strlen(name))
		//	continue;

		//fputs(name_msg, stdout);
		printf("%s", name_msg);
	}

	return NULL;
}

int main(int argc, char* argv[]) {
	if(argc < 3) {
		printf("Usage : %s <IP> <port> <name>\n", argv[0]);
		exit(1);
	}

	if(argv[3] != NULL) // 命令行若没输入<name>，则默认为 [DEFAULT]
		sprintf(name, "[%s]", argv[3]);

	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		errHandle("socket() error");

	struct sockaddr_in clntAddr;
	memset(&clntAddr, 0, sizeof(clntAddr));
	clntAddr.sin_family = AF_INET;
	clntAddr.sin_addr.s_addr = inet_addr(argv[1]);
	clntAddr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&clntAddr, sizeof(clntAddr)) == -1)
		errHandle("connect() error");

	pthread_t sndThread, rcvThread;
	if(pthread_create(&sndThread, NULL, sndMsg, (void *)&sock) != 0)
		errHandle("pthread_create(sndThread) error");
	if(pthread_create(&rcvThread, NULL, rcvMsg, (void *)&sock) != 0)
		errHandle("pthread_create(rcvThread) error");

	void* threadReturn;
	if(pthread_join(sndThread, &threadReturn) != 0)
		errHandle("pthread_join(sndThread) error");
	if(pthread_join(rcvThread, &threadReturn) != 0)
		errHandle("pthread_join(rcvThread) error");

	// 若使用以下方式销毁线程，主进程将直接退出
	// 而客户端将报错 rcvMsg read() error: Bad file descriptor
	/*if(pthread_detach(sndThread) != 0)
	  errHandle("pthread_detach(sndThread) error");
	  if(pthread_detach(rcvThread) != 0)
	  errHandle("pthread_detach(rcvThread) error");*/

	close(sock);

	return 0;
}
