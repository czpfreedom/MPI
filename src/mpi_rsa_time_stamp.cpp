#include "stdio.h"
#include "string.h"
#include "mpi_rsa_time_stamp.h"

namespace namespace_mpi_rsa{

Time_Stamp:: Time_Stamp(){
}


Time_Stamp:: Time_Stamp(struct timeval tv){
    struct tm* pTime;
    pTime = localtime(&tv.tv_sec);
    m_data=(unsigned long)((pTime->tm_year+900)%1000)*(unsigned long)(10000000000000000)+(unsigned long)(pTime->tm_mon+1)*(unsigned long)(100000000000000)+(unsigned long)(pTime->tm_mday)*(unsigned long)(1000000000000)+ (unsigned long)(pTime->tm_hour)*(unsigned long)(10000000000)+ (unsigned long)(pTime->tm_min)*(unsigned long)(100000000)+(unsigned long)(pTime->tm_sec)*(unsigned long)(1000000)+(unsigned long)(tv.tv_usec/1000)*(unsigned long)(1000)+(unsigned long)tv.tv_usec%1000;

    sprintf(m_abbr,"%d-%d-%d-%d-%d-%d-%d-%d",pTime->tm_year+1900,pTime->tm_mon+1,pTime->tm_mday,pTime->tm_hour,pTime->tm_min,pTime->tm_sec,tv.tv_usec/1000,tv.tv_usec%1000);
    sprintf(m_full,"Year:%d Month:%d Day:%d Hour:%d Min:%d Sec:%d ", pTime->tm_year+1900,pTime->tm_mon+1,pTime->tm_mday,pTime->tm_hour,pTime->tm_min,pTime->tm_sec);

}

Time_Stamp:: Time_Stamp(Time_Stamp& time_stamp){
    m_data=time_stamp.m_data;
    memcpy(m_abbr,time_stamp.m_abbr,TIME_STAMP_ABBR_LENGTH);
    memcpy(m_full,time_stamp.m_full,TIME_STAMP_FULL_LENGTH);
}

Time_Stamp& Time_Stamp:: operator=(Time_Stamp& time_stamp){
    m_data=time_stamp.m_data;
    memcpy(m_abbr,time_stamp.m_abbr,TIME_STAMP_ABBR_LENGTH);
    memcpy(m_full,time_stamp.m_full,TIME_STAMP_FULL_LENGTH);
    return * this;
}


int Time_Stamp:: refresh(){

}

}

