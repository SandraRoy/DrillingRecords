#include "DrillingRecordHasher.h"
#include<string>

using namespace std;
unsigned long DrillingRecordHasher::hash(const DrillingRecord& item) const
{
	string value = item.getString(1);
	unsigned long sum = 0;
	for (unsigned int i = 0; i < value.length(); i++)
	{
		sum += (int)(value[i]);
	}
	return sum;
}
