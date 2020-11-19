#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

using namespace std;
#define MSG_LENGTH 64
typedef struct {
	long mtype;
	char mtext[MSG_LENGTH];
} MSG;

int main(int argc, char **argv) {
	key_t key;
	int msgid;
	MSG buf;

	if ((key = ftok(".", 66)) == -1) {
		perror("ftok");
		exit(-1);
	}

	if ((msgid = msgget(key, 0666 | IPC_CREAT)) == -1) {
		perror("msgget");
		exit(-1);
	}
	memset(&buf, 'a', sizeof(buf));
	buf.mtype = 100;
	while (1) {
		if (-1 == msgsnd(msgid, &buf, MSG_LENGTH, 0)) {
			perror("msgsnd 1");
			exit(-1);
		}
		//usleep(1000 * 10);
		sleep(3);
	}
	return 0;
}
