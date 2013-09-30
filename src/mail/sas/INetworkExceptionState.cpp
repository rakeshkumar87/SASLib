/*
 * INetworkExceptionState.cpp
 *
 *  Created on: Sep 27, 2013
 *      Author: Rakesh
 */

#include "INetworkExceptionState.hpp"

namespace mail {
namespace sas {

INetworkExceptionState::INetworkExceptionState(const QString& error) {
	_error = error;
}

INetworkExceptionState::~INetworkExceptionState() {
	// TODO Auto-generated destructor stub
}

mail::sas::INetworkSingleStateSharedPtr INetworkExceptionState::stateMethod(mail::sas::CommunicationService& service) {
	return QSharedPointer<INetworkSingleState>();
}

} /* namespace sas */
} /* namespace mail */
