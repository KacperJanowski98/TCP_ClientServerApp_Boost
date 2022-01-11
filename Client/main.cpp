#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	try
	{
		boost::asio::io_context ioContext;

		// object to resolve a query to a list of endpoints
		tcp::resolver resolver{ ioContext };

		// perform forward resolution of a query to a list of entries
		auto endpoints = resolver.resolve("127.0.0.1", "1337");

		tcp::socket socket{ ioContext };
		// establish a socket connection by trying each endpoint in a sequence
		boost::asio::connect(socket, endpoints);

		while (true)
		{
			// listen for messages
		}
	}
	catch (std::exception& e)
	{

	}

	return 0;
}
