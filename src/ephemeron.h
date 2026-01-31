#ifndef __MTX_EPHEMERON_H
#define __MTX_EPHEMERON_H

#include <stddef.h>

/* used for retrieving stats */
struct ephemeron_stat {
    size_t size;
    size_t used;
};

struct ephemeron_arena;
typedef struct ephemeron_arena *ephemeron_arena_ptr;

/* create a new arena with at least `size` bytes preallocated arena space. */
ephemeron_arena_ptr ephemeron_create(size_t size);

/* allocate a chunk of given size. arena grows if necessary */
void *ephemeron_alloc(ephemeron_arena_ptr arena, size_t size);

/* totally destroy arena. all allocated memory is gone. */
void ephemeron_destroy(ephemeron_arena_ptr arena);

/* clear out arena, but leave preallocated space in place */
void ephemeron_clear(ephemeron_arena_ptr arena);

#endif /* __MTX_EPHEMERON_H */
