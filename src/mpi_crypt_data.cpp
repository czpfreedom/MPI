#include "mpi_crypt_data.h"
#include "stdlib.h"
#include "string.h"

Mpi_Crypt_Data ::  Mpi_Crypt_Data(char* data, int data_length){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    m_time_stamp =Time_Stamp(tv);
    m_data_length =data_length;
    m_data = (char *)malloc(sizeof(char)*m_data_length);
    memcpy(m_data,data,data_length);
}

Mpi_Crypt_Data :: Mpi_Crypt_Data(Mpi_Crypt_Data& mpi_crypt_data){
    m_time_stamp = mpi_crypt_data.m_time_stamp;
    m_data_length = mpi_crypt_data.m_data_length;
    m_data = (char *)malloc(sizeof(char)*m_data_length);
    memcpy(m_data,mpi_crypt_data.m_data,m_data_length);
}

Mpi_Crypt_Data& Mpi_Crypt_Data :: operator=(Mpi_Crypt_Data& mpi_crypt_data){
    m_time_stamp = mpi_crypt_data.m_time_stamp;
    m_data_length = mpi_crypt_data.m_data_length;
    m_data = (char *)malloc(sizeof(char)*m_data_length);
    memcpy(m_data,mpi_crypt_data.m_data,m_data_length);
    return *this;
}

Mpi_Crypt_Data :: ~Mpi_Crypt_Data(){
    free(m_data);
}
