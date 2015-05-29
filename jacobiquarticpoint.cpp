#include "jacobiquarticpoint.h"
#include "printer.h"

JacobiQuarticPoint::JacobiQuarticPoint(Integer field)
{
    Field _temp(field);
    this->PointField= _temp;
    PointField.init(this->x,0);
    PointField.init(this->y,0);
    PointField.init(this->z,0);
    this->p;

}

JacobiQuarticPoint::JacobiQuarticPoint(Integer field,Givaro::Integer x, Givaro::Integer y, Givaro::Integer z, Point p)
{
   Field _temp(field);
   this->PointField = _temp;
   this->PointField.init(this->x,x);
   this->PointField.init(this->y,y);
   this->PointField.init(this->z,z);
   if (p.y1 !=Integer::zero)
       printer::Print(1,"it looks like the point is not of order 2");
   this->p = p;

}

JacobiQuarticPoint::JacobiQuarticPoint(Curve c, Integer field,Point p)
{
    Field _temp (field);
    Field::Element _tempEl, _tempEl2;
    this->PointField.init(_tempEl,c.a4);
    this->PointField.sub(_tempEl,_tempEl,p.x1);
    this->PointField.mul(_tempEl,_tempEl,2);
    this->x = _tempEl;

    this->PointField.init(_tempEl,c.a4);
    this->PointField.mul(_tempEl,_tempEl,2);
    this->PointField.add(_tempEl,_tempEl,p.x1);

    this->PointField.init(_tempEl2,c.a4);
    this->PointField.sub(_tempEl2,_tempEl2,p.x);
    this->PointField.mul(_tempEl2,_tempEl2,_tempEl2);

    this->PointField.mul(_tempEl,_tempEl2,_tempEl);
    this->PointField.init(_tempEl2,c.a6);
    this->PointField.mul(_tempEl2,_tempEl2,_tempEl2);

    this->PointField.add(_tempEl,_tempEl,_tempEl2);
    this->y = _tempEl;

    this->PointField.init(this->z,c.a6);







}

Point ToPoint();
static Point ToPoint(JacobiQuarticPoint p);
