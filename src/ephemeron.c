
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ephemeron.h"

#define BLOCK_SIZE 4096

/* head block within a memory arena. the payload zone follows directly */
struct ephemeron_arena {
    size_t size;
    size_t used;
    void *start; /* cache to save some address computations */
    struct ephemeron_arena *next;
};

ephemeron_arena_ptr ephemeron_create(size_t size) {
    size = ((size + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;

    fprintf(stderr, "EPHEMERON: creating arena of %lu size\n", (unsigned long)size);
    /* FIXME: we could do fancy optimizations, eg. better size alignment, etc */
    ephemeron_arena_ptr arena = calloc(1, sizeof(struct ephemeron_arena) + size);
    if (!arena)
        return NULL;

    arena->size = size;
    arena->start = &arena[1];

    return arena;
}

void ephemeron_destroy(ephemeron_arena_ptr arena) {
    if (arena == NULL)
        return;

    fprintf(stderr, "EPHEMERON: destroying arena\n");
    ephemeron_destroy(arena->next);
    free(arena);
}

void ephemeron_clear(ephemeron_arena_ptr arena) {
    if (arena == NULL)
        return;

    fprintf(stderr, "EPHEMERON: clearing arena\n");
    ephemeron_clear(arena->next);
    arena->start = &arena[1];
    memset(&arena[1], 0, arena->used);
    arena->used = 0;
}

void *ephemeron_alloc(ephemeron_arena_ptr arena, size_t size) {
    if (arena == NULL)
        return NULL;

    fprintf(stderr, "EPHEMERON: allocating %lu bytes\n", (unsigned long)size);
    /* try to allocate here */
    if ((arena->size - arena->used) >= size) {
        void *ptr = arena->start;
        arena->used += size;
        return ptr;
    }

    /* try next one if we have it */
    if (arena->next)
        return ephemeron_alloc(arena->next, size);

    /* out of heap ... we need to grow */
    arena->next = ephemeron_create(size);
    return ephemeron_alloc(arena->next, size);
}
