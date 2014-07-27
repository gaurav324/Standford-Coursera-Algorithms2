/*
In this programming problem and the next you'll code up the knapsack algorithm from lecture. Let's start with a warm-up. Download the text file here. This file describes a knapsack instance, and it has the following format:
[knapsack_size][number_of_items]
[value_1] [weight_1]
[value_2] [weight_2]
...
For example, the third line of the file is "50074 659", indicating that the second item has value 50074 and size 659, respectively.
You can assume that all numbers are positive. You should assume that item weights and the knapsack capacity are integers.
*/
#include <iostream>

using namespace std;
int main() { 
    int W, N;
    cin >> W; cin >> N;

    int v[N], w[N];

    for (int i=0; i < N; ++i) {
        cin >> v[i];
        cin >> w[i];
    }
    
    int k[W+1][N+1];
    for (int i=0; i <=W; ++i) {
        for (int j=0; j<=N; ++j) {
            k[i][j] = 0;
        }
    }
   
    for (int i=1; i <= W; ++i) {
        for (int j=1; j <= N; ++j) {
            if(w[j-1] > i) {
                k[i][j] = k[i][j-1];
            } else {
                // Notice the indices of w and v, those are j-1,
                // which basically means that we are j(1,N) represents
                // the jth element and jth element in array would 
                // be found at j-1 index.
                k[i][j] = max(k[i][j-1], k[i-w[j-1]][j-1] + v[j-1]);
            }
        }
    }

    cout << "Total Value: " << k[W][N] << endl;
}
