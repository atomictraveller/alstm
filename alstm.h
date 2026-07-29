#pragma once
#include "resource.h"

#define OUT_BUFFER_SIZE		16384	//	for audio buffer
int samplerate = 44100;
char action = 0;	//	1 = training, busy  :)
float out1[OUT_BUFFER_SIZE];     //  gui display string, let's use the same length
#define BUFFMASK ((OUT_BUFFER_SIZE << 2) - 1)	//	only used for display string
int p = 0;	//	play position
bool audition = 0;

float sout[88200] = { 0 };	//	

HDC hdcframe;
HBITMAP oldframe;
HBITMAP framebmp;
int* framebuf;

HDC hdcbackground;		HBITMAP oldbackground;	HBITMAP backgroundbmp;	int* backgroundbuf;
HWND hEdit = NULL;

int dispx = 1026;
int dispy = 594;
HFONT hfont0, hfont1;
short int timerate = 32;	//	rate for gui timer

bool showinput = 0;	//	show input field

unsigned long int rnd;
char stop = 0;	//	stop training flag

char wavpath[MAX_PATH] = "";	//	the way to write the file path hereabouts
int wavsamples = 0;
bool stereo = 0;

#define idim 1		//	input/output layer size
#define hidd 128	//	hidden layer size
#define wind 128	//	truncated BPTT depth, written for ^2 values
#define winp (wind + 1)
#define winm (wind - 1)

float sb = 0.f; //  replaces b, previous sample eg. known sample whereas current sample is target
char ch;

//	[dest][source] keeps with [i][j] code structuring

float nno[idim][hidd];		//	weights output layer
float obias[idim];			//	bias

float h0[winp][hidd] = { 0 };		//	hidden layer short term memory state
float c0[winp][hidd] = { 0 };		//	hidden layer long term memory state 'cell state'
float h0f[winp][hidd];		//	hidden layer forget gate
float h0i[winp][hidd];		//	hidden layer input gate
float h0m[winp][hidd];		//	hidden layer input node/potential memory activation
float h0o[winp][hidd];		//	hidden layer output gate

float nnh0hf[hidd][hidd];	//	weights hidden layer forget gate short term state
float nnh0hi[hidd][hidd];	//	weights hidden layer input gate short term state
float nnh0hm[hidd][hidd];	//	weights hidden layer input memory node short term state
float nnh0ho[hidd][hidd];	//	weights hidden layer output gate short term state

float nnh0if[hidd][idim];	//	weights hidden layer forget gate input
float nnh0ii[hidd][idim];	//	weights hidden layer input gate input
float nnh0im[hidd][idim];	//	weights hidden layer input memory node input
float nnh0io[hidd][idim];	//	weights hidden layer output gate input

float h0fbias[hidd];		//	bias hidden layer forget gate
float h0ibias[hidd];		//	bias hidden layer input gate
float h0mbias[hidd];		//	bias hidden layer input node/potential memory/candidate memory
float h0obias[hidd];		//	bias hidden layer output gate


float h[winp][hidd] = { 0 };		//	hidden layer short term memory state
float c[winp][hidd] = { 0 };		//	hidden layer long term memory state 'cell state'
float hf[winp][hidd];		//	hidden layer forget gate
float hi[winp][hidd];		//	hidden layer input gate
float hm[winp][hidd];		//	hidden layer input node/potential memory activation
float ho[winp][hidd];		//	hidden layer output gate

float nnhhf[hidd][hidd];	//	weights hidden layer forget gate short term state
float nnhhi[hidd][hidd];	//	weights hidden layer input gate short term state
float nnhhm[hidd][hidd];	//	weights hidden layer input memory node short term state
float nnhho[hidd][hidd];	//	weights hidden layer output gate short term state

float nnhif[hidd][hidd];	//	weights hidden layer forget gate input
float nnhii[hidd][hidd];	//	weights hidden layer input gate input
float nnhim[hidd][hidd];	//	weights hidden layer input memory node input
float nnhio[hidd][hidd];	//	weights hidden layer output gate input

float hfbias[hidd];			//	bias hidden layer forget gate
float hibias[hidd];			//	bias hidden layer input gate
float hmbias[hidd];			//	bias hidden layer input node/potential memory/candidate memory
float hobias[hidd];			//	bias hidden layer output gate



float dnno[idim][hidd];		//	deltas
float dobias[idim];


float dh0[hidd];
float dh[hidd];

float dnnh0hf[hidd][hidd];
float dnnh0hi[hidd][hidd];
float dnnh0hm[hidd][hidd];
float dnnh0ho[hidd][hidd];

float dnnh0if[hidd][idim];	//	not hidd hidd
float dnnh0ii[hidd][idim];
float dnnh0im[hidd][idim];
float dnnh0io[hidd][idim];

float dh0fbias[hidd];
float dh0ibias[hidd];
float dh0mbias[hidd];
float dh0obias[hidd];


float dnnhhf[hidd][hidd];
float dnnhhi[hidd][hidd];
float dnnhhm[hidd][hidd];
float dnnhho[hidd][hidd];

float dnnhif[hidd][hidd];
float dnnhii[hidd][hidd];
float dnnhim[hidd][hidd];
float dnnhio[hidd][hidd];

float dhfbias[hidd];
float dhibias[hidd];
float dhmbias[hidd];
float dhobias[hidd];


//int cin[wind];	//	was char.. input char per iteration
float samplein[wind];	//	"known" input sample per iteration

//float netin[idim];		//  "hot one" array to input char - not actually used...
float netout[wind][idim];	//	outout/prediction


float dh0_next[hidd];
float dh_next[hidd];

float dc0_next[hidd];
float dc_next[hidd];

float dhf_raw[hidd];
float dhi_raw[hidd];
float dhm_raw[hidd];
float dho_raw[hidd];
float dh0f_raw[hidd];
float dh0i_raw[hidd];
float dh0m_raw[hidd];
float dh0o_raw[hidd];



bool GRADNORM = 0;	//	use gradient normalisation
bool ADAM = 0;	//	use ADAM optimisation
int adamt = 0;

const float beta1 = 0.9f;
const float beta2 = 0.999f;
const float beta1m = 0.1f;
const float beta2m = 0.001f;
const float epsilon = 1e-8f;	//	"try e-4 or e-3 to smooth stuck phases, -8 is indy default"

//	ADAM weight should be zeroed at model initialisation and kept for the entire training
//	they are not currently stored with the model so you gotta add it if you want it

float mnno[idim][hidd] = { 0 };
float mobias[idim] = { 0 };

float mnnh0hf[hidd][hidd] = { 0 };
float mnnh0hi[hidd][hidd] = { 0 };
float mnnh0hm[hidd][hidd] = { 0 };
float mnnh0ho[hidd][hidd] = { 0 };
float mnnh0if[hidd][idim] = { 0 };
float mnnh0ii[hidd][idim] = { 0 };
float mnnh0im[hidd][idim] = { 0 };
float mnnh0io[hidd][idim] = { 0 };
float mh0fbias[hidd] = { 0 };
float mh0ibias[hidd] = { 0 };
float mh0mbias[hidd] = { 0 };
float mh0obias[hidd] = { 0 };

float mnnhhf[hidd][hidd] = { 0 };
float mnnhhi[hidd][hidd] = { 0 };
float mnnhhm[hidd][hidd] = { 0 };
float mnnhho[hidd][hidd] = { 0 };
float mnnhif[hidd][hidd] = { 0 };
float mnnhii[hidd][hidd] = { 0 };
float mnnhim[hidd][hidd] = { 0 };
float mnnhio[hidd][hidd] = { 0 };
float mhfbias[hidd] = { 0 };
float mhibias[hidd] = { 0 };
float mhmbias[hidd] = { 0 };
float mhobias[hidd] = { 0 };


float vnno[idim][hidd] = { 0 };
float vobias[idim] = { 0 };

float vnnh0hf[hidd][hidd] = { 0 };
float vnnh0hi[hidd][hidd] = { 0 };
float vnnh0hm[hidd][hidd] = { 0 };
float vnnh0ho[hidd][hidd] = { 0 };
float vnnh0if[hidd][idim] = { 0 };
float vnnh0ii[hidd][idim] = { 0 };
float vnnh0im[hidd][idim] = { 0 };
float vnnh0io[hidd][idim] = { 0 };
float vh0fbias[hidd] = { 0 };
float vh0ibias[hidd] = { 0 };
float vh0mbias[hidd] = { 0 };
float vh0obias[hidd] = { 0 };

float vnnhhf[hidd][hidd] = { 0 };
float vnnhhi[hidd][hidd] = { 0 };
float vnnhhm[hidd][hidd] = { 0 };
float vnnhho[hidd][hidd] = { 0 };
float vnnhif[hidd][hidd] = { 0 };
float vnnhii[hidd][hidd] = { 0 };
float vnnhim[hidd][hidd] = { 0 };
float vnnhio[hidd][hidd] = { 0 };
float vhfbias[hidd] = { 0 };
float vhibias[hidd] = { 0 };
float vhmbias[hidd] = { 0 };
float vhobias[hidd] = { 0 };


unsigned long int tests = 0;
int thismany = 0;	//	setup for 10 training sessions
bool do10x = 0;

float learn = 0.125f;
float temp = 1.f;   //  temperature/confidence.. low values = higher repeats/confidence
float ebuf = 0.f;   //  error accumulator
float edisp = 0.f;   //  averaged display coefficient (e^edisp = # chars not sure)

char dispix = 0;	//	for stepping through colours :)

float learnarr[34] = {
	0.5f,
	0.25f,
	0.125f, 0.1f,
	0.0625f,
	0.03125f,
	0.015625f, 0.01f,
	0.0078125f,
	0.00390625f,

	0.001953125f, 0.001f,
	0.0009765625f,
	0.00048828125f,
	0.000244140625f,
	0.0001220703125f, 0.0001f,
	0.00006103515625f,
	0.000030517578125f,
	0.0000152587890625f, 0.00001f,

	0.00000762939453125f,
	0.000003814697265625f,
	0.0000019073486328125f, 0.000001f,
	0.00000095367431640625f,
	0.000000476837158203125f,
	0.0000002384185791015625f,
	0.00000011920928955078125f, 0.0000001f,
	0.000000059604644775390625f,

	0.0000000298023223876953125f,
	0.00000001490116119384765625f, 0.00000001f
};
float temparr[10] = { 1.f, .9f, .8f, .7f, .6f, .5f, .4f, .3f, .2f, .1f };
int learnix = 1;    //11  indexes for incrementing parameter value
int tempix = 0;

char displayindex = 0;


/*
//	i'm told - ok to change wind during training, not okay to turn on/off ADAM (needs continuous coefficients throughout)

regularisation "10-4 to 10-2 prevents overfitting.." L2 style regularization here.. ;) changes large error response
temperature = confidence or enthusiasm for learning the subject..
ADAM.. helps not get stuck in local minima

*/