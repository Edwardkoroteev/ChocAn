#include <string>
#include <stdexcept>
#include <ctime>
#include "ServiceRecord.h"

bool operator==(const ServiceRecord &record1, const ServiceRecord &record2)
{
	return record1._member == record2._member
	       && record1._provider == record2._provider
	       && record1._service == record2._service
	       && record1.dateOfService == record2.dateOfService
	       && record1.dateReceived == record2.dateReceived
	       && record1.comment == record2.comment;
}

// compares by date of service
bool operator<(const ServiceRecord &less, const ServiceRecord &great)
{
	// DOS refers to Date Of Service in the scope of this function
	tm * lessDOSTM;
	tm * greatDOSTM;
	time_t lessDOS;
	time_t greatDOS;

	time_t rawtime;
	time(&rawtime);


	lessDOSTM = localtime(&rawtime);
	lessDOSTM->tm_mon = std::stoi(less.dateOfService.substr(0, 2)) - 1;
	lessDOSTM->tm_mday = std::stoi(less.dateOfService.substr(3, 2));
	lessDOSTM->tm_year = std::stoi(less.dateOfService.substr(6, 4)) - 1990;
	lessDOS = mktime(lessDOSTM);

	greatDOSTM = localtime(&rawtime);
	greatDOSTM->tm_mon = std::stoi(great.dateOfService.substr(0, 2)) - 1;
	greatDOSTM->tm_mday = std::stoi(great.dateOfService.substr(3, 2));
	greatDOSTM->tm_year = std::stoi(great.dateOfService.substr(6, 4)) - 1990;
	greatDOS = mktime(greatDOSTM);

	return lessDOS < greatDOS;
}

std::ostream& operator<<(std::ostream &output, const ServiceRecord &record)
{
	output << record._member.prepareWrite() << '|'
	       << record._provider.prepareWrite() << '|'
	       << record._service.prepareWrite() << '|'
	       << record.dateOfService << '|'
	       << record.dateReceived << '|'
	       << record.comment.length() << '|' << record.comment;

	return output;
}

std::istream& operator>>(std::istream &input, ServiceRecord &record)
{
	// the ignores discard the separators
	input >> record._member;
	input.ignore();
	input >> record._provider;
	input.ignore();
	input >> record._service;
	input.ignore();
	std::getline(input, record.dateOfService, '|');
	std::getline(input, record.dateReceived, '|');

	// Read how many characters to extract for the comment, then extract them
	int commentLength;
	char comment[101];
	input >> commentLength;
	if(commentLength > 100)
		throw std::length_error("Bad record: reported comment length too big!");
	input.ignore();
	if(commentLength > 0)
	{
		input.get(comment, commentLength + 1, EOF);
		record.comment = comment;
	}

	return input;
}
