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
        cout << "In Constructor" << endl;
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
        cout << "In Destructor" << endl;
        ofstream outfile;
        outfile.open("TodoList.txt",ofstream::out | ofstream::trunc);
        for(int i = 0; i < tasks.size(); i++)
        {
            cout << tasks[i] << '\n';
            outfile << tasks[i] << endl;
        }
        outfile.close();

    }

    /*
    *   Adds an item to the todo list with the data specified by the string "_duedate" and the task specified by "_task"
    */
    virtual void add(string _duedate, string _task)

    {
        cout << "Adding " << _duedate  << " " << _task <<  endl;
        tasks.push_back(_duedate + " " + _task);
    }

    /*
    *   Removes an item from the todo list with the specified task name
    *
    *   Returns 1 if it removes an item, 0 otherwise
    */

    virtual int remove(string _task)

    {
        cout << "Removing " << _task << endl;
        tasks.erase(std::remove(tasks.begin(), tasks.end(), _task), tasks.end());
        return 0;
    }

    /*
    *   Prints out the full todo list to the console
    */
    virtual void printTodoList()
    {
        cout << "Reading List" << endl;
        ifstream list;
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
    virtual void printDaysTasks(string _date)
    {
        cout << "In daystacks" << endl;
    }
};

#endif