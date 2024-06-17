#pragma once

#define _PAGE_BIT_PRESENT	0	/* is present */
#define _PAGE_BIT_RW		1	/* writeable */
#define _PAGE_BIT_USER		2	/* userspace addressable */
#define _PAGE_BIT_PWT		3	/* page write through */
#define _PAGE_BIT_PCD		4	/* page cache disabled */
#define _PAGE_BIT_ACCESSED	5	/* was accessed (raised by CPU) */
#define _PAGE_BIT_DIRTY		6	/* was written to (raised by CPU) */
#define _PAGE_BIT_PSE		7	/* 4 MB (or 2MB) page */
#define _PAGE_BIT_PAT		7	/* on 4KB pages */
#define _PAGE_BIT_GLOBAL	8	/* Global TLB entry PPro+ */
#define _PAGE_BIT_SOFTW1	9	/* available for programmer */
#define _PAGE_BIT_SOFTW2	10	/* " */
#define _PAGE_BIT_SOFTW3	11	/* " */
#define _PAGE_BIT_PAT_LARGE	12	/* On 2MB or 1GB pages */
#define _PAGE_BIT_SOFTW4	58	/* available for programmer */
#define _PAGE_BIT_PKEY_BIT0	59	/* Protection Keys, bit 1/4 */
#define _PAGE_BIT_PKEY_BIT1	60	/* Protection Keys, bit 2/4 */
#define _PAGE_BIT_PKEY_BIT2	61	/* Protection Keys, bit 3/4 */
#define _PAGE_BIT_PKEY_BIT3	62	/* Protection Keys, bit 4/4 */
#define _PAGE_BIT_NX		63	/* No execute: only valid after cpuid check */

#define _PAGE_PRESENT	(1ULL << _PAGE_BIT_PRESENT)
#define _PAGE_RW	(1ULL << _PAGE_BIT_RW)
#define _PAGE_USER	(1ULL << _PAGE_BIT_USER)
#define _PAGE_PWT	(1ULL << _PAGE_BIT_PWT)
#define _PAGE_PCD	(1ULL << _PAGE_BIT_PCD)
#define _PAGE_ACCESSED	(1ULL << _PAGE_BIT_ACCESSED)
#define _PAGE_DIRTY	(1ULL << _PAGE_BIT_DIRTY)
#define _PAGE_PSE	(1ULL << _PAGE_BIT_PSE)
#define _PAGE_GLOBAL	(1ULL << _PAGE_BIT_GLOBAL)
#define _PAGE_SOFTW1	(1ULL << _PAGE_BIT_SOFTW1)
#define _PAGE_SOFTW2	(1ULL << _PAGE_BIT_SOFTW2)
#define _PAGE_SOFTW3	(1ULL << _PAGE_BIT_SOFTW3)
#define _PAGE_PAT	(1ULL << _PAGE_BIT_PAT)
#define _PAGE_PAT_LARGE (1ULL << _PAGE_BIT_PAT_LARGE)
#define _PAGE_SPECIAL	(1ULL << _PAGE_BIT_SPECIAL)
#define _PAGE_CPA_TEST	(1ULL << _PAGE_BIT_CPA_TEST)
#define _PAGE_PKEY_BIT0	(1ULL << _PAGE_BIT_PKEY_BIT0)
#define _PAGE_PKEY_BIT1	(1ULL << _PAGE_BIT_PKEY_BIT1)
#define _PAGE_PKEY_BIT2	(1ULL << _PAGE_BIT_PKEY_BIT2)
#define _PAGE_PKEY_BIT3	(1ULL << _PAGE_BIT_PKEY_BIT3)
#define _PAGE_NX	(1ULL << _PAGE_BIT_NX)

#define __PP _PAGE_PRESENT
#define __RW _PAGE_RW
#define _USR _PAGE_USER
#define ___A _PAGE_ACCESSED
#define ___D _PAGE_DIRTY
#define ___G _PAGE_GLOBAL
#define __NX _PAGE_NX

#define _PAGE_TABLE		 (__PP|__RW|_USR|___A|   0|___D|   0|   0|   0)

#define PAGE_TABLE_LARGE (_PAGE_TABLE | _PAGE_PSE)
#define PTE (__PP|__RW|_USR|___A|   0|___D|   0|   0|__NX)
