#ifndef RSA_TIME_STAMP_H
#define RSA_TIME_STAMP_H

#include "sys/time.h"
#include "time.h"

#define TIME_STAMP_ABBR_LENGTH 30
#define TIME_STAMP_FULL_LENGTH 50

namespace namespace_mpi_rsa{

// Time: Year:4 Month:2 Day:2 Hour:2 Minute:2 Second:2 Ms:3 Us:3
// c++ char array end with a '\0'

class Time_Stamp {
public: 
    unsigned long m_data;
    char m_abbr[TIME_STAMP_ABBR_LENGTH];
    char m_full[TIME_STAMP_FULL_LENGTH];

    Time_Stamp();
    Time_Stamp(struct timeval tv);
    Time_Stamp(Time_Stamp& time_stamp);
    Time_Stamp& operator=(Time_Stamp& time_stamp);
    
    int refresh();

};

}

#endif

