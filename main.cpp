#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <zmq.h>

int main(int argc, char* argv[])
{
    using namespace std;
    using namespace rapidjson;

    pid_t pid = fork();
    printf("successfull fork and child pid is:%d\n", pid);
    if (pid == 0)
    {
        //child process

        // 1. Parse a JSON string into DOM.
        const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
        Document d;
        d.Parse(json);

        // 2. Modify it by DOM.
        Value& s = d["stars"];
        s.SetInt(s.GetInt() + 1);

        // 3. Stringify the DOM
        // StringBuffer buffer;
        // Writer<StringBuffer> writer(buffer);
        // d.Accept(writer);

        // Output {"project":"rapidjson","stars":11}
        //std::cout << buffer.GetString() << std::endl;

        //sleep(2);
        printf ("Connecting to hello world server…\n");
        void *context = zmq_ctx_new ();
        void *requester = zmq_socket (context, ZMQ_PUSH);
        zmq_connect (requester, "tcp://localhost:5555");

        int request_nbr;
        for (request_nbr = 0; request_nbr != 1000; request_nbr++)
        {
            s.SetInt(rand()%10000);
            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            d.Accept(writer);            

            //printf ("Sending Hello %d…\n", request_nbr);
            int rv = zmq_send (requester, buffer.GetString(), buffer.GetSize(), 0);
            usleep (1000*100);
            //printf("send rv = %d %lu\n", rv, buffer.GetSize());
            //char buffer2 [5] = {0};
            //zmq_recv (requester, buffer2, 10, 0);
            //printf ("Received World %d\n", request_nbr);
        }
        zmq_close (requester);
        zmq_ctx_destroy (context);        
    }
    else
    {
        //parent process is listener
        //  Socket to talk to clients
        void *context = zmq_ctx_new ();
        void *responder = zmq_socket (context, ZMQ_PULL);
        int rc = zmq_bind (responder, "tcp://*:5555");
        assert (rc == 0);

        while (1) {
            char buffer [256+1] = {0};
            zmq_recv (responder, buffer, 256, 0);
            printf ("rcv -> %s %lu\n", buffer, strlen(buffer));
            usleep (1000*100);          //  Do some 'work'
            //zmq_send (responder, "World", 5, 0);


            Document d;
            //printf("is object %d\n", d.IsObject());
            d.Parse(buffer, strlen(buffer));
            printf("--- parse input:%s %d\n", d["project"].GetString(),
                    d["stars"].GetInt());
        }
    }

    return 0;
}