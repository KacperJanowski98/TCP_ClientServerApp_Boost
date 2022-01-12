
#include <iostream>
#include <Networking/Server/tcp_server.h>

int main(int argc, char* argv[])
{
	MOYF::TCPServer server{ MOYF::IPV::V4, 1337 };

	server.OnJoin = [](MOYF::TCPConnection::pointer server) {
		std::cout << "User has joined the server: " << server->GetUsername() << std::endl;
	};

	server.OnLeave = [](MOYF::TCPConnection::pointer server) {
		std::cout << "User has left the server: " << server->GetUsername() << std::endl;
	};

	server.OnClientMessage = [&server](const std::string& message) {
		server.Broadcast(message);
	};

	server.Run();

	return 0;
}
