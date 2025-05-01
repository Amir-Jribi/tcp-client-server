all: serverSingleClient threadedServer asyncServer
serverSingleClient:
	g++ server.cpp -o server.o
	g++ client.cpp -o client.o
threadedServer:
	g++ threaded_server.cpp -o threaded_server.o
	g++ client.cpp -o client.o
asyncServer:
	g++ async_server.cpp -o async_server.o
	g++ client.cpp -o client.o


clean:
	rm -rf client.o server.o async_server.o threaded_server.o