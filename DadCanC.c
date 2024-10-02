#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int number, guess, attempts = 0;

    // Инициализация генератора случайных чисел
    srand(time(0));
    number = rand() % 100 + 1; // Загаданное число от 1 до 100

    printf("Угадайте число от 1 до 100:\n");
    do {
        printf("Введите ваше предположение: ");
        scanf("%d", &guess);
        attempts++;

        if (guess < number) {
            printf("Слишком маленькое число. Попробуйте снова.\n");
        } else if (guess > number) {
            printf("Слишком большое число. Попробуйте снова.\n");
        } else {
            printf("Поздравляю! Вы угадали число %d за %d попыток.\n", number, attempts);
        }
    } while (guess != number);

    return 0;
}
