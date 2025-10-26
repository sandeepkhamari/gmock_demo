add_executable(test_calc test_calculator.cpp test_client.cpp)

target_include_directories(test_calc PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_calc PRIVATE calculator)

#target_link_libraries(test_calc 
#	              PRIVATE
#		      /usr/lib/libgtest.a
#		      /usr/lib/libgtest_main.a
#		      /usr/lib/libgmock.a
#		      /usr/lib/libgmock_main.a
#	      )

include(FetchContent)

####--- Fetch GoogleTest(includes GoogleMock) -----######
FetchContent_Declare(
   googletest
   URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
   DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Disable installing (for speed)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()
include(CTest)
include(GoogleTest)

target_link_libraries(test_calc
	              PRIVATE
		      GTest::gmock
		      GTest::gtest_main
)
	      
include(GoogleTest)
gtest_discover_tests(test_calc)

