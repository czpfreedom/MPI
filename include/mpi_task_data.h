#ifndef MPI_TASK_DATA_H
#define MPI_TASK_DATA_H

#include "mpi_rsa_time_stamp.h"
#include "mpi.h"
#include "mpi_log.h"
#include "stdio.h"
#include "rsa_final.h"

namespace namespace_mpi_rsa{

class MPI_Task_Data{
	
public:

    unsigned long m_task_id;
    Dis_Alg_Type m_dis_alg_type; 
    Handle_Alg_Type m_handle_alg_type;
    int m_block_length;

    Time_Stamp m_time_stamp;

    int m_processor_id;
    int m_processor_num;
    int m_distribute_id;
    int m_gather_id;

    int m_dest_id; //init dest_id =-1 
    int m_loop_num; // the loop number of distribute and gather init m_loop_num=0

    MPI_Status m_mpi_status;
    MPI_Request *m_mpi_request;

// first half key is e and the other half is n    
    char m_key[KEY_LENGTH_MAX];
    char m_text_data[TEXT_LENGTH_MAX];
    char m_mpi_data_send[SEND_LENGTH_MAX];
    char m_mpi_data_recv[RECV_LENGTH_MAX];
    
    int m_text_data_length;

    namespace_rsa_final :: CRT_N m_crt_n;
    namespace_rsa_final ::BN_WORD m_bn_e;

    char m_log_file_name[LOG_FILE_NAME_LENGTH]; 

    MPI_Task_Data();
    MPI_Task_Data(MPI_Task_Data& mpi_task_data);
    MPI_Task_Data& operator=(MPI_Task_Data& mpi_task_data);
    ~MPI_Task_Data();

    int distribute();
    int gather();
    int recv_send_task_data();

    int key_handle();
    int data_handle();

    int dest_calculate();

    int log_info(LOG_TYPE log_type);
    int log_info(LOG_TYPE log_type, DATA_TYPE data_type);

// for a test, deleted when     

    int init_random(Handle_Alg_Type handle_alg_type, Dis_Alg_Type dis_alg_type, int block_length); //just for test, init a FCFS mpi_task_data
    int crypt();

};

//int HANDLE_CRT_MOD_EXP(char *a, char *result, CRT_N crt_n, int data_length );

}

#endif
