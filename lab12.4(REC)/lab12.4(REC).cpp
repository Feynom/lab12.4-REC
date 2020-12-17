#include <iostream>
#include <Windows.h>

using namespace std;

typedef int Info;
struct Elem
{
	Elem* link;
	Info info;
};

void Insert(Elem*& L, Info value);
void Print(Elem* L, int size, int i);
int Count(Elem* L, Elem* first);
void Remove(Elem*& L, Elem* T);
void Process(Elem*& L, Elem* first, int size, int i, int j);
int prev_elem(Elem* L, int count, int size, int i);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Elem* L = NULL;

	Info value, N;

	do
	{
		cout << "Введіть кількість елементів списку: "; cin >> N;
	} while (N < 0);

	for (int i = 0; i < N; i++)
	{
		cout << "Введіть дані: "; cin >> value;
		Insert(L, value);
	}

	cout << "Елементи черги: "; Print(L, Count(L, L), 0); cout << endl;

	Process(L, L, Count(L, L), 0, 0);
	cout << "Рузультат: "; Print(L, Count(L, L), 0);

	return 0;
}
void Insert(Elem*& L, Info value)
{
	Elem* tmp = new Elem;      //1
	tmp->info = value;         //2
	if (L != NULL)
	{
		Elem* T = L;
		while (T->link != L)
			T = T->link;       //3

		T->link = tmp;         //4
	}
	else
		L = tmp;               //5

	tmp->link = L;             //6
}
void Print(Elem* L, int size, int i)
{
	if (i < size)
	{
		cout << L->info << " ";
		return Print(L = L->link, size, i + 1);
	}
}
void Process(Elem*& L, Elem* first, int size, int i, int j)
{
	if(i < size - 1)
	{
		Insert(L, prev_elem(L, i, size, 0)); //добавлення у кінець списку зворотних елементів
		return Process(L, first, size, i + 1, j);
	}

	if(j < size - 1)
	{
		Remove(L, L);//видалення лишніх елементів
		return Process(L, first, size, i, j + 1);
	}
}
int Count(Elem* L, Elem* first)
{
	if (L == NULL)
		return 0;
	else
		if (L->link != first)
			return 1 + Count(L->link, first);
		else
			return 1;
}
int prev_elem(Elem* L, int count, int size, int i)
{
	if (i < size - count - 2)
		return prev_elem(L->link, count, size, i + 1);
	return L->info;
}
void Remove(Elem*& L, Elem* T)
{
	if (T->link != L)
		return Remove(L, T->link);  //1

	if (T != L)
	{
		Elem* tmp = L->link; //2
		delete L;            //3

		L = tmp;             //4
		T->link = L;         //5
	}
}