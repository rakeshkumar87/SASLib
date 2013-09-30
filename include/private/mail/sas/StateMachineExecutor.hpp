/*
 * StateMachineExecutor.hpp
 *
 *  Created on: Sep 27, 2013
 *      Author: Rakesh
 */

#ifndef STATEMACHINEEXECUTOR_HPP_
#define STATEMACHINEEXECUTOR_HPP_

#include "INetworkSingleState.hpp"
#include "AccountSettings.hpp"
#include <QStack>

/**
 * Executes a network based state machine,
 * insuring the typical state transitions of Request, Network Send, Network Read, Response occur.
 */

namespace mail {
namespace sas {

class StateMachineExecutor {
public:
	StateMachineExecutor(const AccountSettings& account);
	virtual ~StateMachineExecutor();
	void setFinalState(const INetworkSingleStateSharedPtr& finalState);
	void addState(const INetworkSingleStateSharedPtr& finalState);
	bool execute();

private:
	CommunicationService _cService;
	QStack<INetworkSingleStateSharedPtr> _stack;
};

} /* namespace sas */
} /* namespace mail */
#endif /* STATEMACHINEEXECUTOR_HPP_ */
