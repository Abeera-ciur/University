
#include <iostream>
#include <string>
using namespace std;

const int MAX = 6;

class Patient {
public:
    string name;
    int severity;
    int arrivalOrder;

    Patient() {
        name = "";
        severity = 0;
        arrivalOrder = 0;
    }

    Patient(string n, int s, int a) {
        name = n;
        severity = s;
        arrivalOrder = a;
    }

    void display() {
        cout << name << " | Severity: " << severity
             << " | Arrival: " << arrivalOrder << endl;
    }

    ~Patient() {
    }
};

Patient queue[MAX];
int count = 0;

void enqueue(Patient p) {
    if (count == MAX) {
        cout << "Queue is full.\n";
        return;
    }

    queue[count] = p;
    count++;
}

void dequeue() {
    if (count == 0) {
        cout << "Queue is empty.\n";
        return;
    }

    int highest = 0;

    for (int i = 1; i < count; i++) {
        if (queue[i].severity > queue[highest].severity) {
            highest = i;
        }
        else if (queue[i].severity == queue[highest].severity &&
                 queue[i].arrivalOrder < queue[highest].arrivalOrder) {
            highest = i;
        }
    }

    queue[highest].display();

    for (int i = highest; i < count - 1; i++) {
        queue[i] = queue[i + 1];
    }

    count--;
}

void processPatients() {
    enqueue(Patient("Ali", 5, 1));
    enqueue(Patient("Sara", 9, 2));
    enqueue(Patient("Ahmed", 7, 3));
    enqueue(Patient("Ayesha", 9, 4));
    enqueue(Patient("Usman", 3, 5));
    enqueue(Patient("Zara", 7, 6));

    cout << "\nPatient Treatment Order:\n";

    while (count > 0) {
        dequeue();
    }
}

int main() {
    processPatients();
    return 0;
}
