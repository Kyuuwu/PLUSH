#ifndef PLUSH_HELPERS_KEYSTATUS
#define PLUSH_HELPERS_KEYSTATUS

namespace PLUSH_helpers {
    enum KeyStatus{
        RELEASED,
        JUST_RELEASED,
        PRESSED,
        JUST_PRESSED
    };

    enum Key{
        KEY_ESCAPE,
        KEY_SPACE,
        KEY_RIGHT,
        KEY_LEFT,
        KEY_UP,
        KEY_DOWN, // 6
        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z // 26
    };

    const unsigned int num_keys = 32;

    struct KeyboardStatus{
        KeyStatus keystatus[num_keys];
    };

    struct MouseStatus{
        bool LEFT_MOUSE_PRESSED = false;
        bool RIGHT_MOUSE_PRESSED = false;
    };
}

#endif