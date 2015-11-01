// ZQServer2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <zmq.h>
#include <iostream>
#include <string>

int main()
{

	//  Socket to talk to clients
	void *context = zmq_ctx_new();
	void *responder = zmq_socket(context, ZMQ_REP);
	int rc = zmq_bind(responder, "tcp://*:5555");
	int msg_cnt = 0;

	while (1) {
		
		
		char buffer[10];
		zmq_recv(responder, buffer, 10, 0);
		     
		char data[] = "M1:132.45";
		zmq_send(responder, data, sizeof(data), 0);
		std::cout << std::to_string(msg_cnt) << ". command sent" << std::endl;
		Sleep(1000);
		msg_cnt++;
	}

	zmq_close(responder);

	return 0;
}

