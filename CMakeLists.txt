cmake_minimum_required(VERSION 2.8)

PROJECT(HARDSPHERE)

# Require MPI for this project:
find_package(MPI REQUIRED)
if(MPI_FOUND)
  set(CMAKE_CXX_COMPILE_FLAGS 
    ${CMAKE_CXX_COMPILE_FLAGS} 
    ${MPI_COMPILE_FLAGS})
  set(CMAKE_CXX_LINK_FLAGS 
    ${CMAKE_CXX_LINK_FLAGS} 
    ${MPI_LINK_FLAGS})
endif()

# require openmp
FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
  message("OPENMP FOUND")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories(${MPI_INCLUDE_PATH})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -pedantic -std=c++11")


set(passap_SRCS src/particle_operations.cpp src/system.cpp src/vector_math.cpp )

add_executable(passap src/main.cpp ${passap_SRCS})
add_executable(setup_system src/setup_system.cpp ${passap_SRCS})
target_link_libraries(passap ${MPI_LIBRARIES})

