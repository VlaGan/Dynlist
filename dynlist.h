#pragma once

template <typename type> class dynlist {
private:
    int size;
    type* dlist;

public:
    dynlist(const int new_size);
    ~dynlist();

    inline type* operator[](const int index);
    inline type* at(const int index);

    inline const int len() const;
    virtual void print();

    virtual void push_back(type value);
    virtual void push_front(type value);
    virtual void push_index(type value, const int index);

    virtual void pop_back();
    virtual void pop_front();
    virtual void pop_index(const int index);

    virtual void resize(const int new_size);
    
    type max() const;
    type max(int &index) const;
    type min() const;
    type min(int &index) const;
    virtual void sort();

    virtual void reverse();


private:
    void QuickSort(size_t const left, size_t const right);
};



template <typename type> inline dynlist<type>::dynlist(const int new_size) {
    size = new_size;
    dlist = new type[size]{};
}

template <typename type> dynlist<type>::~dynlist() {
    delete[] dlist;
    dlist = nullptr;
}

template <typename type> inline type* dynlist<type>::operator[](const int index) {
    if (index < 0)
        return dlist + size + index;
    return dlist + index;
}

template <typename type> inline type* dynlist<type>::at(const int index) {
    if (index < 0)
        return dlist + size + index;
    return dlist + index;
}

template <typename type> inline const int dynlist<type>::len() const { return size; }

template <typename type> void dynlist<type>::print() {
    for (int i = 0; i < size; i++)
        std::cout << dlist[i] << "\t";
    std::cout << std::endl;
}

// do not use cycle with dlist.len() with pop/push-methods, because u got endless cycle
template <typename type> void dynlist<type>::push_back(type value) {
    size++;
    type* ndlist = new type[size];
    for (int i = 0; i < size - 1; i++)
        ndlist[i] = dlist[i];
    ndlist[size - 1] = value;
    delete[] dlist;
    dlist = ndlist;
}

template <typename type> void dynlist<type>::push_front(type value) {
    type* new_mas = new type[size + 1]{};
    new_mas[0] = value;
    for (int i = 1; i < size; i++)
        new_mas[i] = dlist[i - 1];
    size++;
    delete[] dlist;
    dlist = new_mas;
}

template <typename type> void dynlist<type>::push_index(type value, const int index) {
    if (index > size)
        return;
    else if (index == -1)
        return push_back(value);

    size++;
    type* new_mas = new type[size];
    for (int i = 0; i < size; i++) {
        if (index == i)
            new_mas[i] = value;
        else if (i < index)
            new_mas[i] = dlist[i];
        else
            new_mas[i] = dlist[i - 1];
    }
    delete[] dlist;
    dlist = new_mas;
}

template <typename type> void dynlist<type>::pop_back() {
    size--;
    type* new_mas = new type[size];
    for (int i = 0; i < size; i++)
        new_mas[i] = dlist[i];
    delete[] dlist;
    dlist = new_mas;
}

template <typename type> void dynlist<type>::pop_front() {
    type* new_mas = new type[size - 1];
    for (int i = 1; i < size; i++)
        new_mas[i - 1] = dlist[i];
    size--;
    delete[] dlist;
    dlist = new_mas;
}

template <typename type> void dynlist<type>::pop_index(const int index) {
    type* new_mas = new type[size - 1];
    for (int i = 0; i < size - 1; i++) {
        if (i < index)
            new_mas[i] = dlist[i];
        if (i >= index)
            new_mas[i] = dlist[i + 1];
    }
    size--;
    delete[] dlist;
    dlist = new_mas;
}

template <typename type> void dynlist<type>::resize(const int new_size) {
    type* ndlist = new type[new_size]{};
    for (int i = 0; i < new_size; i++) {
        if (i <= size - 1)
            ndlist[i] = dlist[i];
        else
            break;
    }
    size = new_size;
    delete[] dlist;
    dlist = ndlist;
}

template <typename type> type dynlist<type>::max() const {
    type max = dlist[0];
    for (int i = 0; i < size; i++)
        if (max < dlist[i])
            max = dlist[i];
    return max;
}

template <typename type> type dynlist<type>::max(int& index) const {
    type max = dlist[0];
    for (int i = 0; i < size; i++)
        if (max < dlist[i]) {
            max = dlist[i];
            index = i;
        }
    return max;
}

template <typename type> type dynlist<type>::min() const {
    type min = dlist[0];
    for (int i = 0; i < size; i++)
        if (min > dlist[i])
            min = dlist[i];
    return min;
}

template <typename type> type dynlist<type>::min(int& index) const {
    type min = dlist[0];
    for (int i = 0; i < size; i++)
        if (min > dlist[i]) {
            min = dlist[i];
            index = i;
        }
    return min;
}


template <typename type> void dynlist<type>::QuickSort(size_t const left, size_t const right) {
    static type temp;
    size_t i = left, j = right;
    type pivot = dlist[left + ((right - left + 1) >> 1)];

    while (i <= j)
    {
        while (dlist[i] < pivot) ++i;
        while (dlist[j] > pivot) --j;

        if (i <= j)
        {
            temp = dlist[i];
            dlist[i] = dlist[j];
            dlist[j] = temp;
            ++i;
            --j;
        }
    }
    if (j > left)
        QuickSort(left, j);
    if (i < right)
        QuickSort(i, right);
}

template <typename type> void dynlist<type>::sort() {
    QuickSort(0, size - 1);
}

template <typename type> void dynlist<type>::reverse() {
    type* rlist = new type[size];
    for (int i = 0; i < size; i++)
        rlist[i] = *at(-(i + 1));
    delete[] dlist;
    dlist = rlist;
}
