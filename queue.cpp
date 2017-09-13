#include "readerwriterqueue/readerwriterqueue.h"

#include <iostream>
#include <thread>
#include <unistd.h>
#include "utils.h"

using namespace moodycamel;
std::atomic_long total(0);

int g_maxCount  = 100000; 

ReaderWriterQueue<int> q(100);       // Reserve space for at least 100 elements up front
int rand_step()
{
	//std::srand(std::time(0));
	//int step= rand()%49+1; 
	//return step; 
	return 50; 
}
std::thread writer; 
std::thread reader; 
int g_index =0;
int write_proc()
{

	 writer = std::thread([&](){
			while( g_index <= g_maxCount)
			{
			int step = rand_step(); 
			Log(" enqueue "<< step<< " to queue :" ); 
			while(step -- > 0)
			{
			q.enqueue(g_index++);                       // Will allocate memory if the queue is full
			}
			usleep(1); 
				//bool succeeded = q.try_enqueue(18);  // Will only succeed if the queue has an empty slot (never allocates)
				//assert(succeeded);

				//int number;
				//succeeded = q.try_dequeue(number);  // Returns false if the queue was empty

				//assert(succeeded && number == 17);
			}
			Log(" write finished " ); ; 

	}); 
	return 0; 

}

	int result =0; 
int read_proc()
{
	 reader = std::thread([&](){
	// You can also peek at the front item of the queue (consumer only)
		while(result <= g_maxCount)
		{
			//int* front = q.peek();
			//if (front != nullptr)

		if (q.size_approx() >0)
			{
				int ret	= q.try_dequeue(result);
				Log("result is "<< ret << " num is " << result);

			}
			else 
			{
				usleep(1); 
			}
		}
			Log(" read finished " ) ; 
	}); 


	return 0; 
}



int main(int argc, char * argv[])
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
	std::cout<<argv[0] << "      duration:"<<finish - start<<"ms"<<std::endl;
	return 0; 
}
