#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "DrillingRecord.h"
#include "ResizableArray.h"
#include "Exceptions.h"
#include "Comparator.h"
#include "DrillingRecordComparator.h"
#include "Sorter.h"
#include "Search.h"
#include "OULinkedList.h"
#include "OULinkedListEnumerator.h"
#include "Exceptions.h"
#include "OULink.h"
#include "Hasher.h"
#include "HashTableEnumerator.h"
#include "AVLTree.h"
#include "AVLTreeEnumerator.h"
#include "AVLTreeOrder.h"


using namespace std;


ResizableArray<DrillingRecord>* store;
DrillingRecordComparator* field = new DrillingRecordComparator(1);
//OULinkedList<DrillingRecord>* files = new OULinkedList<DrillingRecord>(field);
AVLTree<DrillingRecord>* files = new AVLTree<DrillingRecord>(field);
DrillingRecordHasher* dr = new DrillingRecordHasher();
HashTable<DrillingRecord>* test = new HashTable<DrillingRecord>(field, dr);
int fileCounter = 0, valid = 0, linesRead = 0, columnEntered;
string fileName;



AVLTree<DrillingRecord>* read() //method to read in each file from user
{
	string header, data, datestamp, date, times, number;

	cout << "Enter data file name: ";
	getline(cin, fileName, '\n');
	if (fileName == "")
	{
		AVLTree<DrillingRecord>* temp1 = new AVLTree<DrillingRecord>(field);
		return temp1;

	}
	ifstream text;
	text.open(fileName);
	while (!text.is_open())
	{
		cout << "File is not available." << endl;
		cout << "Enter data file name: ";
		getline(cin, fileName, '\n');
		if (fileName == "")
		{
			AVLTree<DrillingRecord>* temp1 = new AVLTree<DrillingRecord>(field);
			return temp1;
		}
		text.open(fileName);
	}
	AVLTree<DrillingRecord>* localFile = new AVLTree<DrillingRecord>(field);
	getline(text, header);// skips the first line containing headers
	int position = 0;
	while (getline(text, data))
	{
		linesRead++;
		DrillingRecord* obj1 = new DrillingRecord;
		++position;
		istringstream str(data);// allows the line of data to be read as a stream
		getline(str, date, ',');
		if (position == 1)
		{
			datestamp = date;
		}
		obj1->addString(date);
		getline(str, times, ',');
		obj1->addString(times);
		for (unsigned int i = 0; i < 15; i++)
		{
			getline(str, number, ',');
			obj1->addNum((stod)(number));
		}
		getline(str, number, ',');

		//values.addAt(number, 15);
		obj1->addNum((stod)(number));
		if (date.compare(datestamp) != 0 && position != 1)
		{
			cout << "Non-matching date stamp " << date << " at line " << position << "." << endl;
			delete obj1;
		}
		else
		{
			bool error = false;
			for (unsigned int i = 0; i < 16; i++)
			{
				if (obj1->getNum(i) <= 0)// checks for all the float values to greater than zero
				{
					error = true;
					break;
				}
			}
			if (error)
			{
				cout << "Invalid floating-point data at line " << position << "." << endl;
				delete obj1;
			}
			else
			{
				if (!localFile->contains(*obj1))
				{
					localFile->insert(*obj1);
					valid++;
				}
			}


		}//inner while

	}

	if (localFile->getSize() == 0)// checks to see if the inputted file was empty
	{
		cout << "No valid records found" << endl;
		cout << "Enter data file name: ";
		getline(cin, fileName, '\n');
		if (fileName != "")
		{
			text.open(fileName);
			while (!text.is_open())
			{
				cout << "No valid records found" << endl;// reprompt the user for valid data
				cout << "Enter data file name: ";
				getline(cin, fileName, '\n');
				if (fileName != "")
				{
					text.open(fileName);
				}
			}

		}
	}
	else
	{
		fileCounter++;
	}
	
	return localFile;
	
}// endof method 
AVLTree<DrillingRecord>* readFirstFile()
{
	string header, data, datestamp, date, times, number;

	cout << "Enter data file name: ";
	getline(cin, fileName, '\n');
	if (fileName == "")
	{
		AVLTree<DrillingRecord>* temp1 = new AVLTree<DrillingRecord>(field);
		return temp1;

	}
	ifstream text;
	text.open(fileName);
	while (!text.is_open())
	{
		cout << "File is not available." << endl;
		cout << "Enter data file name: ";
		getline(cin, fileName, '\n');
		if (fileName == "")
		{
			AVLTree<DrillingRecord>* temp1 = new AVLTree<DrillingRecord>(field);
			return temp1;
		}
		text.open(fileName);
	}
	
	getline(text, header);// skips the first line containing headers
	int position = 0;
	while (getline(text, data))
	{
		linesRead++;
		DrillingRecord* obj1 = new DrillingRecord;
		++position;
		istringstream str(data);// allows the line of data to be read as a stream
		getline(str, date, ',');
		if (position == 1)
		{
			datestamp = date;
		}
		obj1->addString(date);
		getline(str, times, ',');
		obj1->addString(times);
		for (unsigned int i = 0; i < 15; i++)
		{
			getline(str, number, ',');
			obj1->addNum((stod)(number));
		}
		getline(str, number, ',');

		
		obj1->addNum((stod)(number));
		if (date.compare(datestamp) != 0 && position != 1)
		{
			cout << "Non-matching date stamp " << date << " at line " << position << "." << endl;
			delete obj1;
		}
		else
		{
			bool error = false;
			for (unsigned int i = 0; i < 16; i++)
			{
				if (obj1->getNum(i) <= 0)// checks for all the float values to greater than zero
				{
					error = true;
					break;
				}
			}
			if (error)
			{
				cout << "Invalid floating-point data at line " << position << "." << endl;
				delete obj1;
			}
			else
			{
				store = new ResizableArray<DrillingRecord>(files->getSize());
				test = new HashTable<DrillingRecord>(field, dr, files->getSize());
				if (!files->contains(*obj1))
				{
					files->insert(*obj1);
					valid++;
				}
					
				
			}


		}//inner while

	}

	if (files->getSize() == 0)// checks to see if the inputted file was empty
	{
		cout << "No valid records found" << endl;
		cout << "Enter data file name: ";
		getline(cin, fileName, '\n');
		if (fileName != "")
		{
			text.open(fileName);
			while (!text.is_open())
			{
				cout << "No valid records found" << endl;// reprompt the user for valid data
				cout << "Enter data file name: ";
				getline(cin, fileName, '\n');
				if (fileName != "")
				{
					text.open(fileName);
				}
			}

		}
	}
	else
	{
		fileCounter++;
	}
	if (fileCounter == 1)// data is only added to linked list and array when at least one file has been read in
	{

		AVLTreeEnumerator<DrillingRecord> check = files->enumerator(AVLTreeOrder::inorder);
		test = new HashTable<DrillingRecord>(field, dr, files->getSize()); // Hash Table must be reinitialized to enure updation of bucket value.
		store = new ResizableArray<DrillingRecord>(files->getSize()); //Resizable array must be recosntructed with size equal to number of elemnts to be added.

		while (check.hasNext())
		{
			DrillingRecord* temp = new DrillingRecord(check.next());

			store->add(*temp);
			test->insert(*temp);
		}

	}
	return files;

}
void manipulation()
{
	if (fileCounter >= 1)
	{


		string option;
		cout << "Enter (o)utput, (s)ort, (f)ind, (m)erge, (p)urge, (h)ash table, (pre)order, (in)order, (post)order, or (q)uit: ";
		getline(cin, option, '\n');
		while (option != "q")// exits if user enters quit
		{
			if (option == "o")
			{
				cout << "Enter output file name: ";
				getline(cin, fileName, '\n');
				ofstream text;
				text.open(fileName);
				if (fileName == "")
				{
					for (int i = 0; i < (int)store->getSize(); i++)
					{

						cout << store->get(i) << endl; //pulls the data from ostream and gives output
					}
					cout << "Data lines read: " << linesRead << "; Valid Drilling records read: " << valid << "; Drilling records in memory: " << (int)store->getSize() << endl;
				}
				else
				{
					if (text.is_open())
					{
						for (int i = 0; i < (int)store->getSize(); i++)
						{
							text << store->get(i) << endl;
						}
						text << "Data lines read: " << linesRead << "; Valid Drilling records read: " << valid << "; Drilling records in memory: " << (int)store->getSize() << endl;
					}
					text.close();
				}
			}
			else if (option == "s")
			{
				string column;
				cout << "Enter sort field (0-17): " << endl;
				getline(cin, column, '\n');
				int field = stoi(column);
				columnEntered = field;
				if (field >= 0 && field <= 17)
				{
					DrillingRecordComparator* comp = new DrillingRecordComparator(field);

					Sorter<DrillingRecord>::sort(*store, *comp); //sorts array on the colum specified by user
				}
				else
				{
					continue;
				}
			}
			else if (option == "f")
			{
				ResizableArray<DrillingRecord> Temporary = ResizableArray<DrillingRecord>();
				string column;
				cout << "Enter search field (0-17): ";
				getline(cin, column, '\n');
				int col = stoi(column);
				DrillingRecordComparator* comp = new DrillingRecordComparator(col);// comparator to search on user specified field
				DrillingRecordComparator* timeComp = new DrillingRecordComparator(1);

				if (col > 1 && col < 18)
				{
					string val;
					int foundNum = 0;
					int foundNum1 = 0;
					cout << "Enter positive field value: ";
					getline(cin, val, '\n');
					DrillingRecord temp;
					temp.setNum(stoi(val), col - 2);
					if (stoi(val) > 0) // binary search is already implemeted of array is sorted on the field entered for searching element
					{
						if (columnEntered == col)
						{
							long long int index = binarySearch(temp, *store, *comp);
							if (index >= 0)
							{
								Temporary.add(store->get(index));

								foundNum++;
								while (store->get(index).getNum(col - 2) == store->get(index + 1).getNum(col - 2) && index < (long long int)store->getSize())
								{

									index++;
									foundNum++;
									Temporary.add(store->get(index));
								}
								Sorter<DrillingRecord>::sort(Temporary, *timeComp);
								if (Temporary.getSize() > 0)
								{
									for (int i = 0; i < (int)Temporary.getSize(); i++)
									{
										cout << Temporary.get(i) << endl;
									}
								}
								cout << "Drilling records found: " << foundNum << "." << endl;
							}
						}
						else
						{
							//linear search
							for (int i = 0; i < (int)store->getSize(); i++)
							{
								if (comp->compare(temp, store->get(i)) == 0)
								{
									Temporary.add(store->get(i));
									foundNum1++;

								}
							}
							//Sorter<DrillingRecord>::sort(Temporary, *timeComp);
							if (Temporary.getSize() > 0)
							{
								for (int i = 0; i < (int)Temporary.getSize(); i++)
								{
									cout << Temporary.get(i) << endl;
								}
							}
							cout << "Drilling records found: " << foundNum1 << "." << endl;

						}
					}
				}
				else if (col >= 0 && col <= 1)
				{
					string text;
					int found = 0;
					int found1 = 0;
					cout << "Enter exact text on which to search: ";
					getline(cin, text, '\n');
					DrillingRecord temp1;
					temp1.setString(text, col);// temporary drilling record to store user specified text, in order to support comparison
					if (text != "")
					{
						if (columnEntered == col)
						{
							long long int index = binarySearch(temp1, *store, *comp);
							if (index >= 0)
							{
								Temporary.add(store->get(index));
								found++;
								while (store->get(index).getString(col) == store->get(index + 1).getString(col) && index < (long long int)store->getSize())
								{
									index++;
									found++;
									Temporary.add(store->get(index));
								}
								Sorter<DrillingRecord>::sort(Temporary, *timeComp);
								if (Temporary.getSize() > 0)
								{
									for (int i = 0; i < (int)Temporary.getSize(); i++)
									{
										cout << Temporary.get(i) << endl;
									}
								}
								cout << "Drilling records found: " << found << "." << endl;
							}
						}
						else
						{
							for (int i = 0; i < (int)store->getSize(); i++)
							{
								if (comp->compare(temp1, store->get(i)) == 0)
								{
									Temporary.add(store->get(i));
									found1++;

								}
							}
							
							if (Temporary.getSize() > 0)
							{
								for (int i = 0; i < (int)Temporary.getSize(); i++)
								{
									cout << Temporary.get(i) << endl;
								}
							}
							cout << "Drilling records found: " << found1 << "." << endl;
						}

					}
					else
					{
						continue;
					}
				}
			}

			if (option == "m")
			{

				AVLTree<DrillingRecord>* merger = read();
				AVLTreeEnumerator<DrillingRecord> check = merger->enumerator(AVLTreeOrder::inorder);

				DrillingRecord temp;



				while (check.hasNext())
				{
					temp = check.next();
					if (files->contains(temp))
					{
						files->replace(temp);
					}
					else
					{
						files->insert(temp);
					}
				}
				//store->clear();
				delete store;
				delete test;
				AVLTreeEnumerator<DrillingRecord> checker = files->enumerator(AVLTreeOrder::inorder);
				test = new HashTable<DrillingRecord>(field, dr, files->getSize());
				store = new ResizableArray<DrillingRecord>(files->getSize());
				while (checker.hasNext())
				{
					temp = checker.next();
					store->add(temp);
					test->insert(temp);
				}
			}

			if (option == "p")
			{

				AVLTree<DrillingRecord>* purger = new AVLTree < DrillingRecord>(field);
				purger = read();//read method returns linkedlist with data read in
				AVLTreeEnumerator<DrillingRecord>check = purger->enumerator(AVLTreeOrder::inorder);
				
				while (check.hasNext())
				{
					DrillingRecord* temp = new DrillingRecord(check.next());
					 files->remove(*temp);

				}
				
					
					delete test;
					delete store;
					AVLTreeEnumerator<DrillingRecord> checker = files->enumerator(AVLTreeOrder::inorder);
					test = new HashTable<DrillingRecord>(field, dr, files->getSize());
					store = new ResizableArray<DrillingRecord>(files->getSize());
					while (checker.hasNext())
					{
						DrillingRecord* temp = new DrillingRecord(checker.next());

						store->add(*temp);
						test->insert(*temp);
					}

				
			}
			if (option == "r")// Prints out all the items in the global linked list
			{
				cout << "Enter output file name: ";
				getline(cin, fileName, '\n');
				ofstream text;
				text.open(fileName);
				AVLTreeEnumerator<DrillingRecord>* checker = new AVLTreeEnumerator<DrillingRecord>(files->enumerator());
				if (fileName == "")
				{
					while (checker->hasNext())
					{
						cout << checker->next() << endl;
					}
					cout << "Data lines read: " << linesRead << "; Valid Drilling records read: " << valid << "; Drilling records in memory: " << (int)store->getSize() << endl;
				}
				else
				{
					if (text.is_open())
					{
						AVLTreeEnumerator<DrillingRecord>* check = new AVLTreeEnumerator<DrillingRecord>(files->enumerator());
						while (check->hasNext())
						{
							text << check->next() << endl;
						}
						text << "Data lines read: " << linesRead << "; Valid Drilling records read: " << valid << "; Drilling records in memory: " << (int)store->getSize() << endl;
					}
					text.close();

				}


			}
			if (option == "h")
			{

				cout << "Enter output file name: ";
				getline(cin, fileName, '\n');
				ofstream text;
				text.open(fileName);
				if (fileName == "")
				{
					HashTableEnumerator<DrillingRecord>* traverse = new HashTableEnumerator<DrillingRecord>(test);
					unsigned long previousBucket;

					while (traverse->hasNext())
					{
						previousBucket = test->getBucketNumber(traverse->peek());
						DrillingRecord item = traverse->next();
						cout << previousBucket << ": " << item << endl;
						//cout << endl;
						while (traverse->hasNext() && previousBucket == test->getBucketNumber(traverse->peek()))
						{


							cout << "OVERFLOW: " << traverse->next() << endl;
							//cout << endl;
						}
						cout << endl;

					}

					cout << "Base Capacity: " << test->getBaseCapacity() << "; Total Capacity: " << test->getTotalCapacity() << "; Load Factor: " << test->getLoadFactor() << endl;
					cout << "Data lines read: " << linesRead << "; Valid Drilling records read: " << valid << "; Drilling records in memory: " << (int)store->getSize() << endl;
				}
				else
				{
					if (text.is_open())
					{
						HashTableEnumerator<DrillingRecord>* traverse = new HashTableEnumerator<DrillingRecord>(test);
						unsigned long previousBucket;

						while (traverse->hasNext())
						{
							previousBucket = test->getBucketNumber(traverse->peek());
							DrillingRecord item = traverse->next();
							text << previousBucket << ": " << item << endl;

							while (traverse->hasNext() && previousBucket == test->getBucketNumber(traverse->peek()))
							{

								text << "OVERFLOW: " << traverse->next() << endl;

							}
							text << endl;

						}
						text << "Base Capacity: " << test->getBaseCapacity() << "; Total Capacity: " << test->getTotalCapacity() << "; Load Factor: " << test->getLoadFactor() << endl;
						text << "Data lines read: " << linesRead << "; Valid Drilling records read: " << valid << "; Drilling records in memory: " << (int)store->getSize() << endl;
					}
					text.close();
				}
			}
			if (option == "pre")
			{
				cout << "Enter output file name: ";
				getline(cin, fileName, '\n');
				ofstream text;
				text.open(fileName);
				AVLTreeEnumerator<DrillingRecord> outputEnumerator = files->enumerator(AVLTreeOrder::preorder);
				if (fileName == "")
				{
					
					while (outputEnumerator.hasNext())
					{
						
						cout << outputEnumerator.next() << endl;
					}
					cout << "Data lines read: " << linesRead << "; Valid Drilling records read: " << valid << "; Drilling records in memory: " << (int)store->getSize() << endl;
				}
				else
				{
					if (text.is_open())
					{
						
						AVLTreeEnumerator<DrillingRecord> outputEnumerator = files->enumerator(AVLTreeOrder::preorder);
						while (outputEnumerator.hasNext())
						{
							text << outputEnumerator.next() << endl;
						}
						text << "Data lines read: " << linesRead << "; Valid Drilling records read: " << valid << "; Drilling records in memory: " << (int)store->getSize() << endl;
					}
					text.close();

				
				}
			}
			if (option == "post")
			{
				cout << "Enter output file name: ";
				getline(cin, fileName, '\n');
				ofstream text;
				text.open(fileName);
				AVLTreeEnumerator<DrillingRecord> outputEnumerator = files->enumerator(AVLTreeOrder::postorder);
				if (fileName == "")
				{
					while (outputEnumerator.hasNext())
					{
						cout << outputEnumerator.next() << endl;
					}
					cout << "Data lines read: " << linesRead << "; Valid Drilling records read: " << valid << "; Drilling records in memory: " << (int)store->getSize() << endl;
				}
				else
				{
					if (text.is_open())
					{
						AVLTreeEnumerator<DrillingRecord> outputEnumerator = files->enumerator(AVLTreeOrder::postorder);
						while (outputEnumerator.hasNext())
						{
							text << outputEnumerator.next() << endl;
						}
						text << "Data lines read: " << linesRead << "; Valid Drilling records read: " << valid << "; Drilling records in memory: " << (int)store->getSize() << endl;
					}
					text.close();


				}

			}
			if (option == "in")
			{
				cout << "Enter output file name: ";
				getline(cin, fileName, '\n');
				ofstream text;
				text.open(fileName);
				AVLTreeEnumerator<DrillingRecord> outputEnumerator = files->enumerator(AVLTreeOrder::inorder);
				if (fileName == "")
				{
					while (outputEnumerator.hasNext())
					{
						cout << outputEnumerator.next() << endl;
					}
					cout << "Data lines read: " << linesRead << "; Valid Drilling records read: " << valid << "; Drilling records in memory: " << (int)store->getSize() << endl;
				}
				else
				{
					if (text.is_open())
					{
						AVLTreeEnumerator<DrillingRecord> outputEnumerator = files->enumerator(AVLTreeOrder::inorder);
						while (outputEnumerator.hasNext())
						{
							text << outputEnumerator.next() << endl;
						}
						text << "Data lines read: " << linesRead << "; Valid Drilling records read: " << valid << "; Drilling records in memory: " << (int)store->getSize() << endl;
					}
					text.close();


				}
			}
			cout << "Enter (o)utput, (s)ort, (f)ind, (m)erge, (p)urge, (h)ash table, (pre)order, (in)order, (post)order, or (q)uit: "; //reprompt
			getline(cin, option, '\n');

		}
		cout << "Thanks for using Driller." << endl;
	}//while


}//method 


int main()
{
	readFirstFile();
	manipulation();
	

}

