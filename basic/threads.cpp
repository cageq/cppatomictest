
#include <iostream>
#include <stdio.h>
#include <thread>
#include <mutex>
using namespace std; 
int count = 0;
std::mutex g_mutex; 
#define MAX_THREADS 100
#define MAX_LOOPS 1000000
int main() {
	std::thread threads[MAX_THREADS]; 
    clock_t start = clock();
    clock_t end = clock(); 

    for(int i = 0;i < MAX_THREADS; i++)
    {
	    threads[i] = std::thread([&](){
			    
			    while(count <= 1000000)
			    {

			    g_mutex.lock(); 
			    count ++; 
			    if (count > MAX_LOOPS)
			    {
			    end = clock(); 
			    }
			    g_mutex.unlock(); 
			    }
			    
			    }); 

    }

    for(int i = 0;i < MAX_THREADS; i++)
    {
	    threads[i].join(); 
    }
    
    std::cout << "Result = " << count << endl;
    std::cout << "Time usage = " << end - start << "ms\n";
//system("pause");
    getchar(); 
    return 0;
}

