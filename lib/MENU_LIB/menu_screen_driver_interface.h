/**
 * @file menu_screen_driver_interface.h
 * @author niwciu
 * @brief Abstraction layer for menu display drivers.
 * @date 2025-01-27
 *
 * Provides function pointers for screen initialization, clearing,
 * cursor positioning, and printing strings or characters.
 *
 * @ingroup MenuLib
 * @{
 */

#ifndef _MENU_SCREEN_DRIVER_INTERFACE_
#define _MENU_SCREEN_DRIVER_INTERFACE_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

    /**
     * @brief Function pointer type for void functions with no parameters.
     */
    typedef void (*menu_void_func_ptr)(void);

    /**
     * @brief Function pointer type returning a uint8_t (e.g., screen size).
     */
    typedef uint8_t (*get_screen_size_func_ptr)(void);

    /**
     * @brief Function pointer type for setting cursor position.
     * @param row Row index on the screen
     * @param column Column index on the screen
     */
    typedef void (*screen_position_func_ptr)(uint8_t row, uint8_t column);

    /**
     * @brief Function pointer type for printing a string.
     * @param string Null-terminated string to print
     */
    typedef void (*print_string_func_ptr)(const char *string);

    /**
     * @brief Function pointer type for printing a single character.
     * @param character Character to print
     */
    typedef void (*print_char_func_ptr)(const char character);

    /**
     * @brief Interface struct containing display driver function pointers.
     *
     * Provides abstraction for menu rendering and screen manipulation.
     */
    struct menu_screen_driver_interface_struct
    {
        menu_void_func_ptr screen_init;                        /**< Initialize the screen */
        get_screen_size_func_ptr get_number_of_screen_lines;   /**< Get number of screen lines */
        get_screen_size_func_ptr get_number_of_chars_per_line; /**< Get number of chars per line */
        menu_void_func_ptr clr_scr;                            /**< Clear screen */
        screen_position_func_ptr cursor_position;              /**< Set cursor position */
        print_string_func_ptr print_string;                    /**< Print null-terminated string */
        print_char_func_ptr print_char;                        /**< Print single character */
    };

    /**
     * @brief Get pointer to the currently active display driver interface.
     *
     * @return Pointer to a constant menu_screen_driver_interface_struct
     */
    const struct menu_screen_driver_interface_struct *get_menu_display_driver_interface(void);

    /** @} */ /* end of MenuLib group */

#ifdef __cplusplus
}
#endif

#endif /* _MENU_SCREEN_DRIVER_INTERFACE_ */
