#pragma once
#include <vector>
#include "Package.h"

class Sender
{
	int numberOfPackages;
	std::vector<Package> packages;
	int windowSize;
	float timeToWait = 4.0f;
	int base = 0;
	int nextSeqNumber = 0;

public:
	Sender(const int& numberOfPackages, const int& windowSize);

	void SendPackage(Package package);

	std::vector<Package> GetPackages() const;

	std::vector<Package>& GetPackagesRef();

	int GetWindowSize() const;

	void SetWindowSize(const int& windowSize);

	float GetTimeToWait() const;

	int GetBase() const;

	int GetNextSeqNum() const;

	void IncrementBase();

	void IncrementNextSeqNum();

	void DisplayPackages() const;
};