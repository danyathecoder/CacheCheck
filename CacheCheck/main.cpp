#include <iostream>
#include <intrin.h>
#include <fstream>

#pragma intrinsic(__rdtsc)

int* block;
#define BLOCK_SIZE 32768
#define OFFSET (1024 * 1024)
#define N_MAX 20

void fillBlock(int fragment, int n)
{
	for (int i = 0; i < fragment; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j < n - 1)
			{
				block[j * OFFSET + i] = (j + 1) * OFFSET + i;
			}
			else if (i < fragment - 1)
			{
				block[j * OFFSET + i] = i + 1;
			}
			else
			{
				block[j * OFFSET + i] = 0;
			}
		}
	}
}

int main() {
	block = (int*)malloc(OFFSET * N_MAX * sizeof(int));
	long long timerArray[N_MAX];
	unsigned __int64 startTicks = 0;
	unsigned __int64 endTicks = 0;
	register volatile int index = 0;

	std::ofstream file;
	file.open("data.txt", 'w');

	for (int i = 0; i < N_MAX; i++)
	{
		fillBlock(BLOCK_SIZE / (i + 1), i + 1);

		startTicks = 0;
		endTicks = 0;
		index = 0;
		startTicks = __rdtsc();
		for (int i = 0; i < N_MAX; i++)
		{
			do
			{
				index = block[index];
			} while (index != 0);
		}

		endTicks = __rdtsc();
		int tick = int(endTicks - startTicks);
		std::cout << i + 1 << ". " << tick << "\n";
		file << int(endTicks - startTicks) << "\n";
	}

	free(block);
	file.close();
	system("python3 plotter.py");

	return 0;
}