#pragma once

class Package
{
	int id;
	bool ack = false;
	float time;

public:
	Package(const int& id, const bool& ack, const float& time);

	int GetId() const;

	bool GetAck() const;

	float GetTime() const;

	void SetId(const int& id);

	void SetAck(const bool& ack);

	void SetTime(const float& time);

};