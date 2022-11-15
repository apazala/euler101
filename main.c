#include <inttypes.h>
#include <stdio.h>


int64_t pn[12][12];

int64_t values[12];
int64_t coeffs[11] = {1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1};
void generatevalues(int n)
{
	for (int i = 1; i <= n + 1; i++)
	{
		int64_t value = coeffs[n];
		//Ruffini
		for (int j = n - 1; j >= 0; j--)
		{
			value = value*i + coeffs[j];
		}

		values[i] = (int64_t)value;
	}

}

void init(int n)
{

	generatevalues(n);

	int64_t vaux;
	for (int i = 1; i <= n + 1; i++)
	{
		pn[i][1] = 1;
		for (int j = 2; j <= i; j++)
		{
			pn[i][j] = pn[i][j - 1] * (int64_t)(i - j + 1);
		}
	}
}

int64_t newtoncoeffs[12];

int64_t solve(int n)
{
	int64_t res = 0;
	newtoncoeffs[1] = values[1];
	int runlength = 0;
	for (int i = 1; i <= n; i++)
	{
		int64_t val = 0;
		int k = i + 1;
		for (int j = 1; j <= k; j++)
		{
			val += pn[k][j] * newtoncoeffs[j];
		}

		if (val == values[k])
		{
			runlength++;
		}
		else
		{
			for (int m = 0; m <= runlength; m++)
				printf("%" PRId64 " ", val);
			runlength = 0;
			newtoncoeffs[k] = (values[k] - val)/pn[k][k];
			res += val;
		}

	}

	//Potentially we could reach here without generating exactly N FITs 
	printf("\n");

	return res;
}

int main()
{

	int n = 10;

	init(n);

	int64_t res = solve(n);

	printf("%" PRId64 "\n", res);

	return 0;
}
