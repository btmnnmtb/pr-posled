#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

map<string, string> users;
struct Dish {
    string name;
    int price;
};
struct Sotrudnik {
    string role;
    string surname;
    string name;
    string otchestvo;
    string login;
    string password;
};
vector<Dish> cart; 

void saveUsers() {
    ofstream file("users.txt");
    for (auto& user : users) {
        file << user.first << " " << user.second << "\n";
    }
    file.close();
}
bool login(string username, string password) {
    if (users.find(username) != users.end() && users[username] == password) {
        return true; 
    }
    return false;  
}

void deleteDish() {
    string nameToDelete;
    cout << "Введите название блюда, которое хотите удалить: ";
    cin >> nameToDelete;

    ifstream file("dishes.txt");
    ofstream tempFile("temp.txt");

    if (!file.is_open() || !tempFile.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        string dishName = line.substr(0, line.find(" "));
        if (dishName != nameToDelete) {
            tempFile << line << endl;
        }
        else {
            found = true;
        }
        getline(file, line);
        tempFile << line << endl;
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("dishes.txt");
        rename("temp.txt", "dishes.txt");
        cout << "Блюдо успешно удалено." << endl;
    }
    else {
        remove("temp.txt");
        cout << "Блюдо с таким названием не найдено." << endl;
    }
}
void deleteSotr() {
    string loginToDelete;
    cout << "Введите логин сотрудника, которого хотите удалить: ";
    cin >> loginToDelete;

    ifstream file("sotrudniki.txt");
    ofstream tempFile("temp.txt");

  

    string line;
    bool found = false;
    while (getline(file, line)) {
        string log = line.substr(0, line.find(" "));
        if (log != loginToDelete) {
            tempFile << line << endl;
        }
        else {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("sotrudniki.txt");
        rename("temp.txt", "sotrudniki.txt");
        cout << "Сотрудник успешно удален." << endl;
    }
    else {
        remove("temp.txt");
        cout << "Сотрудник с таким логином не найден." << endl;
    }
}

void registerUser(string username, string password) {
    users[username] = password; 
    saveUsers();
}
void saveAdmins() {
    ofstream file("admins.txt");
    for (const auto& user : users) {
        file << user.first << " " << user.second << "\n";
    }
    file.close();
}
void registerAdmins(string username, string password) {
    users[username] = password; 
        saveAdmins();
}
void addDish(const string& dishName, int price) {
    ofstream file("dishes.txt", ios::app); 

    if (!file.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return;
    }

    file << dishName << " " << price << endl;
    file.close();

    cout << "Блюдо успешно добавлено." << endl;
}
void addsotr(const string& dojnost, const string& surname, const string& name, const string& otchestvo, const string& login, int pass) {
    ofstream file("sotrudniki.txt", ios::app);
   

    file << dojnost << " " << surname << " " << name << " " << otchestvo << " " << login << " " << pass << endl;
    file.close();

    cout << "сотрудник успешно добавлен." << endl;
}



void loadUsers() {
    fstream file("users.txt");
    string line, username, password;
    if (getline(file, line)) {
        size_t pos = line.find(" ");
        username = line.substr(0, pos);
        password = line.substr(pos + 1);
        users[username] = password;
    }
    file.close();  
}
void loadAdmin() {
    fstream file("admins.txt");
    string line, username, password;
    if (getline(file, line)) {
        size_t pos = line.find(" ");
        username = line.substr(0, pos);
        password = line.substr(pos + 1);
        users[username] = password;

    }

    file.close();
}
void loadSotrudnik() {
    fstream file("Sotrudnik.txt");
    string line, role , surname , name, otchestvo , username  ,   password;
    if (getline(file, line)) {
        size_t pos = line.find(" ");
        username = line.substr(0, pos);
        password = line.substr(pos + 1);
        users[username] = password;

    }

    file.close();
}
int calculateTotalPrice() {
    int totalPrice = 0;
    for (const auto& dish : cart) {
        totalPrice += dish.price;
    }
    return totalPrice;
}

void korzina() {
    cout << "Ваша корзина:" << endl;
    if (cart.empty()) {
        cout << "Корзина пуста." << endl;
    }
    else {
        for (const auto& dish : cart) {
            cout << dish.name << " - " << dish.price << " руб." << endl;
        }
    }
    int totalPrice = calculateTotalPrice();
    cout << "Общая сумма: " << totalPrice << " руб." << endl;
    cout << "Внесите полату" << endl; 
    int oplata; 
    cin >> oplata;
    if (oplata == totalPrice) {
        cout << "Оплата прошла успешно" << endl; 
        ofstream file("zakaz.txt" , ios::app);
        if (file.is_open()) {
            file << "Содержимое корзины:" << endl;
            for (const auto& dish : cart) {
                file << dish.name << " - " << dish.price << " руб." << endl;
            }
            file << "Общая сумма: " << calculateTotalPrice() << " руб." << endl;
            file << "Статус: оплачен и передан на кухню" << endl;
            file.close();
            cout << "Данные успешно записаны в файл." << endl;
        }
       
    }
    else if (oplata > totalPrice)
    {
        int cdacha; 
        cdacha = oplata - totalPrice;
        cout << "Ваша сдача -" << cdacha << endl; 
    }
    else if (oplata < totalPrice) {
        cout << "Недостаточно средвтсв" << endl; 
        char ll; 
        cin >> ll;
        system("cls"); 
        korzina(); 

    }

} 
void updatedish() {
    ifstream file("dishes.txt");
    ofstream tempFile("temp.txt");

    if (!file.is_open() || !tempFile.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return;
    }

    string line;
    int dishNumber = 1;
    while (getline(file, line)) {
        cout << dishNumber << ". " << line << endl;
        getline(file, line);
        tempFile << line << endl;
        dishNumber++;
    }

    file.close();
    tempFile.close();

    cout << "Введите номер блюда, которое хотите изменить (0 - для выхода): ";
    int choice;
    cin >> choice;

    if (choice == 0) {
        return;
    }

    if (choice < 1 || choice >= dishNumber) {
        cout << "Неверный номер блюда." << endl;
        return;
    }

    string newName, newPrice;
    cout << "Введите новое название блюда: ";
    cin >> newName;
    cout << "Введите новую цену блюда: ";
    cin >> newPrice;

    file.open("temp.txt");
    tempFile.open("dishes.txt");

    dishNumber = 1;
    while (getline(file, line)) {
        if (dishNumber == choice) {
            tempFile << newName << " " << newPrice << endl;
        }
        else {
            tempFile << line << endl;
        }
        getline(file, line);
        tempFile << line << endl;
        dishNumber++;
    }

    file.close();
    tempFile.close();

    remove("temp.txt");
    cout << "Блюдо успешно изменено." << endl;

}
vector<Sotrudnik> loadSotrudniki() {
    vector<Sotrudnik> sotrudniki;
    fstream file("sotrudniki.txt");
    string line;
    while (getline(file, line)) {
        Sotrudnik sotrudnik;
        size_t pos = line.find(" ");
        sotrudnik.role = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(" ");
        sotrudnik.surname = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(" ");
        sotrudnik.name = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(" ");
        sotrudnik.otchestvo = line.substr(0, pos);
        line = line.substr(pos + 1);
        pos = line.find(" ");
        sotrudnik.login = line.substr(0, pos);
        sotrudnik.password = line.substr(pos + 1);
        sotrudniki.push_back(sotrudnik);
    }
    file.close();
    return sotrudniki;
}
void saveSotrudniki(const vector<Sotrudnik>& sotrudniki) {
    ofstream file("sotrudniki.txt");
    for (const auto& sotrudnik : sotrudniki) {
        file << sotrudnik.role << " " << sotrudnik.surname << " " << sotrudnik.name << " " << sotrudnik.otchestvo << " " << sotrudnik.login << " " << sotrudnik.password << "\n";
    }
    file.close();
}
void editSotrudnik(vector<Sotrudnik>& sotrudniki) {
    int index;
    cout << "Введите номер сотрудника, которого хотите редактировать (1-" << sotrudniki.size() << "): ";
    cin >> index;
    index--; 

    if (index < 0 || index >= sotrudniki.size()) {
        cout << "Неверный номер сотрудника." << endl;
        return;
    }

    cout << "Текущие данные сотрудника:" << endl;
    cout << "Роль: " << sotrudniki[index].role << endl;
    cout << "Фамилия: " << sotrudniki[index].surname << endl;
    cout << "Имя: " << sotrudniki[index].name << endl;
    cout << "Отчество: " << sotrudniki[index].otchestvo << endl;
    cout << "Логин: " << sotrudniki[index].login << endl;
    cout << "Пароль: " << sotrudniki[index].password << endl;

    cout << "Введите новые данные (оставьте поле пустым, чтобы сохранить текущее значение):" << endl;

    string newRole, newSurname, newName, newOtchestvo, newLogin, newPassword;
    cout << "Новая роль: ";
    getline(cin, newRole);
    if (!newRole.empty()) {
        sotrudniki[index].role = newRole;
    }
    cout << "Новая фамилия: ";
    getline(cin, newSurname);
    if (!newSurname.empty()) {
        sotrudniki[index].surname = newSurname;
    }
    cout << "Новое имя: ";
    getline(cin, newName);
    if (!newName.empty()) {
        sotrudniki[index].name = newName;
    }
    cout << "Новое отчество: ";
    getline(cin, newOtchestvo);
    if (!newOtchestvo.empty()) {
        sotrudniki[index].otchestvo = newOtchestvo;
    }
    cout << "Новый логин: ";
    getline(cin, newLogin);
    if (!newLogin.empty()) {
        sotrudniki[index].login = newLogin;
    }
    cout << "Новый пароль: ";
    getline(cin, newPassword);
    if (!newPassword.empty()) {
        sotrudniki[index].password = newPassword;
    }

    saveSotrudniki(sotrudniki);
    cout << "Данные сотрудника успешно обновлены." << endl;
}




int main() {
    setlocale(LC_ALL, "ru");
    cout << "Выберите роль" << endl;
    cout << "1.Пользователь" << endl;
    cout << "2.Админ" << endl;
    cout << "3.Сотрудник" << endl;
    int vubor_role;
    cin >> vubor_role;
    if (vubor_role == 1) {
        loadUsers();
        string username, password;
        cout << "Введите Логин: ";
        cin >> username;
        cout << "Введите пароль: ";
        cin >> password;
        if (login(username, password)) {
            cout << "Вы вошли!" << std::endl;
            cout << "1.Сделать заказ" << endl;
            cout << "2.Выйти" << endl;
            int vubor_user;
            cin >> vubor_user;
            if (vubor_user == 1) {


                ifstream file("dishes.txt");

                if (!file.is_open()) {
                    std::cout << "Не удалось открыть файл." << std::endl;
                    return 1;
                }
                string line;
                int dishNumber = 1;
                while (std::getline(file, line)) {
                    std::cout << dishNumber << ". " << line << std::endl;
                    int price;

                    size_t pos = line.find(" ");
                    std::string dishName = line.substr(0, pos);
                    std::string priceStr = line.substr(pos + 1);
                    price = std::stoi(priceStr);
                    cart.push_back({ dishName, price });
                    dishNumber++;
                }
                file.close();
                cout << "Выберите блюда (укажите их номера, 0 - для завершения): ";
                int choice;
                while (true) {
                    cin >> choice;
                    if (choice == 0) {
                        break;
                    }
                    if (choice >= 1 && choice < dishNumber) {
                        cout << "Блюдо добавлено в корзину." << endl;
                    }
                    else {
                        cout << "Неверный номер блюда. Попробуйте еще раз." << endl;
                    }
                }
                korzina();
            }
            else if (vubor_user == 2) {
                system("cls");
                main();

            }
            else {
                cout << "Вы что-то ввели не правильно" << endl;
            }

        }

        else {
            cout << "Неверный логин или пароль." << endl;
            cout << "Или Вы первый раз и хотите авторизироваться? (y/n) ";
            char choice;
            cin >> choice;
            if (choice == 'y') {
                registerUser(username, password);
                cout << "Вы зарегисрированны!" << endl;
                system("cls");
                main();
            }
        }
    }
    else if (vubor_role == 2) {


        loadAdmin(); string username, password;
        vector<Sotrudnik> sotrudniki = loadSotrudniki();
        cout << "Введите Логин: ";
        cin >> username;
        cout << "Введите пароль: ";
        cin >> password;
        if (login(username, password)) {

            do {



                cout << "Вы вошли как администратор!" << endl;
                cout << "1.Изменить сотрудника " << endl;
                cout << "2.Изменить блюда " << endl;
                cout << "3.Добавть блюдо" << endl;
                cout << "4. удалить блюдо" << endl;
                cout << "5. удалить сотрудника" << endl;
                cout << "6. добавить сотрудника" << endl;
                cout << "Выберите один из вариатов " << endl;
                int vubor_admina;
                cin >> vubor_admina;

                if (vubor_admina == 2) {
                    updatedish();
                    system("cls");

                }
                else if (vubor_admina == 1)
                {
                    editSotrudnik(sotrudniki);

                }
                else if (vubor_admina == 3) {
                    string dishName;
                    int price;
                    cout << "Введите названия нового блюдо" << endl;
                    cin >> dishName;
                    cin >> price;
                    addDish(dishName, price);
                }
                else if (vubor_admina == 4) {
                    deleteDish();

                }
                else if (vubor_admina == 5) {
                    deleteSotr();

                }
                else if (vubor_admina == 6) {
                    string doljn;
                    string surname;
                    string name;
                    string otch;
                    string log;
                    int pass;
                    cout << "Введите должность новго сорудника" << endl;
                    cin >> doljn;
                    cout << "Введите фамилию новго сорудника" << endl;
                    cin >> surname;
                    cout << "Введите имя новго сорудника" << endl;
                    cin >> name;
                    cout << "Введите отчетсво новго сорудника" << endl;
                    cin >> otch;
                    cout << "Введите логин новго сорудника" << endl;
                    cin >> log;
                    cout << "Введите пароль новго сорудника" << endl;
                    cin >> pass;

                    addsotr(doljn, surname, name, otch, log, pass);
                }
            } while (true);


        }







        else {
            cout << "Неверный логин или пароль." << endl;
            cout << "Или Вы первый раз и хотите авторизироваться? (y/n) ";
            char choice;
            cin >> choice;
            if (choice == 'y') {
                registerAdmins(username, password);
                cout << "Вы зарегисрированны!" << endl;
                system("cls");
                main();
            }
            else if (choice == 'n') {
                system("cls");
                main();

            }
        }

    }
    else if (vubor_role == 3) {
        loadSotrudnik();
        string username, password;
        cout << "Введите Логин: ";
        cin >> username;
        cout << "Введите пароль: ";
        cin >> password;
        if (login(username, password)) {
            cout << "afa" << endl;
        }
        else {
            cout << "Неверный логин или пароль или вас не зарегестрировали." << endl;
            main();
        }

    }
    else {
        cout << "нет такой роли" << endl;
        main();
    }



    return 0;



}