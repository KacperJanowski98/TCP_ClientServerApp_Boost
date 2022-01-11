
#include "Networking/tcp_connection.h"
#include <iostream>

namespace MOYF
{
	TCPConnection::TCPConnection(boost::asio::io_context &ioContext)
		: _socket(ioContext)
	{}

	void TCPConnection::Start()
	{
		boost::asio::async_write(_socket, boost::asio::buffer(_message), 
			[this](const boost::system::error_code& error, size_t bytesTransferred) {
				if (error)
				{
					std::cout << "Failed to send message!\n";
				}
				else
				{
					std::cout << "Sent " << bytesTransferred << " bytes of data!\n";
				}
			});
	}
}
