#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Process {
    int pid, at, bt, pr;
    int wt, tat, rt;
};

// Display results
void display(vector<Process> p) {
    float totalWT = 0, totalTAT = 0;

    cout << "\nPID\tAT\tBT\tWT\tTAT\n";
    for (auto &i : p) {
        cout << i.pid << "\t" << i.at << "\t" << i.bt
             << "\t" << i.wt << "\t" << i.tat << endl;
        totalWT += i.wt;
        totalTAT += i.tat;
    }

    cout << "\nAverage WT = " << totalWT / p.size();
    cout << "\nAverage TAT = " << totalTAT / p.size() << endl;
}

// ---------------- FCFS ----------------
void FCFS(vector<Process> p) {
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    int time = 0;

    for (int i = 0; i < p.size(); i++) {
        if (time < p[i].at)
            time = p[i].at;

        p[i].wt = time - p[i].at;
        time += p[i].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }

    cout << "\n--- FCFS Scheduling ---\n";
    display(p);
}

// ---------------- SJF ----------------
void SJF(vector<Process> p) {
    int n = p.size();
    vector<bool> done(n, false);
    int completed = 0, time = 0;

    while (completed < n) {
        int idx = -1, minBT = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].wt = time - p[idx].at;
        time += p[idx].bt;
        p[idx].tat = p[idx].wt + p[idx].bt;

        done[idx] = true;
        completed++;
    }

    cout << "\n--- SJF Scheduling ---\n";
    display(p);
}

// ---------------- Priority ----------------
void Priority(vector<Process> p) {
    int n = p.size();
    vector<bool> done(n, false);
    int completed = 0, time = 0;

    while (completed < n) {
        int idx = -1, bestPr = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].pr < bestPr) {
                bestPr = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].wt = time - p[idx].at;
        time += p[idx].bt;
        p[idx].tat = p[idx].wt + p[idx].bt;

        done[idx] = true;
        completed++;
    }

    cout << "\n--- Priority Scheduling ---\n";
    display(p);
}

// ---------------- Round Robin ----------------
void RoundRobin(vector<Process> p, int tq) {
    int n = p.size();
    queue<int> q;
    vector<bool> inQueue(n, false);

    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    int time = 0, completed = 0;
    q.push(0);
    inQueue[0] = true;

    while (!q.empty()) {
        int i = q.front();
        q.pop();

        if (p[i].rt > tq) {
            time += tq;
            p[i].rt -= tq;
        } else {
            time += p[i].rt;
            p[i].wt = time - p[i].at - p[i].bt;
            p[i].rt = 0;
            completed++;
        }

        for (int j = 0; j < n; j++) {
            if (!inQueue[j] && p[j].at <= time) {
                q.push(j);
                inQueue[j] = true;
            }
        }

        if (p[i].rt > 0)
            q.push(i);
    }

    for (int i = 0; i < n; i++)
        p[i].tat = p[i].wt + p[i].bt;

    cout << "\n--- Round Robin Scheduling ---\n";
    display(p);
}

// ---------------- MAIN ----------------
int main() {
    int n, choice;

    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cin >> p[i].at >> p[i].bt;
    }

    cout << "\n1. FCFS\n2. SJF\n3. Priority\n4. Round Robin\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            FCFS(p);
            break;

        case 2:
            SJF(p);
            break;

        case 3:
            cout << "Enter Priority for each process:\n";
            for (int i = 0; i < n; i++)
                cin >> p[i].pr;
            Priority(p);
            break;

        case 4: {
            int tq;
            cout << "Enter Time Quantum: ";
            cin >> tq;
            RoundRobin(p, tq);
            break;
        }

        default:
            cout << "Invalid Choice!\n";
    }

    return 0;
}

// Enter number of processes: 4
// Enter AT and BT for each process:
// 0 5 
// 1 3
// 2 8 
// 3 6