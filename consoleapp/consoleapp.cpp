#include "SimpleServer.h"
using namespace std;

int main()
{
    Config config;

    config.host = "127.0.0.1";
    config.port = 54000;
    config.winSockVersion = { 2,2 };
    config.loggingEnabled = true;

    SimpleServer::PacketHandlerFn fn = [](const string& packet) { 
        cout << packet << endl;
        if (packet == "ping") return "pong";
        return packet.c_str(); 
    };

    SimpleServer server{ config, fn};
    server.run();

    return 0;
}