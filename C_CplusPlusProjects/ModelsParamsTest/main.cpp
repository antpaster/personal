#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#include <list>
#include <array>

using namespace std;

inline int calcRandPercent()
{
    return rand() % 100;
}

int main()
{
    int sleepDurationSec = 60;
    const string commonNodeName = "unixHost";

    int nodeCount = 5000;
    list<int> *nodeIds = new list<int>;
    for (int i = 0; i < nodeCount; ++i)
    {
        nodeIds->push_back(i);
    }

    array<string, 5> updateComponentSnippets
    {
        "updateComponent VariableContainer[modelAddr: Address[\"",
        "\"], cTag: \"baseComponent\", id: \"attributes\", memUtil: ",
        ", cpuLoad15min: ",
        ", availRAMpercent: ",
        "];\n"
    };

//    int randVal;
    string outputStr;
    while (true)
    {
        srand(time(nullptr));
        for (auto& id: *nodeIds)
        {
            outputStr = updateComponentSnippets[0] + commonNodeName + to_string(id) + updateComponentSnippets[1]
                    + to_string(calcRandPercent()) + updateComponentSnippets[2] + to_string(calcRandPercent()) + updateComponentSnippets[3]
                    + to_string(calcRandPercent()) + updateComponentSnippets[4];
            cout << outputStr;
        }

        cout << endl;

        this_thread::sleep_for(chrono::seconds(sleepDurationSec)); // sleep for sleepDurationSec
    }

    delete nodeIds;

    return 0;
}
