CFLAGS=-Wall -O2
CNOP_FLAGS=-Wall -O0
LDFLAGS=-lrt
TARGETS=switch_state switch_state_nop functions functions_nop jump_table jump_table_nop

all: $(TARGETS) test analysis

.PHONY: all test

functions: functions.c
	gcc $(CFLAGS) functions.c -o functions $(LDFLAGS)

functions_nop: functions.c
	gcc $(CNOP_FLAGS) functions.c -o functions_nop $(LDFLAGS)

jump_table: jump_table.c
	gcc $(CFLAGS) jump_table.c -o jump_table $(LDFLAGS)

jump_table_nop: jump_table.c
	gcc $(CNOP_FLAGS) jump_table.c -o jump_table_nop $(LDFLAGS)

switch_state: switch_state.c
	gcc $(CFLAGS) switch_state.c -o switch_state $(LDFLAGS)

switch_state_nop: switch_state.c
	gcc $(CNOP_FLAGS) switch_state.c -o switch_state_nop $(LDFLAGS)

clean:
	rm -rf $(TARGETS) *.out *.png

test: functions.out functions_nop.out switch_state.out switch_state_nop.out jump_table.out jump_table_nop.out

functions.out: functions
	./run_tests.sh functions functions.out

functions_nop.out: functions_nop
	./run_tests.sh functions_nop functions_nop.out

jump_table.out: jump_table
	./run_tests.sh jump_table jump_table.out

jump_table_nop.out: jump_table_nop
	./run_tests.sh jump_table_nop jump_table_nop.out

switch_state.out: switch_state
	./run_tests.sh switch_state switch_state.out

switch_state_nop.out: switch_state_nop
	./run_tests.sh switch_state_nop switch_state_nop.out

analysis: test
	octave analysis.m



