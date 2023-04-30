# MemoraDB

### Configure Project for VS Code

1. Open the Command Palette (`Ctrl+Shift+P`) and run the command "CMake: Configure".
2. Press `F5` or go to the Run view (`Ctrl+Shift+D`) and click the green "Run" button to start debugging `memora_server`.

## Summary of Project Phase 1: Simple Proof of Concept (POC)

The goal of Phase 1 is to create a minimal working version of MemoraDB to demonstrate its core functionality. This phase focuses on implementing basic CRUD operations and a simple communication protocol between the client and server.

### Design Architecture and Use-Case for Phase 1:

The architecture for Phase 1 consists of a server program and a client library. The server program is responsible for managing an in-memory data store, processing client requests, and performing CRUD operations. The client library provides an API that users can utilize to perform CRUD operations on the server's data store. The client and server communicate using a basic protocol with a predefined message format.

This simple proof of concept can be used as a foundation for a more feature-rich and scalable database system. In Phase 1, MemoraDB can be employed in small-scale applications or prototypes that require a lightweight in-memory database for storing and retrieving data.


### Background Information:

To understand the technology, design patterns, and programming concepts applied in this phase, the following background information is needed:

- C Programming Language: Knowledge of the C programming language, including syntax, data structures, and memory management, is essential for implementing the server program and client library.

- Sockets and IPC: Understanding of sockets and Inter-Process Communication (IPC) mechanisms, such as message queues, is necessary for establishing communication between the client and server.

- Data Structures: Familiarity with basic data structures, such as hash tables or balanced trees, is required for implementing the in-memory data store.

- Client-Server Architecture: Knowledge of the client-server architectural pattern is crucial for designing the communication and interaction between the client library and server program.

### Feature Functionality and Real-World Scenario:

After completing Phase 1, MemoraDB will provide the following functionalities:

- Basic CRUD operations: Create, Read, Update, and Delete records in the in-memory data store.

- Simple communication protocol: A predefined message format for communication between the client and server.

- Client library API: An API that users can leverage to perform CRUD operations on the server's data store.
