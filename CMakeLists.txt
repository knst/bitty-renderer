project(bitty_renderer)

set(SOURCE
    renderer.cpp
    tgaimage.cpp
    model.cpp
    main.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wlogical-op -Wcast-qual -Wcast-align")

add_executable(${PROJECT_NAME} ${SOURCE})
