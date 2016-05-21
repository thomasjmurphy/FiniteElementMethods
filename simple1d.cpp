#include<vector>
#include<iostream>
#include<armadillo>

using namespace std;
using namespace arma;
//solve -laplace(u) = f on [0,1] with finite element method
//h = mesh size = 1/n where n is the number of elements
//boundary condition u(0) = u(1) = 0


mat stiffness(int n)
{
    mat A(n,n);
    A(0,0) = 2.0*n;
    for(int i=1;i<n;i++)
    {
        A(i,i) =   2.0*n;
        A(i-1,i) = -1.0*n;
        A(i,i-1) = -1.0*n;
    }
    return A;
}

mat solvePoisson(int elems, mat f)
{
    mat A = stiffness(elems-1);
    mat x = solve(A,f);
    return x;
}
