#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

// Function to check if page is present
bool isPresent(vector<int> &frames, int page) {
    for (int f : frames) {
        if (f == page)
            return true;
    }
    return false;
}

// FIFO Algorithm
void FIFO(vector<int> pages, int capacity) {
    vector<int> frames;
    queue<int> q;
    int faults = 0;

    cout << "\n--- FIFO Page Replacement ---\n";

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (!isPresent(frames, page)) {
            faults++;

            if (frames.size() < capacity) {
                frames.push_back(page);
                q.push(page);
            } else {
                int oldest = q.front();
                q.pop();

                // Replace oldest
                for (int j = 0; j < frames.size(); j++) {
                    if (frames[j] == oldest) {
                        frames[j] = page;
                        break;
                    }
                }
                q.push(page);
            }
        }

        // Display frames
        cout << "Step " << i + 1 << ": ";
        for (int f : frames)
            cout << f << " ";
        cout << endl;
    }

    cout << "Total Page Faults: " << faults << endl;
    cout << "Page Fault Ratio: " << fixed << setprecision(2)
         << (float)faults / pages.size() << endl;
}

// LRU Algorithm
void LRU(vector<int> pages, int capacity) {
    vector<int> frames;
    vector<int> recent(capacity, 0);
    int faults = 0, time = 0;

    cout << "\n--- LRU Page Replacement ---\n";

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        time++;

        bool found = false;

        for (int j = 0; j < frames.size(); j++) {
            if (frames[j] == page) {
                recent[j] = time;
                found = true;
                break;
            }
        }

        if (!found) {
            faults++;

            if (frames.size() < capacity) {
                frames.push_back(page);
                recent[frames.size() - 1] = time;
            } else {
                // Find least recently used
                int lru_index = 0;
                for (int j = 1; j < capacity; j++) {
                    if (recent[j] < recent[lru_index])
                        lru_index = j;
                }
                frames[lru_index] = page;
                recent[lru_index] = time;
            }
        }

        // Display frames
        cout << "Step " << i + 1 << ": ";
        for (int f : frames)
            cout << f << " ";
        cout << endl;
    }

    cout << "Total Page Faults: " << faults << endl;
    cout << "Page Fault Ratio: " << fixed << setprecision(2)
         << (float)faults / pages.size() << endl;
}

// Optimal Algorithm
void Optimal(vector<int> pages, int capacity) {
    vector<int> frames;
    int faults = 0;

    cout << "\n--- Optimal Page Replacement ---\n";

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (!isPresent(frames, page)) {
            faults++;

            if (frames.size() < capacity) {
                frames.push_back(page);
            } else {
                int farthest = i, index = -1;

                for (int j = 0; j < capacity; j++) {
                    int k;
                    for (k = i + 1; k < pages.size(); k++) {
                        if (frames[j] == pages[k]) {
                            if (k > farthest) {
                                farthest = k;
                                index = j;
                            }
                            break;
                        }
                    }

                    if (k == pages.size()) {
                        index = j;
                        break;
                    }
                }

                frames[index] = page;
            }
        }

        // Display frames
        cout << "Step " << i + 1 << ": ";
        for (int f : frames)
            cout << f << " ";
        cout << endl;
    }

    cout << "Total Page Faults: " << faults << endl;
    cout << "Page Fault Ratio: " << fixed << setprecision(2)
         << (float)faults / pages.size() << endl;
}

// Main Function with Switch
int main() {
    int n, capacity, choice;

    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter page reference string:\n";
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> capacity;

    do {
        cout << "\n===== Page Replacement Menu =====\n";
        cout << "1. FIFO\n";
        cout << "2. LRU\n";
        cout << "3. Optimal\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                FIFO(pages, capacity);
                break;
            case 2:
                LRU(pages, capacity);
                break;
            case 3:
                Optimal(pages, capacity);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}

// 1. FIFO – Sample Input
// Enter number of pages: 12
// Enter page reference string:
// 1 2 3 4 1 2 5 1 2 3 4 5
// Enter number of frames: 3
// Choice: 1

// 2. LRU – Sample Input
// Enter number of pages: 12
// Enter page reference string:
// 7 0 1 2 0 3 0 4 2 3 0 3
// Enter number of frames: 3
// Choice: 2

// 3. Optimal – Sample Input
// Enter number of pages: 12
// Enter page reference string:
// 7 0 1 2 0 3 0 4 2 3 0 3
// Enter number of frames: 3
// Choice: 3