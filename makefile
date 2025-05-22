
TARGET = prg/loop.smp

run: build
	./vm $(TARGET)

build: vm.c
	gcc -g vm.c -o vm
