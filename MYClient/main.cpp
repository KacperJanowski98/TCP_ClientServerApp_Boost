#include <boost/asio.hpp>
#include <array>
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
			std::array<char, 128> buff;
			boost::system::error_code error;

			// read some data from socket
			size_t len = socket.read_some(boost::asio::buffer(buff), error);

			if (error == boost::asio::error::eof)
			{
				// clean connection cut off
				break;
			}
			else if (error)
			{
				throw boost::system::system_error(error);
			}

			std::cout.write(buff.data(), len);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
