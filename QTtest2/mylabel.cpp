#ifndef MYLABEL_CPP
#define MYLABEL_CPP


#include "mylabel.h"


void myLabel::mousePressEvent(QMouseEvent* event)
{
    if(event->button()==Qt::LeftButton)
    {
        QPoint point=event->pos();
        //cout<<"mousePressEvent"<<endl;
        //cout<<point.x()<<" "<<point.y()<<endl;
       emit mouseClicked(point);
    }
}

#endif // MYLABEL_CPP
