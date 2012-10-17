#include "PiezoPiano_objects.h"
#include "built_in.h"


// TFT module connections
char TFT_DataPort at LATE;
sbit TFT_RST at LATC1_bit;
sbit TFT_BLED at LATA9_bit;
sbit TFT_RS at LATB15_bit;
sbit TFT_CS at LATF12_bit;
sbit TFT_RD at LATD5_bit;
sbit TFT_WR at LATD4_bit;
char TFT_DataPort_Direction at TRISE;
sbit TFT_RST_Direction at TRISC1_bit;
sbit TFT_BLED_Direction at TRISA9_bit;
sbit TFT_RS_Direction at TRISB15_bit;
sbit TFT_CS_Direction at TRISF12_bit;
sbit TFT_RD_Direction at TRISD5_bit;
sbit TFT_WR_Direction at TRISD4_bit;
// End TFT module connections

// Touch Panel module connections
sbit DRIVEX_LEFT at LATB13_bit;
sbit DRIVEX_RIGHT at LATB11_bit;
sbit DRIVEY_UP at LATB12_bit;
sbit DRIVEY_DOWN at LATB10_bit;
sbit DRIVEX_LEFT_DIRECTION at TRISB13_bit;
sbit DRIVEX_RIGHT_DIRECTION at TRISB11_bit;
sbit DRIVEY_UP_DIRECTION at TRISB12_bit;
sbit DRIVEY_DOWN_DIRECTION at TRISB10_bit;
// End Touch Panel module connections

// Global variables
unsigned int Xcoord, Ycoord;
const ADC_THRESHOLD = 1000;
char PenDown;
void *PressedObject;
int PressedObjectType;
unsigned int caption_length, caption_height;
unsigned int display_width, display_height;

int _object_count;
unsigned short object_pressed;
TBox *local_box;
TBox *exec_box;
int box_order;
TBox_Round *local_round_box;
TBox_Round *exec_round_box;
int box_round_order;

void PMPWaitBusy() {
  while(PMMODEbits.BUSY);
}

void Set_Index(unsigned short index) {
  TFT_RS = 0;
  PMDIN = index;
  PMPWaitBusy();
}

void Write_Command( unsigned short cmd ) {
  TFT_RS = 1;
  PMDIN = cmd;
  PMPWaitBusy();
}

void Write_Data(unsigned int _data) {
  TFT_RS = 1;
  PMDIN = _data;
  PMPWaitBusy();
}


void Init_ADC() {
  AD1PCFG = 0xFFFF;
  PCFG12_bit = 0;
  PCFG13_bit = 0;
  // PMP setup
  ADC1_Init();
}
static void InitializeTouchPanel() {
  Init_ADC();
  TFT_Set_Active(Set_Index, Write_Command, Write_Data);
  TFT_Init(320, 240);

  TP_TFT_Init(320, 240, 13, 12);                                  // Initialize touch panel
  TP_TFT_Set_ADC_Threshold(ADC_THRESHOLD);                              // Set touch panel ADC threshold

  PenDown = 0;
  PressedObject = 0;
  PressedObjectType = -1;
}


/////////////////////////
  TScreen*  CurrentScreen;

  TScreen                Screen1;
  TBox                   FPianoKey;
  TBox                   GPianoKey;
  TBox                   APianoKey;
  TBox                   BPianoKey;
  TBox                   CPianoKey;
  TBox                   DPianoKey;
  TBox                   EPianoKey;
  TBox_Round             DsPianoKey;
  TBox_Round             CsPianoKey;
  TBox_Round             AsPianoKey;
  TBox_Round             GsPianoKey;
  TBox_Round             FsPianoKey;
  TBox                   * const code Screen1_Boxes[7]=
         {
         &FPianoKey,           
         &GPianoKey,           
         &APianoKey,           
         &BPianoKey,           
         &CPianoKey,           
         &DPianoKey,           
         &EPianoKey            
         };
  TBox_Round             * const code Screen1_Boxes_Round[5]=
         {
         &DsPianoKey,          
         &CsPianoKey,          
         &AsPianoKey,          
         &GsPianoKey,          
         &FsPianoKey           
         };




static void InitializeObjects() {
  Screen1.Color                     = 0xC618;
  Screen1.Width                     = 320;
  Screen1.Height                    = 240;
  Screen1.BoxesCount                = 7;
  Screen1.Boxes                     = Screen1_Boxes;
  Screen1.Boxes_RoundCount          = 5;
  Screen1.Boxes_Round               = Screen1_Boxes_Round;
  Screen1.ObjectsCount              = 12;


  FPianoKey.OwnerScreen     = &Screen1;
  FPianoKey.Order           = 0;
  FPianoKey.Left            = 0;
  FPianoKey.Top             = 0;
  FPianoKey.Width           = 46;
  FPianoKey.Height          = 240;
  FPianoKey.Pen_Width       = 1;
  FPianoKey.Pen_Color       = 0x0000;
  FPianoKey.Visible         = 1;
  FPianoKey.Active          = 1;
  FPianoKey.Transparent     = 1;
  FPianoKey.Gradient        = 0;
  FPianoKey.Gradient_Orientation    = 0;
  FPianoKey.Gradient_Start_Color    = 0xFFFF;
  FPianoKey.Gradient_End_Color      = 0xC618;
  FPianoKey.Color           = 0xFFFF;
  FPianoKey.PressColEnabled     = 0;
  FPianoKey.Press_Color     = 0xFFFF;
  FPianoKey.OnUpPtr         = 0;
  FPianoKey.OnDownPtr       = 0;
  FPianoKey.OnClickPtr      = 0;
  FPianoKey.OnPressPtr      = FPianoKeyOnPress;

  GPianoKey.OwnerScreen     = &Screen1;
  GPianoKey.Order           = 1;
  GPianoKey.Left            = 46;
  GPianoKey.Top             = 0;
  GPianoKey.Width           = 46;
  GPianoKey.Height          = 240;
  GPianoKey.Pen_Width       = 1;
  GPianoKey.Pen_Color       = 0x0000;
  GPianoKey.Visible         = 1;
  GPianoKey.Active          = 1;
  GPianoKey.Transparent     = 1;
  GPianoKey.Gradient        = 0;
  GPianoKey.Gradient_Orientation    = 0;
  GPianoKey.Gradient_Start_Color    = 0xFFFF;
  GPianoKey.Gradient_End_Color      = 0xC618;
  GPianoKey.Color           = 0xFFFF;
  GPianoKey.PressColEnabled     = 0;
  GPianoKey.Press_Color     = 0xFFFF;
  GPianoKey.OnUpPtr         = 0;
  GPianoKey.OnDownPtr       = 0;
  GPianoKey.OnClickPtr      = 0;
  GPianoKey.OnPressPtr      = GPianoKeyOnPress;

  APianoKey.OwnerScreen     = &Screen1;
  APianoKey.Order           = 2;
  APianoKey.Left            = 92;
  APianoKey.Top             = 0;
  APianoKey.Width           = 46;
  APianoKey.Height          = 240;
  APianoKey.Pen_Width       = 1;
  APianoKey.Pen_Color       = 0x0000;
  APianoKey.Visible         = 1;
  APianoKey.Active          = 1;
  APianoKey.Transparent     = 1;
  APianoKey.Gradient        = 0;
  APianoKey.Gradient_Orientation    = 0;
  APianoKey.Gradient_Start_Color    = 0xFFFF;
  APianoKey.Gradient_End_Color      = 0xC618;
  APianoKey.Color           = 0xFFFF;
  APianoKey.PressColEnabled     = 0;
  APianoKey.Press_Color     = 0xFFFF;
  APianoKey.OnUpPtr         = 0;
  APianoKey.OnDownPtr       = 0;
  APianoKey.OnClickPtr      = 0;
  APianoKey.OnPressPtr      = APianoKeyOnPress;

  BPianoKey.OwnerScreen     = &Screen1;
  BPianoKey.Order           = 3;
  BPianoKey.Left            = 138;
  BPianoKey.Top             = 0;
  BPianoKey.Width           = 46;
  BPianoKey.Height          = 240;
  BPianoKey.Pen_Width       = 1;
  BPianoKey.Pen_Color       = 0x0000;
  BPianoKey.Visible         = 1;
  BPianoKey.Active          = 1;
  BPianoKey.Transparent     = 1;
  BPianoKey.Gradient        = 0;
  BPianoKey.Gradient_Orientation    = 0;
  BPianoKey.Gradient_Start_Color    = 0xFFFF;
  BPianoKey.Gradient_End_Color      = 0xC618;
  BPianoKey.Color           = 0xFFFF;
  BPianoKey.PressColEnabled     = 0;
  BPianoKey.Press_Color     = 0xFFFF;
  BPianoKey.OnUpPtr         = 0;
  BPianoKey.OnDownPtr       = 0;
  BPianoKey.OnClickPtr      = 0;
  BPianoKey.OnPressPtr      = BPianoKeyOnPress;

  CPianoKey.OwnerScreen     = &Screen1;
  CPianoKey.Order           = 4;
  CPianoKey.Left            = 184;
  CPianoKey.Top             = 0;
  CPianoKey.Width           = 46;
  CPianoKey.Height          = 240;
  CPianoKey.Pen_Width       = 1;
  CPianoKey.Pen_Color       = 0x0000;
  CPianoKey.Visible         = 1;
  CPianoKey.Active          = 1;
  CPianoKey.Transparent     = 1;
  CPianoKey.Gradient        = 0;
  CPianoKey.Gradient_Orientation    = 0;
  CPianoKey.Gradient_Start_Color    = 0xFFFF;
  CPianoKey.Gradient_End_Color      = 0xC618;
  CPianoKey.Color           = 0xFFFF;
  CPianoKey.PressColEnabled     = 0;
  CPianoKey.Press_Color     = 0xFFFF;
  CPianoKey.OnUpPtr         = 0;
  CPianoKey.OnDownPtr       = 0;
  CPianoKey.OnClickPtr      = 0;
  CPianoKey.OnPressPtr      = CPianoKeyOnPress;

  DPianoKey.OwnerScreen     = &Screen1;
  DPianoKey.Order           = 5;
  DPianoKey.Left            = 230;
  DPianoKey.Top             = 0;
  DPianoKey.Width           = 46;
  DPianoKey.Height          = 240;
  DPianoKey.Pen_Width       = 1;
  DPianoKey.Pen_Color       = 0x0000;
  DPianoKey.Visible         = 1;
  DPianoKey.Active          = 1;
  DPianoKey.Transparent     = 1;
  DPianoKey.Gradient        = 0;
  DPianoKey.Gradient_Orientation    = 0;
  DPianoKey.Gradient_Start_Color    = 0xFFFF;
  DPianoKey.Gradient_End_Color      = 0xC618;
  DPianoKey.Color           = 0xFFFF;
  DPianoKey.PressColEnabled     = 0;
  DPianoKey.Press_Color     = 0xFFFF;
  DPianoKey.OnUpPtr         = 0;
  DPianoKey.OnDownPtr       = 0;
  DPianoKey.OnClickPtr      = 0;
  DPianoKey.OnPressPtr      = DPianoKeyOnPress;

  EPianoKey.OwnerScreen     = &Screen1;
  EPianoKey.Order           = 6;
  EPianoKey.Left            = 276;
  EPianoKey.Top             = 0;
  EPianoKey.Width           = 46;
  EPianoKey.Height          = 240;
  EPianoKey.Pen_Width       = 1;
  EPianoKey.Pen_Color       = 0x0000;
  EPianoKey.Visible         = 1;
  EPianoKey.Active          = 1;
  EPianoKey.Transparent     = 1;
  EPianoKey.Gradient        = 0;
  EPianoKey.Gradient_Orientation    = 0;
  EPianoKey.Gradient_Start_Color    = 0xFFFF;
  EPianoKey.Gradient_End_Color      = 0xC618;
  EPianoKey.Color           = 0xFFFF;
  EPianoKey.PressColEnabled     = 0;
  EPianoKey.Press_Color     = 0xFFFF;
  EPianoKey.OnUpPtr         = 0;
  EPianoKey.OnDownPtr       = 0;
  EPianoKey.OnClickPtr      = 0;
  EPianoKey.OnPressPtr      = EPianoKeyOnPress;

  DsPianoKey.OwnerScreen     = &Screen1;
  DsPianoKey.Order           = 7;
  DsPianoKey.Left            = 261;
  DsPianoKey.Top             = 1;
  DsPianoKey.Width           = 30;
  DsPianoKey.Height          = 170;
  DsPianoKey.Pen_Width       = 1;
  DsPianoKey.Pen_Color       = 0x0000;
  DsPianoKey.Visible         = 1;
  DsPianoKey.Active          = 1;
  DsPianoKey.Transparent     = 1;
  DsPianoKey.Gradient        = 0;
  DsPianoKey.Gradient_Orientation    = 0;
  DsPianoKey.Gradient_Start_Color    = 0xFFFF;
  DsPianoKey.Gradient_End_Color      = 0xC618;
  DsPianoKey.Color           = 0x0000;
  DsPianoKey.PressColEnabled     = 1;
  DsPianoKey.Press_Color     = 0x0000;
  DsPianoKey.Corner_Radius      = 3;
  DsPianoKey.OnUpPtr         = 0;
  DsPianoKey.OnDownPtr       = 0;
  DsPianoKey.OnClickPtr      = 0;
  DsPianoKey.OnPressPtr      = DsPianoKeyOnPress;

  CsPianoKey.OwnerScreen     = &Screen1;
  CsPianoKey.Order           = 8;
  CsPianoKey.Left            = 215;
  CsPianoKey.Top             = 1;
  CsPianoKey.Width           = 30;
  CsPianoKey.Height          = 170;
  CsPianoKey.Pen_Width       = 1;
  CsPianoKey.Pen_Color       = 0x0000;
  CsPianoKey.Visible         = 1;
  CsPianoKey.Active          = 1;
  CsPianoKey.Transparent     = 1;
  CsPianoKey.Gradient        = 0;
  CsPianoKey.Gradient_Orientation    = 0;
  CsPianoKey.Gradient_Start_Color    = 0xFFFF;
  CsPianoKey.Gradient_End_Color      = 0xC618;
  CsPianoKey.Color           = 0x0000;
  CsPianoKey.PressColEnabled     = 1;
  CsPianoKey.Press_Color     = 0x0000;
  CsPianoKey.Corner_Radius      = 3;
  CsPianoKey.OnUpPtr         = 0;
  CsPianoKey.OnDownPtr       = 0;
  CsPianoKey.OnClickPtr      = 0;
  CsPianoKey.OnPressPtr      = CsPianoKeyOnPress;

  AsPianoKey.OwnerScreen     = &Screen1;
  AsPianoKey.Order           = 9;
  AsPianoKey.Left            = 123;
  AsPianoKey.Top             = 1;
  AsPianoKey.Width           = 30;
  AsPianoKey.Height          = 170;
  AsPianoKey.Pen_Width       = 1;
  AsPianoKey.Pen_Color       = 0x0000;
  AsPianoKey.Visible         = 1;
  AsPianoKey.Active          = 1;
  AsPianoKey.Transparent     = 1;
  AsPianoKey.Gradient        = 0;
  AsPianoKey.Gradient_Orientation    = 0;
  AsPianoKey.Gradient_Start_Color    = 0xFFFF;
  AsPianoKey.Gradient_End_Color      = 0xC618;
  AsPianoKey.Color           = 0x0000;
  AsPianoKey.PressColEnabled     = 1;
  AsPianoKey.Press_Color     = 0x0000;
  AsPianoKey.Corner_Radius      = 3;
  AsPianoKey.OnUpPtr         = 0;
  AsPianoKey.OnDownPtr       = 0;
  AsPianoKey.OnClickPtr      = 0;
  AsPianoKey.OnPressPtr      = AsPianoKeyOnPress;

  GsPianoKey.OwnerScreen     = &Screen1;
  GsPianoKey.Order           = 10;
  GsPianoKey.Left            = 77;
  GsPianoKey.Top             = 1;
  GsPianoKey.Width           = 30;
  GsPianoKey.Height          = 170;
  GsPianoKey.Pen_Width       = 1;
  GsPianoKey.Pen_Color       = 0x0000;
  GsPianoKey.Visible         = 1;
  GsPianoKey.Active          = 1;
  GsPianoKey.Transparent     = 1;
  GsPianoKey.Gradient        = 0;
  GsPianoKey.Gradient_Orientation    = 0;
  GsPianoKey.Gradient_Start_Color    = 0xFFFF;
  GsPianoKey.Gradient_End_Color      = 0xC618;
  GsPianoKey.Color           = 0x0000;
  GsPianoKey.PressColEnabled     = 1;
  GsPianoKey.Press_Color     = 0x0000;
  GsPianoKey.Corner_Radius      = 3;
  GsPianoKey.OnUpPtr         = 0;
  GsPianoKey.OnDownPtr       = 0;
  GsPianoKey.OnClickPtr      = 0;
  GsPianoKey.OnPressPtr      = GsPianoKeyOnPress;

  FsPianoKey.OwnerScreen     = &Screen1;
  FsPianoKey.Order           = 11;
  FsPianoKey.Left            = 31;
  FsPianoKey.Top             = 1;
  FsPianoKey.Width           = 30;
  FsPianoKey.Height          = 170;
  FsPianoKey.Pen_Width       = 1;
  FsPianoKey.Pen_Color       = 0x0000;
  FsPianoKey.Visible         = 1;
  FsPianoKey.Active          = 1;
  FsPianoKey.Transparent     = 1;
  FsPianoKey.Gradient        = 0;
  FsPianoKey.Gradient_Orientation    = 0;
  FsPianoKey.Gradient_Start_Color    = 0xFFFF;
  FsPianoKey.Gradient_End_Color      = 0xC618;
  FsPianoKey.Color           = 0x0000;
  FsPianoKey.PressColEnabled     = 1;
  FsPianoKey.Press_Color     = 0x0000;
  FsPianoKey.Corner_Radius      = 3;
  FsPianoKey.OnUpPtr         = 0;
  FsPianoKey.OnDownPtr       = 0;
  FsPianoKey.OnClickPtr      = 0;
  FsPianoKey.OnPressPtr      = FsPianoKeyOnPress;
}

static char IsInsideObject (unsigned int X, unsigned int Y, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height) { // static
  if ( (Left<= X) && (Left+ Width - 1 >= X) &&
       (Top <= Y)  && (Top + Height - 1 >= Y) )
    return 1;
  else
    return 0;
}


#define GetBox(index)                 CurrentScreen->Boxes[index]
#define GetBox_Round(index)           CurrentScreen->Boxes_Round[index]

 void DeleteTrailingSpaces(char* str){
   char i;
   i = 0;
   while(1) {
   if(str[0] == ' ') {
      for(i = 0; i < strlen(str); i++) {
       str[i] = str[i+1];
      }
   }
   else
     break;
  }
 }

void DrawBox(TBox *ABox) {
  if (ABox->Visible == 1) {
    if (object_pressed == 1) {
      object_pressed = 0;
      TFT_Set_Brush(ABox->Transparent, ABox->Press_Color, ABox->Gradient, ABox->Gradient_Orientation, ABox->Gradient_End_Color, ABox->Gradient_Start_Color);
    }
    else {
      TFT_Set_Brush(ABox->Transparent, ABox->Color, ABox->Gradient, ABox->Gradient_Orientation, ABox->Gradient_Start_Color, ABox->Gradient_End_Color);
    }
    TFT_Set_Pen(ABox->Pen_Color, ABox->Pen_Width);
    TFT_Rectangle(ABox->Left, ABox->Top, ABox->Left + ABox->Width - 1, ABox->Top + ABox->Height - 1);
  }
}

void DrawRoundBox(TBox_Round *Around_box) {
    if (Around_box->Visible == 1) {
      if (object_pressed == 1) {
        object_pressed = 0;
        TFT_Set_Brush(Around_box->Transparent, Around_box->Press_Color, Around_box->Gradient, Around_box->Gradient_Orientation,
                      Around_box->Gradient_End_Color, Around_box->Gradient_Start_Color);
      }
      else {
        TFT_Set_Brush(Around_box->Transparent, Around_box->Color, Around_box->Gradient, Around_box->Gradient_Orientation,
                      Around_box->Gradient_Start_Color, Around_box->Gradient_End_Color);
      }
      TFT_Set_Pen(Around_box->Pen_Color, Around_box->Pen_Width);
      if (Around_box->Height > Around_box->Width) {
        TFT_Rectangle_Round_Edges(Around_box->Left + 1, Around_box->Top + 1,
          Around_box->Left + Around_box->Width - 2,
          Around_box->Top + Around_box->Height - 2, Around_box->Corner_Radius);
      }
      else
        {
          TFT_Rectangle_Round_Edges(Around_box->Left + 1, Around_box->Top + 1,
            Around_box->Left + Around_box->Width - 2,
            Around_box->Top + Around_box->Height - 2, Around_box->Corner_Radius);
        }
    }
}

void DrawScreen(TScreen *aScreen) {
 int order;
  unsigned short box_idx;
  TBox *local_box;
  unsigned short round_box_idx;
  TBox_Round *local_round_box;
  char save_bled, save_bled_direction;

  object_pressed = 0;
  order = 0;
  box_idx = 0;
  round_box_idx = 0;
  CurrentScreen = aScreen;

  if ((display_width != CurrentScreen->Width) || (display_height != CurrentScreen->Height)) {
    save_bled = TFT_BLED;
    save_bled_direction = TFT_BLED_Direction;
    TFT_BLED_Direction = 0;
    TFT_BLED           = 0;
    TFT_Set_Active(Set_Index, Write_Command, Write_Data);
    TFT_Init(CurrentScreen->Width, CurrentScreen->Height);
    TP_TFT_Init(CurrentScreen->Width, CurrentScreen->Height, 13, 12);                                  // Initialize touch panel
    TP_TFT_Set_ADC_Threshold(ADC_THRESHOLD);                              // Set touch panel ADC threshold
    TFT_Fill_Screen(CurrentScreen->Color);
    display_width = CurrentScreen->Width;
    display_height = CurrentScreen->Height;
    TFT_BLED           = save_bled;
    TFT_BLED_Direction = save_bled_direction;
  }
  else
    TFT_Fill_Screen(CurrentScreen->Color);


  while (order < CurrentScreen->ObjectsCount) {
    if (box_idx < CurrentScreen->BoxesCount) {
      local_box = GetBox(box_idx);
      if (order == local_box->Order) {
        box_idx++;
        order++;
        DrawBox(local_box);
      }
    }

    if (round_box_idx < CurrentScreen->Boxes_RoundCount) {
      local_round_box = GetBox_Round(round_box_idx);
      if (order == local_round_box->Order) {
        round_box_idx++;
        order++;
        DrawRoundBox(local_round_box);
      }
    }

  }
}

void Get_Object(unsigned int X, unsigned int Y) {
  box_order           = -1;
  box_round_order     = -1;
  //  Boxes
  for ( _object_count = 0 ; _object_count < CurrentScreen->BoxesCount ; _object_count++ ) {
    local_box = GetBox(_object_count);
    if (local_box->Active == 1) {
      if (IsInsideObject(X, Y, local_box->Left, local_box->Top,
                         local_box->Width, local_box->Height) == 1) {
        box_order = local_box->Order;
        exec_box = local_box;
      }
    }
  }

  //  Boxes with Round Edges
  for ( _object_count = 0 ; _object_count < CurrentScreen->Boxes_RoundCount ; _object_count++ ) {
    local_round_box = GetBox_Round(_object_count);
    if (local_round_box->Active == 1) {
      if (IsInsideObject(X, Y, local_round_box->Left, local_round_box->Top,
                         local_round_box->Width, local_round_box->Height) == 1) {
        box_round_order = local_round_box->Order;
        exec_round_box = local_round_box;
      }
    }
  }

  _object_count = -1;
  if (box_order >  _object_count )
    _object_count = box_order;
  if (box_round_order >  _object_count )
    _object_count = box_round_order;
}


static void Process_TP_Press(unsigned int X, unsigned int Y) {
  exec_box            = 0;
  exec_round_box      = 0;

  Get_Object(X, Y);


  if (_object_count != -1) {
    if (_object_count == box_order) {
      if (exec_box->Active == 1) {
        if (exec_box->OnPressPtr != 0) {
          exec_box->OnPressPtr();
          return;
        }
      }
    }

    if (_object_count == box_round_order) {
      if (exec_round_box->Active == 1) {
        if (exec_round_box->OnPressPtr != 0) {
          exec_round_box->OnPressPtr();
          return;
        }
      }
    }

  }
}

static void Process_TP_Up(unsigned int X, unsigned int Y) {

  switch (PressedObjectType) {
    // Box
    case 6: {
      if (PressedObject != 0) {
        exec_box = (TBox*)PressedObject;
        if ((exec_box->PressColEnabled == 1) && (exec_box->OwnerScreen == CurrentScreen)) {
          DrawBox(exec_box);
        }
        break;
      }
      break;
    }
    // Round Box
    case 7: {
      if (PressedObject != 0) {
        exec_round_box = (TBox_Round*)PressedObject;
        if ((exec_round_box->PressColEnabled == 1) && (exec_round_box->OwnerScreen == CurrentScreen)) {
          DrawRoundBox(exec_round_box);
        }
        break;
      }
      break;
    }
  }


  Get_Object(X, Y);


  if (_object_count != -1) {
  // Boxes
    if (_object_count == box_order) {
      if (exec_box->Active == 1) {
        if (exec_box->OnUpPtr != 0)
          exec_box->OnUpPtr();
        if (PressedObject == (void *)exec_box)
          if (exec_box->OnClickPtr != 0)
            exec_box->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  // Boxes with Round Edges
    if (_object_count == box_round_order) {
      if (exec_round_box->Active == 1) {
        if (exec_round_box->OnUpPtr != 0)
          exec_round_box->OnUpPtr();
        if (PressedObject == (void *)exec_round_box)
          if (exec_round_box->OnClickPtr != 0)
            exec_round_box->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  }
  PressedObject = 0;
  PressedObjectType = -1;
}

static void Process_TP_Down(unsigned int X, unsigned int Y) {

  object_pressed      = 0;
  exec_box            = 0;
  exec_round_box      = 0;

  Get_Object(X, Y);

  if (_object_count != -1) {
    if (_object_count == box_order) {
      if (exec_box->Active == 1) {
        if (exec_box->PressColEnabled == 1) {
          object_pressed = 1;
          DrawBox(exec_box);
        }
        PressedObject = (void *)exec_box;
        PressedObjectType = 6;
        if (exec_box->OnDownPtr != 0) {
          exec_box->OnDownPtr();
          return;
        }
      }
    }

    if (_object_count == box_round_order) {
      if (exec_round_box->Active == 1) {
        if (exec_round_box->PressColEnabled == 1) {
          object_pressed = 1;
          DrawRoundBox(exec_round_box);
        }
        PressedObject = (void *)exec_round_box;
        PressedObjectType = 7;
        if (exec_round_box->OnDownPtr != 0) {
          exec_round_box->OnDownPtr();
          return;
        }
      }
    }

  }
}

void Check_TP() {
  if (TP_TFT_Press_Detect()) {
    // After a PRESS is detected read X-Y and convert it to Display dimensions space
    if (TP_TFT_Get_Coordinates(&Xcoord, &Ycoord) == 0) {
      Process_TP_Press(Xcoord, Ycoord);
      if (PenDown == 0) {
        PenDown = 1;
        Process_TP_Down(Xcoord, Ycoord);
      }
    }
  }
  else if (PenDown == 1) {
    PenDown = 0;
    Process_TP_Up(Xcoord, Ycoord);
  }
}

void Init_MCU() {
  PMMODE = 0;
  PMAEN  = 0;
  PMCON  = 0;  // WRSP: Write Strobe Polarity bit
  PMMODEbits.MODE = 2;     // Master 2
  PMMODEbits.WAITB = 0;
  PMMODEbits.WAITM = 1;
  PMMODEbits.WAITE = 0;
  PMMODEbits.MODE16 = 1;   // 16 bit mode
  PMCONbits.CSF = 0;
  PMCONbits.PTRDEN = 1;
  PMCONbits.PTWREN = 1;
  PMCONbits.PMPEN = 1;
  TP_TFT_Rotate_180(0);
  TFT_Set_Active(Set_Index,Write_Command,Write_Data);
}

void Start_TP() {
  Init_MCU();

  InitializeTouchPanel();

  // You can get calibration constants using touch panel calibration example
  TP_TFT_Set_Calibration_Consts(76, 907, 77, 915);    // Set calibration constants

  InitializeObjects();
  display_width = Screen1.Width;
  display_height = Screen1.Height;
  DrawScreen(&Screen1);
}
