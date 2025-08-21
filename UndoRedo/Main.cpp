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

// A 커맨드
class CommandA : public ICommand
{
public:
	CommandA(char ch, char* curChar)
		: inputChar(ch), curChar(curChar), prevChar(*curChar)
	{
	}

	// 현재 문자를 입력으로 받은 문자로 초기화
	void Execute() override
	{
		*curChar = inputChar;
	}

	// 현재 문자를 이전 입력 문자로 초기화
	void Undo() override
	{
		*curChar = prevChar;
	}

	// 입력으로 받은 문자 반환
	char GetChar() const override
	{
		return inputChar;
	}

private:
	char inputChar;		// 입력으로 받은 문자
	char* curChar;		// 현재 문자
	char prevChar;		// 이전 입력 문자
};

// B 커맨드
class CommandB : public ICommand
{
public:
	CommandB(char ch, char* curChar)
		: inputChar(ch), curChar(curChar), prevChar(*curChar)
	{
	}

	// 현재 문자를 입력으로 받은 문자로 초기화
	void Execute() override
	{
		*curChar = inputChar;
	}

	// 현재 문자를 이전 입력 문자로 초기화
	void Undo() override
	{
		*curChar = prevChar;
	}

	// 입력으로 받은 문자 반환
	char GetChar() const override
	{
		return inputChar;
	}

private:
	char inputChar;		// 입력으로 받은 문자
	char* curChar;		// 현재 문자
	char prevChar;		// 이전 입력 문자
};

// C 커맨드
class CommandC : public ICommand
{
public:
	CommandC(char ch, char* curChar)
		: inputChar(ch), curChar(curChar), prevChar(*curChar)
	{
	}

	// 현재 문자를 입력으로 받은 문자로 초기화
	void Execute() override
	{
		*curChar = inputChar;
	}

	// 현재 문자를 이전 입력 문자로 초기화
	void Undo() override
	{
		*curChar = prevChar;
	}

	// 입력으로 받은 문자 반환
	char GetChar() const override
	{
		return inputChar;
	}

private:
	char inputChar;		// 입력으로 받은 문자
	char* curChar;		// 현재 문자
	char prevChar;		// 이전 입력 문자
};

// D 커맨드
class CommandD : public ICommand
{
public:
	CommandD(char ch, char* curChar)
		: inputChar(ch), curChar(curChar), prevChar(*curChar)
	{
	}

	// 현재 문자를 입력으로 받은 문자로 초기화
	void Execute() override
	{
		*curChar = inputChar;
	}

	// 현재 문자를 이전 입력 문자로 초기화
	void Undo() override
	{
		*curChar = prevChar;
	}

	// 입력으로 받은 문자 반환
	char GetChar() const override
	{
		return inputChar;
	}

private:
	char inputChar;		// 입력으로 받은 문자
	char* curChar;		// 현재 문자
	char prevChar;		// 이전 입력 문자
};

// E 커맨드
class CommandE : public ICommand
{
public:
	CommandE(char ch, char* curChar)
		: inputChar(ch), curChar(curChar), prevChar(*curChar)
	{
	}

	// 현재 문자를 입력으로 받은 문자로 초기화
	void Execute() override
	{
		*curChar = inputChar;
	}

	// 현재 문자를 이전 입력 문자로 초기화
	void Undo() override
	{
		*curChar = prevChar;
	}

	// 입력으로 받은 문자 반환
	char GetChar() const override
	{
		return inputChar;
	}

private:
	char inputChar;		// 입력으로 받은 문자
	char* curChar;		// 현재 문자
	char prevChar;		// 이전 입력 문자
};

// 커맨드 명령어 실행 클래스
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

	void ExecuteCommand(ICommand* command)
	{
		// redo 스택 초기화 (새로운 입력 커맨드가 들어왔으므로)
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
	Stack<ICommand*> undoStack;

	// Rndo 스택
	Stack<ICommand*> redoStack;

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

			// 입력 처리를 할 커맨드
			ICommand* command = nullptr;

			switch (ch)
			{
			case 'A': command = new CommandA(ch, &currentChar); break;
			case 'B': command = new CommandB(ch, &currentChar); break;
			case 'C': command = new CommandC(ch, &currentChar); break;
			case 'D': command = new CommandD(ch, &currentChar); break;
			case 'E': command = new CommandE(ch, &currentChar); break;

			default: std::cout << "잘못된 입력입니다. A, B, C, D, E만 입력하세요." << "\n\n";
			}

			// 입력 커맨드 기록 저장
			inputCommandQueue.Push(command);

			// 해당 문자에 대한 커맨드 실행
			commandManager->ExecuteCommand(command);
		}
		else std::cout << "잘못된 입력입니다. A, B, C, D, E만 입력하세요." << "\n\n";
	}

	// 현재 문자 반환
	char GetCurrentChar() const { return currentChar; }

private:
	// 현재 문자
	char currentChar;

	// 입력 커맨드 기록을 저장하는 큐
	Queue<ICommand*> inputCommandQueue;

	// 입력 처리 커맨드 
	CommandManager* commandManager;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Undo/Redo 프로그램 객체 동적할당
	UndoRedoProgram* program = new UndoRedoProgram();

	while (true)
	{
		std::cout << "문자를 입력해 주세요. (A, B, C, D, E) (종료는 '0')" << "\n";
		std::cout << "명령어: 'undo', 'redo', 'show'" << "\n";
		std::cout << "현재 문자: " << program->GetCurrentChar() << "\n";
		std::cout << "> ";

		char inputBuffer[100];
		std::cin >> inputBuffer;
		system("cls");

		// 0이 입력으로 들어오면 프로그램 종료
		if (inputBuffer[0] == '0') break;

		// 입력에 대한 프로세스 수행
		program->ProcessInput(inputBuffer);
	}

	// 메모리 해제
	delete program;
}