//============================================================================
// Name        : d_server.cpp
// Author      : hex
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/ipc.h>
using namespace std;
#define MSG_LENGTH 64
typedef struct {
	long mtype;
	char mtext[MSG_LENGTH];
} MSG;
int main() {
	int id = 0;
	MSG msg_buf;
	key_t key = ftok(".", 66);
	id = msgget(key, IPC_CREAT | 0666);
	if (id == -1) {
		printf("create msg error \n");
		return 0;
	}
	while (1) {
		if (msgrcv(id, (void *) &msg_buf, MSG_LENGTH, 0, 0) < 0) {
			printf("receive msg error \n");
			return 0;
		}
		cout << msg_buf.mtype << endl;
		cout << msg_buf.mtext << endl;

		struct msqid_ds buf;
		msgctl(id, IPC_STAT, &buf);
		//printf("permission : %o\n", buf.msg_perm.mode);
		cout << "msg_qnum" << buf.msg_qnum << endl;
		cout << "msg_stime" << buf.msg_stime << endl;
		cout << "msg_rtime" << buf.msg_rtime << endl;
		cout << "msg_ctime" << buf.msg_ctime << endl;
		cout << "msg_lspid" << buf.msg_lspid << endl;
		cout << "msg_lrpid" << buf.msg_lrpid << endl;

//		sscanf("600", "%o", (unsigned int *) &buf.msg_perm.mode);
//		msgctl(msgid, IPC_SET, &buf);

	}
	if (msgctl(id, IPC_RMID, NULL) < 0) {
		printf("del msg error \n");
		return 0;
	}

	return 0;
}
