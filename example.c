#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "rusty_enum.h"

RUSTY_ENUM(IpAddr, V4, V6)
RUSTY_ENUM_FIELDS(V4, uint8_t, uint8_t, uint8_t, uint8_t)
RUSTY_ENUM_FIELDS(V6, const char *)
RUSTY_ENUM_END(IpAddr); // neovim _really_ hates it when there is no semicolon here for some reason

int main()
{
    IpAddr addr = RUSTY_ENUM_NEW(IpAddr, V4, 192, 168, 1, 0);

    switch (addr.kind) {
        case V4: {
            uint8_t a = RUSTY_ENUM_GET(addr, V4, 0);
            uint8_t b = addr.V4._0;
            assert(a == b);
            break;
        }
        case V6:
            assert(0 && "not implemented");
    }

    puts("assertions have been asserted");
}
