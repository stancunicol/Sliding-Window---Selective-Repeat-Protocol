#include <iostream>
#include "Sender.h"
#include "Receiver.h"
#include "Package.h"
#include <random>
#include <unordered_set>
#include <chrono>
#include <thread>

int ReadNumberOfPackages() {
    int numberOfPackages;
    std::cout << "Enter the number of packages: ";
    std::cin >> numberOfPackages;
    return numberOfPackages;
}

void DisplayPackages(const int& numberOfPackages) {
    std::cout << "Packages: ";
    for (int i = 1; i <= numberOfPackages; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int GenerateWindowSize(const int& numberOfPackages) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, std::min(5, numberOfPackages / 2));
    return dis(gen);
}

void DisplayCurrentWindow(const int& firstPackage, const int& lastPackage, const int& numberOfPackages) {
    std::cout << "Current window: [";
    for (int i = firstPackage; i <= lastPackage && i <= numberOfPackages; i++) {
        std::cout << i;
        if (i != lastPackage && i != numberOfPackages) {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

static float GenerateTime(const float& maxTime) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.1, maxTime);
    return dis(gen);
}

void DeterminePackagesToSend(Sender& sender, const int& numberOfPackages) {
    for (int i = 1; i <= numberOfPackages; i++) {
        sender.SendPackage({ i, false, GenerateTime(5.0) });
    }
}

void DisplayTimeForPackages(Sender& sender) {
    std::cout << "Time for packages: ";
    for (const auto& pkg : sender.GetPackages()) {
        std::cout << pkg.GetId() << " " << pkg.GetTime() << "\n";
    }
    std::cout << std::endl;
}

void SelectiveRepeat(Sender& sender, Receiver& receiver, const int& numberOfPackages) {
    std::unordered_set<int> ackedPackages;
    int windowStart = 1;
    const float timeout = sender.GetTimeToWait();
    std::vector<bool> sendedPackages(numberOfPackages + 1, false);

    DisplayTimeForPackages(sender);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    while (windowStart <= numberOfPackages) {
        int windowEnd = std::min(windowStart + sender.GetWindowSize() - 1, numberOfPackages);

        sender.DisplayPackages();
        receiver.DisplayReceivedPackages();
        DisplayCurrentWindow(windowStart, windowEnd, numberOfPackages);

        std::vector<Package>& packages = sender.GetPackagesRef();

        for (int i = windowStart; i <= windowEnd && i <= numberOfPackages; i++) {
            if (!sendedPackages[i]) {
                std::cout << "sending package " << i << "... (time: "
                    << packages[i - 1].GetTime() << ")\n";
                sendedPackages[i] = true;
            }
        }

        std::vector<std::pair<int, float>> unackedPackets;
        for (int i = windowStart; i <= windowEnd && i <= numberOfPackages; i++) {
            if (ackedPackages.find(i) == ackedPackages.end()) {
                unackedPackets.emplace_back(i, packages[i - 1].GetTime());
            }
        }

        if (unackedPackets.empty()) {
            windowStart = windowEnd + 1;
            continue;
        }

        std::sort(unackedPackets.begin(), unackedPackets.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; });

        bool windowSlid = false;
        for (auto& pkg : unackedPackets) {
            int pkgId = pkg.first;
            float pkgTime = pkg.second;

            if (pkgTime < timeout) {
                std::cout << "received ack for package " << pkgId << "\n";
                ackedPackages.insert(pkgId);
                receiver.ReceivePackage(packages[pkgId - 1]);

                if (windowStart <= numberOfPackages && ackedPackages.find(windowStart) != ackedPackages.end()) {
                    windowStart++;
                    windowSlid = true;
                }

                if (windowSlid) {
                    DisplayCurrentWindow(windowStart, std::min(windowStart + sender.GetWindowSize() - 1, numberOfPackages), numberOfPackages);
                    break;
                }
            }
            else if (pkgTime >= timeout) {
                std::cout << "timeout for package " << pkgId << "\n";
                double newTime = GenerateTime(4.0f);
                packages[pkgId - 1].SetTime(newTime);
                sendedPackages[pkgId] = false;
                std::cout << "will resend package " << pkgId << " with new time: "
                    << packages[pkgId - 1].GetTime() << "\n";
            }
        }

        std::cout << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "\nAll packages successfully transmitted!\n";
}

int main() {
    int numberOfPackages = ReadNumberOfPackages();
    DisplayPackages(numberOfPackages);

    int windowSize = GenerateWindowSize(numberOfPackages);
    std::cout << "\nWindow size: " << windowSize << std::endl;

    Sender sender(numberOfPackages, windowSize);
    DeterminePackagesToSend(sender, numberOfPackages);
    Receiver receiver;

    SelectiveRepeat(sender, receiver, numberOfPackages);

    std::cout << "\nReceiver's buffer (order of received packages): ";
    auto receivedPackages = receiver.GetReceivedPackages();
    for (const auto& pkg : receivedPackages) {
        std::cout << pkg.GetId() << " ";
    }
    std::cout << std::endl;

	std::cout << "\nSender's buffer (order of sent packages): ";
	auto sentPackages = sender.GetPackages();
	for (const auto& pkg : sentPackages) {
		std::cout << pkg.GetId() << " ";
	}
	std::cout << std::endl;

    return 0;
}