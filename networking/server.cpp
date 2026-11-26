#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<unistd.h>
#include<thread>
#include "../common/network_utils.hpp"

using namespace std;

void handleClient(int client_fd) {
    cout << "Client connected successfully!\n";
    string message;
    if (!recvMessage(client_fd, message)) {
        cerr << "Failed to receive message from client\n";
        close(client_fd);
        return;
    }
    cout << "Client says: " << message << '\n';

    string response = "Hello this is Distributed File System, you are connected";

    if (!sendMessage(client_fd, response)) {
        cerr << "Failed to send response\n";
    }
    close(client_fd);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        cerr << "Socket creation failed\n";
        return 1;
    }
    cout << "TCP socket created successfully!\n";
    sockaddr_in server_addr{};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        cerr << "Bind failed: " << strerror(errno) << '\n';
        close(server_fd);
        return 1;
    }

    cout << "Socket bound to port 8080\n";
    if (listen(server_fd, 5) == -1) {
        cerr << "Listen failed: " << strerror(errno) << '\n';
        close(server_fd);
        return 1;
    }

    cout << "Server listening on port 8080...\n";

    
    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);

        if (client_fd == -1) {
            cerr << "Accept failed: " << strerror(errno) << '\n';
            continue;
        }
        thread t(handleClient, client_fd);
        t.detach();
    }
    return 0;
}