// Copyright (c) 2001-2010 quickfixengine.org  All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in
//    the documentation and/or other materials provided with the
//    distribution.
//
// 3. The end-user documentation included with the redistribution,
//    if any, must include the following acknowledgment:
//      "This product includes software developed by
//       quickfixengine.org (http://www.quickfixengine.org/)."
//   Alternately, this acknowledgment may appear in the software itself,
//   if and wherever such third-party acknowledgments normally appear.
//
// 4. The names "QuickFIX" and "quickfixengine.org" must
//    not be used to endorse or promote products derived from this
//    software without prior written permission. For written
//    permission, please contact ask@quickfixengine.org
//
// 5. Products derived from this software may not be called "QuickFIX",
//    nor may "QuickFIX" appear in their name, without prior written
//    permission of quickfixengine.org
//
// THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.  IN NO EVENT SHALL QUICKFIXENGINE.ORG OR
// ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
// USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

#ifndef FIX_APPLICATION_H
#define FIX_APPLICATION_H

#include "Message.h"
#include "SessionID.h"
#include "Mutex.h"

namespace FIX
{
/**
 * This interface must be implemented to define what your %FIX application
 * does.
 *
 * These methods notify your application about events that happen on
 * active %FIX sessions. There is no guarantee how many threads will be calling
 * these functions. If the application is sharing resources among multiple sessions,
 * you must synchronize those resources. You can also use the SynchronizedApplication
 * class to automatically synchronize all function calls into your application.
 * The various MessageCracker classes can be used to parse the generic message
 * structure into specific %FIX messages.
 */
class Application
{
public:
  virtual ~Application() {};
  /// Notification of a session begin created
  virtual void onCreate( const SessionID& ) = 0;
  /// Notification of a session successfully logging on
  virtual void onLogon( const SessionID& ) = 0;
  /// Notification of a session logging off or disconnecting
  virtual void onLogout( const SessionID& ) = 0;
  /// Notification of admin message being sent to target
  virtual void toAdmin( Message&, const SessionID& ) = 0;
  /// Notification of app message being sent to target
  virtual void toApp( Message&, const SessionID& )
  throw( DoNotSend ) = 0;
  /// Notification of admin message being received from target
  virtual void fromAdmin( const Message&, const SessionID& )
  throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon ) = 0;
  /// Notification of app message being received from target
  virtual void fromApp( const Message&, const SessionID& )
  throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType ) = 0;
};

/**
* This is a special implementation of the Application interface that takes
* in another Application interface and synchronizes all of its callbacks. This
* will guarantee that only one thread will access the applications code at a time.
*
* This class is a great convenience for writing applications where you
* don't want to worry about synchronization. There is of course a tradeoff
* in that you may be synchronizing more than you need to. There is also a very
* minor performance penalty due to the extra virtual table lookup.
*/
class SynchronizedApplication : public Application
{
public:
  SynchronizedApplication( Application& app ) : m_app( app ) {}

  void onCreate( const SessionID& sessionID )
  { Locker l( m_mutex ); app().onCreate( sessionID ); }
  void onLogon( const SessionID& sessionID )
  { Locker l( m_mutex ); app().onLogon( sessionID ); }
  void onLogout( const SessionID& sessionID )
  { Locker l( m_mutex ); app().onLogout( sessionID ); }
  void toAdmin( Message& message, const SessionID& sessionID )
  { Locker l( m_mutex ); app().toAdmin( message, sessionID ); }
  void toApp( Message& message, const SessionID& sessionID )
  throw( DoNotSend )
  { Locker l( m_mutex ); app().toApp( message, sessionID ); }
  void fromAdmin( const Message& message, const SessionID& sessionID )
  throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon )
  { Locker l( m_mutex ); app().fromAdmin( message, sessionID ); }
  void fromApp( const Message& message, const SessionID& sessionID )
  throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType )
  { Locker l( m_mutex ); app().fromApp( message, sessionID ); }

  Mutex m_mutex;

  Application& app() { return m_app; }
  Application& m_app;
};

/**
* An empty implementation of an Application. This can be used if you
* do not want to provide an implementation for all the callback methods.
* It is also useful for unit tests writing unit tests where the callback
* values of some or all methods are not of interest.
*/
class NullApplication : public Application
{
  void onCreate( const SessionID& ) {}
  void onLogon( const SessionID& ) {}
  void onLogout( const SessionID& ) {}
  void toAdmin( Message&, const SessionID& ) {}
  void toApp( Message&, const SessionID& )
  throw( DoNotSend ) {}
  void fromAdmin( const Message&, const SessionID& )
  throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, RejectLogon ) {}
  void fromApp( const Message&, const SessionID& )
  throw( FieldNotFound, IncorrectDataFormat, IncorrectTagValue, UnsupportedMessageType ) {}
};
/*! @} */
}

#endif //FIX_APPLICATION_H
