include ../../Makefile

test_time_stamp : test_time_stamp.o 
	$(CXX)  $^ -o $@ $(INC)   $(LIB)

test_time_stamp.o : test_time_stamp.cpp
	$(CXX) -c  $< $(INC) -o $@
