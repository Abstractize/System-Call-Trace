cmake_minimum_required(VERSION 3.0.0)
project(SystemCallTrace VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(SystemCallTrace 
    src/main.c
    src/strategies/executionMode.c
    src/strategies/interactiveStrategy.c
    src/strategies/noninteractiveStrategy.c
    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
