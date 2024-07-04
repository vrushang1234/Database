#ifndef SERVER_H
#define SERVER_H

#include <unordered_map>
#include <string>
#include <atomic>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <sstream>

void handleClient(int client_socket);

void startServer();

extern std::unordered_map<std::string, std::string> data_store;
extern std::atomic<bool> running;

#endif
