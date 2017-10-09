
#include <iostream>
#include <stdio.h>
#include <thread>
#include <atomic>
#include <mutex>
using namespace std; 
std::atomic<int> count(0);
#define MAX_THREADS 100
#define MAX_LOOPS 10000000
int main() {
	std::thread threads[MAX_THREADS]; 
    clock_t start = clock();
    clock_t end = clock(); 
    int expected = MAX_LOOPS; 

    for(int i = 0;i < MAX_THREADS; i++)
    {
	    threads[i] = std::thread([&](){
			    
			    while(count <= MAX_LOOPS)
			    {

			    count ++; 

			    //if(count.compare_exchange_weak(expected,MAX_LOOPS ))
			    std::cout << "count value is " << count << std::endl; 
			    if(count.compare_exchange_strong(expected,MAX_LOOPS +1))
			    //if(count > MAX_LOOPS)
			    {
			  
			    std::cout << "last count value is " << count << std::endl; 
			            end = clock(); 
			            break; 
			    }

			    }
			    
			    }); 

    }

    for(int i = 0;i < MAX_THREADS; i++)
    {
	    threads[i].join(); 
    }
    
    std::cout << "Result = " << count << endl;
    std::cout << "Time usage = " << end - start << "ms\n";
    getchar(); 
    return 0;
}

