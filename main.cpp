#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <algorithm>

using namespace std;

void cacheFile(string& Filename, unordered_map<string, string>& CacheMap, vector<string>& MasterIndex) {
    ifstream fin(Filename + ".txt");

    cout << "Configuring " << Filename + ".txt" << endl;

    // Do not continue if the file has failed to open.
    if (!fin.is_open()) {
        cout << "Failed to open " << Filename << endl;
        return;
    }

    string CacheString;
    while (getline(fin, CacheString)) { 
        if (CacheString.length() < 3) {
            continue;
        }
        CacheMap.insert({CacheString, Filename});
        MasterIndex.push_back(CacheString);

        cout << "Caching: " << CacheString << endl;
    }

    cout << endl;

    fin.close();
}

void Shuffle(vector<string>& targetVector) {
    int size = targetVector.size();
    for (int i = 0; i < size; ++i) {
        int j = i + rand() % (size - i);
        swap(targetVector[i], targetVector[j]);
    }
}

int main() {

    unordered_map<string, string> AnswerMap;
    vector<string> Master;

    vector<string> Files {"nl", "eba","mba","lba","eia","lia"};

    for (unsigned i = 0; i < Files.size(); ++i) {
        cacheFile(Files.at(i), AnswerMap, Master);
    }

    string input;
    int QuestionCount = 0;
    int Score = 0;

    Shuffle(Master);

    for (int i = 0; i < 15; ++i) {
        cout << endl;
    }

    while (input != ":quit") {
        // int randomindex = rand() % Master.size();
        string qs = Master.at(QuestionCount);
        QuestionCount += 1;

        cout << "Q" << QuestionCount <<": " << qs << endl;
        cout << "What period was this event?" << endl;
        cout << "   Answer: ";

        cin >> input;
        if (input == AnswerMap.at(qs)) {
            Score += 1;
            cout << endl;
            cout << "Correct! +1 Points. ";
        } else {
            cout << endl;
            cout << "Incorrect: The answer was " << AnswerMap.at(qs);
        }

        cout << "(" << Score << "/" << QuestionCount << ")" << endl << endl;
    }

    return 0;
}
