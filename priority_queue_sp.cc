/*@author: Parag Patel
  @github:
*/

#include <iostream>
#include <string>
#include <cmath>
#include <stack>

using namespace std;


/* Priority Queue implementation in C++, implementation with a binary heap that is implemented with set of 5 pointers per node
parent,leftchild,rightchild,leftsibling, rightsibling.  We mantain reference to first node in each level in a stack and determine if a node
is in the last node in a level, through log2(current->id + 1) == level.

THIS CODE IS STILL BEING TESTED AND NOT STABLE. NEED TO TEST PERFORMANCE VS ARRAY IMPLEMENTATION. Code should use more memory, but yet
be more dynamic without having need to reallocate once maximum array size is hit.

TODO: REMOVE childrenFilled filed, has it is a bit redundant.

*/

struct Node
{
    Node *parent;
    Node *leftChild;
    Node *rightChild;
    Node *leftSibiling;
    Node *rightSibiling;
    bool childrenFilled;
    int value;
    int id;

    Node(int val)
    {
        id = val;
        childrenFilled = false;
    }
};


class PriorityQueue
{

public:
    Node *root;
    Node *current;
    stack<Node *> firstNodeCurrentLevelStack;
    int level;
    int count;



    PriorityQueue()
    {
        root = NULL;
        current = NULL;
        level = 0;
        count = 0;
    }


    int peek(void)
    {
        if (root == NULL)
        {
            cout << "no items to peek in Priority Queue" << endl;
            return NULL;
        }
        return root->value;
    }

    void initializeIfRoot()
    {
        root = new Node(++count);
        current = root;
        firstNodeCurrentLevelStack.push(root);
        level = 1;

    }
    bool isLevelfull(void)
    {
        if (current == root)
        {
            return true;
        }

        /*
        cout << "current->id = " << current->id << endl;
        cout << "current level  = " << level << endl;
        cout << "log2(current->id)" << log2(current->id + 1) << endl;
        cout << "pow(2.0,level) " <<  pow(2.0,level) << endl; */

        return (log2(current->id + 1) == level );
    }

    void insert(int value)
    {
        //cout << "inserting " << endl;
        if (root == NULL)
        {
            //cout << "initialize empty root" << endl;
            initializeIfRoot();
            current->value = value;
            return;
        }

        shiftCurrenttoLastNodeLevel();
        current->value = value;
        percolateUp();

    }

    int deleteTop(void)
    {
        if (root == NULL)
        {
            cout << "There are no items in PQ to delete" << endl;
            return 0;
        }

        int temp = root->value;
        root->value = current->value;
        deleteCurrentNode();
        percolateDown();


    }


    void deleteCurrentNode()
    {
        if (current == root && root != NULL)
        {
            delete root;
            current = NULL;
            root = NULL;
            firstNodeCurrentLevelStack.pop();
            level = 0;
            count = 0;
        }
        else if (current == firstNodeCurrentLevelStack.top())
        {
            current = firstNodeCurrentLevelStack.top()->leftSibiling;
            current->rightSibiling = NULL;
            Node *tmp ;
            tmp = firstNodeCurrentLevelStack.top();
            firstNodeCurrentLevelStack.pop();
            tmp->parent->childrenFilled = false;
            if (tmp->parent->leftChild == tmp)
            {
                tmp->parent->leftChild = NULL;
            }
            else
            {
                tmp->parent->rightChild = NULL;
            }
            delete tmp;
            level--;
            count--;
        }
        else
        {
            Node *tmp;
            tmp = current;
            current = tmp->leftSibiling;
            current->rightSibiling = NULL;
            tmp->parent->childrenFilled = false;
            if (tmp->parent->leftChild == tmp)
            {
                tmp->parent->leftChild = NULL;
            }
            else
            {
                tmp->parent->rightChild = NULL;
            }


            delete tmp;

            count--;
        }

    }

    void percolateUp(void)
    {
        Node *tmp ;
        tmp = current;
        /*cout << "entering the percolateup function" << endl;
        cout << "current value is " << current->value << endl;
        cout << "root value is " << root->value << endl;
        cout << "current parent value is " << current->parent->value << endl;*/
        while (tmp != root && tmp->value > tmp->parent->value)
        {
            //cout << "in percolateup::while loop" << endl;
            int temp;
            temp = tmp->value;
            tmp->value = tmp->parent->value;
            tmp->parent->value = temp;
            tmp = tmp->parent;
        }
        //cout << "current value is " << current->value << endl;
    }

    void percolateDown(void)
    {
        //swap root and value at x
        Node *tmp;
        tmp = root;

        while (tmp != NULL && tmp->leftChild != NULL && tmp->value < tmp->leftChild->value)
        {

            int temp = tmp->value;
            tmp->value = tmp->leftChild->value;
            tmp->leftChild->value = temp;
            tmp = tmp->leftChild;

        }

    }

    void shiftCurrenttoLastNodeLevel(void)
    {
        if (!isLevelfull())
        {

            Node *newNode = new Node(++count);

            if (current->parent->childrenFilled)
            {
                current->parent->rightSibiling->leftChild = newNode;
                newNode->parent = current->parent->rightSibiling;
            }
            else
            {
                current->parent->rightChild = newNode;
                newNode->parent = current;
                current->parent->childrenFilled = true;

            }
            current->rightSibiling = newNode;
            newNode->leftSibiling = current;

            current = newNode;
            //cout << "up in here up in here" << endl;

        }
        else
        {
            //cout << "here " << endl;
            level++;
            Node *newNode = new Node(++count);
            firstNodeCurrentLevelStack.top()->leftChild = newNode;
            newNode->parent = firstNodeCurrentLevelStack.top();
            firstNodeCurrentLevelStack.push(newNode);

            current->rightSibiling = firstNodeCurrentLevelStack.top();
            firstNodeCurrentLevelStack.top()->leftSibiling = current;
            current = firstNodeCurrentLevelStack.top();



        }


    }


};




int main()
{
    PriorityQueue *pq = new PriorityQueue();

    pq->insert(3);
    //cout << "level after insert = "<< pq->level << endl;
    //cout << "current->id = " << pq->current->id << endl;
    //cout << "log2(current->id) = " << log2(pq->current->id) << endl;
    pq->insert(20);
    //cout << "level after insert = "<< pq->level << endl;
    //cout << "current->id = " << pq->current->id << endl;
    //cout << "level after insert(20) "<< pq->level << endl;

    pq->insert(18);
    // cout << "level after insert = "<< pq->level << endl;
    //cout << "current->id = " << pq->current->id << endl;

    pq->insert(98);
    //cout << "level after insert = "<< pq->level << endl;
    //cout << "current->id = " << pq->current->id << endl;

    pq->insert(198);
    //cout << "level after insert = "<< pq->level << endl;
    //cout << "current->id = " << pq->current->id << endl;


    pq->insert(108);
    //cout << "level after insert = "<< pq->level << endl;
    //cout << "current->id = " << pq->current->id << endl;

    pq->insert(28);
    //cout << "level after insert = "<< pq->level << endl;
    //cout << "current->id = " << pq->current->id << endl;


    pq->insert(1344);
    //cout << "level after insert = "<< pq->level << endl;
    //cout << "current->id = " << pq->current->id << endl;

    //int count = 0;

    while (pq->root )
    {

        pq->deleteTop();
        cout << "peek => " << pq->peek() << endl;
        cout << "count => " << pq->count << endl;
    }
    /*
        cout << "peek => " << pq->peek() << endl;
        cout << "count => " << pq->count << endl;
        cout << "current => " << pq->current->id << endl;
        cout << "DELETE TOP ------------------------------->" << endl;
        pq->deleteTop();
        cout << "peek => " << pq->peek() << endl;
        cout << "count => " << pq->count << endl;
        cout << "current => " << pq->current->id << endl;
        cout << "DELETE TOP ------------------------------->" << endl;
        pq->deleteTop();
        cout << "peek => " << pq->peek() << endl;
        cout << "count => " << pq->count << endl;
        cout << "current => " << pq->current->id << endl;
        cout << "DELETE TOP ------------------------------->" << endl;
        pq->insert(1344);
        cout << "peek => " << pq->peek() << endl;
        cout << "count => " << pq->count << endl;
        cout << "current => " << pq->current->id << endl;
        cout << "INSERT ------------------------------->" << endl;
        pq->deleteTop();
        cout << "peek => " << pq->peek() << endl;
        cout << "count => " << pq->count << endl;
        cout << "current => " << pq->current->id << endl;
        cout << "DELETE TOP ------------------------------->" << endl;
        pq->deleteTop();
        cout << "peek => " << pq->peek() << endl;
        cout << "count => " << pq->count << endl;
        cout << "current => " << pq->current->id << endl;
        cout << "DELETE TOP ------------------------------->" << endl;
        */
}