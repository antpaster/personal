#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#include <list>
#include <array>

#define DEBUG 0

using namespace std;

inline int infoAndExit(const char *programName)
{
    cerr << "Usage: " << programName << " <option(s)> VALUES"
            << "\nOptions:\n"
            << "\t-n NODE_COUNT [10..50000]\tSpecify nodes count in the topology\n"
            << "\t-cc COMPONENT_COUNT [1..1000]\tSpecify processes count and interfaces count in a single node\n"
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
    return "192.168." + to_string(1 + rand() % 254) + '.' + to_string(1 + rand() % 254);
}

string randMacAddress()
{
    string result;
    for (int i = 0; i < 6; ++i)
    {
        result += to_string(rand() % 10) + randAsciiIntervalString(1, 65, 71);
        if (i < 5)
        {
            result += ' ';
        }
    }
    return result;
}

int main(int argc, char* argv[])
{
    int nodeCount, componentCount, sleepDurationSec;

#if !DEBUG
    if (argc != 7)
    {
        return infoAndExit(argv[0]);
    }
    else
    {
        array<string, 3> paramNames{argv[1], argv[3], argv[5]};
        if (!paramNames[0].compare("-n") && !paramNames[1].compare("-cc") && !paramNames[2].compare("-s"))
        {
            nodeCount = stoi(argv[2]);
            componentCount = stoi(argv[4]);
            sleepDurationSec = stoi(argv[6]);
        }
        else
        {
            return infoAndExit(argv[0]);
        }
    }
#else
    nodeCount = 20;
    componentCount = 5;
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
            {"interface", componentCount}, // Default interface count is 100
            {"process", componentCount}, // Default process count is 1000
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

    array<string, 44> updateInterfaceSnippets
    {
        "updateComponent VariableContainer[modelAddr: Address[\"",
        "\"], cTag: \"interface\", ifIndex: ",
        ", ifType: ",
        ", ifName: \"",
        "\", description: \"",
        "\", operStatus: ",
        ", adminStatus: ",
        ", ipAddress: \"",
        "\", ifMtu: ",
        ", physAddress: \"",
        "\", speed: ",
        ", trunkDynamicState: \"",
        "\", trunkDynamicStatus: \"",
        "\", ifInOctets: ",
        ", ifInUcastPkts: ",
        ", ifInNUcastPkts: ",
        ", ifInDiscards: ",
        ", ifInErrors: ",
        ", ifInUnknownProtos: ",
        ", ifOutOctets: ",
        ", ifOutUcastPkts: ",
        ", ifOutNUcastPkts: ",
        ", ifOutDiscards: ",
        ", ifOutErrors: ",
        ", ifOutQLen: ",
        ", ifSpecific: ",
        ", ifAlias: \"",
        "\", neighbour: \"",
        "\", ifInMulticastPkts: ",
        ", ifInBroadcastPkts: ",
        ", ifOutMulticastPkts: ",
        ", ifOutBroadcastPkts: ",
        ", ifHCInOctets: ",
        ", ifHCInUcastPkts: ",
        ", ifHCInMulticastPkts: ",
        ", ifHCInBroadcastPkts: ",
        ", ifHCOutOctets: ",
        ", ifHCOutUcastPkts: ",
        ", ifHCOutMulticastPkts: ",
        ", ifHCOutBroadcastPkts: ",
        ", ifHighSpeed: ",
        ", dot3StatsDuplexStatus: \"",
        "\", vlan: \"",
        "\"];\n"
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
    int ifSpeed;
    int componentCounter = 0;
    string outputStr, componentName;
    while (true)
    {
        srand(time(nullptr));

        for (auto& id: *nodeIds)
        {
            for (int i = 0; i < defaultComponents[0].second; ++i) // interfaces updating
            {
                ifSpeed = rand() % 65536;
                outputStr = updateInterfaceSnippets[0] + commonNodeName + to_string(id)
                        + updateInterfaceSnippets[1] + to_string(componentCounter) // ifIndex
                        + updateInterfaceSnippets[2] + to_string(rand() % 6) // ifType
                        + updateInterfaceSnippets[3] + defaultComponents[0].first + to_string(componentCounter) // ifName
                        + updateInterfaceSnippets[4] + randAsciiIntervalString(20, 97, 123) // description
                        + updateInterfaceSnippets[5] + to_string(rand() % 6) // operStatus
                        + updateInterfaceSnippets[6] + to_string(rand() % 6) // adminStatus
                        + updateInterfaceSnippets[7] + randLocalIp() // ipAddress
                        + updateInterfaceSnippets[8] + to_string(68 + rand() % (65536 - 68)) // ifMtu
                        + updateInterfaceSnippets[9] + randMacAddress() // physAddress
                        + updateInterfaceSnippets[10] + to_string(ifSpeed) // speed
                        + updateInterfaceSnippets[11] + randAsciiIntervalString(15, 97, 123) // trunkDynamicState
                        + updateInterfaceSnippets[12] + randAsciiIntervalString(15, 97, 123) // trunkDynamicStatus
                        + updateInterfaceSnippets[13] + to_string(rand() % 65536) // ifInOctets
                        + updateInterfaceSnippets[14] + to_string(rand() % 65536) // ifInUcastPkts
                        + updateInterfaceSnippets[15] + to_string(rand() % 65536) // ifInNUcastPkts
                        + updateInterfaceSnippets[16] + to_string(rand() % 65536) // ifInDiscards
                        + updateInterfaceSnippets[17] + to_string(rand() % 65536) // ifInErrors
                        + updateInterfaceSnippets[18] + to_string(rand() % 65536) // ifInUnknownProtos
                        + updateInterfaceSnippets[19] + to_string(rand() % 65536) // ifOutOctets
                        + updateInterfaceSnippets[20] + to_string(rand() % 65536) // ifOutUcastPkts
                        + updateInterfaceSnippets[21] + to_string(rand() % 65536) // ifOutNUcastPkts
                        + updateInterfaceSnippets[22] + to_string(rand() % 65536) // ifOutDiscards
                        + updateInterfaceSnippets[23] + to_string(rand() % 65536) // ifOutErrors
                        + updateInterfaceSnippets[24] + to_string(rand() % 65536) // ifOutQLen
                        + updateInterfaceSnippets[25] + to_string(rand() % 65536) // ifSpecific
                        + updateInterfaceSnippets[26] + randAsciiIntervalString(15, 97, 123) // ifAlias
                        + updateInterfaceSnippets[27] + randLocalIp() // neighbour
                        + updateInterfaceSnippets[28] + to_string(rand() % 65536) // ifInMulticastPkts
                        + updateInterfaceSnippets[29] + to_string(rand() % 65536) // ifInBroadcastPkts
                        + updateInterfaceSnippets[30] + to_string(rand() % 65536) // ifOutMulticastPkts
                        + updateInterfaceSnippets[31] + to_string(rand() % 65536) // ifOutBroadcastPkts
                        + updateInterfaceSnippets[32] + to_string(rand() % 65536) // ifHCInOctets
                        + updateInterfaceSnippets[33] + to_string(rand() % 65536) // ifHCInUcastPkts
                        + updateInterfaceSnippets[34] + to_string(rand() % 65536) // ifHCInMulticastPkts
                        + updateInterfaceSnippets[35] + to_string(rand() % 65536) // ifHCInBroadcastPkts
                        + updateInterfaceSnippets[36] + to_string(rand() % 65536) // ifHCOutOctets
                        + updateInterfaceSnippets[37] + to_string(rand() % 65536) // ifHCOutUcastPkts
                        + updateInterfaceSnippets[38] + to_string(rand() % 65536) // ifHCOutMulticastPkts
                        + updateInterfaceSnippets[39] + to_string(rand() % 65536) // ifHCOutBroadcastPkts
                        + updateInterfaceSnippets[40] + to_string(ifSpeed + rand() % (65536 - ifSpeed)) // ifHighSpeed
                        + updateInterfaceSnippets[41] + randAsciiIntervalString(15, 97, 123) // dot3StatsDuplexStatus
                        + updateInterfaceSnippets[42] + randAsciiIntervalString(15, 97, 123) // vlan
                        + updateInterfaceSnippets[43];
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
                        + updateProcessSnippets[3] + componentName + ' ' + randAsciiIntervalString(15, 97, 123) // description
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
                        + updateProcessorSnippets[3] + componentName + ' ' + randAsciiIntervalString(15, 97, 123) // description
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
//                    + updateUnixHostSnippets[33] + randAsciiIntervalString(10, 48, 58) // startTime
//                    + updateUnixHostSnippets[34] + randAsciiIntervalString(15, 97, 123) // version
//                    + updateUnixHostSnippets[35] + randAsciiIntervalString(15, 97, 123) // hostname
//                    + updateUnixHostSnippets[36] + randAsciiIntervalString(15, 97, 123) // apache
//                    + updateUnixHostSnippets[37] + randAsciiIntervalString(15, 97, 123) // hosts
//                    + updateUnixHostSnippets[38] + randAsciiIntervalString(15, 97, 123) // iptables
                    + updateUnixHostSnippets[19];
            cout << outputStr;
        }

        cout << endl;

        this_thread::sleep_for(chrono::seconds(sleepDurationSec)); // sleep for sleepDurationSec
    }

    delete nodeIds;

    return 0;
}
