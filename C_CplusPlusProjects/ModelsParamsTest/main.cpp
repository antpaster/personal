#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <csignal>

#include <list>
#include <vector>
#include <array>

#define DEBUG 0
#define NO_CONFIG 1

using namespace std;

volatile sig_atomic_t doExit = 0;

void signalHandler(int sigNum)
{
#if DEBUG
    cout << "\nProgram finished by " << sigNum << " signal.\n";
#endif

    doExit = 1;
}

inline int infoAndExit(const char *programName)
{
    cerr << "Usage: " << programName << " <option(s)> VALUES"
            << "\nOptions:\n"
#if NO_CONFIG
            << "\t-n NODE_COUNT [10..50000]\tSpecify total nodes count in the topology\n"
            << "\t-cc COMPONENT_COUNT [1..1000]\tSpecify processes count and interfaces count in a single node\n"
#endif
            << "\t-s SLEEP\tSpecify sleep duration in seconds between models parameters setting"
            << "\t-ic INSTANCES_COUNT [1..5]\tSpecify total instances of this program to be launched\n"
            << "\t-in INSTANCE_NUMBER [1..INSTANCES_COUNT]\tSpecify current running instance number\n"
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
    char *charStr = new char[size + 1];
    for (int i = 0; i < size; ++i)
    {
        charStr[i] = (char)(beginCode + rand() % (endCode - beginCode));
    }
    charStr[size] = '\0';

    string result{charStr};

    delete [] charStr;

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

inline string quoteString(string str)
{
    return '\"' + str + '\"';
}

void parseParamsFromFile(int &totalNodeCount, int &componentCount, int &instanceCount, int &instanceNumber)
{
    ifstream topoTestParams("topoTestParams.txt");
    vector<string> lines;
    string line;
    size_t equalSignIndex;
    if (topoTestParams.is_open())
    {
        while(getline(topoTestParams, line))
        {
            equalSignIndex = line.find_last_of('=');
            lines.push_back(line.substr(equalSignIndex + 2));
        }

        if (lines.size() == 4)
        {
            totalNodeCount = stoi(lines[0]);
            componentCount = stoi(lines[1]);
            instanceCount = stoi(lines[2]);
            instanceNumber = stoi(lines[3]);
        }
    }
    topoTestParams.close();
}

int main(int argc, char* argv[])
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = signalHandler;
    sigaction(SIGINT, &action, nullptr);

    signal(SIGINT, signalHandler);

    int currentNodeCount, totalNodeCount, componentCount, sleepDurationSec, instanceCount, instanceNumber;

#if !DEBUG
#if NO_CONFIG
    // Without topoTestParams.txt
    if (argc != 11)
    {
        return infoAndExit(argv[0]);
    }
    else
    {
        array<string, 5> paramNames{argv[1], argv[3], argv[5], argv[7], argv[9]};
        if (!paramNames[0].compare("-n") && !paramNames[1].compare("-cc") && !paramNames[2].compare("-s") && !paramNames[3].compare("-ic")
                && !paramNames[4].compare("-in"))
        {
            totalNodeCount = stoi(argv[2]);
            componentCount = stoi(argv[4]);
            sleepDurationSec = stoi(argv[6]);
            instanceCount = stoi(argv[8]);
            instanceNumber = stoi(argv[10]);
        }
        else
        {
            return infoAndExit(argv[0]);
        }
    }
#else
    // With topoTestParams.txt
    if (argc != 3)
    {
        return infoAndExit(argv[0]);
    }
    else
    {
        string paramName{argv[1]};
        if (!paramName.compare("-s"))
        {
            sleepDurationSec = stoi(argv[2]);
        }
        else
        {
            return infoAndExit(argv[0]);
        }
    }
#endif
#else
    totalNodeCount = 300;
    componentCount = 10;
    sleepDurationSec = 36;
    instanceCount = 3;
    instanceNumber = 1;
#endif

#if !NO_CONFIG
    parseParamsFromFile(totalNodeCount, componentCount, instanceCount, instanceNumber);
#endif

    const string commonNodeName = "unixHost";
    currentNodeCount = totalNodeCount / instanceCount + ((instanceNumber == instanceCount) ? (totalNodeCount % instanceCount) : 0);

    list<int> *nodeIds = new list<int>;
    int nodeBeginIndex = (instanceNumber - 1) * (totalNodeCount / instanceCount);
    for (int i = nodeBeginIndex; i < nodeBeginIndex + currentNodeCount; ++i)
    {
        nodeIds->push_back(i);
    }

    const array<pair<string, int>, 4> defaultComponents
    {
        {
//#if !DEBUG
            {"interface", componentCount}, // Default interface count is 100
            {"process", componentCount}, // Default process count is 1000
            {"processor", 1}, // Default processor count is 10
            {"diskUtilization", 1} // Default disk count is 5
//#else
//            {"interface", 5},
//            {"process", 10},
//            {"processor", 2},
//            {"diskUtilization", 1}
//#endif
        }
    };

    array<string, 45> updateInterfaceSnippets
    {
        "updateComponent VariableContainer[modelAddr: Address[\"",
        "\"], cTag: \"interface\", id: ",
        ", ifIndex: ",
        ", ifType: ",
        ", ifName: ",
        ", description: ",
        ", operStatus: ",
        ", adminStatus: ",
        ", ipAddress: ",
        ", ifMtu: ",
        ", physAddress: ",
        ", speed: ",
        ", trunkDynamicState: ",
        ", trunkDynamicStatus: ",
        ", ifInOctets: ",
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
        ", ifAlias: ",
        ", neighbour: ",
        ", ifInMulticastPkts: ",
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
        ", dot3StatsDuplexStatus: ",
        ", vlan: ",
        "];\n"
    };

    array<string, 6> updateProcessSnippets
    {
        "updateComponent VariableContainer[modelAddr: Address[",
        "], cTag: \"process\", id: ",
        ", name: ",
        ", description: ",
        ", pid: ",
        "];\n"
    };

    array<string, 7> updateProcessorSnippets
    {
        "updateComponent VariableContainer[modelAddr: Address[",
        "], cTag: \"processor\", id: ",
        ", name: ",
        ", description: ",
        ", frequency: ",
        ", temperature: ",
        "];\n"
    };

    array<string, 12> updateDiskUtilizationSnippets
    {
        "updateComponent VariableContainer[modelAddr: Address[",
        "], cTag: \"diskUtilization\", id: ",
        ", name: ",
        ", diskIndex: ",
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
        "updateComponent VariableContainer[modelAddr: Address[",
        "], cTag: \"baseComponent\", id: \"attributes\"",
        ", ip: ",
//        ", memUtil: ",
//        ", cpuUserTimeInPercentage: ",
//        ", cpuSystemTimeInPercentage: ",
//        ", cpuIdleTimeInPercentage: ",
//        ", cpuUsedTimeInPercentage: ",
        ", cpuLoad1min: ",
        ", cpuLoad5min: ",
        ", cpuLoad15min: ",
//        ", availRamPercent: ",
//        ", usedRamPercent: ",
        ", cpuUserTime: ",
        ", cpuRootTime: ",
        ", cpuSystemTime: ",
        ", cpuIdleTime: ",
        ", totalSwapKb: ",
        ", availSwapKb: ",
        ", totalRamKb: ",
        ", availRamKb: ",
        ", usedRamKb: ",
        ", totalFreeKb: ",
        ", totalRamSharedKb: ",
        ", totalRamBufferKb: ",
        ", totalCacheKb: ",
//        ", pmiThreadStateWaits: ",
//        ", pmiThreadStateInterruptSleep: ",
//        ", statCpuStealPercent: ",
//        ", statCpuSystemPercent: ",
//        ", statCpuNicePercent: ",
//        ", statCpuUserPercent: ",
//        ", statCpuIdlePercent: ",
//        ", statCpuIoWaitPercent: ",
//        ", startTime: ",
//        ", version: ",
//        ", hostName: ",
//        ", apache: ",
//        ", hosts: ",
//        ", ipTables: ",
        "];\n"
    };

    int oneNodeComponentCount = 1; // for node attributes
    for (int i = 0; i < defaultComponents.size(); ++i)
    {
        oneNodeComponentCount +=  defaultComponents[i].second;
    }
    double singleUpdateStringDelayMcs = sleepDurationSec * 1e06;
    singleUpdateStringDelayMcs /= (nodeIds->size() * oneNodeComponentCount);
#if DEBUG
    double delaysSumMcs = 0;
#endif

    long long int writtenLowBound = 5368709120; // 5 Gb in b
    long long int readLowBound = 10737418240; // 10 Gb in b
    int swapLowBound = 536870912; // 512 Gb in kb
    int ramLowBound = 268435456; // 256 Gb in kb
    int swapRand, totalRamRand, availRamRand, usedRamRand;
    int ifSpeed;
    int componentCounter = 0;
    string outputStr, componentName;
    while (!doExit)
    {
        srand(time(nullptr));

        for (auto& id: *nodeIds)
        {
            for (int i = 0; i < defaultComponents[0].second; ++i) // interfaces updating
            {
                componentName = defaultComponents[0].first + to_string(id) + '_' + to_string(i);
                ifSpeed = rand() % 65536;
                outputStr = updateInterfaceSnippets[0] + commonNodeName + to_string(id)
                        + updateInterfaceSnippets[1] + quoteString(componentName) // id
                        + updateInterfaceSnippets[2] + to_string(componentCounter) // ifIndex
                        + updateInterfaceSnippets[3] + to_string(rand() % 6) // ifType
                        + updateInterfaceSnippets[4] + quoteString(componentName) // ifName
                        + updateInterfaceSnippets[5]
                        + quoteString(componentName + ' ' + randAsciiIntervalString(15, 97, 123)) // description
                        + updateInterfaceSnippets[6] + to_string(rand() % 3) // operStatus
                        + updateInterfaceSnippets[7] + to_string(rand() % 3) // adminStatus
                        + updateInterfaceSnippets[8] + quoteString(randLocalIp()) // ipAddress
                        + updateInterfaceSnippets[9] + to_string(68 + rand() % (65536 - 68)) // ifMtu
                        + updateInterfaceSnippets[10] + quoteString(randMacAddress()) // physAddress
                        + updateInterfaceSnippets[11] + to_string(ifSpeed) // speed
                        + updateInterfaceSnippets[12] + quoteString(randAsciiIntervalString(15, 97, 123)) // trunkDynamicState
                        + updateInterfaceSnippets[13] + quoteString(randAsciiIntervalString(15, 97, 123)) // trunkDynamicStatus
                        + updateInterfaceSnippets[14] + to_string(rand() % 65536) // ifInOctets
                        + updateInterfaceSnippets[15] + to_string(rand() % 65536) // ifInUcastPkts
                        + updateInterfaceSnippets[16] + to_string(rand() % 65536) // ifInNUcastPkts
                        + updateInterfaceSnippets[17] + to_string(rand() % 65536) // ifInDiscards
                        + updateInterfaceSnippets[18] + to_string(rand() % 65536) // ifInErrors
                        + updateInterfaceSnippets[19] + to_string(rand() % 65536) // ifInUnknownProtos
                        + updateInterfaceSnippets[20] + to_string(rand() % 65536) // ifOutOctets
                        + updateInterfaceSnippets[21] + to_string(rand() % 65536) // ifOutUcastPkts
                        + updateInterfaceSnippets[22] + to_string(rand() % 65536) // ifOutNUcastPkts
                        + updateInterfaceSnippets[23] + to_string(rand() % 65536) // ifOutDiscards
                        + updateInterfaceSnippets[24] + to_string(rand() % 65536) // ifOutErrors
                        + updateInterfaceSnippets[25] + to_string(rand() % 65536) // ifOutQLen
                        + updateInterfaceSnippets[26] + to_string(rand() % 65536) // ifSpecific
                        + updateInterfaceSnippets[27] + quoteString(randAsciiIntervalString(15, 97, 123)) // ifAlias
                        + updateInterfaceSnippets[28] + quoteString(randLocalIp()) // neighbour
                        + updateInterfaceSnippets[29] + to_string(rand() % 65536) // ifInMulticastPkts
                        + updateInterfaceSnippets[30] + to_string(rand() % 65536) // ifInBroadcastPkts
                        + updateInterfaceSnippets[31] + to_string(rand() % 65536) // ifOutMulticastPkts
                        + updateInterfaceSnippets[32] + to_string(rand() % 65536) // ifOutBroadcastPkts
                        + updateInterfaceSnippets[33] + to_string(rand() % 65536) // ifHCInOctets
                        + updateInterfaceSnippets[34] + to_string(rand() % 65536) // ifHCInUcastPkts
                        + updateInterfaceSnippets[35] + to_string(rand() % 65536) // ifHCInMulticastPkts
                        + updateInterfaceSnippets[36] + to_string(rand() % 65536) // ifHCInBroadcastPkts
                        + updateInterfaceSnippets[37] + to_string(rand() % 65536) // ifHCOutOctets
                        + updateInterfaceSnippets[38] + to_string(rand() % 65536) // ifHCOutUcastPkts
                        + updateInterfaceSnippets[39] + to_string(rand() % 65536) // ifHCOutMulticastPkts
                        + updateInterfaceSnippets[40] + to_string(rand() % 65536) // ifHCOutBroadcastPkts
                        + updateInterfaceSnippets[41] + to_string(ifSpeed + rand() % (65536 - ifSpeed)) // ifHighSpeed
                        + updateInterfaceSnippets[42] + quoteString(randAsciiIntervalString(15, 97, 123)) // dot3StatsDuplexStatus
                        + updateInterfaceSnippets[43] + quoteString(randAsciiIntervalString(15, 97, 123)) // vlan
                        + updateInterfaceSnippets[44];
                cout << outputStr;
                componentCounter++;

                this_thread::sleep_for(chrono::microseconds((unsigned int)singleUpdateStringDelayMcs));
#if DEBUG
                delaysSumMcs += singleUpdateStringDelayMcs;
                cout << delaysSumMcs << ": ";
#endif
            }
        }

        if (doExit)
        {
            break;
        }

        componentCounter = 0;
        for (auto& id: *nodeIds)
        {
            for (int i = 0; i < defaultComponents[1].second; ++i) // processes updating
            {
                componentName = defaultComponents[1].first + to_string(id) + '_' + to_string(i);
                outputStr = updateProcessSnippets[0] + quoteString(commonNodeName + to_string(id))
                        + updateProcessSnippets[1] + quoteString(componentName) // id
                        + updateProcessSnippets[2] + quoteString(componentName) // name
                        + updateProcessSnippets[3] + quoteString(componentName + ' ' + randAsciiIntervalString(15, 97, 123)) // description
                        + updateProcessSnippets[4] + to_string(componentCounter) // pid
                        + updateProcessSnippets[5];
                cout << outputStr;
                componentCounter++;

                this_thread::sleep_for(chrono::microseconds((unsigned int)singleUpdateStringDelayMcs));
#if DEBUG
                delaysSumMcs += singleUpdateStringDelayMcs;
                cout << delaysSumMcs << ": ";
#endif
            }
        }

        if (doExit)
        {
            break;
        }

        for (auto& id: *nodeIds)
        {
            for (int i = 0; i < defaultComponents[2].second; ++i) // processors updating
            {
                componentName = defaultComponents[2].first + to_string(id) + '_' + to_string(i);
                outputStr = updateProcessorSnippets[0] + quoteString(commonNodeName + to_string(id))
                        + updateProcessorSnippets[1] + quoteString(componentName) // id
                        + updateProcessorSnippets[2] + quoteString(componentName) // name
                        + updateProcessorSnippets[3] + quoteString(componentName + ' ' + randAsciiIntervalString(15, 97, 123)) // description
                        + updateProcessorSnippets[4] + to_string(2000 + rand() % 2000) // frequency [2000..4000] MHz
                        + updateProcessorSnippets[5] + to_string(20 + rand() % 75) // temperature [20..95] degrees Celcius
                        + updateProcessorSnippets[6];
                cout << outputStr;

                this_thread::sleep_for(chrono::microseconds((unsigned int)singleUpdateStringDelayMcs));
#if DEBUG
                delaysSumMcs += singleUpdateStringDelayMcs;
                cout << delaysSumMcs << ": ";
#endif
            }
        }

        if (doExit)
        {
            break;
        }

        componentCounter = 0;
        for (auto& id: *nodeIds)
        {
            for (int i = 0; i < defaultComponents[3].second; ++i) // diskUtilizations updating
            {
                componentName = defaultComponents[3].first + to_string(id) + '_' + to_string(i);
                outputStr = updateDiskUtilizationSnippets[0] + quoteString(commonNodeName + to_string(id))
                        + updateDiskUtilizationSnippets[1] + quoteString(componentName) // id
                        + updateDiskUtilizationSnippets[2] + quoteString(componentName) // name
                        + updateDiskUtilizationSnippets[3] + to_string(componentCounter) // diskIndex
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

                this_thread::sleep_for(chrono::microseconds((unsigned int)singleUpdateStringDelayMcs));
#if DEBUG
                delaysSumMcs += singleUpdateStringDelayMcs;
                cout << delaysSumMcs << ": ";
#endif
            }
        }

        if (doExit)
        {
            break;
        }

        for (auto& id: *nodeIds) // unixHost attributes updating
        {
            swapRand = swapLowBound + rand() % swapLowBound; // [512..1024] Gb in kb
            totalRamRand = ramLowBound + rand() % ramLowBound; // [256..512] Gb in kb
            availRamRand = ramLowBound + rand() % (totalRamRand - ramLowBound);
            usedRamRand = ramLowBound + rand() % (availRamRand - ramLowBound);
            outputStr = updateUnixHostSnippets[0] + quoteString(commonNodeName + to_string(id)) + updateUnixHostSnippets[1]
//                    + updateUnixHostSnippets[2] + to_string(randPercent()) // memUtil
//                    + updateUnixHostSnippets[3] + to_string(randPercent()) // cpuUserTimeInPercentage
//                    + updateUnixHostSnippets[4] + to_string(randPercent()) // cpuSystemTimeInPercentage
//                    + updateUnixHostSnippets[5] + to_string(randPercent()) // cpuIdleTimeInPercentage
//                    + updateUnixHostSnippets[6] + to_string(randPercent()) // cpuUsedTimeInPercentage
//                    + updateUnixHostSnippets[2] + quoteString(randLocalIp()) // ip
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

            this_thread::sleep_for(chrono::microseconds((unsigned int)singleUpdateStringDelayMcs));
#if DEBUG
                delaysSumMcs += singleUpdateStringDelayMcs;
                cout << delaysSumMcs << ": ";
#endif
        }

#if DEBUG
        cout << "Total updates time mcs " << delaysSumMcs << endl;
        delaysSumMcs = 0;
#endif
    }
#if DEBUG
    cout << "\nResource releasing...\n";
#endif

    delete nodeIds;

    return 0;
}
