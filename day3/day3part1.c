#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct {
	int digitsIndx;
	char digits[3];
	int position[3][2];
} PartNum;

#define MAX_SIZE 512
char schematic[MAX_SIZE][MAX_SIZE];
int xIndx, yIndx;

PartNum parts[MAX_SIZE * MAX_SIZE];
int partsIndx;

void part_add(PartNum* part, char c, int x, int y);
int part_to_number(PartNum* part);

inline bool is_symbol(int x, int y);
inline bool check_number(int x, int y);

int part_to_number(PartNum* part) {
	int n = 0;
	int base = 1;

	for (int i = part->digitsIndx - 1; i >= 0; i--) {
		char c = part->digits[i];
		n += (c - '0')*base;
		base *= 10;
	}

	return n;
}

void part_add(PartNum* part, char c, int x, int y) {
	part->digits[part->digitsIndx] = c;
	part->position[part->digitsIndx][0] = y;
	part->position[part->digitsIndx][1] = x;
	++part->digitsIndx;
}

bool is_symbol(int x, int y) {
	if (x < 0 || x >= xIndx || y < 0 || y >= yIndx)
		return false;

	char c = schematic[y][x];

	if (c == '.')
		return false;
	if (isdigit(c))
		return false;

	return true;
}

bool check_number(int x, int y) {
	if (is_symbol(x + 1, y))
        return true;
	if (is_symbol(x - 1, y))
        return true;
	if (is_symbol(x, y + 1))
        return true;
	if (is_symbol(x, y - 1))
        return true;
	if (is_symbol(x + 1, y + 1))
        return true;
	if (is_symbol(x - 1, y - 1))
        return true;
	if (is_symbol(x + 1, y - 1))
        return true;
	if (is_symbol(x - 1, y + 1))
        return true;

	return false;
}

int main() {

	char buffer[512];
	char* line;

	while (line = fgets(buffer, sizeof(buffer), stdin), line != NULL) {
		xIndx = 0;
		size_t len = strlen(line)-1;
		size_t i = 0;

		while (i < len) {
			if (isdigit(line[i])) {
				PartNum* part = &parts[partsIndx++];

				char c;
				do {
					c = line[i];
					part_add(part, c, xIndx, yIndx);
					schematic[yIndx][xIndx++] = c;
					++i;
				} while (i < len && isdigit(line[i]));
			}
			else {
				schematic[yIndx][xIndx++] = line[i++];
			}
		}

		++yIndx;
	}

	assert(xIndx < MAX_SIZE);
	assert(yIndx < MAX_SIZE);

	size_t result = 0;
	for (size_t i = 0; i < partsIndx; i++) {
		PartNum* part = &parts[i];

		int number = 0;
		for (size_t j = 0; j < part->digitsIndx; j++) {
			if (check_number(part->position[j][1], part->position[j][0])) {
				number = part_to_number(part);
				result += number;
				break;
			}
		}
	}

    printf("%zu\n", result);

	return 0;
}
