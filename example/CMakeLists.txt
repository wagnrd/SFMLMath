project(SFMLMathExample)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window sfml-graphics SFMLMath)

file(COPY myfont.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

