#include <boost/thread/thread.hpp>
#include <atomic> 
#include <iostream>
#include <time.h>

using namespace std;
// 全局的结果数据 
//long total = 0; 
atomic_long total(0);

// 点击函数
void click()
{
    for(int i=0; i<1000000;++i)
    {
        // 对全局数据进行无锁访问 
        total += 1;     
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
    // 输出结果
    cout<<"result:"<<total<<endl;
    cout<<"duration:"<<finish -start<<"ms"<<endl;
    return 0;
}

