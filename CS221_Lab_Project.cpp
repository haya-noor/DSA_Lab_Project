#include <iostream>
#include <string.h>
#include <conio.h>
#include <windows.h>
using namespace std;

class User_login
{
private:
    struct user_info
    {
        string first_name, last_name;
        string username, password;
        user_info *next;
    };

    static const int table_size = 6;
    user_info *HashTable[table_size];

public:
    // initially no user is present and HashTable is empty
    User_login()
    {
        for (int i = 0; i < table_size; i++)
        {
            HashTable[i] = new user_info;
            HashTable[i]->username = "NULL";
            HashTable[i]->first_name = "NULL";
            HashTable[i]->last_name = "NULL";
            HashTable[i]->password = "NULL";
        }
    }

    // This function will allocate index in the HashTable for users' credentials and will store them
    // username is used as a key over here
    int hash_ftn(string username)
    {
        int hash = 0; // hash will store our key(input value based on whic hash function will allocate index for users' info
        int index;

        for (int i = 0; i < username.length(); i++)
        {
            hash = hash + int(username[i]);
        }
        index = hash % table_size;
        cout << "index" << index << endl;
        return index;
    }

    void registration(string f_name, string l_name, string u_name, string pass)
    {

        int index = hash_ftn(u_name);

        if (HashTable[index]->username == "NULL")
        {
            HashTable[index]->first_name = f_name;
            HashTable[index]->last_name = l_name;
            HashTable[index]->username = u_name;
            HashTable[index]->password = pass;
        }
        else
        {
            user_info *ptr = HashTable[index];
            user_info *new_user = new user_info;
            new_user->first_name = f_name;
            new_user->last_name = l_name;
            new_user->username = u_name;
            new_user->password = pass;

            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            ptr->next = new_user;
            new_user->next = NULL;
        }
    }

    void user_credentials(int index)
    {
        user_info *ptr = HashTable[index];
        if (ptr->username == "NULL")
        {
            cout << "index " << index << " is empty\n";
        }
        else
        {
            cout << "index " << index << " contains the following users' data:\n";
            while (ptr != NULL)
            {
                cout << "-----------\n";
                cout << ptr->first_name << endl;
                cout << ptr->last_name << endl;
                cout << ptr->username << endl;
                cout << ptr->password << endl;
                cout << "-------------\n";
                ptr = ptr->next;
            }
        }
    }

    // Total number of users hash to an index i
    int total_users_at_index(int index)
    {
        int count = 0;
        if (HashTable[index]->username == "NULL")
        {
            return count;
        }
        else
        {
            count++;
            user_info *ptr = HashTable[index];
            while (ptr->next != NULL)
            {
                count++;
                ptr = ptr->next;
            }
        }
        return count;
    }

    // Registered Users credetionals
    void user_table()
    {
        int number;
        for (int i = 0; i < table_size; i++)
        {
            number = total_users_at_index(i);
            cout << "-----------------------\n";
            cout << "Index = " << i << endl;
            cout << HashTable[i]->first_name << endl;
            cout << HashTable[i]->last_name << endl;
            cout << HashTable[i]->username << endl;
            cout << HashTable[i]->password << endl;
            cout << "--------------------------\n";
        }
    }
};
int main()
{
    User_login u;
    int choice;
    do
    {
        system("cls");
        cout << "1_ User Registeration\n";
        cout << "2_ User Credentials\n";
        cout << "3_ Total users' hash to specific index\n";
        cout << "4_ Enter 0 to exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            string first, last, user, pass;
            cout << "Enter First name: ";
            cin >> first;
            cout << "Enter last name: ";
            cin >> last;
            cout << "Enter username: ";
            cin >> user;
            cout << "Enter password: ";
            cin >> pass;
            u.registration(first, last, user, pass);
            Sleep(1000);
            break;
        }
        case 2:
        {
            string uname;
            int ind;
            cout << "Enter the username to check credentials" << endl;
            cin >> uname;
            ind = u.hash_ftn(uname);
            u.user_credentials(ind);
            Sleep(1000);
            break;
        }
        case 3:
        {
            string uname;
            int ind;
            cout << "Enter the username to total enteries" << endl;
            cin >> uname;
            ind = u.hash_ftn(uname);
            u.total_users_at_index(ind);
            Sleep(1000);
            break;
        }

        default:
        {
            cout << "Invalid data";
            break;
        }
        }
    }while(choice != 0);
    return 0;
}