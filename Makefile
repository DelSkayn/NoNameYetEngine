

all:
	./Build-Make.sh
clean:
	./Clean.sh
rebuild:
	./Clean.sh
	./Build-Make.sh
rdebug:
	./Build-Make.sh
windows:
	./Build-Make-win.sh

