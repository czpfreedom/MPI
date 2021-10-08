include ../../Makefile

test_time_stamp : test_time_stamp.o $(MPI_RSA_LIB) 
	$(CXX)  $^ -o $@ $(INC)   $(LIB) $(MPI_RSA_LIB)

test_time_stamp.o : test_time_stamp.cpp
	$(CXX) -c  $< $(INC) -o $@
