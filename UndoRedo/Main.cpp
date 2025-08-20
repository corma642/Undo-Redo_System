#include <iostream>
#include "Vector.h"
#include "Stack.h"
#include "Queue.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

struct UndoRedo
{
public:
	UndoRedo()
		: InputQueue(Queue<char>()), UndoStack(Stack<char>()), RedoStack(Stack<char>())
	{
	}

	// 문자 입력받기
	void Input(const char* inputBuffer, char& currentChar)
	{
		if (!strcmp(inputBuffer, "undo")) Undo(currentChar);		// undo 수행
		else if (!strcmp(inputBuffer, "redo")) Redo(currentChar);	// redo 수행
		else if (!strcmp(inputBuffer, "show")) Show();				// show 수행

		// 문자 입력받기
		else
		{
			// 알파벳 문자가 아니면 반환
			if (!((inputBuffer[0] >= 65 && inputBuffer[0] <= 90) ||
				(inputBuffer[0] >= 97 && inputBuffer[0] <= 122)))
			{
				std::cout << "잘 못 입력하셨습니다." << "\n\n";
				return;
			}

			// 입력 큐에 문자 추가
			InputQueue.Push(inputBuffer[0]);

			// undo 스택에 undo할 문자 추가
			UndoStack.Push(inputBuffer[0]);

			// 현재 문자 초기화
			currentChar = UndoStack.Top();
		}
	}

	void Undo(char& value)
	{
		if (UndoStack.Empty())
		{
			return;
		}

		// 현재 입력 키 제거
		UndoStack.Pop();

		// UndoStack이 비어있는 경우
		if (UndoStack.Empty())
		{
			RedoStack.Push(value);
			value = ' ';
			return;
		}

		char saveChar = value;

		value = UndoStack.Top();
		RedoStack.Push(saveChar);
	}

	void Redo(char& value)
	{
		if (RedoStack.Empty())
		{
			return;
		}

		char saveChar = RedoStack.Top();
		RedoStack.Pop();

		UndoStack.Push(saveChar);
		value = saveChar;
	}

	void Show() const
	{
		int undoStackSize = UndoStack.Size();
		std::cout << "Undo List: ";
		for (int i = 0; i < undoStackSize - 1; ++i)
		{
			std::cout << UndoStack.GetData()[i] << (i < undoStackSize - 1 ? ", " : "");
		}

		std::cout << " ";

		int redoStackSize = RedoStack.Size();
		std::cout << "Redo List: ";
		for (int i = 0; i < redoStackSize; ++i)
		{
			std::cout << RedoStack.GetData()[i] << (i < redoStackSize - 1 ? ", " : "");
		}

		std::cout << "\n\n";
	}

private:
	// 입력 저장
	Queue<char> InputQueue;

	// Undo/Redo 스택
	Stack<char> UndoStack;
	Stack<char> RedoStack;
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UndoRedo undoRedo;
	char currentChar = ' ';

	while (true)
	{
		char inputBuffer[100];

		std::cout << "문자를 입력해 주세요. (a ~ Z) (종료는 '0')" << "\n";
		std::cout << "명령어: 'undo', 'redo', 'show'" << "\n";

		std::cout << "현재 문자: " << currentChar << "\n";
		std::cout << "> ";

		std::cin >> inputBuffer;
		system("cls");

		// 0 입력 시, 프로그램(루프) 종료
		if (inputBuffer[0] == '0') break;

		undoRedo.Input(inputBuffer, currentChar);
	}
}