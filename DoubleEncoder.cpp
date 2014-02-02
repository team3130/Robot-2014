#include "DoubleEncoder.h"
void DoubleEncoder::reset(){
	a->Reset();
	b->Reset();
	a->Start();
	b->Start();
}
