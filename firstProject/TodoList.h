#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "TodoListInterface.h"

using namespace std;

class TodoList: public TodoListInterface {
private:
    vector <string> tasks;

    //Helper Method

public:

    TodoList() 
    {
        // cout << "In Constructor" << endl;
        ifstream myfile ("TODOList.txt");
        string line;
            if (myfile.is_open())
            {
                string oldTask;
                while(!myfile.eof())
                {
                    getline(myfile,oldTask);
                    if(oldTask.size() > 0)
                    {
                        tasks.push_back(oldTask);
                    }
                }
                while ( getline (myfile,line) )
                {
                    cout << line << '\n';
                }


                myfile.close();
            }

    }
    virtual ~TodoList() 
    {
        // cout << "In Destructor" << endl;
        ofstream outfile;
        outfile.open("TodoList.txt", ofstream::out | ofstream::trunc);
        for(int i = 0; i < tasks.size(); i++)
        {
            // cout << tasks[i] << '\n';
            outfile << tasks[i] << endl;
        }
        outfile.close();

    }

    /*
    *   Adds an item to the todo list with the data specified by the string "_duedate" and the task specified by "_task"
    */
    void add(string _duedate, string _task)

    {
        cout << "Adding " << _duedate  << " " << _task <<  endl;
        tasks.push_back(_duedate + " " + _task);
    }

    /*
    *   Removes an item from the todo list with the specified task name
    *
    *   Returns 1 if it removes an item, 0 otherwise
    */

    int remove(string _task)

    {
        cout << "Removing " << _task << endl;
        ifstream myfile("TODOList.txt");;
        string match = "";
        bool isDeleted = false;
        for (int i = 0; i < tasks.size(); i++){
            if ((tasks[i]).find(_task) != string::npos){
                tasks.erase(tasks.begin() + i);
            }
        }

        myfile.close();

        if(isDeleted) return 1;
        else return 0;
    }

    /*
    *   Prints out the full todo list to the console
    */
    void printTodoList()
    {
        cout << "Reading List" << endl;
        ifstream list("TODOList.txt");
        string dateAndTask;
        if(list.is_open())
        {
            while ( getline (list,dateAndTask) )
                {
                    cout << dateAndTask << '\n';
                }
        }
        

    }
    
    /*
    *   Prints out all items of a todo list with a particular due date (specified by _duedate)
    */
    void printDaysTasks(string _date)
    {
        cout << "Print out " << _date << " Todo List." << endl;

        ifstream myfile("TODOList.txt");
        string match = _date;
        while(!myfile.eof())
        {
            getline(myfile,match);
            if(match.find(_date) != string::npos)
            {
                cout << match << endl;
            }
        }


    }
};

#endif