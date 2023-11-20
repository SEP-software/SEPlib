project(SEPLIB-vplot-filters)
cmake_minimum_required(VERSION 3.10)

ADD_EXECUTABLE(plas plas.c)
TARGET_LINK_LIBRARIES(plas vplot m)

ADD_EXECUTABLE(pldb pldb.c)
TARGET_LINK_LIBRARIES(pldb vplot m)

