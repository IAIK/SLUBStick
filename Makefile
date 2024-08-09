run:
	./start-qemu.sh

no-graphic:
	./start-qemu.sh

server:
	./start-server.sh

object:
	objdump -D images/vmlinux | less

gdb:
	./start-gdb.sh
