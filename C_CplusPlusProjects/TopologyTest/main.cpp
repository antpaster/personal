#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>

#include <string>
#include <vector>
#include <list>
#include <array>
#include <utility>
#include <iterator>

#define DEBUG 0

using namespace std;

inline int infoAndExit(const char *programName)
{
    cerr << "Usage: " << programName << " <option(s)> VALUES"
            << "\nOptions:\n"
            << "\t-n NODE_COUNT [10..50000]\tSpecify nodes count in the topology\n"
            << "\t-lc LAYER_COUNT [2..NODE_COUNT]\tSpecify layers count in the topology\n"
            << "\t-cc COMPONENT_COUNT [1..1000]\tSpecify processes and interfaces count in a single node\n"
            << "\t[-ml MAKE_LINKS]\tIf presents, nodes in the topology will be connected. Specify this parameter if "
               "INSTANCES_COUNT = INSTANCE_NUMBER\n"
            << "\t-ic INSTANCES_COUNT [1..5]\tSpecify total instances of this program to be launched\n"
            << "\t-in INSTANCE_NUMBER [1..INSTANCES_COUNT]\tSpecify current running instance number\n"
            << endl;
    return 1;
}

/** Calculating the general base of the tree with height @param layerCount and total nodes count @param nodeCount. */
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

/** Making the @param layerCount depth tree of containers without first layer ("root") and the last, cause there are nodes, not containers.
 * Each container has @param childCount children by default, names of the containers in the current layer are stored in
 * @param parentsNames, their children in @param childrenNames respectively. @param topoContainerSnippets is used for constructing the
 * std::string for std::cout. Do this or not, says @param doOutput. */
void makeContainerTopo(int layerCount, int childCount, vector<string> &parentsNames, vector<string> &childrenNames,
        const array<string, 4> &topoContainerSnippets, bool doOutput)
{
    string outputStr;
    for (int i = 0; i < layerCount; ++i)
    {
        childrenNames.clear();
        for (auto &str: parentsNames)
        {
            for (int j = 0; j < childCount; ++j)
            {
                childrenNames.push_back(str + to_string(j));

                if (doOutput)
                {
                    if (parentsNames.size() == 1 && !i)
                    {
                        outputStr = topoContainerSnippets[0] + "root" + topoContainerSnippets[1] + childrenNames.back()
                                + topoContainerSnippets[2] + childrenNames.back() + topoContainerSnippets[3];
                    }
                    else
                    {
                        outputStr = topoContainerSnippets[0] + str + topoContainerSnippets[1] + childrenNames.back()
                                + topoContainerSnippets[2] + childrenNames.back() + topoContainerSnippets[3];
                    }
                    cout << outputStr;
                }
            }
        }
        parentsNames.swap(childrenNames);
    }
}

int main(int argc, char* argv[])
{
    int layerCount, currentLeafCount, totalLeafCount, componentCount, instanceCount, instanceNumber;
    bool isLinked = false;

#if !DEBUG
//    for (int i = 0; i < argc; ++i)
//    {
//        cout << argv[i] << ' ';
//    }
//    cout << endl << argc << endl;

    if (argc < 11)
    {
        return infoAndExit(argv[0]);
    }
    else
    {
        if (argc == 11)
        {
            array<string, 5> paramNames{argv[1], argv[3], argv[5], argv[7], argv[9]};
            if (!paramNames[0].compare("-n") && !paramNames[1].compare("-lc") && !paramNames[2].compare("-cc")
                    && !paramNames[3].compare("-ic") && !paramNames[4].compare("-in"))
            {
                totalLeafCount = stoi(argv[2]);
                layerCount = stoi(argv[4]);
                componentCount = stoi(argv[6]);
                instanceCount = stoi(argv[8]);
                instanceNumber = stoi(argv[10]);
                currentLeafCount = totalLeafCount / instanceCount + ((instanceNumber == instanceCount) ? (totalLeafCount % instanceCount)
                        : 0);
            }
            else
            {
                return infoAndExit(argv[0]);
            }
        }
        else if (argc == 12)
        {
            array<string, 6> paramNames{argv[1], argv[3], argv[5], argv[7], argv[8], argv[10]};
            if (!paramNames[0].compare("-n") && !paramNames[1].compare("-lc") && !paramNames[2].compare("-cc")
                    && !paramNames[3].compare("-ml") && !paramNames[4].compare("-ic") && !paramNames[5].compare("-in"))
            {
                totalLeafCount = stoi(argv[2]);
                layerCount = stoi(argv[4]);
                componentCount = stoi(argv[6]);
                instanceCount = stoi(argv[9]);
                instanceNumber = stoi(argv[11]);
                if (instanceNumber == instanceCount)
                {
                    isLinked = true;
                }
                currentLeafCount = totalLeafCount / instanceCount + ((instanceNumber == instanceCount) ? (totalLeafCount % instanceCount)
                        : 0);
            }
            else
            {
                return infoAndExit(argv[0]);
            }
        }
        else
        {
            return infoAndExit(argv[0]);
        }
    }
#else
    layerCount = 5;
    componentCount = 10;
    isLinked = false;
    instanceCount = 5;
    instanceNumber = 5;
    totalLeafCount = 100;
    currentLeafCount = totalLeafCount / instanceCount + ((instanceNumber == instanceCount) ? (totalLeafCount % instanceCount) : 0);

    fstream createModels("models.txt", ios::out | ios::trunc);
#endif

    int containerBase = (int)pow((double)totalLeafCount, 1.0 / (double)(layerCount - 1));
#if DEBUG
    cout << "Layer count: " << layerCount << ", node count: " << currentLeafCount << ", log base: " << containerBase << endl;
#endif

    /** Making the container tree *********************************************************************************************************/
    array<string, 4> topoContainerSnippets
    {
        "newModel VariableContainer[parentAddr: Address[\"",
        "\"], baseComponentType: @container, modelAddr: Address[\"",
        "\"], name: \"",
        "\"];\n"
    };
//    string containerStr = "container";
    vector<string> *leafParentsNames = new vector<string>;
    if (layerCount == 2)
    {
        leafParentsNames->emplace_back("root");
    }
    else
    {
        leafParentsNames->emplace_back("container");
    }
    vector<string> *childrenNames = new vector<string>;

    makeContainerTopo(layerCount - 2, containerBase, *leafParentsNames, *childrenNames, topoContainerSnippets,
            instanceNumber == 1);

//    for (int i = 0; i < containerBase; ++i)
//    {
//        if (instanceNumber == 1)
//        {
//            outputStr = topoContainerSnippets[0] + "root" + topoContainerSnippets[1] + containerStr + to_string(i)
//                    + topoContainerSnippets[2] + containerStr + to_string(i) + topoContainerSnippets[3];
//            cout << outputStr;
//        }
//    }

//    for (int i = 0; i < containerBase; ++i)
//    {
//        parentContainerStrings->push_back(containerStr + to_string(i));
//        for (int j = 0; j < containerBase; ++j)
//        {
//            leafParents->push_back((*parentContainerStrings)[i] + to_string(j));
//            if (instanceNumber == 1)
//            {
//                outputStr = topoContainerSnippets[0] + (*parentContainerStrings)[i] + topoContainerSnippets[1]
//                        + (*parentContainerStrings)[i] + to_string(j) + topoContainerSnippets[2] + (*parentContainerStrings)[i]
//                        + to_string(j) + topoContainerSnippets[3];
//                cout << outputStr;
//            }
//        }
//    }

    delete childrenNames;

    /** Making the nodes ******************************************************************************************************************/
    string outputStr;
    array<string, 5> topoLeafSnippets
    {
        "newModel VariableContainer[parentAddr: Address[\"",
        "\"], baseComponentType: @unixHost, modelAddr: Address[\"",
        "\"], name: \"",
        "\", description: \"Unix host ",
        "\"];\n"
    };

    cout << endl;

    int currentLeafParentsSize = leafParentsNames->size() / instanceCount + ((instanceNumber == instanceCount)
            ? (leafParentsNames->size() % instanceCount) : 0);
    if (currentLeafParentsSize < 1)
    {
        currentLeafParentsSize = 1;
    }
    int extraLeafCount = currentLeafCount % currentLeafParentsSize;
    int defaultLeavesInContainer = currentLeafCount / currentLeafParentsSize;
    int leafParentBeginIndex = (instanceNumber - 1) * (leafParentsNames->size() / instanceCount);
    int leafIndex = (instanceNumber - 1) * (totalLeafCount / instanceCount);
    int inc;
    list<int> *leavesIds = new list<int>;
    const string commonLeafName = "unixHost";
    string leafName;
    for (int i = leafParentBeginIndex; i < leafParentBeginIndex + currentLeafParentsSize; ++i)
    {
//        cout << [=](){return (i < extraLeafCount - 1) ? 1 : 0;} << endl;
        inc = (i < leafParentBeginIndex + extraLeafCount) ? 1 : 0;
        for (int j = 0; j < defaultLeavesInContainer + inc; ++j)
        {
            leafName = commonLeafName + to_string(leafIndex);
            leavesIds->push_back(leafIndex);
            outputStr = topoLeafSnippets[0] + (*leafParentsNames)[i] + topoLeafSnippets[1] + leafName + topoLeafSnippets[2] + leafName
                    + topoLeafSnippets[3] + to_string(leafIndex) + topoLeafSnippets[4];
            cout << outputStr;
#if DEBUG
                if (createModels.is_open())
                {
                    createModels << outputStr;
                }
#endif
            leafIndex++;
        }
    }

    delete leafParentsNames;

    /** Making the nodes' components (interfaces, processes, ...) *************************************************************************/
    array<string, 4> topoComponentSnippets
    {
        "newComponent VariableContainer[modelAddr: Address[\"",
        "\"], cTag: \"",
        "\", id: \"",
        "\"];\n"
    };

    const array<pair<string, int>, 4> defaultComponents
    {
        {
#if !DEBUG
            {"interface", componentCount}, // Default interface count is 100
            {"process", componentCount}, // Default process count is 1000
            {"processor", 10}, // Default processor count is 10
            {"diskUtilization", 5} // Default disk count is 5
#else
            {"interface", componentCount},
            {"process", componentCount},
            {"processor", 2},
            {"diskUtilization", 1}
#endif
        }
    };

    cout << endl;

    for (auto& id: *leavesIds)
    {
        for (int i = 0; i < defaultComponents.size(); ++i)
        {
            for (int j = 0; j < defaultComponents[i].second; ++j)
            {
                outputStr = topoComponentSnippets[0] + commonLeafName + to_string(id) + topoComponentSnippets[1]
                        + defaultComponents[i].first + topoComponentSnippets[2] + defaultComponents[i].first + to_string(id) + '_'
                        + to_string(j) + topoComponentSnippets[3];
                cout << outputStr;
#if DEBUG
                if (createModels.is_open())
                {
                    createModels << outputStr;
                }
#endif
            }
        }
    }

    if (instanceNumber == instanceCount)
    {
        /** Making the topology ***********************************************************************************************************/
        int topoBase = logBase(layerCount, totalLeafCount);
        list<list<int>> *topoTree = new list<list<int>>;
        auto leavesNamesIt = leavesIds->cbegin();
        leafIndex = 0;
        int currentNodeCount = 0, currLayerNodeCount, layerIndex = 0;

        while (true)
        {
            currLayerNodeCount = (int)pow((double)topoBase, (double)layerIndex);
            currentNodeCount += currLayerNodeCount;
            if (currentNodeCount <= totalLeafCount)
            {
                topoTree->push_back(list<int>{});
                for (int j = 0; j < currLayerNodeCount; ++j)
                {
                    topoTree->back().push_back(leafIndex);
                    leavesNamesIt++;
                    leafIndex++;
                }
                layerIndex++;
            }
            else
            {
                break;
            }
        }

        for (int i = leafIndex; i < totalLeafCount; ++i)
        {
             topoTree->back().push_back(i);
             leavesNamesIt++;
        }

        delete leavesIds;

        if (isLinked)
        {
            /** Making the connections in the topology ************************************************************************************/
            array<string, 5> topoConnectionSnippets
            {
                "connection VariableContainer[firstModelAddr: Address[\"",
                "\"], secondModelAddr: Address[\"",
                "\"], firstId: \"",
                "\", secondId: \"",
                "\", cTag: \"interface\"];\n"
            };
            string interfaceParentNodePrefix, interfaceChildNodePrefix;

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
                        interfaceParentNodePrefix = defaultComponents[0].first + to_string(*topoParentsIt) + '_' + to_string(i
                                + ((topoLayersIt == topoTree->cbegin()) ? 0 : 1));
                        interfaceChildNodePrefix = defaultComponents[0].first + to_string(*topoChildrenIt) + "_0";
                        outputStr = topoConnectionSnippets[0] + commonLeafName + to_string(*topoParentsIt) + topoConnectionSnippets[1]
                                + commonLeafName + to_string(*topoChildrenIt) + topoConnectionSnippets[2] + interfaceParentNodePrefix
                                + topoConnectionSnippets[3] + interfaceChildNodePrefix + topoConnectionSnippets[4];
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
                    interfaceParentNodePrefix = defaultComponents[0].first + to_string(*topoParentsIt) + '_' + to_string(i + 1);
                    interfaceChildNodePrefix = defaultComponents[0].first + to_string(*topoChildrenIt) + "_0";
                    outputStr = topoConnectionSnippets[0] + commonLeafName + to_string(*topoParentsIt)+ topoConnectionSnippets[1]
                            + commonLeafName + to_string(*topoChildrenIt) + topoConnectionSnippets[2] + interfaceParentNodePrefix
                            + topoConnectionSnippets[3] + interfaceChildNodePrefix + topoConnectionSnippets[4];
                    cout << outputStr;
                    topoChildrenIt++;
                }
            }
        }

        delete topoTree;
    }

#if DEBUG
    getchar();

    createModels.close();
#endif

    return 0;
}
