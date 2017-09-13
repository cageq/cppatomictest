#include "readerwriterqueue/benchmarks/ext/folly/ProducerConsumerQueue.h"

#include <iostream>
#include <thread>
#include <queue>
#include <unistd.h>
#include <mutex>
#include "utils.h"

using namespace std; 
using namespace folly; 
int g_maxCount  = 100000; 

//ReaderWriterQueue<int> q(100);       // Reserve space for at least 100 elements up front


//deque<int> q(100);       // Reserve space for at least 100 elements up front
ProducerConsumerQueue<int> q(100); 

int rand_step()
{
//	std::srand(std::time(0));
//	int step= rand()%49+1; 
	//return step; 
	return 50; 
}
std::thread writer; 
std::thread reader; 
int index =0;
int write_proc()
{

	writer = std::thread([&](){
			while( index <= g_maxCount)
			{
			int step = rand_step(); 
			Log( " enqueue "<< step<< " to queue " ); 
			while(step  > 0)
			{
			step--; 

			{
			q.enqueue(index++); 
			}
			}
			usleep(1); 
			}
			Log(" write finished " ); 

			}); 
	return 0; 

}

int result =0; 
int read_proc()
{
	int number = 0 ; 
	reader = std::thread([&](){
			// You can also peek at the front item of the queue (consumer only)
			while(result <= g_maxCount)
			{
			//int* front = q.peek();
			if (!q.isEmpty())
			{
				result = q.try_dequeue(number); 
				Log("result is "<< result << " num is " << number ); 
				result = number; 
			}
			else 
			{
			usleep(1); 
			}
			}
			Log(" read finished " ); ; 
			}); 


	return 0; 
}



int main(int argc,char *argv[])
{
	if (argc >=2 ){
		g_maxCount = atoi(argv[1]); 
		//printf("max count is %d\n",g_maxCount); 
	}


	clock_t start = clock();
	write_proc(); 
	read_proc(); 

	reader.join(); 
	writer.join(); 
	clock_t finish = clock();
	std::cout<<argv[0] << " duration:"<<finish - start<<"ms"<<std::endl;
	return 0; 

}
