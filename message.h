#include <string>
#include <set>
class Message;
class Folder
{
public:
    void addMsg(Message *m)
    {
        messages.insert(m);
    };
    void remMsg(Message *m)
    {
        messages.erase(m);
    };

private:
    std::set<Message *> messages;
};
class Message
{
public:
    explicit Message(const std::string &s = "") : contents(s) {}
    Message(const Message &m) : contents(m.contents), folders(m.folders)
    {
        add_to_folders(m.folders);
    }
    Message &operator=(const Message &m){
        remove_from_folders(folders);
        contents = m.contents;
        folders = m.folders;
        add_to_folders(m.folders);
        return *this;
    };
    ~Message()
    {
        remove_from_folders(folders);
    }
    void save(Folder &f)
    {
        folders.insert(&f);
        f.addMsg(this);
    };
    void remove(Folder &f)
    {
        folders.erase(&f);
        f.remMsg(this);
    };

private:
    std::string contents;
    std::set<Folder *> folders;
    void add_to_folders(std::set<Folder*> folders)
    {
        for (auto f : folders)
        {
            f->addMsg(this);
        }
    };
    void remove_from_folders(std::set<Folder*> folders)
    {
        for (auto f : folders)
        {
            f->remMsg(this);
        }
    };
};