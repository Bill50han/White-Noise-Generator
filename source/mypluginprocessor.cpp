//------------------------------------------------------------------------
// Copyright(c) 2023 Bill50han.
//------------------------------------------------------------------------

#include "mypluginprocessor.h"
#include "myplugincids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

#include "pluginterfaces/vst/ivstevents.h"

using namespace Steinberg;

namespace MyCompanyName {
//------------------------------------------------------------------------
// White_Noise_GeneratorProcessor
//------------------------------------------------------------------------
White_Noise_GeneratorProcessor::White_Noise_GeneratorProcessor ()
{
	//--- set the wanted controller for our processor
	setControllerClass (kWhite_Noise_GeneratorControllerUID);
}

//------------------------------------------------------------------------
White_Noise_GeneratorProcessor::~White_Noise_GeneratorProcessor ()
{}

//------------------------------------------------------------------------
tresult PLUGIN_API White_Noise_GeneratorProcessor::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated
	//---always initialize the parent-------
	tresult result = AudioEffect::initialize (context);
	// if everything Ok, continue
	if (result != kResultOk)
	{
		return result;
	}

	//--- create Audio IO ------
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

	/* If you don't need an event bus, you can remove the next line */
	addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API White_Noise_GeneratorProcessor::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!
	
	//---do not forget to call parent ------
	return AudioEffect::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API White_Noise_GeneratorProcessor::setActive (TBool state)
{
	//--- called when the Plug-in is enable/disable (On/Off) -----
	return AudioEffect::setActive (state);
}

std::mt19937 whitenoisernd(time(0));

//------------------------------------------------------------------------
tresult PLUGIN_API White_Noise_GeneratorProcessor::process (Vst::ProcessData& data)
{
	//--- First : Read inputs parameter changes-----------

    /*if (data.inputParameterChanges)
    {
        int32 numParamsChanged = data.inputParameterChanges->getParameterCount ();
        for (int32 index = 0; index < numParamsChanged; index++)
        {
            if (auto* paramQueue = data.inputParameterChanges->getParameterData (index))
            {
                Vst::ParamValue value;
                int32 sampleOffset;
                int32 numPoints = paramQueue->getPointCount ();
                switch (paramQueue->getParameterId ())
                {
				}
			}
		}
	}*/
	
	//--- Here you have to implement your processing
	/*Steinberg::Vst::IEventList* eventList = data.inputEvents;
	if (eventList)
	{
		int32 c = eventList->getEventCount();
		Vst::Event e = { 0 };

		for (size_t l = 0; l < c; l++)
		{
			eventList->getEvent(l, e);
			if ((e.flags && 1) == true && e.type == e.kNoteOffEvent)
			{
				goto end;
			}
			if ((e.flags&&1)==true && e.type==e.kNoteOnEvent)
			{*/
				Vst::Sample32* output32;
				Vst::Sample64* output64;

				for (size_t j = 0; j < data.numOutputs; j++)
				{
					for (size_t k = 0; k < data.outputs[j].numChannels; k++)
					{
						if (data.symbolicSampleSize == Vst::kSample32)
						{
							output32 = data.outputs[j].channelBuffers32[k];

							for (int32 i = 0; i < data.numSamples; ++i)
							{
								// 生成随机数，范围为-1到1
								float randomSample = ((float)whitenoisernd() / whitenoisernd.max()) * 2 - 1;

								// 将生成的样本写入输出缓冲区
								output32[i] = randomSample;
							}
						}
						else if (data.symbolicSampleSize == Vst::kSample64)
						{
							output64 = data.outputs[j].channelBuffers64[k];

							for (int32 i = 0; i < data.numSamples; ++i)
							{
								// 生成随机数，范围为-1到1
								float randomSample = ((double)whitenoisernd() / whitenoisernd.max()) * 2 - 1;

								// 将生成的样本写入输出缓冲区
								output64[i] = randomSample;
							}
						}
					}
				}
				/*goto end;
			}
		}
		
	}*/
	
end:

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API White_Noise_GeneratorProcessor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----
	return AudioEffect::setupProcessing (newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API White_Noise_GeneratorProcessor::canProcessSampleSize (int32 symbolicSampleSize)
{
	// by default kSample32 is supported
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;

	// disable the following comment if your processing support kSample64
	 if (symbolicSampleSize == Vst::kSample64)
		return kResultTrue; 

	return kResultFalse;
}

//------------------------------------------------------------------------
tresult PLUGIN_API White_Noise_GeneratorProcessor::setState (IBStream* state)
{
	// called when we load a preset, the model has to be reloaded
	IBStreamer streamer (state, kLittleEndian);
	
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API White_Noise_GeneratorProcessor::getState (IBStream* state)
{
	// here we need to save the model
	IBStreamer streamer (state, kLittleEndian);

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace MyCompanyName
