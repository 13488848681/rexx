#rexx common module CmakeLists.txt -- librexx_common.a

set(LIB_REXX_COMMON rexx_common)
set(COMMON_SRC
    configure_base.cpp general.cpp storage.cpp private_key.cpp 
    daemon.cpp argument.cpp pb2json.cpp network.cpp data_secret_key.cpp key_store.cpp
)

#Generate static library files
add_library(${LIB_REXX_COMMON} ${COMMON_SRC})

#Specify compiling options for target objects
target_compile_options(${LIB_REXX_COMMON}
    PUBLIC -std=c++11 
    PUBLIC -DASIO_STANDALONE
    PUBLIC -D_WEBSOCKETPP_CPP11_STL_
    PUBLIC -D${OS_NAME}
	PUBLIC -fPIC
)
