/*
 * INetworkExceptionState.hpp
 *
 *  Created on: Sep 27, 2013
 *      Author: Rakesh
 */

#ifndef INETWORKEXCEPTIONSTATE_HPP_
#define INETWORKEXCEPTIONSTATE_HPP_

#include "INetworkSingleState.hpp"
#include <QSharedPointer>

/**
 * An exception state to report network errors, parsing errors etc.
 */
namespace mail {
namespace sas {

class INetworkExceptionState : public mail::sas::INetworkSingleState {
public:
	INetworkExceptionState(const QString& error);
	virtual ~INetworkExceptionState();
	virtual mail::sas::INetworkSingleStateSharedPtr stateMethod(CommunicationService& service);
	virtual QString toString() { return _error; }

private:
	QString _error;
};

} /* namespace sas */
} /* namespace mail */

#endif /* INETWORKEXCEPTIONSTATE_HPP_ */
