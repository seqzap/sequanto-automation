#include <vector>

#include <QtGui>

#include <sequanto/automation.h>
#include <sequanto/thread.h>

#include "mainwin.h"

extern "C" void windows_init_if_not_already();
extern "C" void windows_destroy_if_not_already();

static SQServer server;

extern "C" void close_connection()
{
  windows_destroy_if_not_already();
  
  sq_server_destroy(&server);
}

extern "C" void open_connection()
{
  sq_server_init ( &server, 4321 );

   windows_init_if_not_already();

   sq_server_poll ( &server );
}

int main ( int _argc, char * _argv[] )
{
   QApplication app ( _argc, _argv );

   sq_init ();   
    
   sq_server_init ( &server, 4321 );

   windows_init_if_not_already();

   MainWin mainWin;
   mainWin.show();

   //QtWrapper::Wrap ( qt_root, &mainWin );
   
   sq_server_poll ( &server );

   atexit(sq_shutdown);

   return app.exec();
}
