#
# type_tests
#

SQ_GENERATE(type_tests type_tests.automation)
ADD_EXECUTABLE(type_tests  type_tests.c ${SQ_GENERATE_type_tests})

ADD_SUBDIRECTORY(type_tests_disabled)

TARGET_LINK_LIBRARIES(type_tests SequantoAutomation)

ADD_CUSTOM_TARGET(run_type_tests ./type_tests DEPENDS type_tests)

IF(UNIX)
  SQ_GENERATE(liab_test liab_test.automation)
  ADD_EXECUTABLE(liab_test liab_test.c ${SQ_GENERATE_liab_test})
  TARGET_LINK_LIBRARIES(liab_test SequantoAutomation)
ENDIF(UNIX)

IF(SQ_ARDUINO)
    SQ_GENERATE_INO(type_tests type_tests.automation type_tests.c)
ENDIF(SQ_ARDUINO)
