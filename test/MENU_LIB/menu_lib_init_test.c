#include "unity/fixture/unity_fixture.h"
#include "menu_lib.h"
#include "mock_menu_implementation.h"
#include "menu_screen_driver_interface.h"
#include "mock_menu_screen_driver_interface.h"
#include <stddef.h>

extern menu_t *menu_entry_point;
extern uint8_t menu_number_of_chars_per_line;
extern uint8_t menu_number_of_screen_lines;

extern const struct menu_screen_driver_interface_struct *DISPLAY;

TEST_GROUP(menu_lib_init);

TEST_SETUP(menu_lib_init)
{
    /* Init before every test */
}

TEST_TEAR_DOWN(menu_lib_init)
{
    /* Cleanup after every test */
}

// TEST(menu_lib_init, WhenMenuInitThenMenuEntryPointIsEqualToPassedConfigDataEntryPoint)
// {
//     menu_init_t menu_config;
//     // When
//     menu_config.menu_entry_point=&mock_menu_1;
//     menu_init(NULL);
//     // Then
//     TEST_ASSERT_EQUAL(menu_config.menu_entry_point,menu_entry_point);
// }

TEST(menu_lib_init, WhenMenuInitThenMenuScreenSizeEqualToPassedConfigDataColumnCountAndRowCount)
{
    // When
    uint8_t epected_screen_number_of_char_per_line = 20;
    uint8_t epected_screen_number_of_lines = 4;
    menu_init();
    // Then
    TEST_ASSERT_EQUAL(epected_screen_number_of_char_per_line, menu_number_of_chars_per_line);
    TEST_ASSERT_EQUAL(epected_screen_number_of_lines, menu_number_of_screen_lines);
}

TEST(menu_lib_init, WhenMenuInitThenMenuScreenDriverInterfaceisEqualToMockMenuScreenDriverInterface)
{

    // When
    menu_init();
    // Then
    TEST_ASSERT_EQUAL(DISPLAY, get_menu_display_driver_interface());
}

// TEST(menu_lib_init, )
// {
//    // When
//    // Then
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(menu_lib_init, )
// {
//    // When
//    // Then
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(menu_lib_init, )
// {
//    // When
//    // Then
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(menu_lib_init, )
// {
//    // When
//    // Then
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(menu_lib_init, )
// {
//    // When
//    // Then
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(menu_lib_init, )
// {
//    // When
//    // Then
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(menu_lib_init, )
// {
//    // When
//    // Then
//     TEST_FAIL_MESSAGE("Implement your test!");
// }

// TEST(menu_lib_init, )
// {
//    // When
//    // Then
//     TEST_FAIL_MESSAGE("Implement your test!");
// }
