#ifndef MPI_TASK_DATA_H
#define MPI_TASK_DATA_H

#include "time_stamp.h"
#include "mpi.h"
#include "stdio.h"
#include "mpi_log.h"


#define KEY_LENGTH_MAX 10000
#define TEXT_LENGTH_MAX 100000
#define SEND_LENGTH_MAX 90000
#define RECV_LENGTH_MAX 90000
#define TAG_MATRIX 1000
#define FCFS_4096  4096

typedef enum dis_alg_type{
    Alg_No_Distribute=1,
    Alg_FCFS,
    Alg_MEAN
}Dis_Alg_Type;


class MPI_Task_Data{

public:

    Dis_Alg_Type m_dis_alg_type; 

    Time_Stamp m_data_id;
    int m_processor_id;
    int m_processor_num;
    int m_distribute_id;
    int m_gather_id;

    int m_dest_id; //init dest_id =-1 
    int m_loop_num; // the loop number of distribute and gather init m_loop_num=0

    MPI_Status m_mpi_status;
    MPI_Request *m_mpi_request;

    char* m_key;
    int m_key_length;
    char *m_text_data;
    int m_text_data_length;
    char* m_mpi_data_send;
    int m_mpi_data_send_length;
    char* m_mpi_data_recv;
    int m_mpi_data_recv_length;

    FILE *m_log_file;

    MPI_Task_Data();
//    MPI_Task_Data(int argc,char* argv[]);

    MPI_Task_Data(MPI_Task_Data& mpi_task_data);
    MPI_Task_Data& operator=(MPI_Task_Data& mpi_task_data);
    ~MPI_Task_Data();

    int distribute();
    int gather();
    int recv_send_task_data();

    int handle();

    int dest_calculate();

    int log_create();
    int log_info(LOG_TYPE log_type);
    int log_quit();

// for a test, deleted when     
    int init_random(); //just for test, init a FCFS mpi_task_data
    int crypt();
    
};

#endif
