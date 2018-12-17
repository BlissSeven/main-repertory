#ifndef OBSERVER_MAINFORM_HPP
#define OBSERVER_MAINFORM_HPP

class MainForm:public Form,public IProgess
{
        TextBox* textfilepath;
        TextBox* txtfilenumber;
        ProgressBar* progressbar;
public:
        void ButtonClick()
        {
            string filepath=txtfilepath->getText();
            int number=atoi(txtFileNumber->getText().c_str());
            consolenotifier cn;
           //FileSplitter splitter(filepath,number,progessbar);
            FileSplitter splitter(filepath,number,progessbar);
            splitter.addIProgess(this);
            splitter.addIProgess(&cn);
            splitter.split();
        }
        virtual void Doprogess(float value)
        {
            progressbar->setvalue(value);
        }
};
class consolenotifier:public IProgess
{
  public:
    virtual void Doprogess(float value)
        cout<<"."<<endl;
};
#endif // OBSERVER_MAINFORM_HPP
