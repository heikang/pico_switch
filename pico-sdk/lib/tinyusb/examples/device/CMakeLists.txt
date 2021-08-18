cmake_minimum_required(VERSION 3.5)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../hw/bsp/${FAMILY}/family.cmake)

project(tinyusb_device_examples)
family_initialize_project(tinyusb_device_examples ${CMAKE_CURRENT_LIST_DIR})

# family_add_subdirectory will filter what to actually add based on selected FAMILY
family_add_subdirectory(board_test)
family_add_subdirectory(dynamic_configuration)
family_add_subdirectory(hid_composite)
