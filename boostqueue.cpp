
#include <boost/lockfree/spsc_queue.hpp>


#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include "utils.h"

using namespace std; 
int g_maxCount  = 100000; 

//ReaderWriterQueue<int> q(100);       // Reserve space for at least 100 elements up front


//deque<int> q(100);       // Reserve space for at least 100 elements up front
boost::lockfree::spsc_queue<int> q(100); 

int rand_step()
{
    //	std::srand(std::time(0));
    //	int step= rand()%49+1; 
    //return step; 
    return 50; 
}
int g_index =0;
int write_proc()
{
    while( g_index <= g_maxCount)
    {
	int step = rand_step(); 
	Log( " enqueue "<< step<< " to queue " ); 
	while(step  > 0)
	{
	    step--; 

	    {
		q.push(g_index++); 
	    }
	}
	usleep(1); 
    }
    Log(" write finished " ); 

    return 0; 

}

int result =0; 
int read_proc()
{
    int number = 0 ; 
    // You can also peek at the front item of the queue (consumer only)
    while(result <= g_maxCount)
    {
	//int* front = q.peek();
	bool ret = q.pop(number); 
	if (ret>0)
	{
	    Log("result is "<< result << " num is " << number ); 
	    result = number; 
	}
	else 
	{
	    usleep(1); 
	}
    }
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
