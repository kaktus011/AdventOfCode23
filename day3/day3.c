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

int currParts[8] = { 0 };

//part one
void part_add(PartNum* part, char c, int x, int y);
int part_to_number(PartNum* part);

inline bool is_symbol(int x, int y);
inline bool check_number(int x, int y);

//part two
int get_ratio_if_valid(int x, int y);
int lookup_part(int x, int y);

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

int lookup_part(int x, int y) {
	for (int i = 0; i < partsIndx; i++) {
		PartNum* part = &parts[i];
		for (int j = 0; j < part->digitsIndx; j++) {
			int py = part->position[j][0];
			int px = part->position[j][1];

			if (x == px && y == py) {
				return i;
			}
		}
	}

	return -1;
}

bool has_id(int* ids, int len, int id) {
	for (int i = 0; i < len; i++) {
		if (ids[i] == id) {
			return true;
		}
	}
	return false;
}

int get_ratio_if_valid(int x, int y) {
	int npart_ids = 0;
	int part_ids[8] = { 0 };

	int offsets[8][2] = {
		{ 1,  0},
		{-1,  0},

		{ 0,  1},
		{ 0, -1},

		{ 1,  1},
		{-1, -1},

		{ 1, -1},
		{-1,  1},
	};

	for (int i = 0; i < 8; i++) {
		int xo = offsets[i][0];
		int yo = offsets[i][1];

		int id;
		if (id = lookup_part(x + xo, y + yo), id >= 0 &&
			!has_id(part_ids, npart_ids, id)) {
			part_ids[npart_ids++] = id;
		}
	}

	if (npart_ids == 2) {
		int ratio = part_to_number(&parts[part_ids[0]]) *
			part_to_number(&parts[part_ids[1]]);
		return ratio;
	}

	return 0;
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

	size_t result1 = 0;
	for (size_t i = 0; i < partsIndx; i++) {
		PartNum* part = &parts[i];

		int number = 0;
		for (size_t j = 0; j < part->digitsIndx; j++) {
			if (check_number(part->position[j][1], part->position[j][0])) {
				number = part_to_number(part);
				result1 += number;
				break;
			}
		}
	}

    printf("%zu\n", result1);


    size_t result2 = 0;
    for (int y = 0; y < yIndx; y++ ) {
        for (int x = 0; x < xIndx; x++) {
            char c = schematic[y][x];
            if (c == '*') {
                result2 += get_ratio_if_valid(x, y);
            }
        }
    }

    printf("%zu\n", result2);

	return 0;
}
