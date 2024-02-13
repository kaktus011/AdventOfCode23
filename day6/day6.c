#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIMES 4
#define MAX_DISTANCES 4
#define BUFF_LEN 64

int main() {
    //part one
    int times[MAX_TIMES];
    int records[MAX_DISTANCES];
    char buffer[BUFF_LEN];
    int result = 1;
    char* line;
    char* token;
    
    //part two
    char time_str[100];
    char curr_record_str[100];
    int64_t time;
    int64_t curr_record;
    int wins1 = 0;
    int i, j = 0;

    //for part one
    /*
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
    */

    //for part two
    fgets(buffer, sizeof(buffer), stdin);
    for (i = 0; i < BUFF_LEN; ++i) {
        if (isdigit(buffer[i])) {
            time_str[j++] = buffer[i];
        }
    }
    time = strtoll(time_str, NULL, 10);
    
    fgets(buffer, sizeof(buffer), stdin);
    for (i = 0, j = 0; i < BUFF_LEN; ++i) {
        if (isdigit(buffer[i])) {
            curr_record_str[j++] = buffer[i];
        }
    }
    curr_record = strtoll(curr_record_str, NULL, 10);

    for (int k = 1; k < time; ++k) {
        int64_t distance = (time - k) * k;

        if (distance > curr_record)
            ++wins1;
    }

    result *= wins1;

    printf("%d \n", result);
    return 0;
}
