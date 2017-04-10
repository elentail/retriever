#pragma once
#include "common.h"
#include "poco_common.h"

using namespace std;
using namespace Poco::Net;

class MSGConnection : public TCPServerConnection {
public:
	MSGConnection(const StreamSocket& s) :
		::TCPServerConnection(s) {
	}

	void run() {
		cout << "New connection from: "
			<< socket().peerAddress().host().toString()
			<< endl << flush;

		bool isOpen = true;
		Poco::Timespan timeOut(10, 0);
		unsigned char incommingBuffer[1000] = {};
		while (isOpen) {
			if (socket().poll(timeOut, ::Socket::SELECT_READ) == false) {
				cout << "TIMEOUT!" << endl << flush;
			}
			else {
				cout << "RX EVENT!!! ---> " << flush;
				int nBytes = -1;

				try {
					nBytes = socket().receiveBytes(incommingBuffer, sizeof(incommingBuffer));
				}
				catch (Poco::Exception& exc) {
					//Handle your network errors.
					cerr << "Network error: " << exc.displayText() << endl;
					isOpen = false;
				}


				if (nBytes == 0) {
					cout << "Client closes connection!" << endl << flush;
					isOpen = false;
				}
				else {
					cout << "Receiving nBytes: " << nBytes << "\r\n";
					cout << "RECEIVED : " << incommingBuffer << endl << flush;

					string message(reinterpret_cast<char*>(incommingBuffer));

					regex info_rex("(\\S+)=(\\S+)");
					map<string, string> info_map;
					smatch info_matcher;
					while (regex_search(message, info_matcher, info_rex)){
						//cout << info_matcher[1] << " , " << info_matcher[2] << endl;
						info_map.emplace(make_pair(info_matcher[1], info_matcher[2]));
						message = info_matcher.suffix();
					}

				}
			}
		}
		cout << "Connection finished!" << endl << flush;
	}
};
