#rexx daemon module CmakeLists.txt

set(DEAMON_DEPENDS_LIB ssl crypto)

# -- rexx_rexxd -- #
set(BIN_REXX_ID rexxd)

add_executable(${BIN_REXX_ID} ./rexx/main.cpp)


IF (${OS_NAME} MATCHES "OS_LINUX")  
    MESSAGE(STATUS "current platform: Linux ")  
	target_link_libraries(${BIN_REXX_ID} -Wl,-dn ${DEAMON_DEPENDS_LIB} ${REXX_LINKER_FLAGS})
ELSE ()  
	MESSAGE(STATUS "current platform: MAC ")  
	target_link_libraries(${BIN_REXX_ID} -Wl, ${DEAMON_DEPENDS_LIB} ${REXX_LINKER_FLAGS})
ENDIF () 



target_compile_options(${BIN_REXX_ID}
    PUBLIC -std=c++11
    PUBLIC -D${OS_NAME}
)

install(TARGETS ${BIN_REXX_ID}
    RUNTIME DESTINATION ${REXXCHAIN}/bin
)

