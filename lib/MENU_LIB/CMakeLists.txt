cmake_minimum_required(VERSION 3.20)
# project(menu_lib C)

add_library(menu_lib STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/menu_lib.c    
)

set_target_properties(menu_lib PROPERTIES 
  OUTPUT_NAME "menu_lib"
  PREFIX ""
)

target_include_directories(menu_lib PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}                 # obecny katalog źródeł
  ../../test/MENU_LIB          # katalog globalny test/MENU_LIB
)
