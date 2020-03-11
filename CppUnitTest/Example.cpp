#include "Example.h"

Example::Example()
    : m_isInitialized(false)
{
}

bool Example::isInitialized()
{
    return m_isInitialized;
}