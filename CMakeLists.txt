cmake_minimum_required(VERSION 3.16.3)
project (BusBooking)

find_program(ASTYLE_EXECUTABLE astyle)
if(ASTYLE_EXECUTABLE)
    set(ASTYLE_OPTIONS_FILE ${CMAKE_SOURCE_DIR}/astyle.options)
    set(ASTYLE_FOUND "true")
    add_custom_target(format-source
        COMMAND ${ASTYLE_EXECUTABLE}  --options=${ASTYLE_OPTIONS_FILE} ${CMAKE_SOURCE_DIR}/*.cpp 
                ${CMAKE_SOURCE_DIR}/include/*.h ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/tests/*.cpp
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        SOURCES ${ASTYLE_OPTIONS_FILE}
    )
else()
    unset(ASTYLE_FOUND)
    message("Artistic style executable was not found, so automatic code style formating will be unavailable")
endif()

include_directories(include/)
link_directories(include/)

add_definitions(-g)

add_library(User
    include/UserClass.h
	src/UserClass.cpp)

add_library(Vendor
    include/VendorClass.h
	src/VendorClass.cpp)

add_library(Reservation
    include/ReservationClass.h
    src/ReservationClass.cpp)

target_link_libraries(Reservation User Vendor)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/database/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

add_executable(TestVendor tests/TestVendor.cpp)
target_link_libraries(TestVendor PRIVATE UnitTest++ Vendor)

add_executable(TestUser tests/TestUser.cpp)
target_link_libraries(TestUser PRIVATE UnitTest++ User)

add_executable(TestReservation tests/TestReservation.cpp)
target_link_libraries(TestReservation PRIVATE UnitTest++ Reservation)

add_executable(BusAPP main.cpp)
target_link_libraries(BusAPP PRIVATE Reservation)