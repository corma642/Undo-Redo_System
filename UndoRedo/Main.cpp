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

// 입력 문자 관리 클래스
class InputCommand : public Command
{
public:
	InputCommand(char ch, char* current)
		: character(ch), currentChar(current), prevChar(*current)
	{
	}

	void Execute() override
	{
		// 현재 문자를 입력으로 받은 문자로 초기화
		*currentChar = character;
	}

	void Undo() override
	{
		// 현재 문자를 이전 입력 문자로 초기화
		*currentChar = prevChar;
	}

	char GetChar() const override
	{
		// 입력으로 받은 문자 반환
		return character;
	}

private:
	// 입력으로 받은 문자
	char character;

	// 현재 문자
	char* currentChar;

	// 이전 입력 문자
	char prevChar;
};

// 입력 처리 명령어 실행과 Undo/Redo 관리 클래스
class CommandManager
{
public:
	CommandManager(char* current) : currentChar(current) {}

	~CommandManager()
	{
		// 메모리 정리
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
		// redo 스택 초기화
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
			std::cout << "(비어있음)";
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
			std::cout << "(비어있음)";
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
	// Undo 스택
	Stack<Command*> undoStack;

	// Rndo 스택
	Stack<Command*> redoStack;

	// 현재 문자
	char* currentChar;
};

// UndoRedo 프로그램 클래스
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

	// 유효한 입력 문자인지 확인하는 함수
	bool IsValidInput(char& ch) const
	{
		return (ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D' || ch == 'E');
	}

	// 입력에 대한 프로세스 수행하는 함수
	void ProcessInput(const char* input)
	{
		if (!strcmp(input, "undo")) commandManager->Undo();			// undo 명령어 실행
		else if (!strcmp(input, "redo")) commandManager->Redo();	// redo 명령어 실행
		else if (!strcmp(input, "show")) commandManager->Show();	// show 명령어 실행

		// 입력 문자가 1글자인지 검사
		else if (strlen(input) == 1)
		{
			// 소문자면 대문자로 변환
			char ch = toupper(input[0]);

			// 유효하지 않은 문자 예외 처리
			if (!IsValidInput(ch))
			{
				std::cout << "잘못된 입력입니다. A, B, C, D, E만 입력하세요." << "\n\n";
				return;
			}

			// 입력 큐에 입력 프로세스를 수행할 문자 저장
			inputQueue.Push(ch);

			// 
			Command* command = new InputCommand(ch, &currentChar);

			// 해당 문자에 대한 커맨드 실행
			commandManager->ExecuteCommand(command);
		}
		else std::cout << "잘못된 입력입니다. A, B, C, D, E만 입력하세요." << "\n\n";
	}

	void Run()
	{
		while (true)
		{
			std::cout << "문자를 입력해 주세요. (A, B, C, D, E) (종료는 '0')" << "\n";
			std::cout << "명령어: 'undo', 'redo', 'show'" << "\n";
			std::cout << "현재 문자: " << currentChar << "\n";
			std::cout << "> ";

			char inputBuffer[100];
			std::cin >> inputBuffer;
			system("cls");

			// 0이 입력으로 들어오면 프로그램 종료
			if (inputBuffer[0] == '0') break;

			// 입력에 대한 프로세스 수행
			ProcessInput(inputBuffer);
		}
	}

private:
	// 현재 문자
	char currentChar;

	// 입력 큐
	Queue<char> inputQueue;

	// 입력 처리 커맨드 
	CommandManager* commandManager;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UndoRedoProgram program;
	program.Run();
}