set(headers sample.h)
set(sources sample.cpp)


add_library(my_library SHARED ${headers} ${sources})
