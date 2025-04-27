#include "Receiver.h"
#include <vector>
#include <iostream>

Receiver::Receiver() = default;

void Receiver::ReceivePackage(Package package) {
    receivedPackages.push_back(package);
}

std::vector<Package> Receiver::GetReceivedPackages() const {
    return receivedPackages;
}

void Receiver::ClearReceivedPackages() {
    receivedPackages.clear();
}

void Receiver::DisplayReceivedPackages() const {
    std::cout << "receiver: ";
    for (const auto& pkg : receivedPackages) {
        std::cout << pkg.GetId() << " ";
    }
    std::cout << std::endl;
}