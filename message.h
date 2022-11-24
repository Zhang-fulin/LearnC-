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
        add_to_other_folders(m);
    }
    Message(Message &&m) : folders(std::move(m.folders)), contents(std::move(m.contents))
    {
        m.remove_from_self_folders();

        for (auto &fold : folders)
        {
            fold->addMsg(this);
        }
        m.folders.clear();
    }
    Message &operator=(const Message &m)
    {
        remove_from_self_folders();
        contents = m.contents;
        folders = m.folders;
        add_to_other_folders(m);
        return *this;
    };
    Message& operator=(Message&& m) {
        
        if (this != &m) {
            remove_from_self_folders();
            m.remove_from_self_folders();

            contents = std::move(m.contents);
            folders = std::move(m.folders);
            for(auto & fold : folders) {
                fold->addMsg(this);
            }
            m.folders.clear();
        }
        return *this;
    }
    ~Message()
    {
        // remove_from_folders();
    }
    void add_to_folder(Folder &f)
    {
        folders.insert(&f);
        f.addMsg(this);
    };
    void remove_from_folder(Folder &f)
    {
        folders.erase(&f);
        f.remMsg(this);
    };

private:
    std::string contents;
    std::set<Folder *> folders;
    void add_to_other_folders(const Message &other)
    {
        for (auto f : other.folders)
        {
            f->addMsg(this);
        }
    };
    void remove_from_self_folders()
    {
        for (auto f : folders)
        {
            f->remMsg(this);
        }
    };
};