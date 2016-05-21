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

mat mass(int n)
{
    mat A(n,n);
    A(0,0) = 2.0/3.0;
    for(int i=1;i<n;i++)
    { 
        A(i,i) =   2.0/3.0;
        A(i-1,i) = 1.0/6.0;
        A(i,i-1) = 1.0/6.0;
    }
    return A;
}


mat solvePoisson(int elems, mat f)
{
    mat A = stiffness(elems-1);
    mat x = solve(A,f);
    return x;
}

mat solveHeatEqn(mat g, double sElems, double tElems)
{
    double tau = 10/tElems;
    mat S = stiffness(sElems-1);
    mat M = mass(sElems-1);
    mat solution(sElems-1,tElems+1);
    mat U_k(sElems-1,1);
    U_k  = g;
    solution.col(0) = g;
    
    mat multiplier = inv(M+S*tau/2)*(M-S*tau/2); //Crank Nicolson Method
    for(int i = 1;i<tElems+1;i++)
    {
        U_k = multiplier*U_k;
        solution.col(i) = U_k;
    }
    return solution.col(tElems);
}




int main()
{
    mat g(10,1); for(int i=0;i<10;i++){g(i,0) = i*100;}
    //cout << stiffness(10);
    //cout << solvePoisson(11,g);
    cout << solveHeatEqn(g,11,1000000);
    return 0;
}

