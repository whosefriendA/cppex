#include <iostream>

// 使用你的名字替换YOUR_NAME
namespace WANGGANG
{
    template <class T>
    // list存储的节点
    struct node
    {
        node<T> *prev_;
        node<T> *next_;
        T data_;
        // 构造函数
        node(const T &data)
            : data_(data), prev_(nullptr), next_(nullptr)
        {
        }
        node()
            : prev_(nullptr), next_(nullptr)
        {
        }
        // 析构函数
        ~node()
        {
        }
    };

    template <class T>
    // 迭代器类
    struct iterator
    {
        typedef node<T> node_;
        typedef iterator<T> iterator_;
        node_ *node_ptr_;

        iterator(node_ *node_ptr)
            : node_ptr_(node_ptr)
        {
        }

        ~iterator()
        {
        }

        // 迭代到下一个节点
        // ++it
        iterator_ &operator++()
        {
            node_ptr_ = node_ptr_->next_;
            return *this;
        }

        // 迭代到前一个节点
        // --it
        iterator_ &operator--()
        {
            node_ptr_ = node_ptr_->prev_;
            return *this;
        }

        // it++
        iterator operator++(int)
        {
            iterator temp = *this;
            node_ptr_ = node_ptr_->next_;
            return temp;
        }

        // it--
        iterator operator--(int)
        {
            iterator temp = *this;
            node_ptr_ = node_ptr_->prev_;
            return temp;
        }

        // 指向迭代器中被访问的成员值
        T &operator*()
        {
            return node_ptr_->data_;
        }

        // 指向迭代器中被访问的成员指针
        T *operator->()
        {
            return &(node_ptr_->data_);
        }

        // 重载==
        bool operator==(const iterator_ &t) const
        {
            return node_ptr_ == t.node_ptr_;
        }

        // 重载!=
        bool operator!=(const iterator_ &t) const
        {
            return node_ptr_ != t.node_ptr_;
        }
    };

    template <class T>
    class list
    {
    public:
        typedef node<T> node_;
        typedef iterator<T> Iterator;

    private:
        node_ *head_; // 头节点,哨兵（不存储有效数据）
        size_t size_; // 存储的有效节点个数

    public:
        // 构造函数
        list()
        {
            head_ = new node_();
            head_->next_ = head_;
            head_->prev_ = head_;
            size_ = 0;
        }

        // 拷贝构造，要求实现深拷贝
        list(const list<T> &lt)
        {
            head_ = new node_();
            head_->next_ = head_;
            head_->prev_ = head_;
            size_ = 0;

            for (Iterator it = lt.begin(); it != lt.end(); ++it)
            {
                push_back(*it);
            }
        }

        template <class inputIterator>
        // 迭代器构造
        list(inputIterator begin, inputIterator end)
        {
            head_ = new node_();
            head_->next_ = head_;
            head_->prev_ = head_;
            size_ = 0;

            for (inputIterator it = begin; it != end; ++it)
            {
                push_back(*it);
            }
        }

        ~list()
        {
            clear();
            delete head_;
        }

        // 拷贝赋值
        list<T> &operator=(const list<T> &lt)
        {
            if (this != &lt)
            {
                clear();
                for (Iterator it = lt.begin(); it != lt.end(); ++it)
                {
                    push_back(*it);
                }
            }
            return *this;
        }

        // 清空list中的数据
        void clear()
        {
            while (!empty())
            {
                pop_back();
            }
        }

        // 返回容器中存储的有效节点个数
        size_t size() const
        {
            return size_;
        }

        // 判断是否为空
        bool empty() const
        {
            return size_ == 0;
        }

        // 尾插
        bool push_back(const T &data)
        {
            node_ *new_node = new node_(data);
            node_ *tail = head_->prev_;

            tail->next_ = new_node;
            new_node->prev_ = tail;
            new_node->next_ = head_;
            head_->prev_ = new_node;

            ++size_;
            return true;
        }

        // 头插
        bool push_front(const T &data)
        {
            node_ *new_node = new node_(data);
            node_ *first = head_->next_;

            new_node->next_ = first;
            first->prev_ = new_node;
            new_node->prev_ = head_;
            head_->next_ = new_node;

            ++size_;
            return true;
        }

        // 尾删
        bool pop_back()
        {
            if (empty())
                return false;

            node_ *tail = head_->prev_;
            node_ *new_tail = tail->prev_;

            new_tail->next_ = head_;
            head_->prev_ = new_tail;

            delete tail;
            --size_;
            return true;
        }

        // 头删
        bool pop_front()
        {
            if (empty())
                return false;

            node_ *first = head_->next_;
            node_ *new_first = first->next_;

            head_->next_ = new_first;
            new_first->prev_ = head_;

            delete first;
            --size_;
            return true;
        }

        // 默认新数据添加到pos迭代器的后面,根据back的方向决定插入在pos的前面还是后面
        bool insert(Iterator pos, const T &data, bool back = true)
        {
            node_ *new_node = new node_(data);
            node_ *current = pos.node_ptr_;

            if (back)
            {
                node_ *next_node = current->next_;
                current->next_ = new_node;
                new_node->prev_ = current;
                new_node->next_ = next_node;
                next_node->prev_ = new_node;
            }
            else
            {
                node_ *prev_node = current->prev_;
                prev_node->next_ = new_node;
                new_node->prev_ = prev_node;
                new_node->next_ = current;
                current->prev_ = new_node;
            }

            ++size_;
            return true;
        }

        // 删除pos位置的元素
        bool erase(Iterator pos)
        {
            if (pos == end())
                return false;

            node_ *current = pos.node_ptr_;
            node_ *prev_node = current->prev_;
            node_ *next_node = current->next_;

            prev_node->next_ = next_node;
            next_node->prev_ = prev_node;

            delete current;
            --size_;
            return true;
        }

        // 获得list第一个有效节点的迭代器
        Iterator begin() const
        {
            return Iterator(head_->next_);
        }

        // 获得list最后一个节点的下一个位置
        Iterator end() const
        {
            return Iterator(head_);
        }

        // 查找data对应的迭代器
        Iterator find(const T &data) const
        {
            for (Iterator it = begin(); it != end(); ++it)
            {
                if (*it == data)
                    return it;
            }
            return end();
        }

        // 获得第一个有效节点元素值
        T front() const
        {
            if (!empty())
                return head_->next_->data_;
            throw std::out_of_range("List is empty");
        }

        // 获得最后一个有效节点元素值
        T back() const
        {
            if (!empty())
                return head_->prev_->data_;
            throw std::out_of_range("List is empty");
        }
    };
};
