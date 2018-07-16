#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include <string>
#include <vector>
#include <array>

using namespace std;

int logBase(int layers, int nodeCount)
{
    int base = 1, seriesSum = 0;
    vector<int> residuals;

    while (true)
    {
        for (int i = 0; i < layers; ++i)
        {
            seriesSum += (int)pow((double)base, (double)i);
        }

        if (nodeCount - seriesSum >= 0)
        {
            residuals.push_back(nodeCount - seriesSum);
        }
        else
        {
            break;
        }

        seriesSum = 0;
        base++;
    }

    return residuals.size();
}

void topoLoops(int n, int base, vector<string> &parentContainerStrings, const array<string, 4> &topoContainerSnippets)
{
//    if (!n)
//    {
//        return;
//    }

    string outputStr;
    vector<string> oldParentContainerStrings(parentContainerStrings);
    parentContainerStrings.clear();

    if (n)
    {
        for (int i = 0; i < oldParentContainerStrings.size(); ++i)
        {
            parentContainerStrings.push_back(oldParentContainerStrings[i] + to_string(i));
            for (int i = 0; i < base; ++i)
            {
                topoLoops(n - 1, base, parentContainerStrings, topoContainerSnippets);
            }
        }
    }
    else
    {
        for (int i = 0; i < oldParentContainerStrings.size(); ++i)
        {
            parentContainerStrings.push_back(oldParentContainerStrings[i] + to_string(i));
            for (int j = 0; j < base; ++j)
            {
                outputStr = topoContainerSnippets[0] + parentContainerStrings[i] + topoContainerSnippets[1] + parentContainerStrings[i]
                        + to_string(j) + topoContainerSnippets[2] + parentContainerStrings[i] + to_string(j)
                        + topoContainerSnippets[3];
                cout << outputStr;
            }
        }
    }
}

int main()
{
    vector<int> nodes;
    int layerCount = 4, leafCount = 199;
    int base = /*logBase(layerCount, nodeCount)*/(int)pow((double)leafCount, 1.0 / (double)layerCount);
    cout << "\nLayer count: " << layerCount << ", node count: " << leafCount << ", log base: " << base << endl;

    int nodesSum = 0;
    for (int i = 0; i < layerCount; ++i)
    {
        nodes.push_back((int)pow((double)base, (double)i));
        nodesSum += nodes[i];
    }
    nodes.back() += leafCount - nodesSum;

    array<string, 4> topoContainerSnippets{
        "newModel VariableContainer[parentAddr: Address[\"",
        "\"], baseComponentType: @container, modelAddr: Address[\"",
        "\"], name: \"",
        "\"];\n"
    };
    string outputStr;
    string containerStr = "container";
    string parentContainerStr;
    vector<string> parentContainerStrings;
    vector<string> leafParents;

//    int i[3];
//    for (int i = 0; i < 3; ++i)
//    {
//        topoLoops(3 - i, base, parentContainerStrings, topoContainerSnippets);
//    }

    for (int i = 0; i < base; ++i)
    {
        outputStr = topoContainerSnippets[0] + "root" + topoContainerSnippets[1] + containerStr + to_string(i) + topoContainerSnippets[2]
                + containerStr + to_string(i) + topoContainerSnippets[3];
        cout << outputStr;
    }

    for (int i = 0; i < base; ++i)
    {
        parentContainerStrings.push_back(containerStr + to_string(i));
        for (int j = 0; j < base; ++j)
        {
            leafParents.push_back(parentContainerStrings[i] + to_string(j));
            outputStr = topoContainerSnippets[0] + parentContainerStrings[i] + topoContainerSnippets[1] + parentContainerStrings[i]
                    + to_string(j) + topoContainerSnippets[2] + parentContainerStrings[i] + to_string(j) + topoContainerSnippets[3];
            cout << outputStr;
        }
    }

    array<string, 5> topoLeafSnippets{
        "newModel VariableContainer[parentAddr: Address[\"",
        "\"], baseComponentType: @unixHost, modelAddr: Address[\"",
        "\"], name: \"",
        "\", ip: \"192.168.57.17\", memUtil: \"",
        "\"];\n"
    };
    double randMemUtil = 0.0;

    cout << endl;

    int extraLeafCount = nodes.back() % leafParents.size();
    int inc, leafCounter = 0, defaultLeavesInContainer = nodes.back() / leafParents.size();
    for (int i = 0; i < leafParents.size(); ++i)
    {
//        cout << [=](){return (i < extraLeafCount - 1) ? 1 : 0;} << endl;
        inc = (i < extraLeafCount) ? 1 : 0;
        for (int j = 0; j < defaultLeavesInContainer + inc; ++j)
        {
            outputStr = topoLeafSnippets[0] + leafParents[i] + topoLeafSnippets[1] + "unixHost" + to_string(i/*leafCounter*/) + to_string(j)
                    + topoLeafSnippets[2] + "unixHost" + to_string(i/*leafCounter*/) + to_string(j) + topoLeafSnippets[3]
                    + to_string(randMemUtil) + topoLeafSnippets[4];
            cout << outputStr;

            leafCounter++;
        }
    }

    cout << leafCounter << endl;

//    for (int i = 0; i < base; ++i)
//    {
//        for (int j = 0; j < base; ++j)
//        {
//            parentContainerStr = parentContainerStrings[i] + to_string(j);
//            for (int p = 0; p < base; ++p)
//            {
//                outputStr = topoContainerSnippets[0] + parentContainerStr + topoContainerSnippets[1] + parentContainerStr + to_string(p)
//                        + topoContainerSnippets[2] + parentContainerStr + to_string(p) + topoContainerSnippets[3];
//                cout << outputStr;
//            }
//        }
//    }

    return 0;
}
