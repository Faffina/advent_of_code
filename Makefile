%: %.c
	gcc -g $< -o prog
	./prog | wl-copy
	wl-paste

%.t: %.c
	gcc -g $< -o prog
	./prog 

c:
	wl-paste > i

t:
	wl-paste > it



