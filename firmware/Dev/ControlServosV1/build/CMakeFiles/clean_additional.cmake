# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "/home/tatiana/projects/zephyros-rp2040-example3/ControlServos/build/zephyr/include/generated/syscalls"
  )
endif()
