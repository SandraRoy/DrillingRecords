#include "DrillingRecordComparator.h"

DrillingRecordComparator::DrillingRecordComparator(unsigned int column)
{
	this->column = column;
}

int DrillingRecordComparator::compare(const DrillingRecord& item1, const DrillingRecord& item2) const
{
	if (column > 17)
	{
		throw new ExceptionIndexOutOfRange;
	}
	else if (column == 0)
	{
		if (item1.getString(column) > item2.getString(column))
		{
			return 1;
		}
		else if (item1.getString(column) < item2.getString(column))
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
	else if (column == 1)
	{
		if (item1.getString(column) > item2.getString(column))
		{
			return 1;
		}
		else if (item1.getString(column) < item2.getString(column))
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if (item1.getNum(column - 2) > item2.getNum(column - 2))//possible bug
		{
			return 1;
		}
		else if (item1.getNum(column - 2) < item2.getNum(column - 2))
		{
			return -1;
		}
		else
		{
			return 0;
		}

	}


}
