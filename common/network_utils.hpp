#pragma once
#include <bits/stdc++.h>
#include <sys/socket.h>
#include<cstdint>
#include<string>
#include<arpa/inet.h>
using namespace std;

inline bool sendAll(int sockfd, const char* data, size_t len) {
    size_t total = 0;
    while (total < len) {
        ssize_t sent = send(sockfd, data + total, len - total, 0);
        if (sent <= 0) {
            return false;
        }

        total += sent;
    }
    return true;
}

inline bool recvAll(int sockfd, char* buffer, size_t len) {
    size_t total = 0;

    while (total < len) {
        ssize_t received = recv(sockfd, buffer + total, len - total, 0);
        if (received <= 0) {
            return false;
        }
        total += received;
    }

    return true;
}

inline bool sendMessage(int sockfd, const string& message) {
    if (message.size() > 1024 * 1024) {
        return false;
    }
    uint32_t length = htonl(static_cast<uint32_t>(message.size()));
    if (!sendAll(sockfd, reinterpret_cast<const char*>(&length), sizeof(length))) {
        return false;
    }
    return sendAll(sockfd, message.data(), message.size());
}

inline bool recvMessage(int sockfd, string& message) {
    uint32_t length = 0;
    if (!recvAll(sockfd, reinterpret_cast<char*>(&length), sizeof(length))) {
        return false;
    }
    length = ntohl(length);
    if (length > 1024 * 1024) {
        return false;
    }
    message.resize(length);
    if (length == 0) {
        return true;
    }
    return recvAll(sockfd, message.data(), length);
}