

# SLUBStick Artifacts

This repo contains artifacts developed during a research project, as well as the code to perform SLUBStick.
For convenience, we provide a Virtual Machine (VM) image ([image](https://todo.todo)) with all necessary programs and scripts included.

## What is SLUBStick

SLUBStick is a kernel exploitation technique that elevates a heap vulnerability to an arbitrary memory read/write primitive and works in several steps:
Initially, it exploits a timing side channel of the allocator to reliably perform a cross-cache attack with better than 99% success rate on commonly used generic caches.
SLUBStick then exploits code patterns prevalent in the Linux kernel to perform a cross-cache attack and turn a heap vulnerability into a page table manipulation, thereby granting the capability to read and write memory arbitrarily.

The artifacts demonstrate the timing side channel and end-to-end exploits, showing the versatility of SLUBStick.
For both, we provide an environment of a VM running Linux kernel x86_64 v6.2.
For the timing side channel, the evaluation presents success rates for slab pages.
For the end-to-end exploits, our attacks exploits an artificial Double Free (DF) vulnerability to obtain an arbitrary physical read and write primitive.
This primitive is then used to manipulate the `/etc/passwd` file to gain root privileges within the VM.

## Dependencies

A Linux system running on the x86_64 architecture as well as that allows to run qemu with KVM enabled.

## Install

To install SLUBStick, run the following command:

```
git clone https://github.com/IAIK/SLUBStick.git
cd SLUBStick
download vm and store in images
make run
```

## Experiments

In the following, we demonstrate experiments of the timing side channel and exploit using SLUBStick:

#### Basic leakage 1 exploit

_How to:_
Execute `./userspace/timed_ppdev_alloc.elf`.

_Results:_ 
This experiment outputs a vertical plot with the following format: `<index>:    <tsc>:###`, where `index` is the allocated object's index, `tsc` the required time of the allocation, and `###` provides a visual representation of the `tsc`.
Allocating a new slab will result in a significantly larger `tsc` compared to that from the CPU free list.
Since one slab (from the `kmalloc-192`) can include 21 objects (observed via `cat /sys/kernel/slab/kmalloc-192/objs_per_slab`), a new slab will be allocated every 21th allocation.
This is seen with the significantly larger `tsc` (i.e., above 2000 compared to about 1100) of every 21th index.

[basic_leakage_1.webm](https://github.com/IAIK/SLUBStick/assets/170955372/b692c4fc-57ab-42a8-82c6-b06d23975227)

#### Basic leakage 2 exploit

_How to:_
Execute `./userspace/timed_anon_vma_name_alloc.elf <cache_size>`.

_Cache sizes:_
16, 32, 64, or 96 Bytes.

_Results:_
Similar to the experiment above, this experiment indicates larger `tsc` values when the SLUB allocator allocates a new slab.
Depending on the `cache_size` (i.e., between 16 to 96 Bytes), the new slab is allocated within the `kmalloc-[16,96]`.
For larger `cache_size`s, fewer objects must be allocated to prompt the allocator to allocate a new slab because fewer objects are located on one slab.
For instance, the `kmalloc-96` generic cache stores 42 objects, indicated with significantly larger `tsc` values for every 42th allocation.

[basic_leakage_2.webm](https://github.com/IAIK/SLUBStick/assets/170955372/d064975b-1a89-4aab-b91f-e2547d283bae)

#### Single page slab reclaiming exploit

_How to:_
Execute `./userspace/eval_pud.elf <cache_size>`.
        
_Cache sizes:_
8, 16, 32, 64, 96, 128, 192, or 256 Bytes.

_Results:_
This experiment outputs which slab page was reclaimed as a Page Upper Directory (PUD), successfully performing the cross-cache attack from the kernel heap to a PUD.
If the correct slab page is reclaimed as a PUD, this experiment outputs `[+] SUCCESS`, while `[!] FAIL` indicates a failed experiment.
`[!] RETRY (start not found)` indicates that the side channel did not find suitable slabs for cross-cache reuse.
This output represents neither a failure nor a success, but the experiment should be retried.

[single_page_slab_reclaiming.webm](https://github.com/IAIK/SLUBStick/assets/170955372/30846d97-3883-4347-8b66-c63502da426c)

#### Persistent code pattern 1 exploit

_How to:_
Execute `./userspace/exploit_signal.elf`.

_Results:_
Tampers with the `/etc/passwd` that unprivileged users can elevate their privilege level by calling `su` without authentication. 

[persistent_code_pattern_1_exploit.webm](https://github.com/IAIK/SLUBStick/assets/170955372/ce042658-c58d-42f5-93fc-829c145be4fa)

#### Persistent code pattern 2 exploit

_How to:_
Execute `./userspace/exploit_snd.elf <cache_size>`.

_Cache sizes:_
16, 32, 64, 96, 128, 192, or 256 Bytes.

_Results:_
Same results as above.

[persistent_code_pattern_2_exploit.webm](https://github.com/IAIK/SLUBStick/assets/170955372/c6875139-e359-4076-b1e8-a475de90d793)

#### Temporal code pattern exploit

_How to:_
Execute `./userspace/exploit_key.elf <cache_size>`

_Cache sizes:_
16, 64, 96, or 128 Bytes.

_Results:_
Same results as above.

[temporal_code_pattern_exploit.webm](https://github.com/IAIK/SLUBStick/assets/170955372/5267548e-c50c-4203-a63b-5bc1ee739e4d)

## Publication

```
@inproceedings{Maar2024SLUBStick,
 author = {Lukas Maar and Stefan Gast and Martin Unterguggenberger and Mathias Oberhuber and Stefan Mangard},
 booktitle = {{USENIX Security}},
 title = {{SLUBStick: Arbitrary Memory Writes through Practical Software Cross-Cache Attacks within the Linux Kernel}},
 year = {2024}
}
```
