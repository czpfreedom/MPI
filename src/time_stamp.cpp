#include "stdio.h"
#include "string.h"
#include "time_stamp.h"

Time_Stamp:: Time_Stamp(){
}


Time_Stamp:: Time_Stamp(struct timeval tv){
    struct tm* pTime;
    pTime = localtime(&tv.tv_sec);
    m_data=(unsigned long)((pTime->tm_year+900)%1000)*(unsigned long)(10000000000000000)+(unsigned long)(pTime->tm_mon+1)*(unsigned long)(100000000000000)+(unsigned long)(pTime->tm_mday)*(unsigned long)(1000000000000)+ (unsigned long)(pTime->tm_hour)*(unsigned long)(10000000000)+ (unsigned long)(pTime->tm_hour)*(unsigned long)(1000000000)+(unsigned long)(pTime->tm_sec)*(unsigned long)(1000000)+(unsigned long)(tv.tv_usec/1000)*(unsigned long)(1000)+(unsigned long)tv.tv_usec%1000;
}

int Time_Stamp:: refresh(){

}

/*
Time_Stamp:: Time_Stamp(Time_Stamp& time_stamp){
}

Time_Stamp& Time_Stamp:: operator=(Time_Stamp& time_stamp){
    return *this;
}

Time_Stamp:: ~Time_Stamp(){

}
*/
