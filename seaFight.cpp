#include <iostream>

const char EMPTYCELL = '+';
const char MISSCELL = '*';
const char SHOTSHIPCELL = '!';
const char KILLEDSHIPCELL = 'X';
const char SHIPCELL = '#';
const char UNKNOWNCELL = '?';

const int SHIPSNUMBER = 10;
const int SHIPS[] = {1, 1, 1, 1, 2, 2, 2, 3, 3, 4};

void helloMessage() {
    std::cout << "Welcome on board, commander! It is \" Sea fight\"\n";
    std::cout << "You need to kill enemy's warships and I will tell you have you missed, damaged or killed a warship\n";
    std::cout << "good luck!\n\n";
}

void printPlayerField(char playerField[12][12]) {
    std::cout << "   ";
    for(int i = 1; i <= 10; i++){
        std::cout << i << ' ';
    }
    std::cout << "\n";
    for(int i = 1; i <= 10; i++){
        std::cout << i;
        if(i != 10){
            std::cout << ' ';
        }
        for(int j = 1; j <= 10; j++){
            std::cout << " " << playerField[i][j];
        }
        std::cout << "\n";
    }
}

void printEnemyField(char enemyField[12][12]) {
    std::cout << "   ";
    for(int i = 1; i <= 10; i++){
        std::cout << i << ' ';
    }
    std::cout << "\n";
    for(int i = 1; i <= 10; i++){
        std::cout << i;
        if(i != 10){
            std::cout << ' ';
        }
        // Выводит строку
        for(int j = 1; j <= 10; j++){
            if (enemyField[i][j] == SHIPCELL){
                std::cout << " " << UNKNOWNCELL;
            } else{
                std::cout << " " << enemyField[i][j];
            }
        }
        std::cout << '\n';
    }
} 

bool isValidPlace(char playerField[12][12], int i1,int j1, int i2,  int j2){
    if(i1 != i2 && j1 != j2){
        return false;
    }
    if(i1 < 1 || i1 > 10 || i2 < 1 || i2 > 10 || j1 < 1 || j1 > 10 || j2 < 1 || j2 > 10){
        return false;
    }
        
    // проверить пустоту всех нужных клеток
    int iMax = std::max(i1, i2), iMin = std::min(i1, i2);
    int jMax = std::max(j1, j2), jMin = std::min(j1, j2);
    for(int i = iMin - 1; i <= iMax + 1; i++) {
        for(int j = jMin - 1; j <= jMax + 1; j++) {
            if (playerField[i][j] != EMPTYCELL && playerField[i][j] != UNKNOWNCELL){
                return false;
            }
        }
    }
    return true;
}

void playerShips(char playerField[12][12]) {
    for(int i = 0; i < SHIPSNUMBER; i++){
        printPlayerField(playerField);
        std::cout << "You need to put this " << SHIPS[i] << " celled ship somewhere.\n";
        std::cout << "Enter cordinates of your number:";
        int i1, i2, j1, j2;
        std::cin >> i1 >> j1 >> i2 >> j2;
        while(SHIPS[i] != abs(i1 - i2) + 1 && SHIPS[i] != abs(j1 - j2) + 1 || (!isValidPlace(playerField,i1,j1, i2, j2))) {
            std::cout << "You can't place a ship on this coords, try again: ";
            std::cin >> i1 >> j1 >> i2 >> j2; 
        }
        int iMax = std::max(i1, i2), iMin = std::min(i1, i2);
        int jMax = std::max(j1, j2), jMin = std::min(j1, j2);
        for (int itemp = iMin; itemp <= iMax; ++itemp)  {
            for (int jtemp = jMin; jtemp <= jMax; ++jtemp) {
                playerField[itemp][jtemp] = SHIPCELL;
            }
        }
    }
}

void computerShips(char enemyField[12][12]) {
    srand(time(0));
    for (int i = 0; i < SHIPSNUMBER; i++){
        int shipLength = SHIPS[i]; 
        // пока не найдено место куда можно разместить корабль делать:
            // начало корабля выбирается рандомно
            // выбираем одну из 4 клеток вокруг начала корабля
            // проверяем можем ли мы разместить корабль в этом месте
            // если можем разместить, то размещаем и делаем break
        while(true){
            int i1 = rand() % 10 + 1, j1 = rand() % 10 + 1;
            int option = rand() % 4;
            int i2, j2;
            if (option == 0) {
                j2 = j1;
                i2 = i1 - shipLength + 1;
            } else if (option == 1) {
                j2 = j1;
                i2 = i1 + shipLength - 1;
            } else if (option == 2) {
                i2 = i1;
                j2 = j1 + shipLength - 1;
            } else {
                i2 = i1;
                j2 = j1 - shipLength + 1;
            }
            if (isValidPlace(enemyField, i1, j1, i2, j2)) {
                int iMax = std::max(i1, i2), iMin = std::min(i1, i2);
                int jMax = std::max(j1, j2), jMin = std::min(j1, j2);
                for (int itemp = iMin; itemp <= iMax; ++itemp)  {
                    for (int jtemp = jMin; jtemp <= jMax; ++jtemp) {
                        enemyField[itemp][jtemp] = SHIPCELL;
                    }
                }
                break; 
            }
        }
    }
}

void markShipFrontiers(char field[12][12], int i, int j){
    if (field[i - 1][j - 1] == EMPTYCELL || field[i - 1][j - 1] == UNKNOWNCELL) {
        field[i - 1][j - 1] = MISSCELL;
    }
    if (field[i - 1][j] == EMPTYCELL || field[i - 1][j] == UNKNOWNCELL) {
        field[i - 1][j] = MISSCELL;
    }
    if (field[i - 1][j + 1] == EMPTYCELL || field[i - 1][j + 1] == UNKNOWNCELL) {
        field[i - 1][j + 1] = MISSCELL;
    }
    if (field[i][j - 1] == EMPTYCELL || field[i][j - 1] == UNKNOWNCELL) {
        field[i][j - 1] = MISSCELL;
    }
    if (field[i][j + 1] == EMPTYCELL || field[i][j + 1] == UNKNOWNCELL) {
        field[i][j + 1] = MISSCELL;
    }
    if (field[i + 1][j + 1] == EMPTYCELL || field[i + 1][j + 1] == UNKNOWNCELL) {
        field[i + 1][j + 1] = MISSCELL;
    }
    if (field[i + 1][j] == EMPTYCELL || field[i + 1][j] == UNKNOWNCELL) {
        field[i + 1][j] = MISSCELL;
    }
    if (field[i + 1][j - 1] == EMPTYCELL || field[i + 1][j - 1] == UNKNOWNCELL) {
        field[i + 1][j - 1] = MISSCELL;
    }
    
}
                                                                                                                                                                                                                                                                                                             
int fireField(char field[12][12], int i1, int j1) {
    if(field[i1][j1] == EMPTYCELL || field[i1][j1] == UNKNOWNCELL) {
        field[i1][j1] = MISSCELL;
        return 0;
    } else {
        field[i1][j1] = SHOTSHIPCELL;
        bool isKilled = true;
        for(int j = j1 + 1; j <= 10; j++) {
            if(field[i1][j] == EMPTYCELL || field[i1][j] == UNKNOWNCELL || field[i1][j] == MISSCELL){
                break;
            } else if (field[i1][j] == SHIPCELL) {
                isKilled = false;
                break;
            }
        }
        for(int j = j1 - 1; j >= 1; j--) {
            if(field[i1][j] == EMPTYCELL || field[i1][j] == UNKNOWNCELL || field[i1][j] == MISSCELL){
                break;
            } else if (field[i1][j] == SHIPCELL) {
                isKilled = false;
                break;
            }
        }
        for(int i = i1 - 1; i >= 1; i--) {
            if(field[i][j1] == EMPTYCELL || field[i][j1] == UNKNOWNCELL || field[i][j1] == MISSCELL){
                break;
            } else if (field[i][j1] == SHIPCELL) {
                isKilled = false;
                break;
            }
        }
        for(int i = i1 + 1; i <= 10; i++) {
            if(field[i][j1] == EMPTYCELL || field[i][j1] == UNKNOWNCELL || field[i][j1] == MISSCELL){
                break;
            } else if (field[i][j1] == SHIPCELL) {
                isKilled = false;
                break;
            }
        }
        if(isKilled) {
            field[i1][j1] = KILLEDSHIPCELL;
            markShipFrontiers(field, i1, j1);
            for(int j = j1 + 1; j <= 10; j++) {
                if(field[i1][j] == EMPTYCELL || field[i1][j] == UNKNOWNCELL || field[i1][j] == MISSCELL){
                    break;
                } else if (field[i1][j] == SHOTSHIPCELL) {
                    markShipFrontiers(field, i1, j);
                    field[i1][j] = KILLEDSHIPCELL;
                }
            }
            for(int j = j1 - 1; j >= 1; j--) {
                if(field[i1][j] == EMPTYCELL || field[i1][j] == UNKNOWNCELL || field[i1][j] == MISSCELL){
                    break;
                } else if (field[i1][j] == SHOTSHIPCELL) {
                    markShipFrontiers(field, i1, j);
                    field[i1][j] = KILLEDSHIPCELL;
                }
            }
            for(int i = i1 - 1; i >= 1; i--) {
                if(field[i][j1] == EMPTYCELL || field[i][j1] == UNKNOWNCELL || field[i][j1] == MISSCELL){
                    break;
                } else if (field[i][j1] == SHOTSHIPCELL) {
                    markShipFrontiers(field, i, j1);
                    field[i][j1] = KILLEDSHIPCELL;
                }
            }
            for(int i = i1 + 1; i <= 10; i++) {
                if(field[i][j1] == EMPTYCELL || field[i][j1] == UNKNOWNCELL || field[i][j1] == MISSCELL){
                    break;
                } else if (field[i][j1] == SHOTSHIPCELL) {
                    markShipFrontiers(field, i, j1);
                    field[i][j1] = KILLEDSHIPCELL;
                }
            } 
            return 2;
        } else {
            return 1;
        }
    }
}

bool isValidCell(char field[12][12], int i, int j) {
    if(i < 1 || i > 10 || j < 1 || j > 10){
        return false;
    }

    if (field[i][j] == SHOTSHIPCELL ||
    field[i][j] == KILLEDSHIPCELL || field[i][j] == MISSCELL){
        return false;
    } else{
        return true;
    }
}

int playerMove(char enemyField[12][12]) {
    // Просим человека ввести координаты выстрела
    std::cout << "enter coordinates where you want to shoot: ";
    int i, j;
    std::cin >> i >> j;
    // Пока координаты неправильные, просим ввести заново
    while(!isValidCell(enemyField, i, j)){
        std::cout << "Do you even see the field? Write adecuate cell!: ";
        std::cin >> i >> j;
    }
    // Делаем выстрел с помощью функции fireField
    int result = fireField(enemyField, i, j);
    // Сообщаем пользователю результат
    if(result == 0) {
        std::cout << "You missed!\n";
    } else if (result == 1) {
        std::cout << "You have damaged a ship!\n";
    } else {
        std::cout << "You have killed a ship!\n"; 
    }
    return result;
    
}

int initDamagedCell_i = 0, initDamagedCell_j = 0;
bool isDamagedShip = false;
int prevDamagedCell_i = 0, prevDamagedCell_j = 0;
int orientation_i = 0, orientation_j = 0;
bool computerMove(char playerField[12][12]) {
    // Ход компьютера...
    
    // Выбор случайной клетки пока не найдется клетка в которую не стреляли

    int i, j;
    if (!isDamagedShip) {
        do {
            i = rand() % 10 + 1;
            j = rand() % 10 + 1;
        } while(!isValidCell(playerField, i, j));
    } else {
        i = prevDamagedCell_i + orientation_i;
        j = prevDamagedCell_j + orientation_j;
    }
    std::cout << "Computer shoots in cell " << i << " " << j << "\n";

    // Выстрел по выбранной клетке
    int result = fireField(playerField, i, j);
    // Сообщение результата выстрела пользователю
    if(result == 0) {
        std::cout << "Computer missed!\n";
        if (isDamagedShip) {
            if (prevDamagedCell_i != initDamagedCell_i || prevDamagedCell_j != initDamagedCell_j) {
                prevDamagedCell_i = initDamagedCell_i;
                prevDamagedCell_j = initDamagedCell_j;
                orientation_i *= -1;
                orientation_j *= -1;
            } else {
                orientation_i = rand() % 3 - 1;
                if (orientation_i == 0) {
                    orientation_j = rand() % 2;
                    if (orientation_j == 0) {
                        orientation_j = -1;
                    }
                } else {
                    orientation_j = 0;
                }
                while(!isValidCell(playerField, initDamagedCell_i + orientation_i, initDamagedCell_j + orientation_j)) {
                    orientation_i = rand() % 3 - 1;
                    if (orientation_i == 0) {
                        orientation_j = rand() % 2;
                        if (orientation_j == 0) {
                            orientation_j = -1;
                        }
                    } else {
                        orientation_j = 0;
                    }
                }
            }
            
        }
    } else if (result == 1) {
        std::cout << "Computer has damaged your ship!\n";
        if (!isDamagedShip) {
            isDamagedShip = true;
            initDamagedCell_i = i;
            initDamagedCell_j = j;
            prevDamagedCell_i = i;
            prevDamagedCell_j = j;
            // выбор направления
            orientation_i = rand() % 3 - 1;
            if (orientation_i == 0) {
                orientation_j = rand() % 2;
                if (orientation_j == 0) {
                    orientation_j = -1;
                }
            } else {
                orientation_j = 0;
            }
            while(!isValidCell(playerField, initDamagedCell_i + orientation_i, initDamagedCell_j + orientation_j)) {
                orientation_i = rand() % 3 - 1;
                if (orientation_i == 0) {
                    orientation_j = rand() % 2;
                    if (orientation_j == 0) {
                        orientation_j = -1;
                    }
                } else {
                    orientation_j = 0;
                }
            }
        } else {
            prevDamagedCell_i = i;
            prevDamagedCell_j = j;
            if (!isValidCell(playerField, i + orientation_i, j + orientation_j)) {
                prevDamagedCell_i = initDamagedCell_i;
                prevDamagedCell_j = initDamagedCell_j;
                orientation_i *= -1;
                orientation_j *= -1;
            }
        }
    } else {
        std::cout << "Computer has killed your ship!\n"; 
        isDamagedShip = false;
    }
    return result;
}

void SeaFight(){
    // Инициализация полей
    char playerField[12][12];
    char enemyField[12][12];
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 12; j++){
            playerField[i][j] = EMPTYCELL;
            enemyField[i][j] = UNKNOWNCELL;
        }
    }
    // Приветствие
    helloMessage();
    // Расстановка кораблей пользователем
    playerShips(playerField);
    // Расстановка кораблей компьютером
    computerShips(enemyField);
    // Случайный выбор кто ходит первым
    srand(time(0));
    int turn = rand() % 2;
    
    int playerCounter = 0;
    int computerCounter = 0;
    // Игровой цикл пока кто-то не уничтожит все корабли
        // Отрисовка поля
        // Чей-то ход
    while(playerCounter != 10 && computerCounter != 10) {
        printPlayerField(playerField);
        printEnemyField(enemyField);
        if(turn == 0){
            std::cout << "Your turn!\n";
            int result = playerMove(enemyField);
            if(result == 0){
                turn = 1;
            } else if(result == 2){
                playerCounter++;
            }
        } else {
            std::cout << "Computer turn!\n";
            int result = computerMove(playerField);
            if(result == 0){
                turn = 0;
            } else if (result == 2){
                computerCounter++;
            }
        } 
    }
    printPlayerField(enemyField);
    printPlayerField(playerField);
    // Объявление победителя
    if(playerCounter == 10){
        std::cout << "VICTORY!"; 
    } else {
        std::cout << "DEFEAT!";
    }
}

int main() {
    SeaFight();
}


// x - убит
// * - мимо
// ? - неизвестно(врага)
// ! - поподание
// + - пустые клетки(свои)
// # - корабли

// Приветствие
// Расстановка кораблей (проверка на правильность ввода)
// Случайный выбор кто ходит первым
// Основной игровой цикл пока кто-то не уничтожит корабли
// Проверка на правильность ввода
// Сообщение о конце игры