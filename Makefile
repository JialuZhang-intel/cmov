CFLAGS=-g -Wall -O3 -masm=intel
LDFLAGS=-g

OBJS=main.o test_cmov.o test_branch.o

main: $(OBJS)

test_cmov.s: test_cmov.c
	$(CC) $(CFLAGS) -S -o $@ $<

test_branch.s: test_branch.c
	$(CC) $(CFLAGS) -S -o $@ $<

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
