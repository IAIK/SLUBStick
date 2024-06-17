#!/usr/bin/env bash
echo "[*] vm start"
# user: lmaar
# pw: asdf
qemu-system-x86_64 \
    -enable-kvm \
    -M pc \
    -m 16384 \
    -machine accel=kvm \
    -cpu kvm64 \
    -smp 4 \
    -drive file=images/ubuntu22.04.qcow2,format=qcow2 \
    -net nic,model=virtio \
    -net user,id=net0,hostfwd=tcp::7000-:8000,hostfwd=tcp::9000-:9000,hostfwd=tcp::9080-:9080,hostfwd=tcp::10021-:22 \
    -serial mon:stdio \
    -device ich9-intel-hda \
    -device hda-duplex \
    -gdb tcp::1234
echo "[*] vm done"

