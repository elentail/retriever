#include "abstract_retriever.h"


Retriever::~Retriever()
{
	session->close();
}
Retriever::Retriever(string hostname)
	:_hostname(hostname)
{
	session = make_unique<FTPClientSession>(_hostname);

	//set timeout (5s)
	session->setTimeout(Poco::Timespan(5, 0));
}
Retriever::Retriever(string hostname, string id, string pw)
	: Retriever(hostname)
{
	session->login(id, pw);
	session->setPassive(true);
}
void Retriever::search_files() {
	auto file1 = make_tuple("opencv/README.md.txt", "./");
	auto file2 = make_tuple("opencv/LICENSE.txt", "./");

	to_download_files.emplace_back(file1);
	to_download_files.emplace_back(file2);

}
void Retriever::download(int thread_count)
{
	//current directory list
	/*
	string row;
	istream &ftp_stream = session->beginList("",true);
	while (getline(ftp_stream, row)) {
		cout << row << endl;
	}
	session->endList();
	*/
	try {
		string reply_msg;
		Poco::Checksum crc32(Poco::Checksum::TYPE_CRC32);
		for (const auto& f : to_download_files) {

			StringTokenizer token(std::get<0>(f), "/");
			string dst_file = std::get<1>(f) + "/" + token[token.count() - 1];

			Poco::FileOutputStream fstream(dst_file, std::ios::out | std::ios::binary);
			std::istream& data = session->beginDownload(std::get<0>(f));
			session->sendCommand("SIZE " + dst_file, reply_msg);
			cout << "reply msg : " << reply_msg << endl;


			for (char byte = data.get(); !data.eof(); byte = data.get()) {
				crc32.update(byte);
				fstream << byte;
			}
			fstream.close();
			session->endDownload();
			//StringTokenizer token(std::get<0>(f), "/");
			//ofstream dst = ofstream(std::get<1>(f)+"/"+token[token.count()-1], ios::out | ios::binary);
			//istream& src = session->beginDownload(std::get<0>(f));
			//dst << src.rdbuf();
			//session->endDownload();
			cout << get<0>(f) << ", " << crc32.checksum() << endl;
			check_string check = make_tuple(dst_file, crc32.checksum());

			downloaded_files.push_back(check);

		}
	}
	catch (exception& e) {
		cout << e.what() << " , " << endl;
	}
}
