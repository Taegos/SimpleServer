#include "SimpleServer.h"

int main()
{
    Config config;

    config.host = "127.0.0.1";
    config.port = 54000;
    config.winSockVersion = { 2,2 };
    config.loggingEnabled = true;

    SimpleServer::PacketHandlerFn fn = [](auto packet) { return ""; };

    SimpleServer server{ config, fn};

    server.run();
    return 0;
}