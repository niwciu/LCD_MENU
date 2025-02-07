#include "menu.h"

#include <stddef.h>

mock_cb_status_e mock_menu_callback_status = CB_STATUS_UNKNOWN;

static void mock_menu_1_1_callback(void);
static void mock_menu_1_2_callback(void);
static void mock_menu_1_3_callback(void);
static void mock_menu_1_4_callback(void);

static void mock_menu_2_1_1_1_callback(void);
static void mock_menu_2_1_1_2_callback(void);
static void mock_menu_2_1_1_3_callback(void);
static void mock_menu_2_1_1_4_callback(void);

static void mock_menu_2_1_2_callback(void);

static void mock_menu_2_1_3_1_callback(void);
static void mock_menu_2_1_3_2_callback(void);
static void mock_menu_2_1_3_3_callback(void);
static void mock_menu_2_1_3_4_callback(void);

static void mock_menu_2_1_4_callback(void);

static void mock_menu_2_2_callback(void);
static void mock_menu_2_3_callback(void);
static void mock_menu_2_4_callback(void);

static void mock_menu_3_1_callback(void);
static void mock_menu_3_2_callback(void);
static void mock_menu_3_3_callback(void);
static void mock_menu_3_4_callback(void);

static void mock_menu_4_1_callback(void);
static void mock_menu_4_2_callback(void);
static void mock_menu_4_3_callback(void);
static void mock_menu_4_4_callback(void);

static void set_callback_status_to_called(void);

menu_t mock_menu_1 = {"menu_1", &mock_menu_2, NULL, &mock_sub_menu_1_1, NULL, NULL};
menu_t mock_sub_menu_1_1 = {"menu_1_1", &mock_sub_menu_1_2, NULL, NULL, &mock_menu_1, mock_menu_1_1_callback};
menu_t mock_sub_menu_1_2 = {"menu_1_2", &mock_sub_menu_1_3, &mock_sub_menu_1_1, NULL, &mock_menu_1, mock_menu_1_2_callback};
menu_t mock_sub_menu_1_3 = {"menu_1_3", &mock_sub_menu_1_4, &mock_sub_menu_1_2, NULL, &mock_menu_1, mock_menu_1_3_callback};
menu_t mock_sub_menu_1_4 = {"menu_1_4", NULL, &mock_sub_menu_1_3, NULL, &mock_menu_1, mock_menu_1_4_callback};
menu_t mock_menu_2 = {"menu_2", &mock_menu_3, &mock_menu_1, &mock_sub_menu_2_1, NULL, NULL};
menu_t mock_sub_menu_2_1 = {"menu_2_1", &mock_sub_menu_2_2, NULL, &mock_sub_menu_2_1_1, &mock_menu_2, NULL};
menu_t mock_sub_menu_2_1_1 = {"menu_2_1_1", &mock_sub_menu_2_1_2, NULL, &mock_sub_menu_2_1_1_1, &mock_sub_menu_2_1, NULL};
menu_t mock_sub_menu_2_1_1_1 = {"menu_2_1_1_1", &mock_sub_menu_2_1_1_2, NULL, NULL, &mock_sub_menu_2_1_1, mock_menu_2_1_1_1_callback};
menu_t mock_sub_menu_2_1_1_2 = {"menu_2_1_1_2", &mock_sub_menu_2_1_1_3, &mock_sub_menu_2_1_1_1, NULL, &mock_sub_menu_2_1_1, mock_menu_2_1_1_2_callback};
menu_t mock_sub_menu_2_1_1_3 = {"menu_2_1_1_3", &mock_sub_menu_2_1_1_4, &mock_sub_menu_2_1_1_2, NULL, &mock_sub_menu_2_1_1, mock_menu_2_1_1_3_callback};
menu_t mock_sub_menu_2_1_1_4 = {"menu_2_1_1_4", NULL, &mock_sub_menu_2_1_1_3, NULL, &mock_sub_menu_2_1_1, mock_menu_2_1_1_4_callback};
menu_t mock_sub_menu_2_1_2 = {"menu_2_1_2", &mock_sub_menu_2_1_3, &mock_sub_menu_2_1_1, NULL, &mock_sub_menu_2_1, mock_menu_2_1_2_callback};
menu_t mock_sub_menu_2_1_3 = {"menu_2_1_3", &mock_sub_menu_2_1_4, &mock_sub_menu_2_1_2, &mock_sub_menu_2_1_3_1, &mock_sub_menu_2_1, NULL};
menu_t mock_sub_menu_2_1_3_1 = {"menu_2_1_3_1", &mock_sub_menu_2_1_3_2, NULL, NULL, &mock_sub_menu_2_1_3, mock_menu_2_1_3_1_callback};
menu_t mock_sub_menu_2_1_3_2 = {"menu_2_1_3_2", &mock_sub_menu_2_1_3_3, &mock_sub_menu_2_1_3_1, NULL, &mock_sub_menu_2_1_3, mock_menu_2_1_3_2_callback};
menu_t mock_sub_menu_2_1_3_3 = {"menu_2_1_3_3", &mock_sub_menu_2_1_3_4, &mock_sub_menu_2_1_3_2, NULL, &mock_sub_menu_2_1_3, mock_menu_2_1_3_3_callback};
menu_t mock_sub_menu_2_1_3_4 = {"menu_2_1_3_4", NULL, &mock_sub_menu_2_1_3_3, NULL, &mock_sub_menu_2_1_3, mock_menu_2_1_3_4_callback};
menu_t mock_sub_menu_2_1_4 = {"menu_2_1_4", NULL, &mock_sub_menu_2_1_3, NULL, &mock_sub_menu_2_1, mock_menu_2_1_4_callback};
menu_t mock_sub_menu_2_2 = {"menu_2_2", &mock_sub_menu_2_3, &mock_sub_menu_2_1, NULL, &mock_menu_2, mock_menu_2_2_callback};
menu_t mock_sub_menu_2_3 = {"menu_2_3", &mock_sub_menu_2_4, &mock_sub_menu_2_2, NULL, &mock_menu_2, mock_menu_2_3_callback};
menu_t mock_sub_menu_2_4 = {"menu_2_4", NULL, &mock_sub_menu_2_3, NULL, &mock_menu_2, mock_menu_2_4_callback};
menu_t mock_menu_3 = {"menu_3", &mock_menu_4, &mock_menu_2, &mock_sub_menu_3_1, NULL, NULL};
menu_t mock_sub_menu_3_1 = {"menu_3_1", &mock_sub_menu_3_2, NULL, NULL, &mock_menu_3, mock_menu_3_1_callback};
menu_t mock_sub_menu_3_2 = {"menu_3_2", &mock_sub_menu_3_3, &mock_sub_menu_3_1, NULL, &mock_menu_3, mock_menu_3_2_callback};
menu_t mock_sub_menu_3_3 = {"menu_3_3", &mock_sub_menu_3_4, &mock_sub_menu_3_2, NULL, &mock_menu_3, mock_menu_3_3_callback};
menu_t mock_sub_menu_3_4 = {"menu_3_4", NULL, &mock_sub_menu_3_3, NULL, &mock_menu_3, mock_menu_3_4_callback};
menu_t mock_menu_4 = {"menu_4", &mock_menu_5, &mock_menu_3, &mock_sub_menu_4_1, NULL, NULL};
menu_t mock_sub_menu_4_1 = {"menu_4_1", &mock_sub_menu_4_2, NULL, NULL, &mock_menu_4, mock_menu_4_1_callback};
menu_t mock_sub_menu_4_2 = {"menu_4_2", &mock_sub_menu_4_3, &mock_sub_menu_4_1, NULL, &mock_menu_4, mock_menu_4_2_callback};
menu_t mock_sub_menu_4_3 = {"menu_4_3", &mock_sub_menu_4_4, &mock_sub_menu_4_2, NULL, &mock_menu_4, mock_menu_4_3_callback};
menu_t mock_sub_menu_4_4 = {"menu_4_4", NULL, &mock_sub_menu_4_3, NULL, &mock_menu_4, mock_menu_4_4_callback};
menu_t mock_menu_5 = {"menu_5", NULL, &mock_menu_4, NULL, NULL, NULL};

static void mock_menu_1_1_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_1_2_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_1_3_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_1_4_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_2_1_1_1_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_2_1_1_2_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_2_1_1_3_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_2_1_1_4_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_2_1_2_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_2_1_3_1_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_2_1_3_2_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_2_1_3_3_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_2_1_3_4_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_2_1_4_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_2_2_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_2_3_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_2_4_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_3_1_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_3_2_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_3_3_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_3_4_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_4_1_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_4_2_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_4_3_callback(void)
{
    set_callback_status_to_called();
}
static void mock_menu_4_4_callback(void)
{
    set_callback_status_to_called();
}

static void set_callback_status_to_called(void)
{
    mock_menu_callback_status = CB_EXECUTED;
}

void mock_set_callback_status_to_unknown(void)
{
    mock_menu_callback_status = CB_STATUS_UNKNOWN;
}