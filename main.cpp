#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;
// Структура для хранения данных игрока (мостик к будущим классам!)
struct Player {
    string name;
    int hp;
    int damage;
    int gearDamage;
    int gearDefend;
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
Item generateRandomItem();

int main() {
    srand(time(0));
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
                hero = createCharacter(); 
                cout << "\n[!] Герой создан! Добро пожаловать, " << hero.name << "!" << endl;
                cout << "Характеристики: HP = " << hero.hp << ", Урон = " << hero.damage << "\n" << endl;
                
                // Внутренний цикл приключений (пока герой не проиграет)
                {
                    bool playing = true;
                    while (playing) {
                        Enemy goblin = spawnGoblin();
                        bool won = startFight(hero, goblin);
                        
                        if (!won) {
                            cout << "\n[!] Вы сбежали из боя и возвращаетесь в главное меню..." << endl;
                            playing = false; // Выходим из цикла приключений
                        } else {
                            cout << "\nХотите продолжить подземелье? (1 - Идти дальше, 0 - В главное меню): ";
                            int nextStep;
                            cin >> nextStep;
                            if (nextStep != 1) {
                                playing = false;
                            }
                        }
                    }
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
    
    int totalHeroDamage = hero.damage + hero.gearDamage;
    int totalHeroDefend = hero.hp + hero.gearDefend;
    cout << "Ваша общая сила удара: " << totalHeroDamage << " (Базовый: " << hero.damage << " + Оружие: " << hero.gearDamage << ")" << endl; 
    cout << "Ваша защита сейчас: " << totalHeroDefend << " (Базовый: " << hero.hp << " + Броня: " << hero.gearDefend << ")" << endl;
    if (totalHeroDamage >= enemy.hp && totalHeroDefend > enemy.damage){
        cout << "[!] Вы победили монстра мощным ударом!" << endl;
        
        // Генерируем лут за победу!
        Item foundItem = generateRandomItem();
        cout << "\n[LOOT] Вы нашли трофей: " << foundItem.name << " [" << foundItem.rarity << "]!" << endl;
        cout << "Бонус предмета к урону: +" << foundItem.damageBonus << endl;
        
        // Увеличиваем бонус шмоток героя
        hero.gearDamage += foundItem.damageBonus;
        cout << "Ваш новый суммарный урон от шмоток: " << hero.gearDamage << endl;

        // Увеличиваем бонус шмоток героя
        hero.gearDefend += foundItem.defendBonus;
        cout << "Ваша суммарная защита от шмоток: " << hero.gearDefend << endl;
        
        return true;
    }
    else if (enemy.damage == hero.hp){
        cout << "[!] У вас честная ничья, но засчитаем это за победу :)" << endl;
        
        // Даже при ничьей можно дать слабый утешительный лут
        Item foundItem = generateRandomItem();
        cout << "[LOOT] В суматохе боя вам удалось утащить трофей: " << foundItem.name << " (+" << foundItem.damageBonus << " к урону)!" << endl;
        hero.gearDamage += foundItem.damageBonus;
        hero.gearDefend += foundItem.defendBonus;
        
        return true;
    }
    else {
        cout << "[X] Вы проиграли... Похоже пора смываться! И быстрее!!" << endl;
        cout << "Монстр злобно хохочет и забирает у вас часть уверенности (и никаких шмоток)." << endl;
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
    newPlayer.gearDamage = 0;
    newPlayer.gearDefend = 0;
    
    return newPlayer;
}
Enemy spawnGoblin(){
    Enemy goblin;
    goblin.name = "Гоблин";
    goblin.hp = 5;
    goblin.damage = 2;

    return goblin;
}
// Пример функции генерации случайного предмета
Item generateRandomItem() {
    Item randomItem;
    
    // Массив или выборка имен и редкости
    int rarityRoll = rand() % 100; // число от 0 до 99
    int innerRoll = rand() % 2 + 1; // число от 1 до 2
    
    if (rarityRoll < 60) {
        randomItem.rarity = "Обычный";
        // Случайный бонус к урону в диапазоне от 1 до 5
        randomItem.damageBonus = 1 + (rand() % 5); 
        randomItem.defendBonus = 0;
        randomItem.name = "Ржавый меч";
    } else if (rarityRoll < 90) {
        randomItem.rarity = "Редкий";
        
        if (innerRoll == 1){
        // Бонус от 6 до 12
        randomItem.damageBonus = 6 + (rand() % 7);
        randomItem.defendBonus = 1;
        randomItem.name = "Эльфийский кинжал";
        }
        if (innerRoll == 2){
        randomItem.damageBonus = 2;
        randomItem.defendBonus = 6 + (rand() % 7);
        randomItem.name = "Эльфийская броня";
        }
        
    } else {
        randomItem.rarity = "Эпический";
        if (innerRoll == 1){
        // Бонус от 13 до 20
        randomItem.damageBonus = 13 + (rand() % 8);
        randomItem.defendBonus = 3;
        randomItem.name = "Меч Тысячи Истин";
        }
        if (innerRoll == 2){
        // Бонус от 13 до 20
        randomItem.damageBonus = 4;
        randomItem.defendBonus = 13 + (rand() % 8);
        randomItem.name = "Броня заклинателя";
        }
    }
    
    return randomItem;
}