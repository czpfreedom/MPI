#include "mpi_rsa_time_stamp.h"
#include "stdio.h"
#include "string.h"
#include "iostream"

using namespace namespace_mpi_rsa;

int main(){
    
    struct timeval tv;
    gettimeofday(&tv,NULL);
    Time_Stamp time_stamp(tv);
    Time_Stamp time_stamp_copy(time_stamp);
    Time_Stamp time_stamp_assign;

// test time_stamp
       struct tm* pTime;
     pTime = localtime(&tv.tv_sec);

     char sTemp[30] = {0};
     snprintf(sTemp, sizeof(sTemp), "%04d%02d%02d%02d%02d%02d%03d%03d", pTime->tm_year+1900, \
            pTime->tm_mon+1, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec, \
            tv.tv_usec/1000,tv.tv_usec%1000);
     printf("time_stamp_origin:%s\n",sTemp);

     printf("time_stamp:%lu\n",time_stamp.m_data);

// test copy
     printf("time_stamp_copy:%lu\n",time_stamp_copy.m_data);

// test assign
     time_stamp_assign=time_stamp;
     printf("time_stamp_assign:%lu\n",time_stamp_assign.m_data);

// test pointer
     time_stamp.m_data++;
     printf("time_stamp++, time_stamp_copy:%lu\n",time_stamp_copy.m_data);
     printf("time_stamp++, time_stamp_assign:%lu\n",time_stamp_assign.m_data);     
    

}
