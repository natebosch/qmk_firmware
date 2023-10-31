#include "quantum.h"

#ifdef OLED_ENABLE
static void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("qwerty"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("LOWER"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("RAISE"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("ADJUST"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

bool oled_task_user(void) {
    render_status();
    return false;
}
#endif
