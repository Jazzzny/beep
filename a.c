// morsebeeper
int main(void)
{
    EventRecord event;
    WindowPtr window;
	ControlHandle shortButton;
	ControlHandle longButton;
	Rect shortButtonRect;
	Rect longButtonRect;

	InitGraf(&qd.thePort);
	InitWindows();

    window = GetNewCWindow(128, NULL, (WindowPtr)-1);

	ShowWindow(window);

	SetPort(window);

	// Add the title text, bold
	MoveTo(45, 20);
	TextFont(0);
	TextSize(20);
	DrawString("\pMorseBeep");


	// back to normal text
	TextFont(1);
	TextSize(12);


	// now do the description
	MoveTo(10, 40);
	DrawString("\pMorse Code is a method of");
	MoveTo(10, 60);
	DrawString("\ptransmitting text information");
	MoveTo(10, 80);
	DrawString("\pas a series of on-off tones.");


	// the buttons
	shortButtonRect.top = 100;
	shortButtonRect.left = 10;
	shortButtonRect.bottom = 140;
	shortButtonRect.right = 95;
	shortButton = NewControl(window, &shortButtonRect, "\pShort Tone", true, 0, 0, 0, pushButProc, 129);

	longButtonRect.top = 100;
	longButtonRect.left = 105;
	longButtonRect.bottom = 140;
	longButtonRect.right = 190;
	longButton = NewControl(window, &longButtonRect, "\pLong Tone", true, 0, 0, 0, pushButProc, 130);


	ShowControl(shortButton);
	ShowControl(longButton);

    while (true)
    {
        if (WaitNextEvent(everyEvent, &event, 10L, nil))
        {
            switch (event.what)
            {
                case mouseDown:
                {
                    WindowPtr winPtr;
                    short part = FindWindow(event.where, &winPtr);
                    if (part == inGoAway && TrackGoAway(winPtr, event.where))
                    {
                        ExitToShell();
                        DisposeWindow(winPtr);
                    }
					else if (part == inContent)
					{
						ControlHandle control;
						short controlPart;
						Point mouse = event.where;
						short controlID;
						GlobalToLocal(&mouse);
						controlPart = FindControl(mouse, winPtr, &control);
						controlID = GetControlReference(control);
							if (controlID == 129)
							{
								SysBeep(30);
							}
							else if (controlID == 130)
							{
								// long tone
								SysBeep(1000);
							}

					}
                } break;
                case updateEvt:
                    BeginUpdate((WindowPtr)event.message);
                    SetPort((WindowPtr)event.message);
                    EndUpdate((WindowPtr)event.message);
                    break;
            }
        }
    }
    return 0;
}