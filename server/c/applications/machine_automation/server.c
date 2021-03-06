#include <sequanto/automation.h>

#include "config.h"
#include "machine_automation.h"
#include "common.h"

#ifdef SQ_WIN32
#include <windows.h>

int server_process_id ()
{
   return GetCurrentProcessId();
}

#else

#include <unistd.h>

int server_process_id ()
{
    return getpid();
}

#endif

const char * server_revision ( void )
{
   static char buff[] = SQ_SCM_REVISION;
   
   return buff;
}

const char * server_version ( void )
{
   static char buff[] = CPACK_PACKAGE_VERSION;
   
   return buff;
}

const char * server_vendor ( void )
{
   static char buff[] = CPACK_PACKAGE_VENDOR;
   
   return buff;
}

void server_quit ( void )
{
   sq_server_destroy ( sq_server_get_instance() );
}

