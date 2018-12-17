#ifndef FACTORY_MAINFORM2_HPP
#define FACTORY_MAINFORM2_HPP

class MainForm:public Form
{
    SplitterFactory* factory;
public:
    MainForm(SplitterFactory* factory1)
        :factory(factory1){}
    void Button_click(){
        ISplitter* splitter=factory->CreateSplitter();
        splitter->split();
    }
};
#endif // FACTORY_MAINFORM2_HPP
