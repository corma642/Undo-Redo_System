#include <iostream>
#include "Vector.h"
#include "Stack.h" 
#include "Queue.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

class ICommand
{
public:
	virtual ~ICommand() {}

	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual char GetChar() const = 0;
};

// A Ŀ�ǵ�
class CommandA : public ICommand
{
public:
	CommandA(char ch, char* curChar)
		: inputChar(ch), curChar(curChar), prevChar(*curChar)
	{
	}

	// ���� ���ڸ� �Է����� ���� ���ڷ� �ʱ�ȭ
	void Execute() override
	{
		*curChar = inputChar;
	}

	// ���� ���ڸ� ���� �Է� ���ڷ� �ʱ�ȭ
	void Undo() override
	{
		*curChar = prevChar;
	}

	// �Է����� ���� ���� ��ȯ
	char GetChar() const override
	{
		return inputChar;
	}

private:
	char inputChar;		// �Է����� ���� ����
	char* curChar;		// ���� ����
	char prevChar;		// ���� �Է� ����
};

// B Ŀ�ǵ�
class CommandB : public ICommand
{
public:
	CommandB(char ch, char* curChar)
		: inputChar(ch), curChar(curChar), prevChar(*curChar)
	{
	}

	// ���� ���ڸ� �Է����� ���� ���ڷ� �ʱ�ȭ
	void Execute() override
	{
		*curChar = inputChar;
	}

	// ���� ���ڸ� ���� �Է� ���ڷ� �ʱ�ȭ
	void Undo() override
	{
		*curChar = prevChar;
	}

	// �Է����� ���� ���� ��ȯ
	char GetChar() const override
	{
		return inputChar;
	}

private:
	char inputChar;		// �Է����� ���� ����
	char* curChar;		// ���� ����
	char prevChar;		// ���� �Է� ����
};

// C Ŀ�ǵ�
class CommandC : public ICommand
{
public:
	CommandC(char ch, char* curChar)
		: inputChar(ch), curChar(curChar), prevChar(*curChar)
	{
	}

	// ���� ���ڸ� �Է����� ���� ���ڷ� �ʱ�ȭ
	void Execute() override
	{
		*curChar = inputChar;
	}

	// ���� ���ڸ� ���� �Է� ���ڷ� �ʱ�ȭ
	void Undo() override
	{
		*curChar = prevChar;
	}

	// �Է����� ���� ���� ��ȯ
	char GetChar() const override
	{
		return inputChar;
	}

private:
	char inputChar;		// �Է����� ���� ����
	char* curChar;		// ���� ����
	char prevChar;		// ���� �Է� ����
};

// D Ŀ�ǵ�
class CommandD : public ICommand
{
public:
	CommandD(char ch, char* curChar)
		: inputChar(ch), curChar(curChar), prevChar(*curChar)
	{
	}

	// ���� ���ڸ� �Է����� ���� ���ڷ� �ʱ�ȭ
	void Execute() override
	{
		*curChar = inputChar;
	}

	// ���� ���ڸ� ���� �Է� ���ڷ� �ʱ�ȭ
	void Undo() override
	{
		*curChar = prevChar;
	}

	// �Է����� ���� ���� ��ȯ
	char GetChar() const override
	{
		return inputChar;
	}

private:
	char inputChar;		// �Է����� ���� ����
	char* curChar;		// ���� ����
	char prevChar;		// ���� �Է� ����
};

// E Ŀ�ǵ�
class CommandE : public ICommand
{
public:
	CommandE(char ch, char* curChar)
		: inputChar(ch), curChar(curChar), prevChar(*curChar)
	{
	}

	// ���� ���ڸ� �Է����� ���� ���ڷ� �ʱ�ȭ
	void Execute() override
	{
		*curChar = inputChar;
	}

	// ���� ���ڸ� ���� �Է� ���ڷ� �ʱ�ȭ
	void Undo() override
	{
		*curChar = prevChar;
	}

	// �Է����� ���� ���� ��ȯ
	char GetChar() const override
	{
		return inputChar;
	}

private:
	char inputChar;		// �Է����� ���� ����
	char* curChar;		// ���� ����
	char prevChar;		// ���� �Է� ����
};

// Ŀ�ǵ� ��ɾ� ���� Ŭ����
class CommandManager
{
public:
	CommandManager(char* current) : currentChar(current) {}

	~CommandManager()
	{
		// �޸� ����
		while (!undoStack.Empty())
		{
			delete undoStack.Top();
			undoStack.Pop();
		}

		while (!redoStack.Empty())
		{
			delete redoStack.Top();
			redoStack.Pop();
		}
	}

	void ExecuteCommand(ICommand* command)
	{
		// redo ���� �ʱ�ȭ (���ο� �Է� Ŀ�ǵ尡 �������Ƿ�)
		while (!redoStack.Empty())
		{
			delete redoStack.Top();
			redoStack.Pop();
		}

		command->Execute();
		undoStack.Push(command);
	}

	void Undo()
	{
		if (undoStack.Empty()) return;

		ICommand* command = undoStack.Top();
		undoStack.Pop();

		command->Undo();
		redoStack.Push(command);
	}

	void Redo()
	{
		if (redoStack.Empty()) return;

		ICommand* command = redoStack.Top();
		redoStack.Pop();

		command->Execute();
		undoStack.Push(command);
	}

	void Show() const
	{
		std::cout << "Undo List: ";

		if (undoStack.Empty())
		{
			std::cout << "(�������)";
		}
		else
		{
			int undoStackSize = undoStack.Size();

			for (int i = 0; i < undoStack.Size(); ++i)
			{
				std::cout << undoStack.GetData()[i]->GetChar() << (i < undoStackSize - 1 ? ", " : "");
			}
		}

		std::cout << " | Redo List: ";

		if (redoStack.Empty())
		{
			std::cout << "(�������)";
		}
		else
		{
			int redoStackSize = redoStack.Size();

			for (int i = 0; i < redoStackSize; ++i)
			{
				std::cout << redoStack.GetData()[i]->GetChar() << (i < redoStackSize - 1 ? ", " : "");
			}
		}

		std::cout << "\n\n";
	}

private:
	// Undo ����
	Stack<ICommand*> undoStack;

	// Rndo ����
	Stack<ICommand*> redoStack;

	// ���� ����
	char* currentChar;
};

// UndoRedo ���α׷� Ŭ����
class UndoRedoProgram
{
public:
	UndoRedoProgram()
		: currentChar(' ')
	{
		commandManager = new CommandManager(&currentChar);
	}

	~UndoRedoProgram()
	{
		delete commandManager;
	}

	// �Է¿� ���� ���μ��� �����ϴ� �Լ�
	void ProcessInput(const char* input)
	{
		if (!strcmp(input, "undo")) commandManager->Undo();			// undo ��ɾ� ����
		else if (!strcmp(input, "redo")) commandManager->Redo();	// redo ��ɾ� ����
		else if (!strcmp(input, "show")) commandManager->Show();	// show ��ɾ� ����

		// �Է� ���ڰ� 1�������� �˻�
		else if (strlen(input) == 1)
		{
			// �ҹ��ڸ� �빮�ڷ� ��ȯ
			char ch = toupper(input[0]);

			// �Է� ó���� �� Ŀ�ǵ�
			ICommand* command = nullptr;

			switch (ch)
			{
			case 'A': command = new CommandA(ch, &currentChar); break;
			case 'B': command = new CommandB(ch, &currentChar); break;
			case 'C': command = new CommandC(ch, &currentChar); break;
			case 'D': command = new CommandD(ch, &currentChar); break;
			case 'E': command = new CommandE(ch, &currentChar); break;

			default: std::cout << "�߸��� �Է��Դϴ�. A, B, C, D, E�� �Է��ϼ���." << "\n\n";
			}

			// �Է� Ŀ�ǵ� ��� ����
			inputCommandQueue.Push(command);

			// �ش� ���ڿ� ���� Ŀ�ǵ� ����
			commandManager->ExecuteCommand(command);
		}
		else std::cout << "�߸��� �Է��Դϴ�. A, B, C, D, E�� �Է��ϼ���." << "\n\n";
	}

	// ���� ���� ��ȯ
	char GetCurrentChar() const { return currentChar; }

private:
	// ���� ����
	char currentChar;

	// �Է� Ŀ�ǵ� ����� �����ϴ� ť
	Queue<ICommand*> inputCommandQueue;

	// �Է� ó�� Ŀ�ǵ� 
	CommandManager* commandManager;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Undo/Redo ���α׷� ��ü �����Ҵ�
	UndoRedoProgram* program = new UndoRedoProgram();

	while (true)
	{
		std::cout << "���ڸ� �Է��� �ּ���. (A, B, C, D, E) (����� '0')" << "\n";
		std::cout << "��ɾ�: 'undo', 'redo', 'show'" << "\n";
		std::cout << "���� ����: " << program->GetCurrentChar() << "\n";
		std::cout << "> ";

		char inputBuffer[100];
		std::cin >> inputBuffer;
		system("cls");

		// 0�� �Է����� ������ ���α׷� ����
		if (inputBuffer[0] == '0') break;

		// �Է¿� ���� ���μ��� ����
		program->ProcessInput(inputBuffer);
	}

	// �޸� ����
	delete program;
}