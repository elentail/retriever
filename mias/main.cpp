#include "abstract_retriever.h"

int main()
{
	Retriever ftp{ "127.0.0.1","roadking","elfjjang" };
	ftp.search_files();
	ftp.download();
	return 0;
}