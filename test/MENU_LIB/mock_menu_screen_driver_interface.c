/**
 * @file mock_menu_screen_driver_interface.c
 * @author niwciu (niwciu@gmail.com)
 * @brief
 * @date 2025-01-27
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "menu_screen_driver_interface.h"
#include "mock_menu_screen_driver_interface.h"
#include <string.h>

char mock_lcd_screen[LCD_Y][LCD_X];
char mock_lcd_string_lines[LCD_Y][LCD_X + 1] = {'\0'};
char *mock_screen_lines[LCD_Y];
uint8_t mock_cur_lcd_x;
uint8_t mock_cur_lcd_y;

mock_menu_screen_init_status_e mock_menu_screen_init_status = MENU_SCREEN_INIT_UNKNOWN;
const struct menu_screen_driver_interface_struct *mock_driver_ptr = NULL;

static void mock_screen_init(void);
static uint8_t get_number_of_screen_lines(void);
static uint8_t get_number_of_chars_per_line(void);
static void mock_clr_scr(void);
static void mock_cursor_position(uint8_t row, uint8_t column);
static void mock_print_string(const char *str);
static void mock_print_char(const char C);

static void mock_copy_screen_char_table_2_scree_string_line_table(void);
static void update_current_mock_lcd_cursor_position(void);

const struct menu_screen_driver_interface_struct mock_menu_screen_incomplete_driver_interface = {0};
const struct menu_screen_driver_interface_struct mock_menu_screen_driver_interface = {
    mock_screen_init,
    get_number_of_screen_lines,
    get_number_of_chars_per_line,
    mock_clr_scr,
    mock_cursor_position,
    mock_print_string,
    mock_print_char,
};

const struct menu_screen_driver_interface_struct *get_menu_display_driver_interface(void)
{
    return mock_driver_ptr;
}

static void mock_screen_init(void)
{
    mock_menu_screen_init_status = MENU_SCREEN_INIT_OK;
}

static uint8_t get_number_of_screen_lines(void)
{
    return LCD_Y;
}
static uint8_t get_number_of_chars_per_line(void)
{
    return LCD_X;
}

static void mock_clr_scr(void)
{
    char *lcd_cur_pos_ptr = &mock_lcd_screen[0][0];
    for (uint8_t i = 0; i < (LCD_X * LCD_Y); i++)
    {
        *(lcd_cur_pos_ptr + i) = ' ';
    }
    mock_copy_screen_char_table_2_scree_string_line_table();
}
static void mock_cursor_position(uint8_t row, uint8_t column)
{
    mock_cur_lcd_x = column;
    mock_cur_lcd_y = row;
}
static void mock_print_string(const char *str)
{
    char *lcd_cur_pos_ptr = &mock_lcd_screen[mock_cur_lcd_y][mock_cur_lcd_x];
    const char *char_ptr = str;
    uint8_t len = strlen(str);
    for (uint8_t i = 0; i < len; i++)
    {

        if ((lcd_cur_pos_ptr) > (&mock_lcd_screen[LCD_Y - 1][LCD_X - 1]))
        {
            lcd_cur_pos_ptr = &mock_lcd_screen[0][0];
        }
        *(lcd_cur_pos_ptr) = *(char_ptr);
        lcd_cur_pos_ptr++;
        char_ptr++;
        update_current_mock_lcd_cursor_position();
    }
    mock_copy_screen_char_table_2_scree_string_line_table();
}
static void mock_print_char(const char C)
{
    mock_lcd_screen[mock_cur_lcd_y][mock_cur_lcd_x] = C;
    mock_copy_screen_char_table_2_scree_string_line_table();
    update_current_mock_lcd_cursor_position();
}

static void mock_copy_screen_char_table_2_scree_string_line_table(void)
{
    for (uint8_t i = 0; i < LCD_Y; i++)
    {
        for (uint8_t j = 0; j < LCD_X; j++)
        {
            mock_lcd_string_lines[i][j] = mock_lcd_screen[i][j];
        }
    }
    for (int i = 0; i < LCD_Y; i++)
    {
        mock_screen_lines[i] = mock_lcd_string_lines[i];
        mock_screen_lines[i][20] = '\0';
    }
}

static void update_current_mock_lcd_cursor_position(void)
{
    mock_cur_lcd_x++;
    if (mock_cur_lcd_x > (LCD_X - 1))
    {
        mock_cur_lcd_x = 0;
        mock_cur_lcd_y++;
        if (mock_cur_lcd_y > (LCD_Y - 1))
            mock_cur_lcd_y = 0;
    }
}

void init_mock_screen_driver(void)
{
    mock_driver_ptr = &mock_menu_screen_driver_interface;
}

void deinit_mock_screen_driver(void)
{
    mock_driver_ptr = NULL;
}

void init_mock_incomplete_screen_driver(void)
{
    mock_driver_ptr = &mock_menu_screen_incomplete_driver_interface;
}