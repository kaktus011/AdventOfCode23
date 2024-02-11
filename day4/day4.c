#include <stdio.h>
#include <string.h>

#define MAX_NUMBERS 25
#define MAX_CARDS 220

//part one
int get_points(int numbers[2][MAX_NUMBERS]);
//part two
void process_card(int ncard, int (*cards)[1], int numbers[2][MAX_NUMBERS]);
int get_total_cards(int cards[MAX_CARDS][1]);
int matches = 0;

int get_points(int numbers[2][MAX_NUMBERS]) {
    int points = 0;
    matches = 0;

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
                matches++;
            }
            else if (numbers[0][i] == numbers[1][winning]) {
                points *= 2;
                matches++;
            }
        }
    }

    return points;
}

void process_card(int ncard, int (*cards)[1], int numbers[2][MAX_NUMBERS]) {
    for (int i = ncard + 1; i <= matches + ncard; i++) {
        ++cards[i][0];
    }
}

int get_total_cards(int cards[MAX_CARDS][1]) {
    int total = 0;

    for (int i = 0; i < MAX_CARDS; i++) {
        total += cards[i][0] + 1;
    }

    return total;
}

int main () {
    int numbers[2][MAX_NUMBERS] = { 0 };
    int cards[MAX_CARDS][1] = { 0 };

    char buffer[128];
    char* line;
    int totalPoints = 0;
    int ncard = -1;

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
        process_card(++ncard, cards, numbers);

        int copies = cards[ncard][0];
        while (copies > 0) {
            process_card(ncard, cards, numbers);
            --copies;
        }
    }

    printf("\n%s %d\n","Total points: ", totalPoints);
    int totalCards = get_total_cards(cards);
    printf("%s %d\n", "Total cards: ", totalCards);

    return 0;
}
