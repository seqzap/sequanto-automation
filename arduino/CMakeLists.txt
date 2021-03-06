IF(SQ_ARDUINO)
    FIND_PACKAGE(Java REQUIRED)
    INCLUDE(UseJava)

    IF(EXISTS "${SQ_ARDUINO_IDE_PATH}/lib/core.jar")
        SET(SQ_ARDUINO_16 FALSE)
        MESSAGE("Using Arduino 1.0.x IDE at ${SQ_ARDUINO_IDE_PATH}")
        MESSAGE("Using ${SQ_ARDUINO_IDE_PATH}/lib/core.jar")
    ELSE()
        IF(EXISTS "${SQ_ARDUINO_IDE_PATH}/lib/arduino-core.jar")
            SET(SQ_ARDUINO_16 TRUE)
            MESSAGE("Using Arduino IDE 1.6 at ${SQ_ARDUINO_IDE_PATH}")
            MESSAGE("Using ${SQ_ARDUINO_IDE_PATH}/lib/arduino-core.jar")
        ELSE()
            MESSAGE(SEND_ERROR "Could not find core.jar at ${SQ_ARDUINO_IDE_PATH}/lib/core.jar")
        ENDIF()
    ENDIF()

    IF(EXISTS "${SQ_ARDUINO_IDE_PATH}/lib/pde.jar")
        MESSAGE("Using ${SQ_ARDUINO_IDE_PATH}/lib/pde.jar")
    ELSE()
        MESSAGE(SEND_ERROR "Could not find pde.jar at ${SQ_ARDUINO_IDE_PATH}/lib/pde.jar")
    ENDIF()

    SET(CMAKE_JAVA_COMPILE_FLAGS "-target" "1.5" "-source" "1.5")

    IF(SQ_ARDUINO_16)
        ADD_JAR(SequantoAutomationTool tools/SequantoAutomationTool/src/SequantoAutomationTool.java INCLUDE_JARS "${SQ_ARDUINO_IDE_PATH}/lib/arduino-core.jar" "${SQ_ARDUINO_IDE_PATH}/lib/pde.jar" "${SQ_ARDUINO_IDE_PATH}/lib/commons-codec-1.7.jar")
    ELSE(SQ_ARDUINO_16)
        ADD_JAR(SequantoAutomationTool tools/SequantoAutomationTool/src/SequantoAutomationTool.java INCLUDE_JARS "${SQ_ARDUINO_IDE_PATH}/lib/core.jar" "${SQ_ARDUINO_IDE_PATH}/lib/pde.jar")
    ENDIF(SQ_ARDUINO_16)

    MESSAGE(STATUS "SequantoAutomation version: ${CPACK_PACKAGE_VERSION}")

    FILE(STRINGS ${SQ_ARDUINO_IDE_PATH}/revisions.txt SQ_ARDUINO_IDE_REVISIONS
      LIMIT_COUNT 1)

    STRING(REGEX REPLACE "^ARDUINO ([0-9\\.]+).*" "\\1" SQ_ARDUINO_IDE_VERSION "${SQ_ARDUINO_IDE_REVISIONS}")
    MESSAGE(STATUS "Arduino IDE version: ${SQ_ARDUINO_IDE_VERSION}")

    GET_TARGET_PROPERTY(_jarFile SequantoAutomationTool JAR_FILE)
    GET_TARGET_PROPERTY(_classDir SequantoAutomationTool CLASSDIR)

    MESSAGE(STATUS "Jar file ${_jarFile}")
    MESSAGE(STATUS "Class compiled to ${_classDir}")

    CONFIGURE_FILE(libraries/SequantoAutomation/utility/src/config.h.in "${SQ_ARDUINO_OUTPUT}/libraries/SequantoAutomation/utility/src/config.h")

    ADD_CUSTOM_COMMAND(TARGET SequantoAutomationTool POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${_jarFile}" "${SQ_ARDUINO_OUTPUT}/tools/SequantoAutomationTool/tool/SequantoAutomationTool.jar")

    FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/libraries DESTINATION "${SQ_ARDUINO_OUTPUT}")

    GET_FILENAME_COMPONENT(SQ_ARDUINO_OUTPUT_ABS ${SQ_ARDUINO_OUTPUT} ABSOLUTE)
    GET_FILENAME_COMPONENT(SQ_ARDUINO_OUTPUT_NAME ${SQ_ARDUINO_OUTPUT} NAME)
    ADD_CUSTOM_COMMAND(TARGET SequantoAutomationTool POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E tar "cfv" "${SQ_ARDUINO_OUTPUT}.zip" --format=zip ${SQ_ARDUINO_OUTPUT_NAME}
      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

    MACRO(SQ_GENERATE_INO name automation)
        FILE(WRITE  "${SQ_ARDUINO_OUTPUT}/libraries/SequantoAutomation/examples/${name}/${name}.ino" "/*\n\n")
        FILE(APPEND "${SQ_ARDUINO_OUTPUT}/libraries/SequantoAutomation/examples/${name}/${name}.ino" "   Thank you for using sequanto-automation, please see\n")
        FILE(APPEND "${SQ_ARDUINO_OUTPUT}/libraries/SequantoAutomation/examples/${name}/${name}.ino" "   http://www.seqzap.com/SeqZapManuals/SeqZapTools/automationtoolbox-arduino.html for more\n\n")
        FILE(APPEND "${SQ_ARDUINO_OUTPUT}/libraries/SequantoAutomation/examples/${name}/${name}.ino" "   Use the Tools->Generate Automation menu item before compiling\n\n")
        FILE(APPEND "${SQ_ARDUINO_OUTPUT}/libraries/SequantoAutomation/examples/${name}/${name}.ino" "BEGIN AUTOMATION\n\n")
        FILE(READ ${automation} CONT)
        STRING(REPLACE "name " "#name " CONT ${CONT})
        STRING(REPLACE "import " "#import " CONT ${CONT})
        FILE(APPEND "${SQ_ARDUINO_OUTPUT}/libraries/SequantoAutomation/examples/${name}/${name}.ino" "${CONT}")
        FILE(APPEND "${SQ_ARDUINO_OUTPUT}/libraries/SequantoAutomation/examples/${name}/${name}.ino" "\n\nEND AUTOMATION */\n\n")
        FOREACH(source ${ARGN})
            FILE(READ ${source} CONT)
            FILE(APPEND "${SQ_ARDUINO_OUTPUT}/libraries/SequantoAutomation/examples/${name}/${name}.ino" "${CONT}")
        ENDFOREACH()
    ENDMACRO()
ENDIF(SQ_ARDUINO)
