#include <iostream>
#include <string>

using namespace std;

// Структура для хранения данных игрока (мостик к будущим классам!)
struct Player {
    string name;
    int hp;
    int damage;
    int gearBonus;
};
struct Enemy{
    string name;
    int hp;
    int damage;
};
struct Item{
    string name;
    string rarity;
    int damageBonus;
    int defendBonus;
};

// Прототипы функций
void showMenu();
Player createCharacter();
Enemy spawnGoblin();
bool startFight(Player &hero, Enemy &enemy);

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
                {
                    Enemy goblin = spawnGoblin();
                    startFight(hero, goblin);
                }
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

bool startFight(Player &hero, Enemy &enemy){
    cout << "\n--- БОЙ С ВРАГОМ ---" << endl;
    cout << "На вас нападает " << enemy.name << "! (HP: " << enemy.hp << ", Урон: " << enemy.damage << ")" << endl;
    
    // Общий урон героя с учетом шмоток
    int totalHeroDamage = hero.damage + hero.gearBonus;
    cout << "Ваша общая сила удара: " << totalHeroDamage << " (Базовый: " << hero.damage << " + Шмотки: " << hero.gearBonus << ")" << endl; 

    if (totalHeroDamage >= enemy.hp && hero.hp > enemy.damage){
        cout << "[!] Вы победили монстра мощным ударом!" << endl;
        return true;
    }
    else if (enemy.damage == hero.hp){
        cout << "[!] У вас честная ничья, но засчитаем это за победу :)";
        return true;
    }
    else {
        cout << "[X] Вы проиграли... Похоже пора смываться! И быстрее!!" << endl;
        return false;
    }
}

// Функция создания персонажа
Player createCharacter() {
    Player newPlayer;
    cout << "Введите имя вашего героя: ";
    cin >> newPlayer.name;
    
    // Задаем базовые параметры
    newPlayer.hp = 100;
    newPlayer.damage = 15;

    // Шмотки

    
    return newPlayer;
}
Enemy spawnGoblin(){
    Enemy goblin;
    goblin.name = "Гоблин";
    goblin.hp = 50;
    goblin.damage = 10;

    return goblin;
}