#include "SequantoAutomation.h"
#include <sequanto/automation.h>

#include "utility/src/sq_server.c"
#include "utility/src/sq_parser.c"
#ifdef SQ_ARDUINO_CAN
#include "utility/src/sq_stream_arduino_due_can.c"
#else
#include "utility/src/sq_stream_arduino.c"
#endif
#include "utility/src/sq_value.c"
#include "utility/src/sq_types.c"
#include "utility/src/sq_protocol.c"
#include "utility/src/sq_log.c"
#include "utility/src/sq_thread.c"
#include "utility/src/sq_automation.c"

static SQServer _server;

void SequantoAutomation::init()
{
    sq_init();
    sq_server_init ( &_server, 4321 );
}

void SequantoAutomation::poll()
{
    sq_server_poll ( &_server );
}
