#include "./Scene.h"
inline Scene &Scene::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}
char Scene::get(pos r, pos c) const
{
    pos row = r * width;
    return contents[row + c];
}
void Scene::some_member() const
{
    ++access_ctr;
}

inline Scene &Scene::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Scene &Scene::set(pos r, pos col, char c)
{
    contents[r * width + col] = c;
    return *this;
}
auto window_mgr::clear(SceneIndex i) -> void
{
    Scene &s = scenes[i];
    s.contents = std::string(s.height * s.width, ' ');
}