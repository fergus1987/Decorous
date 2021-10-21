#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define MAX_CLNT 256
#define EPOLL_SIZE 50
#define BUF_SIZE 100

int clntSocks[MAX_CLNT], clntCnt = 0; // 保存客户端套接字的数组

void errHandle(char* message) {
	perror(message);
	exit(1);
}

void setNonBlock(int fd) { // 对文件描述符设置非阻塞
	int flg = fcntl(fd, F_GETFL);
	if(flg == -1)
		errHandle("F_GETFL error");
	if(fcntl(fd, F_SETFL, flg|O_NONBLOCK) == -1)
		errHandle("F_SETFL error");
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	int servSock = socket(PF_INET, SOCK_STREAM, 0);
	if(servSock == -1)
		errHandle("socket() error");
	//setNonBlock(servSock);

	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	if(bind(servSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1)
		errHandle("bind() error");
	if(listen(servSock, 5) == -1)
		errHandle("listen() error");

	// 创建 epoll_event 数组的两种方式
	struct epoll_event event, events[EPOLL_SIZE];
	// struct epoll_event* events;
	// events = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);

	int epfd = epoll_create(EPOLL_SIZE);
	if(epfd == -1)
		errHandle("epoll_create() error");

	event.events = EPOLLIN;
	event.data.fd = servSock;
	if(epoll_ctl(epfd, EPOLL_CTL_ADD, servSock, &event) == -1)
		errHandle("server epoll_ctl() error");

	while(1) {
		int eventCnt = epoll_wait(epfd, events, EPOLL_SIZE, -1);
		if(eventCnt == -1)
			errHandle("epoll_wait() error");

		for(int i = 0; i < eventCnt; ++i) {
			int epoll_fd = events[i].data.fd;

			if(epoll_fd == servSock) { // 返回的发生事件对应的文件描述符为服务端时
				struct sockaddr_in clntAddr;
				socklen_t addrSz = sizeof(clntAddr);
				int clntSock = accept(servSock, (struct sockaddr*)&clntAddr, &addrSz);
				if(clntSock == -1)
					errHandle("accept() error");
				setNonBlock(clntSock);

				event.events = EPOLLIN | EPOLLET; // 设置边缘触发
				event.data.fd = clntSock;
				if(epoll_ctl(epfd, EPOLL_CTL_ADD, clntSock, &event) == -1)
					errHandle("client epoll_ctl() add error");

				clntSocks[clntCnt++] = clntSock;
				printf("Client %d connected\n", clntSock);

				printf("Now the clntSocks[]: ");
				for(int i = 0; i < clntCnt; ++i)
					printf("[%d]%d ", i, clntSocks[i]);
				putc('\n', stdout);
			}
			else { // 返回的发生事件对应的文件描述符为客户端时
				while(1) {
					char buf[BUF_SIZE];
					int strLen = read(epoll_fd, buf, sizeof(buf));

					if(strLen == -1) {
						if(errno == EAGAIN)
							break;
						printf("client %d ", epoll_fd);
						errHandle("read() error");
					}
					else if(strLen > 0) {
						for(int i = 0; i < clntCnt; ++i) {
							if(clntSocks[i] != epoll_fd) // 不发送回声
								write(clntSocks[i], buf, strLen);
						}
					}
					else if(strLen == 0) {
						if(epoll_ctl(epfd, EPOLL_CTL_DEL, epoll_fd, NULL) == -1)
							errHandle("client epoll_ctl() delete error");

						// 将 epoll_fd 从 clntSocks 中删除并将其后的客户端文件描述符依次前移
						for(int i = 0; i < clntCnt; ++i) {
							if(clntSocks[i] == epoll_fd) {
								do {
									clntSocks[i] = clntSocks[i + 1];
								} while(++i < clntCnt - 1);
								break;
							}
						}

						--clntCnt;
						close(epoll_fd);
						printf("Client %d disconnected\n", epoll_fd);

						printf("Now the clntSocks[]: ");
						for(int i = 0; i < clntCnt; ++i)
							printf("[%d]%d ", i, clntSocks[i]);
						putc('\n', stdout);

						break;
					}
				}
			}
		}
	}

	close(servSock);
	return 0;
}
