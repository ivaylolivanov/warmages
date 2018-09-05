#ifndef ANIMATION
#define ANIMATIN


struct Animation
{
    int index;
    int frames;
    int delay;

    Animation() {}

    Animation( int indx, int frm, int dly ) {
	index  = indx;
	frames = frm;
	delay  = dly;
    }

};

#endif
