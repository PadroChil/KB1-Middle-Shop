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

//  ------------------------------------------------------- СКЛАД -----------------------------------------------------

size_t storageSize = 0;
size_t maxItemSize = 500;
unsigned int* idArr = nullptr;
std::string* nameArr = nullptr;
double* priceArr = nullptr;
unsigned int* countArr = nullptr;
bool isStorageCreated = false;

void CreateStorage();
void ShowStorage(int mode = 0);
void AddStorageItem();
void RemoveStorageItem();
void ChangePrice();

void ChangeStorage();

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



bool IsNumber(const std::string &str);
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
		system("cls");
		if (curentStatus == userStatus[0])
		{
			while (true)
			{
				std::cout << "Выберите тип склада\n1 - Готовый\n2 - Новый\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					CreateStorage();
					ShowSuperAdminMenu();
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
			AddStorageItem();
		}
		else if (choose == "4")
		{
			RemoveStorageItem();
		}
		else if (choose == "5")
		{
			ChangePrice();
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
			std::cout << "Выход ... ";
			Sleep(1500);
			system("cls");
			break;
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


void ShowStorage(int mode)
{
	if (mode == 0)
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
	else if (mode == 1)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t"
		 << "Кол-во\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t"
				 << countArr[i] << "\n";
		}
	
	}
	else if (mode == 2)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t"
			<< "Цена\t";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t"
				<< priceArr[i] << "\n";
		}

	}

}


void AddStorageItem()
{
	std::string chooseId, chooseCount , choose;
	unsigned int id = 0, count = 0;

	while (true)
	{
		system("cls");
		ShowStorage(1);

		std::cout << "Введите ID товара или \"exit\" для выхода: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции пополнения склада!\n";
			Sleep(1500);
			system("cls");
			break;
		}
		std::cout << "Введите кол-во товара для пополнения: ";
		Getline(chooseCount);

		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize -1 || count < 0 || count > maxItemSize)
			{
				std::cout << "Некорректный id или кол-во\nМаксимальнле кол-во - " << maxItemSize << "\n\n";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t"
					<< countArr[id] << "---> " << countArr[id] + count << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose =="1")
				{
					countArr[id] += count;
					std::cout << "Товар успешно пополнен\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена операции пополнения!\n";
					Sleep(1500);
					system("cls");
				}
				else
				{
					Err();
				}
			}
		}

	}

}

void RemoveStorageItem()
{
	std::string chooseId, chooseCount, choose;
	unsigned int id = 0, count = 0;

	while (true)
	{
		system("cls");
		ShowStorage(1);

		std::cout << "Введите ID товара или \"exit\" для выхода: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции списания  товара!\n";
			Sleep(1500);
			system("cls");
			break;
		}
		std::cout << "Введите кол-во товара для списания: ";
		Getline(chooseCount);

		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize - 1 || count < 0 || count > countArr[id])
			{
				std::cout << "Некорректный id или кол-во\nМаксимальнле кол-во - " << countArr[id] << "\n\n";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t"
					<< countArr[id] << "---> " << countArr[id] - count << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					countArr[id] -= count;
					std::cout << "Товар успешно списан\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена списания!\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}
		}

	}

}

void ChangePrice()
{
	std::string chooseId, choosePrice, choose;
	unsigned int id = 0;
	double newPrice;

	while (true)
	{
		system("cls");
		ShowStorage(2);

		std::cout << "Введите ID товара или \"exit\" для выхода: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции изменения цены!\n";
			Sleep(1500);
			system("cls");
			break;
		}
		std::cout << "Введите новую цену товара: ";
		Getline(choosePrice);

		if (IsNumber(chooseId) && IsNumber(choosePrice))
		{
			id = std::stoi(chooseId) - 1;
			newPrice = std::stod(choosePrice);

			if (id < 0 || id > storageSize - 1 || newPrice < 0 || newPrice > 200000)
			{
				std::cout << "Некорректный id или цена\nМаксимальная цена - " << 200000 << "\n\n";
				Sleep(1500);
			}
			else
			{
				std::cout<< "\n" << std::left << std::setw(25) << nameArr[id] << "\t"
					<< priceArr[id] << "---> " << newPrice << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					priceArr[id] = newPrice;
					std::cout << "Цена успешно изменина\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена изменения цены!\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}
		}

	}

}

void ChangeStorage()
{
	std::string choose;
	while (true)
	{
		system("cls");
		std::cout << "1 - Добавить новый товар\n";
		std::cout << "2 - Изменить название товара\n";
		std::cout << "3 - Удалить товар\n";
		std::cout << "0 - Выход из редактора склада\n";
		Getline(choose);
		if (choose == "1")
		{


		}
		else if (choose == "2")
		{


		}
		else if (choose == "3")
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




bool IsNumber(const std::string& str)
{
	if (str.size() <= 0 || str.size() >= 10)
	{
		std::cout << "Некоректный ввод\n";
		std::cout << "Ошибка размера числа. От 1 до 9 символов включительно\n\n";
		Sleep(1500);
		return false;
	}
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
		{
			std::cout << "Некоректный ввод\n";
			std::cout << "Введенные данные не являются числом\n\n";
			Sleep(1500);
			return false;
		}
	}
	return true;
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
