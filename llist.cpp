#include "llist.h"

#include <cassert>

LList::Node::Node(const ValueType& value, Node* next)
{
    this->value = value;
    this->next = next;
}

LList::Node::~Node()
{
    // ничего не удаляем, т.к. агрегация
}

void LList::Node::insertNext(const ValueType& value)
{
    Node* newNode = new Node(value, this->next);
    this->next = newNode;

}

void LList::Node::removeNext()
{
    Node* removeNode = this->next;
    Node* newNext = removeNode->next;
    delete removeNode;
    this->next = newNext;
}

LList::LList()
        : _head(nullptr), _size(0)//просто класс создан здесь
{

}

LList::LList(const LList& copyList)
{
    this->_size = copyList._size;
    if (this->_size == 0) {
        this->_head = nullptr;
        return;
    }

    this->_head = new Node(copyList._head->value);

    Node* currentNode = this->_head;
    Node* currentCopyNode = copyList._head->next;

    while (currentCopyNode) {
        currentNode->next = new Node(currentCopyNode->value);
        currentCopyNode = currentCopyNode->next;
        currentNode = currentNode->next;
    }
}

/*LList& LList::operator=(const LList& copyList)
{
    if (this == &copyList) {
        return *this;
    }
    LList bufList(copyList);
    this->_size = bufList._size;
    this->_head = bufList._head;

    return *this;
}*/

/*LList::LList(LList&& moveList) noexcept
{
    this->_size = moveList._size;
    this->_head = moveList._head;

    moveList._size = 0;
    moveList._head = nullptr;
}*/

/*LList& LList::operator=(LList&& moveList) noexcept
{
    if (this == &moveList) {
        return *this;
    }
    forceNodeDelete(_head);
    this->_size = moveList._size;
    this->_head = moveList._head;

    moveList._size = 0;
moveList._head = nullptr;

return *this;
}*/

LList::~LList()
{
    forceNodeDelete(_head);
}

ValueType& LList::operator[](size_t idx) const
{
    return getNode(idx)->value;
}

ValueType& LList::operator[](size_t idx){
    return getNode(idx)->value;
}

LList::Node* LList::getNode(const size_t pos) const
{
    if (pos < 0) {
        assert(pos < 0);
    }
    else if (pos >= this->_size) {
        assert(pos >= this->_size);
    }

    Node* bufNode = this->_head;
    for (int i = 0; i < pos; ++i) {
        bufNode = bufNode->next;
    }

    return bufNode;
}

void LList::insert_at(size_t idx, int val)
{

    if (idx < 0) {
        assert(idx < 0);
    }
    else if (idx > this->_size) {
        assert(idx > this->_size);
    }

    if (idx == 0) {
        push_front(val);
    }
    else {
        Node* bufNode = this->_head;
        for (size_t i = 0; i < idx-1; ++i) {
            bufNode = bufNode->next;
        }
        bufNode->insertNext(val);
        ++_size;
    }
}

/*void LList::insertAfterNode(Node* node, const ValueType& value)
{
    node->insertNext(value);
    ++_size;
}*/

void LList::push_back(int val)
{
    if (_size == 0) {
        push_front(val);
        return;
    }
    insert_at(_size, val);
}

void LList::push_front(int val) //добавить новый элемент
{
    _head = new Node(val, _head);
    ++_size;
}

void LList::erase_at(size_t idx)
{

    if (idx < 0) {
        assert(idx < 0);
    }
    else if (idx > this->_size) {
        assert(idx > this->_size);
    }

    else if (idx == 0) {
        pop_front();
    }
    else if(idx == _size - 1)
    {
        pop_back();
    }
    else {

        Node *deleteNode = getNode(idx);
        Node *bufNode = getNode(idx + 1);
        getNode(idx - 1)->next = bufNode;
        delete deleteNode;
        --_size;
    }

}
/*void LList::removeNode(Node* node)
{
    int index = findIndex(node->value);

    if(index == -1)
    {
        assert(index == -1);
    }

    else if (index == 0) {
        pop_front();
    }
    else if(index == _size - 1)
    {
        pop_back();
    }
    else {


        erase_at(index);
        --_size;
    }

}*/

/*void LList::removeNextNode(Node* node)
{
    int index = findIndex(node->value);
    remove(index + 1);
}*/
void LList::pop_back()
{

    Node *deleteNode = getNode(_size - 1);
    getNode(_size - 2)->next = nullptr;
    delete deleteNode;
    --_size;
}

void LList::pop_front()
{
    Node *deleteBuf = getNode(0);
    this->_head = getNode(1);
    delete deleteBuf;
    --_size;
}

/*long long int LList::findIndex(const ValueType& value) const
{
    Node *node = this->_head;

    for(int i = 0; i < _size; ++i)
    {
        if(node->value == value){
            return i;
        }
        node = node->next;
    }
    return -1;
}*/

/*LList::Node* LList::findNode(const ValueType& value) const
{
    int index = findIndex(value);
    assert(index != -1);
    return getNode(index);
}*/

void LList::reverse() {
    int index = _size - 1;
    long double n;
    for (int i = 0; i <= int((_size - 1) / 2); ++i) {
        n = getNode(i)->value;
        getNode(i)->value = getNode(_size - 1 - i)->value;
        getNode(_size - 1 - i)->value = n;
    }
}


/*LList LList::reverse()
{
    LList buf(*this);
    buf.reverse();
    return buf;
}*/

/*LList LList::getReverseList() const
{
    LList  buf(*this);
    buf.reverse();
    return buf;
}*/

size_t LList::size() const
{
    return _size;
}


void LList::forceNodeDelete(Node* node)
{
    if (node == nullptr) {
        return;
    }

    Node* nextDeleteNode = node->next;
    delete node;
    forceNodeDelete(nextDeleteNode);
}