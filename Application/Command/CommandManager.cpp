#include "CommandManager.h"

CommandManager::CommandManager()
    : m_ExecuteList{}
	, m_UndoList{}
{
}

CommandManager::~CommandManager()
{
	clear();
}

bool CommandManager::regist(CommandPtr && command)
{
	if (!command->execute())
	{
		return false;
	}
	m_ExecuteList.push_back(std::move(command));
	m_UndoList.clear();
	while (m_ExecuteList.size() > m_Capacity)
	{
		m_ExecuteList.pop_front();
	}
	return true;
}

void CommandManager::clear()
{
	m_ExecuteList.clear();
	m_UndoList.clear();
}

bool CommandManager::undo()
{
	if (m_ExecuteList.size() == 0)
	{
		return false;
	}
	auto command = std::move(m_ExecuteList.back());
	m_ExecuteList.pop_back();
	if (!command->undo())
	{
		return false;
	}
	m_UndoList.push_back(std::move(command));
	return true;
}

bool CommandManager::redo()
{
	if (m_UndoList.size() == 0)
	{
		return false;
	}
	auto command = std::move(m_UndoList.back());
	m_UndoList.pop_back();
	return regist(std::move(command));
}

const std::list<CommandPtr>& CommandManager::executeList() const
{
	return m_ExecuteList;
}

const std::list<CommandPtr>& CommandManager::undoList() const
{
	return m_UndoList;
}

void CommandManager::setExecuteCommandCapacity(std::size_t capacity)
{
	m_Capacity = capacity;
	while (m_ExecuteList.size() > m_Capacity)
	{
		m_ExecuteList.pop_front();
	}
}
