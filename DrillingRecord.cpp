#include "DrillingRecord.h"
#include <iomanip>

DrillingRecord::DrillingRecord()
{
	for (unsigned int i = 0; i < MAX_NUMS; i++)
	{
		nums[i] = 0.0;
	}
}

void DrillingRecord::addNum(double num)
{
	nums[numCtr] = num;
	numCtr++;
}

void DrillingRecord::addString(std::string string)
{
	strings[strCtr] = string;
	strCtr++;
}

double DrillingRecord::getNum(unsigned int index) const
{
	return nums[index];
}

std::string DrillingRecord::getString(unsigned int index) const
{
	return strings[index];
}

void DrillingRecord::setNum(double num, unsigned int index)
{
	nums[index] = num;
}

void DrillingRecord::setString(std::string string, unsigned int index)
{
	strings[index] = string;
}

std::ostream& operator<<(std::ostream& os, const DrillingRecord& record)
{
	os << record.strings[0] << ";" << record.strings[1] << ";";
	for (int i = 0; i < 15; i++)
	{
		os << std::fixed << std::setprecision(2) << record.nums[i] << ";";
	}
	os << std::fixed << std::setprecision(2) << record.nums[15];
	return os;
}
