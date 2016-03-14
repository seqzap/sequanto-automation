IF(SQ_ARDUINO)
    FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/arduino_due_can_monitor.ino DESTINATION "${SQ_ARDUINO_OUTPUT}/libraries/SequantoAutomation/examples/arduino_due_can_monitor/")
ENDIF(SQ_ARDUINO)
