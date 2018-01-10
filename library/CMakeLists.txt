message(STATUS "")
message(STATUS "Libraries")
message(STATUS "=========")

message(STATUS "")
message(STATUS "Shared")
add_subdirectory(dll)
add_subdirectory(dllunicode)

message(STATUS "")
message(STATUS "Static")
add_subdirectory(static)
add_subdirectory(staticunicode)