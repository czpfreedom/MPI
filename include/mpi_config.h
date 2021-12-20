#ifndef MPI_CONFIG_H
#define MPI_CONFIG_H

namespace namespace_mpi_rsa{

/**********************************************************/
/*Config DIstribute****************************************/
/**********************************************************/

const int FCFS_1024 = 1024;
const int FCFS_2048 = 2048;
const int FCFS_4096 = 4096;

typedef enum dis_alg_type{
    Alg_No_Distribute=1,
    Alg_FCFS,
    Alg_MEAN,

}Dis_Alg_Type;

/**********************************************************/
/*Config HANDLE ALG****************************************/
/**********************************************************/

typedef enum handle_alg_type{
    Handle_Alg_No=1,
    Handle_Alg_CRT,
}Handle_Alg_Type;

/**********************************************************/
/*Config LOG***********************************************/
/**********************************************************/

#define MPI_RSA_LOG "/home/nx2/mpi_rsa/log" 

const int LOG_FILE_NAME_LENGTH = 128;

const int LOG_INFO_LENGTH_MAX = 100000;

typedef enum log_type{
//operation
    DIST_LOG=1, //distribution log
    GATH_LOG,   //gather       log
    HAND_LOG,   //handle       log
    TASK_LOG,   //task will be sent
    RESULT_LOG, //result in the end

//new and delete log
    CREATE_LOG,   //new mpi_data_task
    QUIT_LOG,    //delete mpi_data_task
    INIT_LOG     // init something for test
}LOG_TYPE;

/**********************************************************/
/*TASK MESSAGE Deconstruction******************************/
/**********************************************************/
/*

unsigned long:
    0:TASK_ID
    1:HANDLE_ALG
    2:DIS_ALG
    3:BLOCK_LENGTH
*/

/**********************************************************/
/*KEY Deconstruction***************************************/
/**********************************************************/

//     0-1023:KEY_E
const int E_TOP=0;

//  1024-2047:KEY_N 
const int N_TOP=1024;


/**********************************************************/
/*Config TASK_DATA*****************************************/
/**********************************************************/

const int CRYPT_LENGTH = 512;
const int KEY_LENGTH_MAX = 4096;
const int TEXT_LENGTH_MAX = 80000;
const int SEND_LENGTH_MAX = 80000;
const int RECV_LENGTH_MAX = 80000;
const int TAG_MATRIX = 1000;

typedef enum data_type{
    KEY_DATA=1,
    CONTENT_DATA,
    END_DATA,
    MESSAGE_DATA,
}DATA_TYPE;
/**********************************************************/
/*Config TASK_DATA*****************************************/
/**********************************************************/

const int CRT_2048 = 512;

/**********************************************************/

}

#endif
