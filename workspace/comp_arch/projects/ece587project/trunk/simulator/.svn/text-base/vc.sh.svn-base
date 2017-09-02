echo "No victim Cache IPC"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -fastfwd 1000 -max:inst 200000" >&results/novic.txt
cat results/novic.txt | grep IPC

echo "1 way IPC stream buffer size = 2"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -streambuf:size 2 -fastfwd 1000 -max:inst 200000" >&results/stream_buf2.txt
cat results/stream_buf2.txt | grep IPC

echo "1 way IPC stream buffer size = 4"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -streambuf:size 4 -fastfwd 1000 -max:inst 200000" >&results/stream_buf4.txt
cat results/stream_buf4.txt | grep IPC

echo "1 way IPC stream buffer size = 8"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -streambuf:size 4 -fastfwd 1000 -max:inst 200000" >&results/stream_buf8.txt
cat results/stream_buf8.txt | grep IPC

echo "1 way IPC stream buffer size = 16"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -streambuf:size 4 -fastfwd 1000 -max:inst 200000" >&results/stream_buf16.txt
cat results/stream_buf16.txt | grep IPC


echo "1 way IPC with prediction cache = 4"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -cache:il1v il1v:1:32:16:l  -mpredcache:size 4 -fastfwd 1000 -max:inst 200000" >&results/swap1_4m.txt
cat results/swap1_4m.txt | grep IPC

echo "1 way IPC without prediction cache"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -cache:il1v il1v:1:32:16:l  -fastfwd 1000 -max:inst 200000" >&results/swap1.txt
cat results/swap1.txt | grep IPC

echo "2 way IPC with prediction cache = 24"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -cache:il1v il1v:1:32:16:l  -mpredcache:size 24 -fastfwd 1000 -max:inst 200000" >&results/swap1_24m.txt
cat results/swap1_24m.txt | grep IPC

echo "1 way IPC with prediction cache = 16"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -cache:il1v il1v:1:32:16:l  -mpredcache:size 16 -fastfwd 1000 -max:inst 200000" >&results/swap1_16m.txt
cat results/swap1_16m.txt | grep IPC

echo "2 way"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -cache:il1v il1v:1:32:16:l  -mpredcache:size 4 -fastfwd 1000 -max:inst 200000" >&results/swap2.txt
cat results/swap2.txt | grep IPC

echo "4 way"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -cache:il1v il1v:1:32:16:l  -mpredcache:size 4 -fastfwd 1000 -max:inst 200000" >&results/swap4.txt
cat results/swap4.txt | grep IPC

echo "8 way"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -cache:il1v il1v:1:32:8:l  -mpredcache:size 64 -fastfwd 1000 -max:inst 200000" >&results/swap8.txt
cat results/swap8.txt | grep IPC

echo "16 way"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -cache:il1v il1v:1:32:16:l  -mpredcache:size 64 -fastfwd 1000 -max:inst 200000" >&results/swap16.txt
cat results/swap16.txt | grep IPC
echo "32 way"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -cache:il1v il1v:1:32:32:l   -mpredcache:size 64 -fastfwd 1000 -max:inst 200000" >&results/swap32.txt
cat results/swap32.txt | grep IPC
echo "64 way"
./Run.pl -db bench.db -dir results/gcc1 -benchmark go -sim /u/avd/ECE587/Simplescalar/simulator/ss3/sim-outorder -args " -cache:il1 il1:16:32:4:l -cache:il1v il1v:1:32:64:l  -mpredcache:size 128 -fastfwd 1000 -max:inst 200000" >&results/swap64.txt
cat results/swap64.txt | grep IPC
