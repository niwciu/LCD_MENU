/**
 * @file menu_screen_driver_interface.h
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */
/**
 * @file menu_lib.h
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _MENU_SCREEN_DRIVER_INTERFACE_
#define _MENU_SCREEN_DRIVER_INTERFACE_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
#include <stdint.h>

    typedef void (*menu_void_func_ptr)(void);
    typedef uint8_t (*get_screen_size_func_ptr)(void);
    typedef void (*screen_position_func_ptr)(uint8_t row, uint8_t column);
    typedef void (*print_string_func_ptr)(const char *string);
    typedef void (*print_string_char_ptr)(const char character);

    struct menu_screen_driver_interface_struct
    {
        menu_void_func_ptr screen_init;
        get_screen_size_func_ptr get_number_of_screen_lines;
        get_screen_size_func_ptr get_number_of_chars_per_line;
        menu_void_func_ptr clr_scr;
        screen_position_func_ptr cursor_position;
        print_string_func_ptr print_string;
        print_string_char_ptr print_char;
    };

    const struct menu_screen_driver_interface_struct *get_menu_display_driver_interface(void);
/**@}*/
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _MENU_SCREEN_DRIVER_INTERFACE_ */
