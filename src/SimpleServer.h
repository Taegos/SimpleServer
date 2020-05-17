#pragma once

#include <tuple>
#include <string>  
#include <WS2tcpip.h>
#include <functional>
#include "threadpool/ThreadPool.h"
#include "headeronly/SimpleLogger.h"

struct Config {
    std::string host = "127.0.0.1";
    int port = 54000;
    bool loggingEnabled = true;
    std::pair<int, int> winSockVersion = { 2,2 };
    int threadPoolSize = 64;
};

class SimpleServer {
    
public:
    using PacketHandlerFn = std::function<std::string(std::string)>;

    SimpleServer(Config, PacketHandlerFn); 
    ~SimpleServer();
    void run();

private:
    const Config config;
    const SimpleLogger logger;
    ThreadPool threadPool;
    PacketHandlerFn packetHandler;

    void executeSession(SOCKET);
    SOCKET createServerSocket();
    SOCKET waitForConnection(SOCKET);
    std::tuple<std::string, std::string> getSocketInfo(SOCKET);
    std::tuple<std::string, std::string> getPeerInfo(SOCKET);
    void logsock(SOCKET, const std::string&);
};