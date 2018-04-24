#include <map>
#include <stdexcept>
#include "RecordManager.h"

RecordManager::RecordManager(const std::string &filename)
{
	std::ifstream recordInput(filename);

	try
	{
		while(recordInput.peek() != EOF)
		{
			ServiceRecord record;
			recordInput >> record;
			recordInput.ignore(); // discard line ending

			if(!recordInput.good())
				throw std::runtime_error("Stream error during read.");

			records.push_back(record);
		}
	}
	catch(const std::exception &e)
	{
		std::cerr << "ERROR: " << e.what() << '\n'
		          << "Probable records file corruption. Ignoring subsequent "
		          << "records.\n";
	}

	recordInput.close();

	recordOutput.open(filename, std::ios_base::app);
}

void RecordManager::addRecord(const member &_member,
                              const provider &_provider,
                              const service &_service,
                              const std::string &dateOfService,
                              const std::string &comment)
{
	ServiceRecord newRecord;

	newRecord._member = _member;
	newRecord._provider = _provider;
	newRecord._service = _service;
	newRecord.dateOfService = dateOfService;
	newRecord.comment = comment;

	char dateReceived[20];
	time_t rawTime = time(nullptr);
	strftime(dateReceived, 20, "%m-%d-%Y %T", localtime(&rawTime));
	newRecord.dateReceived = dateReceived;

	records.push_back(newRecord);

	recordOutput << newRecord << std::endl;
}

bool RecordManager::writeMemberReport(std::string memberNumber) const
{
	auto i = records.cbegin();

	// find the first matching member
	for(; i->_member.number != memberNumber; ++i)
	{
		if(i == records.cend())
			return false; // member has no records
	}

	std::ofstream reportOutput(i->_member.name + '_'
	                           + getCurrentDate() + ".txt");

	reportOutput << "Name: " << i->_member.name << '\n'
	             << "ID: " << i->_member.number << '\n'
	             << "Address: " << i->_member.street << '\n'
	             << "City: " << i->_member.city << '\n'
	             << "State: " << i->_member.state << '\n'
	             << "ZIP code: " << i->_member.zip << '\n'
	             << '\n';

	std::list<ServiceRecord> recordsByMember;
	// puts matching member in a special list, to be sorted soon
	do
	{
		if(i->_member.number == memberNumber)
			recordsByMember.push_back(*i);
	}
	while(++i != records.cend());

	// using operator<, sorts the list by date of service
	recordsByMember.sort();

	for(auto iter = recordsByMember.cbegin();
	    iter != recordsByMember.cend();
	    ++iter)
	{
		reportOutput << "For service provided on "
		             << iter->dateOfService << '\n'
		             << "\tProvider name: " << iter->_provider.name << '\n'
		             << "\tService name: " << iter->_service.name << '\n'
		             << '\n';
	}

	reportOutput << "END OF REPORT" << std::endl;
	return true;
}

bool RecordManager::writeProviderReport(std::string providerNumber) const
{
	auto i = records.cbegin();

	// find the first matching provider
	for(; i->_provider.number != providerNumber; ++i)
	{
		if(i == records.cend())
			return false; // provider has no records
	}

	std::ofstream reportOutput(i->_provider.name + '_'
	                           + getCurrentDate() + ".txt");

	reportOutput << "Name: " << i->_provider.name << '\n'
	             << "ID: " << i->_provider.number << '\n'
	             << "Address: " << i->_provider.street << '\n'
	             << "City: " << i->_provider.city << '\n'
	             << "State: " << i->_provider.state << '\n'
	             << "ZIP code: " << i->_provider.zip << '\n'
	             << '\n';

	int totalServices = 0;
	float totalFee = 0;
	do
	{
		if(i->_provider.number == providerNumber)
		{
			++totalServices;
			totalFee += i->_service.fee;

			reportOutput << "For service received by the computer at "
			             << i->dateReceived << '\n'
			             << "\tProvided on: " << i->dateOfService << '\n'
			             << "\tMember name: " << i->_member.name << '\n'
			             << "\tMember ID: " << i->_member.number << '\n'
			             << "\tService code: " << i->_service.number << '\n'
			             << std::fixed << std::setprecision(2)
			             << "\tFee in USD: " << i->_service.fee << '\n'
			             << '\n';
		}
	}
	while(++i != records.cend());

	reportOutput << "Total services provided: " << totalServices << '\n'
	             << std::fixed << std::setprecision(2)
	             << "Total fee: " << totalFee << '\n'
	             << '\n'
	             << "END OF REPORT" << std::endl;
	return true;
}

bool RecordManager::writeEFT(std::string providerNumber) const
{
	auto i = records.cbegin();

	// find the first matching provider
	for(; i->_provider.number != providerNumber; ++i)
	{
		if(i == records.cend())
			return false; // provider has no records
	}

	std::ofstream reportOutput(i->_provider.name + '_'
	                           + getCurrentDate() + ".eft");

	reportOutput << "Provider name: " << i->_provider.name << '\n'
	             << "Provider number: " << i->_provider.number << '\n';

	float totalFee = 0;
	do
	{
		if(i->_provider.number == providerNumber)
			totalFee += i->_service.fee;
	}
	while(++i != records.cend());

	reportOutput << std::fixed << std::setprecision(2)
	             << "Total fee: " << totalFee << '\n'
	             << '\n'
	             << "END OF EFT" << std::endl;
	return true;
}

void RecordManager::writeSummaryReport() const
{
	// provider numbers are the keys, and pairs of their running totals of
	// consultations and fees are the data
	using TotalsPair = std::pair<int, float>; // for convenience
	std::map<std::string, TotalsPair> providerTotals;

	for(auto i = records.cbegin(); i != records.cend(); ++i)
	{
		if(providerTotals.count(i->_provider.number) == 0)
			providerTotals[i->_provider.number] = TotalsPair(0, 0);

		++providerTotals[i->_provider.number].first;
		providerTotals[i->_provider.number].second += i->_service.fee;
	}

	TotalsPair summaryTotal(0, 0);
	std::ofstream reportOutput("summary_" + getCurrentDate() + ".txt");
	for(auto i = providerTotals.cbegin(); i != providerTotals.cend(); ++i)
	{
		summaryTotal.first += i->second.first;
		summaryTotal.second += i->second.second;

		reportOutput << "For provider " << i->first << '\n'
		             << "\tTotal services provided: " << i->second.first << '\n'
		             << std::fixed << std::setprecision(2)
		             << "\tTotal fee: " << i->second.second << '\n'
		             << '\n';
	}

	reportOutput << "Total number of providers that rendered services: "
	             << providerTotals.size() << '\n'
	             << "Total number of services provided: " << summaryTotal.first
	             << '\n'
	             << "Total fee for all providers: " << summaryTotal.second
	             << '\n'
	             << '\n'
	             << "END OF SUMMARY REPORT" << std::endl;
}

std::string RecordManager::getCurrentDate() const
{
	char dateCString[11];
	time_t rawTime = time(nullptr);
	strftime(dateCString, 20, "%m-%d-%Y", localtime(&rawTime));

	return dateCString;
}
