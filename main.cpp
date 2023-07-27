//ItemType.h
//#ifndef ITEMTYPETYPE_H
//#define ITEMTYPETYPE_H
#include <string>

const int MAX_ITEMS = 20;
enum RelationType { LESS, GREATER, EQUAL };

class ItemType
{
public:
    ItemType();
    RelationType ComparedTo(ItemType) const;
    void Print() const;
    void Initialize(int number);
private:
    int value;
};
//#endif







//the list header
//#ifndef UNSORTED_H
//#define UNSORTED_H
//#endif


struct NodeType  //where information is in
{
    ItemType info;
    NodeType* next;
};



class UnsortedType
{
public:
    UnsortedType();    // Constructor
    ~UnsortedType();     // Destructor

    bool IsFull() const;
    void InsertItem(ItemType item);
    void DeleteItem(ItemType item);

    void ResetList();
    int GetLenght() const;

    ItemType GetItem(ItemType& item, bool& found);
    ItemType GetNextItem(ItemType& item);

private:
    int length;
    NodeType* listData;
    NodeType* currentPos;

};







//implementation file

#include <iostream>
#include <stdio.h>
using namespace std;

//
//implementation of ItemType.h
//

ItemType::ItemType()
{
    value = 0;
}

RelationType ItemType::ComparedTo(ItemType otherItem) const
{
    if (value < otherItem.value)
        return LESS;
    else if (value > otherItem.value)
        return GREATER;
    else return EQUAL;
}

void ItemType::Initialize(int number)
{
    value = number;
}

void ItemType::Print() const //the print info in the node
{
    cout << "\t" << value << endl;
}



//
//implementation of unsorted.h
//


UnsortedType::UnsortedType()
{
    length = 0;
}


UnsortedType::~UnsortedType()
// thanks to this function, list is empty; all items have been deallocated.
{
    NodeType* tempPtr;

    while (listData != NULL)  //until listdata is null, delete whole nodes
    {
        tempPtr = listData;
        listData = listData->next;
        delete tempPtr;
    }
}

bool UnsortedType::IsFull() const // to check if the list is full
{
    NodeType* location;
    try
    {
        location = new NodeType;
        delete location;
        return false;
    }
    catch (bad_alloc exception)
    {
        return true;
    }
}




void UnsortedType::InsertItem(ItemType item)
{
    NodeType* p;			// Declare a pointer to a node

    p = new NodeType;		// Get a new node 
    p->info = item;		// Store the item in the node
    p->next = listData;		// Store address of first node in next field of new node

    listData = p;			// the new node is now the first node 
    length++;				// Increment length of the list
}



void UnsortedType::DeleteItem(ItemType item)
{
    NodeType* p = listData;
    NodeType* pMatch;

    // Locate node to be deleted.
    if (item.ComparedTo(listData->info) == EQUAL)
    {
        pMatch = listData;			//pMatch points to the node to be deleted 
        listData = listData->next;		// listData points to next node.
    }
    else
    {
        //keep move p to point to next node, until it points to the node before matching node. 
        while (item.ComparedTo((p->next)->info) != EQUAL)
            p = p->next;

        pMatch = p->next;  // this is the node to be deleted 

        p->next = (pMatch->next);	//skip the matching node in the linked list 
    }

    delete pMatch; //recycle the memory 
    length--;
}

ItemType UnsortedType::GetNextItem(ItemType& item)
{
    if (currentPos == NULL)
        currentPos = listData;
    else
        currentPos = currentPos->next;
    item = currentPos->info;
    return item;
}

ItemType UnsortedType::GetItem(ItemType& item, bool& found)
// thanks to this function, if found, item's key matches an element's key in the 
//       list and a copy of that element has been stored in item;
//       otherwise, item is unchanged. 
{
    bool moreToSearch;
    NodeType* p;

    p = listData;
    found = false;
    moreToSearch = (p != NULL);

    while (moreToSearch && !found)
    {
        if (item.ComparedTo(p->info) == EQUAL)
        {
            found = true;
            item = p->info;
        }
        else
        {
            p = p->next;
            moreToSearch = (p != NULL);
        }
    }
    return item;
}

void UnsortedType::ResetList()
// Current position has been initialized.
{
    currentPos = NULL;
}




//
//main
//

#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

int main()
{
    string method;
    ItemType name;
    int getting_name;
    UnsortedType list;
    bool found;

    cout << "Enter the method you want to test\n";
    cout << "InsertItem\n";
    cout << "DeleteItem\n";
    cout << "GetItem\n";
    cout << "PrintList\n";
    cout << "MakeEmpty\n";

    cin >> method;
    while (true)
    {

        if (method == "PutItem")
        {
            cout << "Enter a name:" << endl;
            cin >> getting_name;

            name.Initialize(getting_name);

            list.InsertItem(name);
        }
        else if (method == "DeleteItem")
        {
            cin >> getting_name;

            name.Initialize(getting_name);

            list.DeleteItem(name);
            cout << " is deleted" << endl;
        }
        else if (method == "GetItem")
        {
            name.Initialize(getting_name);

            list.InsertItem(name);

            name = list.GetItem(name, found);
            cout << getting_name << endl;

            if (found)
                cout << " found in list." << endl;
            else cout << " not in list." << endl;
        }
        else if (method == "Print")
            list.ResetList();

        for (int i = 0; i < list.GetLenght(); i++)
        {
            list.GetNextItem(name);
            name.Print();
            cout << " ";
        }

    }
}
