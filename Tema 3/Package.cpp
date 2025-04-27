#include "Package.h"

Package::Package(const int& id, const bool& ack, const float& time)
	: id(id), ack(ack), time(time) {
}

int Package::GetId() const {
	return id;
}

bool Package::GetAck() const {
	return ack;
}

float Package::GetTime() const {
	return time;
}

void Package::SetId(const int& id) {
	this->id = id;
}

void Package::SetAck(const bool& ack) {
	this->ack = ack;
}

void Package::SetTime(const float& time) {
	this->time = time;
}