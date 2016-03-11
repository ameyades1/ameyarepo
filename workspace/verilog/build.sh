
FPATH=$(pwd)
SPATH="../src"

echo "Synthesize - XST..."
xst -intstyle ise -ifn "$FPATH/main.xst" -ofn "$FPATH/main.syr"

echo "Translate - NGDBUILD..."
ngdbuild -intstyle ise -dd _ngo -nt timestamp -uc $SPATH/main.ucf -p xc6slx16-csg324-3 main.ngc main.ngd

echo "Map - MAP...".
map -intstyle ise -p xc6slx16-csg324-3 -w -logic_opt off -ol high -t 1 -xt 0 -register_duplication off -r 4 -global_opt off -mt off -ir off -pr off -lc off -power off -o main_map.ncd main.ngd main.pcf

echo "Place & Route - PAR...".
par -w -intstyle ise -ol high -mt off main_map.ncd main.ncd main.pcf

echo "Generate Post-Place & Route Static Timing - TRCE..."
trce -intstyle ise -v 3 -s 3 -n 3 -fastpaths -xml main.twx main.ncd -o main.twr main.pcf

echo "Generate Programming File - BITGEN..."
bitgen -intstyle ise -f main.ut main.ncd

echo "Programming FPGA..."
djtgcfg enum
djtgcfg prog -d ameya -f main.bit -i 0

