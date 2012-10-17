typedef enum {_taLeft, _taCenter, _taRight} TTextAlign;

typedef struct Screen TScreen;

typedef struct  Box {
  TScreen*  OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          Pen_Width;
  unsigned int  Pen_Color;
  char          Visible;
  char          Active;
  char          Transparent;
  char          Gradient;
  char          Gradient_Orientation;
  unsigned int  Gradient_Start_Color;
  unsigned int  Gradient_End_Color;
  unsigned int  Color;
  char          PressColEnabled;
  unsigned int  Press_Color;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TBox;

typedef struct  Box_Round {
  TScreen*  OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  char          Pen_Width;
  unsigned int  Pen_Color;
  char          Visible;
  char          Active;
  char          Transparent;
  char          Gradient;
  char          Gradient_Orientation;
  unsigned int  Gradient_Start_Color;
  unsigned int  Gradient_End_Color;
  unsigned int  Color;
  char          Corner_Radius;
  char          PressColEnabled;
  unsigned int  Press_Color;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TBox_Round;

struct Screen {
  unsigned int           Color;
  unsigned int           Width;
  unsigned int           Height;
  unsigned short         ObjectsCount;
  unsigned int           BoxesCount;
  TBox                   * const code *Boxes;
  unsigned int           Boxes_RoundCount;
  TBox_Round             * const code *Boxes_Round;
};

extern   TScreen                Screen1;
extern   TBox                   FPianoKey;
extern   TBox                   GPianoKey;
extern   TBox                   APianoKey;
extern   TBox                   BPianoKey;
extern   TBox                   CPianoKey;
extern   TBox                   DPianoKey;
extern   TBox                   EPianoKey;
extern   TBox_Round             DsPianoKey;
extern   TBox_Round             CsPianoKey;
extern   TBox_Round             AsPianoKey;
extern   TBox_Round             GsPianoKey;
extern   TBox_Round             FsPianoKey;
extern   TBox                   * const code Screen1_Boxes[7];
extern   TBox_Round             * const code Screen1_Boxes_Round[5];



/////////////////////////
// Events Code Declarations
void APianoKeyOnPress();
void AsPianoKeyOnPress();
void BPianoKeyOnPress();
void CPianoKeyOnPress();
void CsPianoKeyOnPress();
void DPianoKeyOnPress();
void DsPianoKeyOnPress();
void EPianoKeyOnPress();
void FPianoKeyOnPress();
void FsPianoKeyOnPress();
void GPianoKeyOnPress();
void GsPianoKeyOnPress();
/////////////////////////

/////////////////////////////////
// Caption variables Declarations
extern char FPianoKey_Caption[];
extern char GPianoKey_Caption[];
extern char APianoKey_Caption[];
extern char BPianoKey_Caption[];
extern char CPianoKey_Caption[];
extern char DPianoKey_Caption[];
extern char EPianoKey_Caption[];
extern char DsPianoKey_Caption[];
extern char CsPianoKey_Caption[];
extern char AsPianoKey_Caption[];
extern char GsPianoKey_Caption[];
extern char FsPianoKey_Caption[];
/////////////////////////////////

void DrawScreen(TScreen *aScreen);
void DrawBox(TBox *ABox);
void DrawRoundBox(TBox_Round *Around_box);
void Check_TP();
void Start_TP();
