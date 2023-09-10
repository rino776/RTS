#pragma once
#include <thread>
#include <RenderingEngine.h>
namespace client{
class Console
{
public:
    Console();
    std::thread start();
    void update();
    void init();
    bool shouldClose() { return m_shouldClose; }
    void setShouldClose(bool bShouldClose) { m_shouldClose = bShouldClose; }

private:
    bool m_shouldClose;
};
}
