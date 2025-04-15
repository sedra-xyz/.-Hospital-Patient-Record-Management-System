#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //needed for the bonus task
using namespace std;

struct Patient {
    int ID;
    string name;
    int age;
    string condition;
    Patient* next; 
    
    Patient(int Pid, string Pname, int Page, string Pcondition) {
        ID = Pid;
        name = Pname;
        age = Page;
        condition = Pcondition;
        next = nullptr;
    }
};

class PatientList {
private:
    Patient* head;

public:
    PatientList() {
        head = nullptr;
    }


    void addPatient(int id, string name, int age, string condition) {
        Patient* newPatient = new Patient(id, name, age, condition);
        if (!head) {
            head = newPatient;
        } else {
            Patient* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newPatient;
        }
        cout << "Patient added successfully.\n";
    }

    
    void displayPatients() {
        if (!head) {
            cout << "No patients in the system.\n";
            return;
        }
        Patient* temp = head;
        cout << "\n--- Patient Records ---\n";
        while (temp) {
            cout << "ID: " << temp->ID << ", Name: " << temp->name
                 << ", Age: " << temp->age << ", Condition: " << temp->condition << "\n";
            temp = temp->next;
        }
    }

    ~PatientList() {
        Patient* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};


struct EmergencyPatient {
    int id;
    string name;
    string condition;
    EmergencyPatient* next;

    EmergencyPatient(int pid, string pname, string pcondition) {
        id = pid;
        name = pname;
        condition = pcondition;
        next = nullptr;
    }
};

class EmergencyRoomQueue {
private:
    EmergencyPatient* front;
    EmergencyPatient* rear;

public:
    EmergencyRoomQueue() {
        front = rear = nullptr;
    }

    
    void enqueue(int id, string name, string condition) {
        EmergencyPatient* newPatient = new EmergencyPatient(id, name, condition);
        if (!rear) {
            front = rear = newPatient;
        } else {
            rear->next = newPatient;
            rear = newPatient;
        }
        cout << "Emergency patient added to queue.\n";
    }

    
    void dequeue() {
        if (!front) {
            cout << "No emergency patients in queue.\n";
            return;
        }
        EmergencyPatient* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        cout << "Emergency patient treated and removed: " << temp->name << "\n";
        delete temp;
    }

    
    void displayQueue() {
        if (!front) {
            cout << "Emergency queue is empty.\n";
            return;
        }
        EmergencyPatient* temp = front;
        cout << "\n--- Emergency Room Queue ---\n";
        while (temp) {
            cout << "ID: " << temp->id << ", Name: " << temp->name
                 << ", Condition: " << temp->condition << "\n";
            temp = temp->next;
        }
    }

   
    ~EmergencyRoomQueue() {
        EmergencyPatient* temp;
        while (front) {
            temp = front;
            front = front->next;
            delete temp;
        }
    }
};


struct Treatment {
    int patientId;
    string treatmentDetails;
    Treatment* next;

    Treatment(int id, string details) {
        patientId = id;
        treatmentDetails = details;
        next = nullptr;
    }
};

class TreatmentStack {
private:
    Treatment* top;

public:
    TreatmentStack() {
        top = nullptr;
    }

    
    void push(int id, string details) {
        Treatment* newTreatment = new Treatment(id, details);
        newTreatment->next = top;
        top = newTreatment;
        cout << "Treatment added to history.\n";
    }

    
    void pop() {
        if (!top) {
            cout << "No treatments to undo.\n";
            return;
        }
        cout << "Undoing treatment for Patient ID " << top->patientId
             << ": " << top->treatmentDetails << "\n";
        Treatment* temp = top;
        top = top->next;
        delete temp;
    }

 
    void display() {
        if (!top) {
            cout << "No treatment history.\n";
            return;
        }
        Treatment* temp = top;
        cout << "\n--- Treatment History ---\n";
        while (temp) {
            cout << "Patient ID: " << temp->patientId << ", Treatment: " << temp->treatmentDetails << "\n";
            temp = temp->next;
        }
    }

    

    ~TreatmentStack() {
        Treatment* temp;
        while (top) {
            temp = top;
            top = top->next;
            delete temp;
        }
    }
};


struct CriticalPatient {
    int id;
    string name;
    int severity;  
};

class CriticalQueue {
private:
    vector<CriticalPatient> heap;

    
    static bool compare(CriticalPatient a, CriticalPatient b) {
        return a.severity > b.severity; 
    }

public:
  
    void addCriticalPatient(int id, string name, int severity) {
        CriticalPatient p = {id, name, severity};
        heap.push_back(p);
        push_heap(heap.begin(), heap.end(), compare);
        cout << "Critical patient added with severity " << severity << ".\n";
    }

    
    void treatCriticalPatient() {
        if (heap.empty()) {
            cout << "No critical patients to treat.\n";
            return;
        }
        pop_heap(heap.begin(), heap.end(), compare);
        CriticalPatient p = heap.back();
        heap.pop_back();
        cout << "Treated critical patient: " << p.name << " (Severity: " << p.severity << ")\n";
    }

    
    void displayCriticalQueue() {
        if (heap.empty()) {
            cout << "No critical patients.\n";
            return;
        }
        cout << "\n--- Critical Patient Queue ---\n";
        for (auto& p : heap) {
            cout << "ID: " << p.id << ", Name: " << p.name << ", Severity: " << p.severity << "\n";
        }
    }
};

int main() {
    PatientList patientList;
    EmergencyRoomQueue emergencyQueue;
    TreatmentStack treatmentStack;
    CriticalQueue criticalQueue;

    int choice;

    while (true) {
        cout << "\n=========================\n";
        cout << " Hospital Management Menu\n";
        cout << "=========================\n";
        cout << "1. Add New Patient Record\n";
        cout << "2. Display All Patients\n";
        cout << "3. Add Emergency Patient\n";
        cout << "4. Treat Emergency Patient\n";
        cout << "5. Show Emergency Queue\n";
        cout << "6. Add Treatment to History\n";
        cout << "7. Undo Last Treatment\n";
        cout << "8. Show Treatment History\n";
        cout << "9. Add Critical Patient (with Severity)\n";
        cout << "10. Treat Critical Patient\n";
        cout << "11. Show Critical Patient Queue\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        if (choice == 0) {
            cout << "Exiting program.\n";
            break;
        }

        int id, age, severity;
        string name, condition, treatment;

        switch (choice) {
            case 1:
                cout << "Enter Patient ID: ";
                cin >> id;
                cin.ignore(); 
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cin.ignore();  
                cout << "Enter Condition: ";
                getline(cin, condition);
                patientList.addPatient(id, name, age, condition);
                break;

            case 2:
                patientList.displayPatients();
                break;

            case 3:
                cout << "Enter Patient ID: ";
                cin >> id;
                cin.ignore(); 
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Condition: ";
                getline(cin, condition);
                emergencyQueue.enqueue(id, name, condition);
                break;

            case 4:
                emergencyQueue.dequeue();
                break;

            case 5:
                emergencyQueue.displayQueue();
                break;

            case 6:
                cout << "Enter Patient ID: ";
                cin >> id;
                cin.ignore(); 
                cout << "Enter Treatment Details: ";
                getline(cin, treatment);
                treatmentStack.push(id, treatment);
                break;

            case 7:
                treatmentStack.pop();
                break;

            case 8:
                treatmentStack.display();
                break;

            case 9:
                cout << "Enter Patient ID: ";
                cin >> id;
                cin.ignore();  
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Severity (1=most critical): ";
                cin >> severity;
                criticalQueue.addCriticalPatient(id, name, severity);
                break;

            case 10:
                criticalQueue.treatCriticalPatient();
                break;

            case 11:
                criticalQueue.displayCriticalQueue();
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
