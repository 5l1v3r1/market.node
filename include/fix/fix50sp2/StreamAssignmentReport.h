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

#ifndef FIX50SP2_STREAMASSIGNMENTREPORT_H
#define FIX50SP2_STREAMASSIGNMENTREPORT_H

#include "Message.h"

namespace FIX50SP2
{

  class StreamAssignmentReport : public Message
  {
  public:
    StreamAssignmentReport() : Message(MsgType()) {}
    StreamAssignmentReport(const FIX::Message& m) : Message(m) {}
    StreamAssignmentReport(const Message& m) : Message(m) {}
    StreamAssignmentReport(const StreamAssignmentReport& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("CD"); }

    StreamAssignmentReport(
      const FIX::StreamAsgnRptID& aStreamAsgnRptID )
    : Message(MsgType())
    {
      set(aStreamAsgnRptID);
    }

    FIELD_SET(*this, FIX::StreamAsgnRptID);
    FIELD_SET(*this, FIX::StreamAsgnReqType);
    FIELD_SET(*this, FIX::StreamAsgnReqID);
    FIELD_SET(*this, FIX::NoAsgnReqs);
    class NoAsgnReqs: public FIX::Group
    {
    public:
    NoAsgnReqs() : FIX::Group(1499,453,FIX::message_order(453,146,0)) {}
      FIELD_SET(*this, FIX::NoPartyIDs);
      class NoPartyIDs: public FIX::Group
      {
      public:
      NoPartyIDs() : FIX::Group(453,448,FIX::message_order(448,447,452,802,0)) {}
        FIELD_SET(*this, FIX::PartyID);
        FIELD_SET(*this, FIX::PartyIDSource);
        FIELD_SET(*this, FIX::PartyRole);
        FIELD_SET(*this, FIX::NoPartySubIDs);
        class NoPartySubIDs: public FIX::Group
        {
        public:
        NoPartySubIDs() : FIX::Group(802,523,FIX::message_order(523,803,0)) {}
          FIELD_SET(*this, FIX::PartySubID);
          FIELD_SET(*this, FIX::PartySubIDType);
        };
      };
      FIELD_SET(*this, FIX::NoRelatedSym);
      class NoRelatedSym: public FIX::Group
      {
      public:
      NoRelatedSym() : FIX::Group(146,55,FIX::message_order(55,65,48,22,460,461,167,762,200,541,224,225,239,226,227,228,255,543,470,471,472,240,202,947,206,231,223,207,106,348,349,107,350,351,691,667,875,876,873,874,965,966,1049,967,968,969,970,971,996,997,1079,1151,1146,1147,1227,1191,1192,1193,1194,1195,1196,1198,1199,1200,201,1244,1242,1197,1435,1439,1449,1450,1451,1452,1457,1458,1478,1479,1480,1481,1482,63,1617,1500,1502,58,354,355,0)) {}
        FIELD_SET(*this, FIX::Symbol);
        FIELD_SET(*this, FIX::SymbolSfx);
        FIELD_SET(*this, FIX::SecurityID);
        FIELD_SET(*this, FIX::SecurityIDSource);
        FIELD_SET(*this, FIX::Product);
        FIELD_SET(*this, FIX::CFICode);
        FIELD_SET(*this, FIX::SecurityType);
        FIELD_SET(*this, FIX::SecuritySubType);
        FIELD_SET(*this, FIX::MaturityMonthYear);
        FIELD_SET(*this, FIX::MaturityDate);
        FIELD_SET(*this, FIX::CouponPaymentDate);
        FIELD_SET(*this, FIX::IssueDate);
        FIELD_SET(*this, FIX::RepoCollateralSecurityType);
        FIELD_SET(*this, FIX::RepurchaseTerm);
        FIELD_SET(*this, FIX::RepurchaseRate);
        FIELD_SET(*this, FIX::Factor);
        FIELD_SET(*this, FIX::CreditRating);
        FIELD_SET(*this, FIX::InstrRegistry);
        FIELD_SET(*this, FIX::CountryOfIssue);
        FIELD_SET(*this, FIX::StateOrProvinceOfIssue);
        FIELD_SET(*this, FIX::LocaleOfIssue);
        FIELD_SET(*this, FIX::RedemptionDate);
        FIELD_SET(*this, FIX::StrikePrice);
        FIELD_SET(*this, FIX::StrikeCurrency);
        FIELD_SET(*this, FIX::OptAttribute);
        FIELD_SET(*this, FIX::ContractMultiplier);
        FIELD_SET(*this, FIX::CouponRate);
        FIELD_SET(*this, FIX::SecurityExchange);
        FIELD_SET(*this, FIX::Issuer);
        FIELD_SET(*this, FIX::EncodedIssuerLen);
        FIELD_SET(*this, FIX::EncodedIssuer);
        FIELD_SET(*this, FIX::SecurityDesc);
        FIELD_SET(*this, FIX::EncodedSecurityDescLen);
        FIELD_SET(*this, FIX::EncodedSecurityDesc);
        FIELD_SET(*this, FIX::Pool);
        FIELD_SET(*this, FIX::ContractSettlMonth);
        FIELD_SET(*this, FIX::CPProgram);
        FIELD_SET(*this, FIX::CPRegType);
        FIELD_SET(*this, FIX::DatedDate);
        FIELD_SET(*this, FIX::InterestAccrualDate);
        FIELD_SET(*this, FIX::SecurityStatus);
        FIELD_SET(*this, FIX::SettleOnOpenFlag);
        FIELD_SET(*this, FIX::InstrmtAssignmentMethod);
        FIELD_SET(*this, FIX::StrikeMultiplier);
        FIELD_SET(*this, FIX::StrikeValue);
        FIELD_SET(*this, FIX::MinPriceIncrement);
        FIELD_SET(*this, FIX::PositionLimit);
        FIELD_SET(*this, FIX::NTPositionLimit);
        FIELD_SET(*this, FIX::UnitOfMeasure);
        FIELD_SET(*this, FIX::TimeUnit);
        FIELD_SET(*this, FIX::MaturityTime);
        FIELD_SET(*this, FIX::SecurityGroup);
        FIELD_SET(*this, FIX::MinPriceIncrementAmount);
        FIELD_SET(*this, FIX::UnitOfMeasureQty);
        FIELD_SET(*this, FIX::ProductComplex);
        FIELD_SET(*this, FIX::PriceUnitOfMeasure);
        FIELD_SET(*this, FIX::PriceUnitOfMeasureQty);
        FIELD_SET(*this, FIX::SettlMethod);
        FIELD_SET(*this, FIX::ExerciseStyle);
        FIELD_SET(*this, FIX::OptPayoutAmount);
        FIELD_SET(*this, FIX::PriceQuoteMethod);
        FIELD_SET(*this, FIX::ListMethod);
        FIELD_SET(*this, FIX::CapPrice);
        FIELD_SET(*this, FIX::FloorPrice);
        FIELD_SET(*this, FIX::PutOrCall);
        FIELD_SET(*this, FIX::FlexibleIndicator);
        FIELD_SET(*this, FIX::FlexProductEligibilityIndicator);
        FIELD_SET(*this, FIX::ValuationMethod);
        FIELD_SET(*this, FIX::ContractMultiplierUnit);
        FIELD_SET(*this, FIX::FlowScheduleType);
        FIELD_SET(*this, FIX::RestructuringType);
        FIELD_SET(*this, FIX::Seniority);
        FIELD_SET(*this, FIX::NotionalPercentageOutstanding);
        FIELD_SET(*this, FIX::OriginalNotionalPercentageOutstanding);
        FIELD_SET(*this, FIX::AttachmentPoint);
        FIELD_SET(*this, FIX::DetachmentPoint);
        FIELD_SET(*this, FIX::StrikePriceDeterminationMethod);
        FIELD_SET(*this, FIX::StrikePriceBoundaryMethod);
        FIELD_SET(*this, FIX::StrikePriceBoundaryPrecision);
        FIELD_SET(*this, FIX::UnderlyingPriceDeterminationMethod);
        FIELD_SET(*this, FIX::OptPayoutType);
        FIELD_SET(*this, FIX::SettlType);
        FIELD_SET(*this, FIX::StreamAsgnType);
        FIELD_SET(*this, FIX::MDStreamID);
        FIELD_SET(*this, FIX::StreamAsgnRejReason);
        FIELD_SET(*this, FIX::Text);
        FIELD_SET(*this, FIX::EncodedTextLen);
        FIELD_SET(*this, FIX::EncodedText);
      };
    };
  };

}

#endif
