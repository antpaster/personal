#include <iostream>
#include <cmath>
#include <cstdio>

#include <string>
#include <vector>
#include <list>
#include <array>
#include <iterator>

using namespace std;

/** Calculating the general base of the tree with height @param layerCount and total nodes count @param nodeCount */
int logBase(int layerCount, int nodeCount)
{
    int base = 1, seriesSum = 0;
    vector<int> *residuals = new vector<int>;

    while (true)
    {
        for (int i = 0; i < layerCount; ++i)
        {
            seriesSum += (int)pow((double)base, (double)i);
        }

        if (nodeCount - seriesSum >= 0)
        {
            residuals->push_back(nodeCount - seriesSum);
        }
        else
        {
            break;
        }

        seriesSum = 0;
        base++;
    }

    int result = residuals->size();
    delete residuals;

    return result;
}

//void topoLoops(int n, int base, vector<string> &parentContainerStrings, const array<string, 4> &topoContainerSnippets)
//{
////    if (!n)
////    {
////        return;
////    }

//    string outputStr;
//    vector<string> oldParentContainerStrings(parentContainerStrings);
//    parentContainerStrings.clear();

//    if (n)
//    {
//        for (int i = 0; i < oldParentContainerStrings.size(); ++i)
//        {
//            parentContainerStrings.push_back(oldParentContainerStrings[i] + to_string(i));
//            for (int i = 0; i < base; ++i)
//            {
//                topoLoops(n - 1, base, parentContainerStrings, topoContainerSnippets);
//            }
//        }
//    }
//    else
//    {
//        for (int i = 0; i < oldParentContainerStrings.size(); ++i)
//        {
//            parentContainerStrings.push_back(oldParentContainerStrings[i] + to_string(i));
//            for (int j = 0; j < base; ++j)
//            {
//                outputStr = topoContainerSnippets[0] + parentContainerStrings[i] + topoContainerSnippets[1] + parentContainerStrings[i]
//                        + to_string(j) + topoContainerSnippets[2] + parentContainerStrings[i] + to_string(j)
//                        + topoContainerSnippets[3];
//                cout << outputStr;
//            }
//        }
//    }
//}

int main()
{
    int layerCount = 4, leafCount = 5000;
    int containerBase = (int)pow((double)leafCount, 1.0 / (double)(layerCount - 1));
//    cout << "\nLayer count: " << layerCount << ", node count: " << leafCount << ", log base: " << containerBase << endl;

    /** Making the container tree *********************************************************************************************************/
    array<string, 4> topoContainerSnippets
    {
        "newModel VariableContainer[parentAddr: Address[\"",
        "\"], baseComponentType: @container, modelAddr: Address[\"",
        "\"], name: \"",
        "\"];\n"
    };
    string outputStr;
    string containerStr = "container";
    vector<string> *parentContainerStrings = new vector<string>;
    vector<string> *leafParents = new vector<string>;

//    int i[3];
//    for (int i = 0; i < 3; ++i)
//    {
//        topoLoops(3 - i, base, parentContainerStrings, topoContainerSnippets);
//    }

    for (int i = 0; i < containerBase; ++i)
    {
        outputStr = topoContainerSnippets[0] + "root" + topoContainerSnippets[1] + containerStr + to_string(i) + topoContainerSnippets[2]
                + containerStr + to_string(i) + topoContainerSnippets[3];
        cout << outputStr;
    }

    for (int i = 0; i < containerBase; ++i)
    {
        parentContainerStrings->push_back(containerStr + to_string(i));
        for (int j = 0; j < containerBase; ++j)
        {
            leafParents->push_back((*parentContainerStrings)[i] + to_string(j));
            outputStr = topoContainerSnippets[0] + (*parentContainerStrings)[i] + topoContainerSnippets[1] + (*parentContainerStrings)[i]
                    + to_string(j) + topoContainerSnippets[2] + (*parentContainerStrings)[i] + to_string(j) + topoContainerSnippets[3];
            cout << outputStr;
        }
    }

    delete parentContainerStrings;

    /** Making the nodes ******************************************************************************************************************/
    array<string, 5> topoLeafSnippets
    {
        "newModel VariableContainer[parentAddr: Address[\"",
        "\"], baseComponentType: @unixHost, modelAddr: Address[\"",
        "\"], name: \"",
        "\", ip: \"192.168.57.17\", description: \"Unix host\"];\n"
    };

    cout << endl;

    int extraLeafCount = leafCount % leafParents->size();
    int inc, leafCounter = 0, defaultLeavesInContainer = leafCount / leafParents->size();
    list<int> *leavesIds = new list<int>;
    const string commonLeafName = "unixHost";
    string leafName;
    for (int i = 0; i < leafParents->size(); ++i)
    {
//        cout << [=](){return (i < extraLeafCount - 1) ? 1 : 0;} << endl;
        inc = (i < extraLeafCount) ? 1 : 0;
        for (int j = 0; j < defaultLeavesInContainer + inc; ++j)
        {
            leafName = commonLeafName + to_string(leafCounter);
            leavesIds->push_back(leafCounter);
            outputStr = topoLeafSnippets[0] + (*leafParents)[i] + topoLeafSnippets[1] + leafName + topoLeafSnippets[2] + leafName
                    + topoLeafSnippets[3];
            cout << outputStr;

            leafCounter++;
        }
    }

    delete leafParents;

    /** Making the topology ***************************************************************************************************************/
    int topoBase = logBase(layerCount, leavesIds->size());
    list<list<int>> *topoTree = new list<list<int>>;
    auto leavesNamesIt = leavesIds->cbegin();
    leafCounter = 0;
    int totalNodeCount = 0, currLayerNodeCount, layerIndex = 0;

    while (true)
    {
        currLayerNodeCount = (int)pow((double)topoBase, (double)layerIndex);
        totalNodeCount += currLayerNodeCount;
        if (totalNodeCount <= leafCount)
        {
            topoTree->push_back(list<int>{});
            for (int j = 0; j < currLayerNodeCount; ++j)
            {
                topoTree->back().push_back(leafCounter);
                leavesNamesIt++;
                leafCounter++;
            }
            layerIndex++;
        }
        else
        {
            break;
        }
    }

    for (int i = leafCounter; i < leafCount; ++i)
    {
         topoTree->back().push_back(i);
         leavesNamesIt++;
    }

    /** Making the nodes' interfaces ******************************************************************************************************/
    array<string, 3> topoInterfaceSnippets
    {
        "newComponent VariableContainer[modelAddr: Address[\"",
        "\"], cTag: \"interface\", id: \"",
        "\", ifType: 6];\n"
    };

    cout << endl;

    leafCounter = 0;
    for (auto& id: *leavesIds)
    {
        outputStr = topoInterfaceSnippets[0] + commonLeafName + to_string(id) + topoInterfaceSnippets[1] + to_string(leafCounter)
                + topoInterfaceSnippets[2];
        cout << outputStr;
        leafCounter++;
    }

    delete leavesIds;

    /** Making the connections in the topology ********************************************************************************************/
    array<string, 5> topoConnectionSnippets
    {
        "connection VariableContainer[first: Address[\"",
        "\"], second: Address[\"",
        "\"], firstInstId: \"",
        "\", secondInstId: \"",
        "\", cTag: \"interface\"];\n"
    };

    cout << endl;

    // Making connections for all levels but the last
    auto topoLayersIt = topoTree->cbegin();
    auto topoChildrenIt = next(topoLayersIt)->cbegin();
    for (; topoLayersIt != prev(topoTree->cend(), 2); ++topoLayersIt)
    {
        topoChildrenIt = next(topoLayersIt)->cbegin();
        for (auto topoParentsIt = topoLayersIt->cbegin(); topoParentsIt != topoLayersIt->cend(); ++topoParentsIt)
        {
            for (int i = 0; i < topoBase; ++i)
            {
                outputStr = topoConnectionSnippets[0] + commonLeafName + to_string(*topoParentsIt) + topoConnectionSnippets[1]
                        + commonLeafName + to_string(*topoChildrenIt) + topoConnectionSnippets[2] + to_string(*topoParentsIt)
                        + topoConnectionSnippets[3] + to_string(*topoChildrenIt) + topoConnectionSnippets[4];
                cout << outputStr;
                topoChildrenIt++;
            }
        }
    }

    // Connecting the last level with pre-last
    topoLayersIt = prev(topoTree->cend(), 2); // pre-leaf layer
    topoChildrenIt = next(topoLayersIt)->cbegin(); // leaf layer
    extraLeafCount = next(topoLayersIt)->size() % topoLayersIt->size();
    defaultLeavesInContainer = next(topoLayersIt)->size() / topoLayersIt->size();
    for (auto topoParentsIt = topoLayersIt->cbegin(); topoParentsIt != topoLayersIt->cend(); ++topoParentsIt)
    {
        if (extraLeafCount)
        {
            inc = 1;
            extraLeafCount--;
        }
        else
        {
            inc = 0;
        }
        for (int i = 0; i < defaultLeavesInContainer + inc; ++i)
        {
            outputStr = topoConnectionSnippets[0] + commonLeafName + to_string(*topoParentsIt)+ topoConnectionSnippets[1] + commonLeafName
                    + to_string(*topoChildrenIt) + topoConnectionSnippets[2] + to_string(*topoParentsIt) + topoConnectionSnippets[3]
                    + to_string(*topoChildrenIt) + topoConnectionSnippets[4];
            cout << outputStr;
            topoChildrenIt++;
        }
    }

    delete topoTree;

//    getchar();

    return 0;
}
