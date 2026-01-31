
#include <stdio.h>
#include "ephemeron.h"

int main() {
    ephemeron_arena_ptr arena = ephemeron_create(128);
    ephemeron_alloc(arena, 1024);
    ephemeron_alloc(arena, 1024);
    ephemeron_alloc(arena, 1024);
    ephemeron_alloc(arena, 1024);
    ephemeron_alloc(arena, 1024);

    ephemeron_clear(arena);
    ephemeron_alloc(arena, 1024);
    ephemeron_alloc(arena, 1024);

    ephemeron_destroy(arena);
}
