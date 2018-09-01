# Author: Jared Stark;   Created: Mon Aug 16 11:28:20 PDT 2004
# Description: Makefile for building a cbp submission.

CFLAGS = -g -Wall
CXXFLAGS = -g -Wall

objects = cbp_inst.o main.o op_state.o predictor.o tread.o

predictor : $(objects)
	$(CXX) -o $@ $(objects)

cbp_inst.o : cbp_inst.h cbp_assert.h cbp_fatal.h cond_pred.h finite_stack.h indirect_pred.h stride_pred.h value_cache.h
main.o : tread.h cbp_inst.h predictor.h op_state.h
op_state.o : op_state.h
predictor.o : predictor.h op_state.h tread.h cbp_inst.h
tread.o : tread.h cbp_inst.h op_state.h

.PHONY : clean
clean :
	rm -f predictor $(objects) check.log

CHECK_TRACE_FILE=../traces/DIST-FP-1
CHECK_RAT_SIZE=4
CHECK_G_HISTORY_SIZE=12
check:
	valgrind --leak-check=full --log-file=check.log ./predictor --trace-file=$(CHECK_TRACE_FILE) --rat-size=$(CHECK_RAT_SIZE) --g-history-size=$(CHECK_G_HISTORY_SIZE)
	
