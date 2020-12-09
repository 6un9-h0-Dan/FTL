/* Pi-hole: A black hole for Internet advertisements
*  (c) 2020 Pi-hole, LLC (https://pi-hole.net)
*  Network-wide ad blocking via your own hardware.
*
*  FTL Engine
*  Pi-hole syscall implementation for realloc
*
*  This file is copyright under the latest version of the EUPL.
*  Please see LICENSE file for your rights under this license. */

#include "../FTL.h"
//#include "syscalls.h" is implicitly done in FTL.h
#include "../log.h"

#undef realloc
void __attribute__((alloc_size(2))) *FTLrealloc(void *ptr_in, const size_t size, const char * file, const char * function, const int line)
{
	// The FTLrealloc() function changes the size of the memory block pointed to
	// by ptr to size bytes. The contents will be unchanged in the range from
	// the start of the region up to the minimum of the old and new sizes. If
	// the new size is larger than the old size, the added memory will not be
	// initialized. If ptr is NULL, then the call is equivalent to malloc(size),
	// for all values of size; if size is equal to zero, and ptr is
	// not NULL, then the call is equivalent to free(ptr). Unless ptr is
	// NULL, it must have been returned by an earlier call to malloc(), cal‐
	// loc() or realloc(). If the area pointed to was moved, a free(ptr) is
	// done.
	void *ptr_out = realloc(ptr_in, size);
	if(ptr_out == NULL)
		logg("FATAL: Memory reallocation (%p -> %zu) failed in %s() (%s:%i)",
		     ptr_in, size, function, file, line);

	return ptr_out;
}