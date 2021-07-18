project (AmethystServer)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/AmethystServer.cpp
)
target_link_libraries(${PROJECT_NAME} PUBLIC
    AmethystCore
    )
