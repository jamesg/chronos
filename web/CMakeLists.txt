atlas_add_web_library(
    PREFIX chronos
    TARGET chronos-web
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/static.a
    SOURCES
        index.html
        index.js
        models.js
        )

