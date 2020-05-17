#include <thread>
#include "SimpleServer.h"
#include "SimpleNetworkExceptions.h"

#pragma comment (lib, "ws2_32.lib")

SimpleServer::SimpleServer(Config config, PacketHandlerFn packetHandler) :
    config { config },
    packetHandler { packetHandler },
    logger{ config.loggingEnabled },
    threadPool{ config.threadPoolSize } {
    WSADATA data;
    WORD ver = MAKEWORD(config.winSockVersion.first, config.winSockVersion.second);
    int status = WSAStartup(ver, &data);
    if (status != 0) throw WinSockException("Failed to initialze winsock");
}


SimpleServer::~SimpleServer()
{
    WSACleanup();
}


void SimpleServer::run() 
{
    SOCKET server = createServerSocket();
    const auto [host, port] = getSocketInfo(server);
	logger.outnl("Running server  on:\n\n", "    HOST: ", host, "\n", "    PORT: ", port);
    logger.outnl("\n\nWaiting for connections ...");

    while (true) {
        SOCKET connection = waitForConnection(server);
        threadPool.enqueue([&]() { executeSession(connection); });
    }

    closesocket(server);
}


void SimpleServer::executeSession(SOCKET connection)
{
    char buf[4096];

    logpeer(connection, "connected");
    while (true) {

        memset(buf, 0, 4096);
        int len = recv(connection, buf, 4096, 0);

        if (len == 0) {
            break;
        }
        if (len == SOCKET_ERROR) {
            logger.outnl("ERR");
        }

        std::string response = packetHandler(buf);

        int status = send(connection, response.c_str(), response.size() + 1, 0);
        if (status == SOCKET_ERROR) {
            logpeer(connection, "failed to send data");
        }
    }

    logpeer(connection, "disconnected");
    closesocket(connection);
}


SOCKET SimpleServer::createServerSocket() 
{
    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) throw WinSockException{"Failed to create socket"};

    sockaddr_in addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_port = htons(config.port);
    addr.sin_addr.S_un.S_addr = inet_addr(config.host.c_str());

    int status0 = bind(server, (sockaddr*)&addr, sizeof(addr));
    if (status0 == SOCKET_ERROR) throw SocketException(server, "Failed to bind socket");

	int status1 = listen(server, SOMAXCONN);
    if (status1 == SOCKET_ERROR) throw SocketException(server, "Failed to start listening for connections");
    
    return server;
}


SOCKET SimpleServer::waitForConnection(SOCKET server) 
{
    sockaddr_in clientAddr;
    int size = sizeof(clientAddr);
    SOCKET connection = accept(server, (sockaddr*)&clientAddr, &size);
    if (connection == INVALID_SOCKET) throw SocketException(connection, "Failed to accept connection");

    return connection;
}


std::tuple<std::string, std::string> SimpleServer::getSocketInfo(SOCKET socket) 
{
    sockaddr_in addr;
    socklen_t len = sizeof(sockaddr_in);
    getsockname(socket, (sockaddr*)&addr, &len);

    return std::make_tuple(
        inet_ntoa(addr.sin_addr),
        std::to_string( ntohs(addr.sin_port))
    );
}


std::tuple<std::string, std::string> SimpleServer::getPeerInfo(SOCKET socket)
{
    sockaddr_in addr;
    socklen_t len = sizeof(sockaddr_in);
    getpeername(socket, (sockaddr*)&addr, &len);

    char host[NI_MAXHOST];
    char port[NI_MAXHOST];

    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(port, NI_MAXHOST);

    if (getnameinfo((sockaddr*)&addr, sizeof(addr), host, NI_MAXHOST, port, NI_MAXSERV, 0) != 0) {
        inet_ntop(AF_INET, &addr.sin_addr, host, NI_MAXHOST);
        std::string portStr = std::to_string(ntohs(addr.sin_port));
        strncpy_s(port, &portStr[0], portStr.size());
    }

    return std::make_tuple(host, port);
}


void SimpleServer::logpeer(SOCKET peer, const std::string& msg)
{
    const auto [host, port] = getPeerInfo(peer);
    logger.outnl("[", host, ":", port, "] ", msg);
}