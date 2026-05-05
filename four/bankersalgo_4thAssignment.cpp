#include <iostream>

using namespace std;

int main() {
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resources: ";
    cin >> m;

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m];

    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> alloc[i][j];
        }
    }

    cout << "\nEnter Maximum Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    cout << "\nEnter Available Resources:\n";
    for (int i = 0; i < m; i++) {
        cin >> avail[i];
    }

    // Calculate Need Matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    bool finish[n] = {false};
    int safeSeq[n];
    int work[m];

    // Copy available to work
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0;

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canExecute = true;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "\nSystem is NOT in a safe state (Deadlock possible)\n";
            return 0;
        }
    }

    cout << "\nSystem is in SAFE state.\nSafe sequence is: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safeSeq[i];
        if (i != n - 1) cout << " -> ";
    }
    cout << endl;

    return 0;
}

/*
PS C:\Users\Harsh\Desktop\Shortcuts\OS & OSL> cd "c:\Users\Harsh\Desktop\Shortcuts\OS & OSL\" ; if ($?) { g++ bankersalgo.cpp -o bankersalgo } ; if ($?) { .\bankersalgo }
Enter number of processes: 5
Enter number of resources: 3

Enter Allocation Matrix:
0 1 0 2 0 0 3 0 2 2 1 1 0 0 2

Enter Maximum Matrix:
7 5 3 3 2 2 9 0 2 2 2 2 4 3 3

Enter Available Resources:
3 2 2


System is NOT in a safe state (Deadlock possible)
PS C:\Users\Harsh\Desktop\Shortcuts\OS & OSL>

for System is NOT in a safe state (Deadlock possible) 
Enter Available Resources:
3 3 2
*/