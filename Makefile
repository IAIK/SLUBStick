run:
	./start-qemu.sh

server:
	./start-server.sh

object:
	objdump -D images/vmlinux | less

gdb:
	./start-gdb.sh
