#pragma once
#include <string>  
#include <functional>
#include <WS2tcpip.h>

struct WinSockException : public std::exception
{
public:

    WinSockException(const std::string& msg) : msg{ msg }
    {
        std::cout << description() << std::endl;
        WSACleanup();
    }

    const char* what() const throw ()
    {
        return descriptionShort().c_str();
    }

private:
    std::string descriptionShort() const {
        return msg + " Err #" + std::to_string(WSAGetLastError());
    }

    std::string description() const {
        std::string d;
        d += "WinSock error";
        d += "\n";
        d += "\n    Message: " + msg;
        d += "\n    Error Code: " + std::to_string(WSAGetLastError());
        d += "\n";
        d += "\nSee https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2";
        d += "\nfor error code reference.";
        return d;
    }

    const std::string msg;
};


struct SocketException : WinSockException
{
public:

    SocketException(SOCKET socket, const std::string& msg) : WinSockException{ msg }
    {
        closesocket(socket);
    }
};