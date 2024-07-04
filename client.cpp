#include "client.h"

#define PORT 8080

std::atomic<bool> running(true);

void receiveMessages(int sock)
{
    char buffer[1024] = {0};
    while (running)
    {
        int valread = read(sock, buffer, 1024);
        if (valread > 0)
        {
            std::cout << "Server: " << buffer << "\n";
            memset(buffer, 0, sizeof(buffer));
        }
        else if (valread == 0)
        {
            std::cout << "Server closed the connection\n";
            close(sock);
            running = false;
            break;
        }
        else
        {
            std::cerr << "Read error\n";
            close(sock);
            running = false;
            break;
        }
    }
}

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation failed\n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported\n";
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection Failed\n";
        return -1;
    }

    std::cout << "Connected to the server\n";

    std::thread recvThread(receiveMessages, sock);
    recvThread.detach();

    while (running)
    {
        std::string message;
        std::getline(std::cin, message);

        if (message == "exit")
        {
            std::cout << "Exiting...\n";
            running = false;
            break;
        }

        if (send(sock, message.c_str(), message.size(), 0) < 0)
        {
            std::cerr << "Send failed\n";
            running = false;
            break;
        }
    }

    close(sock);
    return 0;
}
