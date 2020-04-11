all: xvbell

xvbell:
	gcc -Wall -Wextra -Werror -o xvbell xvbell.c -lX11

clean:
	rm -f *.o xvbell
