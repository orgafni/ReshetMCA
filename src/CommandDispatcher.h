/*
 * CommandDispatcher.h
 *
 *  Created on: May 14, 2016
 *      Author: Or Gafni
 */

#ifndef COMMANDDISPATCHER_H_
#define COMMANDDISPATCHER_H_

#include "MThread.h"

// forward decleration
class ClientManager;

class CommandDispatcher : public MThread
{
private:
	ClientManager* m_manager;
public:
	CommandDispatcher(ClientManager* manager);
	void run();


};

#endif /* COMMANDDISPATCHER_H_ */
