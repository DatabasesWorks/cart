#include "business.h"

Business::Business(QObject *parent) : QObject(parent)
{
    initStore();
}

void Business::initStore()
{

    m_store = {
        {"box", 5},
        {"noodle", 5},
        {"ball", 5},
    };
}
