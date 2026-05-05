#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

// ---------------- FCFS ----------------
void FCFS(vector<int> req, int head) {
    int seek_time = 0;

    cout << "\nSeek Sequence: ";
    for (int i = 0; i < req.size(); i++) {
        cout << req[i] << " ";
        seek_time += abs(head - req[i]);
        head = req[i];
    }

    cout << "\nTotal Seek Time: " << seek_time << endl;
}

// ---------------- SSTF ----------------
void SSTF(vector<int> req, int head) {
    int seek_time = 0;
    int n = req.size();
    vector<bool> visited(n, false);

    cout << "\nSeek Sequence: ";

    for (int i = 0; i < n; i++) {
        int min_dist = INT_MAX, index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int dist = abs(head - req[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                    index = j;
                }
            }
        }

        visited[index] = true;
        seek_time += min_dist;
        head = req[index];
        cout << req[index] << " ";
    }

    cout << "\nTotal Seek Time: " << seek_time << endl;
}

// ---------------- SCAN ----------------
void SCAN(vector<int> req, int head, int disk_size, int direction) {
    int seek_time = 0;
    vector<int> left, right;

    for (int i = 0; i < req.size(); i++) {
        if (req[i] < head)
            left.push_back(req[i]);
        else
            right.push_back(req[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << "\nSeek Sequence: ";

    if (direction == 1) { // Right
        for (int i = 0; i < right.size(); i++) {
            cout << right[i] << " ";
            seek_time += abs(head - right[i]);
            head = right[i];
        }

        // Move to end
        seek_time += abs(head - (disk_size - 1));
        head = disk_size - 1;

        for (int i = left.size() - 1; i >= 0; i--) {
            cout << left[i] << " ";
            seek_time += abs(head - left[i]);
            head = left[i];
        }
    } else { // Left
        for (int i = left.size() - 1; i >= 0; i--) {
            cout << left[i] << " ";
            seek_time += abs(head - left[i]);
            head = left[i];
        }

        // Move to start
        seek_time += abs(head - 0);
        head = 0;

        for (int i = 0; i < right.size(); i++) {
            cout << right[i] << " ";
            seek_time += abs(head - right[i]);
            head = right[i];
        }
    }

    cout << "\nTotal Seek Time: " << seek_time << endl;
}

// ---------------- C-SCAN ----------------
void CSCAN(vector<int> req, int head, int disk_size) {
    int seek_time = 0;
    vector<int> left, right;

    for (int i = 0; i < req.size(); i++) {
        if (req[i] < head)
            left.push_back(req[i]);
        else
            right.push_back(req[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << "\nSeek Sequence: ";

    // Move right first
    for (int i = 0; i < right.size(); i++) {
        cout << right[i] << " ";
        seek_time += abs(head - right[i]);
        head = right[i];
    }

    // Move to end
    seek_time += abs(head - (disk_size - 1));
    head = disk_size - 1;

    // Jump to start
    seek_time += (disk_size - 1);
    head = 0;

    // Service left
    for (int i = 0; i < left.size(); i++) {
        cout << left[i] << " ";
        seek_time += abs(head - left[i]);
        head = left[i];
    }

    cout << "\nTotal Seek Time: " << seek_time << endl;
}

// ---------------- MAIN ----------------
int main() {
    int n, head, choice, disk_size, direction;

    cout << "Enter number of requests: ";
    cin >> n;

    vector<int> req(n);

    cout << "Enter request sequence:\n";
    for (int i = 0; i < n; i++)
        cin >> req[i];

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "\nDisk Scheduling Algorithms:\n";
    cout << "1. FCFS\n2. SSTF\n3. SCAN\n4. C-SCAN\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            FCFS(req, head);
            break;

        case 2:
            SSTF(req, head);
            break;

        case 3:
            cout << "Enter disk size: ";
            cin >> disk_size;

            cout << "Enter direction (0 = Left, 1 = Right): ";
            cin >> direction;

            SCAN(req, head, disk_size, direction);
            break;

        case 4:
            cout << "Enter disk size: ";
            cin >> disk_size;

            CSCAN(req, head, disk_size);
            break;

        default:
            cout << "Invalid Choice!" << endl;
    }

    return 0;
}

// 1. FCFS (First Come First Serve)
// Sample Input:
// Enter number of requests: 8
// Enter request sequence:
// 98 183 37 122 14 124 65 67
// Enter initial head position: 53
// Enter your choice: 1

// 2. SSTF (Shortest Seek Time First)

// Sample Input:

// Enter number of requests: 8
// Enter request sequence:
// 98 183 37 122 14 124 65 67
// Enter initial head position: 53
// Enter your choice: 2

// 3. SCAN (Elevator Algorithm)

// Sample Input:

// Enter number of requests: 8
// Enter request sequence:
// 98 183 37 122 14 124 65 67
// Enter initial head position: 53
// Enter your choice: 3
// Enter disk size: 200

// Enter direction: 0

// 4. C-SCAN (Circular SCAN)

// Sample Input:

// Enter number of requests: 8
// Enter request sequence:
// 98 183 37 122 14 124 65 67
// Enter initial head position: 53
// Enter your choice: 4
// Enter disk size: 200