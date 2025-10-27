/**
 * @file menu_lib.c
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "menu_lib.h"
#include "menu.h"
#include "menu_screen_driver_interface.h"
#include <string.h>

#ifndef UNIT_TESTS
#define PRIVATE static
#else
#define PRIVATE
#endif

#define ADDITIONAL_SPACE_CHAR_QTY 2

PRIVATE uint8_t menu_number_of_chars_per_line;
PRIVATE uint8_t menu_number_of_screen_lines;

static menu_t *current_menu_pointer;
static menu_t *menu_item_2_print = NULL;
static menu_t *menu_1st_item = NULL;

static uint8_t cursor_selection_menu_index[MAX_MENU_DEPTH];
static uint8_t cursor_row_position[MAX_MENU_DEPTH]; // depand
static uint8_t menu_level;

PRIVATE const struct menu_screen_driver_interface_struct *DISPLAY = NULL;
static menu_exit_cb_t menu_top_level_exit_cb = NULL;

static const char *default_header = {" MENU "};
static const char *custom_header = NULL;

static void display_menu_header(void);
static void display_main_menu_header(void);
static void display_sub_menu_header(void);
static void fill_header_with_dashes(void);
static void clear_current_menu_view_with_cursor(void);
static void update_menu_item_2_ptrint(void);
static void update_current_menu_view_with_cursor(void);

void menu_init(void)
{
    DISPLAY = get_menu_display_driver_interface();
    menu_number_of_chars_per_line = DISPLAY->get_number_of_chars_per_line();
    menu_number_of_screen_lines = DISPLAY->get_number_of_screen_lines();
    // add function for defining max submenu_level nad error handling if menu_depth is to low?
}

void menu_view_init(menu_t *menu_entry_point, menu_exit_cb_t menu_exit_cb, const char *meun_header) // zmian nazwy na enable menu view
{
    current_menu_pointer = menu_entry_point;
    menu_1st_item = menu_entry_point;
    menu_level = 0;
    cursor_selection_menu_index[menu_level] = 0;
    cursor_row_position[menu_level] = 0;
    menu_top_level_exit_cb = menu_exit_cb;
    custom_header = meun_header;
    update_screen_view();
}

void menu_next(void)
{
    if (current_menu_pointer->next != NULL)
    {
        current_menu_pointer = current_menu_pointer->next;
        cursor_selection_menu_index[menu_level]++; // ToDo maybe it can be replaced with function that calculate current index base on current pointer and entry point and menu level
        if (cursor_row_position[menu_level] < (menu_number_of_screen_lines - 2))
        {
            cursor_row_position[menu_level]++;
        }
        update_screen_view();
    }
}

void menu_prev(void)
{
    if (current_menu_pointer->prev != NULL)
    {
        current_menu_pointer = current_menu_pointer->prev;
        cursor_selection_menu_index[menu_level]--; // ToDo maybe it can be replaced with function that calculate current index base on current pointer and entry point and menu level
        if (cursor_row_position[menu_level] != 0)
        {
            cursor_row_position[menu_level]--;
        }
        update_screen_view();
    }
}

void menu_enter(void)
{
    if ((current_menu_pointer->child) != NULL)
    {
        menu_level++;
        if (menu_level < (MAX_MENU_DEPTH)) // protection agains going out of table range -> ToDo need to be better managed
        {
            current_menu_pointer = current_menu_pointer->child;
            cursor_selection_menu_index[menu_level] = 0;
            cursor_row_position[menu_level] = 0;
        }
        else
        {
            menu_level--;
        }
        update_screen_view();
    }
    else
    {
        if ((current_menu_pointer->callback) != NULL)
        {
            current_menu_pointer->callback();
        }
    }
}
void menu_esc(void)
{
    if ((current_menu_pointer->parent) != NULL)
    {
        menu_level--;
        current_menu_pointer = current_menu_pointer->parent;
        update_screen_view();
    }
    else
    {
        if (menu_top_level_exit_cb != NULL)
        {
            menu_top_level_exit_cb();
        }
    }
}

void update_screen_view(void)
{
    display_menu_header();
    clear_current_menu_view_with_cursor();
    update_menu_item_2_ptrint();
    update_current_menu_view_with_cursor();
}

menu_t *get_current_menu_position(void)
{
    return current_menu_pointer;
}

static void display_menu_header(void)
{
    fill_header_with_dashes();

    if (current_menu_pointer->parent == NULL)
    {
        display_main_menu_header();
    }
    else
    {
        display_sub_menu_header();
    }
}
static void display_main_menu_header(void)
{
    uint8_t column;
    const char *header_2_display;
    if (custom_header == NULL)
    {
        column = 7;
        header_2_display = default_header;
    }
    else
    {
        column = (menu_number_of_chars_per_line - strlen(custom_header)) / 2;
        header_2_display = custom_header;
        // custom_header = NULL;
    }
    DISPLAY->cursor_position(0, column);
    DISPLAY->print_string(header_2_display);
    menu_item_2_print = menu_1st_item;
}
static void display_sub_menu_header(void)
{
    uint8_t header_str_len = strlen(current_menu_pointer->parent->name);
    header_str_len = header_str_len + ADDITIONAL_SPACE_CHAR_QTY;
    uint8_t header_start_position = (menu_number_of_chars_per_line - header_str_len) / 2;
    DISPLAY->cursor_position(0, header_start_position);
    DISPLAY->print_char(' ');
    DISPLAY->print_string(current_menu_pointer->parent->name);
    DISPLAY->print_char(' ');
    // set first item for current sub menu
    menu_item_2_print = current_menu_pointer->parent->child;
}

static void fill_header_with_dashes(void)
{
    DISPLAY->cursor_position(0, 0);
    for (uint8_t i = 0; i < menu_number_of_chars_per_line; i++)
    {
        DISPLAY->print_char('-');
    }
}

static void clear_current_menu_view_with_cursor(void)
{
    DISPLAY->cursor_position(1, 0);
    for (uint8_t i = 1; i < menu_number_of_screen_lines; i++)
    {
        for (uint8_t j = 0; j < menu_number_of_chars_per_line; j++)
        {
            DISPLAY->print_char(' ');
        }
    }
}

static void update_menu_item_2_ptrint(void)
{
    uint8_t print_offset = cursor_selection_menu_index[menu_level] - cursor_row_position[menu_level];
    for (uint8_t i = 0; i < print_offset; i++)
    {
        menu_item_2_print = menu_item_2_print->next;
    }
}

static void update_current_menu_view_with_cursor(void)
{

    for (uint8_t i = 1; i < menu_number_of_screen_lines; i++)
    {
        // update cursor position
        DISPLAY->cursor_position(i, 0);
        if (i == cursor_row_position[menu_level] + 1)
        {
            DISPLAY->print_char(62);
        }
        // update curent menu view
        DISPLAY->cursor_position(i, 1);
        DISPLAY->print_string(menu_item_2_print->name);
        menu_item_2_print = menu_item_2_print->next;
        if (NULL == menu_item_2_print)
        {
            break;
        }
    }
}