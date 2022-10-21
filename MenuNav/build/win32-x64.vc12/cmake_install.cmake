# Install script for directory: G:/Dev/MenuNav

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "G:/Dev/MenuNav/dist/win32-x64.vc12")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/share/VistaBuildInfo/MenuNavBuildInfo.txt")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/share/VistaBuildInfo" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES "G:/Dev/MenuNav/build/win32-x64.vc12/bin/MenuNavBuildInfo.txt")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/MenuNav.exe")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE EXECUTABLE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "G:/Dev/MenuNav/build/win32-x64.vc12/bin/MenuNav.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/MenuNavD.exe")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE EXECUTABLE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "G:/Dev/MenuNav/build/win32-x64.vc12/bin/MenuNavD.exe")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaAspects.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaBase.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaDataFlowNet.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaDeviceDriversBase.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaInterProcComm.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaKernel.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaKernelOpenSGExt.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaMath.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaOGLExt.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaTools.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/VistaAspects.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/VistaBase.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/VistaDataFlowNet.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/VistaDeviceDriversBase.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/VistaInterProcComm.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/VistaKernel.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/VistaKernelOpenSGExt.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/VistaMath.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/VistaOGLExt.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/VistaTools.dll"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaCyberGloveDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaCyberGlovePlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaCyberGloveTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaDTrackDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaDTrackPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaDTrackTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaFastrakDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaFastrakPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaFastrakTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutJoystickDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutJoystickPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutJoystickTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutKeyboardDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutKeyboardPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutKeyboardTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutMouseDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutMousePlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutMouseTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaHapticDeviceEmulatorDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaHapticDeviceEmulatorPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaHapticDeviceEmulatorTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaHIDDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaHIDPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaHIDTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaIRManDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaIRManPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaIRManTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaLeapMotionDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaLeapMotionPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaLeapMotionTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaMIDIDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaMIDIPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaMIDITranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaPhantomServerDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaPhantomServerPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaPhantomServerTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaSpaceMouseDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaSpaceMousePlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaSpaceMouseTranscoder.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaCyberGloveDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaCyberGlovePlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaCyberGloveTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaDTrackDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaDTrackPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaDTrackTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaFastrakDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaFastrakPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaFastrakTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutJoystickDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutJoystickPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutJoystickTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutKeyboardDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutKeyboardPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutKeyboardTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutMouseDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutMousePlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutMouseTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaHapticDeviceEmulatorDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaHapticDeviceEmulatorPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaHapticDeviceEmulatorTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaHIDDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaHIDPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaHIDTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaIRManDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaIRManPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaIRManTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaLeapMotionDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaLeapMotionPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaLeapMotionTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaMIDIDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaMIDIPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaMIDITranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaPhantomServerDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaPhantomServerPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaPhantomServerTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaSpaceMouseDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaSpaceMousePlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaSpaceMouseTranscoder.dll"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/OSGBase.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/OSGSystem.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/OSGWindowGLUT.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/OSGWindowWIN32.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "G:/Dev/externals/OpenSG/OpenSG-1.8/win32-x64.vc12/lib/OSGBase.dll"
    "G:/Dev/externals/OpenSG/OpenSG-1.8/win32-x64.vc12/lib/OSGSystem.dll"
    "G:/Dev/externals/OpenSG/OpenSG-1.8/win32-x64.vc12/lib/OSGWindowGLUT.dll"
    "G:/Dev/externals/OpenSG/OpenSG-1.8/win32-x64.vc12/lib/OSGWindowWIN32.dll"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/freeglut.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "G:/Dev/externals/freeglut/win32-x64/lib/freeglut.dll")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/glew32.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/glew32d.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "G:/Dev/externals/glew/glew-1.10.0/win32-x64/lib/glew32.dll"
    "G:/Dev/externals/glew/glew-1.10.0/win32-x64/lib/glew32d.dll"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/Leap.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/LeapC.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/LeapJava.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/msvcp120.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/msvcr120.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "G:/Dev/externals/LeapSDK/LeapSDK-3.1.3/LeapSDK/lib/x64/Leap.dll"
    "G:/Dev/externals/LeapSDK/LeapSDK-3.1.3/LeapSDK/lib/x64/LeapC.dll"
    "G:/Dev/externals/LeapSDK/LeapSDK-3.1.3/LeapSDK/lib/x64/LeapJava.dll"
    "G:/Dev/externals/LeapSDK/LeapSDK-3.1.3/LeapSDK/lib/x64/msvcp120.dll"
    "G:/Dev/externals/LeapSDK/LeapSDK-3.1.3/LeapSDK/lib/x64/msvcr120.dll"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/sqlite3.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "G:/Dev/externals/sqlite/sqlite-3.7.17/win32-x64/lib/sqlite3.dll")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaOpenGLWidgets.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaWidgets.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "G:/Dev/VistaWidgets/build/win32-x64.vc12/lib/VistaOpenGLWidgets.dll"
    "G:/Dev/VistaWidgets/build/win32-x64.vc12/lib/VistaWidgets.dll"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGraph.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGraphWidgets.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "G:/Dev/VistaGraphLib/build/win32-x64.vc12/lib/VistaGraph.dll"
    "G:/Dev/VistaGraphLib/build/win32-x64.vc12/lib/VistaGraphWidgets.dll"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VflPullDownMenu.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "G:/Dev/VflPullDownMenu/build/win32-x64.vc12/lib/VflPullDownMenu.dll")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VflTextRendering.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "G:/Dev/VflTextRendering/build/win32-x64.vc12/lib/VflTextRendering.dll")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/ftgl.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES "G:/Dev/externals/ftgl/ftgl-2.1.3~rc5/win32-x64.vc12/lib/ftgl.dll")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaCyberGloveDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaCyberGlovePlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaCyberGloveTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaDTrackDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaDTrackPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaDTrackTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaFastrakDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaFastrakPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaFastrakTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutJoystickDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutJoystickPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutJoystickTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutKeyboardDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutKeyboardPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutKeyboardTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutMouseDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutMousePlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaGlutMouseTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaHapticDeviceEmulatorDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaHapticDeviceEmulatorPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaHapticDeviceEmulatorTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaHIDDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaHIDPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaHIDTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaIRManDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaIRManPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaIRManTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaLeapMotionDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaLeapMotionPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaLeapMotionTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaMIDIDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaMIDIPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaMIDITranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaPhantomServerDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaPhantomServerPlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaPhantomServerTranscoder.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaSpaceMouseDriver.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaSpaceMousePlugin.dll;G:/Dev/MenuNav/dist/win32-x64.vc12/bin/VistaSpaceMouseTranscoder.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "G:/Dev/MenuNav/dist/win32-x64.vc12/bin" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaCyberGloveDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaCyberGlovePlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaCyberGloveTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaDTrackDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaDTrackPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaDTrackTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaFastrakDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaFastrakPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaFastrakTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutJoystickDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutJoystickPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutJoystickTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutKeyboardDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutKeyboardPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutKeyboardTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutMouseDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutMousePlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaGlutMouseTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaHapticDeviceEmulatorDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaHapticDeviceEmulatorPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaHapticDeviceEmulatorTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaHIDDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaHIDPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaHIDTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaIRManDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaIRManPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaIRManTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaLeapMotionDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaLeapMotionPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaLeapMotionTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaMIDIDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaMIDIPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaMIDITranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaPhantomServerDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaPhantomServerPlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaPhantomServerTranscoder.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaSpaceMouseDriver.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaSpaceMousePlugin.dll"
    "G:/Dev/ViSTA_Oculus/build/win32-x64.vc12/lib/DriverPlugins/VistaSpaceMouseTranscoder.dll"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY FILES "G:/Dev/MenuNav/configfiles" REGEX "/\\.git$" EXCLUDE REGEX "/[^/]*\\.ini$" REGEX "/[^/]*\\.xml$")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY FILES "G:/Dev/MenuNav/resources" REGEX "/\\.git$" EXCLUDE REGEX "/[^/]*\\.glsl$" REGEX "/[^/]*\\.obj$" REGEX "/[^/]*\\.mtl$" REGEX "/[^/]*\\.txt$" REGEX "/[^/]*\\.png$" REGEX "/[^/]*\\.jpg$" REGEX "/[^/]*\\.3ds$" REGEX "/[^/]*\\.ac$" REGEX "/[^/]*\\.tga$")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "G:/Dev/MenuNav/setup.ini")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES
    "G:/Dev/MenuNav/build/win32-x64.vc12/toinstall/run.bat"
    "G:/Dev/MenuNav/build/win32-x64.vc12/toinstall/run_oculus.bat"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "G:/Dev/MenuNav/build/win32-x64.vc12/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
