add_library(Math_Util 
    ./util/util.cpp
)

set(TEST_FILES
    ${TEST_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/vector/test/vecTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/matrix/test/matTest.cpp
    PARENT_SCOPE
)
