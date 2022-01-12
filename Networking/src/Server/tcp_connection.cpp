
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
		asyncRead();
	}

	void TCPConnection::Post(const std::string& message)
	{
		bool queueIdle = _outgoingMessages.empty();
		_outgoingMessages.push(message);

		if (queueIdle)
		{
			asyncWrite();
		}
	}

	void TCPConnection::asyncRead()
	{
		io::async_read_until(_socket, _streamBuf, "\n", 
			[self = shared_from_this()](boost::system::error_code ec, size_t bytesTransferred){
			self->onRead(ec, bytesTransferred);
		});
	}

	void TCPConnection::onRead(boost::system::error_code ec, size_t bytesTransferred)
	{
		if (ec)
		{
			_socket.close(ec);
			// error handler
			return;
		}
		std::stringstream message;
		message << _username << ": " << std::iostream(&_streamBuf).rdbuf();
		_streamBuf.consume(bytesTransferred);

		std::cout << message.str();

		// add a message handler
		asyncRead();
	}

	void TCPConnection::asyncWrite()
	{
		io::async_write(_socket, io::buffer(_outgoingMessages.front()),
			[self = shared_from_this()](boost::system::error_code ec, size_t bytesTransferred){
			self->onWrite(ec, bytesTransferred);
		});
	}

	void TCPConnection::onWrite(boost::system::error_code ec, size_t bytesTransferred)
	{
		if (ec)
		{
			_socket.close(ec);
			// error handler
			return;
		}

		_outgoingMessages.pop();

		if (_outgoingMessages.empty())
		{
			asyncWrite();
		}
	}

}
