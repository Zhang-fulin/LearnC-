#include <string>
#include <vector>
#include <iostream>
class Scene;
class window_mgr
{
public:
    using SceneIndex = std::vector<Scene>::size_type;
    void clear(SceneIndex);

private:
    std::vector<Scene> scenes{};
};

class Scene
{
    friend class window_mgr;
    friend void window_mgr::clear(SceneIndex);
public:
    typedef std::string::size_type pos;
    Scene() = default;
    Scene(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht * wd, c) {}
    char get() const
    {
        return contents[cursor];
    }
    inline char get(pos ht, pos wd) const;
    Scene &move(pos r, pos c);

public:
    void some_member() const;

public:
    Scene &set(char);
    Scene &set(pos, pos, char);

public:
    Scene &display(std::ostream &os)
    {
        do_display(os);
        return *this;
    }
    const Scene &display(std::ostream &os) const
    {
        do_display(os);
        return *this;
    }

private:
    void do_display(std::ostream &os) const { os << contents; }

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    mutable size_t access_ctr;
};

