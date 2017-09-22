#ifndef __UTILS_H__
#define __UTILS_H__


#ifdef _WIN32 
inline void mysleep(int a )
{
	Sleep(0); 
}
#define usleep mysleep 

#else 
#include <unistd.h>
#include <sys/time.h> 
#endif 

#ifndef NDEBUG
//#define Log(msg) do{ std::cout << __FILE__ << "(@" << __LINE__ << "): " << msg << '\n'; } while( false )
#define Log(msg) do{ std::cout <<   msg << '\n'; } while( false )
//#define Log(msg) do{ std::cout << __FILE__ << "(@" << __LINE__ << "): " << msg << '\n'; } while( false )
#define Trace( format, ... )   printf( "%s::%s(%d)" format, __FILE__, __FUNCTION__,  __LINE__, __VA_ARGS__ )
#else
#define Log(msg) 
#define Trace( format, ... )
#endif

#endif // 
