/*
 * Project name:
     PiezoPiano.vtft
 * Version: 
     1.0
 * Description:
     This is an example of a simple piano for the Mikromedia Workstation's Piezo Buzzer.
     Tap the keys on the Piezo Piano to play a tune.
 * Generated by:
     Visual TFT
 * Created by:
     Andrew Hazelden
 * Email:
     andrew@andrewhazelden.com
 * Website:
     http://www.andrewhazelden.com
 * Date of creation
     8/27/2012
 * Time of creation
     9:24:19 PM
 * Test configuration:
     MCU:             P32MX460F512L
     Dev.Board:       MikroMMB_for_PIC32_hw_rev_1.10
                      http://www.mikroe.com/eng/products/view/595/mikrommb-for-pic32-board/
     Oscillator:      80000000 Hz
     SW:              mikroC PRO for PIC32
                      http://www.mikroe.com/eng/products/view/623/mikroc-pro-for-pic32/
                      
     Piezo Buzzer:    Mikromedia Workstation V7
                      http://www.mikroe.com/mikromedia/workstation-pic/
                      The Piezo Buzzer is on pin Group G4.2
                      Enable the DIP Switch SW3 - G4.2 Buzzer
                      
                      Note:
                      The PIC32 Mikromedia Workstation Piezo Buzzer = RF4

                      The dsPIC33 Mikromedia Workstation Piezo Buzzer = RF0

 */

#include "PiezoPiano_objects.h"

void main() {

  Start_TP();
  
  //PIC32 Mikromedia Piezo Buzzer = RF4 / Group 4.2
  Sound_Init(&PORTF, 4);
  
  while (1) {
    Check_TP();
  }

}