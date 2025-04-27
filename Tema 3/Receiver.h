#pragma once
#include <vector>
#include "Package.h"

class Receiver
{
	std::vector<Package> receivedPackages;

public:
	Receiver();

	void ReceivePackage(Package package);

	std::vector<Package> GetReceivedPackages() const;

	void ClearReceivedPackages();

	void DisplayReceivedPackages() const;
};