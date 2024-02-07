#include <stdio.h>
#include <string.h>
#include <limits.h>

int main() {
	int n;
	char buffer[128];
	size_t result = 0;

	while (scanf("%s %d:", buffer, &n) == 2) {
		int id = n;
		int r = INT_MIN;
        int g = INT_MIN;
        int b = INT_MIN;

		while (scanf("%d %s", &n, buffer) == 2) {
			char c = buffer[strlen(buffer) - 1];

			if (buffer[0] == 'r') {
				if (n > r)
					r = n;
			}
			else if (buffer[0] == 'g') {
				if (n > g)
					g = n;
			}
			else if (buffer[0] == 'b') {
				if (n > b)
					b = n;
			}

			if (c != ';' && c != ',')
				break;
		}

		size_t power = (size_t)r * (size_t)g * (size_t)b;
		result += power;
	}

	printf("%zu\n", result);

	return 0;
}
