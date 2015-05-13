file(GLOB server_sources *.cpp)
add_library(chronos-server-lib ${server_sources})
target_link_libraries(
    chronos-server-lib
    atlas-com-http-server
    hades
    ${CMAKE_CURRENT_BINARY_DIR}/../web/static.a
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    )

