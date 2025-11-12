#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>


//  ---------------------------------------- УЧЕТНЫЕ ЗАПИСИ --------------------------------------------------------

size_t userSize = 2;
std::string  userStatus[3]{ "Супер администратор","Администратор","Сотрудник" };
std::string* loginArr = new std::string[userSize]{"admin","user"};
std::string* passArr = new std::string[userSize]{"admin","user"};
std::string* statusArr = new std::string[userSize]{ userStatus[0],userStatus[2] };
std::string curentStatus;

//  ----------------------------------------------------------------------------------------------------------------
// 
//  ------------------------------------------------------- СКЛАД -----------------------------------------------------

size_t storageSize = 0;
unsigned int* idArr = nullptr;
std::string* nameArr = nullptr;
double* priceArr = nullptr;
unsigned int* countArr = nullptr;
bool isStorageCreated = false;

void CreateStorage();
void ShowStorage();

template<typename ArrType > 
void FillArr(ArrType* dynamicArr, ArrType* staticArr, size_t arraySize)
{
	for (size_t i = 0; i < arraySize; i++)
	{
		dynamicArr[i] = staticArr[i];
	}

}

//----------------------------------------------------------------------------------------------------------

// --------------------------------------- СЛУЖЕБНЫЕ ------------------------------------------------------------


void Start();
bool Login();
void ShowSuperAdminMenu();

void CreateStorage();


inline void Getline(std::string& str);
inline void Err();
//----------------------------------------------------------------------------------------------------------

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	Start();

	delete[]loginArr, passArr, statusArr;
	if (isStorageCreated)
	{
		delete[]idArr, nameArr, countArr, priceArr;
	}


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
					CreateStorage();
					ShowStorage();
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

		for (size_t i = 0; i < userSize; i++)
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

void ShowSuperAdminMenu()
{
	std::string choose;
	while (true)
	{
		std::cout << "1 - Начать продажу\n";
		std::cout << "2 - Показать склад\n";
		std::cout << "3 - Пополнить склад\n";
		std::cout << "4 - Списать товар\n";
		std::cout << "5 - Изменить цену\n";
		std::cout << "6 - Редактировать склад\n";
		std::cout << "7 - Редактировать персонал\n";
		std::cout << "8 - Отчет о прибыли\n";
		std::cout << "0 - Закрыть смену\n";
		std::cout << "Ввод: ";
		Getline(choose);
		if (choose == "1")
		{

		}
		else if (choose == "2")
		{
			ShowStorage();
		}
		else if (choose == "3")
		{

		}
		else if (choose == "4")
		{

		}
		else if (choose == "5")
		{

		}
		else if (choose == "6")
		{

		}
		else if (choose == "7")
		{

		}
		else if (choose == "8")
		{

		}
		else if (choose == "0")
		{

		}
		else
		{
			Err();
		}


	}


}

void CreateStorage()
{
	const unsigned int staticSize = 10;

	unsigned int id[staticSize]{ 1,2,3,4,5,6,7,8,9,10 }; 
	std::string name[staticSize]
	{
		"Cтол из термопасты","Дрявая Кровать","Электрический стул",
		"Кривой Комод","Кожанный Шкаф","Кукулс Стелаж","Столик туалетный",
		"Разбитая Полка","Кресло - качалка", "Прикроватная Тумба"

	};
	double price[staticSize]{ 5600.5, 15000.9, 3200.2,
		5000.1,20000.0,1500.4,2500.3,300.8,1488.1,1700.6 };
	unsigned int count[staticSize]{5,4,8,10,7,14,9,12,23,15};
	
	storageSize = staticSize;
	idArr = new unsigned int[storageSize];
	nameArr = new std::string[storageSize];
	countArr = new unsigned int[storageSize];
	priceArr = new double[storageSize];
	isStorageCreated = true;

	FillArr(idArr, id, storageSize);
	FillArr(nameArr, name, storageSize);
	FillArr(countArr, count, storageSize);
	FillArr(priceArr, price, storageSize);

}

void ShowStorage()
{
	system("cls");
	std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t"
		<< "Цена\t" << "Кол-во\n";

	for (size_t i = 0; i < storageSize; i++)
	{
		std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t"
			<< priceArr[i] << "\t" << countArr[i] << "\n";
	}
	system("pause");
	system("cls");
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