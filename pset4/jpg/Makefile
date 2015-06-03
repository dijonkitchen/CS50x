#
# Makefile
#
# Computer Science 50
# Problem Set 4
#

all: recover

recover: recover.c
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o recover recover.c
	
clean:
	rm -f *.o a.out core recover
