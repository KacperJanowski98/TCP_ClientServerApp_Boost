
#pragma once

#include <boost/asio.hpp>
#include "Networking/Server/tcp_connection.h"
#include <vector>
#include <functional>
#include <optional>
#include <unordered_set>

namespace MOYF
{
	namespace io = boost::asio;

	enum class IPV
	{
		V4,
		V6
	};

	class TCPServer
	{
	public:
		TCPServer(IPV ipv, int port);

		int Run();
		void Broadcast(const std::string &message);
	private:
		void startAccept();
	private:
		IPV _ipVersion;
		int _port;

		io::io_context _ioContext;
		io::ip::tcp::acceptor _acceptor;
		std::optional<io::ip::tcp::socket> _socket;
		std::unordered_set<TCPConnection::pointer> _connections {};
	};

}
