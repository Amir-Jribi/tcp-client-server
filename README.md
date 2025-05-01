# TCP Client-Server Communication Project

This project demonstrates a TCP-based client-server communication system implemented in C++. It includes three versions of the server:

- **Single-Client Server**: Handles one client at a time.
- **Multi-Threaded Server**: Spawns a new thread for each client connection.
- **Asynchronous Server**: Uses `poll()` to manage multiple clients without threading.

## 🧰 Features

- TCP connection setup using Berkeley sockets
- Client IP and port identification
- Message exchange between client and server
- Threaded and asynchronous models to handle multiple clients
- Clean and modular C++ code

## 🧪 Example Behavior

Single-client server: Accepts one client, exchanges messages, then closes the connection.

Threaded server: Accepts multiple clients, each handled in a separate thread.

Async server: Manages all clients in a single thread using non-blocking poll().

## 📌 Notes
The server listens on port 6969 by default.

Ensure that the server is started before any client attempts to connect.

You may change the server port number in the code if required.


## 🧱 Build Instructions

To compile all binaries:
```bash
make all
```
To clean the output files
```bash
make clean
```


## 📝 Future Improvements
Add benchmarking tools to compare the performance of threaded vs asynchronous server.




