// ZQServer2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <zmq.h>
#include <iostream>

int main()
{

	//  Socket to talk to clients
	void *context = zmq_ctx_new();
	void *responder = zmq_socket(context, ZMQ_REP);
	int rc = zmq_bind(responder, "tcp://*:5555");
	

	while (1) {
		char buffer[10];
		zmq_recv(responder, buffer, 10, 0);
		printf("Received Hello\n");
		//sleep(1);          //  Do some 'work'
		zmq_send(responder, "World", 5, 0);
		std::cout << buffer;
	}

	zmq_close(responder);

	return 0;
}

