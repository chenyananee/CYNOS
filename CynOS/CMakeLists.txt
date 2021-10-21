# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)


target_sources(${PROJECT_NAME}
    PRIVATE
    # {{BEGIN_TARGET_SOURCES}}
	${CMAKE_CURRENT_LIST_DIR}/cynos_debug.c
	${CMAKE_CURRENT_LIST_DIR}/cynos_event.c
    ${CMAKE_CURRENT_LIST_DIR}/cynos_fifo.c
    ${CMAKE_CURRENT_LIST_DIR}/cynos_fsm.c
    ${CMAKE_CURRENT_LIST_DIR}/cynos_funlib.c
    ${CMAKE_CURRENT_LIST_DIR}/cynos_kernel.c
    ${CMAKE_CURRENT_LIST_DIR}/cynos_list.c
    ${CMAKE_CURRENT_LIST_DIR}/cynos_task.c
    ${CMAKE_CURRENT_LIST_DIR}/cynos_time.c

    # {{END_TARGET_SOURCES}}
)

# Add the Common/inc directory to the project include list
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}
)
