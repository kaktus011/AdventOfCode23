#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIMES 4
#define MAX_DISTANCES 4
#define BUFF_LEN 128

int main() {
    int times[MAX_TIMES];
    int records[MAX_DISTANCES];
    char buffer[BUFF_LEN];
    int result = 1;
    char* line;
    char* token;

    line = fgets(buffer, sizeof(buffer), stdin);
    token = strtok(line, " ");
    token = strtok(NULL, " ");
    for (int i = 0; i < MAX_TIMES && token != NULL; ++i) {
        times[i] = strtol(token, NULL, 10);
        token = strtok(NULL, " ");
    }

    line = fgets(buffer, sizeof(buffer), stdin);
    token = strtok(line, " ");
    token = strtok(NULL, " ");
    for (int i = 0; i < MAX_TIMES && token != NULL; ++i) {
        records[i] = strtol(token, NULL, 10);
        token = strtok(NULL, " ");
    }

	for (int i = 0; i < MAX_TIMES; ++i) {
		int curr_time = times[i];
		int curr_record = records[i];
		int wins = 0;

		for (int k = 1; k < curr_time; ++k) {
			int distance = k * (curr_time - k);

			if (distance > curr_record)
				++wins;
		}

		result *= wins;
	}

    printf("%d\n", result);

    return 0;
}
