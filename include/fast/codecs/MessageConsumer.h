// Copyright (c) 2009, 2010, 2011 Object Computing, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimer in the documentation
//      and/or other materials provided with the distribution.
//    * Neither the name of Object Computing, Inc. nor the names of its
//      contributors may be used to endorse or promote products derived from this
//      software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifdef _MSC_VER
# pragma once
#endif
#ifndef MESSAGECONSUMER_H
#define MESSAGECONSUMER_H
#include "MessageConsumer_fwd.h"
#include <Common/QuickFAST_Export.h>
#include <Messages/Message_fwd.h>
#include <Common/Logger.h>

namespace QuickFAST{
  namespace Codecs{
    /// @brief interface to be implemented by a consumer of decoded messages.
    class MessageConsumer : public Common::Logger
    {
    public:
      virtual ~MessageConsumer(){}
      /// @brief Accept a decoded message
      /// @param message is the decoded message, valid for the life of this call.
      /// @returns true if decoding should continue; false to stop decoding
      virtual bool consumeMessage(Messages::Message & message) = 0;

      /// @brief Notify consumer when decoding starts.
      ///
      /// This will be called before any call to consumeMessage().
      virtual void decodingStarted() = 0;

      /// @brief notify consumer that decoding has stopped.
      ///
      /// No calls to consumeMessage() will be generated after this call.
      virtual void decodingStopped() = 0;
    };
  }
}
#endif /* MESSAGECONSUMER_H */
