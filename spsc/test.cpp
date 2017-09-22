#include <boost/thread/thread.hpp>
#include <atomic> 
#include <iostream>
#include <time.h>

// 全局的结果数据 
//long total = 0; 
std::atomic_long total(0);
// 点击函数
void click()
{
    for(int i=0; i<1000000;++i)
    {
        // 对全局数据进行无锁访问 
        total ++;     
    }
}
 
 
int main(int argc, char* argv[])
{
    // 计时开始
    clock_t start = clock();
    // 创建 100 个线程模拟点击统计
    boost::thread_group threads;
    for(int i=0; i<100;++i) 
    {
        threads.create_thread(click);
    }

    threads.join_all();
    // 计时结束
    clock_t finish = clock();
	total = 100; 
    // 输出结果
	std::cout<<"result:"<<total<<std::endl;
	std::cout<<"duration:"<<finish -start<<"ms"<<std::endl;

	std::atomic<bool> flag; 
	std::cout << " is lock free " << flag.is_lock_free() << std::endl; 

	printf(" total is %ld\n",total.load()); 
    return 0;
}

