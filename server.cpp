#include "server.h"
#include "hashmap.h"

#define PORT 8080

std::unordered_map<std::string, std::string> data_store;
std::atomic<bool> running(true);

void handleClient(int client_socket)
{
    char buffer[1024] = {0};

    while (running)
    {
        int valread = read(client_socket, buffer, 1024);
        if (valread > 0)
        {
            std::string message(buffer);
            std::stringstream ss(message);
            std::string command, key, value;
            ss >> command >> key;
            if (command == "SET")
            {
                ss >> value;
                std::string response = "";
                if (value != "")
                {

                    setKeyValue(key, value);
                    response = "SET OK\n";
                }
                else
                {
                    response = "SET ERROR: VALUE NOT FOUND\n";
                }
                send(client_socket, response.c_str(), response.size(), 0);
            }
            else if (command == "GET")
            {
                std::string response = "VALUE: " + getValueForKey(key) + "\n";
                send(client_socket, response.c_str(), response.size(), 0);
            }
            else
            {
                std::string response = "UNKNOWN COMMAND\n";
                send(client_socket, response.c_str(), response.size(), 0);
            }
            memset(buffer, 0, sizeof(buffer));
        }
        else if (valread == 0)
        {
            std::cout << "Client disconnected\n";
            break;
        }
        else
        {
            std::cerr << "Read error\n";
            break;
        }
    }

    close(client_socket);
}

void startServer()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "Socket creation failed\n";
        return;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cerr << "Setsockopt failed\n";
        return;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cerr << "Bind failed\n";
        return;
    }

    if (listen(server_fd, 3) < 0)
    {
        std::cerr << "Listen failed\n";
        return;
    }

    std::cout << "Server listening on port " << PORT << "\n";

    while (true)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            std::cerr << "Accept failed\n";
            continue;
        }

        std::thread client_thread(handleClient, new_socket);
        client_thread.detach();
    }
}

int main()
{
    startServer();
    return 0;
}
