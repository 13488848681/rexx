#rexx overlay module CmakeLists.txt -- librexx_overlay.a

set(LIB_REXX_OVERLAY rexx_overlay)
#Automatically get src files from the specified directory
aux_source_directory(${REXX_SRC_DIR}/overlay/ OVERLAY_SRC)

#Generate static library files
add_library(${LIB_REXX_OVERLAY} ${OVERLAY_SRC})

#Specify compiling options for the target objects
target_compile_options(${LIB_REXX_OVERLAY}
    PUBLIC -std=c++11 
    PUBLIC -DASIO_STANDALONE
    PUBLIC -D_WEBSOCKETPP_CPP11_STL_
    PUBLIC -D${OS_NAME}
)
