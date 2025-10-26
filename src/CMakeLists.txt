add_library(calculator STATIC calculator.cpp client.cpp)
target_include_directories(calculator PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_compile_definitions(calculator PRIVATE SRC_MACRO)
target_compile_options(calculator PRIVATE -Wall -Wextra -O2)
#target_link_options(calculator PUBLIC "-Wl")

add_executable(calcApp main.cpp)
target_include_directories(calcApp PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(calcApp PRIVATE calculator)

