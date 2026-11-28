#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../common/network_utils.hpp"

using namespace std;
int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        cerr << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in server_addr{};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8081);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        cerr << "Connection failed: " << strerror(errno) << '\n';
        close(sockfd);
        return 1;
    }

    cout << "Connected to Coordinator!\n";

    string message = "REGISTER node_1 127.0.0.1 9001 10737418240";

    if (!sendMessage(sockfd, message)) {
        cerr << "Registration request failed\n";
        close(sockfd);
        return 1;
    }

    string response;

    if (recvMessage(sockfd, response)) {
        cout << "Registration: " << response << '\n';
    }

    close(sockfd);

    // New connection for LIST_NODES
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        cerr << "Socket creation failed\n";
        return 1;
    }

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        cerr << "Connection failed\n";
        close(sockfd);
        return 1;
    }

    if (!sendMessage(sockfd, "LIST_NODES")) {
        cerr << "LIST_NODES request failed\n";
        close(sockfd);
        return 1;
    }

    if (recvMessage(sockfd, response)) {
        cout << "\nRegistered nodes:\n" << response << '\n';
    } else {
        cerr << "Failed to receive node list\n";
    }

    close(sockfd);
    return 0;
}