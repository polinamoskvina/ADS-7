// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <string>
#include <iostream>

template<typename T>
class TPQueue {
    struct ELEM {
        ELEM* follow;
        T infa;
    };

 public:
    TPQueue(): top(nullptr), end(nullptr) {}
    ~TPQueue() {
        while (top) {
            pop();
        }
    }
    T pop() {
        if (top) {
            ELEM* temp = top->follow;
            T infa = top->infa;
            delete top;
            top = temp;
            return infa;
        } else {
            throw(std::string("Is empty"));
        }
    }
    void push(const T& infa) {
        if (top && end) {
            if (infa.prior > top->infa.prior) {
                ELEM* temp = create(infa);
                temp->follow = top;
                top = temp;
            } else if (end->infa.prior >= infa.prior) {
                ELEM* temp = create(infa);
                end->follow = temp;
                end = temp;
            } else {
                ELEM* temp = create(infa);
                ELEM* current = top;
                while (current->follow->infa.prior >= infa.prior) {
                    current = current->follow;
                }
                temp->follow = current->follow;
                current->follow = temp;
            }
        } else {
            top = create(infa);
            end = top;
        }
    }

 private:
    ELEM* top;
    ELEM* end;
    ELEM* create(const T& infa) {
        ELEM* element = new ELEM;
        element->infa = infa;
        element->follow = nullptr;
        return element;
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
