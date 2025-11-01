#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <chrono>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

// use chrono script for timing from canvas
using namespace std::chrono;

// add how many times we will be running the program to get average times
const int numSimulations = 15; // run 15 times
const int numOperations = 4; // 4 operations: read, sort, insert, delete
const int numStructures = 3; // 3 data structures: vector, list, set

// first we create a struct to hold our results
struct mainResults {
    long long vectorTime;
    long long listTime;
    long long setTime;
    
};

// read all 20,000 strings from the file into a vector
    vector<string> readStringsFromFile(const string& filename) { 
        vector<string> strings; 
        ifstream file(filename); 
        string line;
        while (getline(file, line)) { 
            strings.push_back(line);
        }
        return strings;
    }

    // The first race is READING. The challenge is to read the 20,000 data elements into each of these data structures: vector, list, set

    mainResults readingRace(const vector<string>& data) {
        mainResults results = {0, 0, 0};

        // vector reading
        auto start = high_resolution_clock::now(); // start timing  
        vector<string> vec(data); // push data into vector

        auto end = high_resolution_clock::now(); // end timing
        results.vectorTime = duration_cast<microseconds>(end - start).count();  // how long it took

        //list reading
        start = high_resolution_clock::now();
        list<string> lst(data.begin(), data.end());

        end = high_resolution_clock::now();
        results.listTime = duration_cast<microseconds>(end - start).count();

        //set reading
        start = high_resolution_clock::now();
        set<string> st(data.begin(), data.end());

        end = high_resolution_clock::now();
        results.setTime = duration_cast<microseconds>(end - start).count();

        return results;
    }

    
// race 2 for sorting the data structures
    mainResults sortingRace(const vector<string>& data) {
        mainResults results = {0, 0, 0};

        // vector sorting
        vector<string> vec(data);
        auto start = high_resolution_clock::now();
        sort(vec.begin(), vec.end());

        auto end = high_resolution_clock::now();
        results.vectorTime = duration_cast<microseconds>(end - start).count();

        // list sorting
        list<string> lst(data.begin(), data.end());
        start = high_resolution_clock::now();
        lst.sort();

        end = high_resolution_clock::now();
        results.listTime = duration_cast<microseconds>(end - start).count();

        // set sorting but sorting is already done when inserting
        set<string> st(data.begin(), data.end());
        start = high_resolution_clock::now();

        end = high_resolution_clock::now();
        results.setTime =  - 1; // already sorted

        return results;

    }

    // race 3 for inserting. Insert the value "TESTCODE" into the middle of the vector or the middle of the list, or into the set

    mainResults insertingRace(const vector<string>& data) {
        mainResults results = {0, 0, 0};
        const string toInsert = "TESTCODE";

        // vector inserting
        vector<string> vec(data);
        auto start = high_resolution_clock::now();
        vec.insert(vec.begin() + vec.size() / 2, toInsert);

        auto end = high_resolution_clock::now();
        results.vectorTime = duration_cast<microseconds>(end - start).count();

        // list inserting
        list<string> lst(data.begin(), data.end());
        start = high_resolution_clock::now();
        auto it = lst.begin();
        advance(it, lst.size() / 2);
        lst.insert(it, toInsert);

        end = high_resolution_clock::now();
        results.listTime = duration_cast<microseconds>(end - start).count();

        // set inserting
        set<string> st(data.begin(), data.end());
        start = high_resolution_clock::now();
        st.insert(toInsert);

        end = high_resolution_clock::now();
        results.setTime = duration_cast<microseconds>(end - start).count();

        return results;
    }

    //  race 4 for deleting. Delete the middle-ish element of the vector, the list, or the set

    mainResults deletingRace(const vector<string> &data) {
        mainResults results = {0, 0, 0};

        // vector deleting
        vector<string> vec(data);
        auto start = high_resolution_clock::now();
        vec.erase(vec.begin() + vec.size() / 2);

        auto end = high_resolution_clock::now();
        results.vectorTime = duration_cast<microseconds>(end - start).count();

        // list deleting
        list<string> lst(data.begin(), data.end());
        start = high_resolution_clock::now();
        auto it = lst.begin();
        advance(it, lst.size() / 2);
        lst.erase(it);

        end = high_resolution_clock::now();
        results.listTime = duration_cast<microseconds>(end - start).count();

        // set deleting
        set<string> st(data.begin(), data.end());
        start = high_resolution_clock::now();
        auto itSet = st.begin();
        advance(itSet, st.size() / 2);
        st.erase(itSet);

        end = high_resolution_clock::now();
        results.setTime = duration_cast<microseconds>(end - start).count();

        return results;

    }

    // display in a neat table
    
    void displayResults(const mainResults& read, const mainResults& sort, const mainResults& insert, const mainResults& deletes) {   
        cout << "Operation\tVector\t\tList\t\tSet" << endl;
        cout << "Read\t\t" << (long long)read.vectorTime << "\t\t" << (long long)read.listTime << "\t\t" << (long long)read.setTime << endl;
        cout << "Sort\t\t" << (long long)sort.vectorTime << "\t\t" << (long long)sort.listTime << "\t\t" << (long long)sort.setTime << endl;
        cout << "Insert\t\t" << (long long)insert.vectorTime << "\t\t" << (long long)insert.listTime << "\t\t" << (long long)insert.setTime << endl;
        cout << "Delete\t\t" << (long long)deletes.vectorTime << "\t\t" << (long long)deletes.listTime << "\t\t" << (long long)deletes.setTime << endl;
}




int main() {

    // read data from file
    vector<string> data = readStringsFromFile("codes.txt");

    // run the races now
   mainResults readResults = readingRace(data);
   mainResults sortResults = sortingRace(data);
   mainResults insertResults = insertingRace(data);
   mainResults deleteResults = deletingRace(data);

   // create a 3d array to store the average results
    int results[numSimulations][numOperations][numStructures];

    // store results in the array so we have to run them first
    for (int sim = 0; sim < numSimulations; ++sim) {
        
        // run the races
        mainResults readResults = readingRace(data);
        mainResults sortResults = sortingRace(data);
        mainResults insertResults = insertingRace(data);
        mainResults deleteResults = deletingRace(data);

        // now store the results in the array

        // reading results
        results[sim][0][0] = readResults.vectorTime;
        results[sim][0][1] = readResults.listTime;
        results[sim][0][2] = readResults.setTime;

        // sorting results use 1 since it's second in the array
        results[sim][1][0] = sortResults.vectorTime;
        results[sim][1][1] = sortResults.listTime;
        results[sim][1][2] = sortResults.setTime;

        // insert results
        results[sim][2][0] = insertResults.vectorTime;
        results[sim][2][1] = insertResults.listTime;
        results[sim][2][2] = insertResults.setTime;

        // delete results
        results[sim][3][0] = deleteResults.vectorTime;
        results[sim][3][1] = deleteResults.listTime;
        results[sim][3][2] = deleteResults.setTime;

        // output the tests ran
        cout << "\nSimlations completed: " << endl;
        cout << "Operation\tVector\tList\tSet" << endl;
        cout << "Read\t\t" << results[0][0][0] << "\t\t" << results[0][0][1] << "\t\t" << results[0][0][2] << endl;
        cout << "Sort\t\t" << results[0][1][0] << "\t\t" << results[0][1][1] << "\t\t" << results[0][1][2] << endl;
        cout << "Insert\t\t" << results[0][2][0] << "\t\t" << results[0][2][1] << "\t\t" << results[0][2][2] << endl;
        cout << "Delete\t\t" << results[0][3][0] << "\t\t" << results[0][3][1] << "\t\t" << results[0][3][2] << endl;
    
    }


   
    // display the results
    displayResults(readResults, sortResults, insertResults, deleteResults);

    return 0;
}

// milestone 1 complete

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/