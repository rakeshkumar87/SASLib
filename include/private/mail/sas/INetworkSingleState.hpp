/*
 * INetworkSingleState.hpp
 *
 *  Created on: Sep 27, 2013
 *      Author: Rakesh
 */

#ifndef INETWORKSINGLESTATE_HPP_
#define INETWORKSINGLESTATE_HPP_

#include "CommunicationService.hpp"
#include <QSharedPointer>

/**
 * An Interface which defines a single state in the state machine.
 */

namespace mail {
namespace sas {

class INetworkSingleState {
public:
	INetworkSingleState(){};
	virtual ~INetworkSingleState(){};
	virtual QSharedPointer<INetworkSingleState> stateMethod( CommunicationService& service ) = 0;
	virtual QString toString() = 0;
};

typedef QSharedPointer<mail::sas::INetworkSingleState> INetworkSingleStateSharedPtr;

}
}

#endif /* INETWORKSINGLESTATE_HPP_ */
