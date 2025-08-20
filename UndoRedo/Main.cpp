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

	// ���� �Է¹ޱ�
	void Input(const char* inputBuffer, char& currentChar)
	{
		if (!strcmp(inputBuffer, "undo")) Undo(currentChar);		// undo ����
		else if (!strcmp(inputBuffer, "redo")) Redo(currentChar);	// redo ����
		else if (!strcmp(inputBuffer, "show")) Show();				// show ����

		// ���� �Է¹ޱ�
		else
		{
			// ���ĺ� ���ڰ� �ƴϸ� ��ȯ
			if (!((inputBuffer[0] >= 65 && inputBuffer[0] <= 90) ||
				(inputBuffer[0] >= 97 && inputBuffer[0] <= 122)))
			{
				std::cout << "�� �� �Է��ϼ̽��ϴ�." << "\n\n";
				return;
			}

			// �Է� ť�� ���� �߰�
			InputQueue.Push(inputBuffer[0]);

			// undo ���ÿ� undo�� ���� �߰�
			UndoStack.Push(inputBuffer[0]);

			// ���� ���� �ʱ�ȭ
			currentChar = UndoStack.Top();
		}
	}

	void Undo(char& value)
	{
		if (UndoStack.Empty())
		{
			return;
		}

		// ���� �Է� Ű ����
		UndoStack.Pop();

		// UndoStack�� ����ִ� ���
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
	// �Է� ����
	Queue<char> InputQueue;

	// Undo/Redo ����
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

		std::cout << "���ڸ� �Է��� �ּ���. (a ~ Z) (����� '0')" << "\n";
		std::cout << "��ɾ�: 'undo', 'redo', 'show'" << "\n";

		std::cout << "���� ����: " << currentChar << "\n";
		std::cout << "> ";

		std::cin >> inputBuffer;
		system("cls");

		// 0 �Է� ��, ���α׷�(����) ����
		if (inputBuffer[0] == '0') break;

		undoRedo.Input(inputBuffer, currentChar);
	}
}