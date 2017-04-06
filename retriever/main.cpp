//#include "abstract_retriever.h"
#include "message_server.h"


int main()
{
	//Retriever ftp{ "127.0.0.1","roadking","elfjjang" };
	//ftp.search_files();
	//ftp.download();

	//Create a server socket to listen.
	int port = 10004;
	ServerSocket svs(port);

	//Configure some server params.
	TCPServerParams* pParams = new TCPServerParams();
	pParams->setMaxThreads(4);
	pParams->setMaxQueued(4);
	pParams->setThreadIdleTime(100);

	//Create your server
	TCPServer myServer(new TCPServerConnectionFactoryImpl<MSGConnection>(), svs, pParams);
	myServer.start();

	while (1);

	return 0;
}