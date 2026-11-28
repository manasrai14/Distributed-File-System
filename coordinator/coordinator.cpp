#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include "../common/network_utils.hpp"
using namespace std;

struct StorageNode {
    string node_id;
    string ip_address;
    int port;
    uint64_t capacity;
    bool online;
};


unordered_map<string, StorageNode> nodes;

void handleClient(int client_fd) {
    string message;
    if (!recvMessage(client_fd, message)) {
        cerr << "Failed to receive request\n";
        close(client_fd);
        return;
    }
    stringstream ss(message);
    string command;
    ss >> command;

    // Handle LIST_NODES
    if (command == "LIST_NODES") {
        string response;

        for (const auto& [id, node] : nodes) {
            response += id + " " + node.ip_address + " " +
                        to_string(node.port) + " " +
                        to_string(node.capacity) + " " +
                        (node.online ? "ONLINE" : "OFFLINE") + "\n";
        }

        if (response.empty()) {
            response = "NO_NODES_REGISTERED";
        }

        sendMessage(client_fd, response);
        close(client_fd);
        return;
    }
    string node_id, ip;
    int port = 0;
    uint64_t capacity = 0;

    ss >> node_id >> ip >> port >> capacity;

    if (command != "REGISTER" || node_id.empty() || ip.empty() ||
        port <= 0 || port > 65535 || capacity == 0) {

        sendMessage(client_fd, "INVALID_REQUEST");
        close(client_fd);
        return;
    }

    if (nodes.find(node_id) != nodes.end()) {
        sendMessage(client_fd, "ERROR NODE_ALREADY_EXISTS");
        close(client_fd);
        return;
    }
    StorageNode node{
        node_id,
        ip,
        port,
        capacity,
        true
    };

    nodes.emplace(node_id, node);

    cout << "Storage node registered: " << node_id << '\n';

    sendMessage(client_fd, "REGISTERED " + node_id);

    close(client_fd);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        cerr << "Coordinator socket creation failed\n";
        return 1;
    }
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in server_addr{};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8081);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        cerr << "Coordinator bind failed: " << strerror(errno) << '\n';
        close(server_fd);
        return 1;
    }
    cout << "Coordinator bound to port 8081\n";

    if (listen(server_fd, 10) == -1) {
        cerr << "Coordinator listen failed: " << strerror(errno) << '\n';
        close(server_fd);
        return 1;
    }
    cout << "Coordinator listening on port 8081...\n";
    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);

        if (client_fd == -1) {
            cerr << "Accept failed: " << strerror(errno) << '\n';
            continue;
        }

        cout << "A component connected to the Coordinator!\n";

        handleClient(client_fd);
    }
    close(server_fd);
    return 0;
}