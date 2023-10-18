#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void printSeats(char**, const size_t, const size_t);
void fillCinema(char**, size_t, size_t, size_t, const char);
void randomFillSeats(char**, const size_t, const size_t);
// создание динамических двумерных массивов
// настройка структуры зала
// стоимость: прибыль, время сеанса, фильм, vip места, диванчики:)
// выбрать желаемый ряд

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    unsigned cols, rows;
    cout << "Введите количество рядов в зале -> "; cin >> rows;
    cout << "Введите количество мест в каждом ряду -> "; cin >> cols;

    char** seats = new char* [rows];
    for (size_t i{}; i != rows; i++) {
        seats[i] = new char[cols];
    }

    randomFillSeats(seats, cols, rows);
    printSeats(seats, cols, rows);

    string repeat = "Yes";
    unsigned humans; // число человек в группе

    char gr = '0';
    do
    {
        gr = (int)gr + 1;
        cout << "Введите колличество человек в группе " << gr << " -> " << '\n';
        cin >> humans;

        bool complete = false;
        for (size_t i{}; i < rows; ++i) { // бежим по рядам
            unsigned slots{}, firstSeat{}, lastSeat{};
            for (size_t j{}; j < cols; ++j) { // бежим по местам ряда i
                if (seats[i][j] == '0') { // если место пустое
                    slots++; // число подряд-свободных мест
                    if (slots == 1) firstSeat = j; // место для первого человека
                }
                else {
                    slots = 0; firstSeat = 0;
                }

                if (slots == humans) {
                    lastSeat = j;
                    if (!complete) fillCinema(seats, firstSeat, lastSeat, i, gr);
                    complete = true;
                }
            }
        }

        if (!complete) {
            cout << "Группу " << gr << " невозможно посадить в один ряд" << '\n';
            gr = (int)gr - 1;
        }

        printSeats(seats, cols, rows);

        cout << "Хотите посадить ещё одну группу?" << '\n';
        cin >> repeat;
    } while (repeat == "Yes");

}
void printSeats(char** seats, const size_t cols, const size_t rows) {
    cout << "-----SCREEN-----" << '\n';
    for (size_t i{}; i != rows; ++i) {
        for (size_t j{}; j != rows; ++j) {
            cout << seats[i][j] << " ";
        }
        cout << '\n';
    }
}

// рандомно сажаем людей
void randomFillSeats(char** seats, const size_t cols, const size_t rows) {
    char elems[2] = { '0', '*' };
    /*можно через if*/
    for (size_t i{}; i != rows; ++i) {
        for (size_t j{}; j != rows; ++j) {
            seats[i][j] = elems[rand() % 2];
        }
    }
}

void fillCinema(char** seats, size_t fs, size_t ls, size_t row, const char gr) {
    for (size_t i = fs; i <= ls; ++i) {
        seats[row][i] = gr;
    }
}
