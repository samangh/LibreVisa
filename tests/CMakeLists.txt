add_library(dummy dummy.cpp)
target_link_libraries(dummy PRIVATE visa)
target_include_directories(dummy PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)


##
## Test files
##

set(SRC_FILES
  find
  lock_attr_exclusive
  lock_attr_global
  lock_attr_shared
  lock_invalid_mode
  lock_recursive_exclusive
  lock_recursive_shared
  open
  open_multi
  print
  read
  rule_3_2_3
  rule_3_3_2
  rule_3_6_38
  rule_3_7_3
  rule_4_2_1
  rule_4_2_2
  rule_4_3_11
  wait_immediate_noevents
  wait_nenabled
  wait_timeout
  write)

foreach(TARGET ${SRC_FILES})
  add_executable(${TARGET} ${TARGET}.c)
  add_test(${TARGET} ${TARGET})
  target_include_directories(${TARGET} PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> dummy)
  target_link_libraries(${TARGET} PRIVATE visa dummy)
endforeach()

##
## Includes
##
