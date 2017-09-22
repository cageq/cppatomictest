
#include <new>

#include "readerwriterqueue/benchmarks/ext/folly/ProducerConsumerQueue.h"

#include <iostream>
#include <thread>
#include <queue>
#include <stdio.h>
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
int  g_index =0;
int write_proc()
{

	while( g_index <= g_maxCount+10)
	{
		int step = rand_step(); 
		Log( " enqueue "<< step<< " to queue " ); 
		while(step  > 0)
		{
				bool ret  = q.enqueue(g_index); 
				if (ret)
				{
					g_index++; 
					step--; 
				}
		}
		usleep(1); 
	}
	Log(" write finished " ); 

	return 0; 

}

bool g_running = true; 
int result =0; 
int read_proc()
{
	int number = 0 ; 
	// You can also peek at the front item of the queue (consumer only)
	while(result <= g_maxCount)
	{
		//int* front = q.peek();
		if (!q.isEmpty())
		{
			result = q.try_dequeue(number); 
			if (result)
			{
				Log("result is "<< result << " num is " << number ); 
				result = number; 
			}
			else 
			{
				Log("dequeue failed"); 

			}
		}
		else 
		{
			usleep(1); 
		}
	}

	g_running = false; 
	Log(" read finished " ); ; 
	return 0; 
}



int main(int argc,char *argv[])
{
	if (argc >=2 ){
		g_maxCount = atoi(argv[1]); 
		//printf("max count is %d\n",g_maxCount); 
	}


	clock_t start = clock();

	std::thread writer(write_proc); 
	std::thread reader(read_proc); 
	reader.join(); 
	writer.join(); 

	clock_t finish = clock();
	std::cout<<argv[0] << " duration:"<<finish - start<<"ms"<<std::endl;

	return 0; 

}
