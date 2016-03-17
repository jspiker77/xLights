#ifndef PIANOEFFECT_H
#define PIANOEFFECT_H

#include "RenderableEffect.h"

#include <string>
#include <list>

class PianoEffect : public RenderableEffect
{
    public:
        PianoEffect(int id);
        virtual ~PianoEffect();
        virtual bool CanBeRandom() {return false;}
    
        virtual void Render(Effect *effect, const SettingsMap &settings, RenderBuffer &buffer);

    protected:
        virtual wxPanel *CreatePanel(wxWindow *parent);
    private:
    
		void RenderPiano(RenderBuffer &buffer, const int startmidi, const int endmidi, const bool sharps);
		void ReduceChannels(std::list<float>* pdata, int start, int end, bool sharps);
		void DrawPiano(RenderBuffer &buffer, std::list<float>* pdata, bool sharps, int start, int end);
		bool IsSharp(float f);
};

#endif // PIANOEFFECT_H
