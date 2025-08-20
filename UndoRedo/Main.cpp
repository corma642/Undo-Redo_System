#include <iostream>
#include "Vector.h"
#include "Stack.h" 
#include "Queue.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

class Command
{
public:
	virtual ~Command() {}

	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual char GetChar() const = 0;
};

// �Է� ���� ���� Ŭ����
class InputCommand : public Command
{
public:
	InputCommand(char ch, char* current)
		: character(ch), currentChar(current), prevChar(*current)
	{
	}

	void Execute() override
	{
		// ���� ���ڸ� �Է����� ���� ���ڷ� �ʱ�ȭ
		*currentChar = character;
	}

	void Undo() override
	{
		// ���� ���ڸ� ���� �Է� ���ڷ� �ʱ�ȭ
		*currentChar = prevChar;
	}

	char GetChar() const override
	{
		// �Է����� ���� ���� ��ȯ
		return character;
	}

private:
	// �Է����� ���� ����
	char character;

	// ���� ����
	char* currentChar;

	// ���� �Է� ����
	char prevChar;
};

// �Է� ó�� ��ɾ� ����� Undo/Redo ���� Ŭ����
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

	void ExecuteCommand(Command* command)
	{
		// redo ���� �ʱ�ȭ
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

		Command* command = undoStack.Top();
		undoStack.Pop();

		command->Undo();
		redoStack.Push(command);
	}

	void Redo()
	{
		if (redoStack.Empty()) return;

		Command* command = redoStack.Top();
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
	Stack<Command*> undoStack;

	// Rndo ����
	Stack<Command*> redoStack;

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

	// ��ȿ�� �Է� �������� Ȯ���ϴ� �Լ�
	bool IsValidInput(char& ch) const
	{
		return (ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D' || ch == 'E');
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

			// ��ȿ���� ���� ���� ���� ó��
			if (!IsValidInput(ch))
			{
				std::cout << "�߸��� �Է��Դϴ�. A, B, C, D, E�� �Է��ϼ���." << "\n\n";
				return;
			}

			// �Է� ť�� �Է� ���μ����� ������ ���� ����
			inputQueue.Push(ch);

			// 
			Command* command = new InputCommand(ch, &currentChar);

			// �ش� ���ڿ� ���� Ŀ�ǵ� ����
			commandManager->ExecuteCommand(command);
		}
		else std::cout << "�߸��� �Է��Դϴ�. A, B, C, D, E�� �Է��ϼ���." << "\n\n";
	}

	void Run()
	{
		while (true)
		{
			std::cout << "���ڸ� �Է��� �ּ���. (A, B, C, D, E) (����� '0')" << "\n";
			std::cout << "��ɾ�: 'undo', 'redo', 'show'" << "\n";
			std::cout << "���� ����: " << currentChar << "\n";
			std::cout << "> ";

			char inputBuffer[100];
			std::cin >> inputBuffer;
			system("cls");

			// 0�� �Է����� ������ ���α׷� ����
			if (inputBuffer[0] == '0') break;

			// �Է¿� ���� ���μ��� ����
			ProcessInput(inputBuffer);
		}
	}

private:
	// ���� ����
	char currentChar;

	// �Է� ť
	Queue<char> inputQueue;

	// �Է� ó�� Ŀ�ǵ� 
	CommandManager* commandManager;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UndoRedoProgram program;
	program.Run();
}