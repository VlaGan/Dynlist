// dynlist class

template <typename type> class dynlist {
private:
    int size;
    type* dlist;

public:
    dynlist(const int new_size);
    ~dynlist();

    inline type* operator[](const int index);
    inline type* at(const int index);
    void operator+=(const type value);
    void operator-=(const type value);
    void operator*=(const type value);
    void operator/=(const type value);

    inline const int len() const;
    void print();

    void push_back(type value);
    void push_front(type value);
    void push_index(int index, type value);

    void pop_back();
    void pop_front();
    void pop_index(int index);

    void resize(const int new_size);
    
    type max();
    type max(int &index);
    type min();
    type min(int& index);
    void sort();

    void reverse();
    void set();


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

template <typename type> void dynlist<type>::operator+=(const type value) {
    for (int i = 0; i < size; i++)
        dlist[i] += value;
}

template <typename type> void dynlist<type>::operator-=(const type value) {
    for (int i = 0; i < size; i++)
        dlist[i] -= value;
}

template <typename type> void dynlist<type>::operator*=(const type value) {
    for (int i = 0; i < size; i++)
        dlist[i] *= value;
}

template <typename type> void dynlist<type>::operator/=(const type value) {
    for (int i = 0; i < size; i++)
        dlist[i] /= value;
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

template <typename type> void dynlist<type>::push_index(int index, type value) {
    if (index > 0 && index > size - 1)
        return;
    else if (index < 0 && abs(index) > size+1)
        return;

    if (index < 0)
        index = size + index + 1;

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

template <typename type> void dynlist<type>::pop_index(int index) {
    if (index > 0 && index > size - 1)
        return;
    else if (index < 0 && abs(index) > size)
        return;

    if (index < 0)
        index = size + index;

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

template <typename type> type dynlist<type>::max(){
    type max = dlist[0];
    for (int i = 0; i < size; i++)
        if (max < dlist[i])
            max = dlist[i];
    return max;
}

template <typename type> type dynlist<type>::max(int& index){
    type max = dlist[0];
    for (int i = 0; i < size; i++)
        if (max < dlist[i]) {
            max = dlist[i];
            index = i;
        }
    return max;
}

template <typename type> type dynlist<type>::min(){
    type min = dlist[0];
    for (int i = 0; i < size; i++)
        if (min > dlist[i])
            min = dlist[i];
    return min;
}

template <typename type> type dynlist<type>::min(int& index){
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
    type pt = dlist[left + ((right - left + 1) >> 1)];

    while (i <= j){
        while (dlist[i] < pt) ++i;
        while (dlist[j] > pt) --j;

        if (i <= j){
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

// minus speed -- for first time
template <typename type> void dynlist<type>::set() {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (i != j)
                if (dlist[i] == dlist[j])
                    pop_index(j);
}
