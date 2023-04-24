#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int factorial (int n){
    if(n==1)
    {
        return 1;
    }else {
        return n*factorial(n-1);
    }
}

int digit_sum(int n){
   int sum=0;
   while(n != 0){
       sum = sum + n %10;
       n = n/10;
   }
   return sum;
}

int main()
{
    pid_t pid = fork();
    
    if(pid == 0){
        int n;
        cout<<"Enter a number : ";
        cin>>n;
        int result = factorial(n);
        cout << "Factorial of " << n << ": " << result << endl;
    }else {
        wait(NULL);
        int n ;
        cout<<"Enter a number : ";
        cin>>n;
        int result = digit_sum(n);
        cout << "Digit sum of " << n << ": " << result << endl;
    }

    return 0;
}