#include "Networking/tcp_server.h"
#include <iostream>

namespace MOYF
{
	using boost::asio::ip::tcp;

	TCPServer::TCPServer(IPV ipv, int port)
		: _ipVersion(ipv)
		, _port(port)
		, _acceptor(_ioContext, tcp::endpoint(_ipVersion == IPV::V4 ? tcp::v4() : tcp::v6(), _port))
	{}

	int TCPServer::Run()
	{
		try
		{
			startAccept();
			// blocking method 
			_ioContext.run();
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return -1;
		}
		return 0;
	}

	void TCPServer::startAccept()
	{
		// create a connection

		// asynchronously accept the connection
	}
}
