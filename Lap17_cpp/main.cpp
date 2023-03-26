#include <iostream>
#include <cmath>

#define NAME_LENGTH 30

using namespace std;

template <typename T>
struct HashTable
{
    T** items;

    HashTable(const int size)
    {
        this->size = size;
        this->items = new T * [size];
        std::fill(items, items + size, nullptr);
    }

    ~HashTable()
    {
        for (int i = 0; i < size; i++) delete items[i];
        delete[] items;
    }

    int getSize()
    {
        return size;
    }

    void add(T* item)
    {
        int i = hash(*(item->key));
        items[i] = item;
    }

    T* get(const int key)
    {
        int i = getIndex(key);
        if (i == -1) return nullptr;
        return items[i];
    }

    void remove(const int key)
    {
        int i = getIndex(key);
        if (items[i] != nullptr) {
            delete items[i];
            items[i] = nullptr;
        }
    }

private:
    int size;
    int p = 0;

    int getIndex(const int key)
    {
        int i = createHash(key);
        while (items[i] != nullptr)
        {
            if (*(items[i]->key) == key) return i;
            adjustHash(i);
        }
        return -1;
    }

    int hash(const int key)
    {
        int i = createHash(key);
        while (items[i] != nullptr) adjustHash(i);
        return i;
    }

    int createHash(const int key)
    {
        p = 0;
        return abs(key % size);
    }

    void adjustHash(int& i)
    {
        i = i + pow(++p, 2);
        if (i == size) i = 0;
    }
};

struct Item
{
    int* key = &manufacturedDay;

    char name[NAME_LENGTH] = "";
    int price = 0;
    int manufacturedDay = 0;

    void print()
    {
        printf_s("{name: \"%s\", price: %d, manufacturedDay: %d}\n", name, price, manufacturedDay);
    }
};

int main()
{
    const int N = 8;
    const int M = 15;

    Item items[N];

    for (Item& item : items)
    {
        cout << "Enter [name] [price] [day]: ";
        scanf_s("%s%d%d", item.name, NAME_LENGTH, &(item.price), &(item.manufacturedDay));
    }
    cout << "All items:" << endl;
    for (Item& item : items)
    {
        cout << "  ";
        item.print();
    }

    HashTable<Item> table = HashTable<Item>(M);
    for (Item& item : items)
    {
        Item* itemPtr = new Item;
        *itemPtr = item;
        table.add(itemPtr);
    }
    cout << "Hash table content:" << endl;
    for (int i = 0; i < table.getSize(); i++)
    {
        Item* item = table.items[i];
        if (item == nullptr)
        {
            printf_s("[%d] - NULL\n", i);
            continue;
        }
        printf_s("[%d] - ", i);
        item->print();
    }

    int key;
    cout << "Enter key: ";
    cin >> key;

    Item* foundItem = table.get(key);
    if (foundItem == nullptr) cout << "Not found(" << endl;
    else foundItem->print();

    delete &table;

    return 0;
}
