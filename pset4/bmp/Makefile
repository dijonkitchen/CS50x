#
# Makefile
#
# Computer Science 50
# Problem Set 4
#

all: copy whodunit resize

copy: copy.c
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o copy copy.c

whodunit: whodunit.c
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o whodunit whodunit.c

resize: resize.c
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -o resize resize.c

clean:
	rm -f *.o a.out core copy whodunit resize
