# Distributed File System (DistFS)

A distributed file storage system built with **C++20**, designed to explore distributed computing, networking, storage management, and fault tolerance.

## Overview

DistFS aims to provide a reliable way to store and retrieve files across multiple independent storage nodes.

The system is being developed from the ground up, with a focus on understanding core systems engineering concepts and building a practical distributed storage architecture.

## Planned Features

- **File Chunking:** Split large files into smaller chunks.
- **Distributed Storage:** Store chunks across multiple storage nodes.
- **Replication:** Maintain multiple copies of chunks for reliability.
- **Fault Tolerance:** Detect node failures and recover lost replicas.
- **Data Integrity:** Verify stored data using SHA-256 checksums.
- **Concurrent Operations:** Support multiple clients and simultaneous requests.
- **Client Interface:** Upload, download, list, and delete files through a CLI.

## Technology Stack

- **Language:** C++20
- **Networking:** TCP Sockets
- **Build System:** CMake
- **Database:** SQLite
- **Concurrency:** C++ Threads
- **Platform:** Linux (Ubuntu)

## Project Structure

```text
Distributed-File-System/
├── client/
├── coordinator/
├── storage_node/
├── networking/
├── common/
├── tests/
├── CMakeLists.txt
├── main.cpp
└── README.md
```

## Current Status

<ins>In Development</ins>

- [x] Initial project setup
- [x] CMake build configuration
- [ ] TCP client-server communication
- [ ] File chunking and reconstruction
- [ ] Multiple storage nodes
- [ ] Coordinator and metadata management
- [ ] Chunk replication
- [ ] Failure detection and recovery
- [ ] Data integrity verification

## Building the Project

```bash
cmake -S . -B build
cmake --build build
./build/distfs
```

## Goals

The primary goal of DistFS is to build a functional distributed storage system while exploring networking, concurrency, distributed coordination, fault tolerance, and systems design.

---

**Author:** [Manas Rai](https://github.com/manasrai14)