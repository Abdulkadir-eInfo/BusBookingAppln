cmake_minimum_required(VERSION 3.16.3)
project (BusBooking)

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

add_executable(BusAPP main.cpp)
target_link_libraries(BusAPP PRIVATE Reservation)

#add_executable(Tester tests/BookingTests.cpp)
#target_link_libraries(Tester PRIVATE UnitTest++)


#add_custom_command(TARGET Tester
#    	POST_BUILD COMMAND Tester
#	COMMENT "Running unit tests")