//Greedy Search Algorithm implementation in C++ for the Job Scheduling Problem, where each job takes 1 unit of time and must be done before its deadline to earn a profit.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a job
struct Job {
    char id;
    int deadline;
    int profit;
};

// Comparator to sort jobs by descending profit
bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

// Function to schedule jobs to maximize profit
void jobScheduling(vector<Job>& jobs) {
    // Sort jobs in decreasing order of profit
    sort(jobs.begin(), jobs.end(), compare);

    int n = jobs.size();

    // Find max deadline to determine number of time slots
    int maxDeadline = 0;
    for (auto job : jobs)
        maxDeadline = max(maxDeadline, job.deadline);

    // Track used time slots
    vector<bool> slot(maxDeadline + 1, false); 
    // track scheduled job ids
    vector<char> result(maxDeadline + 1);

    int totalProfit = 0;

    for (auto job : jobs) {
        // Try to schedule job at latest possible free slot before deadline
        for (int t = job.deadline; t > 0; t--) {
            if (!slot[t]) {
                slot[t] = true;
                result[t] = job.id;
                totalProfit += job.profit;
                break;
            }
        }
    }

    // Output results
    cout << "Scheduled Jobs: ";
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i]) cout << result[i] << " ";
    }
    cout << "\nTotal Profit: " << totalProfit << endl;
}

// Main function
int main() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<Job> jobs(n);

    cout << "Enter job details (id deadline profit):\n";
    for (int i = 0; i < n; i++) {
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
    }

    jobScheduling(jobs);
    return 0;
}

// sample input
// Enter number of jobs: 5
// Enter job details (id deadline profit):
// A 2 100
// B 1 19
// C 2 27
// D 1 25
// E 3 15
