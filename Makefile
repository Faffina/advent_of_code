%: %.c
	gcc -g $< -o prog
	./prog | wl-copy
	wl-paste

c:
	wl-paste > i

t:
	wl-paste > it



