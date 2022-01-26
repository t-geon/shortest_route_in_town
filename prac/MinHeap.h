#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <utility>
#include <vector>

template<typename TKey, typename TValue>
class MinHeap
{
private:
    // array for the elements which should be heap-sorted
    std::vector<std::pair<TKey, TValue>> m_vec;

public:
    MinHeap() {
        TKey a1 = 0; TValue a2 = 0;
        m_vec.push_back(std::make_pair(a1, a2));
    }

    // <summary>
    // insert key-value pair
    // </summary>
    //
    // <param name="key">
    // the key that is used for sorting
    // </param>
    //
    // <param name="value">
    // the value that is managed in this heap
    // </param>
    void Push(TKey key, TValue value) {
        m_vec.push_back(std::make_pair(key, value));
        for (int i = m_vec.size() - 1; i > 1; i = i / 2) {
            if (m_vec[i].first < m_vec[i / 2].first) { swap(m_vec[i], m_vec[i / 2]); }
        }
    }


    // <summary>
    // remove the minimum element
    // </summary>
    void Pop() {
        if (m_vec.size() == 1) { return; }
        swap(m_vec[1], m_vec[m_vec.size() - 1]);//맨 뒤 값을 맨 위로 올리기
        m_vec.pop_back();//head삭제


        for (int i = 1; i * 2 <= m_vec.size() - 1;)//head부터 자식으로 내려가면서 확인
        {
            if (i * 2 + 1 <= m_vec.size() - 1) {//오른자식이 있을 때
                if (m_vec[i].first < m_vec[i * 2].first && m_vec[i].first < m_vec[i * 2 + 1].first) { break; }//head가 제일 작을 

                 //head보다 child가 더 작을 때
                else if (m_vec[i * 2].first < m_vec[i * 2 + 1].first) {//left<right
                    swap(m_vec[i], m_vec[i * 2]);
                    i = i * 2;
                }
                else {
                    swap(m_vec[i], m_vec[i * 2 + 1]);//left>right
                    i = i * 2 + 1;
                }
            }
            else {//왼쪽만 확인(오른 자식이 없을 )
                if (m_vec[i].first < m_vec[i * 2].first) { break; }
                else {
                    swap(m_vec[i], m_vec[i * 2]);
                    i = i * 2;
                }
            }
        }
    }


    // <summary>
    // get the minimum element
    // </summary>
    //
    // <returns>
    // the minimum element
    // </returns>
    std::pair<TKey, TValue> Top() {
        if (m_vec.size() == 1) {
            std::pair<TKey, TValue> re = std::make_pair(NULL, NULL);
            return re;
        }
        else { return m_vec[1]; }
    }


    // <summary>
    // get the key-value pair which the value is the same as the target
    // </summary>
    //
    // <returns>
    // the key-value pair which the value is the same as the target
    // </returns>
    std::pair<TKey, TValue> Get(TValue target) {
        for (int i = m_vec.size() - 1; i >= 1; i--) { //뒤에서 부터 찾는다.
            if (m_vec[i].second == target) { return m_vec[i]; }
        }
        std::pair<TKey, TValue> re = std::make_pair(NULL, NULL);
        return re;//없으면 NULL반환
    }


    // <summary>
    // check whether this heap is empty or not
    // </summary>
    //
    // <returns>
    // true if this heap is empty
    // </returns>
    bool IsEmpty() {
        if (m_vec.size() == 1) { return 1; }
        else { return 0; }
    }


    // <summary>
    // change the key of the node which the value is the target.<para/>
    // In general, the newKey should be smaller than the old key.<para/>
    // </summary>
    //
    // <parma name="target">
    // the target to change the key
    // </param>
    //
    // <param name="newKey">
    // new key for the target
    // </param>
    void DecKey(TValue target, TKey newKey) {
        for (int i = m_vec.size() - 1; i >= 1; i--) { //뒤에서 부터 찾는다.
            //TValue v = m_vec[i].second;
            if (m_vec[i].second == target) {
                //TKey* k= &m_vec[i].first;
                if (m_vec[i].first > newKey) {
                    m_vec[i].first = newKey; //key를 바꾼다.
                    for (int j = i; j > 1; j = j / 2) {
                        if (m_vec[j] < m_vec[j / 2]) { swap(m_vec[j], m_vec[j / 2]); }
                    }
                }
                return;
            }
        }
        return;
    }
    private:
        // <summary>
        // heap-sort, heapify.<para/>
        // this function can be called recursively
        // </summary>
        void Heapify(int index) {
            int c = 2 * index;
            if (c < m_vec.size()) {
                if (m_vec[c] < m_vec[c + 1]) {
                    c += 1;
                }
            }
            if (m_vec[index] < m_vec[c]) {
                swap(m_vec[index], m_vec[c]);
                if (c <= m_vec.size() / 2) { Heapify(c); }
            }
        };
};

#endif
