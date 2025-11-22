#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>
#include <unordered_set>


//  ---------------------------------------- УЧЕТНЫЕ ЗАПИСИ ----------------------------------------------------- \\

size_t userSize = 2;
std::string  userStatus[3]{ "Супер администратор","Администратор","Сотрудник" };
std::string* loginArr = new std::string[userSize]{ "admin","user" };
std::string* passArr = new std::string[userSize]{ "admin","user" };
std::string* statusArr = new std::string[userSize]{ userStatus[0],userStatus[2] };
std::string curentStatus;


void ChangeAccounts();
void ShowUsers(int mode = 0);
void AddNewUser();
void ChangePass();
void DeleteUser();

//  ---------------------------------------------------------------------------------------------------------------- \\


//  ------------------------------------------------------- СКЛАД ---------------------------------------------------- \\

size_t storageSize = 0;
size_t maxItemSize = 250;
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
void AddNewItem();
void ChangeName();
void DeleteItem();

template<typename ArrType >
void FillArr(ArrType* dynamicArr, ArrType* staticArr, size_t arraySize)
{
	for (size_t i = 0; i < arraySize; i++)
	{
		dynamicArr[i] = staticArr[i];
	}

}

// -------------------------------------------------------------------------------------------------------------- \\


// --------------------------------------------------- СЛУЖЕБНЫЕ ------------------------------------------------- \\

std::unordered_set<char> specialSymbols;
std::unordered_set<char> passSymbols;
bool isPassSetCreated = false;
bool isSetCreated = false;

void Start();
bool Login();
void ShowSuperAdminMenu();
bool CheckLogin(const std::string& str);
void SetSpecialSymbols();
void SetPassSymbols();
bool CheckPass(const std::string& str);


bool IsNumber(const std::string& str);
inline void Getline(std::string& str);
inline void Err();

// ---------------------------------------------------------------------------------------------------------------- \\


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
					if (isStorageCreated == false)
					{
						CreateStorage();
					}
					system("cls");
					ShowSuperAdminMenu();
					break;
				}
				else if (choose == "2")
				{
					if (isStorageCreated == false)
					{

					}
					system("cls");
					ShowSuperAdminMenu();
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
			if (isStorageCreated == false)
			{
				CreateStorage();
			}
		}
		else if (curentStatus == userStatus[2])
		{
			// Готовый склад
			if (isStorageCreated == false)
			{
				CreateStorage();
			}
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
				std::cout << "Ваш статус: " << statusArr[i] << "\n\n";
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
		if (choose == "1" && storageSize > 0)
		{

		}
		else if (choose == "2" && storageSize > 0)
		{
			ShowStorage();
		}
		else if (choose == "3" && storageSize > 0)
		{
			AddStorageItem();
		}
		else if (choose == "4" && storageSize > 0)
		{
			RemoveStorageItem();
		}
		else if (choose == "5" && storageSize > 0)
		{
			ChangePrice();
		}
		else if (choose == "6")
		{
			ChangeStorage();
		}
		else if (choose == "7")
		{
			ChangeAccounts();
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


bool CheckLogin(const std::string& str)
{
	if (str.size() < 5 || str.size() >= 20)
	{
		std::cout << "Недопустимая длины логина.От 5 до 20\n";
		Sleep(1500);
		return false;
	}

	for (char sym : str)
	{
		if (!specialSymbols.count(sym))
		{
			std::cout << "Некорректные символы в логине!\n\n";
			Sleep(1500);
			return false;
		}
	}

	for (size_t i = 0; i < userSize; i++)
	{
		if (str == loginArr[i])
		{
			std::cout << "Имя уже занято\n\n";
			Sleep(1500);
			return false;
		}
	}
	return true;
}


void SetSpecialSymbols()
{
	for (char i = '0'; i <= '9'; i++)
	{
		specialSymbols.insert(i);
	}
	for (char i = 'A'; i <= 'Z'; i++)
	{
		specialSymbols.insert(i);
	}
	for (char i = 'a'; i <= 'z'; i++)
	{
		specialSymbols.insert(i);
	}
	isSetCreated = true;
}


void SetPassSymbols()
{
	for (char i = '!'; i <= '&'; i++)
	{
		passSymbols.insert(i);
	}
	for (char i = '('; i <= '+'; i++)
	{
		passSymbols.insert(i);
	}
	for (char i = '.'; i <= '~'; i++)
	{
		passSymbols.insert(i);
	}
	isPassSetCreated = true;
}


bool CheckPass(const std::string& str)
{
	if (str.size() < 8 || str.size() > 20)
	{
		std::cout << "Ошибка длины пароля\n";
		Sleep(1500);
		return false;
	}
	int numCount = 0, symCount = 0;

	std::unordered_set<char> specialPassSym{ '!', '@', '#', '$', '%', '^', '&', '*',
		'(', ')', '-', '_', '=', '+', '/', '?', '|', '\\', '\"', '\'', ',', '.',
		'<', '>', '~', ':', ';', '{', '}', '[', ']' };
	for (char sym : str)
	{
		if (!passSymbols.count(sym))
		{
			std::cout << "Некоректный пароль\n";
			Sleep(1500);
			return false;
		}

		if (std::isdigit(sym))
		{
			numCount++;
		}

		if (specialPassSym.count(sym))
		{
			symCount++;
		}
	}

	if (numCount > 3 && symCount > 3)
	{
		return true;
	}
	else
	{
		std::cout << "Минимум 3 символа  и 3 цифры\n";
		return false;
	}
}


void ChangeAccounts()
{
	std::string choose;
	if (isSetCreated == false)
	{
		SetSpecialSymbols();
	}
	if (isPassSetCreated == false)
	{
		SetPassSymbols();
	}

	while (true)
	{
		system("cls");
		std::cout << "1 - Добавить нового пользователя\n";
		std::cout << "2 - Показать пользователя\n";
		std::cout << "3 - Изменить пароль пользователя\n";
		std::cout << "4 - Удалить пользователя\n";
		std::cout << "0 - Выход из редактора аккаунтов\n";
		std::cout << "Ввод: ";
		Getline(choose);
		if (choose == "1")
		{
			AddNewUser();
		}
		else if (choose == "2" && userSize > 1)
		{
			ShowUsers();
		}
		else if (choose == "3" && userSize > 1)
		{
			ChangePass();
		}
		else if (choose == "4" && userSize > 1)
		{
			DeleteUser();
		}
		else if (choose == "0")
		{
			if (userSize < 1)
			{
				std::cout << "Нет доступных пользователей\n";
			}
			system("cls");
			break;
		}
		else
		{
			Err();
		}
	}


}


void ShowUsers(int mode)
{
	if (mode == 0)
	{
		system("cls");
		std::cout << "№\t" << std::left << std::setw(12) << "Логин\t\t" << "Пароль\t\t\t" << "Роль\n";
		for (size_t i = 1; i < userSize; i++)
		{
			std::cout << i << "\t" << std::left << std::setw(8) << loginArr[i] << "\t\t" << passArr[i]
				<< "\t\t\t" << statusArr[i] << "\n";
		}
	}
	else if (mode == 1)
	{
		system("cls");
		std::cout << "№\t" << std::left << std::setw(12) << "Логин\t\t" << "Пароль\t\t\t" << "Роль\n";
		for (size_t i = 0; i < userSize; i++)
		{
			std::cout << i << "\t" << std::left << std::setw(8) << loginArr[i] << "\t\t" << passArr[i]
				<< "\t\t\t" << statusArr[i] << "\n";
		}
		Sleep(2000);
	}
}


void AddNewUser()
{
	std::string newLogin, newPass, newRole, choose;
	bool exit = true;
	while (true)
	{
		while (true)
		{
			system("cls");
			std::cout << "Введите логин нового пользователя или \"exit\" для выхода: ";
			Getline(newLogin);
			if (newLogin == "exit")
			{
				std::cout << "Отмена добавления нового пользователя!\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (CheckLogin(newLogin))
			{
				break;
			}
			else
			{
				std::cout << "Допустимые символы: a-z, A-Z, 0-9\n\n";
				Sleep(1500);
			}
		}

		while (exit)
		{
			system("cls"); std::cout << "Введите пароль нового пользователя или \"exit\" для выхода: ";
			Getline(newPass);
			if (newPass == "exit")
			{
				std::cout << "Отмена добавления нового пользователя!\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (CheckPass(newPass))
			{
				break;
			}
			else
			{
				std::cout << "Допустимые символы: a-z, A-Z, 0-9 + символы\n\n";
				Sleep(1500);
			}
		}

		while (exit)
		{
			system("cls"); std::cout << "Введите роль нового пользователя или \"exit\" для выхода\n";
			std::cout << "1 - Администратор\n2 - Сотрудник\nВвод: ";
			Getline(choose);
			if (choose == "exit")
			{
				std::cout << "Отмена добавления нового пользователя!\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (choose == "1")
			{
				newRole = userStatus[1];
				break;
			}
			else if (choose == "2")
			{
				newRole = userStatus[2];
				break;
			}
			else
			{
				Err();
			}
		}

		while (exit)
		{

			std::cout << "Пользователь: " << newLogin << "\n";
			std::cout << "Пароль: " << newPass << "\n";
			std::cout << "Роль: " << newRole << "\n";

			std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
			Getline(choose);
			if (choose == "1")
			{
				userSize++;
				std::string* loginArrTemp = new std::string[userSize];
				std::string* passArrTemp = new std::string[userSize];
				std::string* statusArrTemp = new std::string[userSize];

				FillArr(loginArrTemp, loginArr, userSize - 1);
				FillArr(passArrTemp, passArr, userSize - 1);
				FillArr(statusArrTemp, statusArr, userSize - 1);

				loginArrTemp[userSize - 1] = newLogin;
				passArrTemp[userSize - 1] = newPass;
				statusArrTemp[userSize - 1] = newRole;

				std::swap(loginArrTemp, loginArr);
				std::swap(passArrTemp, passArr);
				std::swap(statusArrTemp, statusArr);

				delete[] loginArrTemp, passArrTemp, statusArrTemp;
				std::cout << "Идет подготовка...\n";
				Sleep(2000);
				std::cout << "Пользователь успешно добавлен!\n\n";
				exit = false;
				Sleep(1500);
				break;
			}
			else if (choose == "2")
			{
				std::cout << "Отмена\n";
				Sleep(1500);
				break;
			}
			else
			{
				Err();
			}

		}
		if (exit == false)
		{
			break;
		}
	}
}


void ChangePass()
{
	std::string newPass1, newPass2, choose;
	int userNumber = 0;
	int isAdmin = 0;

	while (true)
	{
		if (curentStatus == userStatus[0])
		{
			ShowUsers(1);
			isAdmin = 0;
		}
		else
		{
			ShowUsers();
			isAdmin = 1;
		}
		ShowUsers();
		std::cout << "Выберите номер пользователя или \"exit\" для выхода: ";
		Getline(choose);
		if (choose == "exit")
		{
			std::cout << "Отмена изменения пароля!\n";
			Sleep(1500);
			break;
		}

		else if (IsNumber(choose))
		{
			userNumber = std::stoi(choose);
			if (userNumber < isAdmin || userNumber > userSize - 1)
			{
				std::cout << "Пользователя с таким номером не существует!\n";
				Sleep(1500);
			}
			for (size_t i = isAdmin; i < userSize; i++)
			{
				if (i == userNumber)
				{
					system("cls");
					std::cout << "Введите  новый пароль для пользователя " << loginArr[i] << ": ";
					Getline(newPass1);
					std::cout << "Введите  новый пароль для пользователя " << loginArr[i] << ": ";
					Getline(newPass2);

					if (CheckPass(newPass1) && CheckPass(newPass2) && newPass1 == newPass2)
					{
						passArr[i] = newPass1;
						std::cout << "Успешно\n";
						Sleep(1500);
						break;
					}
					else
					{
						std::cout << "Повторите попытку\n";
						Sleep(1500);
						i--;

					}
				}

			}
		}

		else
		{
			Err();
		}

	}
}


void DeleteUser()
{
	std::string chooseNumber, choose, checkPass;
	int userNumber = 0;
	int isAdmin = 0;

	while (true)
	{
		if (curentStatus == userStatus[0])
		{
			if (userSize < 2)
			{
				std::cout << "Нет доступных пользователей для удаления\n";
				Sleep(1500);
				return;
			}
			ShowUsers();
			isAdmin = 1;
		}
		else
		{
			ShowUsers();
			isAdmin = 1;
		}
		ShowUsers();
		std::cout << "Выберите номер пользователя для удаления или \"exit\" для выхода: ";
		Getline(choose);
		if (choose == "exit")
		{
			std::cout << "Отмена удаления пользователя!\n";
			Sleep(1500);
			break;
		}

		else if (IsNumber(choose))
		{
			userNumber = std::stoi(choose);
			if (userNumber < isAdmin || userNumber > userSize - 1)
			{
				std::cout << "Пользователя с таким номером не существует!\n";
				Sleep(1500);
			}
			for (size_t i = isAdmin; i < userSize; i++)
			{
				if (i == userNumber)
				{
					std::cout << "Удаление пользователя: " << loginArr[i] << "\n\n";
					std::cout << "Для подтверждения введите пароль супер администратора или \"exit\" для выхода: ";
					Getline(checkPass);
					if (checkPass == "exit")
					{
						std::cout << "Отмена удаления пользователя: " << loginArr[i] << "\n\n";
						Sleep(1500);
						break;
					}
					else if (checkPass == passArr[0])
					{
						userSize--;
						std::string* loginArrTemp = new std::string[userSize];
						std::string* passArrTemp = new std::string[userSize];
						std::string* statusArrTemp = new std::string[userSize];

						for (size_t i = 0, c = 0; i < userSize; i++, c++)
						{
							if (userNumber == c)
							{
								c++;
							}
							loginArrTemp[i] = loginArr[c];
							passArrTemp[i] = passArr[c];
							statusArrTemp[i] = statusArr[c];
						}

						std::swap(loginArrTemp, loginArr);
						std::swap(passArrTemp, passArr);
						std::swap(statusArrTemp, statusArr);

						delete[] loginArrTemp, passArrTemp, statusArrTemp;
						std::cout << "Идет подготовка...\n";
						Sleep(2000);
						std::cout << "Пользователь успешно удален!\n\n";
						Sleep(1500);
						break;
					}
					else
					{
						std::cout << "Некорректный пароль\n";
						Sleep(1500);
						i--;
					}
				}

			}
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
	unsigned int count[staticSize]{ 5,4,8,10,7,14,9,12,23,15 };

	if (isStorageCreated)
	{
		delete[]idArr, nameArr, countArr, priceArr;
	}

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
	else if (mode == 3)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t" << "\n";
		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\n";
		}

	}

}


void AddStorageItem()
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

			if (id < 0 || id > storageSize - 1 || count < 0 || count > maxItemSize)
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
				if (choose == "1")
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
				std::cout << "\n" << std::left << std::setw(25) << nameArr[id] << "\t"
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
		std::cout << "Ввод: ";
		Getline(choose);
		if (choose == "1")
		{
			AddNewItem();

		}
		else if (choose == "2" && storageSize > 0)
		{
			ChangeName();

		}
		else if (choose == "3" && storageSize > 0)
		{
			DeleteItem();

		}
		else if (choose == "0")
		{
			system("cls");
			break;

		}
		else
		{
			Err();
		}
	}

}


void AddNewItem()
{
	std::string newName, newPrice, newCount, choose;
	double price = 0.0, count = 0.0;
	bool exit = true;

	while (true)
	{
		while (true)
		{
			system("cls");

			std::cout << "\tДобавление нового товара!\n\nВведите \"exit\" для прекрацения операции\n\n";

			std::cout << "Введите название нового товара: ";
			Getline(newName);

			if (newName == "exit")
			{
				std::cout << "Операция добавления товара прервана!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}

			if (newName.size() <= 0 || newName.size() >= 36)
			{
				std::cout << "Ошибка! Максимальная длина названия 36 символов\n";
				Sleep(1500);
				system("cls");

			}
			else
			{
				break;
			}


		}

		while (exit)
		{
			system("cls");
			std::cout << "\tДобавление нового товара!\n\nВведите \"exit\" для прекрацения операции\n\n";
			std::cout << "Введите кол-во нового товара: ";
			Getline(newCount);

			if (newCount == "exit")
			{
				std::cout << "Операция добавления товара прервана!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}

			if (IsNumber(newCount))
			{
				count = std::stoi(newCount);
				if (count > maxItemSize)
				{
					std::cout << "Ошибка максимального размера товара. Не более " << maxItemSize << "ед.\n\n";
				}
				else
				{
					break;
				}

			}

		}

		while (exit)
		{
			system("cls");
			std::cout << "\tДобавление нового товара!\n\nВведите \"exit\" для прекрацения операции\n\n";
			std::cout << "Введите цену нового товара: ";
			Getline(newPrice);

			if (newPrice == "exit")
			{
				std::cout << "Операция добавления товара прервана!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}

			if (IsNumber(newPrice))
			{
				count = std::stoi(newPrice);
				if (price > 200000)
				{
					std::cout << "Ошибка максимальной цены товара. Не более " << 200000 << "ед.\n\n";
					Sleep(1500);
				}
				else
				{
					break;
				}

			}

		}

		if (exit)
		{
			std::cout << "Новый товар: " << newName << "\nКол-во: " << count << "\nЦена: " << price << "\n\n";
			std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
			Getline(choose);

			if (choose == "1")
			{
				storageSize++;
				unsigned int* idArrTemp = new unsigned int[storageSize];
				std::string* nameArrTemp = new std::string[storageSize];
				unsigned int* countArrTemp = new unsigned int[storageSize];
				double* priceArrTemp = new double[storageSize];

				FillArr(idArrTemp, idArr, storageSize - 1);
				FillArr(nameArrTemp, nameArr, storageSize - 1);
				FillArr(countArrTemp, countArr, storageSize - 1);
				FillArr(priceArrTemp, priceArr, storageSize - 1);

				idArrTemp[storageSize - 1] = storageSize;
				nameArrTemp[storageSize - 1] = newName;
				priceArrTemp[storageSize - 1] = price;
				countArrTemp[storageSize - 1] = count;

				std::swap(idArr, idArrTemp);
				std::swap(nameArr, nameArrTemp);
				std::swap(countArr, countArrTemp);
				std::swap(priceArr, priceArrTemp);

				delete[]idArrTemp, nameArrTemp, countArrTemp, priceArrTemp;
				std::cout << "Идет подготовка...";
				Sleep(2000);
				std::cout << "Товар успешно добавлен!\n\n";
				Sleep(1500);


			}
			else if (choose == "2")
			{
				std::cout << "Отмена\n\n";
				Sleep(1500);

			}
			else
			{
				Err();
			}
		}

		if (exit == false)
		{
			break;
		}
	}
}


void ChangeName()
{
	std::string newName, chooseId, choose;
	unsigned int id = 0;

	while (true)
	{
		system("cls");
		ShowStorage(3);
		std::cout << "\nВведите ID товара или \"exit\" для выхода: ";
		Getline(chooseId);

		if (newName == "exit")
		{
			std::cout << "Операция смены товара прервана!\n\n";
			Sleep(1500);
			break;
		}

		std::cout << "Введите название нового товара: ";
		Getline(newName);

		if (newName.size() <= 0 || newName.size() >= 36 || newName == "exit")
		{
			std::cout << "Ошибка имени! Максимальная длина названия 36 символов\n";
			Sleep(1500);
		}
		else if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;
			if (id < 0 || id > storageSize - 1)
			{
				std::cout << "Ошибка ID!\n";
				Sleep(1500);
			}
			else
			{
				std::cout << "\n" << std::left << std::setw(25)
					<< nameArr[id] << "---> " << newName << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					nameArr[id] = newName;
					std::cout << "Изменение названия успешно завершино\n";
					Sleep(1500);
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена\n";
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


void DeleteItem()
{
	std::string chooseId, choose;
	unsigned int id = 0;

	while (true)
	{
		system("cls");
		ShowStorage(3);
		std::cout << "\nВведите ID товара для удаления или \"exit\" для выхода: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Операция удаления товара прервана!\n\n";
			Sleep(1500);
			break;
		}

		if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;
			if (id < 0 || id > storageSize - 1)
			{
				std::cout << "Ошибка ID\n";
				Sleep(1500);
			}
			else
			{
				std::cout << "Удаляемый товар: " << nameArr[id] << "\n\n";
				std::cout << "Подтвердить ?\n1 - Да\n2 - Нет\nВвод: ";
				Getline(choose);

				if (choose == "1")
				{
					storageSize--;
					unsigned int* idArrTemp = new unsigned int[storageSize];
					std::string* nameArrTemp = new std::string[storageSize];
					unsigned int* countArrTemp = new unsigned int[storageSize];
					double* priceArrTemp = new double[storageSize];

					for (size_t i = 0, c = 0; i < storageSize; i++, c++)
					{
						if (id == c)
						{
							c++;
						}

						idArrTemp[i] = i + 1;
						nameArrTemp[i] = nameArr[c];
						countArrTemp[i] = countArr[c];
						priceArrTemp[i] = priceArr[c];

					}

					std::swap(idArr, idArrTemp);
					std::swap(nameArr, nameArrTemp);
					std::swap(countArr, countArrTemp);
					std::swap(priceArr, priceArrTemp);

					delete[]idArrTemp, nameArrTemp, countArrTemp, priceArrTemp;
					std::cout << "Идет подготовка...";
					Sleep(2000);
					std::cout << "Товар успешно удалён!\n\n";
					Sleep(1500);
					break;

				}
				else if (choose == "2")
				{
					std::cout << "Отмена удаления товара!\n";
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