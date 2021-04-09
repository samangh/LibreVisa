set(TARGET "visa")

##
## Source files
##

set(SRC_FILES
	base_vprintf.cpp
	event_queue.cpp
	findlist.cpp
	messagepump.cpp
	object.cpp
	object_cache.cpp
	resource.cpp
	resource_manager.cpp
	session.cpp
	thread.h
	thread_pthread.cpp
	timeval_op.h
	util.h
	viBufWrite.cpp
	viClose.cpp
	viDisableEvent.cpp
	viEnableEvent.cpp
	viFindNext.cpp
	viFindRsrc.cpp
	viFlush.cpp
	viGetAttribute.cpp
	viLock.cpp
	viOpen.cpp
	viOpenDefaultRM.cpp
	viParseRsrc.cpp
	viPrintf.cpp
	viRead.cpp
	viReadSTB.cpp
	viSetAttribute.cpp
	viSetBuf.cpp
	viSPrintf.cpp
	viUnlock.cpp
	viVPrintf.cpp
	viVSPrintf.cpp
	viWaitOnEvent.cpp
	viWrite.cpp)

set(USB_SOURCES
  usb/usb_resource.cpp usb/usb_resource.h
  usb/usb_resource_creator.cpp usb/usb_resource_creator.h
  usb/usb_string.h)

set(VXI_SOURCES
  vxi/vxi_resource.cpp vxi/vxi_resource.h
  vxi/vxi_resource_creator.cpp vxi/vxi_resource_creator.h)

set(AVAHI_SOURCES
  messagepump_avahi.cpp messagepump_avahi.h
  vxi/avahi.cpp vxi/avahi.h)

if(WITH_USB)
  list(APPEND SRC_FILES ${USB_SOURCES})
endif()

if(WITH_VXI)
  list(APPEND SRC_FILES ${VXI_SOURCES})
  if(WITH_MDNS)
    list(APPEND SRC_FILES ${AVAHI_SOURCES})
  endif()
endif()

add_library(${TARGET} ${SRC_FILES})

##
## Includes
##

target_include_directories(${TARGET}
  INTERFACE
  PUBLIC
    $<INSTALL_INTERFACE:includel>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  PRIVATE
  )

target_link_libraries(${TARGET}
  INTERFACE
  PUBLIC
  PRIVATE
    Boost::regex
    $<$<BOOL:${WITH_USB}>:LibUSB>
    "$<$<BOOL:${WITH_AVAHI}>:Avahi::common Avahi::client>"
  )
