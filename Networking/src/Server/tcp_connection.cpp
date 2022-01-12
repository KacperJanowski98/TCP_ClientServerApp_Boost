
#include "Networking/Server/tcp_connection.h"
#include <iostream>

namespace MOYF
{
	TCPConnection::TCPConnection(io::ip::tcp::socket&& socket)
		: _socket(std::move(socket))
	{
		boost::system::error_code ec;
		std::stringstream name;
		name << _socket.remote_endpoint();

		_username = name.str();
	}

	void TCPConnection::Start()
	{
		
	}

	void TCPConnection::Post(const std::string& message)
	{

	}

	void TCPConnection::asyncRead()
	{

	}

	void TCPConnection::onRead(boost::system::error_code ec, size_t bytesTransferred)
	{

	}

	void TCPConnection::asyncWrite()
	{

	}

	void TCPConnection::onWrite(boost::system::error_code ec, size_t bytesTransferred)
	{

	}

}
