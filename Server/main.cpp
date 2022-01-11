#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	try 
	{
		// I/O functionality for users of the asynchronous I/O object to keep information 
		boost::asio::io_context ioContext;

		// accepting new socket connection
		tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 1337));

		while (true)
		{
			std::cout << "Accepting connections on port 1337!\n";
			// asynchronous and blocking stream-oriented socket functionality
			tcp::socket socket(ioContext);
			// accept a new connection
			acceptor.accept(socket);

			std::cout << "Client connected! Sending message!\n";
			std::string hello_message = "Hello client!\n";
			boost::system::error_code error;

			// write a message to a stream
			boost::asio::write(socket, boost::asio::buffer(hello_message), error);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
