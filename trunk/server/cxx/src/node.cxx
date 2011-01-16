#include <sequanto/log.h>
#include <sequanto/server.h>
#include <sequanto/node.h>
#include <stdexcept>
#include <string>

using namespace std;
using namespace sequanto::automation;

Node::Node ( const std::string & _name )
   : m_parent ( NULL ),
     m_name ( _name )
{
   if ( _name.empty() )
   {
      throw runtime_error ( "SequantoAutomation_CXX: Node name can not be empty." );
   }
   if ( !IsValidName(_name) )
   {
      throw runtime_error ( "SequantoAutomation_CXX: Node name contains illegal characters, only alpha-numeric, dash and underscore are valid characters." );
   }
}

bool Node::IsValidName ( const std::string & _name )
{
   return IsValidName ( _name.data(), _name.length() );
}

bool Node::IsValidName ( const char * const _name, size_t _length )
{
   if ( _length == 0 )
   {
      return false;
   }
   for ( size_t i = 0; i < _length; i++ )
   {
      if ( !::isalnum(_name[i]) && _name[i] != '_' && _name[i] != '-' )
      {
         return false;
      }
   }
   return true;
}

Node * Node::GetParent () const
{
   return m_parent;
}

void Node::SetParent ( Node * _parent )
{
   if ( m_parent != NULL )
   {
      throw std::runtime_error ( "SequantoAutomation_CXX: This node already has a parent associated with it." );
   }
   m_parent = _parent;
}


const std::string & Node::GetName () const
{
   return m_name;
}

const std::string & Node::GetFullName ()
{
   if ( m_fullname.empty() )
   {
      std::string slash ( "/" );
      const Node * curr = this;
      while ( curr != NULL )
      {
         m_fullname = slash + curr->GetName() + m_fullname;
         curr = curr->GetParent();
      }
   }
   return m_fullname;
}

Node * Node::FindChild ( const std::string & _name ) const
{

   return NULL;
}

Node::Iterator * Node::ListChildren () const
{
   return NULL;
}

void Node::HandleGet ( SQValue & _outputValue )
{
}

void Node::HandleSet ( const SQValue * const _value )
{
}

void Node::HandleCall ( size_t _numberOfValues, const SQValue * const _inputValues, SQValue & _output )
{
}

void Node::HandleMonitorStateChange ( bool _enable )
{
}

void Node::LogAsync ( const std::string & _message ) const
{
   sq_log ( _message.c_str() );
}

Node::~Node()
{
}

Node::Iterator::~Iterator()
{
}
