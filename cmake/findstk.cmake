include(FindPackageHandleStandardArgs)
find_path(STK_INCLUDE_DIR stk/Stk.h stk)
find_library(STK_LIBRARY stk)

find_package_handle_standard_args(STK
 DEFAULT_MSG
  STK_INCLUDE_DIR
  STK_LIBRARY
)

mark_as_advanced(STK_LIBRARY STK_INCLUDE_DIR)

if(STK_FOUND)
  set(STK_LIBRARIES    ${STK_LIBRARY})
  set(STK_INCLUDE_DIRS ${STK_INCLUDE_DIR})
endif()
