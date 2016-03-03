/**
   Arduino DUE CAN monitor
   -----------------------
   This sequanto-automation example application will read CAN frames from the CAN0 port on a Arduino DUE board
   and allow the received frames to be read using the sequanto-automation protocol on the CAN port.

   Please see http://seqzap.com/ for more.

   BEGIN AUTOMATION
   property /version get_version
   property /vendor get_vendor
   property /scm_revision get_scm_revision
   function /can/init init_can_device
   property /can/messages number_of_messages
   function /can/pop pop_message
   property /can/id get_message_id
   property /can/priority get_message_priority
   property /can/extended get_message_is_extended
   property /can/length get_message_length
   property /can/data get_message_data
   function /can/send send_message
   END AUTOMATION
*/

#include "SequantoAutomation.h"
#include "code/automation_automation.h"
#include <sequanto/types.h>
#include <due_can.h>

extern "C"
{
  static const char s_version[] = CPACK_PACKAGE_VERSION;
  static const char s_vendor[] = CPACK_PACKAGE_VENDOR;
  static const char s_scm_revision[] = SQ_SCM_REVISION;

  const char* get_version()
  {
    return s_version;
  }

  const char* get_vendor()
  {
    return s_vendor;
  }

  const char* get_scm_revision()
  {
    return s_scm_revision;
  }

  void init_can_device (int baud_rate)
  {
    Can0.init(baud_rate);

    int filter;
    // extended
    for (filter = 0; filter < 3; filter++)
    {
      Can0.setRXFilter(filter, 0, 0, true);
      Can1.setRXFilter(filter, 0, 0, true);
    }  
    //standard
    for (int filter = 3; filter < 7; filter++) 
    {
      Can0.setRXFilter(filter, 0, 0, false);
      Can1.setRXFilter(filter, 0, 0, false);
    }  
  }

  int number_of_messages()
  {
    return Can0.available();
  }

  static CAN_FRAME s_frame;
  static SQByteArray s_data;
  
  SQBool pop_message()
  {
    if (Can0.rx_avail())
    {
      Can0.read(s_frame);
      s_data.m_length = s_frame.length;
      return SQ_TRUE;
    }
    else
    {
      return SQ_FALSE;
    }
  }

  int get_message_id()
  {
    return s_frame.id;
  }

  int get_message_priority()
  {
    return s_frame.priority;
  }

  SQBool get_message_is_extended()
  {
    return s_frame.extended != 0 ? SQ_TRUE : SQ_FALSE;
  }

  int get_message_length()
  {
    return s_frame.length;
  }

  const SQByteArray * get_message_data()
  {
    return &s_data;
  }

  void send_message(int _id, int _priority, SQBool _extended, const SQByteArray * _data)
  {
    s_frame.id = _id;
    s_frame.priority = _priority;
    s_frame.extended = _extended;
    s_frame.length = _data->m_length;
    for ( int i = 0; i < _data->m_length; i++ )
    {
      s_frame.data.bytes[i] = _data->m_start[i];
    }
    Can0.sendFrame(s_frame);
  }
}

void setup() {
  s_frame.length = 0;
  s_data.m_length = 0;
  s_data.m_start = s_frame.data.bytes;
  init_can_device(CAN_BPS_125K);
  SequantoAutomation::init();
}

void loop() {
  SequantoAutomation::poll();
}

