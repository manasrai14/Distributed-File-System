#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<unistd.h>
using namespace std;

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

    int client_fd = accept(server_fd, nullptr, nullptr);

    if (client_fd == -1) {
        cerr << "Accept failed: " << strerror(errno) << '\n';
        close(server_fd);
        return 1;
    }

    cout << "Client connected successfully!\n";

    char buffer[1024] = {0};

    int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        cout << "Client says: " << buffer << '\n';
    }

    string response = "Hello from DistFS server!";

    send(client_fd, response.c_str(), response.size(), 0);
    cout << "Response sent to client!\n";
    return 0;
}