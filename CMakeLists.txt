cmake_minimum_required(VERSION 3.15)
project(Project_Penguin VERSION 1.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")


include(FetchContent)
FetchContent_Declare(
    Eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG        
    
)

FetchContent_MakeAvailable(Eigen)

include_directories(include)


file(GLOB_RECURSIVE SOURCE_FILES
    "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})


target_link_libraries(${PROJECT_NAME} PRIVATE Eigen::Eigen)

message(STATUS "Project Penguin configured successfully with C++20 and Eigen!")
