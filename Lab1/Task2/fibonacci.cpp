#include <iostream>
#include <sys/time.h>
using namespace std;

int main() {
    int n, firstTerm = 1, secondTerm = 1, nextTerm;
    struct timeval start_time, end_time;
    cout << "Enter number of terms: ";
    cin >> n;

    cout << "Fibonacci Series: " << firstTerm << " + " << secondTerm << " + ";
    gettimeofday(&start_time, NULL);
    //measure the execution time of the following loop
    for (int i = 1; i <= n-2; ++i) {
        nextTerm = firstTerm + secondTerm;
        cout << nextTerm << " + ";
        firstTerm = secondTerm;
        secondTerm = nextTerm;
    }
    gettimeofday(&end_time, NULL);
    cout<<endl;
    cout<<"Runtime (s): "<<(end_time.tv_sec - start_time.tv_sec)<<endl;
    cout<<"Runtime (ms):"<<(end_time.tv_usec - start_time.tv_usec)<<endl;
    return 0;
}
