#include <iostream>
#include <Windows.h>
#include <string>
#include "App.h"
using namespace std;

public class BinApplication
{
private:
	App* head;
	int size;
	void BinPrint(App* app)
	{
		if (app != NULL)
		{
			BinPrint(app->left);
			cout << app->name << " " << app->prouzvod << " " << app->razmer << " " << app->zena << endl;
			BinPrint(app->right);
		}
	}
	void BinPrintMas(App* h, int& apsize, App* mas)
	{
		if (h != NULL)
		{
			BinPrintMas(h->left, apsize, mas);
			strcpy_s(mas[apsize].name, h->name);
			strcpy_s(mas[apsize].prouzvod, h->prouzvod);
			mas[apsize].razmer = h->razmer;
			mas[apsize].zena = h->zena;
			apsize++;
			BinPrintMas(h->right, apsize, mas);
		}
	}
	void ClearBin(App* h)
	{
		if (h == NULL)
		{
			return;
		}
		ClearBin(h->left);
		ClearBin(h->right);
		this->RemoveApp(h->razmer, h->name);
	}
	void BalanceBin(BinApplication* bap, App* mas, int size)
	{
		if (size == 0)
		{
			return;
		}
		bap->AddApp(mas[size / 2]);
		BalanceBin(bap, mas, size / 2);
		if (size > 2)
		{
			if (size % 2 == 0)
				BalanceBin(bap, (mas + size / 2 + 1), size / 2 - 1);
			else
				BalanceBin(bap, (mas + size / 2 + 1), size / 2);
		}
	}
public:
	BinApplication()
	{
		head = NULL;
		size = 0;
	}
	~BinApplication()
	{
		ClearBin(head);
		head = NULL;
		size = 0;
	}
	void AddApp(App app)
	{
		App *apl = new App();
		strcpy_s(apl->name, app.name);
		strcpy_s(apl->prouzvod, app.prouzvod);
		apl->razmer = app.razmer;
		apl->zena = app.zena;
		if (!head)
		{
			head = apl;
			size++;
			return;
		}
		else
		{
			App* cur = head;
			App* help = NULL;
			bool right = true;
			while (cur)
			{
				if (!cur->Sort(apl))
				{
					help = cur;
					cur = cur->right;
					right = true;
				}
				else
				{
					help = cur;
					cur = cur->left;
					right = false;
				}
			}
			cur = apl;
			size++;
			if (right)
				help->right = cur;
			else
				help->left = cur;
		}
	}
	void BinPrint()
	{
		BinPrint(head);
	}
	void RemoveApp(double raz, char* name)
	{
		if (!head)
		{
			throw 3;
		}
		App* cur = head;
		App* help = NULL;
		bool right = true;
		while (cur)
		{
			if ((cur->razmer == raz) && (strcmp(name, cur->name) == 0))
			{
				if ((!cur->left) && (!cur->right))
				{
					if (cur == head)
					{
						cur = NULL;
						size--;
						return;
					}
					else
					{
						cur = NULL;
						if (right)
							help->right = NULL;
						else
							help->left = NULL;
						size--;
						return;
					}
				}
				else if (!cur->left)
				{
					if (cur == head)
					{
						head = cur->right;
						cur = NULL;
						size--;
						return;
					}
					else
					{
						if (right)
							help->right = cur->right;
						else
							help->left = cur->right;
						cur = NULL;
						size--;
						return;
					}
				}
				else if (!cur->right)
				{
					if (cur == head)
					{
						head = cur->left;
						cur = NULL;
						size--;
						return;
					}
					else
					{
						if (right)
							help->right = cur->left;
						else
							help->left = cur->left;
						cur = NULL;
						size--;
						return;
					}
				}
				else
				{
					App *tmp = cur->right;
					if (tmp->left)
					{
						App *neednode = tmp;
						while (tmp->left)
						{
							neednode = tmp;
							tmp = tmp->left;
						}
						tmp->left = cur->left;
						if (tmp->right)
							neednode->left = tmp->right;
						if (cur == head)
						{
							head = tmp;
							cur = NULL;
							size--;
							return;
						}
						cur = tmp;
						size--;
						return;
					}
					else
						cur = tmp;
					size--;
					return;
				}
			}
			else
			{
				if (cur->razmer > raz)
				{
					help = cur;
					cur = cur->left;
					right = false;
				}
				else if (cur->razmer < raz)
				{
					help = cur;
					cur = cur->right;
					right = true;
				}
				else
				{
					if (strcmp(cur->name, name) > 0)
					{
						help = cur;
						cur = cur->left;
						right = false;
					}
					else
					{
						help = cur;
						cur = cur->right;
						right = true;
					}
				}
			}
		}
		throw 2;
	}
	bool FindInBinApp(double raz, char* name)
	{
		if (!head)
		{
			throw 3;
		}
		App* cur = head;
		while (cur)
		{
			if ((cur->razmer == raz) || (strcmp(cur->name, name) == 0))
			{
				return true;
			}
			else
			{
				if (cur->razmer > raz)
					cur = cur->left;
				else if (cur->razmer < raz)
					cur = cur->right;
				else
				{
					if (strcmp(cur->name, name) > raz)
						cur = cur->left;
					else
						cur = cur->right;
				}
			}
		}
		return false;
	}
	App* BinPrintMas(int &massize)
	{
		massize = 0;
		App *app = new App[size];
		BinPrintMas(head, massize, app);
		return app;
	}
	void BalanceBin()
	{
		int massize;
		App* mas = this->BinPrintMas(massize);
		this->ClearBin(head);
		head = NULL;
		BalanceBin(this, mas, massize);
		size = massize;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n;
	cout << "Введите количество программ: ";
	cin >> n;
	cin.ignore();
	BinApplication* bap = new BinApplication();
	int l = 0;
	try
	{	
	for (int i = 0; i < n; i++)
	{
		App Applications;
		_itoa_s(rand() % 10000, Applications.name, 36);
		_itoa_s(rand() % 10000, Applications.prouzvod, 36);
		Applications.razmer = rand() % 1000;
		Applications.zena = rand() % 1000;
		bap->AddApp(Applications);
	}
	bap->BinPrint();
	cout << endl;
	bap->BalanceBin();
	bap->BinPrint();
	//	*double size = 0;
	//	char nameapp[100];
	//	for (int i = 0; i < 5; i++)
	//	{
	//		cout << "Введите размер на диске: ";
	//		cin >> size;
	//		cin.ignore();
	//		cout << "Введите наименование программы: ";
	//		cin.getline(nameapp, 99);
	//		bap->RemoveApp(size, nameapp);
	//		bap->BinPrint();
	//	}
	//	for (int i = 0; i < 3; i++)
	//	{
	//		cout << "Введите размер на диске: ";
	//		cin >> size;
	//		cin.ignore();
	//		cout << "Введите наименование программы: ";
	//		cin.getline(nameapp, 99);
	//		if (bap->FindInBinApp(size, nameapp))
	//			cout << "Такой листик есть)" << endl;
	//		else
	//	//		cout << "Такого листика нет" << endl;
	//	//}*/
	//	//int apsize = 0;
	//	//App *app = bap->BinPrintMas(apsize);
	//	//for (int i = 0; i < apsize; i++)
	//	//{
	//	//	cout << app[i].name << " " << app[i].prouzvod << " " << app[i].razmer << " " << app[i].zena << endl;
	//	//}
	}
	catch (...)
	{
		cout << "Exeption!" << endl;
	}
	return 0;
}