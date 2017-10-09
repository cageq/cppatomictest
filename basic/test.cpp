#include <atomic>
#include <string>
#include <iostream>




int main()
{
	std::atomic<int> pos ; 

	//pos *=3; 

	char szBuf[64] = "abcde"; 
	std::atomic<char*> p(szBuf);

	p = p+2; 


	pos = pos *  3; 
	int a = 10; 
	a *= 4; 

	char * pMid = p+2; 
	std::cout << "mid "<< pMid<<std::endl; 
	char *pMid2 = p.fetch_add(2); 
	std::cout << "mid: "<< pMid2<<std::endl; 
	std::cout << "p: "<< p <<std::endl; 

	return 0; 
}
