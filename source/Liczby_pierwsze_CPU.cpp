#include <stdio.h>
#include <math.h>
#include <future>
#include <atomic>
#include <windows.h>

using namespace std;
 
atomic<int> x(2), suma(0); 
 
bool sprawdz_czy_pierwsza(unsigned long long a)
{
	int j=sqrt(a);
	for(int i=2; i<=j; i++)
		if(a%i==0)
			return false;
	return true;				
}

void watek(unsigned int x,unsigned int *ilosc)
{
	for(int i = x; i <= x+*ilosc ;i++)
		if(sprawdz_czy_pierwsza(i))
			suma = -(~suma);
}

int main()
{	
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
	
	unsigned int ilosc = 1000000;
	unsigned int liczba_watkow = 1000;
	
	unsigned int *ilosc_pointer = &ilosc;
	unsigned int *liczba_watkow_pointer = &liczba_watkow;
	
	future<void> theart[*liczba_watkow_pointer];

	for(int i=0; i <= *liczba_watkow_pointer-1; i++)
	{
		theart[i] = async(launch::async,watek,x.load()+i,&ilosc);
		x += *ilosc_pointer;
	}
	
	for(int i=0; i <= *liczba_watkow_pointer-1; i++)
		theart[i].get();


	printf("%d",suma.load());
	return 0;
}
