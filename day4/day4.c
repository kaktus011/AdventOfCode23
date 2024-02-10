#include <stdio.h>
#include <string.h>

#define MAX_NUMBERS 25

int get_points(int numbers[2][MAX_NUMBERS]);

int get_points(int numbers[2][MAX_NUMBERS]) {
    int points = 0;

    for (int winning = 0; winning < MAX_NUMBERS; winning++) {
        if (numbers[1][winning]  == 0) {
            break;
        }

        for (int i = 0; i < MAX_NUMBERS; i++) {
            if (numbers[0][i] == 0) {
                break;
            }

            if (numbers[0][i] == numbers[1][winning] && points == 0) {
                ++points;
            }
            else if (numbers[0][i] == numbers[1][winning]) {
                points *= 2;
            }
        }
    }

    return points;
}

int main () {
    int numbers[2][MAX_NUMBERS] = { 0 };
    char buffer[128];
    char* line;
    int totalPoints = 0;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        const char* ptr = strchr(buffer, ':');
        const char* ptr1= strchr(buffer, '|');
        int startIndx = (ptr - buffer) + 2;
        int num = 0;
        int indx = 0;

        for (int i = startIndx; i < sizeof(buffer) && buffer[i] != '|'; ++i) {
            int curr = buffer[i] - '0';

            if (curr >= 0 && curr <= 9) {
                num += curr;
                num *= 10;
            }

            if (buffer[i] == ' ' && i > startIndx) {
                if (num > 0) {
                    num /= 10;
                    numbers[0][indx++] = num;
                    num = 0;
                }
            }
        }

        num = 0;
        startIndx = ptr1 - buffer + 2;
        indx = 0;
        for (int i = startIndx; i < sizeof(buffer); ++i) {
            int curr = buffer[i] - '0';

            if (curr >= 0 && curr <= 9) {
                num += curr;
                num *= 10;
            }

            if (buffer[i] == ' ' || i == sizeof(buffer) - 1) {
                if (num > 0) {
                    num /= 10;
                    numbers[1][indx++] = num;
                    num = 0;
                }
            }
        }
        totalPoints += get_points(numbers);
    }

    printf("\n%s %d\n","total points: ", totalPoints);

    return 0;
}
