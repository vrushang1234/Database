#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>

void receiveMessages(int sock);

extern std::atomic<bool> running;

#endif