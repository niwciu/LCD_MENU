/**
 * @file menu_lib.h
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _MENU_LIB_
#define _MENU_LIB_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "menu.h"
// #include "menu_lib_type.h"
#include <stdint.h>

    typedef void (*menu_exit_cb_t)(void);

    void menu_init(void);
    void menu_view_init(menu_t *menu_to_enter, menu_exit_cb_t menu_exit_cb, const char *custom_meun_header);
    void menu_next(void);
    void menu_prev(void);
    void menu_enter(void);
    void menu_esc(void);
    void update_screen_view(void);

    menu_t *get_current_menu_position(void);

/**@}*/
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _MENU_LIB_ */
