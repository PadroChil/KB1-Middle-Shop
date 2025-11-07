#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>


// Учетные записи ------------------------------------------------------------------------------------------

size_t userSize = 2;
std::string  userStatus[3]{ "Супер администратор","Администратор","Сотрудник" };
std::string* loginArr = new std::string[userSize]{"admin","user"};
std::string* passArr = new std::string[userSize]{"admin","user"};
std::string* statusArr = new std::string[userSize]{ userStatus[0],userStatus[2] };
std::string curentStatus;

//----------------------------------------------------------------------------------------------------------


// Склад ------------------------------------------------------------------------------------------

size_t storageSize = 10;
int* idArr = new int[storageSize] {};
std::string* nameArr = new std::string[storageSize]{};
double* priceArr = new double[storageSize] {};
unsigned int* count = new unsigned int[storageSize] {};


//----------------------------------------------------------------------------------------------------------





void Start();
bool Login();

void CreateStorage();


inline void Getline(std::string& str);
inline void Err();

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	Start();

	delete[]loginArr, passArr, statusArr;

	return 0;
}


void Start()
{
	std::string choose;
	if (Login())
	{
		if (curentStatus == userStatus[0])
		{
			while (true)
			{
				std::cout << "Выберите тип склада\n1 - Готовый\n2 - Новый\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					// Готовый склад
					break;
				}
				else if (choose == "2")
				{
					// Новый склад
					break;
				}
				else
				{
					Err();
				}
			}
			

		}
		else if (curentStatus == userStatus[1])
		{
			// Готовый склад
		}
		else if (curentStatus == userStatus[2])
		{
			// Готовый склад
		}
	}
	else
	{
		system("cls");
		std::cout << "\n\n\tЗавершение работы\n";
		Sleep(2000);
		system("cls");
	}
}

bool Login()
{
	std::string login, pass;

	while (true)
	{
		std::cout << "\n\n\n\t\tAMD мебель\n\n\n";
		std::cout << "Введите логин: ";
		Getline(login);
		std::cout << "Введите пароль: ";
		Getline(pass);

		if (login == "exit" && pass == "exit")
		{
			curentStatus = "";
			return false;
		}

		if (login == loginArr[0] && pass == passArr[0])
		{
			std::cout << "Пользователь: " << loginArr[0] << "\n\nДобро пожаловать!\n\n";
			std::cout << "Ваш статус: " << statusArr[0] <<"\n\n";
			curentStatus = statusArr[0];
			return true;
		}

		for (size_t i = 1; i < userSize; i++)
		{
			if (login == loginArr[i] && pass == passArr[i])
			{
				std::cout << "Пользователь: " << loginArr[i] << "\n\nДобро пожаловать!\n\n";
				std::cout << "Ваш статус: "<< statusArr[i]<<"\n\n";
				curentStatus = statusArr[i];
				return true;
			}
		}
		Err();
	}
}

void CreateStorage()
{
	const unsigned int staticSize = 10;

	int id[staticSize]{ 1,2,3,4,5,6,7,8,9,10 }; 
	std::string name[staticSize]
	{
		"Cтол из термопасты","Дрявая Кровать","Електрический стул",
		"Кривой Комод","Кожанный Шкаф","Кукулс Стелаж","Столик туалетный",
		"Разбитая Полка","Кресло - качалка", "Прикроватная Тумба"

	};
	double price[staticSize]{ 5600.5, 15000.9, 3200.2,
		5000.1,20000.0,1500.4,2500.3,300.8,1488.1,1700.6 };
	unsigned int count[staticSize]{5,4,8,10,7,14,9,12,23,15};

}

inline void Getline(std::string& str)
{
	std::getline(std::cin, str, '\n');

}

inline void Err()
{
	std::cout << "Некорректный ввод\n\n";
	Sleep(1500);
	system("cls");
}