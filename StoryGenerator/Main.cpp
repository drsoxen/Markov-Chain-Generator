#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;
class Node;

vector<Node*> TheList;

class Node 
{
public:
	Node(){};
	Node(string name)
	{
		this->Name = name;
	}
	Node(string name,string NextWord)
	{
		this->Name = name;
	}
	string Name;
	vector<Node*>NextNames;
};

Node* GetNode(vector<Node*>*Vec,string* NodeName)
{
	for (int i = 0; i < Vec->size() ; i++)
	{
		if(Vec->at(i)->Name == *NodeName)
			return Vec->at(i);
	}
	return NULL;
}

Node * BlankNode(string* Word)
{
	Node * tempNode = new Node(*Word);
	return tempNode;
}

void Search(vector<Node*>*Vec, string* Word, string* NextWord)
{
	Node * TempVecNextWord = GetNode(Vec,NextWord);
	Node * TempVecWord = GetNode(Vec,Word);

	if(TempVecWord == NULL)
	{
		if(TempVecNextWord != NULL)
		{
			TempVecWord = new Node(*Word);
			TempVecWord->NextNames.push_back(TempVecNextWord);
		}
		else
		{
			Vec->push_back(BlankNode(NextWord));
			Search(Vec,Word,NextWord);
			return;
		}

		Vec->push_back(TempVecWord);
	}
	else
	{
		if(TempVecNextWord != NULL)
		{
			Node * NewTempNode = GetNode(&TempVecWord->NextNames,NextWord);
			if(NewTempNode == NULL)
			TempVecWord->NextNames.push_back(TempVecNextWord);
		}
		else
		{
			Vec->push_back(BlankNode(NextWord));
			Search(Vec,Word,NextWord);
			return;
		}
	}

	return;
}


void GenerateList()
{

	ifstream Fin;

	Fin.open("seedText.txt");

	string Word = "";
	string NextWord = "";

	Fin>>Word;

	while(!Fin.eof())
	{
		Fin>>NextWord;

		Search(&TheList,&Word,&NextWord);

		Word = NextWord;

	}
}

int main()
{
	GenerateList();

	ofstream mySaveFile;
	mySaveFile.open ("Output.txt");

	int random;
	Node* currentWord;
	Node* PrevWord;

	srand(time(0));

	random = rand()%TheList.size();
	currentWord = TheList.at(random);

	for (int i = 0; i < 1000 ; i++)
	{
		if(currentWord->NextNames.size() > 0)
		{
			mySaveFile<<currentWord->Name<<" ";
			random = rand()%currentWord->NextNames.size();
			PrevWord = currentWord;
			currentWord = currentWord->NextNames.at(random);
		}
		else
		currentWord = PrevWord;
	}

	mySaveFile<<"\n\n\n\nTHE END";

	mySaveFile.close();

	system("Output.txt");
	return 0;
}