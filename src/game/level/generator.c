#include <stdlib.h>
#include <string.h>

#include "generator.h"

static void _split_room(vec2 room, vec2* rooms, bool h)
{

}

void generate_rooms(void)
{
    room rooms[MIN_ROOMS + (rand() % (MAX_ROOMS - MIN_ROOMS + 1))];
}