#include<vector>
#include<iostream>

using namespace std;

//solve -laplace(u) = f on [0,1] with finite element method
//h = mesh size = 1/n where n is the number of elements
//boundary condition u(0) = u(1) = 0

vector<double> solve(double h, vector<double> f)
{
    int elems = (int)h;
    int n = elems-1;   //number of basis functions
    vector<vector<double>> A;
    A.resize(n,vector<double>(n,0));
    vector<double> b(n,0);
    
    double n2 = n*n
    A[0][0] = 2*n2;
    A[0][1] = -1*n2;
    A[1][0] = -1*n2;
    A[n-1][n-1] = 2*n2;
    A[n-1][n-2] = -1*n2;
    A[n-2][n-1] = -1*n2;
    
    for(int i =1;i<n-1;i++)
    {
        for(int j=1;j<n-1;j++)
        {
            if(i == j){A[i][j] = 2*n2;}
            if(abs(i-j) == 1){A[i][j] = -1*n2;}
        }
    }
    for(int i=0;i<n;i++)
    {
        b[i] = f[i+1]/n;   //int f*phi_n ~= f(x_n)/n
    }
    vector<double> x = b/A;
    return x;
}
