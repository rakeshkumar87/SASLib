/*
 * StateMachineExecutor.cpp
 *
 *  Created on: Sep 27, 2013
 *      Author: Rakesh
 */

#include "StateMachineExecutor.hpp"
#include "INetworkExceptionState.hpp"
#include <QSharedPointer>
#include <QObject>

namespace mail {
namespace sas {

StateMachineExecutor::StateMachineExecutor(const AccountSettings& account)
    : _cService(account)
{
}

StateMachineExecutor::~StateMachineExecutor() {
	// TODO Auto-generated destructor stub
}

void StateMachineExecutor::setFinalState(const INetworkSingleStateSharedPtr& finalState) {
	_stack.clear();
	addState(finalState);
}

void StateMachineExecutor::addState(const INetworkSingleStateSharedPtr& state) {
	_stack.push(state);
}

bool StateMachineExecutor::execute() {
	bool retVal = true;
    INetworkSingleStateSharedPtr nextState;
	while( !_stack.isEmpty() ) {
        nextState = _stack.pop();
        nextState = nextState->stateMethod(_cService);

        if ( !nextState.isNull() ) {

        	if (dynamic_cast<INetworkExceptionState*>(nextState.data()) != NULL) {
                qDebug() << "Exception during execution of state machine:" << nextState->toString();
        		_stack.clear();
                break;
        	}

            _stack.push(nextState);
        }
	}

	return retVal;
}

} /* namespace sas */
} /* namespace mail */

