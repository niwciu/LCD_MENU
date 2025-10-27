#include "unity/fixture/unity_fixture.h"
#include "menu_lib.h"
#include "mock_menu_implementation.h"
#include "mock_menu_screen_driver_interface.h"
#include <stddef.h>

// #include "tested_module.h"

typedef void (*fun_ptr)(void);

static void call_menu_fun_x_times(fun_ptr fun_2_call, uint8_t repetition);

TEST_GROUP(menu_lib);

TEST_SETUP(menu_lib)
{
    /* Init before every test */
    init_mock_screen_driver();
}

TEST_TEAR_DOWN(menu_lib)
{
    /* Cleanup after every test */
}

/* MENU entry Init View Test cases to run */
TEST(menu_lib, GivenMenuInitWith2004ScreenWhenMenuViewInitForMockMenuCalledThenScreenContentIsEqualToExpected)
{
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_1             ",
        " menu_2             ",
        " menu_3             "};
    // Given
    menu_init();
    // When
    menu_view_init(&mock_menu_1, mock_menu_top_level_exit_callback, NULL);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

/* MENU ESC on top level Test cases to run */
TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndTopLevelEscCbRegisteredWhenMenuEscCalledThenTopLevelEscCbExecuted)
{
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_1             ",
        " menu_2             ",
        " menu_3             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, mock_menu_top_level_exit_callback, NULL);
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
    set_top_level_exit_cb_status_to_unknown();
    // When
    menu_esc();
    // Then
    TEST_ASSERT_EQUAL(CB_EXECUTED, mock_menu_top_level_exit_cb_status);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndTopLevelEscCbNotRegisteredWhenMenuEscCalledThenTopLevelEscCbStatusIsEqualToUnknown)
{
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_1             ",
        " menu_2             ",
        " menu_3             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
    set_top_level_exit_cb_status_to_unknown();
    // When
    menu_esc();
    // Then
    TEST_ASSERT_EQUAL(CB_STATUS_UNKNOWN, mock_menu_top_level_exit_cb_status);
}

/* MENU NEXT on top level menu Test cases to run */
TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuWhenMenuNextCalledThenScreenContentIsEqualToExpected)
{
    const char *expected_screen[4] = {
        "------- MENU -------",
        " menu_1             ",
        ">menu_2             ",
        " menu_3             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, mock_menu_top_level_exit_callback, NULL);
    // When
    menu_next();
    // Then`
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuWhenMenuNextCalledTwiceThenScreenContentIsEqualToExpected)
{
    uint8_t fun_call_repetition = 2;
    const char *expected_screen[4] = {
        "------- MENU -------",
        " menu_1             ",
        " menu_2             ",
        ">menu_3             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, mock_menu_top_level_exit_callback, NULL);
    // When
    call_menu_fun_x_times(menu_next, fun_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuWhenMenuNextCalled3TimesThenScreenContentIsEqualToExpected)
{
    uint8_t fun_call_repetition = 3;
    const char *expected_screen[4] = {
        "------- MENU -------",
        " menu_2             ",
        " menu_3             ",
        ">menu_4             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    // When
    call_menu_fun_x_times(menu_next, fun_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuWhenMenuNextCalled4TimesThenScreenContentIsEqualToExpected)
{
    uint8_t fun_call_repetition = 4;
    const char *expected_screen[4] = {
        "------- MENU -------",
        " menu_3             ",
        " menu_4             ",
        ">menu_5             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    // When
    call_menu_fun_x_times(menu_next, fun_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuWhenMenuNextCalled5TimesThenScreenContentIsEqualToExpected)
{
    uint8_t fun_call_repetition = 5;
    const char *expected_screen[4] = {
        "------- MENU -------",
        " menu_3             ",
        " menu_4             ",
        ">menu_5             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    // When
    call_menu_fun_x_times(menu_next, fun_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

/* MENU PREV on top level menu Test cases to run */
TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled100TimesWhenMenuPrevCalledOnceThenScreenContentIsEqualToExpected)
{
    uint8_t fun_call_repetition = 100;
    const char *expected_screen[4] = {
        "------- MENU -------",
        " menu_3             ",
        ">menu_4             ",
        " menu_5             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, fun_call_repetition);
    // When
    menu_prev();
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled100TimesWhenMenuPrevCalledTwiceThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_call_repetition = 100;
    uint8_t menu_prev_call_repetition = 2;
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_3             ",
        " menu_4             ",
        " menu_5             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_call_repetition);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled100TimesWhenMenuPrevCalled3TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_call_repetition = 100;
    uint8_t menu_prev_call_repetition = 3;
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_2             ",
        " menu_3             ",
        " menu_4             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_call_repetition);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled100TimesWhenMenuPrevCalled4TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_call_repetition = 100;
    uint8_t menu_prev_call_repetition = 4;
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_1             ",
        " menu_2             ",
        " menu_3             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_call_repetition);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled100TimesWhenMenuPrevCalled5TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_call_repetition = 100;
    uint8_t menu_prev_call_repetition = 5;
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_1             ",
        " menu_2             ",
        " menu_3             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_call_repetition);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled100TimesWhenMenuPrevCalled100TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_call_repetition = 100;
    uint8_t menu_prev_call_repetition = 100;
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_1             ",
        " menu_2             ",
        " menu_3             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_call_repetition);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

/* MENU NEXT & PREV combination on top level menu Test cases to run */
TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledOnceWhenMenuPrevCalledOnceThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_call_repetition = 1;
    uint8_t menu_prev_call_repetition = 1;
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_1             ",
        " menu_2             ",
        " menu_3             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_call_repetition);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledTwiceWhenMenuPrevCalledTwiceThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_call_repetition = 2;
    uint8_t menu_prev_call_repetition = 2;
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_1             ",
        " menu_2             ",
        " menu_3             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_call_repetition);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled3TimesWhenMenuPrevCalled3TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_call_repetition = 3;
    uint8_t menu_prev_call_repetition = 3;
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_1             ",
        " menu_2             ",
        " menu_3             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_call_repetition);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledTwiceWhenMenuPrevCalledOnceThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_call_repetition = 2;
    uint8_t menu_prev_call_repetition = 1;
    const char *expected_screen[4] = {
        "------- MENU -------",
        " menu_1             ",
        ">menu_2             ",
        " menu_3             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_call_repetition);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled3TimesWhenMenuPrevCalledOnceThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_call_repetition = 3;
    uint8_t menu_prev_call_repetition = 1;
    const char *expected_screen[4] = {
        "------- MENU -------",
        " menu_2             ",
        ">menu_3             ",
        " menu_4             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_call_repetition);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled3TimesWhenMenuPrevCalledTwiceThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_call_repetition = 3;
    uint8_t menu_prev_call_repetition = 2;
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_2             ",
        " menu_3             ",
        " menu_4             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_call_repetition);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_call_repetition);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

/* MENU ENTER menu Test cases to run */
TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuWhenMenuEnterCalledThenScreenContentIsEqualToExpected)
{
    const char *expected_screen[4] = {
        "------ menu_1 ------",
        ">menu_1_1           ",
        " menu_1_2           ",
        " menu_1_3           "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    // When
    menu_enter();
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockAndMenuNextCalledMenuWhenMenuEnterCalledThenScreenContentIsEqualToExpected)
{
    const char *expected_screen[4] = {
        "------ menu_2 ------",
        ">menu_2_1           ",
        " menu_2_2           ",
        " menu_2_3           "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    // When
    menu_enter();
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockAndMenuNext50TimesCalledMenuWhenMenuEnterCalledThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetitions = 50;
    const char *expected_screen[4] = {
        "------- MENU -------",
        " menu_3             ",
        " menu_4             ",
        ">menu_5             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_repetitions);
    // When
    menu_enter();
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

/* MENU ENTER & NEXT & PREV on 1'st level menu Test cases to run */
TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalledWhenMenuNextCalledOnceThenScreenContentIsEqualToExpected)
{
    const char *expected_screen[4] = {
        "------ menu_2 ------",
        " menu_2_1           ",
        ">menu_2_2           ",
        " menu_2_3           "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    menu_enter();
    // When
    menu_next();
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalledWhenMenuNextCalled50TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 50;
    const char *expected_screen[4] = {
        "------ menu_2 ------",
        " menu_2_2           ",
        " menu_2_3           ",
        ">menu_2_4           "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    menu_enter();
    // When
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalledAndMenuNextCalled50TimesWhenMenuPrevCalled2TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 50;
    const char *expected_screen[4] = {
        "------ menu_2 ------",
        ">menu_2_2           ",
        " menu_2_3           ",
        " menu_2_4           "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    menu_enter();
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    // When
    menu_prev();
    menu_prev();
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalledAndMenuNextCalled50TimesWhenMenuPrevCalled10TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 50;
    uint8_t menu_prev_repetition_counter = 10;
    const char *expected_screen[4] = {
        "------ menu_2 ------",
        ">menu_2_1           ",
        " menu_2_2           ",
        " menu_2_3           "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    menu_enter();
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_repetition_counter);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

/* MENU ENTER & NEXT & PREV to 2'st level menu Test cases to run */
TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalledTwiceWhenMenuNextCalledOnceThenScreenContentIsEqualToExpected)
{
    const char *expected_screen[4] = {
        "----- menu_2_1 -----",
        " menu_2_1_1         ",
        ">menu_2_1_2         ",
        " menu_2_1_3         "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    menu_enter();
    menu_enter();
    // When
    menu_next();
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalledTwiceWhenMenuNextCalled50TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 50;
    const char *expected_screen[4] = {
        "----- menu_2_1 -----",
        " menu_2_1_2         ",
        " menu_2_1_3         ",
        ">menu_2_1_4         "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    menu_enter();
    menu_enter();
    // When
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalledTwiceAndMenuNextCalled50TimesWhenMenuPrevCalled2TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 50;
    const char *expected_screen[4] = {
        "----- menu_2_1 -----",
        ">menu_2_1_2         ",
        " menu_2_1_3         ",
        " menu_2_1_4         "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    menu_enter();
    menu_enter();
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    // When
    menu_prev();
    menu_prev();
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalledTwiceAndMenuNextCalled50TimesWhenMenuPrevCalled10TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 50;
    uint8_t menu_prev_repetition_counter = 10;
    const char *expected_screen[4] = {
        "----- menu_2_1 -----",
        ">menu_2_1_1         ",
        " menu_2_1_2         ",
        " menu_2_1_3         "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    menu_enter();
    menu_enter();
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_repetition_counter);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

/* MENU ENTER & NEXT & PREV to 3'rd level menu Test cases to run */
TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalled3TimesWhenMenuNextCalledOnceThenScreenContentIsEqualToExpected)
{
    uint8_t menu_enter_repetition_counter = 3;
    const char *expected_screen[4] = {
        "---- menu_2_1_1 ----",
        " menu_2_1_1_1       ",
        ">menu_2_1_1_2       ",
        " menu_2_1_1_3       "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    call_menu_fun_x_times(menu_enter, menu_enter_repetition_counter);
    // When
    menu_next();
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalled3TimesWhenMenuNextCalled50TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 50;
    uint8_t menu_enter_repetition_counter = 3;
    const char *expected_screen[4] = {
        "---- menu_2_1_1 ----",
        " menu_2_1_1_2       ",
        " menu_2_1_1_3       ",
        ">menu_2_1_1_4       "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    call_menu_fun_x_times(menu_enter, menu_enter_repetition_counter);
    // When
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalled3TimesAndMenuNextCalled50TimesWhenMenuPrevCalled2TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 50;
    uint8_t menu_enter_repetition_counter = 3;
    const char *expected_screen[4] = {
        "---- menu_2_1_1 ----",
        ">menu_2_1_1_2       ",
        " menu_2_1_1_3       ",
        " menu_2_1_1_4       "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    call_menu_fun_x_times(menu_enter, menu_enter_repetition_counter);
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    // When
    menu_prev();
    menu_prev();
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalled3TimesAndMenuNextCalled50TimesWhenMenuPrevCalled10TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 50;
    uint8_t menu_prev_repetition_counter = 10;
    uint8_t menu_enter_repetition_counter = 3;
    const char *expected_screen[4] = {
        "---- menu_2_1_1 ----",
        ">menu_2_1_1_1       ",
        " menu_2_1_1_2       ",
        " menu_2_1_1_3       "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    call_menu_fun_x_times(menu_enter, menu_enter_repetition_counter);
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    // When
    call_menu_fun_x_times(menu_prev, menu_prev_repetition_counter);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

/* MENU ENTER & NEXT & PREV & ESC different Test cases to run */
TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalledAndMenuNextCalleWhenMenuEscCalleddOnceThenScreenContentIsEqualToExpected)
{
    const char *expected_screen[4] = {
        "------- MENU -------",
        " menu_1             ",
        ">menu_2             ",
        " menu_3             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    menu_enter();
    menu_next();
    // When
    menu_esc();
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalledAndMenuEnterCalledAndMenuNextCalleWhenMenuEscCalledd10TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_esc_repetition_counter = 10;
    const char *expected_screen[4] = {
        "------- MENU -------",
        " menu_1             ",
        ">menu_2             ",
        " menu_3             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    menu_next();
    menu_enter();
    menu_next();
    // When
    call_menu_fun_x_times(menu_esc, menu_esc_repetition_counter);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled5TimesAndMenuPrevCalled3TimesAndMenuEnterCalledTwiceAndMenuNextCalled3TimesAndMenuPrevCalledOnceAndMenuEntrCalledOnceWhenMenuNextCalledOnceThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 5;
    uint8_t menu_prev_repetition_counter = 3;
    uint8_t menu_enter_repetition_counter = 2;
    const char *expected_screen[4] = {
        "---- menu_2_1_3 ----",
        " menu_2_1_3_1       ",
        ">menu_2_1_3_2       ",
        " menu_2_1_3_3       "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    call_menu_fun_x_times(menu_prev, menu_prev_repetition_counter);
    call_menu_fun_x_times(menu_enter, menu_enter_repetition_counter);
    menu_next_repetition_counter = 3;
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    menu_prev();
    menu_enter();
    // When
    menu_next();
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled5TimesAndMenuPrevCalled3TimesAndMenuEnterCalledTwiceAndMenuNextCalled3TimesAndMenuPrevCalledOnceAndMenuEntrCalledOnceAndMenuNextCalledOnceWhenMenuEscCalledOnceThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 5;
    uint8_t menu_prev_repetition_counter = 3;
    uint8_t menu_enter_repetition_counter = 2;
    const char *expected_screen[4] = {
        "----- menu_2_1 -----",
        " menu_2_1_2         ",
        ">menu_2_1_3         ",
        " menu_2_1_4         "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    call_menu_fun_x_times(menu_prev, menu_prev_repetition_counter);
    call_menu_fun_x_times(menu_enter, menu_enter_repetition_counter);
    menu_next_repetition_counter = 3;
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    menu_prev();
    menu_enter();
    menu_next();
    // When
    menu_esc();
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled5TimesAndMenuPrevCalled3TimesAndMenuEnterCalledTwiceAndMenuNextCalled3TimesAndMenuPrevCalledOnceAndMenuEntrCalledOnceAndMenuNextCalledOnceWhenMenuEscCalledTwiceThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 5;
    uint8_t menu_prev_repetition_counter = 3;
    uint8_t menu_enter_repetition_counter = 2;
    uint8_t menu_esc_repetition_counter = 2;
    const char *expected_screen[4] = {
        "------ menu_2 ------",
        ">menu_2_1           ",
        " menu_2_2           ",
        " menu_2_3           "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    call_menu_fun_x_times(menu_prev, menu_prev_repetition_counter);
    call_menu_fun_x_times(menu_enter, menu_enter_repetition_counter);
    menu_next_repetition_counter = 3;
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    menu_prev();
    menu_enter();
    menu_next();
    // When
    call_menu_fun_x_times(menu_esc, menu_esc_repetition_counter);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled5TimesAndMenuPrevCalled3TimesAndMenuEnterCalledTwiceAndMenuNextCalled3TimesAndMenuPrevCalledOnceAndMenuEntrCalledOnceAndMenuNextCalledOnceWhenMenuEscCalled3TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 5;
    uint8_t menu_prev_repetition_counter = 3;
    uint8_t menu_enter_repetition_counter = 2;
    uint8_t menu_esc_repetition_counter = 3;
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_2             ",
        " menu_3             ",
        " menu_4             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    call_menu_fun_x_times(menu_prev, menu_prev_repetition_counter);
    call_menu_fun_x_times(menu_enter, menu_enter_repetition_counter);
    menu_next_repetition_counter = 3;
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    menu_prev();
    menu_enter();
    menu_next();
    // When
    call_menu_fun_x_times(menu_esc, menu_esc_repetition_counter);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled5TimesAndMenuPrevCalled3TimesAndMenuEnterCalledTwiceAndMenuNextCalled3TimesAndMenuPrevCalledOnceAndMenuEntrCalledOnceAndMenuNextCalledOnceWhenMenuEscCalled10TimesThenScreenContentIsEqualToExpected)
{
    uint8_t menu_next_repetition_counter = 5;
    uint8_t menu_prev_repetition_counter = 3;
    uint8_t menu_enter_repetition_counter = 2;
    uint8_t menu_esc_repetition_counter = 10;
    const char *expected_screen[4] = {
        "------- MENU -------",
        ">menu_2             ",
        " menu_3             ",
        " menu_4             "};
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    call_menu_fun_x_times(menu_prev, menu_prev_repetition_counter);
    call_menu_fun_x_times(menu_enter, menu_enter_repetition_counter);
    menu_next_repetition_counter = 3;
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    menu_prev();
    menu_enter();
    menu_next();
    // When
    call_menu_fun_x_times(menu_esc, menu_esc_repetition_counter);
    // Then
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_screen, mock_screen_lines, LCD_Y);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled5TimesAndMenuPrevCalled3TimesAndMenuEnterCalledTwiceAndMenuNextCalled3TimesAndMenuPrevCalledOnceAndMockMenuCalblackStatusSetToUnknownWhenMenuEnterCalleddTwiceThenMockMenuCalblackStatusIsEqualToCbExecuted)
{
    uint8_t menu_next_repetition_counter = 5;
    uint8_t menu_prev_repetition_counter = 3;
    uint8_t menu_enter_repetition_counter = 2;
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    call_menu_fun_x_times(menu_prev, menu_prev_repetition_counter);
    call_menu_fun_x_times(menu_enter, menu_enter_repetition_counter);
    menu_next_repetition_counter = 3;
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    menu_prev();
    mock_set_callback_status_to_unknown();
    // When
    menu_enter();
    menu_enter();
    // Then
    TEST_ASSERT_EQUAL(CB_EXECUTED, mock_menu_callback_status);
}

TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled5TimesAndMockMenuCalblackStatusSetToUnknownWhenMenuEnterCalleddOnceThenMockMenuCalblackStatusIsEqualToUnknown)
{
    uint8_t menu_next_repetition_counter = 5;
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    mock_set_callback_status_to_unknown();
    // When
    menu_enter();
    // Then
    TEST_ASSERT_EQUAL(CB_STATUS_UNKNOWN, mock_menu_callback_status);
}
TEST(menu_lib, GivenMenuInitWith2004ScreenAndMenuViewInitForMockMenuAndMenuNextCalled2TimesWhenGetCurrentMenuPositionCalledThenReturnetValueIsEqualToMockMenu3)
{
    uint8_t menu_next_repetition_counter = 2;
    // Given
    menu_init();
    menu_view_init(&mock_menu_1, NULL, NULL);
    call_menu_fun_x_times(menu_next, menu_next_repetition_counter);
    // When
    menu_t *readed_menu_pos = get_current_menu_position();
    // Then
    TEST_ASSERT_EQUAL(&mock_menu_3, readed_menu_pos);
}

// TEST(menu_lib, )
// {
//     // Given
//     // When
//     // Then
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

static void call_menu_fun_x_times(fun_ptr fun_2_call, uint8_t repetition)
{
    for (uint8_t i = 0; i < repetition; i++)
    {
        fun_2_call();
    }
}