#include "Sender.h"
#include <cstdint>
#include <vector>
#include <iostream>

Sender::Sender(const int& numberOfPackages, const int& windowSize)
	: numberOfPackages(numberOfPackages), windowSize(windowSize) {
}

void Sender::SendPackage(Package package) {
	if (package.GetId() - 1 < packages.size()) {
		packages[package.GetId() - 1] = package;
	}
	else {
		packages.push_back(package);
	}
}

std::vector<Package> Sender::GetPackages() const {
	return packages;
}

std::vector<Package>& Sender::GetPackagesRef() {
	return packages;
}

int Sender::GetWindowSize() const {
	return windowSize;
}

void Sender::SetWindowSize(const int& windowSize) {
	this->windowSize = windowSize;
}

float Sender::GetTimeToWait() const {
	return timeToWait;
}

int Sender::GetBase() const {
	return base;
}

int Sender::GetNextSeqNum() const {
	return nextSeqNumber;
}

void Sender::IncrementBase() {
	base++;
}

void Sender::IncrementNextSeqNum() {
	nextSeqNumber++;
}

void Sender::DisplayPackages() const {
	std::cout << "sender: ";
	for (const auto& pkg : packages) {
		std::cout << pkg.GetId() << " ";
	}
	std::cout << std::endl;
}