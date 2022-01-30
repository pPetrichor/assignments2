#include"fibonacci.h"
int fibonacci(int n)
{
	if (n == 0 ) return 0;
	else if (n == 1) return 1;
	else 
	{
		int fib_0 = 0, fib_1 = 1;
		for(int i=2;i<=n;++i)
		{
			int temp = fib_0 + fib_1;
			fib_0 = fib_1;
			fib_1 = temp;
		}
		return fib_1;
	}
}
