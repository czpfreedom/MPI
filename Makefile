### Makefile #####################

MPI_RSA_PATH=/home/nx2/mpi_rsa
MPI_PATH=/usr/local/mpich

RSA_PATH=/home/nx2/rsa_final

DIR_INC = $(MPI_RSA_PATH)/include
DIR_SRC = $(MPI_RSA_PATH)/src
DIR_OBJ = $(MPI_RSA_PATH)/obj
DIR_LIB = $(MPI_RSA_PATH)/lib
DIR_TEST= $(MPI_RSA_PATH)/test
DIR_LOG = $(MPI_RSA_PATH)/log

MPI_INC=$(MPI_PATH)/include
MPI_LIB=$(MPI_PATH)/lib

RSA_INC = $(RSA_PATH)/include
RSA_LIB = $(RSA_PATH)/lib/rsa_final.a

MPI_RSA_LIB = $(DIR_LIB)/libmpirsa.so

CC=gcc
CXX=g++
MPICXX =mpic++

INC=-I$(DIR_INC) -I$(MPI_INC)
LIB=-L$(DIR_LIB) -L$(MPI_LIB) -lmpi

CC_SRC= $(wildcard ${DIR_SRC}/*.c)
CC_OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${CC_SRC}))

CXX_SRC= $(wildcard ${DIR_SRC}/*.cpp)
CXX_OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${CXX_SRC}))

TEST_TIME_STAMP=$(DIR_TEST)/test_time_stamp
TEST_MPI_TASK_DATA = $(DIR_TEST)/test_mpi_task_data

$(MPI_RSA_LIB) : $(CXX_OBJ)
	$(MPICXX) -shared $^ -o $@

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp
	$(MPICXX) -c  -fPIC $< $(INC) -o $@

clean:  clean_test_time_stamp clean_test_mpi_task_data
	rm -f $(DIR_OBJ)/*.o
	rm -f $(DIR_LIB)/*.o
	rm -f $(DIR_LIB)/*.a
	rm -f $(DIR_LIB)/*.so

clean_test_time_stamp : 
	rm -f $(TEST_TIME_STAMP)/*.o
	rm -f $(TEST_TIME_STAMP)/test_time_stamp

clean_test_mpi_task_data :
	rm -f $(TEST_MPI_TASK_DATA)/*.o
	rm -f $(TEST_MPI_TASK_DATA)/test_mpi_task_data
clean_log :
	rm -f $(DIR_LOG)/*
