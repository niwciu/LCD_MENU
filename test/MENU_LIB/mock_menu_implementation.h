#include "menu_lib_type.h"

#pragma once

#define MAX_MENU_DEPTH 4

typedef enum
{
    CB_STATUS_UNKNOWN,
    CB_EXECUTED,
} mock_cb_status_e;

extern mock_cb_status_e mock_menu_callback_status;
extern mock_cb_status_e mock_menu_top_level_exit_cb_status;

extern menu_t mock_menu_1;
extern menu_t mock_sub_menu_1_1;
extern menu_t mock_sub_menu_1_2;
extern menu_t mock_sub_menu_1_3;
extern menu_t mock_sub_menu_1_4;
extern menu_t mock_menu_2;
extern menu_t mock_sub_menu_2_1;
extern menu_t mock_sub_menu_2_1_1;
extern menu_t mock_sub_menu_2_1_1_1;
extern menu_t mock_sub_menu_2_1_1_2;
extern menu_t mock_sub_menu_2_1_1_3;
extern menu_t mock_sub_menu_2_1_1_4;
extern menu_t mock_sub_menu_2_1_2;
extern menu_t mock_sub_menu_2_1_3;
extern menu_t mock_sub_menu_2_1_3_1;
extern menu_t mock_sub_menu_2_1_3_2;
extern menu_t mock_sub_menu_2_1_3_3;
extern menu_t mock_sub_menu_2_1_3_4;
extern menu_t mock_sub_menu_2_1_4;
extern menu_t mock_sub_menu_2_2;
extern menu_t mock_sub_menu_2_3;
extern menu_t mock_sub_menu_2_4;
extern menu_t mock_menu_3;
extern menu_t mock_sub_menu_3_1;
extern menu_t mock_sub_menu_3_2;
extern menu_t mock_sub_menu_3_3;
extern menu_t mock_sub_menu_3_4;
extern menu_t mock_menu_4;
extern menu_t mock_sub_menu_4_1;
extern menu_t mock_sub_menu_4_2;
extern menu_t mock_sub_menu_4_3;
extern menu_t mock_sub_menu_4_4;
extern menu_t mock_menu_5;

void mock_set_callback_status_to_unknown(void);
void set_top_level_exit_cb_status_to_unknown(void);
void mock_menu_top_level_exit_callback(void);