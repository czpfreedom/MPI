#ifndef TIME_STAMP_H
#define TIME_STAMP_H

#include <sys/time.h>
#include <time.h>

#define TIME_STAMP_LENGTH 20

using namespace std;

// Time: Year:4 Month:2 Day:2 Hour:2 Minute:2 Second:2 Ms:3 Us:3
// c++ char array end with a '\0'
class Time_Stamp {
public: 


    unsigned long m_data;
    Time_Stamp();
    Time_Stamp(struct timeval tv);
    
    int refresh();

};




#endif

