
function(add_namespaced_library)
    cmake_parse_arguments(PARSE_ARGV 0 ARG "" "NAME" "SOURCES;DEPENDS_INTERNAL;DEPENDS")

    add_library(${PROJECT_NAME}_${ARG_NAME}_obj OBJECT ${ARG_SOURCES})
    add_library(${PROJECT_NAME}::${ARG_NAME}_obj ALIAS ${PROJECT_NAME}_${ARG_NAME}_obj)

    add_library(${PROJECT_NAME}_${ARG_NAME} INTERFACE)
    add_library(${PROJECT_NAME}::${ARG_NAME} ALIAS ${PROJECT_NAME}_${ARG_NAME})

    list(TRANSFORM ARG_DEPENDS_INTERNAL REPLACE "(.+)" "${PROJECT_NAME}::\\1")
    target_link_libraries(${PROJECT_NAME}_${ARG_NAME}_obj INTERFACE
        ${ARG_DEPENDS_INTERNAL}
        ${ARG_DEPENDS}
    )

    target_link_libraries(${PROJECT_NAME}_${ARG_NAME} INTERFACE
        ${PROJECT_NAME}::${ARG_NAME}_obj
        $<TARGET_OBJECTS:${PROJECT_NAME}::${ARG_NAME}_obj>
    )
endfunction()

function(add_namespaced_executable)
    cmake_parse_arguments(PARSE_ARGV 0 ARG "" "NAME" "SOURCES;DEPENDS_INTERNAL;DEPENDS")

    add_executable(${ARG_NAME} ${ARG_SOURCES})
    add_executable(${PROJECT_NAME}::${ARG_NAME} ALIAS ${ARG_NAME})

    list(TRANSFORM ARG_DEPENDS_INTERNAL REPLACE "(.+)" "${PROJECT_NAME}::\\1")
    target_link_libraries(${ARG_NAME} PRIVATE
        ${ARG_DEPENDS_INTERNAL}
        ${ARG_DEPENDS}
    )
endfunction()