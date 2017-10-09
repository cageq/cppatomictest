#include <atomic>




int main()
{

	char szBuf[64]; 
	std::atomic<char*> p(szBuf);


	char * pMid = p+2; 

	return 0; 
}
