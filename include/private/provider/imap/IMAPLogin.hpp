/*
 * IMAPLogin.hpp
 *
 *  Created on: Sep 27, 2013
 *      Author: Rakesh
 */

#ifndef IMAPLOGIN_HPP_
#define IMAPLOGIN_HPP_

#include "INetworkSingleState.hpp"
#include "AccountSettings.hpp"
#include <QSharedPointer>

namespace provider {
namespace imap {

class IMAPLoginRequest : public mail::sas::INetworkSingleState
{
public:
	IMAPLoginRequest(const mail::sas::AccountSettings& account);
	virtual ~IMAPLoginRequest();
	mail::sas::INetworkSingleStateSharedPtr stateMethod( mail::sas::CommunicationService& service);
	QString toString() { return "IMapLoginRequest"; }

private:
	mail::sas::AccountSettings _account;
};

class IMAPLoginResponse : public mail::sas::INetworkSingleState
{
public:
	IMAPLoginResponse();
	virtual ~IMAPLoginResponse();
	mail::sas::INetworkSingleStateSharedPtr stateMethod( mail::sas::CommunicationService& service );
	QString toString() { return "IMapLoginResponse"; }
};

}
}
#endif /* IMAPLOGIN_HPP_ */
