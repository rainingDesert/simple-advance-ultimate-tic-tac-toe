#include "TTT.h"

int main(){
	char playType = 'a';
	char statType = 'a';
	int limitDepth = 8;
	int limitSim = 100000;
	double c = 0.5;
	Imp* imp = NULL;
	if(statType == 'a')
		imp =new Imp(statType, playType, 1, -1, 0, -2, limitDepth);
	else
		imp = new Imp(statType, playType, 1, -1, 0, -2, limitSim, c);

	imp->execution();
}