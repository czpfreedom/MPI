#ifndef MPI_CRYPT_DATA_H
#define MPI_CRYPT_DATA_H

#include "mpi_rsa_time_stamp.h"

namespace namespace_mpi_rsa{

//Crypt_Data, consist of cipher and plain together

class Mpi_Crypt_Data{

public:

    Time_Stamp m_time_stamp;
    char* m_data;
    char* m_key;
    int m_data_length;

    Mpi_Crypt_Data(char* data, int data_length);
    Mpi_Crypt_Data(Mpi_Crypt_Data& mpi_crypt_data);
    Mpi_Crypt_Data& operator=(Mpi_Crypt_Data& mpi_crypt_data);
    ~Mpi_Crypt_Data();

};

class Mpi_Cipher_Data : public Mpi_Crypt_Data{

};

class Mpi_Plain_Data : public Mpi_Crypt_Data{
    
};

}


#endif
