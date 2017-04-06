#pragma once

#ifndef  _RETRIEVER_H_
#define _RETRIEVER_H_

#include "common.h"
#include "poco_common.h"

class Retriever
{
private:

	// custom type
	using check_string = tuple<string, Poco::UInt32>;

	// download file list, local path
	vector<double_string> to_download_files;
	vector<check_string> downloaded_files;

	const string _hostname;
	const string _id,_pw;
	unique_ptr<FTPClientSession> session;

	//Poco::Net::FTPClientSession;

public:
	Retriever() = delete;
	virtual ~Retriever() ;
	//virtual void search_files(string&& local_path) = 0;
	void search_files();

	Retriever(string hostname);
	Retriever(string hostname, string id, string pw);

	void download(int thread_count = 1);
};

#endif // !