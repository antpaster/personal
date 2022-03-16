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
#include <thread>
#include <chrono>
#include <random>

#define DEBUG 0

using namespace std;

const string commonLeafName = "unixHost";
const unsigned int linksCreationDelaySec = 5;
const double minLon = 37;
const double maxLon = 39;
const double minLat = 55;
const double maxLat = 56;

inline int infoAndExit(const char *programName)
{
    cerr << "Usage: " << programName << " <option(s)> VALUES"
            << "\nOptions:\n"
            << "\t-n NODE_COUNT [10..50000]\tSpecify total nodes count in the topology\n"
            << "\t-lc LAYER_COUNT [2..NODE_COUNT]\tSpecify layers count in the topology\n"
            << "\t-cc COMPONENT_COUNT [1..1000]\tSpecify processes count and interfaces count in a single node\n"
            << "\t[<-ml MAKE_LINKS> OR <-xcda CONNECT_BY_XCDA_PROTOCOL>]\tIf presents, nodes in the topology will be connected "
               "(by particular protocol, if it's specified). Specify this parameter if INSTANCES_COUNT = INSTANCE_NUMBER\n"
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
void makeContainersTree(int layerCount, int childCount, vector<string> &parentsNames, vector<string> &childrenNames,
        const array<string, 4> &topoContainerSnippets, bool doOutput
#if DEBUG
        , ofstream &creationFile
#endif
        )
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
#if DEBUG
                    if (creationFile.is_open())
                    {
                        creationFile << outputStr;
                    }
#endif
                }
            }
        }
        parentsNames.swap(childrenNames);
    }
}

void connectLeavesInTopology(int topoBase, const list<list<int>> *topoTree, string linkingType,
        const array<string, 9> &topoConnectionSnippets, const array<pair<string, int>, 4> &defaultComponents
#if DEBUG
        , ofstream &creationFile
#endif
        )
{
    /** Making the connections in the topology ************************************************************************************/
    string interfaceParentNodePrefix, interfaceChildNodePrefix, outputStr;

    cout << endl;

    auto topoLayersIt = topoTree->cbegin();
    auto topoChildrenIt = next(topoLayersIt)->cbegin();
    topoLayersIt = prev(topoTree->cend(), 2); // pre-leaf layer
    topoChildrenIt = next(topoLayersIt)->cbegin(); // leaf layer
    int extraLeafCount = next(topoLayersIt)->size() % topoLayersIt->size();
    int defaultLeavesInContainer = next(topoLayersIt)->size() / topoLayersIt->size();
    int inc;

    if (linkingType == "-ml")
    {
        // Making connections for all levels but the last
        //this_thread::sleep_for(chrono::seconds(linksCreationDelaySec)); // delay before links creation
        for (; topoLayersIt != prev(topoTree->cend(), 2); ++topoLayersIt)
        {
            topoChildrenIt = next(topoLayersIt)->cbegin();
            for (auto topoParentsIt = topoLayersIt->cbegin(); topoParentsIt != topoLayersIt->cend(); ++topoParentsIt)
            {
                for (int i = 0; i < topoBase; ++i)
                {

                    // networkLinks for models
                    outputStr = topoConnectionSnippets[0] + commonLeafName + to_string(*topoParentsIt) + topoConnectionSnippets[1]
                            + commonLeafName + to_string(*topoChildrenIt) + topoConnectionSnippets[2] + "attributes"
                            + topoConnectionSnippets[3] + "attributes" + topoConnectionSnippets[4] + "uh"  + to_string(*topoParentsIt)
                            + "<--->uh" + to_string(*topoChildrenIt) + topoConnectionSnippets[5] + "baseComponent"
                            + topoConnectionSnippets[6] + "baseComponent" + topoConnectionSnippets[7] + "networkLink"
                            + topoConnectionSnippets[8];
                    cout << outputStr;
#if DEBUG
                    if (creationFile.is_open())
                    {
                        creationFile << outputStr;
                    }
#endif
                    // networkSubLinks for portEntites in models
                    interfaceParentNodePrefix = defaultComponents[0].first + to_string(*topoParentsIt) + '-' + to_string(i
                            + ((topoLayersIt == topoTree->cbegin()) ? 0 : 1));
                    interfaceChildNodePrefix = defaultComponents[0].first + to_string(*topoChildrenIt) + "-0";
                    outputStr = topoConnectionSnippets[0] + commonLeafName + to_string(*topoParentsIt) + topoConnectionSnippets[1]
                            + commonLeafName + to_string(*topoChildrenIt) + topoConnectionSnippets[2] + interfaceParentNodePrefix
                            + topoConnectionSnippets[3] + interfaceChildNodePrefix + topoConnectionSnippets[4] + "pe"
                            + to_string(*topoParentsIt) + '-' + to_string(i + ((topoLayersIt == topoTree->cbegin()) ? 0 : 1)) + "<--->pe"
                            + to_string(*topoChildrenIt) + "-0" + topoConnectionSnippets[5] + "interface"
                            + topoConnectionSnippets[6] + "interface" + topoConnectionSnippets[7] + "ethLink"
                            + topoConnectionSnippets[8];
                    cout << outputStr;
#if DEBUG
                    if (creationFile.is_open())
                    {
                        creationFile << outputStr;
                    }
#endif
                }
                topoChildrenIt++;
            }
        }

        // Connecting the last level with pre-last
        //this_thread::sleep_for(chrono::seconds(linksCreationDelaySec)); // delay before links creation
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
                // networkLinks for models
                outputStr = topoConnectionSnippets[0] + commonLeafName + to_string(*topoParentsIt)+ topoConnectionSnippets[1]
                        + commonLeafName + to_string(*topoChildrenIt) + topoConnectionSnippets[2] + "attributes" + topoConnectionSnippets[3]
                        + "attributes" + topoConnectionSnippets[4] + "uh"  + to_string(*topoParentsIt) + "<--->uh"
                        + to_string(*topoChildrenIt) + topoConnectionSnippets[5] + "baseComponent"
                        + topoConnectionSnippets[6] + "baseComponent" + topoConnectionSnippets[7] + "networkLink"
                        + topoConnectionSnippets[8];
                cout << outputStr;
#if DEBUG
                if (creationFile.is_open())
                {
                    creationFile << outputStr;
                }
#endif
                // networkSubLinks for portEntites in models
                interfaceParentNodePrefix = defaultComponents[0].first + to_string(*topoParentsIt) + '-' + to_string(i + 1);
                interfaceChildNodePrefix = defaultComponents[0].first + to_string(*topoChildrenIt) + "-0";
                outputStr = topoConnectionSnippets[0] + commonLeafName + to_string(*topoParentsIt)+ topoConnectionSnippets[1]
                        + commonLeafName + to_string(*topoChildrenIt) + topoConnectionSnippets[2] + interfaceParentNodePrefix
                        + topoConnectionSnippets[3] + interfaceChildNodePrefix + topoConnectionSnippets[4] + "pe"
                        + to_string(*topoParentsIt) + '-' + to_string(i + 1) + "<--->pe" + to_string(*topoChildrenIt) + "-0"
                        + topoConnectionSnippets[5] + "interface" + topoConnectionSnippets[6] + "interface" + topoConnectionSnippets[7]
                        + "ethLink" + topoConnectionSnippets[8];
                cout << outputStr;
#if DEBUG
                if (creationFile.is_open())
                {
                    creationFile << outputStr;
                }
#endif
                topoChildrenIt++;
            }
        }
    }
    else if (linkingType == "-xcda")
    {
        for (; topoLayersIt != prev(topoTree->cend(), 2); ++topoLayersIt)
        {
            topoChildrenIt = next(topoLayersIt)->cbegin();
            for (auto topoParentsIt = topoLayersIt->cbegin(); topoParentsIt != topoLayersIt->cend(); ++topoParentsIt)
            {
                for (int i = 0; i < topoBase; ++i)
                {
                    // update ifAliases
                    interfaceParentNodePrefix = defaultComponents[0].first + to_string(*topoParentsIt) + '-' + to_string(i
                            + ((topoLayersIt == topoTree->cbegin()) ? 0 : 1));
                    interfaceChildNodePrefix = defaultComponents[0].first + to_string(*topoChildrenIt) + "-0";
                    outputStr = "updateComponent VariableContainer[modelAddr: Address[" + commonLeafName + to_string(*topoParentsIt)
                            + "], cTag: \"interface\", id: " + interfaceParentNodePrefix + ", ifAlias: \"$" + commonLeafName
                            + to_string(*topoChildrenIt) + '_' + interfaceChildNodePrefix + "$\"];\n";
                    cout << outputStr;
#if DEBUG
                    if (creationFile.is_open())
                    {
                        creationFile << outputStr;
                    }
#endif
                }
                topoChildrenIt++;
            }
        }

        // Connecting the last level with pre-last
        //this_thread::sleep_for(chrono::seconds(linksCreationDelaySec)); // delay before links creation
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
                // update ifAliases
                interfaceParentNodePrefix = defaultComponents[0].first + to_string(*topoParentsIt) + '-' + to_string(i + 1);
                interfaceChildNodePrefix = defaultComponents[0].first + to_string(*topoChildrenIt) + "-0";
                outputStr = "updateComponent VariableContainer[modelAddr: Address[\"" + commonLeafName + to_string(*topoParentsIt)
                        + "\"], cTag: \"interface\", id: \"" + interfaceParentNodePrefix + "\", ifAlias: \"$" + commonLeafName
                        + to_string(*topoChildrenIt) + '_' + interfaceChildNodePrefix + "$\"];\n";
                cout << outputStr;
#if DEBUG
                if (creationFile.is_open())
                {
                    creationFile << outputStr;
                }
#endif
                topoChildrenIt++;
            }
        }
    }
}

void makeLeafTopology(int topoBase, int totalLeafCount, int leafStartIndex, string linkingType,
       const array<pair<string, int>, 4> &defaultComponents
#if DEBUG
       , ofstream &creationFile
#endif
       )
{
    list<list<int>> *topoTree = new list<list<int>>;
    int currentNodeCount = 0, layerIndex = 0, leafCounter = 0, currLayerNodeCount;

    while (true)
    {
        currLayerNodeCount = (int)pow((double)topoBase, (double)layerIndex);
        currentNodeCount += currLayerNodeCount;
        if (currentNodeCount <= totalLeafCount)
        {
            topoTree->push_back(list<int>{});
            for (int j = 0; j < currLayerNodeCount; ++j)
            {
                topoTree->back().push_back(leafStartIndex + leafCounter);
                leafCounter++;
            }
            layerIndex++;
        }
        else
        {
            topoTree->push_back(list<int>{});
            for (int j = leafCounter; j < totalLeafCount; ++j)
            {
                topoTree->back().push_back(leafStartIndex + j);
            }
            break;
        }
    }

    array<string, 9> topoConnectionSnippets
    {
        "connection VariableContainer[firstModelAddr: Address[\"",
        "\"], secondModelAddr: Address[\"",
        "\"], firstId: \"",
        "\", secondId: \"",
        "\", name: \"",
        "\", firstTag: \"",
        "\", secondTag: \"",
        "\", edgeType: @",
        "];\n"
    };

    connectLeavesInTopology(topoBase, topoTree, linkingType, topoConnectionSnippets, defaultComponents
#if DEBUG
            , creationFile);
#else
            );
#endif

    // Connect the topology in one container with the topology in another one
    //this_thread::sleep_for(chrono::seconds(linksCreationDelaySec)); // delay before links creation
    if (leafStartIndex)
    {
        string interfaceParentNodePrefix, interfaceChildNodePrefix, outputStr;
        if (linkingType == "-ml")
        {
            outputStr = topoConnectionSnippets[0] + commonLeafName + to_string(leafStartIndex - 1)+ topoConnectionSnippets[1]
                    + commonLeafName + to_string(leafStartIndex + totalLeafCount - 2) + topoConnectionSnippets[2] + "attributes"
                    + topoConnectionSnippets[3] + "attributes" + topoConnectionSnippets[4] + "uh"  + to_string(leafStartIndex - 1)
                    + "<--->uh" + to_string(leafStartIndex + totalLeafCount - 2) + topoConnectionSnippets[5] + "baseComponent"
                    + topoConnectionSnippets[6] + "baseComponent" + topoConnectionSnippets[7] + "networkLink" + topoConnectionSnippets[8];
        }
        else if (linkingType == "-xcda")
        {
            interfaceParentNodePrefix = defaultComponents[0].first + to_string(leafStartIndex - 1) + "-1";
            interfaceChildNodePrefix = defaultComponents[0].first + to_string(leafStartIndex + totalLeafCount - 2) + "-1";
            outputStr = "updateComponent VariableContainer[modelAddr: Address[\"" + commonLeafName + to_string(leafStartIndex - 1)
                    + "\"], cTag: \"interface\", id: \"" + interfaceParentNodePrefix + "\", ifAlias: \"$" + commonLeafName
                    + to_string(leafStartIndex + totalLeafCount - 2) + '_' + interfaceChildNodePrefix + "$\"];\n";
        }

        cout << outputStr;
#if DEBUG
        if (creationFile.is_open())
        {
            creationFile << outputStr;
        }
#endif
    }

    delete topoTree;
}

int main(int argc, char* argv[])
{
    int layerCount, currentLeafCount, totalLeafCount, componentCount, instanceCount, instanceNumber;
    string linkingType;
    const int usedInterfacesDivisor = 10; // only one tenth of interface amount will be used for connections in topology

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
                    && (!paramNames[3].compare("-ml") || !paramNames[3].compare("-xcda")) && !paramNames[4].compare("-ic")
                    && !paramNames[5].compare("-in"))
            {
                totalLeafCount = stoi(argv[2]);
                layerCount = stoi(argv[4]);
                componentCount = stoi(argv[6]);
                instanceCount = stoi(argv[9]);
                instanceNumber = stoi(argv[11]);
                if (instanceNumber == instanceCount)
                {
                    linkingType = paramNames[3];
                }
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
    layerCount = 3;
    componentCount = 100;
    linkingType = "-xcda";
    instanceCount = 1;
    instanceNumber = 1;
    totalLeafCount = 50;

    ofstream simpleModelsCreation("simpleModelsCreation.txt", ios::trunc);
#endif

    currentLeafCount = totalLeafCount / instanceCount + ((instanceNumber == instanceCount) ? (totalLeafCount % instanceCount) : 0);
    int containerBase = (int)pow((double)totalLeafCount, 1.0 / (double)(layerCount - 1));
#if DEBUG
    cout << "Layer count: " << layerCount << ", node count: " << currentLeafCount << ", log base: " << containerBase << endl;
#endif

    // Writing node count and component count into the file for further using by ModelsParamsTest
    ofstream topoTestParams("topoTestParams.txt", ios::trunc);
    if (topoTestParams.is_open())
    {
        topoTestParams << "Node count = " << totalLeafCount
             << "\nComponent count = " << componentCount
             << "\nInstance count = " << instanceCount
             << "\nInstance number = " << instanceNumber << endl;
    }
    topoTestParams.close();

    /** Making the container tree *********************************************************************************************************/
    array<string, 4> topoContainerSnippets
    {
        "newModel VariableContainer[parentAddr: Address[\"",
        "\"], baseComponentType: @container, modelAddr: Address[\"",
        "\"], name: \"",
        "\"];\n"
    };
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

    makeContainersTree(layerCount - 2, containerBase, *leafParentsNames, *childrenNames, topoContainerSnippets,
            instanceNumber == 1
#if DEBUG
            , simpleModelsCreation
#endif
            );

    delete childrenNames;

    /** Making the nodes ******************************************************************************************************************/
    default_random_engine gen;
    uniform_real_distribution<double> lonDistr(minLon, maxLon);
    uniform_real_distribution<double> latDistr(minLat, maxLat);

    string outputStr;
    array<string, 7> topoLeafSnippets
    {
        "newModel VariableContainer[parentAddr: Address[\"",
        "\"], baseComponentType: @networkDevice, modelAddr: Address[\"",
        "\"], name: \"",
        "\", description: \"Unix host ",
        "\", geoLon: ",
        ", geoLat: ",
        "];\n"
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
    list<int> *leafCountPerContainer = new list<int>;
    string leafName;
    for (int i = leafParentBeginIndex; i < leafParentBeginIndex + currentLeafParentsSize; ++i)
    {
//        cout << [=](){return (i < extraLeafCount - 1) ? 1 : 0;} << endl;
        inc = (i < leafParentBeginIndex + extraLeafCount) ? 1 : 0;
        leafCountPerContainer->push_back(defaultLeavesInContainer + inc);
        for (int j = 0; j < defaultLeavesInContainer + inc; ++j)
        {
            leafName = commonLeafName + to_string(leafIndex);
            leavesIds->push_back(leafIndex);
            outputStr = topoLeafSnippets[0] + (*leafParentsNames)[i] + topoLeafSnippets[1] + leafName + topoLeafSnippets[2] + leafName
                    + topoLeafSnippets[3] + to_string(leafIndex) + topoLeafSnippets[4] + to_string(lonDistr(gen)) + topoLeafSnippets[5]
                    + to_string(latDistr(gen)) + topoLeafSnippets[6];
            cout << outputStr;
#if DEBUG
            if (simpleModelsCreation.is_open())
            {
                simpleModelsCreation << outputStr;
            }
#endif
            leafIndex++;
        }
    }

    delete leafParentsNames;

    /** Making the nodes' components (interfaces, processes, ...) *************************************************************************/
    array<string, 5> topoComponentSnippets
    {
        "newComponent VariableContainer[modelAddr: Address[\"",
        "\"], cTag: \"",
        "\", id: \"",
        "\", name: \"",
        "\"];\n"
    };

    const array<pair<string, int>, 4> defaultComponents
    {
        {
            {"interface", componentCount},
            {"volume", 4},
            {"memory", 1},
            {"cpuLoad", 2}
        }
    };

    cout << endl;

    if (componentCount > 0)
    {
        for (auto& id: *leavesIds)
        {
            for (int i = 0; i < defaultComponents.size(); ++i)
            {
                for (int j = 0; j < defaultComponents[i].second; ++j)
                {
                    outputStr = topoComponentSnippets[0] + commonLeafName + to_string(id) + topoComponentSnippets[1]
                            + defaultComponents[i].first + topoComponentSnippets[2] + defaultComponents[i].first + to_string(id) + '-'
                            + to_string(j) + topoComponentSnippets[3] + defaultComponents[i].first + to_string(id) + '-' + to_string(j)
                            + topoComponentSnippets[4];
                    cout << outputStr;
#if DEBUG
                    if (simpleModelsCreation.is_open())
                    {
                        simpleModelsCreation << outputStr;
                    }
#endif
                }
            }
        }
    }

    delete leavesIds;

    if ((instanceNumber == instanceCount) && (linkingType.size() != 0))
    {
        /** Making the topology ***********************************************************************************************************/
        // Fixed amount of connections, except in the last layer (it's less or equal there)
        int topoBase = componentCount / usedInterfacesDivisor;
        if (!topoBase)
        {
            topoBase = 1;
        }

        this_thread::sleep_for(chrono::seconds(linksCreationDelaySec)); // delay before links creation

        leafIndex = 0;
        for (auto &leafCount: *leafCountPerContainer)
        {
            makeLeafTopology(topoBase, leafCount, leafIndex, linkingType, defaultComponents
#if DEBUG
            , simpleModelsCreation
#endif
            );
            leafIndex += leafCount;
        }

        delete leafCountPerContainer;
    }

#if DEBUG
    getchar();

    simpleModelsCreation.close();
#endif

    return 0;
}
