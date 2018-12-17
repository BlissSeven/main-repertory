#ifndef PROTOTYPE_CLIENT_HPP
#define PROTOTYPE_CLIENT_HPP

class MainForm:public Form
{
    ISplitter* prototype;
public:
    MainForm(ISplitter* prototype){
        this->prototype=prototype;
    }
    void Button1_Click(){
        ISplitter* splitter=
                prototype->clone();
        splitter->split();
    }
};
#endif // PROTOTYPE_CLIENT_HPP
