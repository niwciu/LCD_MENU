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
#include <stdint.h>

    void menu_init(void);
    void menu_view_init(menu_t *menu_to_enter);
    void menu_next(void);
    void menu_prev(void);
    void menu_enter(void);
    void menu_esc(void);

/**@}*/
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _MENU_LIB_ */
