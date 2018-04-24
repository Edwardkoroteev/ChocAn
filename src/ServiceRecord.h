#ifndef SERVICERECORD_H_INCLUDED
#define SERVICERECORD_H_INCLUDED

#include <iostream>
#include "member.h"
#include "provider.h"
#include "service.h"

struct ServiceRecord
{
	member _member;
	provider _provider;
	service _service;
	std::string dateOfService;
	std::string dateReceived;
	std::string comment;
};

std::ostream& operator<<(std::ostream &output, const ServiceRecord &record);
std::istream& operator>>(std::istream &input, ServiceRecord &record);
bool operator==(const ServiceRecord &record1, const ServiceRecord &record2);

// compares by date of service
bool operator<(const ServiceRecord &less, const ServiceRecord &greater);

#endif // SERVICERECORD_H_INCLUDED
