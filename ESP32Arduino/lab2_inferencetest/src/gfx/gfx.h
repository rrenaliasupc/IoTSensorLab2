

void GFX_Init(void);

void Gfx_InitialScreen(bool IsCapture);

void Gfx_WaitingForGesture(void);
void Gfx_Recording(void);
void Gfx_Presenting_RecognitedType(int Type,float probability);

void Gfx_RecordNewGesture(int Type, int Types, int CurrentSample,int TotalSamples);
void Gfx_EndDataCollection(void);

void Gfx_print(char* text);
void Gfx_println(char* text);