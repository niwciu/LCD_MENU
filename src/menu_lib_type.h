/**
 * @file menu_lib_type.h
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @version 1.0.0
 * @date 2025-02-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef _MENU_LIB_TYPE_
#define _MENU_LIB_TYPE_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    /**
     * @brief Represents a single menu item in a hierarchical menu system.
     *
     * Each menu item is part of a doubly linked list on the same menu level
     * and can optionally point to a submenu (child) or its parent menu for multi-level navigation.
     * A callback function can be assigned to a menu item to execute specific functionality
     * when the item is selected.
     */
    typedef struct menu_t
    {
        const char *name;       /**< Name of the menu item (displayed on the screen). */
        struct menu_t *next;    /**< Pointer to the next menu item on the same level. */
        struct menu_t *prev;    /**< Pointer to the previous menu item on the same level. */
        struct menu_t *child;   /**< Pointer to the submenu (child menu) of this item. */
        struct menu_t *parent;  /**< Pointer to the parent menu of this item. */
        void (*callback)(void); /**< Callback function executed when the menu item is selected. */
    } menu_t;

/**@}*/
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _MENU_LIB_TYPE_ */