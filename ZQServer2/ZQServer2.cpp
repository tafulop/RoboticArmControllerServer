// ZQServer2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <zmq.h>
#include <iostream>
#include <string>

void sendCommand(void*, char*);

int main()
{

	//  Socket to talk to clients
	void *context = zmq_ctx_new();
	void *responder = zmq_socket(context, ZMQ_REP);
	int rc = zmq_bind(responder, "tcp://*:5555");
	int msg_cnt = 0;

	while (1) {
		
		char data2[] = "M5:-";		
		char data[] = "M3:-";

		sendCommand(responder, data);
		//Sleep(10);
		sendCommand(responder, data2);
		//Sleep(10);
	}

	zmq_close(responder);

	return 0;
}



	static void sendCommand(void* r, char* cmd) {

		static int n;
		char buffer[10];
		zmq_recv(r, buffer, 10, 0);

		zmq_send(r, cmd, sizeof(cmd), 0);
		std::cout << std::to_string(n++) << ". command sent." << std::endl;
		
		
		Sleep(1);
	}

