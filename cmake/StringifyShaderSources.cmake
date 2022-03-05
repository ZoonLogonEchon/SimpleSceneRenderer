function(READ_INTO_STRING SRC_PATH TARGET)
    set(SHADER_STRING "")
    file(STRINGS  ${SRC_PATH} SHADER_AS_STR)
    foreach(X ${SHADER_AS_STR})
        string(APPEND SHADER_STRING "\\\n ${X}\\n")
    endforeach()
    set(${TARGET} ${SHADER_STRING} PARENT_SCOPE)
endfunction()