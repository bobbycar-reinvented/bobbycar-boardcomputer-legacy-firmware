#include "lock.h"

namespace bobbyicons {
const espgui::Icon<24, 24> lock {{
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4108, 0xe318, 0x8631, 0x8631, 0xe318, 0x2000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x4529, 0xae73, 0xf39c, 0x96b5, 0x96b5, 0x14a5, 0xae73, 0x2421, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xe739, 0xf39c, 0xb6b5, 0x75ad, 0x14a5, 0x14a5, 0x75ad, 0x75ad, 0x14a5,
    0xe739, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2421, 0xd39c,
    0x75ad, 0x718c, 0x694a, 0xe318, 0xe318, 0x2842, 0x1084, 0x14a5, 0xf39c, 0x4529, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2000, 0x4d6b, 0x96b5, 0xb294, 0x6529, 0x0000, 0x0000, 0x0000, 0x0000, 0x2421, 0x518c,
    0x96b5, 0x8e73, 0x2000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4108, 0x9294, 0x55ad,
    0xaa52, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x694a, 0x55ad, 0xf39c, 0x6108, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6108, 0x14a5, 0x14a5, 0x4529, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4529,
    0x14a5, 0x55ad, 0x8210, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8210, 0x34a5, 0xf39c,
    0x2421, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2421, 0xd39c, 0x75ad, 0x8210, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x8210, 0x34a5, 0x14a5, 0x4529, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4529,
    0xf39c, 0x75ad, 0x8210, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4108, 0x35a5, 0x55ad,
    0x4529, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x4529, 0x34a5, 0x75ad, 0x6108, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x8231, 0x667b, 0x70c5, 0x50bd, 0x0873, 0x0452, 0xe451, 0xc349, 0xa349, 0xc349, 0x0452, 0xe872,
    0x30b5, 0x91c5, 0x887b, 0x6331, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0573, 0xaaf6, 0x45ee, 0xa3e5,
    0x43d5, 0xc3c4, 0x63bc, 0x23b4, 0x43b4, 0x83c4, 0xc3cc, 0x43d5, 0x03e6, 0xe9f6, 0x10ef, 0xe662, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x056b, 0xc9f6, 0x63f6, 0xe0ed, 0x60e5, 0xe0d4, 0xa0cc, 0xa0cc, 0xc0cc, 0xe0d4, 0x20dd, 0xa0e5,
    0x60f6, 0x48ff, 0x30ef, 0xc662, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x056b, 0xc9f6, 0x83f6, 0xe0ed,
    0x80e5, 0x00d5, 0xc0cc, 0xa0cc, 0xc0d4, 0x00d5, 0x20dd, 0xa0ed, 0x60f6, 0x48ff, 0x30ef, 0xc662, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x056b, 0xc9f6, 0x83f6, 0xe0ed, 0x80e5, 0x00d5, 0xc0cc, 0xa0cc, 0xc0d4, 0x00d5, 0x20dd, 0xa0e5,
    0x60f6, 0x48ff, 0x30ef, 0xc662, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x056b, 0xc9f6, 0x83f6, 0xe0ed,
    0x80e5, 0x00d5, 0xa0cc, 0xa0cc, 0xe0d4, 0x00d5, 0x20dd, 0xc0ed, 0x60f6, 0x48ff, 0x30ef, 0xc662, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x056b, 0xc9f6, 0x63f6, 0xe0ed, 0x80e5, 0x00d5, 0xc0cc, 0xc0cc, 0xe0d4, 0x00dd, 0x40dd, 0xa0e5,
    0x60f6, 0x48ff, 0x30ef, 0xc662, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x056b, 0xc9f6, 0x83f6, 0x00f6,
    0x80e5, 0x00d5, 0xc0cc, 0xc0cc, 0xe0d4, 0x00dd, 0x40e5, 0xc0ed, 0x60f6, 0x48ff, 0x30ef, 0xc662, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x056b, 0xc9f6, 0x83f6, 0x00f6, 0x80e5, 0x00d5, 0xa0cc, 0xa0cc, 0xe0d4, 0x00dd, 0x40dd, 0xc0ed,
    0x60f6, 0x48ff, 0x30ef, 0xc662, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x056b, 0xc9f6, 0x83f6, 0xe0f5,
    0x80e5, 0x00d5, 0xc0cc, 0xc0cc, 0xe0d4, 0x00dd, 0x40dd, 0xc0ed, 0x60f6, 0x48ff, 0x30ef, 0xc662, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x056b, 0xc9f6, 0x83f6, 0x00f6, 0x80e5, 0x20d5, 0xc0cc, 0xc0cc, 0x00d5, 0x20dd, 0x40e5, 0xc0ed,
    0x80f6, 0x48ff, 0x30ef, 0xc662, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x2573, 0xc9f6, 0x83f6, 0x00f6,
    0x80e5, 0x20d5, 0xe0cc, 0xe0cc, 0x00d5, 0x20dd, 0x40e5, 0xc0ed, 0x80fe, 0x68ff, 0x30ef, 0xe662, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x8231, 0x647b, 0x217b, 0xe07a, 0xc072, 0x806a, 0x6062, 0x6062, 0x606a, 0x806a, 0xa072, 0xe072,
    0x207b, 0xa47b, 0x8873, 0x6331, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

}, "lock"};
} // namespace bobbyicons

