#ifndef RECORDMANAGER_H_INCLUDED
#define RECORDMANAGER_H_INCLUDED

#include <list>
#include <string>
#include <fstream>
#include "ServiceRecord.h"

class RecordManager
{
public:
	RecordManager(const std::string &filename = "records.txt");
	void addRecord(const member &_member,
	               const provider &_provider,
	               const service &_service,
	               const std::string &dateOfService,
	               const std::string &comment = "");
	bool writeMemberReport(std::string memberNumber) const;
	bool writeProviderReport(std::string providerNumber) const;
	bool writeEFT(std::string providerNumber) const;
	void writeSummaryReport() const;

private:
	std::list<ServiceRecord> records;
	std::ofstream recordOutput;

	std::string getCurrentDate() const;
};

#endif // RECORDMANAGER_H_INCLUDED
