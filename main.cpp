#include <iostream>
#include <ctime>
#include <cstdlib>
#include <utility>
#include "Matrix.h"

int main()
{
    using std::cout;
    using std::endl;
    
    int factor = 2;
    
    srand(time(NULL));
    
    try
    {
        Matrix<int> m1(2, 4);
        Matrix<int> m2(4, 2);
        Matrix<int> m3(m1);
        
        for(std::size_t i = 0; i < m1.length(0); i++)
        {
            for(std::size_t j = 0; j < m1.length(1); j++)
            {
                m1(i, j) = rand()%10;
                m2(j, i) = rand()%10;
            }
        }
        
        cout << "Matrix A: " << endl << m1 << endl;
        cout << "Matrix B: " << endl << m2 << endl;
        cout << "Matrix A * B: " << endl << m1 * m2 << endl << endl;
        cout << "Matrix A *= B: " << endl << (m1 *= m2) << endl << endl;

        Matrix<int> m4(m1);
        cout << "Matrix A * " << factor << ": " << endl << factor * m1 << endl;
        cout << "Transposed Matrix A: " << endl << m1.transpose() << endl;

        m1 = m2;
        cout << "Matrix A = B: " << endl << m1 << endl;
        
        m1 = std::move(m2);    
        cout << "Matrix A after moving from B: " << endl << m1 << endl;
    }
    catch(std::exception ex)
    {
        cout << ex.what() << endl;
    }

    return 0;
}
