#include <bits/stdc++.h>

using namespace std;

struct Customer
{
    char name[128];
    int balance = 50000;
    char address[128];
    char transactions[128];
};
Customer *customers;
int customersCount;

void menu()
{
    cout << "Hello in bank management system please enter your choice" << endl;
    cout << "1-To print all names and account balances." << endl;
    cout << "2-To print specific customer's account balance." << endl;
    cout << "3-To edit customer's transaction." << endl;
    cout << "4-To show customer with highest balance." << endl;
    cout << "5-To change  customer's name , address or account balance." << endl;
    cout << "6-To show  how many customer's in one city." << endl;
}

void print_names()
{
    for (int i = 0; i < customersCount; i++)
    {
        cout << customers[i].name << " : " << customers[i].balance << endl;
    }
}

void specific_balance()
{
    char specific_name[128];
    cout << "please enter customer's name." << endl;
    cin >> specific_name;
    for (int j = 0; j < customersCount; j++)
    {
        if (strcmp(customers[j].name, specific_name) == 0)
        {
            cout << customers[j].balance << endl;
            break;
        }
    }
}
void highest_balance()
{
    int _max = 0;
    for (int i = 0; i < customersCount; i++)
    {
        if (customers[i].balance > _max)
        {
            _max = customers[i].balance;
        }
    }
    for (int j = 0; j < customersCount; j++)
    {
        if (customers[j].balance == _max)
        {
            cout << customers[j].name << ":" << _max << endl;
            break;
        }
    }

}

bool validate_address(Customer x)
{
    int dist = 0; //dist refer to first distance in address
    int counter = 0; // to count , (comma) in address.
    for (int j = 0; j < strlen(x.address); j++)
    {
        if (x.address[j] == ' ')
        {
            dist = j;
            break;
        }
    }
    for (int m = 0; m < dist; m++)
    {
        if (!(x.address[m] >= '0' && x.address[m] <= '9'))
        {
            return false;
        }
    }
    for (int b = dist + 1; b < strlen(x.address); b++)
    {
        if (x.address[b] == ',')
        {
            counter += 1;
        }
    }
    if (counter == 2)
        return true;
    return false;
}
void register_customers()
{
    cout << "Enter the number of customers: ";
    cin >> customersCount;
    customers = new Customer[customersCount];
    for (int i = 0; i < customersCount; i++)
    {
        cout << "Please enter customer's name." << endl;
        cin >> customers[i].name;
        cin.ignore(32000, '\n');
        cout << "Enter " << customers[i].name << "\'s address:" << endl;
        cin.getline(customers[i].address, 128);
        while (validate_address(customers[i]) == false)
        {
            cout << "Invalid address please try add again:" << endl;
            cin.getline(customers[i].address, 128);
        }
        strcpy(customers[i].transactions, ""); // to do: enter history
    }
}

void change_balance()
{
    char _name[128];
    int new_balance;
    cout << "Please enter customer's name that you change his balance" << endl;
    cin >> _name;
    cout << "Enter new_balance" << endl;
    cin >> new_balance;
    for (int i = 0; i < customersCount; i++)
    {
        if ((strcmp(customers[i].name, _name) == 0))
            customers[i].balance = new_balance;
    }
}
void change_name()
{
    char old_name[128];
    char new_name[128];
    cout << "please enter name you want to change" << endl;
    cin >> old_name;
    cout << "Please enter new name." << endl;
    cin >> new_name;
    for (int i = 0; i < customersCount; i++)
    {
        if (strcmp(customers[i].name, old_name) == 0)
            strcpy(customers[i].name, new_name);
    }
}

void change_address()
{
    char _name[128];
    char new_address[128];
    cout << "please enter customer's name that you want to change his address" << endl;
    cin >> _name;
    cout << "Please enter new address." << endl;
    cin >> new_address;
    for (int i = 0; i < customersCount; i++)
    {
        if (strcmp(customers[i].name, _name) == 0)
            strcpy(customers[i].address, new_address);
    }
}


bool validate_compute_transaction(Customer &x)   // format must be "[W/D] ### [W/D] #### .."
{
    x.balance = 50000;
    for (int i = 0; i < strlen(x.transactions); i++)
    {
        if (x.transactions[i] == 'W')
        {
            i += 2; // skip 'w' and ' '
            int val = 0;
            while (i < strlen(x.transactions) && '0' <= x.transactions[i] && x.transactions[i] <= '9')
            {
                i++;
                val = val * 10 + x.transactions[i] - '0';
            }
            x.balance -= val;
        }
        else if (x.transactions[i] == 'D')
        {
            i += 2;
            int val = 0;
            while (i < strlen(x.transactions) && '0' <= x.transactions[i] && x.transactions[i] <= '9')
            {
                i++;
                val = val * 10 + x.transactions[i] - '0';
            }
            x.balance += val;
        }
        else if (x.transactions[i] != ' ')
        {
            x.balance = 50000;
            return false;
        }
    }
    return true;
}
void edit_transaction()
{
    char _name[128];
    cout << "Please enter customer's name that you change his transaction" << endl;
    cin >> _name;
    for (int i = 0; i < customersCount; i++)
    {
        if ((strcmp(customers[i].name, _name) == 0))
        {
            cout << "Transactions history was: " << customers[i].transactions << endl;
            cout << "Enter transactions history:" << endl;
            cin.ignore(32000, '\n');
            cin.getline(customers[i].transactions, 128);
            while (validate_compute_transaction(customers[i]) == false)
            {
                cout << "Invalid history please try again:" << endl;
                cin.getline(customers[i].transactions, 128);
            }
        }
    }
}
bool compare_city(char a[128], char b[128])
{
    for (int j = 0; j < strlen(a) - strlen(b); j++)
    {
        bool good = true;
        for (int i = 0; i < strlen(b); i++)
        {
            if (a[i + j] != b[i])
                good = false;
        }
        if (good)
            return true;
    }
    return false;
}
void search_city()
{
    char specific_city[128];
    cout << "please enter city name." << endl;
    cin >> specific_city;
    for (int j = 0; j < customersCount; j++)
    {
        if (compare_city(customers[j].address, specific_city))
            cout << customers[j].name << endl;
    }
}
int main()
{
    register_customers();
    int choice;
    while (true)
    {
        menu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            print_names();
            break;
        case 2:
            specific_balance();
            break;
        case 3:
            edit_transaction();
            break;
        case 4:
        {
            highest_balance();
            break;
        };
        case 5:
        {
            int change;
            cout << "To change Name press 1,To change address press 2, To change balance press 3." << endl;
            cin >> change;
            switch (change)
            {
            case 1:
            {
                change_name();
                break;
            };
            case 2:
            {
                change_address();
                break;
            };
            case 3:
            {
                change_balance();
            };
            break;
            };
            break;
        }
        case 6:
            search_city();
            break;
        default:
            cout << "Invalid choice" << endl;
        };
    }
    return 0;
}