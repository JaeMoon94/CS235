#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <map>

using namespace std;

// argc counts how many argument passed on commandline
// argv[0] is file name wich is going to be ./Lab3 in this case
// argv[1] is going to be the filename 1Nephi.txt in this case
// command line for this is going to be ./Lab3 1Nephi.txt

int main(int argc, char *argv[]) 
{
    ifstream ifs;
    ofstream ofset;
    string fileName = argv[1];
    ifs.open(fileName.c_str());
    string word;
    vector <string> myVector;
    string noPunc = "";
    set <string> mySet;

    ofset.open("Nephie_set.txt");

    while(!ifs.eof())
    {
        ifs >> word;

        mySet.insert(word);

        // cout << word << endl;
        for (int i = 0; i < word.size(); i ++)
        {
            if(isalpha(word[i]))
            {
               noPunc += word[i]; 
            }
        }
        myVector.push_back(noPunc);
        noPunc = "";
    }

    ifs.close();

    set<string> ::iterator setItr;
    for(setItr = mySet.begin(); setItr != mySet.end(); setItr++)
    {
        ofset << *setItr << endl;
    }

    ofset.close();
    // cout << myVector.at(2) << endl;

    // check vector works.
    // for(int i = 0; i < myVector.size(); i ++) 
    // {
    //     cout << myVector.at(i) << endl;
    // }
    // cout << "size: " << myVector.size() << endl;

    //save it to userfile
    ofstream outfile;
    outfile.open("jae_vector.txt");
    for(int i = 0; i < myVector.size(); i ++)
    {
        outfile << myVector.at(i) << endl;
    }
    outfile.close();


    //part 3 (key=”having”, value=”been”), (key=”been”, value=”born”), (key=”born”, value=”of”)

    map <string,string> wordmap;
    string last = "";
    for(int i = 0; i < myVector.size(); i++)
    {
        wordmap[last] = myVector.at(i);
        last = myVector.at(i);
    }

    ofstream mapOutfile;
    mapOutfile.open("1Nephi.txt_map.txt");
    map <string,string> :: iterator itr;
    for(itr = wordmap.begin(); itr != wordmap.end(); itr++)
    {
        mapOutfile << itr->first << ", " << itr -> second << endl; 
    }

    mapOutfile.close();


    //part 4 

    string state = "";
    for(int i = 0; i < 100; i++)
    {
        // cout << wordmap[state] << " ";
        state = wordmap[state];
    }
    cout << endl;
    

    //part 5

    map<string, vector<string> > newWordmap;
    string newState = "";
    for(int i = 0; i < myVector.size(); i++)
    {
        newWordmap[newState].push_back(myVector.at(i));
        newState = myVector.at(i);
    }

    map <string,string> :: iterator it;
    for(it = wordmap.begin(); it != wordmap.end(); it++)
    {
        if(it->first == "Nephi")
        {
            for(int i= 0; i < newWordmap["Nephi"].size(); i++)
            {
                // cout << newWordmap["Nephi"].at(i);
                if(i < newWordmap["Nephi"].size()-1)
                {
                    // cout << ", ";
                }
            }
            cout << endl;
        }
    }

    //part 6

    map <vector <string>, vector <string> > finalWordMap;

    int numContext = 2;
    vector<string> stateVec;
    for(int i = 0; i < numContext; i++)
    {
        stateVec.push_back("");
    }

    for(int i = 0; i < myVector.size(); i++)
    {
        finalWordMap[stateVec].push_back(myVector.at(i));
        stateVec.push_back(myVector.at(i));
        stateVec.erase(stateVec.begin());
    }

    stateVec.clear();
    for (int i = 0; i < numContext; i++) 
    {
        stateVec.push_back("");
    }

    for (int i = 0; i < 100; i++) 
    {
        int ind = rand() % finalWordMap[stateVec].size();
        cout << finalWordMap[stateVec][ind]<<" ";
        stateVec.push_back(finalWordMap[stateVec][ind]);
        stateVec.erase(stateVec.begin());
    }
    cout << endl;


    return 0;
}