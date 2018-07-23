#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#include <list>
#include <array>

#define DEBUG 1

using namespace std;

inline int infoAndExit(const char *programName)
{
    cerr << "Usage: " << programName << " <option(s)> VALUES"
            << "\nOptions:\n"
            << "\t-n NODES\tSpecify nodes count in the topology\n"
            << "\t-s SLEEP\tSpecify sleep duration in seconds between models parameters setting"
            << endl;
    return 1;
}

inline int randPercent()
{
    return rand() % 100;
}

inline string randTimeDiff()
{
    int hours = rand() % 24;
    int minutes = rand() % 60;
    int seconds = rand() % 60;
    return "TimeDiff[0 " + to_string(hours) + ':' + to_string(minutes) + ':' + to_string(seconds) + " 0]";
}

string randAsciiIntervalString(int size, int beginCode, int endCode)
{
    char *result = new char[size + 1];
    for (int i = 0; i < size; ++i)
    {
        result[i] = (char)(beginCode + rand() % (endCode - beginCode));
    }
    result[size] = '\0';
    return result;
}

inline string randLocalIp()
{
    return "192.168." + to_string(1 + rand() % 253) + '.' + to_string(1 + rand() % 253);
}

int main(int argc, char* argv[])
{
    int nodeCount, sleepDurationSec;

#if !DEBUG
    if (argc < 5)
    {
        return infoAndExit(argv[0]);
    }
    else
    {
        string nodesParam{argv[1]};
        string sleepParam{argv[3]};
        if (!nodesParam.compare("-n") && !sleepParam.compare("-s"))
        {
            nodeCount = stoi(argv[2]);
            sleepDurationSec = stoi(argv[4]);
        }
        else
        {
            return infoAndExit(argv[0]);
        }
    }
#else
    nodeCount = 20;
    sleepDurationSec = 60;
#endif

    const string commonNodeName = "unixHost";

    list<int> *nodeIds = new list<int>;
    for (int i = 0; i < nodeCount; ++i)
    {
        nodeIds->push_back(i);
    }

    const array<pair<string, int>, 4> defaultComponents
    {
        {
#if !DEBUG
            {"interface", 100}, // Default interface count is 100
            {"process", 100}, // Default process count is 1000
            {"processor", 10}, // Default processor count is 10
            {"diskUtilization", 5} // Default disk count is 5
#else
            {"interface", 5},
            {"process", 10},
            {"processor", 2},
            {"diskUtilization", 1}
#endif
        }
    };

    array<string, 7> updateInterfaceSnippets
    {
        "updateComponent VariableContainer[modelAddr: Address[\"",
        "\"], cTag: \"interface\", id: \"",
        "\", ifIndex: ",
        ", ifType: ",
        ", adminStatus: ",
        ", operStatus: ",
        "];\n"
    };

    array<string, 6> updateProcessSnippets
    {
        "updateComponent VariableContainer[modelAddr: Address[\"",
        "\"], cTag: \"process\", id: \"",
        "\", name: \"",
        "\", description: \"",
        "\", pid: ",
        "];\n"
    };

    array<string, 7> updateProcessorSnippets
    {
        "updateComponent VariableContainer[modelAddr: Address[\"",
        "\"], cTag: \"processor\", id: \"",
        "\", name: \"",
        "\", description: \"",
        "\", frequency: ",
        ", temperature: ",
        "];\n"
    };

    array<string, 12> updateDiskUtilizationSnippets
    {
        "updateComponent VariableContainer[modelAddr: Address[\"",
        "\"], cTag: \"diskUtilization\", id: \"",
        "\", name: \"",
        "\", index: ",
        ", written: ",
        ", read: ",
        ", writeAccesses: ",
        ", readAccesses: ",
        ", loadAverage15: ",
        ", loadAverage5: ",
        ", loadAverage1: ",
        "];\n"
    };

    array<string, 20> updateUnixHostSnippets
    {
        "updateComponent VariableContainer[modelAddr: Address[\"",
        "\"], cTag: \"baseComponent\", id: \"attributes\"",
        ", ip: \"",
//        ", memUtil: ",
//        ", cpuUserTimeInPercentage: ",
//        ", cpuSystemTimeInPercentage: ",
//        ", cpuIdleTimeInPercentage: ",
//        ", cpuUsedTimeInPercentage: ",
        "\", cpuLoad1min: ",
        ", cpuLoad5min: ",
        ", cpuLoad15min: ",
//        ", availRAMpercent: ",
//        ", usedRAMpercent: ",
        ", cpuUserTime: ",
        ", cpuRootTime: ",
        ", cpuSystemTime: ",
        ", cpuIdleTime: ",
        ", totalSwapkb: ",
        ", availSwapkb: ",
        ", totalRAMkb: ",
        ", availRAMkb: ",
        ", usedRAMkb: ",
        ", totalFreekb: ",
        ", totalRAMSharedkb: ",
        ", totalRAMBufferkb: ",
        ", totalCachekb: ",
//        ", pmiThreadStateWaits: ",
//        ", pmiThreadStateInterruptSleep: ",
//        ", statCpuStealPercent: ",
//        ", statCpuSystemPercent: ",
//        ", statCpuNicePercent: ",
//        ", statCpuUserPercent: ",
//        ", statCpuIdlePercent: ",
//        ", statCpuIOWaitPercent: ",
//        ", startTime: ",
//        ", version: ",
//        ", hostname: ",
//        ", apache: ",
//        ", hosts: ",
//        ", iptables: ",
        "];\n"
    };

    long long int writtenLowBound = 5368709120; // 5 Gb in b
    long long int readLowBound = 10737418240; // 10 Gb in b
    int swapLowBound = 536870912; // 512 Gb in kb
    int ramLowBound = 268435456; // 256 Gb in kb
    int swapRand, totalRamRand, availRamRand, usedRamRand;
    int componentCounter = 0;
    string outputStr, componentName;
    while (true)
    {
        srand(time(nullptr));

        for (auto& id: *nodeIds)
        {
            for (int i = 0; i < defaultComponents[0].second; ++i) // interfaces updating
            {
                outputStr = updateInterfaceSnippets[0] + commonNodeName + to_string(id)
                        + updateInterfaceSnippets[1] + defaultComponents[0].first + to_string(id) + '_' + to_string(i) // id
                        + updateInterfaceSnippets[2] + to_string(componentCounter) // ifIndex
                        + updateInterfaceSnippets[3] + to_string(rand() % 6) // ifType
                        + updateInterfaceSnippets[4] + to_string(rand() % 6) // adminStatus
                        + updateInterfaceSnippets[5] + to_string(rand() % 6) // operStatus
                        + updateInterfaceSnippets[6];
                cout << outputStr;
                componentCounter++;
            }
        }

        componentCounter = 0;
        for (auto& id: *nodeIds)
        {
            for (int i = 0; i < defaultComponents[1].second; ++i) // processes updating
            {
                componentName = defaultComponents[1].first + to_string(id) + '_' + to_string(i);
                outputStr = updateProcessSnippets[0] + commonNodeName + to_string(id)
                        + updateProcessSnippets[1] + componentName // id
                        + updateProcessSnippets[2] + componentName // name
                        + updateProcessSnippets[3] + componentName + ' ' + randAsciiIntervalString(15, 97, 122) // description
                        + updateProcessSnippets[4] + to_string(componentCounter) // pid
                        + updateProcessSnippets[5];
                cout << outputStr;
                componentCounter++;
            }
        }

        componentCounter = 0;
        for (auto& id: *nodeIds)
        {
            for (int i = 0; i < defaultComponents[2].second; ++i) // processors updating
            {
                componentName = defaultComponents[2].first + to_string(id) + '_' + to_string(i);
                outputStr = updateProcessorSnippets[0] + commonNodeName + to_string(id)
                        + updateProcessorSnippets[1] + componentName // id
                        + updateProcessorSnippets[2] + componentName // name
                        + updateProcessorSnippets[3] + componentName + ' ' + randAsciiIntervalString(15, 97, 122) // description
                        + updateProcessorSnippets[4] + to_string(2000 + rand() % 2000) // frequency [2000..4000] MHz
                        + updateProcessorSnippets[5] + to_string(20 + rand() % 75) // temperature [20..95] degrees Celcius
                        + updateProcessorSnippets[6];
                cout << outputStr;
                componentCounter++;
            }
        }

        componentCounter = 0;
        for (auto& id: *nodeIds)
        {
            for (int i = 0; i < defaultComponents[3].second; ++i) // diskUtilizations updating
            {
                componentName = defaultComponents[3].first + to_string(id) + '_' + to_string(i);
                outputStr = updateDiskUtilizationSnippets[0] + commonNodeName + to_string(id)
                        + updateDiskUtilizationSnippets[1] + componentName // id
                        + updateDiskUtilizationSnippets[2] + componentName // name
                        + updateDiskUtilizationSnippets[3] + to_string(componentCounter) // index
                        + updateDiskUtilizationSnippets[4] + to_string(writtenLowBound + rand() % writtenLowBound) // written
                        + updateDiskUtilizationSnippets[5] + to_string(readLowBound + rand() % readLowBound) // read
                        + updateDiskUtilizationSnippets[6] + to_string(rand() % 1000) // writeAccesses
                        + updateDiskUtilizationSnippets[7] + to_string(rand() % 1000) // readAccesses
                        + updateDiskUtilizationSnippets[8] + to_string(randPercent()) // loadAverage15
                        + updateDiskUtilizationSnippets[9] + to_string(randPercent()) // loadAverage5
                        + updateDiskUtilizationSnippets[10] + to_string(randPercent()) // loadAverage1
                        + updateDiskUtilizationSnippets[11];
                cout << outputStr;
                componentCounter++;
            }
        }

        for (auto& id: *nodeIds) // unixHost attributes updating
        {
            swapRand = swapLowBound + rand() % swapLowBound; // [512..1024] Gb in kb
            totalRamRand = ramLowBound + rand() % ramLowBound; // [256..512] Gb in kb
            availRamRand = ramLowBound + rand() % (totalRamRand - ramLowBound);
            usedRamRand = ramLowBound + rand() % (availRamRand - ramLowBound);
            outputStr = updateUnixHostSnippets[0] + commonNodeName + to_string(id) + updateUnixHostSnippets[1]
//                    + updateUnixHostSnippets[2] + to_string(randPercent()) // memUtil
//                    + updateUnixHostSnippets[3] + to_string(randPercent()) // cpuUserTimeInPercentage
//                    + updateUnixHostSnippets[4] + to_string(randPercent()) // cpuSystemTimeInPercentage
//                    + updateUnixHostSnippets[5] + to_string(randPercent()) // cpuIdleTimeInPercentage
//                    + updateUnixHostSnippets[6] + to_string(randPercent()) // cpuUsedTimeInPercentage
                    + updateUnixHostSnippets[2] + randLocalIp() // ip
                    + updateUnixHostSnippets[3] + to_string(randPercent()) // cpuLoad1min
                    + updateUnixHostSnippets[4] + to_string(randPercent()) // cpuLoad5min
                    + updateUnixHostSnippets[5] + to_string(randPercent()) // cpuLoad15min
//                    + updateUnixHostSnippets[10] + to_string(100.0 * availRamRand / totalRamRand) // availRAMpercent
//                    + updateUnixHostSnippets[11] + to_string(100.0 * usedRamRand / availRamRand) // usedRAMpercent
                    + updateUnixHostSnippets[6] + randTimeDiff() // cpuUserTime
                    + updateUnixHostSnippets[7] + randTimeDiff() // cpuRootTime
                    + updateUnixHostSnippets[8] + randTimeDiff() // cpuSystemTime
                    + updateUnixHostSnippets[9] + randTimeDiff() // cpuIdleTime
                    + updateUnixHostSnippets[10] + to_string(swapRand) // totalSwapkb
                    + updateUnixHostSnippets[11] + to_string(swapLowBound + rand() % (swapRand - swapLowBound)) // availSwapkb
                    + updateUnixHostSnippets[12] + to_string(totalRamRand) // totalRAMkb
                    + updateUnixHostSnippets[13] + to_string(availRamRand) // availRAMkb
                    + updateUnixHostSnippets[14] + to_string(usedRamRand) // usedRAMkb
                    + updateUnixHostSnippets[15] + to_string(ramLowBound + rand() % (availRamRand - ramLowBound)) // totalFreekb
                    + updateUnixHostSnippets[16] + to_string(ramLowBound + rand() % (availRamRand - ramLowBound)) // totalRAMSharedkb
                    + updateUnixHostSnippets[17] + to_string(ramLowBound + rand() % (availRamRand - ramLowBound)) // totalRAMBufferkb
                    + updateUnixHostSnippets[18] + to_string(randPercent()) // totalCachekb
//                    + updateUnixHostSnippets[25] + to_string(rand() % 10) // pmiThreadStateWaits
//                    + updateUnixHostSnippets[26] + to_string(rand() % 10) // pmiThreadStateInterruptSleep
//                    + updateUnixHostSnippets[27] + to_string(randPercent()) // statCpuStealPercent
//                    + updateUnixHostSnippets[28] + to_string(randPercent()) // statCpuSystemPercent
//                    + updateUnixHostSnippets[29] + to_string(randPercent()) // statCpuNicePercent
//                    + updateUnixHostSnippets[30] + to_string(randPercent()) // statCpuUserPercent
//                    + updateUnixHostSnippets[31] + to_string(randPercent()) // statCpuIdlePercent
//                    + updateUnixHostSnippets[32] + to_string(randPercent()) // statCpuIOWaitPercent
//                    + updateUnixHostSnippets[33] + randAsciiIntervalString(10, 48, 57) // startTime
//                    + updateUnixHostSnippets[34] + randAsciiIntervalString(15, 97, 122) // version
//                    + updateUnixHostSnippets[35] + randAsciiIntervalString(15, 97, 122) // hostname
//                    + updateUnixHostSnippets[36] + randAsciiIntervalString(15, 97, 122) // apache
//                    + updateUnixHostSnippets[37] + randAsciiIntervalString(15, 97, 122) // hosts
//                    + updateUnixHostSnippets[38] + randAsciiIntervalString(15, 97, 122) // iptables
                    + updateUnixHostSnippets[19];
            cout << outputStr;
        }

        cout << endl;

        this_thread::sleep_for(chrono::seconds(sleepDurationSec)); // sleep for sleepDurationSec
    }

    delete nodeIds;

    return 0;
}
