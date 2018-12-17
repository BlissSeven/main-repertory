#ifndef STATE1_HPP
#define STATE1_HPP
enum NetworkState
{
    Network_Open,
    Network_Close,
    Network_Connect,
};
class NetworkProcessor{
    NetworkState state;
public:
    void operation1(){
        if(state==Network_Open)
        {
            //
            state=Network_Close;
        }
        else if(state==Network_Close)
        {
            //
            state=Network_Connect;
        }
        else if(state=Network_Connect)
        {
            //
            state=Network_Open;
        }
    }
    void operation2(){
        if (state == Network_Open){

            //**********
            state = Network_Connect;
        }
        else if (state == Network_Close){

            //.....
            state = Network_Open;
        }
        else if (state == Network_Connect){

            //$$$$$$$$$$
            state = Network_Close;
        }
    }
    void operation3(){

    }
};
#endif // STATE1_HPP
