#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../common/network_utils.hpp"
using namespace std;

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (client_fd == -1) {
        cerr << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        cerr << "Connection failed: " << strerror(errno) << '\n';
        close(client_fd);
        return 1;
    }
    cout << "Connected to DistFS server!\n";
    string message = "Hello from DistFS client!";
    if (!sendMessage(client_fd, message)) {
        cerr << "Failed to send message\n";
        close(client_fd);
        return 1;
    }

    cout << "Message sent to server!\n";

    string response;

    if (recvMessage(client_fd, response)) {
        cout << "Server says: " << response << '\n';
    } else {
        cerr << "Failed to receive response\n";
    }

    close(client_fd);
    return 0;
}
