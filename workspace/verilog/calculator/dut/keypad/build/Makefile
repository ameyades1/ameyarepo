all: clean compile sim

clean:
	rm -rf work transcript

compile:
	vlib work
	vlog ../src/*.sv

sim:
	vsim -c tb_keypad -do "run -all; quit"
