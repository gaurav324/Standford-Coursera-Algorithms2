/**
 * Schedule a list of jobs such a way that weighted completion time of all jobs is min.
 *
 * Input Priority(i) and Weight(i)
 *
 * Analysis of algorithms - II (Tim Roughgarden, Stanford)
 *
 * Author: Gaurav Nanda
 */

#include <iostream>
#include <queue>

using namespace std;
int main() {
    // Read in the file.
    int total_jobs;
    cin >> total_jobs;

    int i=0;

    // Metric one is being greedy on W/L. This is the correct greedy criterion.
    priority_queue<pair<double, pair<int, int>>> metric_one;

    // Metric two is being greedy on W-L
    priority_queue<pair<int, pair<int, int>>> metric_two;
    
    int a,b;
    while(cin >> a >> b) {
        pair<int, int> wl;
        wl.first = a;
        wl.second = b;

        pair<double, pair<int, int>> m1;
        m1.first = a * 1.0/b;
        m1.second = wl;
        metric_one.push(m1);

        pair<int, pair<int, int>> m2;
        m2.first = a-b;
        m2.second = wl;
        metric_two.push(m2);
    }

    int ct = 0;
    double weighted_sum_m1 = 0;
    while (!metric_one.empty()) {
        auto popped = metric_one.top();
        weighted_sum_m1 += popped.second.first * (popped.second.second + ct);
        ct += popped.second.second;
        metric_one.pop();
    }

    ct = 0;
    double weighted_sum_m2 = 0;
    while (!metric_two.empty()) {
        auto popped = metric_two.top();
        weighted_sum_m2 += popped.second.first * (popped.second.second + ct);
        ct += popped.second.second;
        metric_two.pop();
    }
   
    cout.precision(15);
    cout << "Weighted sum using W/L metric: " << std::fixed << weighted_sum_m1 << endl;
    cout << "Weighted sum using W-L metric: " << std::fixed << weighted_sum_m2 << endl;
}
