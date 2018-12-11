CFLAGS=-g -Wall -O3 -masm=intel
LDFLAGS=-g

NO_CMOV_FLAGS= \
	-fno-tree-loop-if-convert \
	-fno-tree-loop-if-convert-stores \
	-fno-if-conversion \
	-fno-if-conversion2

OBJS=main.o test_cmov.o test_branch.o

main: $(OBJS)

test_branch.o: test_branch.c
	$(CC) $(CFLAGS) $(NO_CMOV_FLAGS) -c -o $@ $<

test_cmov.s: test_cmov.c
	$(CC) $(CFLAGS) -S -o $@ $<

test_branch.s: test_branch.c
	$(CC) $(CFLAGS) $(NO_CMOV_FLAGS) -S -o $@ $<

plot: out.png

out.png: out.csv
	./plot.gnuplot

out.csv: main
	./main | tee out.csv

clean:
	rm -f out.csv out.png
	rm -f *.o
	rm -f main
	rm -f *.s
