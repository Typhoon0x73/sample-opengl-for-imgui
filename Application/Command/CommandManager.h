#ifndef COMMANDMANAGER_H_
#define COMMANDMANAGER_H_

#include "ICommand.h"
#include <list>

class CommandManager
{
public:

	explicit CommandManager();

	virtual ~CommandManager();

	bool regist(CommandPtr&& command);

	void clear();

	bool undo();

	bool redo();

public:

	const std::list<CommandPtr>& executeList() const;

	const std::list<CommandPtr>& undoList() const;

	void setExecuteCommandCapacity(std::size_t capacity);

private:

	std::size_t           m_Capacity{ 50 };
	std::list<CommandPtr> m_ExecuteList;
	std::list<CommandPtr> m_UndoList;
};

#endif // !COMMANDMANAGER_H_
