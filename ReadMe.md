# 📜 MENU_LIB - C Modular Cross-Platform C Menu Engine
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![CMake](https://img.shields.io/badge/build-cmake-green)](https://cmake.org/)

`MENU_LIB` is a **lightweight and portable C library** for creating hierarchical menus on embedded systems. It is built on **doubly linked lists**, providing **efficient forward/backward navigation**, submenu support, and dynamic menu rendering. The library abstracts the display driver, allowing it to work on **LCD, OLED, terminal screens**, or any custom display interface.

Menus are defined in **`menu.h` and `menu.c`**, which can be automatically generated using the **JS Menu Designer** tool. This tool allows you to visually design your menu structure and produces:

* Menu item structures (`menu_t`)
* Constant strings for menu labels
* Empty callback stubs ready to be implemented

> ⚠️ **Important:** The generated files (`menu.h` and `menu.c`) **must be included and linked** in your project for the library to work correctly. You then implement the callback functions for the items that need custom behavior.

---

## Features ✨

* 📂 **Hierarchical Menus** – Multi-level menus, limited only by `MAX_MENU_DEPTH`.
* 🔄 **Doubly Linked List Based** – Efficient navigation forward and backward between items.
* ▶️ **Navigation Functions** – `menu_next`, `menu_prev`, `menu_enter`, `menu_esc` for easy cursor control.
* 🔧 **Callbacks** – Assign a function to each menu item to define custom behavior.
* 🖥️ **Display Driver Abstraction** – Compatible with any screen via `menu_screen_driver_interface_struct`.
* 📝 **Flexible Headers** – Default or custom headers for main menus and submenus.
* 🛡️ **Safe Pointer Handling** – Built-in error checks and status codes (`menu_status_t`).
* ⚙️ **CI/CD Friendly** – Works with code coverage, complexity analysis, static analysis, and formatting tools.
* 🧩 **JS Menu Designer Tool Integration** – Generates menu structures and empty callbacks, streamlining development.

## 🚀 Getting Started / Usage

To integrate **MENU_LIB** into your project, follow these steps:

### 🧩 1. Add the Library to Your Project

You can include **MENU_LIB** in one of two ways:

#### Option A — Precompiled Library (Recommended for Larger Projects)

1. Copy library to their project location and using library internall CMakeLists.txt integrate with your project main CMakeLists.txt to precompile library.
2. Make sure to **add the include path** to `menu.h` in library internall CMakeLists.txt if this file is located **outside the library directory**.
3. For more details go to examples folder and check **XXXprecompiled lib integration** exapmpe

#### Option B — Direct Source Inclusion

Simply copy the following files into your project structure and add them to your project configuration:

* `menu_lib.c`
* `menu_lib.h`
* `menu_lib_type.h`
* `menu_screen_driver_interface.h`

This method is simpler for small embedded projects without complex build setups.

---

### ⚙️ 2. Generate Menu Definition Files

MENU_LIB works together with a **JavaScript Menu Designer Tool** 🧠, which helps you visually design your menu structure.
This tool automatically generates two essential files:

* **`menu.h`** – contains menu structure definitions and string constants.
* **`menu.c`** – contains initialized menu item objects and empty callback stubs.

Place these two files in your project source directory and make sure they are compiled together with your application.

> 💡 **Important:** If you use the precompiled version of MENU_LIB, ensure that the `menu.h` file path is correctly added to the library’s include directories in CMake.

---

### 🖥️ 3. Implement the Display Interface

MENU_LIB uses an **abstraction layer** to communicate with your display device.
This is defined in `menu_screen_driver_interface.h`, and it allows you to easily adapt the library to different types of screens — LCD, OLED, UART terminals, etc.

You need to implement a driver that provides all required display functions such as:

* Initializing the screen
* Setting the cursor position
* Printing characters and strings
* Returning screen dimensions (rows and columns)

Example structure definition:

```c
struct menu_screen_driver_interface_struct
{
    void (*screen_init)(void);
    uint8_t (*get_number_of_screen_lines)(void);
    uint8_t (*get_number_of_chars_per_line)(void);
    void (*clr_scr)(void);
    void (*cursor_position)(uint8_t row, uint8_t column);
    void (*print_string)(const char *string);
    void (*print_char)(const char character);
};
```

Then, provide an instance of this structure and expose it through:

```c
const struct menu_screen_driver_interface_struct *get_menu_display_driver_interface(void)
{
    return &LCD_driver;
}
```

> 💡 **Tip:** For quick integration and testing, you can use a fully compatible display driver available here:
> 🔗 [LCD_HD44780 by niwciu](https://github.com/niwciu/LCD_HD44780)

This driver works perfectly with MENU_LIB and provides a ready-to-use example implementation of the required interface.

---

### 🧭 4. Basic Initialization Example

Once everything is linked correctly, initialize and display your menu:

```c
#include "menu_lib.h"
#include "menu.h"  // generated by the Menu Designer

int main(void)
{
    // Initialize display driver and menu system
    if (menu_init() != MENU_OK)
        return -1;

    // Initialize and display root menu
    menu_view_init(&root_menu, NULL, "Main Menu");

    // Example navigation loop
    while (1)
    {
        // Replace with actual input handling
        menu_next();
        menu_enter();
    }
}
```

---

### 🧱 5. Integration Notes

* The library does not depend on any specific hardware – it relies on your custom **screen driver interface** (`menu_screen_driver_interface.h`).
* You can implement this interface for LCDs, serial consoles, or any display type.
* Menu navigation (`menu_next`, `menu_prev`, `menu_enter`, `menu_esc`) can be triggered by hardware buttons, rotary encoders, or touch events.
