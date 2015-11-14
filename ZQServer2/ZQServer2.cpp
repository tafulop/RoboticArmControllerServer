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
	void *publisher = zmq_socket(context, ZMQ_PUB);
	int rc = zmq_bind(publisher, "tcp://*:5556");
	
	int msg_cnt = 0;

	while (1) {
		
		char* data = "M3 ";
		float ang = 123.456;
		int szam = 123;

		int len = 3 + sizeof(float);

		zmq_msg_t msg;
		zmq_msg_init_size(&msg, 20);
		

		snprintf((char*)zmq_msg_data(&msg), 20, "%s %f", data, ang);
		
		//zmq_send(publisher, "M3 123",5,0);
		zmq_send(publisher, &msg, 15, 0);
		std::cout << "Sent a message." <<std::endl;

		Sleep(1000);
	}

	zmq_close(publisher);

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

