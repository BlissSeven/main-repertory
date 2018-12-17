#ifndef FACTORY_MAINFORM1_HPP
#define FACTORY_MAINFORM1_HPP

class MainForm:public Form
{
public:
    void Button_click(){
        ISplitter* splitter=new BinarySplitter();
        splitter->split();
    }
};
#endif // FACTORY_MAINFORM1_HPP
