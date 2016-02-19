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
  }

  int number_of_messages()
  {
    return Can0.available();
  }

  static CAN_FRAME s_frame;

  SQBool pop_message()
  {
    if (Can0.rx_avail())
    {
      Can0.read(s_frame);
      //s_data.m_length = s_frame.length;
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

  static char s_data[8 * 2 + 1];

  const char * get_message_data()
  {
    int i;
    for ( i; i < s_frame.length; i++ )
    {
      s_data[i] = '0' + s_frame.data.bytes[i] & 0x0F;
      s_data[i + 1] = '0' + ((s_frame.data.bytes[i] & 0xF0) >> 4);
    }
    s_data[i * 2] = '\0';
    return s_data;
    //return sq_byte_array_create((SQByte*) &s_frame.data, s_frame.length);
    //s_data.m_start = (SQByte*) &s_frame.data;
    //s_data.m_length = 0;
    //return &s_data;
  }

  void send_message(int _id, int _priority, SQBool _extended, SQByteArray * _data)
  {
    s_frame.id = _id;
    s_frame.priority = _priority;
    s_frame.extended = _extended;
    s_frame.length = _data->m_length;
    for ( int i = 0; i++; i < _data->m_length )
    {
      s_frame.data.bytes[i] = _data->m_start[i];
    }
    Can0.sendFrame(s_frame);
  }
}

void setup() {
  s_frame.length = 0;
  SequantoAutomation::init();
}

void loop() {
  SequantoAutomation::poll();
}

