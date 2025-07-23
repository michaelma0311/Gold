#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 100000
 
int N;
int A[2*MAXN];
long long best;
int ones;
 
long long llabs(long long x)
{
	if(x<0) return -x;
	return x;
}
 
long long countInversions(int a,int b)
{
	long long t = 0;
	int n1 = 0;
	for(int i=a;i<=b;i++)
	{
		if(A[i]==1) n1++;
		else t += n1;
	}
	return t;
}
 
int tp, sgn;
 
void solve()
{
	long long inv0 = countInversions(0,N-1);
	long long inv1 = countInversions(N,2*N-1);
	long long dif = inv0 - inv1;
	best = min(best, llabs(dif));
	int n1 = 0;
	int j = N;
	int displaced = 0;
	long long cost = 0;
	for(int i=N-1;i>=0;i--) if(A[i]==tp)
	{
		dif -= sgn*(N-1-i), cost += N-1-i;
		dif += sgn*(ones - N), cost++;
		dif += sgn*n1, cost += n1;
		dif += sgn*displaced, cost += displaced;
		n1++;
		if(n1 + displaced > N) return;
		while(n1 + displaced > j-N)
		{
			if(A[j]==1-tp) j++;
			else if(j==2*N-1) return;
			else
			{
				dif += sgn*(N + n1 + displaced - j), cost += N + n1 + displaced - j;
				displaced++;
				j++;
			}
		}
		best = min(best, cost+llabs(dif));
	}
}
 
int main()
{
    freopen("balance.in","r",stdin);
	cin >> N;
	for(int i=0;i<2*N;i++)
	{
		cin >> A[i];
		ones += A[i];
	}
	best = MAXN*((long long)MAXN);
	tp = 1, sgn = 1;
	solve();
	tp = 0, sgn = -1;
	solve();
	cout << best << '\n';
}