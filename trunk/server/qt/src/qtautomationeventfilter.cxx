#include <sequanto/qtautomationeventfilter.h>
#include <cassert>

using namespace sequanto::automation;

const int QtAutomationMoveEvent::ID = QEvent::registerEventType();

QtAutomationMoveEvent::QtAutomationMoveEvent ( int _x, int _y )
   : QEvent( (QEvent::Type) ID),
     m_position(_x, _y)
{
}

const QPoint & QtAutomationMoveEvent::position()
{
   return m_position;
}

QtAutomationMoveEvent::~QtAutomationMoveEvent()
{
}

const int QtAutomationResizeEvent::ID = QEvent::registerEventType();

QtAutomationResizeEvent::QtAutomationResizeEvent ( int _width, int _height )
   : QEvent( (QEvent::Type) ID),
     m_size(_width, _height)
{
}

const QSize & QtAutomationResizeEvent::size()
{
   return m_size;
}

QtAutomationResizeEvent::~QtAutomationResizeEvent()
{
}

QtAutomationEventFilter::QtAutomationEventFilter ( ListNode * _node, QObject * _parent )
      : QObject(_parent),
        m_node ( _node )
{
}

bool QtAutomationEventFilter::eventFilter ( QObject * _object, QEvent * _event )
{
   switch ( _event->type() )
   {
   case QEvent::ChildAdded:
   case QEvent::ChildRemoved:
      m_node->SendUpdate();
      break;

   case QEvent::Move:
      dynamic_cast<IntegerPropertyNode*> ( m_node->FindChild("x") )->SendUpdate();
      dynamic_cast<IntegerPropertyNode*> ( m_node->FindChild("y") )->SendUpdate();
      break;
      
   case QEvent::Resize:
      dynamic_cast<IntegerPropertyNode*> ( m_node->FindChild("width") )->SendUpdate();
      dynamic_cast<IntegerPropertyNode*> ( m_node->FindChild("height") )->SendUpdate();
      break;
      
   case QEvent::Destroy:
      break;
   }

   if ( _event->type() == QtAutomationMoveEvent::ID )
   {
      QPoint position = dynamic_cast<QtAutomationMoveEvent*>(_event)->position();
      qobject_cast<QWidget*> ( _object )->move ( position );
      return true;
   }
   else if ( _event->type() == QtAutomationResizeEvent::ID )
   {
      QSize size = dynamic_cast<QtAutomationResizeEvent*>(_event)->size();
      qobject_cast<QWidget*> ( _object )->resize ( size );
      return true;
   }
   else
   {
      return QObject::eventFilter(_object, _event );
   }
}

QtAutomationEventFilter::~QtAutomationEventFilter ()
{
}