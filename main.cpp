#include <iostream>
#include <string>

using namespace std;

// Структура для хранения данных игрока (мостик к будущим классам!)
struct Player {
    string name;
    int hp;
    int damage;
};

// Прототипы функций
void showMenu();
Player createCharacter();

int main() {
    int choice = 0;
    Player hero; // Создаем переменную типа Player (пока пустую)
    
    cout << "===========================" << endl;
    cout << "   ДОБРО ПОЖАЛОВАТЬ В RPG   " << endl;
    cout << "===========================" << endl;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n--- СОЗДАНИЕ ПЕРСОНАЖА ---" << endl;
                hero = createCharacter(); // Вызываем функцию создания персонажа
                cout << "\n[!] Герой создан! Добро пожаловать, " << hero.name << "!" << endl;
                cout << "Характеристики: HP = " << hero.hp << ", Урон = " << hero.damage << "\n" << endl;
                // Здесь позже начнется основной игровой цикл
                break;
            case 2:
                cout << "\nВыход из игры. До встречи!" << endl;
                break;
            default:
                cout << "\nНеверный выбор. Попробуйте снова.\n" << endl;
        }
    } while (choice != 2);

    return 0;
}

// Определение функции меню
void showMenu() {
    cout << "Главное меню:" << endl;
    cout << "1. Начать новую игру" << endl;
    cout << "2. Выйти" << endl;
    cout << "Ваш выбор: ";
}

// Функция создания персонажа
Player createCharacter() {
    Player newPlayer;
    cout << "Введите имя вашего героя: ";
    cin >> newPlayer.name;
    
    // Задаем базовые параметры
    newPlayer.hp = 100;
    newPlayer.damage = 15;
    
    return newPlayer;
}