#ifndef ICOMMAND_H_
#define ICOMMAND_H_

#include <memory>
#include <string>

class ICommand
{
public:

	virtual ~ICommand() = default;

	virtual bool execute() = 0;

	virtual bool undo() = 0;

	virtual bool redo() = 0;

	virtual std::string logStr() const = 0;
};

using CommandPtr = std::unique_ptr<ICommand>;

#endif // !ICOMMAND_H_
