#include <iostream>
#include <string>
using namespace std;

class patient {
    public:
        int p_id, age;
        string name, address;
        static int totalpatients;

        patient() {
            p_id = 0;
            age = 0;
            name = "";
            address = "";
        }

        patient(int id, string n, int a, string addr) {
            p_id = id;
            name = n;
            age = a;
            address = addr;
            totalpatients++;
        }

        patient(const patient &p) {
            this->p_id = p.p_id;
            this->name = p.name;
            this->age = p.age;
            this->address = p.address;
        }

        ~patient() {
            cout << "Patient with Id " << p_id << " has been deleted" << endl;
        }

        virtual void input() {}
        friend void display(const patient &p);
};

int patient::totalpatients = 0;

void display(const patient &p) {
    cout << "\n\n\tPatient Details\n";
    cout << "ID: " << p.p_id << endl;
    cout << "Name: " << p.name << endl;
    cout << "Age: " << p.age << endl;
    cout << "Address: " << p.address << endl;
}

class details : public patient {
    public:
        void input() override {
            cout << "Enter Patient ID: ";
            cin >> p_id;
            cin.ignore(); 
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            while (age <= 0) {
                cout << "Invalid age. Enter again!!: ";
                cin >> age;
            }
            cin.ignore(); 
            cout << "Enter Address: ";
            getline(cin, address);
            totalpatients++;
        }
         
        static void displaytotal() {
            cout << "Total number of patients: " << totalpatients << endl;
        }
};

class workers {
    public:
        void staff(int id=0) {
            cout << "\nStaff ID: " << id << endl;
        }

        void staff(string fname="", string s="N/A", int age=0) {
            cout << "Doctor's name: " << fname << endl;
            cout << "Specialization: " << s << endl;
            cout << "Age: " << age << endl;
        }
};

int main() {
    patient p;
    workers w;
    cout << "\tAvailable Staff\n";
    w.staff(1);
    w.staff("James", "OPD", 30);
    w.staff(2);
    w.staff("Sarala", "Surgeon", 45);
    w.staff(3);
    w.staff("Rohan","General Physician",42);

    details* d[100];
    int num = 0;
    int ch;

    do {
        cout << "\nMENU\n";
        cout << "1. Add new patient\n";
        cout << "2. Display patient details\n";
        cout << "3. Display total patients\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1: {
                d[num] = new details();
                d[num]->input();
                num++;
                break;
            }
            case 2: {
                int pid;
                cout << "Enter patient id to display details: ";
                cin >> pid;
                bool found = false;
                for (int i = 0; i < num; i++) {
                    if (d[i]->p_id == pid) {
                        display(*d[i]);  
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Patient with id " << pid << " not found" << endl;
                }
                break;
            }
            case 3: {
                details::displaytotal();
                break;
            }
            case 4: {
                cout << "Exiting program....." << endl;
                break;
            }
            default:
                cout << "Invalid input. Please enter a valid choice\n";
        }
    } while (ch != 4);

    for (int i = 0; i < num; i++) {
        delete d[i];
    }
    return 0;
}

