#ifndef PLUSH_ENTITY_STATUS
#define PLUSH_ENTITY_STATUS

namespace PLUSH {
    struct EntityStatus{
        bool visible = false;
        int ID = 0;
        float time = 0.0f;
        float duration = 0.0f;
        float duration2 = 0.0f;
        int mode = 0;
        int orientation = 0;
        unsigned int count = 0;
    };
}

#endif