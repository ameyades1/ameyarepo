all: clean build sim 

debug: clean dbg

leak:
	@echo "\n----LEAK CHECK----\n"
	valgrind --leak-check=full ./Debug/cachesim ../../../trunk/docs/cc1.din

sim: 
	@echo "\n----RUNNING SIMULATION----\n"
	./Debug/cachesim ../../../trunk/docs/cc1.din
	@echo "\n----DONE----\n"

clean:
	@echo "\n---Cleaning---\n"
	rm -rf *.o Debug/*.* cachesim

build:
	@echo "\n---Compiling---\n"
	g++ -c main.cpp -o Debug/main.o 
	g++ -c Cache/Cache.cpp -o Debug/cache.o
	g++ -c CacheWriteThru/CacheWriteThru.cpp -o Debug/cachewritethru.o
	g++ -c L2/CacheL2.cpp -o Debug/cachel2.o
	g++ -c Trace/Trace.cpp -o Debug/trace.o
	g++ -c Trace/Trace_Cmds.cpp -o Debug/tracecmds.o
	g++ -o Debug/cachesim Debug/*.o
	@echo "\n----COMPILATION FINISHED----\n"

CDBG=-g -Wall

dbg:
	@echo "\n---Compiling for Debug---\n"
	g++ $(CDBG) -c main.cpp -o Debug/main.o 
	g++ $(CDBG) -c Cache/Cache.cpp -o Debug/cache.o
	g++ $(CDBG) -c CacheWriteThru/CacheWriteThru.cpp -o Debug/cachewritethru.o
	g++ $(CDBG) -c L2/CacheL2.cpp -o Debug/cachel2.o
	g++ $(CDBG) -c Trace/Trace.cpp -o Debug/trace.o
	g++ $(CDBG) -c Trace/Trace_Cmds.cpp -o Debug/tracecmds.o
	g++ $(CDBG) -o cachesim Debug/*.o
	@echo "\n----COMPILATION FINISHED----\n"
