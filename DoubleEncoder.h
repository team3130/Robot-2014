#include "WPILib.h"
class DoubleEncoder: public PIDSource{
private:
	Encoder* a;
	Encoder* b;
public:
	DoubleEncoder(Encoder* aa, Encoder* bb){
		a=aa;
		b=bb;
		a->SetPIDSourceParameter(PIDSource::kDistance);
		b->SetPIDSourceParameter(PIDSource::kDistance);
	}
	void setPIDSourceParameter(PIDSourceParameter ps){
		a->SetPIDSourceParameter(ps);
		b->SetPIDSourceParameter(ps);
	}
	void setDistancePerPulse(double d){
		a->SetDistancePerPulse(d);
		b->SetDistancePerPulse(d);
	}
	void reset();
	double PIDGet(){
		return (a->GetDistance()+b->GetDistance())/2.0;
	}
};
