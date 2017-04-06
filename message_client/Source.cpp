#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/StreamCopier.h"

#include <iostream>
int main(int argc, char** argv)
{
	Poco::Net::SocketAddress sa("127.0.0.1", 10004);
	Poco::Net::StreamSocket socket(sa);
	//socket.sendBytes()

	Poco::Net::SocketStream str(socket);
	str << "EQPID:127.0.0.1 ID:roadking PW:elfjjang\r\n";

	str.flush();
	//Poco::StreamCopier::copyStream(str, std::cout);
	socket.close();
	return 0;
}