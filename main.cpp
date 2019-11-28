#include "lab1.h"

int main() 
{
	std::cout << "function: cos(x)th(x)" << "\tinterval: [ 7; 11 ]\n\n";
	double a1 = 7, b1 = 11; // Начало и конец интервала
	// Оптимальный пассивный поиск
	std::cout << "Optimum passive search:\n";
	passive_search(a1, b1);
	// Метод Фибоначчи
	fibonacci_method(a1, b1);
	return 0;
}
