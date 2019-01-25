#rexx tools module CmakeLists.txt -- librexxtools.so

set(LIB_REXX_TOOLS rexxtools)
set(TOOLS_SRC
    lib_rexx_tools.cpp
)

set(INNER_TOOLS_LIBS rexx_common rexx_utils rexx_ed25519)
set(REXX_TOOLS_DEPENDS_LIBS json ssl crypto scrypt)


#Generate share library files
add_library(${LIB_REXX_TOOLS} SHARED ${TOOLS_SRC})

target_link_libraries(${LIB_REXX_TOOLS} ${INNER_TOOLS_LIBS} ${REXX_TOOLS_DEPENDS_LIBS})

#Specify compiling options for target objects
target_compile_options(${LIB_REXX_TOOLS}
    PUBLIC -std=c++11 
    PUBLIC -DASIO_STANDALONE
    PUBLIC -D_WEBSOCKETPP_CPP11_STL_
    PUBLIC -D${OS_NAME}
)
